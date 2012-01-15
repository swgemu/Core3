/*
 * RecreationBuildingObject.h
 *
 *  Created on: 14/01/2012
 *      Author: kyle
 */

#ifndef RECREATIONBUILDINGOBJECTTEMPLATE_H_
#define RECREATIONBUILDINGOBJECTTEMPLATE_H_

#include "SharedBuildingObjectTemplate.h"

class RecreationBuildingObjectTemplate : public SharedBuildingObjectTemplate {
	int medicalRating;
	int healthWoundRegenRate;
	int actionWoundRegenRate;
	int mindWoundRegenRate;

public:
	RecreationBuildingObjectTemplate() {
	}

	~RecreationBuildingObjectTemplate() {
	}

	void readObject(LuaObject* templateData) {
		SharedBuildingObjectTemplate::readObject(templateData);

		medicalRating = templateData->getIntField("medicalRating");
		healthWoundRegenRate = templateData->getIntField("healthWoundRegenRate");
		actionWoundRegenRate = templateData->getIntField("actionWoundRegenRate");
		mindWoundRegenRate = templateData->getIntField("mindWoundRegenRate");

	}

	bool isRecreationBuildingObjectTemplate() {
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


#endif /* RECREATIONBUILDINGOBJECTTEMPLATE_H_ */
