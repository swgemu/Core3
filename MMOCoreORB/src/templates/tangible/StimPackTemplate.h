/*
 * StimPackTemplate.h
 *
 *  Created on: 10/08/2010
 *      Author: victor
 */

#ifndef STIMPACKTEMPLATE_H_
#define STIMPACKTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class StimPackTemplate : public SharedTangibleObjectTemplate {
	int medicineUse;
	int medicineClass;
	float effectiveness;
	Vector<byte> attributes;


public:
	const static int STIM_A = 1;
	const static int STIM_B = 2;
	const static int STIM_C = 3;
	const static int STIM_D = 4;
	const static int STIM_E = 5;

	StimPackTemplate() {
		medicineUse = 0;
		effectiveness = 0;
		medicineClass = 0;
	}

	~StimPackTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		medicineUse = templateData->getIntField("medicineUse");
		effectiveness = templateData->getFloatField("effectiveness");
		medicineClass = templateData->getIntField("medicineClass");

		LuaObject atts = templateData->getObjectField("attributes");

		for (int i = 0; i < atts.getTableSize(); ++i) {
			byte att = atts.getIntAt(i + 1);

			attributes.add(att);
		}

		atts.pop();
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

	inline int getMedicineClass() {
		return medicineClass;
	}

	inline Vector<byte> getAttributes() {
		return attributes;
	}
};

#endif
