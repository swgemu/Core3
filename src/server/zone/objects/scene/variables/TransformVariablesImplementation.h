/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef TRANSFORMVARIABLESIMPLEMENTATION_H_
#define TRANSFORMVARIABLESIMPLEMENTATION_H_

#include "engine/engine.h"

#include "TransformVariables.h"

class TransformVariablesImplementation : public TransformVariablesServant, public Coordinate {
	uint64 newParentID;

	float directionX;
	float directionZ;
	float directionY;
	float directionW;

	uint8 directionAngle;

	uint32 movementStamp;
	uint32 movementCounter;

public:
	TransformVariablesImplementation() {
		newParentID = 0;

		directionX = 0.f;
		directionZ = 0.f;
		directionY = 0.f;
		directionW = 0.f;

		directionAngle = 0;

		movementStamp = 0;
		movementCounter = 0;
	}

	//setters
	inline void setDirectionAngle(uint8 angle) {
		directionAngle = angle;
	}

	inline void setMovementCounter(uint32 counter) {
		movementCounter = counter;
	}

	inline void setMovementStamp(uint32 stamp) {
		movementStamp = stamp;
	}

	inline void setDirection(float x, float z, float y, float w) {
		directionX = x;
		directionZ = z;
		directionY = y;
		directionW = w;
	}

	//getters

	inline uint32 getMovementCounter() {
		return movementCounter;
	}

	inline uint8 getDirectionAngle() {
		return directionAngle;
	}

	inline float getDirectionX() {
		return directionX;
	}

	inline float getDirectionZ() {
		return directionZ;
	}

	inline float getDirectionY() {
		return directionY;
	}

	inline float getDirectionW() {
		return directionW;
	}

};


#endif /* TRANSFORMVARIABLESIMPLEMENTATION_H_ */
