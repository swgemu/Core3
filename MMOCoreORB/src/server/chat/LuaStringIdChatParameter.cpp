/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "LuaStringIdChatParameter.h"

const char LuaStringIdChatParameter::className[] = "LuaStringIdChatParameter";

Luna<LuaStringIdChatParameter>::RegType LuaStringIdChatParameter::Register[] = {
		{ "_setObject", &LuaStringIdChatParameter::_setObject },
		{ "_getObject", &LuaStringIdChatParameter::_getObject },
		{ "setTT", &LuaStringIdChatParameter::setTT },
		{ "setTU", &LuaStringIdChatParameter::setTU },
		{ "setTO", &LuaStringIdChatParameter::setTO },
		{ "setDI", &LuaStringIdChatParameter::setDI },
		{ "setDF", &LuaStringIdChatParameter::setDF },
		{ 0, 0 }
};

LuaStringIdChatParameter::LuaStringIdChatParameter(lua_State * L) {
	String fullPath = lua_tostring(L, 1);
	realObject = new StringIdChatParameter(fullPath);
}

LuaStringIdChatParameter::~LuaStringIdChatParameter() {
}

int LuaStringIdChatParameter::_setObject(lua_State* L) {
	realObject = static_cast<StringIdChatParameter*>(lua_touserdata(L, -1));

	return 0;
}

int LuaStringIdChatParameter::_getObject(lua_State* L) {
	lua_pushlightuserdata(L, realObject.get());

	return 1;
}

int LuaStringIdChatParameter::setTT(lua_State *L) {
	String tt = lua_tostring(L, -1);

	realObject->setTT(tt);

	return 0;
}

int LuaStringIdChatParameter::setTU(lua_State *L) {
	String tu = lua_tostring(L, -1);

	realObject->setTU(tu);

	return 0;
}

int LuaStringIdChatParameter::setTO(lua_State *L) {
	String to = lua_tostring(L, -1);

	realObject->setTO(to);

	return 0;
}

int LuaStringIdChatParameter::setDI(lua_State *L) {
	int di = lua_tointeger(L, -1);

	realObject->setDI(di);

	return 0;
}

int LuaStringIdChatParameter::setDF(lua_State *L) {
	float df = lua_tonumber(L, -1);

	realObject->setDF(df);

	return 0;
}
