/*
 * LuaCreatureObject.h
 *
 *  Created on: 31/08/2009
 *      Author: victor
 */

#ifndef LUACREATUREOBJECT_H_
#define LUACREATUREOBJECT_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/LuaSceneObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;

	class LuaCreatureObject : public LuaSceneObject {
	public:
		// Constants
		static const char className[];
		static Luna<LuaCreatureObject>::RegType Register[];

		// Initialize the pointer
		LuaCreatureObject(lua_State *L);
		~LuaCreatureObject();

		int _setObject(lua_State* L);
		int _getObject(lua_State* L);
		// Methods we will need to use
		int getBankCredits(lua_State *L);
		int setBankCredits(lua_State* L);
		int setHAM(lua_State* L);
		int sendSystemMessage(lua_State* L);
		int sendGroupMessage(lua_State* L);
		int playMusicMessage(lua_State *L);
		int sendNewbieTutorialRequest(lua_State *L);
		int hasScreenPlayState(lua_State *L);
		int setScreenPlayState(lua_State *L);
		int getScreenPlayState(lua_State *L);
		int sendNewbieTutorialEnableHudElement(lua_State* L);
		int getInCellNumber(lua_State* L);
		int sendOpenHolocronToPageMessage(lua_State* L);
		int getTargetID(lua_State* L);
		int clearCombatState(lua_State* L);
		int getHAM(lua_State* L);
		int getMaxHAM(lua_State* L);
		int inflictDamage(lua_State* L);
		int playEffect(lua_State* L);
		int setState(lua_State* L);
		int setPosture(lua_State* L);
		int hasSkill(lua_State* L);
		int removeSkill(lua_State* L);
		int getConversationSession(lua_State* L);
		int doAnimation(lua_State* L);
		int engageCombat(lua_State* L);
		int getPlayerObject(lua_State* L);
		int getFaction(lua_State* L);
		int setFaction(lua_State* L);
		int isImperial(lua_State* L);
		int isRebel(lua_State* L);
		int isNeutral(lua_State* L);
		int teleport(lua_State* L);
		int getName(lua_State* L);
		int isAiAgent(lua_State* L);
		int setFactionRank(lua_State* L);
		int getFactionRank(lua_State* L);
		int getCashCredits(lua_State* L);
		int subtractCashCredits(lua_State* L);
		int addCashCredits(lua_State* L);
		int removeScreenPlayState(lua_State* L);
		int isGrouped(lua_State* L);
		int getGroupSize(lua_State* L);
		int getGroupMember(lua_State* L);

	private:
		// The pointer to the 'real object' defined in object.cc
		Reference<CreatureObject*> realObject;
	};

}
}
}
}

using namespace server::zone::objects::creature;


#endif /* LUACREATUREOBJECT_H_ */
