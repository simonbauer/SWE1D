/*
 * FWaveTest.h
 *
 *  Created on: 20.10.2014
 *      Author: vmuser
 */

#ifndef FWAVETEST_H_
#define FWAVETEST_H_

#include <cxxtest/TestSuite.h>
#include "types.h"
#include "FWave.hpp"

class FWaveTest : public CxxTest::TestSuite
{
public:
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

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void testSameHeightRightSpeed(void) {
		T startHeight = 5.0f;
		T speedLeft = 3.0f;
		T speedRight = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(startHeight, startHeight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void testSameHeightLeftRightSpeed(void) {
		T startHeight = 5.0f;
		T speedLeft = -3.0f;
		T speedRight = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(startHeight, startHeight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void testSameHeightRightLeftSpeed(void) {
		T startHeight = 5.0f;
		T speedLeft = 2.0f;
		T speedRight = -3.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(startHeight, startHeight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void decreasingHeightNoSpeed(void) {
		T heightLeft = 10.0f;
		T heightRight = 5.0f;
		T speedLeft = 0.0f;
		T speedRight = 0.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void decreasingHeightLeftSpeed(void) {
		T heightLeft = 10.0f;
		T heightRight = 5.0f;
		T speedLeft = -2.0f;
		T speedRight = -3.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void decreasingHeightRightSpeed(void) {
		T heightLeft = 10.0f;
		T heightRight = 5.0f;
		T speedLeft = 3.0f;
		T speedRight = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void decreasingHeightLeftRightSpeed(void) {
		T heightLeft = 10.0f;
		T heightRight = 5.0f;
		T speedLeft = -2.0f;
		T speedRight = 3.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void decreasingHeightRightLeftSpeed(void) {
		T heightLeft = 10.0f;
		T heightRight = 5.0f;
		T speedLeft = 3.0f;
		T speedRight = -2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void increasingHeightNoSpeed(void) {
		T heightLeft = 5.0f;
		T heightRight = 10.0f;
		T speedLeft = 0.0f;
		T speedRight = 0.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void increasingHeightLeftSpeed(void) {
		T heightLeft = 5.0f;
		T heightRight = 10.0f;
		T speedLeft = -3.0f;
		T speedRight = -2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void increasingHeightRightSpeed(void) {
		T heightLeft = 5.0f;
		T heightRight = 10.0f;
		T speedLeft = 2.0f;
		T speedRight = 3.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void increasingHeightLeftRightSpeed(void) {
		T heightLeft = 5.0f;
		T heightRight = 10.0f;
		T speedLeft = -3.0f;
		T speedRight = 2.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}

	void increasingHeightRightLeftSpeed(void) {
		T heightLeft = 5.0f;
		T heightRight = 10.0f;
		T speedLeft = 2.0f;
		T speedRight = -3.0f;

		T hl, hr, hul, hur, maxWS;

		fwave.computeNetUpdates(heightLeft, heightRight, speedLeft, speedRight, 0.0f, 0.0f, hl, hul, hr, hur, maxWS);

		TS_ASSERT_EQUALS(hl, 0.0f);
		TS_ASSERT_EQUALS(hr, 0.0f);

		TS_ASSERT_EQUALS(hul, 0.0f);
		TS_ASSERT_EQUALS(hur, 0.0f);
	}
};


#endif /* FWAVETEST_H_ */
