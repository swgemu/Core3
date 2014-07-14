/*
 * LuaAiAgent.h
 *
 *  Created on: 21/01/2012
 *      Author: victor
 */

#ifndef LUAAIAGENT_H_
#define LUAAIAGENT_H_


#include "engine/engine.h"

#include "server/zone/objects/creature/LuaCreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class AiAgent;

	class LuaAiAgent : public LuaCreatureObject {
	public:
		// Constants
		static const char className[];
		static Luna<LuaAiAgent>::RegType Register[];

		// Initialize the pointer
		LuaAiAgent(lua_State *L);
		~LuaAiAgent();

		int _setObject(lua_State* L);
		int _getObject(lua_State* L);
		int setAiTemplate(lua_State* L);
		int setFollowObject(lua_State* L);
		int setOblivious(lua_State* L);
		int setWatchObject(lua_State* L);
		int setStalkObject(lua_State* L);
		int getFollowObject(lua_State* L);
		int getFollowState(lua_State* L);
		int findNextPosition(lua_State* L);
		int getMaxDistance(lua_State* L);
		int generatePatrol(lua_State* L);
		int setDestination(lua_State* L);
		int completeMove(lua_State* L);
		int setWait(lua_State* L);
		int getWait(lua_State* L);
		int isWaiting(lua_State* L);
		int stopWaiting(lua_State* L);
		int getCurrentSpeed(lua_State* L);
		int setCurrentSpeed(lua_State* L);
		int getTargetFromMap(lua_State* L);
		int getTargetFromDefenders(lua_State* L);
		int validateTarget(lua_State* L);
		int followHasState(lua_State* L);
		int selectWeapon(lua_State* L);
		int selectDefaultWeapon(lua_State* L);
		int selectSpecialAttack(lua_State* L);
		int selectDefaultAttack(lua_State* L);
		int validateStateAttack(lua_State* L);
		int removeDefender(lua_State* L);
		int removeDefenders(lua_State* L);
		int enqueueAttack(lua_State* L);
		int isRetreating(lua_State* L);
		int isFleeing(lua_State* L);
		int isAggressiveTo(lua_State* L);
		int isAttackableBy(lua_State* L);
		int isScentMasked(lua_State* L);
		int isConcealed(lua_State* L);
		int clearCombatState(lua_State* L);
		int activateRecovery(lua_State* L);
		int setBehaviorStatus(lua_State* L);
		int getBehaviorStatus(lua_State* L);
		int resetBehaviorList(lua_State* L);
		int executeBehavior(lua_State* L);
		int info(lua_State* L);
		int spatialChat(lua_State* L);
		int setDefender(lua_State* L);
		int addDefender(lua_State* L);
		int assist(lua_State* L);
		int checkRange(lua_State* L);
		int broadcastInterrupt(lua_State* L);
		int getSocialGroup(lua_State* L);
		int getOwner(lua_State* L);
	private:
		ManagedReference<AiAgent*> realObject;
	};
}
}
}
}

using namespace server::zone::objects::creature;
#endif /* LUAAIAGENT_H_ */
