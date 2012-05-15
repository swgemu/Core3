/*
 * CampStructureObjectTemplate.cpp
 *
 *  Created on: Jan 2, 2012
 *      Author: Kyle
 */


#include "CampStructureTemplate.h"


void CampStructureTemplate::readObject(LuaObject* templateData) {
	SharedBuildingObjectTemplate::readObject(templateData);

	duration = templateData->getIntField("duration");
	radius = templateData->getFloatField("radius");
	experience = templateData->getIntField("experience");
	aggroMod = templateData->getIntField("aggroMod");
	skillRequired = templateData->getIntField("skillRequired");

	healthWoundRegenRate = templateData->getIntField("healthWoundRegenRate");
	actionWoundRegenRate = templateData->getIntField("actionWoundRegenRate");
	mindWoundRegenRate = templateData->getIntField("mindWoundRegenRate");
}

