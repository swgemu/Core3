/*
 * StimPackTemplate.h
 *
 *  Created on: 10/08/2010
 *      Author: victor
 */

#ifndef STIMPACKTEMPLATE_H_
#define STIMPACKTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class StimPackTemplate : public SharedTangibleObjectTemplate {
	int medicineUse;
	float effectiveness;

public:
	StimPackTemplate() {
		medicineUse = 0;
		effectiveness = 0;
	}

	~StimPackTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		medicineUse = templateData->getIntField("medicineUse");
		effectiveness = templateData->getFloatField("effectiveness");
    }

	inline int getMedicineUse() {
		return medicineUse;
	}

	inline float getEffectiveness() {
		return effectiveness;
	}

	bool isStimPackTemplate() {
		return true;
	}
};

#endif
