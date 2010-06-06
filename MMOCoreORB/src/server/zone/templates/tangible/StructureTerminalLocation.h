/*
 * StructureTerminalLocation.h
 *
 *  Created on: Jun 5, 2010
 *      Author: crush
 */

#ifndef STRUCTURETERMINALLOCATION_H_
#define STRUCTURETERMINALLOCATION_H_

#include "engine/engine.h"

class StructureTerminalLocation {
	uint8 cellNumber;

	Quaternion direction;

	float positionX;
	float positionY;
	float positionZ;

public:
	StructureTerminalLocation(uint8 cellnum, float posX, float posZ, float posY, float dirX, float dirY, float dirZ, float dirW) {
		cellNumber = cellnum;
		direction.set(dirW, dirX, dirY, dirZ);
		positionX = posX;
		positionY = posY;
		positionZ = posZ;
	}

	~StructureTerminalLocation() {

	}

	inline uint8 getCellNumber() {
		return cellNumber;
	}

	inline Quaternion& getDirection() {
		return direction;
	}

	inline float getPositionX() {
		return positionX;
	}

	inline float getPositionY() {
		return positionY;
	}

	inline float getPositionZ() {
		return positionZ;
	}
};

#endif /* STRUCTURETERMINALLOCATION_H_ */
