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
	int _getObject(lua_State* L);
	int sendTo(lua_State* L);
	int sendUpdateTo(lua_State* L);
	int setProperty(lua_State* L);
	int getPropertyValue(lua_State* L);
	int setDefaultCallback(lua_State* L);
	int setTargetNetworkId(lua_State* L);
	int getTargetNetworkId(lua_State* L);
	int setForceCloseDistance(lua_State* L);
	int addDataItem(lua_State* L);
	int clearDataSource(lua_State* L);
	int addDataSourceContainer(lua_State* L);
	int clearDataSourceContainer(lua_State* L);
	int addChildWidget(lua_State* L);
	int subscribeToEvent(lua_State* L);
	int getPageId(lua_State* L);
	int subscribeToPropertyForEvent(lua_State* L);
	int getStoredData(lua_State* L);
	int setStoredData(lua_State* L);
	int deleteStoredData(lua_State* L);
private:
	Reference<SuiPageData*> realObject;
};

#endif /* LUASUIPAGEDATA_H_ */
