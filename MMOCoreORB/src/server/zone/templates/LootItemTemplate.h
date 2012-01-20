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

#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"

class LootItemTemplate: public LuaTemplate {
protected:
	CraftingValues craftingValues;

	String name;
	String customObjectName;
	Vector<String> customizationStringNames;
	Vector<Vector<int> > customizationValues;

	String directObjectTemplate;

	int minimumLevel;
	int maximumLevel;

public:
	LootItemTemplate(const String& name) {
		this->name = name;
	}

	void readObject(LuaObject* templateData) {
		directObjectTemplate = templateData->getStringField("directObjectTemplate");
		minimumLevel = templateData->getIntField("minimumLevel");
		maximumLevel = templateData->getIntField("maximumLevel");
		customObjectName = templateData->getStringField("customObjectName");

		LuaObject craftvals = templateData->getObjectField("craftingValues");

		lua_State* L = craftvals.getLuaState();

		if (craftvals.isValidTable()) {
			for (int i = 1; i <= craftvals.getTableSize(); ++i) {
				lua_rawgeti(L, -1, i);

				LuaObject row(L);

				if (row.isValidTable()) {
					String property = row.getStringAt(1);
					float min = row.getFloatAt(2);
					float max = row.getFloatAt(3);

					craftingValues.addExperimentalProperty(property, property, min, max, 0, false);
					craftingValues.setMaxPercentage(property, 1.0f);
				}

				row.pop();
			}
		}

		craftvals.pop();

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
	}

	String& getDirectObjectTemplate() {
		return directObjectTemplate;
	}

	String& getCustomObjectName() {
		return customObjectName;
	}

	Vector<String>* getCustomizationStringNames() {
		return &customizationStringNames;
	}

	Vector<Vector<int> >* getCustomizationValues() {
		return &customizationValues;
	}

	CraftingValues getCraftingValuesCopy() {
		return craftingValues;
	}

	int getMaximumLevel() const {
		return maximumLevel;
	}

	int getMinimumLevel() const {
		return minimumLevel;
	}
};

#endif /* LOOTITEMTEMPLATE_H_ */
