/*
 * PlayerCreatureTemplate.h
 *
 *  Created on: Feb 15, 2011
 *      Author: crush
 */

#ifndef PLAYERCREATURETEMPLATE_H_
#define PLAYERCREATURETEMPLATE_H_

#include "SharedCreatureObjectTemplate.h"
#include "server/zone/managers/skill/imagedesign/CustomizationDataMap.h"

class PlayerCreatureTemplate : public SharedCreatureObjectTemplate {
	CustomizationDataMap dataMap;
	Reference<Vector<String>* > startingSkills;

public:
	PlayerCreatureTemplate() {
		startingSkills = new Vector<String>();
	}

	~PlayerCreatureTemplate() {
	}

	CustomizationDataMap* getCustomizationDataMap() {
		return &dataMap;
	}

	CustomizationData* getCustomizationData(const String& customizationName) {
		return &dataMap.get(customizationName);
	}

	Vector<String>* getStartingSkills() {
		return startingSkills;
	}

	void setCustomizationDataMap(const CustomizationDataMap& map) {
		dataMap = map;
	}

	void parseVariableData(const String& varName, LuaObject* templateData);

	void readObject(LuaObject* templateData);
};

#endif /* PLAYERCREATURETEMPLATE_H_ */
