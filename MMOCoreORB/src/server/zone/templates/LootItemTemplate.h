/*
 * LootItemTemplate.h
 *
 *  Created on: 18/12/2011
 *      Author: victor
 */

#ifndef LOOTITEMTEMPLATE_H_
#define LOOTITEMTEMPLATE_H_

#include "engine/engine.h"
#include "LuaTemplate.h"

//class Customization

class LootItemTemplate: public LuaTemplate {
protected:
	String name;
	String draftSchematic;
	String customObjectName;
	Vector<String> experimentalSubGroupTitles;
	Vector<int> experimentalMin;
	Vector<int> experimentalMax;
	Vector<String> customizationStringNames;

	Vector<Vector<int> > customizationValues;

	String directObjectTemplate;

	int qualityRangeMin;
	int qualityRangeMax;
	int minimumLevel;
	int maximumLevel;
	float chance;

public:
	LootItemTemplate(const String& name) {
		this->name = name;
	}

	void readObject(LuaObject* templateData) {
		directObjectTemplate = templateData->getStringField("directObjectTemplate");
		minimumLevel = templateData->getIntField("minimumLevel");
		maximumLevel = templateData->getIntField("maximumLevel");
		chance = templateData->getFloatField("chance");
		customObjectName = templateData->getStringField("customObjectName");

		LuaObject experimentalSubGroupTitlesList = templateData->getObjectField("experimentalSubGroupTitles");

		for (int i = 1; i <= experimentalSubGroupTitlesList.getTableSize(); ++i) {
			experimentalSubGroupTitles.add(experimentalSubGroupTitlesList.getStringAt(i));
		}

		experimentalSubGroupTitlesList.pop();

		LuaObject experimentalMinList = templateData->getObjectField("experimentalMin");

		for (int i = 1; i <= experimentalMinList.getTableSize(); ++i) {
			experimentalMin.add(experimentalMinList.getIntAt(i));
		}

		experimentalMinList.pop();

		LuaObject experimentalMaxList = templateData->getObjectField("experimentalMax");

		for (int i = 1; i <= experimentalMaxList.getTableSize(); ++i) {
			experimentalMax.add(experimentalMaxList.getIntAt(i));
		}

		experimentalMaxList.pop();

		LuaObject customizationStringNamesList = templateData->getObjectField("customizationStringNames");

		for (int i = 1; i <= customizationStringNamesList.getTableSize(); ++i) {
			customizationStringNames.add(customizationStringNamesList.getStringAt(i));

			//printf("adding customizationStringName\n");
		}

		customizationStringNamesList.pop();

		LuaObject custValues = templateData->getObjectField("customizationValues");

		for (int i = 1; i <= custValues.getTableSize(); ++i) {
			lua_rawgeti(templateData->getLuaState(), -1, i);

			LuaObject values(templateData->getLuaState());

			Vector<int> valuesVector;

			for (int j = 1; j <= values.getTableSize(); ++j) {
				valuesVector.add(values.getIntAt(j));

				//printf("adding value to valuesVector\n");
			}

			customizationValues.add(valuesVector);

			values.pop();
		}

		custValues.pop();

		qualityRangeMin = templateData->getIntField("qualityRangeMin");
		qualityRangeMax = templateData->getIntField("qualityRangeMax");
	}

	String& getDirectObjectTemplate() {
		return directObjectTemplate;
	}

	String& getCustomObjectName() {
		return customObjectName;
	}

	String getDraftSchematic() const {
		return draftSchematic;
	}

	Vector<int>* getExperimentalMax() {
		return &experimentalMax;
	}

	Vector<int>* getExperimentalMin() {
		return &experimentalMin;
	}

	Vector<String>* getExperimentalSubGroupTitles() {
		return &experimentalSubGroupTitles;
	}

	Vector<String>* getCustomizationStringNames() {
		return &customizationStringNames;
	}

	Vector<Vector<int> >* getCustomizationValues() {
		return &customizationValues;
	}

	int getQualityRangeMax() const {
		return qualityRangeMax;
	}

	int getQualityRangeMin() const {
		return qualityRangeMin;
	}

    float getChance() const {
		return chance;
	}

	int getMaximumLevel() const {
		return maximumLevel;
	}

	int getMinimumLevel() const {
		return minimumLevel;
	}
};

#endif /* LOOTITEMTEMPLATE_H_ */
