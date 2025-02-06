/*
 *	PlanetManagerImplementation.cpp
 *
 *	Created on: 12/15/17
 *	Author: g
 */

#include "server/zone/managers/space/SpaceManager.h"

#include "server/zone/SpaceZone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "conf/ConfigManager.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/area/space/SpaceActiveArea.h"
#include "server/zone/objects/area/areashapes/SphereAreaShape.h"
#include "server/zone/objects/area/areashapes/CuboidAreaShape.h"
#include "server/zone/objects/area/space/NebulaArea.h"
#include "server/zone/objects/region/space/SpaceRegion.h"
#include "server/zone/packets/jtl/CreateNebulaLightningMessage.h"
#include "server/zone/objects/region/space/SpaceSpawnArea.h"
#include "server/zone/managers/ship/SpaceSpawn.h"
#include "server/zone/objects/tangible/space/content_infrastructure/SpaceSpawner.h"

// #define DEBUG_SPACE_REGIONS

void SpaceManagerImplementation::initialize() {
	String spaceZoneName = spaceZone->getZoneName();

	VectorMap<uint64, Vector3> stationMap;
	stationMap.setNoDuplicateInsertPlan();
	stationMap.setNullValue(Vector3::ZERO);

	spaceStationMap.put(STRING_HASHCODE("rebel"), stationMap);
	spaceStationMap.put(STRING_HASHCODE("station"), stationMap);
	spaceStationMap.put(STRING_HASHCODE("stationDeepSpace"), stationMap);
	spaceStationMap.put(STRING_HASHCODE("imperial"), stationMap);

	info(true) << "loading space manager " << spaceZoneName;

	// Load Space Regions
	loadRegions();

	// Load Nebulas
	loadNebulaAreas();

	// Load Space Lua Config
	loadLuaConfig();
}

void SpaceManagerImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();
}

void SpaceManagerImplementation::start() {
}

void SpaceManagerImplementation::finalize() {
	spaceZone = nullptr;
	server = nullptr;
}

void SpaceManagerImplementation::loadRegions() {
	Lua* lua = new Lua();
	lua->init();

	String spaceZoneName = spaceZone->getZoneName();

#ifdef DEBUG_SPACE_REGIONS
	info(true) << "Reading from regions file: " << " scripts/managers/space/regions/" << spaceZoneName << "_regions.lua";
#endif // DEBUG_SPACE_REGIONS

	lua->runFile("scripts/managers/space/regions/" + spaceZoneName + "_regions.lua");
	LuaObject regionObjects = lua->getGlobalObject(spaceZoneName + "_regions");

	lua_State* s = regionObjects.getLuaState();

	for (int i = 1; i <= regionObjects.getTableSize(); ++i) {
		lua_rawgeti(s, -1, i);
		LuaObject regionObject(s);

		if (regionObject.isValidTable()) {
			readRegionObject(regionObject);
		}

		regionObject.pop();
	}

	regionObjects.pop();

	delete lua;
	lua = nullptr;

	info(true) << "Loaded " << regionMap.getTotalRegions() << " total regions.";
}

