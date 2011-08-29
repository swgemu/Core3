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

public:
	PlayerCreatureTemplate() {
	}

	~PlayerCreatureTemplate() {
	}

	CustomizationDataMap* getCustomizationDataMap() {
		return &dataMap;
	}

	CustomizationData* getCustomizationData(const String& customizationName) {
		return &dataMap.get(customizationName);
	}

	void setCustomizationDataMap(const CustomizationDataMap& map) {
		dataMap = map;
	}

	void readObject(LuaObject* templateData) {
		SharedCreatureObjectTemplate::readObject(templateData);
	}
};

#endif /* PLAYERCREATURETEMPLATE_H_ */
