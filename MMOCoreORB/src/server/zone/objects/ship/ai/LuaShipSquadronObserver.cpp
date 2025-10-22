
/*
 *	Copyright <SWGEmu>
 *	See file COPYING for copying conditions.
 *
 *	LuaShipSquadronObserver.cpp
 *
 *	Created on: 2025-10-21
 *	Author: Hakry
 */


 /*
#include "LuaShipSquadronObserver.h"


const char LuaShipSquadronObserver::className[] = "LuaShipSquadronObserver";

Luna<LuaShipSquadronObserver>::RegType LuaShipSquadronObserver::Register[] = {
	{ "_setObject", &LuaShipSquadronObserver::_setObject },
	{ "_getObject", &LuaSceneObject::_getObject },


	{ 0, 0 }
};

LuaShipSquadronObserver::LuaShipSquadronObserver(lua_State *L) : LuaShipObject(L) {
#ifdef DYNAMIC_CAST_LUAOBJECTS
	realObject = dynamic_cast<SquadronObserver*>(_getRealSceneObject());

	E3_ASSERT(!_getRealSceneObject() || realObject != nullptr);
#else
	realObject = static_cast<SquadronObserver*>(lua_touserdata(L, 1));
#endif
}

LuaShipSquadronObserver::~LuaShipSquadronObserver(){
}

int LuaShipSquadronObserver::_setObject(lua_State* L) {
	LuaShipObject::_setObject(L);

#ifdef DYNAMIC_CAST_LUAOBJECTS
	auto obj = dynamic_cast<SquadronObserver*>(_getRealSceneObject());

	if (realObject != obj)
		realObject = obj;

	E3_ASSERT(!_getRealSceneObject() || realObject != nullptr);
#else
	auto obj = static_cast<SquadronObserver*>(lua_touserdata(L, -1));

	if (realObject != obj)
		realObject = obj;
#endif

	return 0;
}
*/