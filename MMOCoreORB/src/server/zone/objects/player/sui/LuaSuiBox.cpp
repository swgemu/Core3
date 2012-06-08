/*
 * LuaSuiBox.cpp
 *
 *  Created on: 27/01/2012
 *      Author: xyborn
 */

#include "LuaSuiBox.h"
#include "SuiBox.h"
#include "server/zone/objects/scene/SceneObject.h"

const char LuaSuiBox::className[] = "LuaSuiBox";

Luna<LuaSuiBox>::RegType LuaSuiBox::Register[] = {
		{ "_setObject", &LuaSuiBox::_setObject },
		{ "getUsingObject", &LuaSuiBox::getUsingObject },
		{ 0, 0 }
};

LuaSuiBox::LuaSuiBox(lua_State *L) {
	realObject = static_cast<SuiBox*>(lua_touserdata(L, 1));
}

LuaSuiBox::~LuaSuiBox(){
}

int LuaSuiBox::_setObject(lua_State* L) {
	realObject = static_cast<SuiBox*>(lua_touserdata(L, -1));

	return 0;
}

int LuaSuiBox::getUsingObject(lua_State* L) {
	SceneObject* obj = realObject->getUsingObject().get().get();

	if (obj != NULL) {
		lua_pushlightuserdata(L, obj);
	} else {
		lua_pushnil(L);
	}

	return 1;
}
