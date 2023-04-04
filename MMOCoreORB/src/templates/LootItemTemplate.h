/*
 * LootItemTemplate.h
 *
 *  Created on: 18/12/2011
 *      Author: victor
 */

#ifndef LOOTITEMTEMPLATE_H_
#define LOOTITEMTEMPLATE_H_

#include "templates/LuaTemplate.h"
#include "templates/crafting/AttributesMap.h"
#include "templates/manager/TemplateManager.h"
#include "templates/SharedTangibleObjectTemplate.h"
#include "server/zone/objects/scene/SceneObjectType.h"

class LootItemTemplate: public LuaTemplate, public Logger {
protected:
	String templateName;
	String customObjectName;
	String directObjectTemplate;

	int junkDealerTypeNeeded;
	int junkMinValue;
	int junkMaxValue;

	AttributesMap attributesMap;
	bool suppressSerialNumber;

	Vector<String> customizationStringNames;
	Vector<Vector<int> > customizationValues;

	float randomDotChance;
	float staticDotChance;
	int staticDotType;
	VectorMap<String, SortedVector<int> > staticDotValues;

	VectorMap<String, int> skillMods;

public:
	LootItemTemplate(const String& name) : attributesMap() {
		templateName = name;
		randomDotChance = -1;
		staticDotChance = -1;
		staticDotType = -1;

		junkDealerTypeNeeded = 0;
		junkMinValue = 0;
		junkMaxValue = 0;
		suppressSerialNumber = false;

		setLoggingName("LootItemTemplate");
	}

	void readObject(LuaObject* templateData) {
		customObjectName = templateData->getStringField("customObjectName");
		directObjectTemplate = templateData->getStringField("directObjectTemplate");
		suppressSerialNumber = templateData->getBooleanField("suppressSerialNumber");

		junkDealerTypeNeeded = templateData->getIntField("junkDealerTypeNeeded");
		junkMinValue = templateData->getIntField("junkMinValue");
		junkMaxValue = templateData->getIntField("junkMaxValue");

		// info(true) << "---------- Loading data for " << directObjectTemplate << " ----------";

		// set lootItemTemplate values
		// shared tangible object template draft schematic data set as base valueMap
		auto tanoTemplate = dynamic_cast<SharedTangibleObjectTemplate*>(TemplateManager::instance()->getTemplate(directObjectTemplate.hashCode()));

		if (tanoTemplate != nullptr) {
			const auto groups = tanoTemplate->getExperimentalGroups();
			const auto attributes = tanoTemplate->getExperimentalAttributes();
			const auto minValues = tanoTemplate->getExperimentalMin();
			const auto maxValues = tanoTemplate->getExperimentalMax();
			const auto precisionValues = tanoTemplate->getExperimentalPrecision();
			const auto combines = tanoTemplate->getExperimentalWeights();

			//info(true) << "Template: " << directObjectTemplate << " Total attributes: " << attributes->size();

			for (int i = 0; i < attributes->size(); ++i) {
				const String& attribute = attributes->get(i);
				const String& group = groups->get(i);

				float min = minValues->get(i);
				float max = maxValues->get(i);

				if (tanoTemplate->getGameObjectType() & SceneObjectType::COMPONENT) {
					min = 0.f;
					max = 0.f;
				}

				short int precision = precisionValues->get(i);
				short int combine = combines->get(i);
				bool hidden = min == max && max == 0;

				attributesMap.addExperimentalAttribute(attribute, group, min, max, precision, hidden, combine);
				attributesMap.setMaxPercentage(attribute, 1.f);
			}
		}

		LuaObject craftvals = templateData->getObjectField("craftingValues");

		if (craftvals.isValidTable()) {
			for (int i = 1; i <= craftvals.getTableSize(); ++i) {
				LuaObject row = craftvals.getObjectAt(i);

				if (row.isValidTable()) {
					String attribute = row.getStringAt(1);

					float min = row.getFloatAt(2);
					float max = row.getFloatAt(3);
					int prec = 0;
					bool hidden = false;
					int combineType = AttributesMap::LINEARCOMBINE;

					if (row.getTableSize() > 3)
						prec = row.getFloatAt(4);

					if (row.getTableSize() > 4)
						hidden = row.getBooleanAt(5);

					if (row.getTableSize() > 5)
						combineType = row.getIntAt(6);

					// The AttributesMap will automatically handle if the attribute already exists and only updates the values.
					attributesMap.addExperimentalAttribute(attribute, attribute, min, max, prec, hidden, combineType);
					attributesMap.setMaxPercentage(attribute, 1.0f);
				}

				row.pop();
			}

			craftvals.pop();
		}

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

		// info(true) << "---------- FINISHED Loading data for " << directObjectTemplate << " ----------";
	}

	const String& getTemplateName() const {
		return templateName;
	}

	const String& getDirectObjectTemplate() const {
		return directObjectTemplate;
	}

	const String& getCustomObjectName() const {
		return customObjectName;
	}

	const Vector<String>* getCustomizationStringNames() const {
		return &customizationStringNames;
	}

	const Vector<Vector<int> >* getCustomizationValues() const {
		return &customizationValues;
	}

	bool getSuppressSerialNumber() const {
		return suppressSerialNumber;
	}

	AttributesMap getAttributesMapCopy() const {
		return attributesMap;
	}

	const VectorMap<String, int>* getSkillMods() const {
		return &skillMods;
	}

	float getRandomDotChance() const {
		return randomDotChance;
	}

	float getStaticDotChance() const {
		return staticDotChance;
	}

	int getStaticDotType() const {
		return staticDotType;
	}

	int getJunkDealerTypeNeeded() const {
		return junkDealerTypeNeeded;
	}

	int getJunkMinValue() const {
		return junkMinValue;
	}

	int getJunkMaxValue() const {
		return junkMaxValue;
	}

	const VectorMap<String, SortedVector<int> >* getStaticDotValues() const {
		return &staticDotValues;
	}
};

#endif /* LOOTITEMTEMPLATE_H_ */
