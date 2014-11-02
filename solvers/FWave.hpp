
#ifndef FWAVE_HPP_
#define FWAVE_HPP_
#include <cassert>
#include <cmath>
#include <iostream>
	namespace solver {
		template <typename T> class FWave;
	}
	template <typename T> class solver::FWave {
	public:
		FWave() {}
		struct Quantity {
			T h;
			T hu;
		};
		enum CellType{
			WetWet,
			DryDry,
			WetDry,
			DryWet
		};
		static const T g = 9.81;
		static const T zeroTol = 0.0000001;
		static const T dryTol = 0.01;
		/**
		 * Compute left and right going net-updates.
		 *
		 * @param &hl height on the left side of the edge.
		 * @param &hr height on the right side of the edge.
		 * @param &hul momentum on the left side of the edge.
		 * @param &hur momentum on the right side of the edge.
		 * @param &bl bathymetry on the left side of the edge.
		 * @param &br bathymetry on the right side of the edge.
		 *
		 * @param &outhl output height of the cell on the left side of the edge.
		 * @param &outhr output height of the cell on the right side of the edge.
		 * @param &outhul output momentum of the cell on the left side of the edge.
		 * @param &outhur output momentum of the cell on the right side of the edge.
		 * @param &outmaxWS will be set to: Maximum (linearized) wave speed -> Should be used in the CFL-condition.
		 */
		void computeNetUpdates(T hl, T hr, T hul, T hur, T bl, T br, T &outhl, T &outhr, T &outhul, T &outhur, T &outmaxWS) {
			struct Quantity ql, qr;
			ql.h = hl;
			ql.hu = hul;
			qr.h = hr;
			qr.hu = hur;

			//waterheight should be always above the ground and h != 0 to prevent division by 0
			assert(ql.h > zeroTol && qr.h > zeroTol);

			outhl = outhr = outhul = outhur = (T)0;
			outmaxWS = 0;

			CellType ct = computeBoundary(ql, qr, &br, &bl);

			if(ct == DryDry) {
			    outhl = outhr = outhul = outhur  = (T)0;
			    //Nothing changes (no water)
			    return;
			}

			//compute Wavespeeds lambda. Equation (3)
			T h = std::sqrt(g * computeHeightRoe(ql, qr));
			T u = computeVeloRoe(ql, qr);
			T lambda1 = u - h;
			T lambda2 = u + h;

			//Formula (9)
			if(lambda1 < 0 && lambda2 < 0) {
				lambda2 = (T)0;
			} else if(lambda1 > 0 && lambda2 > 0) {
				lambda1 = (T)0;
			}

			//Compute eigencoefficients [a_1 , a_2] (Formula (8))
			T ec[2];
			computeEigencoeff(ql, qr, lambda1, lambda2,br, bl, ec);

			//Compute wave Z1 and Z2 (Formula (6))
			T z1[2], z2[2];
			computeWaveZ(ec[0], lambda1, z1);
			computeWaveZ(ec[1], lambda2, z2);

			//Formula (7)
			if(lambda1 > 0) {
				outhr += z1[0];
				outhur += z1[1];
			} else if(lambda1 < 0) {
				outhl += z1[0];
				outhul += z1[1];
			}
			if(lambda2 > 0) {
				outhr += z2[0];
				outhur += z2[1];
			} else if(lambda2 < 0) {
				outhl += z2[0];
				outhul += z2[1];
			}
			outmaxWS = std::max( std::fabs(lambda1) , std::fabs(lambda2) );

			//Dry cells staying dry
			if(ct == WetDry){
				outhr = outhur = (T)0;
			}else if(ct == DryWet){
				outhl = outhul = (T)0;
			}
		};
	private:
		/**
		 * Look up the height of both sides and determine the property of the edge as celltype.
		 *
		 * @param &ql Quantity [h, (hu)T] of left cell
		 * @param &qr Quantity [h, (hu)T] of right cell
		 * @return CellType state of the edge
		 */
		CellType computeBoundary(Quantity &ql, Quantity &qr,T *bl,T *br){
			if(ql.h < dryTol){
				if(qr.h < dryTol){
					//Dry-Dry: Nothing changes
					return DryDry;
				}else{
					//Dry-Wet: Right incoming wave get reflected
					//As2. Formula (4)
					ql.h = qr.h;
					ql.hu = -qr.hu;
					bl = br;
					return DryWet;
				}
			}else{
				if(qr.h < dryTol){
					//Wet-Dry: left incoming wave get reflected
					qr.h = ql.h;
					qr.hu = -ql.hu;
					br = bl;
					return WetDry;
				}else{
					//Wet-Wet: Nothing changes
					return WetWet;
				}
			}

		}
		/**
		 * Compute height h(hl,hr) = 0.5(hl + hr). (Formula (4))
		 *
		 * @param &ql Quantity [h, (hu)T] of left cell
		 * @param &qr Quantity [h, (hu)T] of right cell
		 * @return Height h_Roe
		 */
		T computeHeightRoe(Quantity &ql, Quantity &qr) {
			return (T)0.5 * (ql.h + qr.h);
		};
		/**
		 * (ul * sqrt(hl) + ur * sqrt(hr))
		 * Compute height u(hl,hr) = -------------------------------- (Formula (4))
		 * (sqrt(hl) + sqrt(hr))
		 *
		 * @param &ql Quantity [h, (hu)T] of left cell
		 * @param &qr Quantity [h, (hu)T] of right cell
		 * @return Velocity u_Roe
		 */
		T computeVeloRoe(Quantity &ql,Quantity &qr) {
			T ul = ql.hu / ql.h;
			T ur = qr.hu / qr.h;
			T sqhl = std::sqrt(ql.h);
			T sqhr = std::sqrt(qr.h);
			return (ul * sqhl + ur * sqhr) / (sqhl + sqhr);
		};
		/**
		 * Compute the eigencoefficients a_p by using the wavespeeds and the flux formula. (Formula (8))
		 *
		 * @param &ql Quantity [h, (hu)T] of left cell
		 * @param &qr Quantity [h, (hu)T] of right cell
		 * @param lambda1 Wavespeed 1
		 * @param lambda2 Wavespeed 2
		 * @param out[2] output array of size 2, contains eigencoefficients a_1 and a_2
		 */
		void computeEigencoeff(Quantity &ql, Quantity &qr, T lambda1, T lambda2,T br, T bl, T out[2]) {
			T fqr[2], fql[2];
			flux(qr, fqr);
			flux(ql, fql);

			T bathymetry[] = {0, -(g * (br-bl) * ((ql.h+qr.h)/2))};

			T dFlux[] = {fqr[0]-fql[0], fqr[1]-fql[1] - bathymetry[1]};

			T mat[2][2] = { {1.0f, 1.0f}, {lambda1, lambda2}};

			inverseMatrix(mat);
			out[0] = mat[0][0] * dFlux[0] + mat[0][1] * dFlux[1];
			out[1] = mat[1][0] * dFlux[0] + mat[1][1] * dFlux[1];
		};
		/**
		 * Evaluating the flux formula f = [hu, hu^2 + 0.5*g*h^2]^T
		 *
		 * @param q Quantity to be used for the flux calculation
		 * @param out[2] output array of size 2, contains [hu, hu^2 + 0.5*g*h^2]^T
		 */
		void flux(Quantity &q, T out[2]) {
			T u = q.hu / q.h;
			out[0] = q.hu;
			out[1] = q.h * (u * u) + 0.5f * g * q.h * q.h;
		};
		/**
		 * Inverts a given 2x2 matrix
		 *
		 * @param m 2x2 Matrix to be inverted and also the one in which the result will be stored.
		 */
		void inverseMatrix(T m[2][2]) {
			T a = m[0][0];
			T b = m[0][1];
			T c = m[1][0];
			T d = m[1][1];

			T det = (a*d - b*c);

			assert(std::fabs(det) > zeroTol);

			m[0][0] = (1.0f / det) * d;
			m[0][1] = (1.0f / det) * (-b);
			m[1][0] = (1.0f / det) * (-c);
			m[1][1] = (1.0f / det) * a;
		};
		/**
		 * Multiplicate eigencoefficient with eigenvector
		 *
		 * @param ec Eigencoefficient
		 * @param lambda Wavespeed to corresponding eigenvector
		 * @param out[2] output array of size 2, contains [ec, ec * lambda]^T
		 */
		void computeWaveZ(T ec, T lambda, T out[2]) {
			out[0] = ec;
			out[1] = ec*lambda;
		};
	};
#endif /* FWAVE_HPP_ */

