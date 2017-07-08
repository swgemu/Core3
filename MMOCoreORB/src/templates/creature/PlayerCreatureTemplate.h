/*
 * PlayerCreatureTemplate.h
 *
 *  Created on: Feb 15, 2011
 *      Author: crush
 */

#ifndef PLAYERCREATURETEMPLATE_H_
#define PLAYERCREATURETEMPLATE_H_

#include "templates/creature/SharedCreatureObjectTemplate.h"
#include "templates/customization/CustomizationDataMap.h"

class PlayerCreatureTemplate : public SharedCreatureObjectTemplate {
	CustomizationDataMap dataMap;
	Reference<Vector<String>* > startingSkills;
	Reference<Vector<String>* > startingItems;

protected:
	uint8 defaultLanguage;

public:
	PlayerCreatureTemplate() {
		startingSkills = new Vector<String>();
		startingItems = new Vector<String>();
		defaultLanguage = 0;
	}

	~PlayerCreatureTemplate() {
	}

	CustomizationDataMap* getCustomizationDataMap() {
		return &dataMap;
	}

	Vector<CustomizationData>* getCustomizationData(const String& customizationName) {
		return &dataMap.get(customizationName);
	}

	Vector<String>* getStartingSkills() {
		return startingSkills;
	}

	Vector<String>* getStartingItems() {
		return startingItems;
	}

	inline uint8 getDefaultLanguage() {
		return defaultLanguage;
	}

	void setCustomizationDataMap(const CustomizationDataMap& map) {
		dataMap = map;
	}

	void parseVariableData(const String& varName, LuaObject* templateData);

	void readObject(LuaObject* templateData);

	bool isPlayerCreatureTemplate() {
		return true;
	}
};

#endif /* PLAYERCREATURETEMPLATE_H_ */
