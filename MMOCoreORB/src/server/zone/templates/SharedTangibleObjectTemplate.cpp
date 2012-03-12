/*
 * SharedTangibleObjectTemplate.cpp
 *
 *  Created on: 30/04/2010
 *      Author: victor
 */

#include "SharedTangibleObjectTemplate.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/templates/footprint/StructureFootprint.h"
#include "params/PaletteColorCustomizationVariables.h"
#include "params/RangedIntCustomizationVariables.h"

SharedTangibleObjectTemplate::SharedTangibleObjectTemplate() {
	numberExperimentalProperties = new Vector<short>();
	experimentalProperties = new Vector<String>();
	experimentalWeights = new Vector<short>();
	experimentalGroupTitles = new Vector<String>();
	experimentalSubGroupTitles = new Vector<String>();
	experimentalMin = new Vector<int>();
	experimentalMax = new Vector<int>();
	experimentalPrecision = new Vector<short>();
	playerRaces = new Vector<uint32>();

	resourceWeights = new Vector<Reference<ResourceWeight* > >();

	skillMods.setNoDuplicateInsertPlan();
	skillMods.setNullValue(0);

	faction = 0;
	factoryCrateSize = 100;
}

SharedTangibleObjectTemplate::~SharedTangibleObjectTemplate() {
	delete numberExperimentalProperties;
	delete experimentalProperties;
	delete experimentalWeights;
	delete experimentalGroupTitles;
	delete experimentalSubGroupTitles;
	delete experimentalMin;
	delete experimentalMax;
	delete experimentalPrecision;
	delete playerRaces;
	delete resourceWeights;
}

void SharedTangibleObjectTemplate::parseFileData(IffStream* iffStream) {
	iffStream->openChunk('PCNT');

	int variableCount = iffStream->getInt();

	iffStream->closeChunk('PCNT');

	for (int i = 0; i < variableCount; ++i) {
		Chunk* chunk = iffStream->openChunk();

		if (chunk == NULL)
			continue;

		if (chunk->getChunkID() == 'XXXX') {
			String varName;
			chunk->readString(varName);

			parseVariableData(varName, chunk);
		} else {
			Logger::console.error("WTF AM I OPENING AGAIN");
		}

		iffStream->closeChunk();
	}
}

