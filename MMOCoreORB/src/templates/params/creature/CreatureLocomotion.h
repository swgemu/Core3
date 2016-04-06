/*
 * CreatureLocomotion.h
 *
 *  Created on: Aug 25, 2011
 *      Author: da
 */

#ifndef CREATURELOCOMOTION_H_
#define CREATURELOCOMOTION_H_

class CreatureLocomotion {
public:
	enum {
		INVALID            = 0xFF,
		STANDING           = 0,
		SNEAKING           = 1,
		WALKING            = 2,
		RUNNING            = 3,
		KNEELING           = 4,
		CROUCHSNEAKING     = 5,
		CROUCHWALKING      = 6,
		PRONE              = 7,
		CRAWLING           = 8,
		CLIMBINGSTATIONARY = 9,
		CLIMBING           = 10,
		HOVERING           = 11,
		FLYING             = 12,
		LYINGDOWN          = 13,
		SITTING            = 14,
		SKILLANIMATING     = 15,
		DRIVINGVEHICLE     = 16,
		RIDINGCREATURE     = 17,
		KNOCKEDDOWN        = 18,
		INCAPACITATED      = 19,
		DEAD               = 20,
		BLOCKING           = 21
	};

	enum {
		STATIONARY,
		SLOW,
		FAST
	};
};


#endif /* CREATURELOCOMOTION_H_ */
