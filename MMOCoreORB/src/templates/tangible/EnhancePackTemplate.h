/*
 * EnhancePackTemplate.h
 *
 *  Created on: 10/08/2010
 *      Author: victor
 */

#ifndef ENHANCEPACKTEMPLATE_H_
#define ENHANCEPACKTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class EnhancePackTemplate : public SharedTangibleObjectTemplate {
	int medicineUse;
	float effectiveness;
	float absorption;
	float duration;
	byte attribute;

public:
	EnhancePackTemplate() {
		medicineUse = 0;
		effectiveness = 0;
		absorption = 0;
		duration = 0;
		attribute = 0;
	}

	~EnhancePackTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		medicineUse = templateData->getIntField("medicineUse");
		effectiveness = templateData->getFloatField("effectiveness");
		absorption = templateData->getFloatField("absorption");
		duration = templateData->getFloatField("duration");
		attribute = templateData->getIntField("attribute");
    }

	inline int getMedicineUse() {
		return medicineUse;
	}

	inline float getEffectiveness() {
		return effectiveness;
	}

	inline float getAbsorption() {
		return absorption;
	}

	inline byte getAttribute() {
		return attribute;
	}

	inline float getDuration() {
		return duration;
	}

	bool isEnhancePackTemplate() {
		return true;
	}
};

#endif /* ENHANCEPACKTEMPLATE_H_ */
