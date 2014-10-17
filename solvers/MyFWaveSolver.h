/*
 * MyFWaveSolver.h
 *
 *  Created on: Oct 17, 2014
 *      Author: kyu
 */

#ifndef MYFWAVESOLVER_H_
#define MYFWAVESOLVER_H_

class MyFWaveSolver {
public:
	MyFWaveSolver();
	virtual ~MyFWaveSolver();
	void computeNetupdates(double hl, double hul, double hr, double hur);
	struct Quantity{
			double h;
			double hu;
		};
private:

	const float g = 9.81f;
	double computeWavespeed(Quantity* ql, Quantity* qr);
	double computeHeightRoe(Quantity* ql, Quantity* qr);
	double computeVeloRoe(Quantity* ql,Quantity*  qr);
};

#endif /* MYFWAVESOLVER_H_ */
