/*
 * HospitalBuildingObject.h
 *
 *  Created on: 14/01/2012
 *      Author: kyle
 */

#ifndef HOSPITALBUILDINGOBJECTTEMPLATE_H_
#define HOSPITALBUILDINGOBJECTTEMPLATE_H_

#include "SharedBuildingObjectTemplate.h"

class HospitalBuildingObjectTemplate : public SharedBuildingObjectTemplate {
	int medicalRating;
	int healthWoundRegenRate;
	int actionWoundRegenRate;
	int mindWoundRegenRate;

public:
	HospitalBuildingObjectTemplate() : medicalRating(0), healthWoundRegenRate(0), actionWoundRegenRate(0), mindWoundRegenRate(0) {
	}

	~HospitalBuildingObjectTemplate() {
	}

	void readObject(LuaObject* templateData) {
		SharedBuildingObjectTemplate::readObject(templateData);

		medicalRating = templateData->getIntField("medicalRating");
		healthWoundRegenRate = templateData->getIntField("healthWoundRegenRate");
		actionWoundRegenRate = templateData->getIntField("actionWoundRegenRate");
		mindWoundRegenRate = templateData->getIntField("mindWoundRegenRate");

	}

	bool isHospitalBuildingObjectTemplate() {
		return true;
	}

	inline int getMedicalRating() {
		return medicalRating;
	}

	inline int getHealthWoundRegenRate() {
		return healthWoundRegenRate;
	}

	inline int getActionWoundRegenRate() {
		return actionWoundRegenRate;
	}

	inline int getMindWoundRegenRate() {
		return mindWoundRegenRate;
	}
};


#endif /* HOSPITALBUILDINGOBJECTTEMPLATE_H_ */
