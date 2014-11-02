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
private:
	/** Zero: 0.0f */
	T zero;

public:
	/** Delta used for comparing expected and actual values */
	static const T delta = 0.0001f;

	/** FWave to test */
	solver::FWave<T> fwave;

	FWaveTest() {
		zero = 0.0f;
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

		fwave.computeNetUpdates(startHeight, startHeight, zero, zero, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(startHeight, startHeight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(startHeight, startHeight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(startHeight, startHeight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(startHeight, startHeight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

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

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, zero, zero, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -23.9468, delta);
		TS_ASSERT_DELTA(hr, 205.6470, delta);

		TS_ASSERT_DELTA(hul, 18.9468, delta);
		TS_ASSERT_DELTA(hur, 162.3279, delta);
	}

	/**
		 * Tests FWave#computeNetUpdates with the following parameters:<br>
		 * hl = 6.0<br>
		 * hr = 6.0<br>
		 * <br>
		 * hul = 2.0<br>
		 * hur = 2.0<br>
		 * <br>
		 * bl = 4.0<br>
		 * br = 4.0<br>
		 */
		void testSameBatymethrySameHeightSpeedRightLeft(void) {
			T heightLeft = 6.0f;
			T heightRight = 6.0f;
			T speedLeft = 2.0f;
			T speedRight = -2.0f;
			T bl = 4.0f;
			T br = 4.0f;

			T hl, hr, hul, hur, maxWS;

			fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, bl, br, hl, hul, hr, hur, maxWS);

			TS_ASSERT_DELTA(hl, -2.0000, delta);
			TS_ASSERT_DELTA(hr, 15.3440, delta);

			TS_ASSERT_DELTA(hul, -2.0000, delta);
			TS_ASSERT_DELTA(hur, -15.3440, delta);
		}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 6.0<br>
	 * hr = 4.0<br>
	 * <br>
	 * hul = 2.0<br>
	 * hur = 2.0<br>
	 * <br>
	 * bl = 2.0<br>
	 * br = 4.0<br>
	 */
	void testIncreasingBatymethrySameHeightSpeedRight(void) {
		T heightLeft = 6.0f;
		T heightRight = 4.0f;
		T speedLeft = 2.0f;
		T speedRight = 2.0f;
		T bl = 2.0f;
		T br = 4.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, bl, br, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -0.0237, delta);
		TS_ASSERT_DELTA(hr, 0.1569, delta);

		TS_ASSERT_DELTA(hul, 0.0237, delta);
		TS_ASSERT_DELTA(hur, 0.1763, delta);
	}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 6.0<br>
	 * hr = 4.0<br>
	 * <br>
	 * hul = -2.0<br>
	 * hur = 2.0<br>
	 * <br>
	 * bl = 2.0<br>
	 * br = 4.0<br>
	 */
	void testIncreasingBatymethrySameHeightSpeedLeftRight(void) {
		T heightLeft = 6.0f;
		T heightRight = 4.0f;
		T speedLeft = -2.0f;
		T speedRight = 2.0f;
		T bl = 2.0f;
		T br = 4.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, bl, br, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 1.9879, delta);
		TS_ASSERT_DELTA(hr, -13.8409, delta);

		TS_ASSERT_DELTA(hul, 2.0120, delta);
		TS_ASSERT_DELTA(hur, 14.1743, delta);
	}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 6.0<br>
	 * hr = 4.0<br>
	 * <br>
	 * hul = 2.0<br>
	 * hur = -2.0<br>
	 * <br>
	 * bl = 2.0<br>
	 * br = 4.0<br>
	 */
	void testIncreasingBatymethrySameHeightSpeedRightLeft(void) {
		T heightLeft = 6.0f;
		T heightRight = 4.0f;
		T speedLeft = 2.0f;
		T speedRight = -2.0f;
		T bl = 2.0f;
		T br = 4.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, bl, br, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -2.0120, delta);
		TS_ASSERT_DELTA(hr, 14.1743, delta);

		TS_ASSERT_DELTA(hul, -1.9879, delta);
		TS_ASSERT_DELTA(hur, -13.8409, delta);
	}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 4.0<br>
	 * hr = 6.0<br>
	 * <br>
	 * hul = 2.0<br>
	 * hur = 2.0<br>
	 * <br>
	 * bl = 4.0<br>
	 * br = 2.0<br>
	 */
	void testDecreasingBatymethrySameHeightSpeedRight(void) {
		T heightLeft = 4.0f;
		T heightRight = 6.0f;
		T speedLeft = 2.0f;
		T speedRight = 2.0f;
		T bl = 4.0f;
		T br = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, bl, br, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 0.0237, delta);
		TS_ASSERT_DELTA(hr, -0.1569, delta);

		TS_ASSERT_DELTA(hul, -0.0237, delta);
		TS_ASSERT_DELTA(hur, -0.1763, delta);
	}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 4.0<br>
	 * hr = 6.0<br>
	 * <br>
	 * hul = -2.0<br>
	 * hur = 2.0<br>
	 * <br>
	 * bl = 4.0<br>
	 * br = 2.0<br>
	 */
	void testDecreasingBatymethrySameHeightSpeedLeftRight(void) {
		T heightLeft = 4.0f;
		T heightRight = 6.0f;
		T speedLeft = -2.0f;
		T speedRight = 2.0f;
		T bl = 4.0f;
		T br = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, bl, br, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 2.0120, delta);
		TS_ASSERT_DELTA(hr, -14.1743, delta);

		TS_ASSERT_DELTA(hul, 1.9879, delta);
		TS_ASSERT_DELTA(hur, 13.8409, delta);
	}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 4.0<br>
	 * hr = 6.0<br>
	 * <br>
	 * hul = 2.0<br>
	 * hur = -2.0<br>
	 * <br>
	 * bl = 4.0<br>
	 * br = 2.0<br>
	 */
	void testDecreasingBatymethrySameHeightSpeedRightLeft(void) {
		T heightLeft = 4.0f;
		T heightRight = 6.0f;
		T speedLeft = 2.0f;
		T speedRight = -2.0f;
		T bl = 4.0f;
		T br = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, bl, br, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, -1.9879, delta);
		TS_ASSERT_DELTA(hr, 13.8409, delta);

		TS_ASSERT_DELTA(hul, -2.0120, delta);
		TS_ASSERT_DELTA(hur, -14.1743, delta);
	}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 20.0<br>
	 * hr = 20.0<br>
	 * <br>
	 * hul = 2.0<br>
	 * hur = 0.0<br>
	 * <br>
	 * bl = 4.0<br>
	 * br = 2.0<br>
	 */
	void testDecreasingBatymethryDecreasingHeightSpeedRightStay(void) {
		T heightLeft = 20.0f;
		T heightRight = 20.0f;
		T speedLeft = 2.0f;
		T speedRight = 0.0f;
		T bl = 4.0f;
		T br = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, bl, br, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 13.0107, delta);
		TS_ASSERT_DELTA(hr, -181.5923, delta);

		TS_ASSERT_DELTA(hul, -15.0107, delta);
		TS_ASSERT_DELTA(hur, -211.0076, delta);
	}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 20.0<br>
	 * hr = 20.0<br>
	 * <br>
	 * hul = 0.0<br>
	 * hur = -2.0<br>
	 * <br>
	 * bl = 4.0<br>
	 * br = 2.0<br>
	 */
	void testDecreasingBatymethryDecreasingHeightSpeedStayLeft(void) {
		T heightLeft = 20.0f;
		T heightRight = 20.0f;
		T speedLeft = 0.0f;
		T speedRight = -2.0f;
		T bl = 4.0f;
		T br = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, bl, br, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 13.0035, delta);
		TS_ASSERT_DELTA(hr, -182.7930, delta);

		TS_ASSERT_DELTA(hul, -15.0035, delta);
		TS_ASSERT_DELTA(hur, -209.4069, delta);
	}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 20.0<br>
	 * hr = 16.0<br>
	 * <br>
	 * hul = 2.0<br>
	 * hur = 0.0<br>
	 * <br>
	 * bl = 2.0<br>
	 * br = 4.0<br>
	 */
	void testIncreasingBatymethryDecreasingHeightSpeedRightStay(void) {
		T heightLeft = 20.0f;
		T heightRight = 16.0f;
		T speedLeft = 2.0f;
		T speedRight = 0.0f;
		T bl = 2.0f;
		T br = 4.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, bl, br, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 12.2918, delta);
		TS_ASSERT_DELTA(hr, -162.6900, delta);

		TS_ASSERT_DELTA(hul, -14.2918, delta);
		TS_ASSERT_DELTA(hur, -190.6699, delta);
	}

	/**
	 * Tests FWave#computeNetUpdates with the following parameters:<br>
	 * hl = 20.0<br>
	 * hr = 16.0<br>
	 * <br>
	 * hul = 0.0<br>
	 * hur = -2.0<br>
	 * <br>
	 * bl = 2.0<br>
	 * br = 4.0<br>
	 */
	void testIncreasingBatymethryDecreasingHeightSpeedStayLeft(void) {
		T heightLeft = 20.0f;
		T heightRight = 16.0f;
		T speedLeft = 0.0f;
		T speedRight = -2.0f;
		T bl = 2.0f;
		T br = 4.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, bl, br, hl, hul, hr, hur, maxWS);

		TS_ASSERT_DELTA(hl, 12.2833, delta);
		TS_ASSERT_DELTA(hr, -163.9506, delta);

		TS_ASSERT_DELTA(hul, -14.2833, delta);
		TS_ASSERT_DELTA(hur, -188.9594, delta);
	}
};


#endif /* FWAVETEST_H_ */
