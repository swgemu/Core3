/*
 * LuaSuiManager.cpp
 *
 *  Created on: Jan 28, 2012
 *      Author: xyborn
 */

#include "SuiManager.h"
#include "LuaSuiManager.h"

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
	return 0;
}