void SharedTangibleObjectTemplate::parseVariableData(const String& varName, LuaObject* data) {
	lua_State* state = data->getLuaState();
	TemplateManager* templateManager = TemplateManager::instance();

	if (varName == "certificationsRequired") {
		LuaObject certifications(state);
		certificationsRequired.removeAll();
		for (int i = 1; i <= certifications.getTableSize(); ++i) {
			certificationsRequired.add(certifications.getStringAt(i));
		}

		certifications.pop();
	} else if (varName == "structureFootprintFileName") {
		structureFootprint = templateManager->loadStructureFootprint(Lua::getStringParameter(state));
	} else if (varName == "targetable") {
		targetable = Lua::getByteParameter(state);
	} else if (varName == "playerUseMask") {
		playerUseMask = Lua::getShortParameter(state);
	} else if (varName == "useCount") {
		useCount = Lua::getIntParameter(state);
	} else if (varName == "factoryCrateSize") {
		factoryCrateSize = Lua::getIntParameter(state);
	} else if (varName == "maxCondition") {
		maxCondition = Lua::getIntParameter(state);
	} else if (varName == "level") {
		level = Lua::getIntParameter(state);
	} else if (varName == "optionsBitmask") {
		optionsBitmask = Lua::getIntParameter(state);
	} else if (varName == "pvpStatusBitmask") {
		pvpStatusBitmask = Lua::getIntParameter(state);
	} else if (varName == "sliceable") {
		sliceable = Lua::getIntParameter(state);
	} else if (varName == "faction") {
		String factionString = Lua::getStringParameter(state);
		faction = factionString.toLowerCase().hashCode();
	} else if (varName == "playerRaces") {
		LuaObject races(state);

		// Inherited lists need to be tossed if a new list is about to be created
		if (playerRaces->size() != 0) {
			playerRaces->removeAll();
		}

		for (int i = 1; i <= races.getTableSize(); ++i) {
			String race = races.getStringAt(i);

			if (!playerRaces->contains(race.hashCode())) {
				playerRaces->add(race.hashCode());
			}


		}

		races.pop();
	} else if (varName == "skillMods") {
		LuaObject smods(state);
		for (int i = 1; i <= smods.getTableSize(); ++i) {
			lua_rawgeti(state, -1, i);
			LuaObject mod(state);

			String modName = mod.getStringAt(1);
			int64 modValue = mod.getLongAt(2);

			skillMods.put(modName, modValue);

			mod.pop();
		}
		smods.pop();
	} else if (varName == "numberExperimentalProperties") {
		LuaObject numberExperimentalPropertiesList(state);
		numberExperimentalProperties->removeAll();
		for (int i = 1; i <= numberExperimentalPropertiesList.getTableSize(); ++i) {
			numberExperimentalProperties->add(numberExperimentalPropertiesList.getIntAt(i));
		}

		numberExperimentalPropertiesList.pop();
	} else if (varName == "experimentalProperties") {
		LuaObject experimentalPropertiesList(state);
		experimentalProperties->removeAll();
		for (int i = 1; i <= experimentalPropertiesList.getTableSize(); ++i) {
			experimentalProperties->add(experimentalPropertiesList.getStringAt(i));
		}

		experimentalPropertiesList.pop();
	} else if (varName == "experimentalWeights") {
		LuaObject experimentalWeightsList(state);
		experimentalWeights->removeAll();
		for (int i = 1; i <= experimentalWeightsList.getTableSize(); ++i) {
			experimentalWeights->add(experimentalWeightsList.getIntAt(i));
		}

		experimentalWeightsList.pop();
	} else if (varName == "experimentalGroupTitles") {
		LuaObject experimentalGroupTitlesList(state);
		experimentalGroupTitles->removeAll();
		for (int i = 1; i <= experimentalGroupTitlesList.getTableSize(); ++i) {
			experimentalGroupTitles->add(experimentalGroupTitlesList.getStringAt(i));
		}

		experimentalGroupTitlesList.pop();
	} else if (varName == "experimentalSubGroupTitles") {
		LuaObject experimentalSubGroupTitlesList(state);
		experimentalSubGroupTitles->removeAll();
		for (int i = 1; i <= experimentalSubGroupTitlesList.getTableSize(); ++i) {
			experimentalSubGroupTitles->add(experimentalSubGroupTitlesList.getStringAt(i));
		}

		experimentalSubGroupTitlesList.pop();
	} else if (varName == "experimentalMin") {
		LuaObject experimentalMinList(state);
		experimentalMin->removeAll();
		for (int i = 1; i <= experimentalMinList.getTableSize(); ++i) {
			experimentalMin->add(experimentalMinList.getIntAt(i));
		}

		experimentalMinList.pop();
	} else if (varName == "experimentalMax") {
		LuaObject experimentalMaxList(state);
		experimentalMax->removeAll();
		for (int i = 1; i <= experimentalMaxList.getTableSize(); ++i) {
			experimentalMax->add(experimentalMaxList.getIntAt(i));
		}

		experimentalMaxList.pop();
	} else if (varName == "experimentalPrecision") {
		LuaObject experimentalPrecisionList(state);
		experimentalPrecision->removeAll();
		for (int i = 1; i <= experimentalPrecisionList.getTableSize(); ++i) {
			experimentalPrecision->add(experimentalPrecisionList.getIntAt(i));
		}
		experimentalPrecisionList.pop();
	} else {
		data->pop();
	}

}

void SharedTangibleObjectTemplate::parseVariableData(const String& varName, Chunk* data) {
	TemplateManager* templateManager = TemplateManager::instance();

	if (varName == "paletteColorCustomizationVariables") {
//		paletteColorCustomizationVariables.parse(data);
		PaletteColorCustomizationVariables pccv;
		pccv.parse(data); //need to parse cant skip
	} else if (varName == "rangedIntCustomizationVariables") {
//		rangedIntCustomizationVariables.parse(data);

		RangedIntCustomizationVariables ricv;
		ricv.parse(data);
	} else if (varName == "constStringCustomizationVariables") {
/*		uint8 unk = data->getUnsignedByte();
		uint32 num = data->getUnsignedInt();

		if (num != 0) {
			QString fileName = data->getIffStream()->getFileName().c_str();
			SWGForensics::instance->printToConsole("EUREKA found constStringCustomizationVariables" + fileName);
			SWGForensics::instance->runTraverse = false;
		}*/
	} else if (varName == "socketDestinations") {
//		socketDestinations.parse(data);
	} else if (varName == "structureFootprintFileName") {		
		StringParam structureFootprintFileName;

		if (structureFootprintFileName.parse(data))
			structureFootprint = templateManager->loadStructureFootprint(structureFootprintFileName.get());
	} else if (varName == "useStructureFootprintOutline") {
/*		useStructureFootprintOutline.parse(data);
		variables[varName] = &useStructureFootprintOutline;*/
	} else if (varName == "targetable") {
		targetable.parse(data);
//		variables[varName] = &targetable;
	} else if (varName == "certificationsRequired") {
/*		certificationsRequired.parse(data);
		variables[varName] = &certificationsRequired;*/
	} else if (varName == "customizationVariableMapping") {
/*		customizationVariableMapping.parse(data);
		variables[varName] = &customizationVariableMapping;*/
	}
}

