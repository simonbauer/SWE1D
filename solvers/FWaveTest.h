/*
 * FWaveTest.h
 *
 *  Created on: 20.10.2014
 *      Author: vmuser
 */

#ifndef FWAVETEST_H_
#define FWAVETEST_H_

#include <cxxtest/TestSuite.h>
#include "../../TsunamiOriginal/SWE1D/src/types.h"
#include "FWave.hpp"

class FWaveTest : public CxxTest::TestSuite
{
public:
	static const T delta = 0.0001f;
	solver::FWave<T> fwave;

	FWaveTest() {
		//fwave = new solver::FWave();
	}

	/*virtual ~FWaveTest() {
		fwave = NULL;
	}*/

	void testSameHeightNoSpeed(void) {
		T startHeight = 5.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(startHeight, startHeight, 0.0f, 0.0f, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void testSameHeightLeftSpeed(void) {
		T startHeight = 5.0f;
		T speedLeft = -2.0f;
		T speedRight = -3.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(startHeight, startHeight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -0.5356f, delta);
		TS_ASSERT_DELTA(hr, 4.0196f, delta);

		TS_ASSERT_DELTA(hul, -0.4643f, delta);
		TS_ASSERT_DELTA(hur, -3.0196f, delta);
	}

	void testSameHeightRightSpeed(void) {
		T startHeight = 5.0f;
		T speedLeft = 3.0f;
		T speedRight = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(startHeight, startHeight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -0.4643, delta);
		TS_ASSERT_DELTA(hr, 3.0196, delta);

		TS_ASSERT_DELTA(hul, -0.5356, delta);
		TS_ASSERT_DELTA(hur, -4.0196, delta);
	}

	void testSameHeightLeftRightSpeed(void) {
		T startHeight = 5.0f;
		T speedLeft = -3.0f;
		T speedRight = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(startHeight, startHeight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 2.5356, delta);
		TS_ASSERT_DELTA(hr, -18.0124, delta);

		TS_ASSERT_DELTA(hul, 2.4643, delta);
		TS_ASSERT_DELTA(hur, 17.0124, delta);
	}

	void testSameHeightRightLeftSpeed(void) {
		T startHeight = 5.0f;
		T speedLeft = 2.0f;
		T speedRight = -3.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(startHeight, startHeight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -2.5356, delta);
		TS_ASSERT_DELTA(hr, 18.0124, delta);

		TS_ASSERT_DELTA(hul, -2.4643, delta);
		TS_ASSERT_DELTA(hur, -17.0124, delta);
	}

	void testDecreasingHeightNoSpeed(void) {
		T heightLeft = 10.0f;
		T heightRight = 5.0f;
		T speedLeft = 0.0f;
		T speedRight = 0.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 21.4439, delta);
		TS_ASSERT_DELTA(hr, -183.9375, delta);

		TS_ASSERT_DELTA(hul, -21.4439, delta);
		TS_ASSERT_DELTA(hur, -183.9375, delta);
	}

	void testDecreasingHeightLeftSpeed(void) {
		T heightLeft = 10.0f;
		T heightRight = 5.0f;
		T speedLeft = -2.0f;
		T speedRight = -3.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 20.8836, delta);
		TS_ASSERT_DELTA(hr, -186.7684, delta);

		TS_ASSERT_DELTA(hul, -21.8836, delta);
		TS_ASSERT_DELTA(hur, -179.7066, delta);
	}

	void testDecreasingHeightRightSpeed(void) {
		T heightLeft = 10.0f;
		T heightRight = 5.0f;
		T speedLeft = 3.0f;
		T speedRight = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 20.9298, delta);
		TS_ASSERT_DELTA(hr, -172.3821, delta);

		TS_ASSERT_DELTA(hul, -21.9298, delta);
		TS_ASSERT_DELTA(hur, -195.5929, delta);
	}

	void testDecreasingHeightLeftRightSpeed(void) {
		T heightLeft = 10.0f;
		T heightRight = 5.0f;
		T speedLeft = -2.0f;
		T speedRight = 3.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 23.9006, delta);
		TS_ASSERT_DELTA(hr, -201.8700, delta);

		TS_ASSERT_DELTA(hul, -18.9006, delta);
		TS_ASSERT_DELTA(hur, -164.6049, delta);
	}

	void testDecreasingHeightRightLeftSpeed(void) {
		T heightLeft = 10.0f;
		T heightRight = 5.0f;
		T speedLeft = 3.0f;
		T speedRight = -2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 18.9468, delta);
		TS_ASSERT_DELTA(hr, -162.3279, delta);

		TS_ASSERT_DELTA(hul, -23.9468, delta);
		TS_ASSERT_DELTA(hur, -205.6470, delta);
	}

	void testIncreasingHeightNoSpeed(void) {
		T heightLeft = 5.0f;
		T heightRight = 10.0f;
		T speedLeft = 0.0f;
		T speedRight = 0.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -21.4439, delta);
		TS_ASSERT_DELTA(hr, 183.9375, delta);

		TS_ASSERT_DELTA(hul, 21.4439, delta);
		TS_ASSERT_DELTA(hur, 183.9375, delta);
	}

	void testIncreasingHeightLeftSpeed(void) {
		T heightLeft = 5.0f;
		T heightRight = 10.0f;
		T speedLeft = -3.0f;
		T speedRight = -2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -20.8836, delta);
		TS_ASSERT_DELTA(hr, 186.7684, delta);

		TS_ASSERT_DELTA(hul, 21.8836, delta);
		TS_ASSERT_DELTA(hur, 179.7066, delta);
	}

	void testIncreasingHeightRightSpeed(void) {
		T heightLeft = 5.0f;
		T heightRight = 10.0f;
		T speedLeft = 2.0f;
		T speedRight = 3.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -20.9298, delta);
		TS_ASSERT_DELTA(hr, 172.3821, delta);

		TS_ASSERT_DELTA(hul, 21.9298, delta);
		TS_ASSERT_DELTA(hur, 195.5929, delta);
	}

	void testIncreasingHeightLeftRightSpeed(void) {
		T heightLeft = 5.0f;
		T heightRight = 10.0f;
		T speedLeft = -3.0f;
		T speedRight = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -18.9006, delta);
		TS_ASSERT_DELTA(hr, 164.6049, delta);

		TS_ASSERT_DELTA(hul, 23.9006, delta);
		TS_ASSERT_DELTA(hur, 201.8700, delta);
	}

	void testIncreasingHeightRightLeftSpeed(void) {
		T heightLeft = 5.0f;
		T heightRight = 10.0f;
		T speedLeft = 2.0f;
		T speedRight = -3.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -23.9468, delta);
		TS_ASSERT_DELTA(hr, 205.6470, delta);

		TS_ASSERT_DELTA(hul, 18.9468, delta);
		TS_ASSERT_DELTA(hur, 162.3279, delta);
	}
};


#endif /* FWAVETEST_H_ */
