/*
 * LuaSuiManager.cpp
 *
 *  Created on: Jan 28, 2012
 *      Author: xyborn
 */

#include "server/ServerCore.h"
#include "SuiManager.h"
#include "server/zone/objects/player/sui/keypadbox/SuiKeypadBox.h"
#include "LuaSuiManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/callbacks/LuaSuiCallback.h"

const char LuaSuiManager::className[] = "LuaSuiManager";

Luna<LuaSuiManager>::RegType LuaSuiManager::Register[] = {
		{ "sendKeypadSui", &LuaSuiManager::sendKeypadSui },
		{ 0, 0 }
};

LuaSuiManager::LuaSuiManager(lua_State* L) {
	realObject = SuiManager::instance();
}

LuaSuiManager::~LuaSuiManager(){
}

int LuaSuiManager::sendKeypadSui(lua_State* L) {
	String callback = lua_tostring(L, -1);
	String play = lua_tostring(L, -2);
	SceneObject* creatureSceneObject = (SceneObject*) lua_touserdata(L, -3);
	SceneObject* keypad = (SceneObject*) lua_touserdata(L, -4);

	if (keypad == NULL)
		return 0;

	if (creatureSceneObject == NULL || !creatureSceneObject->isCreatureObject())
		return 0;

	CreatureObject* creature = (CreatureObject*) creatureSceneObject;

	PlayerObject* playerObject = creature->getPlayerObject();

	if (playerObject != NULL) {
		ManagedReference<SuiKeypadBox*> keypadSui = new SuiKeypadBox(creature, 0x00);
		keypadSui->setCallback(new LuaSuiCallback(ServerCore::getZoneServer(), play, callback));
		keypadSui->setUsingObject(keypad);
		keypadSui->setForceCloseDisabled();
		creature->sendMessage(keypadSui->generateMessage());
		playerObject->addSuiBox(keypadSui);
	}

	return 0;
}
