/*
 * SharedStructureObjectTemplate.h
 *
 *  Created on: May 22, 2010
 *      Author: crush
 */

#ifndef CAMPSTRUCTURETEMPLATE_H_
#define CAMPSTRUCTURETEMPLATE_H_

#include "SharedBuildingObjectTemplate.h"

class CampStructureTemplate : public SharedBuildingObjectTemplate {
protected:
	uint16 experience;
	uint16 duration;
	uint16 radius;
	uint16 aggroMod;
	uint16 medicalRating;
	uint16 skillRequired;
	uint16 healthWoundRegenRate;
	uint16 actionWoundRegenRate;
	uint16 mindWoundRegenRate;

public:
	CampStructureTemplate() {

	}

	~CampStructureTemplate() {

	}

	void readObject(LuaObject* templateData);

	bool isCampStructureTemplate() {
		return true;
	}

	inline int getDuration() const {
		return duration;
	}

	inline int getExperience() const {
		return experience;
	}

	inline int getRadius() const {
		return radius;
	}

	inline int getAggroMod() const {
		return aggroMod;
	}

	inline int getMedicalRating() const {
		return medicalRating;
	}

	inline int getSkillRequired() const {
		return skillRequired;
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

#endif /* CAMPSTRUCTURETEMPLATE_H_ */
