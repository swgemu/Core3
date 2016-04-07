/*
 * TrapTemplate.h
 *
 *  Created on: Jan 16, 2012
 *      Author: kyle
 */

#ifndef TRAPTEMPLATE_H_
#define TRAPTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class TrapTemplate: public SharedTangibleObjectTemplate {
protected:
	int skillRequired;
	int healthCost;
	int actionCost;
	int mindCost;
	float maxRange;
	short poolToDamage;
	float minDamage;
	float maxDamage;
	int duration;
	String defenseMod;
	uint64 state;
	String animation;
	String successMessage;
	String failMessage;
	String startSpam;
	String stopSpam;

public:
	TrapTemplate() {
		skillRequired = 0;
		healthCost = 0;
		actionCost = 0;
		mindCost = 0;
		poolToDamage = 0;
		maxRange = 0;
		minDamage = 0;
		maxDamage = 0;
		duration = 0;
		state = 0;
		animation = "";
		successMessage = "";
		failMessage = "";
		startSpam = "";
		stopSpam = "";
		defenseMod = "";
	}

	~TrapTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
		skillRequired = templateData->getIntField("skillRequired");
		healthCost = templateData->getIntField("healthCost");
		actionCost = templateData->getIntField("actionCost");
		mindCost = templateData->getIntField("mindCost");
		maxRange = templateData->getFloatField("maxRange");
		poolToDamage= templateData->getShortField("poolToDamage");
		minDamage = templateData->getFloatField("minDamage");
		maxDamage = templateData->getFloatField("maxDamage");
		duration = templateData->getIntField("duration");
		state = templateData->getLongField("state");
		animation = templateData->getStringField("animation");
		successMessage = templateData->getStringField("successMessage");
		failMessage = templateData->getStringField("failMessage");
		startSpam = templateData->getStringField("startSpam");
		stopSpam = templateData->getStringField("stopSpam");
		defenseMod = templateData->getStringField("defenseMod");
	}

	int getActionCost() {
	    return actionCost;
	}

	int getDuration() {
		return duration;
	}

	const String& getAnimation() {
	    return animation;
	}

	const String& getSuccessMessage() {
	    return successMessage;
	}

	const String& getFailMessage() {
	    return failMessage;
	}

	const String& getStartSpam() {
	    return startSpam;
	}

	const String& getStopSpam() {
	    return stopSpam;
	}

	const String& getDefenseMod() {
		return defenseMod;
	}

	int getHealthCost() {
	    return healthCost;
	}

	float getMaxDamage() {
	    return maxDamage;
	}

	float getMaxRange() {
	    return maxRange;
	}

	float getMinDamage() {
	    return minDamage;
	}

	int getMindCost() {
	    return mindCost;
	}

	int getSkillRequired() {
		return skillRequired;
	}

	short getPoolToDamage() {
		return poolToDamage;
	}

	uint64 getState() {
	    return state;
	}
};

#endif /* TRAPTEMPLATE_H_ */
