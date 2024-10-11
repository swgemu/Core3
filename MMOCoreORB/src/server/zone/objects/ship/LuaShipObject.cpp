#include "LuaShipObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/intangible/tasks/StoreShipTask.h"
#include "server/zone/objects/ship/events/DestroyShipTask.h"

const char LuaShipObject::className[] = "LuaShipObject";

Luna<LuaShipObject>::RegType LuaShipObject::Register[] = {
	{ "_setObject", &LuaShipObject::_setObject },
	{ "_getObject", &LuaSceneObject::_getObject },
	{ "getControlDeviceID", &LuaShipObject::getControlDeviceID },
	{ "storeShip", &LuaShipObject::storeShip },
	{ "getTotalShipDamage", &LuaShipObject::getTotalShipDamage },
	{ "repairShip", &LuaShipObject::repairShip },
	{ "getPilot", &LuaShipObject::getPilot },
	{ "getPilotID", &LuaShipObject::getPilotID },
	{ "getOwner", &LuaShipObject::getOwner },
	{ "getOwnerID", &LuaShipObject::getOwnerID },
	{ "scheduleDestroyShipTask", &LuaShipObject::scheduleDestroyShipTask },
	{ "ejectPassenger", &LuaShipObject::ejectPassenger },
	{ "canBePilotedBy", &LuaShipObject::canBePilotedBy },
	{ 0, 0}
};

LuaShipObject::LuaShipObject(lua_State *L) : LuaTangibleObject(L) {
#ifdef DYNAMIC_CAST_LUAOBJECTS
	realObject = dynamic_cast<ShipObject*>(_getRealSceneObject());
	assert(!_getRealSceneObject() || realObject != nullptr);
#else
	realObject = static_cast<ShipObject*>(lua_touserdata(L, 1));
#endif
}

LuaShipObject::~LuaShipObject(){
}

int LuaShipObject::_setObject(lua_State* L) {
	LuaTangibleObject::_setObject(L);

#ifdef DYNAMIC_CAST_LUAOBJECTS
	auto obj = dynamic_cast<ShipObject*>(_getRealSceneObject());

	if (obj != realObject)
		realObject = obj;

	assert(!_getRealSceneObject() || realObject != nullptr);
#else
	auto obj = static_cast<ShipObject*>(lua_touserdata(L, -1));

	if (realObject != obj)
		realObject = obj;
#endif

	return 0;
}

int LuaShipObject::getControlDeviceID(lua_State* L) {
	lua_pushinteger(L, realObject->getControlDeviceID());
	return 1;
}

int LuaShipObject::storeShip(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 5) {
		realObject->error() << "Improper number of arguments in LuaShipObject::storeShip.";
		return 0;
	}

	float y = lua_tonumber(L, -1);
	float z =  lua_tonumber(L, -2);
	float x = lua_tonumber(L, -3);
	String zoneName =  lua_tostring(L, -4);
	CreatureObject* player = (CreatureObject*) lua_touserdata(L, -5);

	if (player == nullptr)
		return 0;

	ZoneServer* zoneServer = player->getZoneServer();

	if (zoneServer == nullptr)
		return 0;

	ManagedReference<SceneObject*> device = zoneServer->getObject(realObject->getControlDeviceID());

	if (device == nullptr || !device->isShipControlDevice())
		return 0;

	ShipControlDevice* shipControlDevice = device.castTo<ShipControlDevice*>();

	if (shipControlDevice == nullptr)
		return 0;

	Vector3 coordinates(x, y, z);

	StoreShipTask* task = new StoreShipTask(player, shipControlDevice, zoneName, coordinates);

	if (task != nullptr)
		task->schedule(500);

	return 0;
}

int LuaShipObject::getTotalShipDamage(lua_State* L) {
	Locker lock(realObject);

	float totalDamage = realObject->getTotalShipDamage();

	lua_pushnumber(L, totalDamage);
	return 1;
}

