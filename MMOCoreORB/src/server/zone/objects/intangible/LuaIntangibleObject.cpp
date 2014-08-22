/*
 * LuaIntangibleObject.cpp
 *
 *  Created on: 13/01/2012
 *      Author: victor
 */

#include "LuaIntangibleObject.h"

const char LuaIntangibleObject::className[] = "LuaIntangibleObject";

Luna<LuaIntangibleObject>::RegType LuaIntangibleObject::Register[] = {
		{ "_setObject", &LuaIntangibleObject::_setObject },
		{ "_getObject", &LuaSceneObject::_getObject },
		{ 0, 0 }
};


LuaIntangibleObject::LuaIntangibleObject(lua_State *L) : LuaSceneObject(L) {
	realObject = (IntangibleObject*)lua_touserdata(L, 1);
}

LuaIntangibleObject::~LuaIntangibleObject() {
}

int LuaIntangibleObject::_setObject(lua_State* L) {
	realObject = (IntangibleObject*)lua_touserdata(L, -1);

	LuaSceneObject::_setObject(L);

	return 0;
}
