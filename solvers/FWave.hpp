/*
 * FWave.hpp
 *
 *  Created on: Oct 18, 2014
 *      Author: kyu
 */

#ifndef FWAVE_HPP_
#define FWAVE_HPP_

class FWave {
public:
	FWave();
	virtual ~FWave();

	struct Quantity {
		double h;
		double hu;
	};

	/**
	 * Compute left and right going net-updates.
	 *
	 * @param hl 	height of the left side of the edge
	 * @param hul momentum of the left side of the edge
	 * @param hr 	height of the right side of the edge
	 * @param hur momentum of the right side of the edge
	 */
	void computeNetupdates(double hl, double hul, double hr, double hur) {
		struct Quantity ql, qr;
		ql.h = hl;
		ql.hu = hul;
		qr.h = hr;
		qr.hu = hur;

		double lambda1 = computeWavespeed(ql, qr, -1.0f);
		double lambda2 = computeWavespeed(ql, qr, 1.0f);
	}

private:

	const float g = 9.81f;
	/**
	 * Approximate the true wave speeds using the data of left and right cell. (Formula (3))
	 *
	 * @param ql Quantity [h, (hu)T] of left cell
	 * @param qr Quantity [h, (hu)T] of right cell
	 * @param signum Determines whether the second part of the term u(ql,qr) +- sqrt(gh(ql,qr)) will be substracted or added.
	 * @return Wavespeed lambda_1 or lambda_2 (depending on signum > 0 or signum < 0)
	 */
	double computeWavespeed(Quantity* ql, Quantity* qr, float signum) {
		int sgn = 0;
		if (signum > 0.0f) {
			sgn = 1;
		} else if (x < 0.0f) {
			sgn = -1;
		}
		return computeVeloRoe(ql, qr) + sgn * sqrt(g * computeHeightRoe(ql, qr));
	}

	/**
	 * Compute height h(hl,hr) = 0.5(hl + hr). (Formula (4))
	 *
	 * @param ql Quantity [h, (hu)T] of left cell
	 * @param qr Quantity [h, (hu)T] of right cell
	 * @return Height h_Roe
	 */
	double computeHeightRoe(Quantity* ql, Quantity* qr) {
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
	double computeVeloRoe(Quantity* ql, Quantity* qr) {
		double ul = ql->hu / ql->h;
		double ur = qr->hu / qr->h;
		return (ul * sqrt(ql->h) + ur * sqrt(qr->h)) / (sqrt(ql->h) + sqrt(qr->h));
	}

	/**
	 *  Compute the eigencoefficients a_p by using the wavespeeds and the flux formula. (Formula (8))
	 *
	 * @param ql Quantity [h, (hu)T] of left cell
	 * @param qr Quantity [h, (hu)T] of right cell
	 * @param lambda1 Wavespeed 1
	 * @param lambda2 Wavespeed 2
	 * @return double array of size 2, contains eigencoefficients a_1 and a_2
	 */
	double* computeEigencoeff(Quantity* ql, Quantity* qr, double lambda1, double lambda2){
		double* fqr = flux(qr);
		double* fql = flux(ql);

		double dFlux[2] = { fqr[0]-fql[0], fqr[1]-fql[1] };

		double* m[2][2] = { 1,1, lambda1, lambda2 };
		inverseMatrix(m);

		double a[2] = { m[0][0] * dFlux[0] + m[0][1] * dFlux[1],
						m[1][0] * dFlux[0] + m[1][1] * dFlux[1]
		};
		return a;
	}

	/**
	 *  Evaluating the flux formula f = [hu, hu^2 + 0.5*g*h^2]^T
	 *
	 * @param q Quantity to be used for the flux calculation
	 * @return double array of size 2, contains [hu, hu^2 + 0.5*g*h^2]^T
	 */
	double* flux(Quantity* q){
		double tmp[2] = { q->hu, q->hu * q->hu + 0.5 * g * q->h * q->h};
		return tmp;
	}

	/**
	 *  Inverts a given matrix
	 *
	 * @param m Matrix to be inverted and also the one in which the result will be stored.
	 */
	void inverseMatrix(double* m){
		//TODO
	}

	//TODO: Formula(6) and (7)
};

#endif /* FWAVE_HPP_ */
