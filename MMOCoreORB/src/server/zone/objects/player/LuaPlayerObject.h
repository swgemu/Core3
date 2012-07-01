/*
 * LuaPlayerObject.h
 *
 *  Created on: 13/01/2012
 *      Author: victor
 */

#ifndef LUAPLAYEROBJECT_H_
#define LUAPLAYEROBJECT_H_

#include "engine/engine.h"
#include "server/zone/objects/intangible/LuaIntangibleObject.h"
#include "PlayerObject.h"

class LuaPlayerObject : public LuaIntangibleObject {
public:
	// Constants
	static const char className[];
	static Luna<LuaPlayerObject>::RegType Register[];

	// Initialize the pointer
	LuaPlayerObject(lua_State *L);
	~LuaPlayerObject();

	int _setObject(lua_State* L);
	// Methods we will need to use
	int getFactionStanding(lua_State* L);
	int isOnLeave(lua_State* L);
	int isOvert(lua_State* L);
	int isCovert(lua_State* L);
	int setFactionStatus(lua_State* L);
	int isChangingFactionStatus(lua_State* L);
	int increaseFactionStanding(lua_State* L);
	int decreaseFactionStanding(lua_State* L);
	int addWaypoint(lua_State* L);
	int addRewardedSchematic(lua_State* L);
	int addPermissionGroup(lua_State* L);
	int removePermissionGroup(lua_State* L);
	int hasPermissionGroup(lua_State* L);
	int awardBadge(lua_State* L);
	int hasBadge(lua_State* L);

private:
	// The pointer to the 'real object' defined in object.cc
	Reference<PlayerObject*> realObject;
};



#endif /* LUAPLAYEROBJECT_H_ */
