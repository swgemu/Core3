/*
 * ArmorObjectTemplate.h
 *
 *  Created on: 01/06/2010
 *      Author: victor
 */

#ifndef ELEVATORTERMINALTEMPLATE_H_
#define ELEVATORTERMINALTEMPLATE_H_


#include "../SharedTangibleObjectTemplate.h"

class ElevatorTerminalTemplate : public SharedTangibleObjectTemplate {
	float deltaZ;

public:
	ElevatorTerminalTemplate() {
		deltaZ = 0;
	}

	~ElevatorTerminalTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		deltaZ = templateData->getFloatField("deltaZ");
	}

	inline float getDeltaZ() const {
		return deltaZ;
	}

	void setDeltaZ(float z) {
		deltaZ = z;
	}

	bool isElevatorTerminalTemplate() {
		return true;
	}
};


#endif /* ELEVATORTERMINALTEMPLATE_H_ */
