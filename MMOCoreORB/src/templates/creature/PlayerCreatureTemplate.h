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
	Vector<String> startingSkills;
	Vector<String> startingItems;

protected:
	uint8 defaultLanguage;

public:
	PlayerCreatureTemplate() {
		defaultLanguage = 0;
	}

	~PlayerCreatureTemplate() {
	}

	const CustomizationDataMap& getCustomizationDataMap() const {
		return dataMap;
	}

	CustomizationDataMap& getCustomizationDataMap() {
		return dataMap;
	}

	const Vector<CustomizationData>& getCustomizationData(const String& customizationName) const {
		return dataMap.get(customizationName);
	}

	const Vector<String>& getStartingSkills() const {
		return startingSkills;
	}

	const Vector<String>& getStartingItems() const {
		return startingItems;
	}

	inline uint8 getDefaultLanguage() const {
		return defaultLanguage;
	}

	void setCustomizationDataMap(const CustomizationDataMap& map) {
		dataMap = map;
	}

	void parseVariableData(const String& varName, LuaObject* templateData);

	void readObject(LuaObject* templateData) override;

	bool isPlayerCreatureTemplate() const override {
		return true;
	}
};

#endif /* PLAYERCREATURETEMPLATE_H_ */
