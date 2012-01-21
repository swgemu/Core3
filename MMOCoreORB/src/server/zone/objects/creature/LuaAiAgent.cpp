/*
 * LuaAiAgent.cpp
 *
 *  Created on: 21/01/2012
 *      Author: victor
 */

#include "AiAgent.h"
#include "LuaAiAgent.h"

const char LuaAiAgent::className[] = "LuaAiAgent";

Luna<LuaAiAgent>::RegType LuaAiAgent::Register[] = {
		{ "_setObject", &LuaAiAgent::_setObject },
		{ "_getObject", &LuaAiAgent::_getObject },
		{ "setFollowObject", &LuaAiAgent::setFollowObject },
		{ 0, 0 }
};


LuaAiAgent::LuaAiAgent(lua_State *L) : LuaCreatureObject(L) {
	realObject = static_cast<AiAgent*>(lua_touserdata(L, 1));
}

LuaAiAgent::~LuaAiAgent(){
}

int LuaAiAgent::_setObject(lua_State* L) {
	realObject = static_cast<AiAgent*>(lua_touserdata(L, -1));

	return 0;
}

int LuaAiAgent::_getObject(lua_State* L) {
	lua_pushlightuserdata(L, realObject.get());

	return 0;
}

int LuaAiAgent::setFollowObject(lua_State* L) {
	//setFollowObject(SceneObject obj)
	SceneObject* obj = (SceneObject*) lua_touserdata(L, -1);

	realObject->setFollowObject(obj);

	return 0;
}

