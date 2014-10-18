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

	}

private:

	const float g = 9.81f;
	/**
	 * Approximate the true wave speeds using the data of left and right cell.
	 *
	 * @param ql Quantity [h, (hu)T] of left cell
	 * @param qr Quantity [h, (hu)T] of right cell
	 * @param signum Determines whether the second part of the term u(ql,qr) +- sqrt(gh(ql,qr)) will be substracted or added.
	 */
	void MyFWaveSolver::computeWavespeed(Quantity* ql, Quantity* qr, float signum) {
		int sgn = 0;
		if (signum > 0.0f) {
			sgn = 1;
		} else if (x < 0.0f) {
			sgn = -1;
		}
		return computeVeloRoe(ql, qr) + sgn * sqrt(g * computeHeightRoe(ql, qr));
	}

	/**
	 * Compute height h(hl,hr) = 0.5(hl + hr)
	 *
	 * @param ql Quantity [h, (hu)T] of left cell
	 * @param qr Quantity [h, (hu)T] of right cell
	 */
	void MyFWaveSolver::computeHeightRoe(Quantity* ql, Quantity* qr) {
		return 0.5 * (ql->h + qr->h);
	}

	/**
	 *                            (ul * sqrt(hl) + ur * sqrt(hr))
	 *  Compute height u(hl,hr) = --------------------------------
	 *                                (sqrt(hl) + sqrt(hr))
	 *
	 * @param ql Quantity [h, (hu)T] of left cell
	 * @param qr Quantity [h, (hu)T] of right cell
	 */
	void MyFWaveSolver::computeVeloRoe(Quantity* ql, Quantity* qr) {
		double ul = ql->hu / ql->h;
		double ur = qr->hu / qr->h;
		return (ul * sqrt(ql->h) + ur * sqrt(qr->h))
				/ (sqrt(ql->h) + sqrt(qr->h));
	}
};

#endif /* FWAVE_HPP_ */