void SpaceManagerImplementation::readRegionObject(LuaObject& regionObject) {
	String name = regionObject.getStringAt(1);
	float x = regionObject.getFloatAt(2);
	float z = regionObject.getFloatAt(3);
	float y = regionObject.getFloatAt(4);

#ifdef DEBUG_SPACE_REGIONS
	info(true) << "readSpaceRegion -- Name: " << name << " x = " << x << " z = " << z << " y = " << y;
#endif // DEBUG_SPACE_REGIONS

	int type = regionObject.getIntAt(6);

	// For SPHERE
	float radius = 0;

	// For CUBOID
	float length = 0;
	float width = 0;
	float height = 0;

	LuaObject areaShapeObject = regionObject.getObjectAt(5);

	if (!areaShapeObject.isValidTable()) {
		error("Invalid area shape table for spawn region " + name);
		return;
	}

	int regionShape = areaShapeObject.getIntAt(1);

	if (regionShape == SpaceActiveArea::SPHERE) {
		radius = areaShapeObject.getFloatAt(2);

		if (radius < 256) {
			error() << "Invalid SPHERE Region Radius for Space Region: " << name << " Radius = " << radius;
			return;
		}
	} else if (regionShape == SpaceActiveArea::CUBOID) {
		length = areaShapeObject.getFloatAt(2);
		width = areaShapeObject.getFloatAt(3);
		height = areaShapeObject.getFloatAt(4);

		if (length < 256 || width < 256 || height < 256) {
			error() << "Invalid CUBOID Region Dimension for Space Region: " << name << " Length = " << length << " Width = " << width << " Height = " << height;
			return;
		}
	} else {
		error() << "Invalid Region Shape: " << regionShape << " for Space Region " << name;
		return;
	}

	areaShapeObject.pop();

	ManagedReference<SpaceRegion*> spaceRegion = nullptr;
	bool spawnAreaRegion = (type & ActiveArea::SPAWNAREA);

	if (spawnAreaRegion) {
		spaceRegion = dynamic_cast<SpaceRegion*>(ObjectManager::instance()->createObject(STRING_HASHCODE("object/space_spawn_area.iff"), 0, "spawnareas"));
#ifdef DEBUG_SPACE_REGIONS
		info(true) << "\n\n\n\n ~~~ Creating space_spawn_area object ~~~ ";
#endif // DEBUG_SPACE_REGIONS
	} else {
		spaceRegion = dynamic_cast<SpaceRegion*>(ObjectManager::instance()->createObject(STRING_HASHCODE("object/space_region_area.iff"), 0, "regions"));
#ifdef DEBUG_SPACE_REGIONS
		info(true) << " --- Creating region_area object --- ";
#endif // DEBUG_SPACE_REGIONS
	}

	if (spaceRegion == nullptr) {
		return;
	}

	Locker lock(spaceRegion);

	spaceRegion->setObjectName(name, false);
	spaceRegion->setAreaName(name);

	if (regionShape == SpaceActiveArea::SPHERE) {
		ManagedReference<SphereAreaShape*> sphereAreaShape = new SphereAreaShape();

		// Lock the shape for mutation
		Locker shapeLocker(sphereAreaShape, spaceRegion);

		sphereAreaShape->setAreaCenter(x, z, y);
		sphereAreaShape->setRadius(radius);

		spaceRegion->setAreaShape(sphereAreaShape);
	} else if (regionShape == SpaceActiveArea::CUBOID) {
		ManagedReference<CuboidAreaShape*> cuboidAreaShape = new CuboidAreaShape();

		// Lock the shape for mutation
		Locker shapeLocker(cuboidAreaShape, spaceRegion);

		cuboidAreaShape->setAreaCenter(x, z, y);
		cuboidAreaShape->setDimensions(length, width, height);

		spaceRegion->setAreaShape(cuboidAreaShape);
	}

	// Assign the type flags to the region
	spaceRegion->setRegionFlags(type);

	// Initialize the position of the region
	spaceRegion->initializePosition(x, z, y);

	// Transfer it into the zone
	spaceZone->transferObject(spaceRegion, -1, true);

	if (spawnAreaRegion) {
#ifdef DEBUG_SPACE_REGIONS
		info(true) << "Adding Spawn Area";
#endif // DEBUG_SPACE_REGIONS

		ManagedReference<SpaceSpawnArea*> spawnArea = spaceRegion.castTo<SpaceSpawnArea*>();

		if (spawnArea != nullptr) {
			// Set the max spawn limit
			spawnArea->setMaxSpawnLimit(regionObject.getIntAt(8));

			LuaObject spawnGroups = regionObject.getObjectAt(7);

			if (spawnGroups.isValidTable()) {
				Vector<uint32> groups;

				for (int i = 1; i <= spawnGroups.getTableSize(); i++) {
					uint32 groupHash = spawnGroups.getStringAt(i).hashCode();

#ifdef DEBUG_SPACE_REGIONS
					info(true) << "Adding Space Spawn Group: #" << i << " Name: " << spawnGroups.getStringAt(i);
#endif // DEBUG_SPACE_REGIONS

					groups.add(spawnGroups.getStringAt(i).hashCode());
				}

				spawnArea->buildSpawnList(&groups);

				spawnGroups.pop();
			}
		}
	}

	// Add region to the map
	regionMap.addRegion(spaceRegion);

#ifdef DEBUG_SPACE_REGIONS
	info(true) << "FINISHED Loading Space Region -- Name: " << name;
#endif // DEBUG_SPACE_REGIONS
}

