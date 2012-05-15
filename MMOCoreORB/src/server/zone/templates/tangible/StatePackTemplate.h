/*
 * StatePackTemplate.h
 *
 *  Created on: 12/08/2010
 *      Author: victor
 */

#ifndef STATEPACKTEMPLATE_H_
#define STATEPACKTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class StatePackTemplate : public SharedTangibleObjectTemplate {
	int medicineUse;
	uint64 state;

public:
	StatePackTemplate() {
		medicineUse = 0;
		state = 0;
	}

	~StatePackTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		medicineUse = templateData->getIntField("medicineUse");
		state = templateData->getFloatField("state");
    }

	inline int getMedicineUse() {
		return medicineUse;
	}

	inline uint64 getState() {
		return state;
	}

	bool isStatePackTemplate() {
		return true;
	}
};

#endif /* STATEPACKTEMPLATE_H_ */
