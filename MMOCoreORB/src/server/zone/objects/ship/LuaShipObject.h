#ifndef LUASHIPOBJECT_H_
#define LUASHIPOBJECT_H_

#include "engine/engine.h"
#include "server/zone/objects/tangible/LuaTangibleObject.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {

	class ShipObject;

	class LuaShipObject : public LuaTangibleObject {
	public:
		//Constants
		static const char className[];
		static Luna<LuaShipObject>::RegType Register[];

		//Initialize the pointer
		LuaShipObject(lua_State *L);
		~LuaShipObject();

		int _setObject(lua_State* L);
		int getControlDeviceID(lua_State* L);
		int storeShip(lua_State* L);
		int getTotalShipDamage(lua_State* L);
		int repairShip(lua_State* L);
		int getPilot(lua_State* L);
		int getPilotID(lua_State* L);
		int getOwner(lua_State* L);
		int getOwnerID(lua_State* L);
		int scheduleDestroyShipTask(lua_State* L);
		int ejectPassenger(lua_State* L);
		int canBePilotedBy(lua_State* L);
		int hasUpperTurret(lua_State* L);
		int hasLowerTurret(lua_State* L);
		int isUpperTurretFunctional(lua_State* L);
		int isLowerTurretFunctional(lua_State* L);
		int getShipName(lua_State* L);
		int setHyperspacing(lua_State* L);
		int setShipFactionString(lua_State* L);

	private:
		ShipObject* realObject;
	};

}
}
}
}

using namespace server::zone::objects::ship;

#endif /*LUASHIPOBJECT_H_ */