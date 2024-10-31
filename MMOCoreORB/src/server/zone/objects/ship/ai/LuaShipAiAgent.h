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
