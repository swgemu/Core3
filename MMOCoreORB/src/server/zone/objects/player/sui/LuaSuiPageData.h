/*
 * LuaSuiPageData.h
 *
 *  Created on: Nov 7, 2013
 *      Author: crush
 */

#ifndef LUASUIPAGEDATA_H_
#define LUASUIPAGEDATA_H_

#include "engine/engine.h"
#include "server/zone/objects/player/sui/SuiPageData.h"

class LuaSuiPageData {
public:
	static const char className[];
	static Luna<LuaSuiPageData>::RegType Register[];

	LuaSuiPageData(lua_State *L);
	~LuaSuiPageData();

	int _setObject(lua_State* L);
private:
	Reference<SuiPageData*> realObject;
};

#endif /* LUASUIPAGEDATA_H_ */
