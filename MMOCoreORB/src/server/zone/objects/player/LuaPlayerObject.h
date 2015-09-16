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
#include "server/zone/objects/player/PlayerObject.h"

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
	int increaseFactionStanding(lua_State* L);
	int decreaseFactionStanding(lua_State* L);
	int addWaypoint(lua_State* L);
	int removeWaypoint(lua_State* L);
	int removeWaypointBySpecialType(lua_State* L);
	int addRewardedSchematic(lua_State* L);
	int addPermissionGroup(lua_State* L);
	int removePermissionGroup(lua_State* L);
	int hasPermissionGroup(lua_State* L);
	int awardBadge(lua_State* L);
	int hasBadge(lua_State* L);
	int addHologrindProfession(lua_State* L);
	int getHologrindProfessions(lua_State* L);
	int getForcePower(lua_State* L);
	int getForcePowerMax(lua_State* L);
	int setForcePower(lua_State* L);
	int isJedi(lua_State* L);
	int setJediState(lua_State* L);
	int isOnline(lua_State* L);
	int setActiveQuestsBit(lua_State* L);
	int clearActiveQuestsBit(lua_State* L);
	int hasActiveQuestBitSet(lua_State* L);
	int hasCompletedQuestsBitSet(lua_State* L);
	int setCompletedQuestsBit(lua_State* L);
	int clearCompletedQuestsBit(lua_State* L);
	int hasAbility(lua_State* L);
	int addAbility(lua_State* L);
	int getExperience(lua_State* L);
	int addEventPerk(lua_State* L);
	int getEventPerkCount(lua_State* L);
	int getCharacterAgeInDays(lua_State* L);
	int isPrivileged(lua_State* L);
	int closeSuiWindowType(lua_State* L);
	int getExperienceList(lua_State* L);
	int getExperienceCap(lua_State* L);
	int activateQuest(lua_State* L);
	int canActivateQuest(lua_State* L);

private:
	// The pointer to the 'real object' defined in object.cc
	Reference<PlayerObject*> realObject;
};



#endif /* LUAPLAYEROBJECT_H_ */