int LuaShipObject::repairShip(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 3 && numberOfArguments != 4) {
		realObject->error() << "Improper number of arguments in LuaShipObject::repairShip.";
		return 0;
	}

	bool decay = true;
	int totalCost = 0;
	float repairPercent = 0.f;
	CreatureObject* player = nullptr;

	if (numberOfArguments == 4) {
		decay = lua_toboolean(L, -1);
		totalCost = lua_tointeger(L, -2);
		repairPercent = lua_tonumber(L, -3);
		player = (CreatureObject*) lua_touserdata(L, -4);
	} else {
		totalCost = lua_tointeger(L, -1);
		repairPercent = lua_tonumber(L, -2);
		player = (CreatureObject*) lua_touserdata(L, -3);
	}

	if (player == nullptr)
		return 0;

	// Lock the ship
	Locker lock(realObject);

	realObject->repairShip(repairPercent, decay);

	Locker clock(player, realObject);

	TransactionLog logCash(player, realObject, TrxCode::SHIPPINGSYSTEM, totalCost, true);

	// Deduct cost from player
	player->subtractCashCredits(totalCost);

	return 0;
}

int LuaShipObject::getPilot(lua_State* L) {
	auto pilot = realObject->getPilot();

	if (pilot == nullptr) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, pilot);
	}

	return 1;
}

int LuaShipObject::getPilotID(lua_State* L) {
	auto pilot = realObject->getPilot();
	uint64 pilotID = 0;

	if (pilot != nullptr)
		pilotID = pilot->getObjectID();

	lua_pushinteger(L, pilotID);

	return 1;
}

int LuaShipObject::getOwner(lua_State* L) {
	auto owner = realObject->getOwner().get();

	if (owner == nullptr) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, owner);
	}

	return 1;
}

int LuaShipObject::getOwnerID(lua_State* L) {
	uint64 ownerID = realObject->getOwnerID();

	lua_pushinteger(L, ownerID);

	return 1;
}

int LuaShipObject::scheduleDestroyShipTask(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	int delay = 4000;

	if (numberOfArguments > 1) {
		delay = lua_tointeger(L, -1);
	}

	auto destroyTask = new DestroyShipTask(realObject);

	if (destroyTask == nullptr) {
		return 0;
	}

	destroyTask->schedule(delay);

	return 0;
}

int LuaShipObject::ejectPassenger(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 2) {
		realObject->error() << "Improper number of arguments in LuaShipObject::ejectPassenger.";
		return 0;
	}

	Reference<CreatureObject*> playerRef = (CreatureObject*) lua_touserdata(L, -2);
	Reference<ShipObject*> shipRef = realObject;
	int delay = lua_tointeger(L, -1);

	if (playerRef == nullptr) {
		return 0;
	}

	Core::getTaskManager()->scheduleTask([shipRef, playerRef] () {
		if (playerRef == nullptr || shipRef == nullptr) {
			return;
		}

		Locker lock(shipRef);

		const auto launchZone = shipRef->getSpaceLaunchZone();
		const auto launchLoc = shipRef->getSpaceLaunchLocation();

		Locker clock(playerRef, playerRef);

		// Remove the player from the onboard list
		shipRef->removePlayerOnBoard(playerRef);

		// Send the player to the launch location
		playerRef->switchZone(launchZone, launchLoc.getX(), launchLoc.getZ(), launchLoc.getY(), 0, false, -1);
	}, "EjectPassengerLambda", delay);

	return 0;
}

int LuaShipObject::canBePilotedBy(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 1) {
		realObject->error() << "Improper number of arguments in LuaShipObject::canBePilotedBy.";
		return 0;
	}

	CreatureObject* player = (CreatureObject*)lua_touserdata(L, -1);
	bool canPilot = true;

	if (player != nullptr) {
		canPilot = realObject->canBePilotedBy(player);
	}

	lua_pushboolean(L, canPilot);

	return 1;
}