void SharedTangibleObjectTemplate::readObject(IffStream* iffStream) {
	uint32 nextType = iffStream->getNextFormType();

	if (nextType != 'STOT') {
		SharedObjectTemplate::readObject(iffStream);

		return;
	}

	iffStream->openForm('STOT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream);

		derv = iffStream->getNextFormType();
	}

	/*while (derv != 0) {
		if (derv != '
	}*/

	iffStream->openForm(derv);

	try {
		parseFileData(iffStream);
	} catch (Exception& e) {
		String msg;
		msg += "exception caught parsing file data ->";
		msg += e.getMessage();

		Logger::console.error(msg);
	}

	iffStream->closeForm(derv);

	if (iffStream->getRemainingSubChunksNumber() > 0) {
		readObject(iffStream);
	}


	iffStream->closeForm('STOT');
}


void SharedTangibleObjectTemplate::readObject(LuaObject* templateData) {
	SharedObjectTemplate::readObject(templateData);

	TemplateManager* templateManager = TemplateManager::instance();

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

	/*LuaObject certifications = templateData->getObjectField("certificationsRequired");

	for (int i = 1; i <= certifications.getTableSize(); ++i) {
		certificationsRequired.add(certifications.getStringAt(i));
	}

	certifications.pop();

	structureFootprint = templateManager->loadStructureFootprint(templateData->getStringField("structureFootprintFileName"));

	targetable = templateData->getByteField("targetable");

	playerUseMask = templateData->getShortField("playerUseMask");

	useCount = templateData->getIntField("useCount");

	maxCondition = templateData->getIntField("maxCondition");
	level = templateData->getIntField("level");

	optionsBitmask = templateData->getIntField("optionsBitmask");
	pvpStatusBitmask = templateData->getIntField("pvpStatusBitmask");

	sliceable = templateData->getIntField("sliceable");

	LuaObject numberExperimentalPropertiesList = templateData->getObjectField("numberExperimentalProperties");
	for (int i = 1; i <= numberExperimentalPropertiesList.getTableSize(); ++i) {
		numberExperimentalProperties->add(
				numberExperimentalPropertiesList.getIntAt(i));
	}
	numberExperimentalPropertiesList.pop();

	LuaObject experimentalPropertiesList = templateData->getObjectField("experimentalProperties");
	for (int i = 1; i <= experimentalPropertiesList.getTableSize(); ++i) {
		experimentalProperties->add(experimentalPropertiesList.getStringAt(i));
	}
	experimentalPropertiesList.pop();

	LuaObject experimentalWeightsList = templateData->getObjectField("experimentalWeights");
	for (int i = 1; i <= experimentalWeightsList.getTableSize(); ++i) {
		experimentalWeights->add(experimentalWeightsList.getIntAt(i));
	}
	experimentalWeightsList.pop();

	LuaObject experimentalGroupTitlesList = templateData->getObjectField("experimentalGroupTitles");
	for (int i = 1; i <= experimentalGroupTitlesList.getTableSize(); ++i) {
		experimentalGroupTitles->add(experimentalGroupTitlesList.getStringAt(i));
	}
	experimentalGroupTitlesList.pop();

	LuaObject experimentalSubGroupTitlesList = templateData->getObjectField("experimentalSubGroupTitles");
	for (int i = 1; i <= experimentalSubGroupTitlesList.getTableSize(); ++i) {
		experimentalSubGroupTitles->add(
				experimentalSubGroupTitlesList.getStringAt(i));
	}
	experimentalSubGroupTitlesList.pop();

	LuaObject experimentalMinList = templateData->getObjectField("experimentalMin");
	for (int i = 1; i <= experimentalMinList.getTableSize(); ++i) {
		experimentalMin->add(experimentalMinList.getIntAt(i));
	}
	experimentalMinList.pop();

	LuaObject experimentalMaxList = templateData->getObjectField("experimentalMax");
	for (int i = 1; i <= experimentalMaxList.getTableSize(); ++i) {
		experimentalMax->add(experimentalMaxList.getIntAt(i));
	}
	experimentalMaxList.pop();

	LuaObject experimentalPrecisionList = templateData->getObjectField("experimentalPrecision");
	for (int i = 1; i <= experimentalPrecisionList.getTableSize(); ++i) {
		experimentalPrecision->add(experimentalPrecisionList.getIntAt(i));
	}
	experimentalPrecisionList.pop();*/

	// Add experimental properties groups to the draft schematic
	uint32 weightIterator = 0;
	String subtitle = "";
	resourceWeights->removeAll();
	for (uint32 i = 0; i < numberExperimentalProperties->size(); i++) {

		ResourceWeight* newWeight = new ResourceWeight();

		newWeight->addProperties(experimentalGroupTitles->get(i),
				experimentalSubGroupTitles->get(i), experimentalMin->get(i),
				experimentalMax->get(i), experimentalPrecision->get(i));

		for (uint32 j = 0; j < numberExperimentalProperties->get(i); j++) {

			newWeight->addWeight(experimentalProperties->get(weightIterator),
					experimentalWeights->get(weightIterator));

			weightIterator++;
		}

		resourceWeights->add(newWeight);
	}
}
