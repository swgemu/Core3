/*
 * ThreatStates.h
 *
 *  Created on: 1/20/2012
 *      Author: victor
 */

#ifndef THREATSTATES_H_
#define THREATSTATES_H_

#include "engine/engine.h"

class ThreatStates {
public:
	/// Normal States 0x01, 0x02 etc

	/// Unique States 0x101 0x102
	/// Only one of these can exist
	/// in the map at a time
	const static int UNIQUESTATE = 0x100;
	const static int TAUNTED = 0x101;
	const static int FOCUSED = 0x102;
};
#endif /* THREATSTATES_H_ */