void SpaceManagerImplementation::loadNebulaAreas() {
	auto zoneServer = spaceZone->getZoneServer();

	if (zoneServer == nullptr)
		return;

	TemplateManager* templateManager = TemplateManager::instance();

	if (templateManager == nullptr)
		return;

	String zoneName = spaceZone->getZoneName();

	// No Nebulas in space_heavy1
	if (zoneName == "space_heavy1")
		return;

	IffStream* iffStream = templateManager->openIffFile("datatables/space/nebula/" + zoneName + ".iff");

	if (iffStream == nullptr) {
		warning() << "Nebula table for " << zoneName << " could not be found.";
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	// Declare variables
	String name, ambientSound, lightningAppearance, lightningSound, lightningSoundLoop, lightningHitEffectClient, lightningHitEffectServer;
	float x, z, y, radius, density, lightningDamageMin, lightningDamageMax, lightningFrequency, lightningDurationMax;
	StringBuffer nebulaName;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		row->getCell(0)->getValue(name);
		row->getCell(1)->getValue(x);
		row->getCell(2)->getValue(z);
		row->getCell(3)->getValue(y);
		row->getCell(4)->getValue(radius);
		row->getCell(5)->getValue(density);

		row->getCell(23)->getValue(ambientSound);
		row->getCell(29)->getValue(lightningFrequency);
		row->getCell(30)->getValue(lightningDurationMax);
		row->getCell(31)->getValue(lightningDamageMin);
		row->getCell(32)->getValue(lightningDamageMax);
		row->getCell(33)->getValue(lightningAppearance);
		row->getCell(42)->getValue(lightningSound);
		row->getCell(43)->getValue(lightningSoundLoop);
		row->getCell(44)->getValue(lightningHitEffectClient);
		row->getCell(45)->getValue(lightningHitEffectServer);

		// Create new nebula area
		ManagedReference<NebulaArea*> nebulaArea = (zoneServer->createObject(STRING_HASHCODE("object/nebula_area.iff"), 0)).castTo<NebulaArea*>();

		if (nebulaArea == nullptr)
			continue;

		Locker areaLock(nebulaArea);

		// Create sphere active area shape
		ManagedReference<SphereAreaShape*> sphereArea = new SphereAreaShape();

		if (sphereArea == nullptr)
			continue;

		Locker shapeLocker(sphereArea, nebulaArea);

		sphereArea->setAreaCenter(x, z, y);
		sphereArea->setRadius(radius);

		shapeLocker.release();

		nebulaName << zoneName << "_nebula_" << name;
		nebulaArea->setAreaName(nebulaName.toString());
		nebulaName.deleteAll();

		nebulaArea->setAreaShape(sphereArea);

		nebulaArea->setNebulaDensity(density);
		nebulaArea->setAmbientSound(ambientSound);
		nebulaArea->setLightningFrequency(lightningFrequency);
		nebulaArea->setLightningDurationMax(lightningDurationMax);
		nebulaArea->setLightningDamageMin(lightningDamageMin);
		nebulaArea->setLightningDamageMax(lightningDamageMax);
		nebulaArea->setLightningAppearance(lightningAppearance);
		nebulaArea->setLightningSound(lightningSound);
		nebulaArea->setLightningSoundLoop(lightningSoundLoop);
		nebulaArea->setLightningHitEffectClient(lightningHitEffectClient);
		nebulaArea->setLightningHitEffectServer(lightningHitEffectServer);

		nebulaArea->setNebulaID(i + 1);
		nebulaArea->setRadius(radius);

		/*
		StringBuffer debugMsg;
		debugMsg << zoneName << "_nebula_" << name << " - X = " << x << " Z = " << z << " Y = " << y << " Radius = " << radius;
		debugMsg << "Ambient Sound: " << ambientSound << " Lightning Frequencey: " << lightningFrequency << " lightningDurationMax: " << lightningDurationMax;
		debugMsg << " Lightning Damage Min: " << lightningDamageMin << " Lightning Damage Max: " << lightningDamageMax << " Lightning Appearance: " << lightningAppearance;
		debugMsg << " Lightning Sound: " << lightningSound << " Lightning Sound Loop: " << lightningSoundLoop << " Lightning Hit Effect Client: " << lightningHitEffectClient << " Lightning Hit Effect Server: " << lightningHitEffectServer;
		info(true) << debugMsg.toString();
		*/

		// Initialize nebula position
		nebulaArea->initializePosition(x, z, y);

		spaceZone->transferObject(nebulaArea, -1, true);
	}

	delete iffStream;
}

