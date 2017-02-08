/*
 * SharedDraftSchematicObjectTemplate.cpp
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#include "DraftSchematicObjectTemplate.h"
#include "templates/manager/TemplateManager.h"

DraftSchematicObjectTemplate::DraftSchematicObjectTemplate() {
	craftingToolTab = 0;

	complexity = 0;
	size = 0;

	xp = 0;

	isMagic = false;

	tanoCRC = 0;

	ingredientTemplateNames = new Vector<String> ();
	ingredientTitleNames = new Vector<String> ();
	ingredientSlotType = new Vector<short> ();
	ingredientAppearance = new Vector<String>();
	resourceTypes = new Vector<String> ();
	resourceQuantities = new Vector<int> ();
	contribution = new Vector<short> ();

	draftSlots = new Vector<Reference<DraftSlot*> > ();

	additionalTemplates = new Vector<String> ();

	tangibleTemplate = NULL;

	tanoCRC = 0;

	skillMods.setNoDuplicateInsertPlan();
	skillMods.setNullValue(0);
	labratory = 0;
	factoryCrateSize = 25;
}

DraftSchematicObjectTemplate::~DraftSchematicObjectTemplate() {
	delete ingredientTemplateNames;
	delete ingredientTitleNames;
	delete ingredientSlotType;
	delete ingredientAppearance;
	delete resourceTypes;
	delete resourceQuantities;
	delete contribution;

	delete additionalTemplates;

	delete draftSlots;
}

void DraftSchematicObjectTemplate::parseVariableData(const String& varName, LuaObject* data) {
	lua_State* state = data->getLuaState();

	if (varName == "customObjectName") {
		customObjectName = Lua::getStringParameter(state);
	} else if (varName == "craftingToolTab") {
		craftingToolTab = Lua::getIntParameter(state);
	} else if (varName == "complexity") {
		complexity = Lua::getShortParameter(state);
	} else if (varName == "size") {
		size = Lua::getShortParameter(state);
	} else if (varName == "xpType") {
		xpType = Lua::getStringParameter(state);
	} else if (varName == "xp") {
		xp = Lua::getIntParameter(state);
	} else if (varName == "lab") {
		labratory = Lua::getIntParameter(state);
	} else if (varName == "factoryCrateSize") {
		factoryCrateSize = Lua::getIntParameter(state);
	} else if (varName == "isMagic") {
		isMagic = Lua::getBooleanParameter(state);
	} else if (varName == "assemblySkill") {
		assemblySkill = Lua::getStringParameter(state);
	} else if (varName == "experimentingSkill") {
		experimentingSkill = Lua::getStringParameter(state);
	} else if (varName == "customizationSkill") {
		customizationSkill = Lua::getStringParameter(state);
	} else if (varName == "ingredientTemplateNames") {
		LuaObject ingredientTemplateNamesList(state);
		ingredientTemplateNames->removeAll();
		for (int i = 1; i <= ingredientTemplateNamesList.getTableSize(); ++i) {
			ingredientTemplateNames->add(ingredientTemplateNamesList.getStringAt(i));
		}
		ingredientTemplateNamesList.pop();
	} else if (varName == "ingredientTitleNames") {
		LuaObject ingredientTitleNamesList(state);
		ingredientTitleNames->removeAll();
		for (int i = 1; i <= ingredientTitleNamesList.getTableSize(); ++i) {
			ingredientTitleNames->add(ingredientTitleNamesList.getStringAt(i));
		}
		ingredientTitleNamesList.pop();
	} else if (varName == "ingredientSlotType") {
		LuaObject ingredientSlotTypeList(state);
		ingredientSlotType->removeAll();
		for (int i = 1; i <= ingredientSlotTypeList.getTableSize(); ++i) {
			ingredientSlotType->add(ingredientSlotTypeList.getIntAt(i));
		}
		ingredientSlotTypeList.pop();
	} else if (varName == "ingredientAppearance") {
		LuaObject ingredientAppearanceList(state);
		ingredientAppearance->removeAll();
		for (int i = 1; i <= ingredientAppearanceList.getTableSize(); i++) {
			ingredientAppearance->add(ingredientAppearanceList.getStringAt(i));
		}
		ingredientAppearanceList.pop();
	} else if (varName == "resourceTypes") {
		LuaObject resourceTypesList(state);
		resourceTypes->removeAll();
		for (int i = 1; i <= resourceTypesList.getTableSize(); ++i) {
			resourceTypes->add(resourceTypesList.getStringAt(i));
		}
		resourceTypesList.pop();
	} else if (varName == "resourceQuantities") {
		LuaObject resourceQuantitiesList(state);
		resourceQuantities->removeAll();
		for (int i = 1; i <= resourceQuantitiesList.getTableSize(); ++i) {
			resourceQuantities->add(resourceQuantitiesList.getIntAt(i));
		}
		resourceQuantitiesList.pop();
	} else if (varName == "contribution") {
		LuaObject contributionList(state);
		contribution->removeAll();
		for (int i = 1; i <= contributionList.getTableSize(); ++i) {
			contribution->add(contributionList.getIntAt(i));
		}
		contributionList.pop();
	} else if (varName == "targetTemplate") {
		String temp = Lua::getStringParameter(state);
		tanoCRC = temp.hashCode();
	} else if (varName == "additionalTemplates") {
		LuaObject availableTemplateList(state);
		additionalTemplates->removeAll();
		for (int i = 1; i <= availableTemplateList.getTableSize(); ++i) {
			additionalTemplates->add(availableTemplateList.getStringAt(i));
		}
		availableTemplateList.pop();
	} else if (varName == "skillMods") {
		LuaObject skillModList(state);
		skillMods.removeAll();
		for (int i = 1; i <= skillModList.getTableSize(); ++i) {
			LuaObject mod = skillModList.getObjectAt(i);

			String modName = mod.getStringAt(1);
			int modValue = mod.getIntAt(2);

			skillMods.put(modName, modValue);

			mod.pop();
		}
		skillModList.pop();
	} else if (varName == "weaponDots") {
		LuaObject weaponDotList(state);
		weaponDots.removeAll();
		for (int i = 1; i <= weaponDotList.getTableSize(); ++i) {
			LuaObject dot = weaponDotList.getObjectAt(i);
			VectorMap<String, int> dotValues;

			for (int j = 1; j <= dot.getTableSize(); ++j) {
				LuaObject attribute = dot.getObjectAt(j);

				String attrName = attribute.getStringAt(1);
				int attrValue = attribute.getIntAt(2);

				dotValues.put(attrName, attrValue);

				attribute.pop();
			}

			weaponDots.add(dotValues);

			dot.pop();
		}
		weaponDotList.pop();
	} else {
		data->pop();
	}

}

void DraftSchematicObjectTemplate::readObject(LuaObject* templateData) {
	SharedDraftSchematicObjectTemplate::readObject(templateData);

	lua_State* L = templateData->getLuaState();

	if (!templateData->isValidTable())
		return;

	int i = 0;

	lua_pushnil(L);
	while (lua_next(L, -2) != 0) {
		// 'key' is at index -2 and 'value' at index -1
		//printf("%s - %s\n",
		//		lua_tostring(L, -2), lua_typename(L, lua_type(L, -1)));

		int type = lua_type(L, -2);

		if (type == LUA_TSTRING) {
			size_t len = 0;
			const char* varName = lua_tolstring(L, -2, &len);

			parseVariableData(varName, templateData);
		} else
			lua_pop(L, 1);


		++i;
	}

	if (ingredientAppearance->isEmpty() && !ingredientTemplateNames->isEmpty()) {
		for (int i = 0; i < ingredientTemplateNames->size(); ++i) {
			ingredientAppearance->add("");
		}
	}

	draftSlots->removeAll();
	for (int i = 0; i < ingredientTemplateNames->size(); ++i) {
		DraftSlot* newSlot = new DraftSlot();
		newSlot->setStringId(ingredientTemplateNames->get(i),
				ingredientTitleNames->get(i));
		newSlot->setSlotType(ingredientSlotType->get(i));
		newSlot->setResourceType(resourceTypes->get(i));
		newSlot->setQuantity(resourceQuantities->get(i));
		newSlot->setContribution(contribution->get(i));

		addSlot(newSlot);
	}
}

Vector<Reference<ResourceWeight*> >* DraftSchematicObjectTemplate::getResourceWeights() {

	try {
		if (tangibleTemplate == NULL)
			tangibleTemplate = dynamic_cast<SharedTangibleObjectTemplate*> (TemplateManager::instance()->getTemplate(tanoCRC));

		if (tangibleTemplate == NULL) {
			Logger::console.error(
					"Template not found for server crc: "
							+ additionalTemplates->get(0));
			return NULL;
		}
	} catch (...) {
		Logger::console.error(
				"Unhandled exception in DraftSchematicObjectTemplate::getResourceWeights");
		return NULL;
	}

	return tangibleTemplate->getResourceWeights();

}
