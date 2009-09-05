/*
 * ObjectManager.cpp
 *
 *  Created on: Sep 5, 2009
 *      Author: theanswer
 */

#include "ObjectManager.h"
#include "zone/objects/scene/SceneObject.h"
#include "zone/objects/ObjectMap.h"

ObjectManager::ObjectManager() : Logger("ObjectManager") {
	luaInstance = new Lua();
	luaInstance->init();

	info("loading object templates...", true);
	registerFunctions();
	luaInstance->runFile("scripts/object/main.lua");
}

ObjectManager::~ObjectManager() {
	delete luaInstance;
	luaInstance = NULL;
}

SceneObject* ObjectManager::createObject(uint32 objectCRC, uint64 objectID) {
	return NULL;
}


void ObjectManager::registerFunctions() {
	//lua generic
	lua_register(luaInstance->getLuaState(), "includeFile", includeFile);
}

int ObjectManager::includeFile(lua_State* L) {
	String filename = Lua::getStringParameter(L);

	Lua::runFile("scripts/object/" + filename, L);

	return 0;
}
