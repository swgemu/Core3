/*
 * RepairToolTemplate.h
 *
 *  Created on: Mar 21, 2012
 *      Author: kyle
 */

#ifndef REPAIRTOOLTEMPLATE_H_
#define REPAIRTOOLTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class RepairToolTemplate : public SharedTangibleObjectTemplate {
	uint32 mask;
	String boostSkill;
	String boostSkillMod;
	int stationType;

public:
	RepairToolTemplate() {
		mask = 0;
		boostSkill = "";
		boostSkillMod = "";
		stationType = 0;
	}

	~RepairToolTemplate() {

	}

	void readObject(LuaObject* templateData) override {
		SharedTangibleObjectTemplate::readObject(templateData);
		mask = templateData->getIntField("canRepairType");
		boostSkill =templateData->getStringField("boostSkill");
		boostSkillMod =templateData->getStringField("boostSkillMod");
		stationType = templateData->getIntField("stationType");
	}

	uint32 getRepairType() const {
		return mask;
	}

	const String& getSkill() const {
		return boostSkill;
	}

	const String& getSkillMod() const {
		return boostSkillMod;
	}

	int getStationType() const {
		return stationType;
	}

	bool isRepairToolTemplate() const override {
		return true;
	}

};

#endif /* REPAIRTOOLTEMPLATE_H_ */
