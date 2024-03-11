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
#include "server/zone/managers/loot/LootAttributeType.h"

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

	int levelMax;
	int levelMin;

	uint32 objectType;

	bool isRandomResource;

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

		levelMax = 0;
		levelMin = 0;

		objectType = 0;

		isRandomResource = false;

		setLoggingName("LootItemTemplate");
	}

	void readObject(LuaObject* templateData) {
		customObjectName = templateData->getStringField("customObjectName");
		directObjectTemplate = templateData->getStringField("directObjectTemplate");
		suppressSerialNumber = templateData->getBooleanField("suppressSerialNumber");

		junkDealerTypeNeeded = templateData->getIntField("junkDealerTypeNeeded");
		junkMinValue = templateData->getIntField("junkMinValue");
		junkMaxValue = templateData->getIntField("junkMaxValue");

		levelMin = templateData->getFloatField("minimumLevel", 0);
		levelMax = templateData->getFloatField("maximumLevel", -1);

		isRandomResource = directObjectTemplate == "object/resource_container/simple.iff";

		auto tanoTemplate = dynamic_cast<SharedTangibleObjectTemplate*>(TemplateManager::instance()->getTemplate(directObjectTemplate.hashCode()));

		if (tanoTemplate != nullptr) {
			objectType = tanoTemplate->getGameObjectType();

			const auto groups = tanoTemplate->getExperimentalGroups();
			const auto attributes = tanoTemplate->getExperimentalAttributes();
			const auto minValues = tanoTemplate->getExperimentalMin();
			const auto maxValues = tanoTemplate->getExperimentalMax();
			const auto precisionValues = tanoTemplate->getExperimentalPrecision();
			const auto combines = tanoTemplate->getExperimentalWeights();

			bool isComponent = (tanoTemplate->getGameObjectType() & SceneObjectType::COMPONENT);

			for (int i = 0; i < attributes->size(); ++i) {
				const String& attribute = attributes->get(i);
				const String& group = groups->get(i);

				float min = minValues->get(i);
				float max = maxValues->get(i);

				int precision = precisionValues->get(i);
				bool hidden = group == "" || group == "null";
				int combine = LootAttributeType::getAttributeType(objectType, attribute);

				if (isComponent) {
					min = 0.f;
					max = 0.f;
				}

				if (min == max && max == 0.f) {
					combine = LootAttributeType::STATIC;
					hidden = true;
				}

				attributesMap.addExperimentalAttribute(attribute, group, min, max, precision, hidden, combine);
				attributesMap.setCurrentPercentage(attribute, 0.f, 1.f);
			}
		}

		LuaObject craftvals = templateData->getObjectField("craftingValues");

		if (craftvals.isValidTable()) {
			for (int i = 1; i <= craftvals.getTableSize(); ++i) {
				LuaObject row = craftvals.getObjectAt(i);

				if (row.isValidTable() && row.getTableSize() >= 3) {
					String attribute = row.getStringAt(1);
					String group = attribute;

					float min = row.getFloatAt(2);
					float max = row.getFloatAt(3);

					int precision = 0;
					bool hidden = false;
					int combine = LootAttributeType::getAttributeType(objectType, attribute);

					if (attributesMap.hasExperimentalAttribute(attribute)) {
						group = attributesMap.getAttributeGroup(attribute);
						precision = attributesMap.getPrecision(attribute);
					}

					if (row.getTableSize() >= 4) {
						precision = row.getIntAt(4);
					}

					if (row.getTableSize() >= 5) {
						hidden = row.getBooleanAt(5);
					}

					if (row.getTableSize() >= 6) {
						combine = row.getIntAt(6);
					}

					if (min == max && max == 0.f) {
						combine = LootAttributeType::STATIC;
						hidden = true;
					}

					attributesMap.addExperimentalAttribute(attribute, group, min, max, precision, hidden, combine);
					attributesMap.setCurrentPercentage(attribute, 0.f, 1.f);

					row.pop();
				}
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
		randomDotChance = templateData->getFloatField("randomDotChance", -1);
		staticDotChance = templateData->getFloatField("staticDotChance", -1);
		staticDotType = templateData->getFloatField("staticDotType", -1);

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

	int getLevelMax() const {
		return levelMax;
	}

	int getLevelMin() const {
		return levelMin;
	}

	bool isRandomResourceContainer() const {
		return isRandomResource;
	}

	uint32 getObjectType() const {
		return objectType;
	}

	const VectorMap<String, SortedVector<int> >* getStaticDotValues() const {
		return &staticDotValues;
	}
};

#endif /* LOOTITEMTEMPLATE_H_ */
