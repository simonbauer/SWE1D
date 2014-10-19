/*
 * FWave.hpp
 *
 *  Created on: Oct 18, 2014
 *      Author: kyu
 */

#ifndef FWAVE_HPP_
#define FWAVE_HPP_

#include <cassert>
#include <cmath>

namespace solver {
  template <typename T> class FWave;
}

template <typename T> class solver::FWave {
public:
	FWave();
	virtual ~FWave();

	typedef struct Quantity {
		T h;
		T hu;
	};
	static T g = 9.81f;

	 /**
	  * Compute left and right going net-updates.
	  *
	  * @param hl height on the left side of the edge.
	  * @param hr height on the right side of the edge.
	  * @param hul momentum on the left side of the edge.
	  * @param hur momentum on the right side of the edge.
	  * @param bl bathymetry on the left side of the edge.
	  * @param br bathymetry on the right side of the edge.
	  *
	  * @param outhl output height of the cell on the left side of the edge.
	  * @param outhr output height of the cell on the right side of the edge.
	  * @param outhul output momentum of the cell on the left side of the edge.
	  * @param outhur output momentum of the cell on the right side of the edge.
	  * @param outmaxWS will be set to: Maximum (linearized) wave speed -> Should be used in the CFL-condition.
	  */
	void computeNetupdates(T hl, T hr, T hul, T hur, T bl, T br, T &outhl, T &outhr, T &outhul, T &outhur, T &outmaxWS) {
		struct Quantity ql, qr;
		ql.h = hl;
		ql.hu = hul;
		qr.h = hr;
		qr.hu = hur;

		outhl = outhr = outhul = outhur  = 0;
		outmaxWS = 0;

		T lambda1 = computeWavespeed(&ql, &qr, -1.0f);
		T lambda2 = computeWavespeed(&ql, &qr, 1.0f);

		//Compute eigencoefficients [a_1 , a_2]  (Formula (8))
		T* ec[2] = computeEigencoeff(ql, qr, lambda1, lambda2);

		//Compute wave Z1 and Z2  (Formula (6))
		T* z1[2] = computeWaveZ(ec[0], lambda1);
		T* z2[2] = computeWaveZ(ec[1], lambda2);

		if(lambda1 > 0){
			outhr += z1[0];
			outhur += z1[1];
		}else if(lambda1 < 0){
			outhl += z1[0];
			outhul += z1[1];
		}
		if(lambda2 > 0){
			outhr += z2[0];
			outhur += z2[1];
		}else if(lambda2 < 0){
			outhl += z2[0];
			outhul += z2[1];
		}


	}

private:

	/**
	 * Approximate the true wave speeds using the data of left and right cell. (Formula (3))
	 *
	 * @param ql Quantity [h, (hu)T] of left cell
	 * @param qr Quantity [h, (hu)T] of right cell
	 * @param signum Determines whether the second part of the term u(ql,qr) +- sqrt(gh(ql,qr)) will be substracted or added.
	 * @return Wavespeed lambda_1 or lambda_2 (depending on signum > 0 or signum < 0)
	 */
	T computeWavespeed(Quantity *ql,Quantity *qr, float signum) {
		int sgn = 0;
		if (signum > 0.0f) {
			sgn = 1;
		} else if (signum < 0.0f) {
			sgn = -1;
		}
		return computeVeloRoe(ql, qr) + sgn * std::sqrt(g * computeHeightRoe(ql, qr));
	}

	/**
	 * Compute height h(hl,hr) = 0.5(hl + hr). (Formula (4))
	 *
	 * @param ql Quantity [h, (hu)T] of left cell
	 * @param qr Quantity [h, (hu)T] of right cell
	 * @return Height h_Roe
	 */
	T computeHeightRoe(Quantity *ql, Quantity *qr) {
		return 0.5 * (ql->h + qr->h);
	}

	/**
	 *                            (ul * sqrt(hl) + ur * sqrt(hr))
	 *  Compute height u(hl,hr) = --------------------------------    (Formula (4))
	 *                                (sqrt(hl) + sqrt(hr))
	 *
	 * @param ql Quantity [h, (hu)T] of left cell
	 * @param qr Quantity [h, (hu)T] of right cell
	 * @return Velocity u_Roe
	 */
	T computeVeloRoe(Quantity *ql,Quantity *qr) {
		T ul = ql->hu / ql->h;
		T ur = qr->hu / qr->h;
		return (ul * std::sqrt(ql->h) + ur * std::sqrt(qr->h)) / (std::sqrt(ql->h) + std::sqrt(qr->h));
	}

	/**
	 *  Compute the eigencoefficients a_p by using the wavespeeds and the flux formula. (Formula (8))
	 *
	 * @param ql Quantity [h, (hu)T] of left cell
	 * @param qr Quantity [h, (hu)T] of right cell
	 * @param lambda1 Wavespeed 1
	 * @param lambda2 Wavespeed 2
	 * @return T array of size 2, contains eigencoefficients a_1 and a_2
	 */
	T* computeEigencoeff(Quantity* ql, Quantity* qr, T lambda1, T lambda2){
		T* fqr = flux(qr);
		T* fql = flux(ql);

		T dFlux[2] = { fqr[0]-fql[0], fqr[1]-fql[1] };

		T mat[2][2] = { {1.0f, 1.0f}, {lambda1, lambda2}};

		inverseMatrix(mat);
		T a[2] = { mat[0][0] * dFlux[0] + mat[0][1] * dFlux[1],
					mat[1][0] * dFlux[0] + mat[1][1] * dFlux[1]};

		return a;
	}

	/**
	 *  Evaluating the flux formula f = [hu, hu^2 + 0.5*g*h^2]^T
	 *
	 * @param q Quantity to be used for the flux calculation
	 * @return T array of size 2, contains [hu, hu^2 + 0.5*g*h^2]^T
	 */
	T* flux(Quantity* q){
		T tmp[2] = { q->hu, q->hu * q->hu + 0.5f * g * q->h * q->h};
		return tmp;
	}

	/**
	 *  Inverts a given matrix
	 *
	 * @param m 2x2 Matrix to be inverted and also the one in which the result will be stored.
	 */
	void inverseMatrix(T* m){
		T a = m[0][0];
		T b = m[0][1];
		T c = m[1][0];
		T d = m[1][1];

		T det = (a*d - b*c);


		m[0][0] = (1.0f / det) * d;
		m[0][1] = (1.0f / det) * -b;
		m[1][0] = (1.0f / det) * -c;
		m[1][1] = (1.0f / det) * a;

	}

	T* computeWaveZ(T ec, T lambda){
		T* out[2] = {ec, ec*lambda};
		return out;
	}

};

#endif /* FWAVE_HPP_ */
