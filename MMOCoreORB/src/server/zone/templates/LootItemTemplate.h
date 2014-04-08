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
#include "server/zone/managers/crafting/CraftingManager.h"

class LootItemTemplate: public LuaTemplate {
protected:
	String templateName;
	String customObjectName;
	String directObjectTemplate;

	int junkDealerTypeNeeded;
	int junkMinValue;
	int junkMaxValue;

	CraftingValues craftingValues;

	Vector<String> customizationStringNames;
	Vector<Vector<int> > customizationValues;

	float randomDotChance;
	float staticDotChance;
	int staticDotType;
	VectorMap<String, SortedVector<int> > staticDotValues;

	VectorMap<String, int> skillMods;

public:
	LootItemTemplate(const String& name) {
		templateName = name;
		randomDotChance = -1;
		staticDotChance = -1;
		staticDotType = -1;
	}

	void readObject(LuaObject* templateData) {
		customObjectName = templateData->getStringField("customObjectName");
		directObjectTemplate = templateData->getStringField("directObjectTemplate");

		junkDealerTypeNeeded = templateData->getIntField("junkDealerTypeNeeded");
		junkMinValue = templateData->getIntField("junkMinValue");
		junkMaxValue = templateData->getIntField("junkMaxValue");

		//TODO: At this point, we should go ahead and pull in the tangible objects stats

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
					float prec = 0;
					bool hidden = false;
					short combineType = CraftingManager::LINEARCOMBINE;

					if (row.getTableSize() > 3)
						prec = row.getFloatAt(4);

					if (row.getTableSize() > 4)
						hidden = row.getBooleanAt(5);

					if (row.getTableSize() > 5)
						combineType = row.getIntAt(6);

					craftingValues.addExperimentalProperty(property, property,
							min, max, prec, hidden, combineType);
					craftingValues.setMaxPercentage(property, 1.0f);
				}

				row.pop();
			}
		}

		craftvals.pop();

		LuaObject customizationStringNamesList = templateData->getObjectField("customizationStringNames");

		for (int i = 1; i <= customizationStringNamesList.getTableSize(); ++i) {
			customizationStringNames.add(customizationStringNamesList.getStringAt(i));
		}

		customizationStringNamesList.pop();

		LuaObject custValues = templateData->getObjectField("customizationValues");

		for (int i = 1; i <= custValues.getTableSize(); ++i) {
			lua_rawgeti(templateData->getLuaState(), -1, i);

			LuaObject values(templateData->getLuaState());

			Vector<int> valuesVector;

			for (int j = 1; j <= values.getTableSize(); ++j) {
				valuesVector.add(values.getIntAt(j));
			}

			customizationValues.add(valuesVector);

			values.pop();
		}

		custValues.pop();

		LuaObject skillModsLuaObject = templateData->getObjectField("skillMods");

		for (int i = 1; i <= skillModsLuaObject.getTableSize(); ++i) {
			lua_rawgeti(templateData->getLuaState(), -1, i);

			LuaObject skill(templateData->getLuaState());

			skillMods.put(skill.getStringAt(1), skill.getIntAt(2));

			skill.pop();
		}

		skillModsLuaObject.pop();

		// Initializations.
		float randomDot = -1;

		randomDot = templateData->getFloatField("randomDotChance");

		if (randomDot >= 0) {
			randomDotChance = randomDot;
		}

		float staticDot = -1;

		staticDot = templateData->getFloatField("staticDotChance");

		if (staticDot >= 0) {
			staticDotChance = staticDot;
		}

		int type = -1;
		type = templateData->getIntField("staticDotType");

		if (type >= 0)
			staticDotType = type;

		LuaObject dotValuesTable = templateData->getObjectField("staticDotValues");

		if (dotValuesTable.isValidTable() && dotValuesTable.getTableSize() > 0) {
			for (int i = 1; i <= dotValuesTable.getTableSize(); ++i) {
				lua_rawgeti(templateData->getLuaState(), -1, i);

				LuaObject dot(templateData->getLuaState());

				String property;
				SortedVector<int> valuesVector;

				if (dot.isValidTable()) {
					property = dot.getStringAt(1);
					valuesVector.put(dot.getIntAt(2));
					valuesVector.put(dot.getIntAt(3));
				}
					staticDotValues.put(property, valuesVector);

				dot.pop();
			}
			dotValuesTable.pop();
		}

	}

	String& getTemplateName() {
		return templateName;
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

	VectorMap<String, int>* getSkillMods() {
		return &skillMods;
	}

	float getRandomDotChance() {
		return randomDotChance;
	}

	float getStaticDotChance() {
		return staticDotChance;
	}

	int getStaticDotType() {
		return staticDotType;
	}

	int getJunkDealerTypeNeeded() {
		return junkDealerTypeNeeded;
	}
	int getJunkMinValue() {
		return junkMinValue;
	}
	int getJunkMaxValue() {
		return junkMaxValue;
	}
	VectorMap<String, SortedVector<int> >* getStaticDotValues() {
		return &staticDotValues;
	}
};

#endif /* LOOTITEMTEMPLATE_H_ */
