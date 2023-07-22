//
// Created by g on 12/15/17.
//

#include "server/zone/SpaceZone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/space/SpaceManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "conf/ConfigManager.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "templates/faction/Factions.h"

void SpaceManagerImplementation::loadLuaConfig() {
	String planetName = spacezone->getZoneName();

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/space_manager.lua");

	// Get's the configuration settings object for this planet.
	LuaObject base = lua->getGlobalObject(planetName);

	if (base.isValidTable()) {
		LuaObject luaObject = base.getObjectField("zoneObjects");
		if (!luaObject.isValidTable())
			return;

		for (int i = 1; i <= luaObject.getTableSize(); ++i) {
			lua_State* L = luaObject.getLuaState();
			lua_rawgeti(L, -1, i);

			LuaObject zoneObject(L);

			String templateFile = zoneObject.getStringField("templateFile");
			//  info("Attempting to load: " + templateFile + " in " + spacezone->getZoneName(), true);

			auto shot = TemplateManager::instance()->getTemplate(templateFile.hashCode());
			if (shot == nullptr) {
				zoneObject.pop();
				continue;
			}

			ManagedReference<SceneObject*> obj = nullptr;

			if (shot->getGameObjectType() & SceneObjectType::SHIP) {
				obj = ShipManager::instance()->createShip(templateFile, 0, true);
			} else {
				obj = ObjectManager::instance()->createObject(templateFile.hashCode(), 0, "");
			}

			if (obj != nullptr) {
				Locker objLocker(obj);

				float x = zoneObject.getFloatField("x");
				float y = zoneObject.getFloatField("y");
				float z = zoneObject.getFloatField("z");
				float ox = zoneObject.getFloatField("ox");
				float oy = zoneObject.getFloatField("oy");
				float oz = zoneObject.getFloatField("oz");
				float ow = zoneObject.getFloatField("ow");

				uint64 parentID = zoneObject.getLongField("parent");
				Quaternion direction(ow,ox,oy,oz);
				direction.normalize();

				obj->initializePosition(x, z, y);
				obj->setDirection(direction);

				ManagedReference<SceneObject*> parent = spacezone->getZoneServer()->getObject(parentID);

				if (parent != nullptr)
					parent->transferObject(obj, -1, true);
				else
					spacezone->transferObject(obj, -1, true);

				obj->createChildObjects();

				if (obj->isShipObject()) {
					auto ship = obj->asShipObject();

					if (ship != nullptr) {
						ship->setRotationMatrix(direction);

						if (ship->isSpaceStationObject()) {
							String faction = ship->getShipFaction();

							if (faction == "" || !spaceStationMap.contains(faction)) {
								faction = "neutral";

								ship->setFaction(Factions::FACTIONNEUTRAL);
								ship->setOptionBit(OptionBitmask::INVULNERABLE, false);
							}

							uint64 stationID = ship->getObjectID();
							Vector3 stationPosition = ship->getPosition();

							spaceStationMap.get(faction).put(stationID, stationPosition);
						}
					}
				}

				//   info("Object Added: " + obj->getObjectName() + ": " + String::valueOf(obj->getPositionX()) + " " + String::valueOf(obj->getPositionY()) + " " + String::valueOf(obj->getPositionZ()), true);
			}

			zoneObject.pop();
		}
		try {
			LuaObject travelPoints = luaObject.getObjectField("jtlTravelPoints");
			loadJTLData(&travelPoints);
			travelPoints.pop();

			LuaObject launchLocation = luaObject.getObjectField("jtlLaunchPoint");
			if (!launchLocation.isValidTable())
				return;

			jtlZoneName = launchLocation.getStringAt(1);
			float x = launchLocation.getFloatAt(2);
			float y = launchLocation.getFloatAt(3);
			float z = launchLocation.getFloatAt(4);
			jtlLaunchLocation = Vector3(x, y, z);
			launchLocation.pop();
		} catch (Exception &e) {
			error(e.getMessage());
		}
	} else {
		warning("Space configuration settings not found.");
	}
}

void SpaceManagerImplementation::initialize() {
	VectorMap<uint64, Vector3> stationMap;
	stationMap.setNoDuplicateInsertPlan();
	stationMap.setNullValue(Vector3::ZERO);

	spaceStationMap.put("rebel", stationMap);
	spaceStationMap.put("neutral", stationMap);
	spaceStationMap.put("imperial", stationMap);

	info("loading space manager " + spacezone->getZoneName(), true);
	loadLuaConfig();
}

void SpaceManagerImplementation::loadJTLData(LuaObject* luaObject) {
	if (!luaObject->isValidTable())
		return;
	//
	for (int i = 1; i <= luaObject->getTableSize(); ++i) {
		lua_State* L = luaObject->getLuaState();
		lua_rawgeti(L, -1, i);

		LuaObject location(L);

		String locationName = location.getStringAt(1);
		float x = location.getFloatAt(2);
		float y = location.getFloatAt(3);
		float z = location.getFloatAt(4);
		jtlTravelDestinations.put(locationName, Vector3(x, y, z));
		location.pop();
	}
}

void SpaceManagerImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();
}

void SpaceManagerImplementation::finalize() {
	spacezone = nullptr;
	server = nullptr;
}

void SpaceManagerImplementation::start() {
}

Vector3 SpaceManagerImplementation::getJtlLaunchLocationss() {
	return jtlLaunchLocation;
}

Vector3 SpaceManagerImplementation::getClosestSpaceStationPosition(const Vector3& shipPosition, const String& shipFaction) {
	uint64 objectID = getClosestSpaceStationObjectID(shipPosition, shipFaction);

	if (objectID == 0) {
		return shipPosition;
	}

	return spaceStationMap.get(shipFaction).get(objectID);
}

uint64 SpaceManagerImplementation::getClosestSpaceStationObjectID(const Vector3& shipPosition, const String& shipFaction) {
	uint64 stationObjectID = 0;
	float stationDistance = FLT_MAX;

	for (int i = 0; i < spaceStationMap.size(); ++i) {
		const auto& stationKey = spaceStationMap.elementAt(i).getKey();
		const auto& stationMap = spaceStationMap.elementAt(i).getValue();

		if (shipFaction != stationKey) {
			continue;
		}

		for (int ii = 0; ii < stationMap.size(); ++ii) {
			const auto& entryPosition = stationMap.elementAt(ii).getValue();
			float sqrDistance = shipPosition.squaredDistanceTo(entryPosition);

			if (stationDistance > sqrDistance) {
				stationDistance = sqrDistance;
				stationObjectID = stationMap.elementAt(ii).getKey();
			}
		}
	}

	return stationObjectID;
}
