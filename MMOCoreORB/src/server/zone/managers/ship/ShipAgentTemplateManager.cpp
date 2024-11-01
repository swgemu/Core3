/*
 * ShipAgentTemplateManager.cpp
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#include "ShipAgentTemplateManager.h"
#include "conf/ConfigManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/managers/stringid/StringIdManager.h"

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
