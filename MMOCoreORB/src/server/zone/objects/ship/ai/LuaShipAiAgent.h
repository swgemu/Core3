/*
 * LuaShipAiAgent.h
 *
 *  Created on: 2024/10/30
 *  Author: Hakry
 */

#ifndef LUASHIPAIAGENT_H_
#define LUASHIPAIAGENT_H_

#include "engine/engine.h"

#include "server/zone/objects/ship/LuaShipObject.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
class ShipAiAgent;

class LuaShipAiAgent : public LuaShipObject {
public:
	// Constants
	static const char className[];
	static Luna<LuaShipAiAgent>::RegType Register[];

	// Initialize the pointer
	LuaShipAiAgent(lua_State* L);
	~LuaShipAiAgent();

	int _setObject(lua_State* L);
	int setShipAiTemplate(lua_State* L);
	int setGuardPatrol(lua_State* L);
	int setRandomPatrol(lua_State* L);
	int setFixedPatrol(lua_State* L);
	int setSquadronPatrol(lua_State* L);
	int setSquadronFollow(lua_State* L);
	int setEscort(lua_State* L);
	int setWaveAttack(lua_State* L);
	int setDespawnOnNoPlayerInRange(lua_State* L);
	int setMinimumGuardPatrol(lua_State* L);
	int setMaximumGuardPatrol(lua_State* L);
	int addFixedPatrolPoint(lua_State* L);
	int assignFixedPatrolPointsTable(lua_State* L);
	int setDefender(lua_State* L);
	int getShipAgentTemplateName(lua_State* L);
	int tauntPlayer(lua_State* L);
	int addAggro(lua_State* L);
	int engageShipTarget(lua_State* L);
	int addSpaceFactionAlly(lua_State* L);
	int removeSpaceFactionAlly(lua_State* L);
	int addSpaceFactionEnemy(lua_State* L);
	int removeSpaceFactionEnemy(lua_State* L);
	int setEscortSpeed(lua_State* L);
	int setMissionOwner(lua_State* L);
	int getMissionOwnerID(lua_State* L);
	int repairShipAgent(lua_State* L);
	int removeEnemyShip(lua_State* L);
	int setConversationMobile(lua_State* L);
	int swapSpaceFactionAssociations(lua_State* L);
	int clearPatrolPoints(lua_State* L);

private:
	ShipAiAgent* realObject;
};
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship::ai;

#endif /* LUASHIPAIAGENT_H_ */
