/*
 * LuaSuiManager.cpp
 *
 *  Created on: Jan 28, 2012
 *      Author: xyborn
 */

#include "server/ServerCore.h"
#include "SuiManager.h"
#include "LuaSuiManager.h"
#include "server/zone/objects/scene/SceneObject.h"

const char LuaSuiManager::className[] = "LuaSuiManager";

Luna<LuaSuiManager>::RegType LuaSuiManager::Register[] = {
		{ "sendKeypadSui", &LuaSuiManager::sendKeypadSui },
		{ "sendConfirmSui", &LuaSuiManager::sendConfirmSui },
		{ "sendMessageBox", &LuaSuiManager::sendMessageBox },
		{ "sendInputBox", &LuaSuiManager::sendInputBox },
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

	realObject->sendKeypadSui(keypad, creatureSceneObject, play, callback);

	return 0;
}

int LuaSuiManager::sendConfirmSui(lua_State* L) {
	String button = lua_tostring(L, -1);
	String prompt = lua_tostring(L, -2);
	String callback = lua_tostring(L, -3);
	String play = lua_tostring(L, -4);
	SceneObject* scno = (SceneObject*)lua_touserdata(L, -5);
	SceneObject* scno2 = (SceneObject*)lua_touserdata(L, -6);

	realObject->sendConfirmSui(scno2, scno, play, callback, prompt, button);

	return 0;
}

int LuaSuiManager::sendInputBox(lua_State* L) {
	String button = lua_tostring(L, -1);
	String prompt = lua_tostring(L, -2);
	String callback = lua_tostring(L, -3);
	String play = lua_tostring(L, -4);
	SceneObject* player = (SceneObject*) lua_touserdata(L, -5);
	SceneObject* usingObject = (SceneObject*) lua_touserdata(L, -6);

	realObject->sendInputBox(usingObject, player, play, callback, prompt, button);

	return 0;
}

int LuaSuiManager::sendMessageBox(lua_State* L) {
	SceneObject* usingObject = (SceneObject*) lua_touserdata(L, -7);
	SceneObject* targetPlayer = (SceneObject*) lua_touserdata(L, -6);
	String title = lua_tostring(L, -5);
	String text = lua_tostring(L, -4);
	String okButton = lua_tostring(L, -3);
	String screenplay = lua_tostring(L, -2);
	String callback = lua_tostring(L, -1);

	realObject->sendMessageBox(usingObject, targetPlayer, title, text, okButton, screenplay, callback);

	return 0;
}
