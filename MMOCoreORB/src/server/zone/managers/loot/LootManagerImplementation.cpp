/*
 * LootManagerImplementation.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: Kyle
 */

#include "engine/engine.h"

#include "LootManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/loot/lootgroup/LootGroupObject.h"
#include "server/zone/managers/loot/lootgroup/LootObject.h"


void LootManagerImplementation::initialize() {
	lua = new Lua();
	lua->init();

	info("loading configuration");
	if(!loadConfigData()) {

		loadDefaultConfig();

		info("***** ERROR in configuration, using default values");
	}

	info("initialized");
}

bool LootManagerImplementation::loadConfigFile() {
	return lua->runFile("scripts/managers/loot_manager.lua");
}

bool LootManagerImplementation::loadConfigData() {
	if (!loadConfigFile())
		return false;


	return true;
}

void LootManagerImplementation::loadDefaultConfig() {

}

void LootManagerImplementation::createLoot(SceneObject* container, CreatureObject* creature) {

}

void LootManagerImplementation::createLoot(SceneObject* container, const String& lootGroup) {

}
