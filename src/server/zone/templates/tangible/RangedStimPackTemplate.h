/*
 * RangedRangedRangedStimPackTemplate.h
 *
 *  Created on: 10/08/2010
 *      Author: victor
 */

#ifndef RANGEDSTIMPACKTEMPLATE_H_
#define RANGEDSTIMPACKTEMPLATE_H_

#include "StimPackTemplate.h"

class RangedStimPackTemplate : public StimPackTemplate {
	float effectiveness;
	float range;
	float area;
	float rangeMod;

public:
	RangedStimPackTemplate() {
		effectiveness = 0;
		range = 0;
		area = 0;
		rangeMod = 0;
	}

	~RangedStimPackTemplate() {

	}

	void readObject(LuaObject* templateData) {
		StimPackTemplate::readObject(templateData);

		range = templateData->getFloatField("range");
		rangeMod = templateData->getFloatField("rangeMod");
		area = templateData->getFloatField("area");
		effectiveness = templateData->getFloatField("effectiveness");
    }

	inline float getEffectiveness() {
		return effectiveness;
	}

	inline float getRange() {
		return range;
	}

	inline float getArea() {
		return area;
	}

	inline float getRangeMod() {
		return rangeMod;
	}

	bool isRangedStimPackTemplate() {
		return true;
	}
};


#endif /* RANGEDSTIMPACKTEMPLATE_H_ */
