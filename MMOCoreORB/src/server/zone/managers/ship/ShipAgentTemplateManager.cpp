/*
 * ShipAgentTemplateManager.cpp
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#include "ShipAgentTemplateManager.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "templates/params/ship/ShipFlag.h"
#include "conf/ConfigManager.h"
#include "templates/params/creature/ObjectFlag.h"

AtomicInteger ShipAgentTemplateManager::loadedMobileTemplates;

int ShipAgentTemplateManager::DEBUG_MODE = 0;
int ShipAgentTemplateManager::ERROR_CODE = NO_ERROR;

ShipAgentTemplateManager::ShipAgentTemplateManager() : Logger("ShipAgentTemplateManager") {
	setLoggingName("ShipAgentTemplateManager");

	lua = new Lua();
	lua->init();

	if (DEBUG_MODE) {
		setLogging(true);
		lua->setLogging(true);
	}

	hashTable.setNullValue(nullptr);

	lua->registerFunction("includeFile", includeFile);
	lua->registerFunction("addTemplate", addTemplate);

	lua->setGlobalInt("NONE", 				ObjectFlag::NONE);
	lua->setGlobalInt("ATTACKABLE",		 	ObjectFlag::ATTACKABLE);
	lua->setGlobalInt("AGGRESSIVE", 		ObjectFlag::AGGRESSIVE);
	lua->setGlobalInt("OVERT", 				ObjectFlag::OVERT);
	lua->setGlobalInt("TEF", 				ObjectFlag::TEF);
	lua->setGlobalInt("PLAYER", 			ObjectFlag::PLAYER);
	lua->setGlobalInt("ENEMY",		 		ObjectFlag::ENEMY);
	lua->setGlobalInt("WILLBEDECLARED", 	ObjectFlag::WILLBEDECLARED);
	lua->setGlobalInt("WASDECLARED", 		ObjectFlag::WASDECLARED);

	lua->setGlobalInt("CONVERSABLE",		OptionBitmask::CONVERSE);
	lua->setGlobalInt("AIENABLED",			OptionBitmask::AIENABLED);
	lua->setGlobalInt("INVULNERABLE",		OptionBitmask::INVULNERABLE);
	lua->setGlobalInt("FACTIONAGGRO",		OptionBitmask::FACTIONAGGRO);
	lua->setGlobalInt("INTERESTING",		OptionBitmask::INTERESTING);
	lua->setGlobalInt("JTLINTERESTING",		OptionBitmask::JTLINTERESTING);

	// Ship Bitmasks in ShipFlag.h
	lua->setGlobalInt("ESCORT",				ShipFlag::ESCORT);
	lua->setGlobalInt("FOLLOW",				ShipFlag::FOLLOW);
	lua->setGlobalInt("TURRETSHIP",			ShipFlag::TURRETSHIP);
	lua->setGlobalInt("GUARD_PATROL",		ShipFlag::GUARD_PATROL);
	lua->setGlobalInt("RANDOM_PATROL",		ShipFlag::RANDOM_PATROL);
	lua->setGlobalInt("FIXED_PATROL",		ShipFlag::FIXED_PATROL);
	lua->setGlobalInt("SQUADRON_PATROL",	ShipFlag::SQUADRON_PATROL);
	lua->setGlobalInt("SQUADRON_FOLLOW",	ShipFlag::SQUADRON_FOLLOW);
	lua->setGlobalInt("TEST",				ShipFlag::TEST);

	loadLuaConfig();
}

ShipAgentTemplateManager::~ShipAgentTemplateManager() {
}

void ShipAgentTemplateManager::loadLuaConfig() {
}

int ShipAgentTemplateManager::loadTemplates() {
	if (!DEBUG_MODE) {
		info(true) << "Loading Ship Agent Templates...\n";
	}

	bool ret = false;

	try {
		ret = lua->runFile("scripts/ship_mobile/ship_agents.lua");
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
		ret = false;
	}

	lua = nullptr;

	if (!ret) {
		ERROR_CODE = GENERAL_ERROR;
		error() << "Failed to load Ship Agent Templates";
	}

	if (!DEBUG_MODE) {
		info(true) << "Finished Loading Ship Agent Templates -  Total: " << hashTable.size();
	}

	return ERROR_CODE;
}

int ShipAgentTemplateManager::checkArgumentCount(lua_State* L, int args) {
	int parameterCount = lua_gettop(L);

	if (parameterCount < args) {
		return 1;
	} else if (parameterCount > args)
		return 2;

	return 0;
}

int ShipAgentTemplateManager::includeFile(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to ShipAgentTemplateManager::includeFile");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String filename = Lua::getStringParameter(L);

	int oldError = ERROR_CODE;

	bool ret = Lua::runFile("scripts/ship_mobile/ships/" + filename, L);

	if (!ret) {
		ERROR_CODE = GENERAL_ERROR;

		instance()->error("running file scripts/ship_mobile/ships/" + filename);
	} else {
		if (!oldError && ERROR_CODE) {
			instance()->error("running file scripts/ship_mobile/ships/" + filename);
		}
	}

	return 0;
}

int ShipAgentTemplateManager::addTemplate(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to ShipAgentTemplateManager::addTemplate");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String tempName = lua_tostring(L, -2);
	uint32 crc = (uint32) tempName.hashCode();

	LuaObject obj(L);

	ShipAgentTemplate* newTemp = new ShipAgentTemplate();

	newTemp->setTemplateName(tempName);
	newTemp->readObject(&obj);

	if (instance()->hashTable.containsKey(crc)) {
		luaL_where (L, 2);
		String luaMethodName = lua_tostring(L, -1);

		lua_pop(L, 1);

		instance()->error("overwriting Ship Mobile " + tempName + " with " + luaMethodName);

		ERROR_CODE = DUPLICATE_MOBILE;
	}

	ShipAgentTemplateManager::instance()->hashTable.put(crc, newTemp);

	int count = loadedMobileTemplates.increment();

	if (ConfigManager::instance()->isProgressMonitorActivated() && !DEBUG_MODE) {
		printf("\r\tLoading ship mobile templates: [%d] / [?]\t", count);
	}

	return 0;
}
