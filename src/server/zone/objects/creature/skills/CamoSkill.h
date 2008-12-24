/*
 * CamoSkill.h
 *
 *  Created on: Oct 21, 2008
 *      Author: swgdev
 */

#ifndef CAMOSKILL_H_
#define CAMOSKILL_H_

#include "Skill.h"

class CamoSkill : public Skill {
protected:
	float duration;

	int camoType;

public:
	CamoSkill(const String& name,const int cat, ZoneProcessServerImplementation* serv) : Skill(name, CAMO, cat, serv) {
		duration = 0;
		camoType = 11;
	}


	virtual void doSkill(CreatureObject* creature, String& modifier) {

	}

	virtual void doSkill(CreatureObject* creature,SceneObject* target, String& modifier) {

	}


	void doAnimations(CreatureObject* creature) {
	}

	virtual void finish(CreatureObject* creature) {
	}

	float calculateSpeed(CreatureObject* creature) {
			return 0;
	}

	virtual bool isUseful(CreatureObject* creature) {
		return false;
	}

	virtual bool calculateCost(CreatureObject* creature) {
		return false;
	}

	virtual void setCamoType(int camo) {
		camoType = camo;
	}

	virtual void setDuration(float dur) {
		duration = dur;
	}


	inline float getDuration() {
		return duration;
	}

	inline int getCamoType() {
		return camoType;
	}
};

#endif
