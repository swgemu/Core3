/*
 * RepairToolTemplate.h
 *
 *  Created on: Mar 21, 2012
 *      Author: kyle
 */

#ifndef REPAIRTOOLTEMPLATE_H_
#define REPAIRTOOLTEMPLATE_H_

#include "../../SharedTangibleObjectTemplate.h"

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

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
		mask = templateData->getIntField("canRepairType");
		boostSkill =templateData->getStringField("boostSkill");
		boostSkillMod =templateData->getStringField("boostSkillMod");
		stationType = templateData->getIntField("stationType");
	}

	uint32 getRepairType() {
		return mask;
	}

	String getSkill() {
		return boostSkill;
	}

	String getSkillMod() {
		return boostSkillMod;
	}

	int getStationType() {
		return stationType;
	}

    bool isRepairToolTemplate() {
    	return true;
    }

};

#endif /* REPAIRTOOLTEMPLATE_H_ */
