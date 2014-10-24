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
	/** Delta used for comparing expected and actual values */
	static const T delta = 0.0001f;

	/** FWave to test */
	solver::FWave<T> fwave;

	FWaveTest() {
	}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 5.0<br>
	 * hr = 5.0<br>
	 * <br>
	 * hul = 0<br>
	 * hur = 0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
	void testSameHeightNoSpeed(void) {
		T startHeight = 5.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(startHeight, startHeight, 0.0f, 0.0f, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 5.0<br>
	 * hr = 5.0<br>
	 * <br>
	 * hul = -2.0<br>
	 * hur = -3.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 5.0<br>
	 * hr = 5.0<br>
	 * <br>
	 * hul = 3.0<br>
	 * hur = 2.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 5.0<br>
	 * hr = 5.0<br>
	 * <br>
	 * hul = -3.0<br>
	 * hur = 2.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 5.0<br>
	 * hr = 5.0<br>
	 * <br>
	 * hul = 2.0<br>
	 * hur = -3.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 10.0<br>
	 * hr = 5.0<br>
	 * <br>
	 * hul = 0<br>
	 * hur = 0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 10.0<br>
	 * hr = 5.0<br>
	 * <br>
	 * hul = -2.0<br>
	 * hur = -3.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 10.0<br>
	 * hr = 5.0<br>
	 * <br>
	 * hul = 3.0<br>
	 * hur = 2.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 10.0<br>
	 * hr = 5.0<br>
	 * <br>
	 * hul = -2.0<br>
	 * hur = 3.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 10.0<br>
	 * hr = 5.0<br>
	 * <br>
	 * hul = 3.0<br>
	 * hur = -2.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 5.0<br>
	 * hr = 10.0<br>
	 * <br>
	 * hul = 0<br>
	 * hur = 0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 5.0<br>
	 * hr = 10.0<br>
	 * <br>
	 * hul = -3.0<br>
	 * hur = -2.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 5.0<br>
	 * hr = 10.0<br>
	 * <br>
	 * hul = 2.0<br>
	 * hur = 3.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 5.0<br>
	 * hr = 10.0<br>
	 * <br>
	 * hul = -3.0<br>
	 * hur = 2.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 5.0<br>
	 * hr = 10.0<br>
	 * <br>
	 * hul = 2.0<br>
	 * hur = -3.0<br>
	 * <br>
	 * bl = 0<br>
	 * br = 0<br>
	 */
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
