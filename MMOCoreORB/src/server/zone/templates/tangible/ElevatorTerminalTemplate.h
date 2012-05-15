/*
 * ElevatorTerminalTemplate.h
 *
 *  Created on: March 15, 2011
 *      Author: crush
 */

#ifndef ELEVATORTERMINALTEMPLATE_H_
#define ELEVATORTERMINALTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class ElevatorTerminalTemplate : public SharedTangibleObjectTemplate {
	byte movementType;

public:
	static const byte UPONLY = 0x00;
	static const byte DOWNONLY = 0x01;
	static const byte UPANDDOWN = 0x02;

public:
	ElevatorTerminalTemplate() {
		movementType = UPONLY;
	}

	~ElevatorTerminalTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		movementType = templateData->getByteField("movementType");
    }

	inline byte getMovementType() {
		return movementType;
	}

	inline bool isMovingUp() {
		return (movementType == UPONLY || movementType == UPANDDOWN);
	}

	inline bool isMovingDown() {
		return (movementType == DOWNONLY || movementType == UPANDDOWN);
	}
};

#endif /* ELEVATORTERMINALTEMPLATE_H_ */
