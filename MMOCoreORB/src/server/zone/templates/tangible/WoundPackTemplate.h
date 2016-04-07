/*
 * WoundPackTemplate.h
 *
 *  Created on: 11/08/2010
 *      Author: victor
 */

#ifndef WOUNDPACKTEMPLATE_H_
#define WOUNDPACKTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class WoundPackTemplate : public SharedTangibleObjectTemplate {
	int medicineUse;
	float effectiveness;
	byte attribute;

public:
	WoundPackTemplate() {
		medicineUse = 0;
		effectiveness = 0;
		attribute = 0;
	}

	~WoundPackTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		medicineUse = templateData->getIntField("medicineUse");
		effectiveness = templateData->getFloatField("effectiveness");
		attribute = templateData->getIntField("attribute");
    }

	inline int getMedicineUse() {
		return medicineUse;
	}

	inline float getEffectiveness() {
		return effectiveness;
	}

	inline byte getAttribute() {
		return attribute;
	}

	bool isWoundPackTemplate() {
		return true;
	}
};

#endif /* WOUNDPACKTEMPLATE_H_ */
