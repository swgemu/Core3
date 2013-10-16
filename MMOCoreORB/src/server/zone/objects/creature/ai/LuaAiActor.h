/*
 * LuaAiActor.h
 *
 *  Created on: Sep 1, 2013
 *      Author: swgemu
 */

#ifndef LUAAIACTOR_H_
#define LUAAIACTOR_H_

#include "server/zone/objects/creature/ai/AiActor.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
	class AiActor;

	class LuaAiActor {
	public:
		static const char className[];
		static Luna<LuaAiActor>::RegType Register[];

		LuaAiActor(lua_State *L);
		virtual ~LuaAiActor();

		int _setObject(lua_State* L);
		int _getObject(lua_State *L);
		int doAwarenessCheck(lua_State *L);
		int getNpcTemplate(lua_State *L);
		int setLevel(lua_State *L);
		int isCamouflaged(lua_State *L);
		int isScentMasked(lua_State *L);
		int isConcealed(lua_State *L);
		int activateRecovery(lua_State *L);
		int activateMovementEvent(lua_State *L);
		int activateAwarenessEvent(lua_State *L);
		int activatePostureRecovery(lua_State *L);
		int queueDizzyFallEvent(lua_State *L);
		int setNextPosition(lua_State *L);
		int setNextStepPosition(lua_State *L);
		int getNextStepPosition(lua_State *L);
		int setShowNextPosition(lua_State *L);
		int isShowNextPosition(lua_State *L);
		int getMovementMarkers(lua_State *L);
		int getMovementMarkersSize(lua_State *L);
		int getMovementMarker(lua_State *L);
		int dropMovementMarker(lua_State *L);
		int dropAllMovemementMarkers(lua_State *L);
		int addMovementMarker(lua_State *L);
		int clearPatrolPoints(lua_State *L);
		int getPatrolPoints(lua_State *L);
		int addPatrolPoint(lua_State *L);
		int setHomeLocation(lua_State *L);
		int getHomeLocation(lua_State *L);
		int getNumberOfPlayersInRange(lua_State *L);
		int getFollowObject(lua_State *L);
		int setFollowObject(lua_State *L);
		int setTargetObject(lua_State *L);
		int setOblivious(lua_State *L);
		int setDefender(lua_State *L);
		int addDefender(lua_State *L);
		int removeDefender(lua_State *L);
		int isAttackableBy(lua_State *L);
		int isAggressiveTo(lua_State *L);
		int getKinetic(lua_State *L);
		int getEnergy(lua_State *L);
		int getElectricity(lua_State *L);
		int getStun(lua_State *L);
		int getBlast(lua_State *L);
		int getHeat(lua_State *L);
		int getCold(lua_State *L);
		int getAcid(lua_State *L);
		int getLightSaber(lua_State *L);
		int isStalker(lua_State *L);
		int isKiller(lua_State *L);
		int getFerocity(lua_State *L);
		int getArmor(lua_State *L);
		int getFactionString(lua_State *L);
		int getSocialGroup(lua_State *L);
		int getChanceHit(lua_State *L);
		int getDamageMin(lua_State *L);
		int getDamageMax(lua_State *L);
		int getBaseXp(lua_State *L);
		int getDiet(lua_State *L);
		int getAttackMap(lua_State *L);
		int getCreatureTemplate(lua_State *L);
		Reference<AiActor*> realObject;
	};

}
}
}
}
}

using namespace server::zone::objects::creature::ai;

#endif /* LUAAIACTOR_H_ */