void SpaceManagerImplementation::loadLuaConfig() {
	String spaceZoneName = spaceZone->getZoneName();

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/space/space_manager.lua");

	// Get's the configuration settings object for this planet.
	LuaObject base = lua->getGlobalObject(spaceZoneName);

	if (base.isValidTable()) {
		LuaObject luaObject = base.getObjectField("spaceStations");

		if (!luaObject.isValidTable())
			return;

		for (int i = 1; i <= luaObject.getTableSize(); ++i) {
			lua_State* L = luaObject.getLuaState();
			lua_rawgeti(L, -1, i);

			LuaObject stationObject(L);

			String templateFile = stationObject.getStringField("templateFile");

			ManagedReference<ShipAiAgent*> shipAgent = ShipManager::instance()->createAiShip(templateFile);

			if (shipAgent == nullptr)
				continue;

			Locker shipLocker(shipAgent);

			float x = stationObject.getFloatField("x");
			float y = stationObject.getFloatField("y");
			float z = stationObject.getFloatField("z");
			float ox = stationObject.getFloatField("ox");
			float oy = stationObject.getFloatField("oy");
			float oz = stationObject.getFloatField("oz");
			float ow = stationObject.getFloatField("ow");

			uint64 parentID = stationObject.getLongField("parent");

			Quaternion direction(ow, ox, oy, oz);
			direction.normalize();

			shipAgent->initializePosition(x, z, y);
			shipAgent->setDirection(direction);
			shipAgent->initializeTransform(Vector3(x,y,z), direction);

			// Transfer into the zone
			spaceZone->transferObject(shipAgent, -1, true);

			shipAgent->createChildObjects();

			uint32 factionHash = shipAgent->getShipFaction();
			uint64 stationID = shipAgent->getObjectID();
			Vector3 stationPosition = shipAgent->getPosition();

			spaceStationMap.get(factionHash).put(stationID, stationPosition);

			// info(true) << "SpaceStation Added: " << shipAgent->getDisplayedName() << " Location: " + shipAgent->getPosition().toString();

			stationObject.pop();
		}

		try {
			LuaObject launchLocation = luaObject.getObjectField("jtlLaunchPoint");
			loadJTLData(&launchLocation);
			launchLocation.pop();
		} catch (Exception& e) {
			error(e.getMessage());
		}
	} else {
		warning("Space configuration settings not found.");
	}
}

void SpaceManagerImplementation::loadJTLData(LuaObject* launchLocation) {
	if (launchLocation == nullptr || !launchLocation->isValidTable()) {
		return;
	}

	jtlZoneName = launchLocation->getStringAt(1);

	float x = launchLocation->getFloatAt(2);
	float z = launchLocation->getFloatAt(3);
	float y = launchLocation->getFloatAt(4);

	jtlLaunchLocation = Vector3(x, y, z);
}

Vector3 SpaceManagerImplementation::getJtlLaunchLocationss() {
	return jtlLaunchLocation;
}

Vector3 SpaceManagerImplementation::getClosestSpaceStationPosition(const Vector3& shipPosition, const String& shipFaction) {
	uint64 objectID = getClosestSpaceStationObjectID(shipPosition, shipFaction.hashCode());

	if (objectID == 0) {
		return shipPosition;
	}

	return spaceStationMap.get(shipFaction.hashCode()).get(objectID);
}

