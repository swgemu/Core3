/*
 * LuaSuiPageData.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: crush
 */

#include "LuaSuiPageData.h"
#include "server/zone/objects/player/sui/SuiPageData.h"

const char LuaSuiPageData::className[] = "LuaSuiPageData";

Luna<LuaSuiPageData>::RegType LuaSuiPageData::Register[] = {
		{ "_setObject", &LuaSuiPageData::_setObject },
		{ 0, 0 }
};

LuaSuiPageData::LuaSuiPageData(lua_State *L) {
	realObject = static_cast<SuiPageData*>(lua_touserdata(L, 1));
}

LuaSuiPageData::~LuaSuiPageData() {
}

int LuaSuiPageData::_setObject(lua_State* L) {
	realObject = static_cast<SuiPageData*>(lua_touserdata(L, -1));

	return 0;
}
