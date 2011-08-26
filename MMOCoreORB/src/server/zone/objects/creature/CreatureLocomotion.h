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
	static const uint8 INVALID = 0xFF;
	static const uint8 STANDING = 0;
	static const uint8 SNEAKING = 1;
	static const uint8 WALKING = 2;
	static const uint8 RUNNING = 3;
	static const uint8 KNEELING = 4;
	static const uint8 CROUCHSNEAKING = 5;
	static const uint8 CROUCHWALKING = 6;
	static const uint8 PRONE = 7;
	static const uint8 CRAWLING = 8;
	static const uint8 CLIMBINGSTATIONARY = 9;
	static const uint8 CLIMBING = 10;
	static const uint8 HOVERING = 11;
	static const uint8 FLYING = 12;
	static const uint8 LYINGDOWN = 13;
	static const uint8 SITTING = 14;
	static const uint8 SKILLANIMATING = 15;
	static const uint8 DRIVINGVEHICLE = 16;
	static const uint8 RIDINGCREATURE = 17;
	static const uint8 KNOCKEDDOWN = 18;
	static const uint8 INCAPACITATED = 19;
	static const uint8 DEAD = 20;
	static const uint8 BLOCKING = 21;
};


#endif /* CREATURELOCOMOTION_H_ */
