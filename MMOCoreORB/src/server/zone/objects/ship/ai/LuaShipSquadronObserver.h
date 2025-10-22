/*
 * LuaShipSquadronObserver.h
 *
 *  Created on: 2024/10/30
 *  Author: Hakry
 */


/*
#ifndef LUASHIPSQUADRONOBSERVER_H_
#define LUASHIPSQUADRONOBSERVER_H_

#include "engine/engine.h"

#include "engine/util/Observer.h"
#include "server/zone/objects/scene/LuaSceneObject.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
class SquadronObserver;

class LuaShipSquadronObserver : public Observer {
public:
	// Constants
	static const char className[];
	static Luna<LuaShipSquadronObserver>::RegType Register[];

	// Initialize the pointer
	LuaShipSquadronObserver(lua_State* L);
	~LuaShipSquadronObserver();

	int _setObject(lua_State* L);


private:
	SquadronObserver* realObject;
};
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship::ai;
*/
#endif /* LUASHIPSQUADRONOBSERVER_H_ */
