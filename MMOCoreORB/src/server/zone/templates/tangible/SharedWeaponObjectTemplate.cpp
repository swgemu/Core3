/*
 * SharedWeaponObjectTemplate.cpp
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#include "SharedWeaponObjectTemplate.h"

void SharedWeaponObjectTemplate::parseVariableData(const String& varName, LuaObject* templateData) {
	lua_State* state = templateData->getLuaState();

	if (varName == "weaponEffect") {
		weaponEffect = Lua::getStringParameter(state);
	} else if (varName == "weaponEffectIndex") {
		weaponEffectIndex = Lua::getIntParameter(state);
	} else if (varName == "attackType") {
		attackType = Lua::getIntParameter(state);
	} else
		templateData->pop();
}

void SharedWeaponObjectTemplate::parseVariableData(const String& varName, Chunk* data) {
	if (varName == "weaponEffect") {
		weaponEffect.parse(data);
	} else if (varName == "weaponEffectIndex") {
		weaponEffectIndex.parse(data);
	} else if (varName == "attackType") {
		attackType.parse(data);
	}
}

void SharedWeaponObjectTemplate::parseFileData(IffStream* iffStream) {
	iffStream->openChunk('PCNT');

	int variableCount = iffStream->getInt();

	iffStream->closeChunk('PCNT');

	for (int i = 0; i < variableCount; ++i) {
	//while (iffStream->getRemainingSubChunksNumber() > 0) {
		Chunk* chunk = iffStream->openChunk('XXXX');

		if (chunk == NULL)
			continue;

		String varName;
		iffStream->getString(varName);

		//std::cout << "parsing wtf shit:[" << varName.toStdString() << "]\n";
		parseVariableData(varName, chunk);

		iffStream->closeChunk();
	}
}

void SharedWeaponObjectTemplate::readObject(IffStream* iffStream) {
	uint32 nextType = iffStream->getNextFormType();

	if (nextType != 'SWOT') {
		//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

		SharedTangibleObjectTemplate::readObject(iffStream);

		return;
	}

	iffStream->openForm('SWOT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream);

		derv = iffStream->getNextFormType();
	}

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

	iffStream->closeForm('SWOT');
}

void SharedWeaponObjectTemplate::readObject(LuaObject* templateData) {
	SharedTangibleObjectTemplate::readObject(templateData);

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

	//here goes server data only

	xpType = templateData->getStringField("xpType");

	damageType = templateData->getIntField("damageType");

	LuaObject certifications = templateData->getObjectField("certificationsRequired");

	certificationsRequired.removeAll();

	for (int i = 1; i <= certifications.getTableSize(); ++i) {
		certificationsRequired.add(certifications.getStringAt(i));
	}

	certifications.pop();

	creatureAccuracyModifiers.removeAll();

	LuaObject accMods = templateData->getObjectField("creatureAccuracyModifiers");

	for (int i = 1; i <= accMods.getTableSize(); ++i) {
		creatureAccuracyModifiers.add(accMods.getStringAt(i));
	}

	accMods.pop();

	creatureAimModifiers.removeAll();

	LuaObject aimMods = templateData->getObjectField("creatureAimModifiers");

	for (int i = 1; i <= aimMods.getTableSize(); ++i) {
		creatureAimModifiers.add(aimMods.getStringAt(i));
	}

	aimMods.pop();

	defenderDefenseModifiers.removeAll();

	LuaObject defMods = templateData->getObjectField("defenderDefenseModifiers");

	for (int i = 1; i <= defMods.getTableSize(); ++i) {
		defenderDefenseModifiers.add(defMods.getStringAt(i));
	}

	defMods.pop();

	damageModifiers.removeAll();

	LuaObject dmgMods = templateData->getObjectField("damageModifiers");

	for (int i = 1; i <= dmgMods.getTableSize(); ++i) {
		damageModifiers.add(dmgMods.getStringAt(i));
	}

	dmgMods.pop();

	speedModifiers.removeAll();

	LuaObject speedMods = templateData->getObjectField("speedModifiers");

	for (int i = 1; i <= speedMods.getTableSize(); ++i) {
		speedModifiers.add(speedMods.getStringAt(i));
	}

	speedMods.pop();

	defenderSecondaryDefenseModifiers.removeAll();

	LuaObject secMods = templateData->getObjectField("defenderSecondaryDefenseModifiers");

	for (int i = 1; i <= secMods.getTableSize(); ++i)
		defenderSecondaryDefenseModifiers.add(secMods.getStringAt(i));

	secMods.pop();

	defenderToughnessModifiers.removeAll();

	LuaObject toughMods = templateData->getObjectField("defenderToughnessModifiers");

	for (int i = 1; i <= toughMods.getTableSize(); ++i)
		defenderToughnessModifiers.add(toughMods.getStringAt(i));

	toughMods.pop();

	armorPiercing = templateData->getIntField("armorPiercing");

	healthAttackCost = templateData->getIntField("healthAttackCost");
	actionAttackCost = templateData->getIntField("actionAttackCost");
	mindAttackCost = templateData->getIntField("mindAttackCost");
	forceCost = templateData->getIntField("forceCost");

	pointBlankAccuracy = templateData->getIntField("pointBlankAccuracy");
	pointBlankRange = templateData->getIntField("pointBlankRange");

	idealRange = templateData->getIntField("idealRange");
	idealAccuracy = templateData->getIntField("idealAccuracy");

	maxRange = templateData->getIntField("maxRange");
	maxRangeAccuracy = templateData->getIntField("maxRangeAccuracy");

	minDamage = templateData->getIntField("minDamage");
	maxDamage = templateData->getIntField("maxDamage");

	woundsRatio = templateData->getFloatField("woundsRatio");

	area = templateData->getIntField("area");

	attackSpeed = templateData->getFloatField("attackSpeed");
}