uint64 SpaceManagerImplementation::getClosestSpaceStationObjectID(const Vector3& shipPosition, const uint32 factionHash) {
	uint64 stationObjectID = 0;
	float stationDistance = FLT_MAX;

	for (int i = 0; i < spaceStationMap.size(); ++i) {
		const auto& stationKey = spaceStationMap.elementAt(i).getKey();
		const auto& stationMap = spaceStationMap.elementAt(i).getValue();

		if (factionHash != stationKey) {
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

void SpaceManagerImplementation::broadcastNebulaLightning(ShipObject* ship, const Vector3& nebulaCenter, uint16 lightningCount, int nebulaID, int startMili, int endMili, const Vector3& startPoint, const Vector3& endPoint) {
	if (ship == nullptr)
		return;

	CloseObjectsVector* closeObjects = ship->getCloseObjects();
	SortedVector<ManagedReference<TreeEntry*>> closeObjectsCopy(200, 50);

	if (closeObjects != nullptr) {
		closeObjects->safeCopyReceiversTo(closeObjectsCopy, CloseObjectsVector::PLAYERTYPE);
	} else {
		spaceZone->getInRangeObjects(nebulaCenter.getX(), nebulaCenter.getZ(), nebulaCenter.getY(), spaceZone->getZoneObjectRange(), &closeObjectsCopy, true);
	}

	try {
		for (int i = 0; i < closeObjectsCopy.size(); ++i) {
			auto playerEntry = static_cast<SceneObject*>(closeObjectsCopy.getUnsafe(i).get());

			if (playerEntry == nullptr || !playerEntry->isPlayerCreature()) {
				continue;
			}

			uint32 syncStamp = playerEntry->getSyncStamp();

			auto lightningMessage = new CreateNebulaLightningMessage(lightningCount, nebulaID, startMili + syncStamp, endMili + syncStamp, startPoint, endPoint);
			playerEntry->sendMessage(lightningMessage);
		}
	} catch (...) {
		throw;
	}
}

SceneObject* SpaceManagerImplementation::spaceDynamicSpawn(uint32 shipCRC, Zone* zone, SpaceSpawner* spaceSpawner) {
	if (spaceSpawner == nullptr) {
		return nullptr;
	}

	auto shipManager = ShipManager::instance();

	if (shipManager == nullptr) {
		return nullptr;
	}

	ManagedReference<ShipAiAgent*> shipAgent = shipManager->createAiShip("", shipCRC);

	if (shipAgent == nullptr) {
		return nullptr;
	}

	Locker lock(shipAgent);

	Vector3 spawnLocation = spaceSpawner->getLocationForSpawn();

	shipAgent->initializePosition(spawnLocation.getX(), spawnLocation.getZ(), spawnLocation.getY());

	shipAgent->setHomeLocation(spawnLocation.getX(), spawnLocation.getZ(), spawnLocation.getY(), Quaternion::IDENTITY);
	shipAgent->setHomeObject(spaceSpawner);

	// ShipAgents will be despawned by the SpaceSpawnObserver
	shipAgent->setDespawnOnNoPlayerInRange(false);

	shipAgent->initializeTransform(spawnLocation, Quaternion::IDENTITY);

	shipAgent->setHyperspacing(true);

	if (!zone->transferObject(shipAgent, -1, true)) {
		shipAgent->destroyObjectFromWorld(true);
		shipAgent->destroyObjectFromDatabase(true);

		return nullptr;
	}

	shipAgent->setHyperspacing(false);

	return shipAgent;
}

bool SpaceManagerImplementation::isSpawningPermittedAt(float x, float z, float y, float distance) {
	Vector3 targetPos(x, y, z);

	if (!spaceZone->isWithinBoundaries(targetPos)) {
		return false;
	}

	SortedVector<ActiveArea*> activeAreas;

	spaceZone->getInRangeActiveAreas(x, z, y, &activeAreas, true);

	// info(true) << " -- isSpawningPermittedAt - X: " << targetPos.getX() << " Z: " << targetPos.getZ() << " Y: " << targetPos.getY() << " Distance: " << distance << " Total in range active areas: " << activeAreas.size();

	for (int i = 0; i < activeAreas.size(); ++i) {
		ActiveArea* area = activeAreas.get(i);

		if (area == nullptr || !area->isNoSpawnArea()) {
			continue;
		}

		// info(true) << "Failed to spawn due to being in no spawn area";

		return false;
	}

	if (!findNearbySpawner(x, z, y, distance)) {
		return false;
	}

	// info(true) << "Successful check, ship lair can spawn!\n\n";

	return true;
}

bool SpaceManagerImplementation::findNearbySpawner(float x, float z, float y, float distance) {
	Vector3 targetPos(x, y, z);

	SortedVector<TreeEntry*> closeObjects;

	spaceZone->getInRangeObjects(targetPos.getX(), targetPos.getZ(), targetPos.getY(), ZoneServer::SPACECLOSEOBJECTRANGE, &closeObjects, true, false);

	// info(true) << " -- findNearbySpawner - X: " << targetPos.getX() << " Z: " << targetPos.getZ() << " Y: " << targetPos.getY() << " Distance: " << distance << " Nearby Object Size: " << closeObjects.size();

	for (int i = 0; i < closeObjects.size(); ++i) {
		Reference<SceneObject*> sceneO = static_cast<SceneObject*>(closeObjects.get(i));

		if (sceneO == nullptr || sceneO->getGameObjectType() != SceneObjectType::SPACESPAWNER) {
			continue;
		}

		auto spaceSpawner = sceneO.castTo<SpaceSpawner*>();

		if (spaceSpawner == nullptr) {
			continue;
		}

		float spawnerSize = SpaceSpawnArea::SPACE_SPAWN_SIZE;

		float checkDistance = (distance * distance) + (spawnerSize * spawnerSize);
		float distanceSq = targetPos.squaredDistanceTo(spaceSpawner->getWorldPosition());

		// info(true) << "The Check Distance is " << (uint32)checkDistance << " The distance Squared is: " << (uint32)distanceSq << " Currently Checked Spawner Size: " << spawnerSize;

		if (distanceSq < checkDistance) {
			// info(true) << "Failed to spawn due to nearby spawner!";
			return false;
		}
	}

	return true;
}
