/*
 * CurePackTemplate.h
 *
 *  Created on: 10/08/2010
 *      Author: victor
 */

#ifndef CUREPACKTEMPLATE_H_
#define CUREPACKTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class CurePackTemplate : public SharedTangibleObjectTemplate {
	float effectiveness;
	uint64 state;
	float area;
	String commandToExecute;
	int medicineUse;

public:
	CurePackTemplate() {
		effectiveness = 0;
		state = 0;
		area = 0;
		medicineUse = 0;
	}

	~CurePackTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		medicineUse = templateData->getIntField("medicineUse");
		state = templateData->getLongField("state");
		commandToExecute = templateData->getStringField("commandToExecute");
		area = templateData->getFloatField("area");
		effectiveness = templateData->getFloatField("effectiveness");
    }

	inline float getEffectiveness() {
		return effectiveness;
	}

	inline uint64 getState() {
		return state;
	}

	inline float getArea() {
		return area;
	}

	inline int getMedicineUse() {
		return medicineUse;
	}

	inline String& getCommandToExecute() {
		return commandToExecute;
	}

	bool isCurePackTemplate() {
		return true;
	}
};


#endif /* CUREPACKTEMPLATE_H_ */
