/*
 * DotPackTemplate.h
 *
 *  Created on: 10/08/2010
 *      Author: victor
 */

#ifndef DOTPACKTEMPLATE_H_
#define DOTPACKTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class DotPackTemplate : public SharedTangibleObjectTemplate {
	float effectiveness;
	float range;
	float area;
	float rangeMod;
	float potency;
	int medicineUse;
	uint32 duration;
	uint32 pool;
	uint32 dotType;
	String commandToExecute;
	bool hasArea;

public:
	DotPackTemplate() {
		medicineUse = 0;
		effectiveness = 0;
		duration = 0;
		area = 0;
		range = 0;
		potency = 0;
		rangeMod = 0;
		pool = 0;
		dotType = 0;
		hasArea = false;
	}

	~DotPackTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		medicineUse = templateData->getIntField("medicineUse");
		effectiveness = templateData->getFloatField("effectiveness");
		duration = templateData->getIntField("duration");
		area = templateData->getFloatField("area");
		hasArea = area != 0;
		range = templateData->getFloatField("range");
		rangeMod = templateData->getFloatField("rangeMod");
		pool = templateData->getIntField("pool");
		dotType = templateData->getIntField("dotType");
		potency = templateData->getFloatField("potency");
		commandToExecute = templateData->getStringField("commandToExecute");
    }

	inline int getMedicineUse() {
		return medicineUse;
	}

	inline float getEffectiveness() {
		return effectiveness;
	}

	inline uint32 getPool() {
		return pool;
	}

	inline float getRange() {
		return range;
	}

	inline float getArea() {
		return area;
	}

	inline bool isArea() {
		return hasArea;
	}

	inline float getRangeMod() {
		return rangeMod;
	}

	inline uint32 getDuration() {
		return duration;
	}

	inline float getPotency() {
		return potency;
	}

	inline uint32 getDotType() {
		return dotType;
	}

	inline String& getCommandToExecute() {
		return commandToExecute;
	}

	bool isDotPackTemplate() {
		return true;
	}
};

#endif /* DOTPACKTEMPLATE_H_ */
