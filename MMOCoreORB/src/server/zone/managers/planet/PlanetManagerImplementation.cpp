/*
 * PlanetManagerImplementation.cpp
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#include "server/zone/managers/planet/PlanetManager.h"

#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/weather/WeatherManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/object/ObjectManager.h"

#include "engine/util/iffstream/IffStream.h"
#include "templates/snapshot/WorldSnapshotIff.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"
#include "server/zone/managers/stringid/StringIdManager.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/packets/player/PlanetTravelPointListResponse.h"
#include "server/zone/objects/area/BadgeActiveArea.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"

#include "server/zone/objects/area/areashapes/CircularAreaShape.h"
#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"
#include "server/zone/objects/area/areashapes/RingAreaShape.h"
#include "server/zone/objects/region/SpawnArea.h"
#include "server/zone/managers/creature/CreatureManager.h"

#include "conf/ConfigManager.h"
#include "PlanetTravelPoint.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/collision/NavMeshManager.h"

//#define DEBUG_REGIONS

ClientPoiDataTable PlanetManagerImplementation::clientPoiDataTable;
Mutex PlanetManagerImplementation::poiMutex;

void PlanetManagerImplementation::initialize() {
	numberOfCities = 0;

	info("Loading planet.");

	planetTravelPointList->setZoneName(zone->getZoneName());

	// Load Planet Regions
	loadRegions();

	loadLuaConfig();
	loadTravelFares();

	buildRegionNavAreas();
	buildCityNavMeshes();

	if (zone->getZoneName() == "dathomir") {
		Reference<ActiveArea*> area = zone->getZoneServer()->createObject(STRING_HASHCODE("object/fs_village_area.iff"), 0).castTo<ActiveArea*>();

		Locker locker(area);
		area->setRadius(768.f);
		area->initializePosition(5306, 0, -4145);
		zone->transferObject(area, -1, true);

		ManagedReference<SceneObject*> scenery = zone->getZoneServer()->createObject(STRING_HASHCODE("object/static/structure/general/fs_village_nobuild_768m.iff"), 0);

		Locker slocker(scenery, area);
		scenery->initializePosition(5306, zone->getHeight(5306, -4145), -4145);
		area->attachScenery(scenery);

		slocker.release();
		locker.release();

		Reference<ActiveArea*> sarlaccArea = zone->getZoneServer()->createObject(STRING_HASHCODE("object/sarlacc_area.iff"), 0).castTo<ActiveArea*>();

		Locker locker2(sarlaccArea);

		sarlaccArea->setRadius(60.f);
		sarlaccArea->initializePosition(-2085, 0, 3147);
		zone->transferObject(sarlaccArea, -1, true);

		locker2.release();

		Reference<ActiveArea*> sarlaccPreArea = zone->getZoneServer()->createObject(STRING_HASHCODE("object/sarlacc_area.iff"), 0).castTo<ActiveArea*>();

		Locker locker3(sarlaccPreArea);

		sarlaccPreArea->setRadius(30.f);
		sarlaccPreArea->initializePosition(-2085, 0, 3147);
		zone->transferObject(sarlaccPreArea, -1, true);
	}

	if (zone->getZoneName() == "tatooine") {
		Reference<ActiveArea*> area = zone->getZoneServer()->createObject(
				STRING_HASHCODE("object/sarlacc_area.iff"), 0).castTo<ActiveArea *>();

		Locker locker(area);
		area->setRadius(30.f);
		area->initializePosition(-6174, 0, -3361);
		zone->transferObject(area, -1, true);

		locker.release();

		Reference<ActiveArea*> preArea = zone->getZoneServer()->createObject(
				STRING_HASHCODE("object/sarlacc_area.iff"), 0).castTo<ActiveArea *>();

		Locker locker2(preArea);

		preArea->setRadius(60.f);
		preArea->initializePosition(-6174, 0, -3361);
		zone->transferObject(preArea, -1, true);
	}
}

void PlanetManagerImplementation::start() {
	if (gcwManager != nullptr)
		gcwManager->start();
}

void PlanetManagerImplementation::loadLuaConfig() {
	String planetName = zone->getZoneName();

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/planet/planet_manager.lua");

	//Get's the configuration settings object for this planet.
	LuaObject luaObject = lua->getGlobalObject(planetName);

	if (luaObject.isValidTable()) {
		bool weatherEnabled = luaObject.getIntField("weatherEnabled");

		if (weatherEnabled) {
			weatherManager = new WeatherManager(zone);
			weatherManager->initialize();
		} else {
			info("Weather Disabled", true);
		}

		bool gcwEnabled = luaObject.getIntField("gcwEnabled");

		if (gcwEnabled) {
			gcwManager = new GCWManager(zone);
			gcwManager->initialize();
		}

		loadClientPoiData();

		LuaObject planetTravelPointsTable = luaObject.getObjectField("planetTravelPoints");
		planetTravelPointList->readLuaObject(&planetTravelPointsTable);
		planetTravelPointsTable.pop();

		loadSnapshotObjects();

		LuaObject planetObjectsTable = luaObject.getObjectField("planetObjects");
		loadPlanetObjects(&planetObjectsTable);
		planetObjectsTable.pop();

		LuaObject badges = luaObject.getObjectField("badgeAreas");
		loadBadgeAreas(&badges);
		badges.pop();
	} else {
		warning("Configuration settings not found.");
	}

	luaObject.pop();

	// Configure shuttleport timing
	if ((shuttleportAwayTime = lua->getGlobalInt("shuttleportAwayTime")) <= 0)
		shuttleportAwayTime = 300;

	if ((shuttleportLandedTime = lua->getGlobalInt("shuttleportLandedTime")) <= 0)
		shuttleportLandedTime = 120;

	if ((shuttleportLandingTime = lua->getGlobalInt("shuttleportLandingTime")) <= 0)
		shuttleportLandingTime = 11;

	// Configure starport timing
	if ((starportAwayTime = lua->getGlobalInt("starportAwayTime")) <= 0)
		starportAwayTime = 60;

	if ((starportLandedTime = lua->getGlobalInt("starportLandedTime")) <= 0)
		starportLandedTime = 120;

	if ((starportLandingTime = lua->getGlobalInt("starportLandingTime")) <= 0)
		starportLandingTime = 14;

#if DEBUG_TRAVEL
	// Allow override in config-local for testing
	shuttleportAwayTime = ConfigManager::instance()->getInt("Core3.PlanetManager.ShuttleportAwayTime", shuttleportAwayTime);
	shuttleportLandedTime = ConfigManager::instance()->getInt("Core3.PlanetManager.ShuttleportLandedTime", shuttleportLandedTime);
	shuttleportLandingTime = ConfigManager::instance()->getInt("Core3.PlanetManager.ShuttleportLandingTime", shuttleportLandingTime);
	starportAwayTime = ConfigManager::instance()->getInt("Core3.PlanetManager.StarportAwayTime", starportAwayTime);
	starportLandedTime = ConfigManager::instance()->getInt("Core3.PlanetManager.StarportLandedTime", starportLandedTime);
	starportLandingTime = ConfigManager::instance()->getInt("Core3.PlanetManager.StarportLandingTime", starportLandingTime);
	info(true) << "\033[42;30m" << __FUNCTION__ << "()"
		<< ": shuttleportAwayTime=" << shuttleportAwayTime
		<< "; shuttleportLandedTime=" << shuttleportLandedTime
		<< "; shuttleportLandingTime=" << shuttleportLandingTime
		<< "; starportAwayTime=" << starportAwayTime
		<< "; starportLandedTime=" << starportLandedTime
		<< "; starportLandingTime=" << starportLandingTime
		<< "\033[0m";
#endif

	delete lua;
	lua = nullptr;
}

void PlanetManagerImplementation::loadPlanetObjects(LuaObject* luaObject) {
	if (!luaObject->isValidTable())
		return;

	for (int i = 1; i <= luaObject->getTableSize(); ++i) {
		lua_State* L = luaObject->getLuaState();
		lua_rawgeti(L, -1, i);

		LuaObject planetObject(L);

		String templateFile = planetObject.getStringField("templateFile");

		// Don't spawn character builder terminals if they're not enabled
		if (templateFile == "object/tangible/terminal/terminal_character_builder.iff" && !ConfigManager::instance()->getCharacterBuilderEnabled()) {
			planetObject.pop();
			continue;
		}

		ManagedReference<SceneObject*> obj = ObjectManager::instance()->createObject(templateFile.hashCode(), 0, "");

		if (obj != nullptr) {
			Locker objLocker(obj);

			float x = planetObject.getFloatField("x");
			float y = planetObject.getFloatField("y");
			float z = planetObject.getFloatField("z");
			float ox = planetObject.getFloatField("ox");
			float oy = planetObject.getFloatField("oy");
			float oz = planetObject.getFloatField("oz");
			float ow = planetObject.getFloatField("ow");
			uint64 parentID = planetObject.getLongField("parent");

			if (obj->isBuildingObject()) {
				BuildingObject* building = obj->asBuildingObject();

				building->createCellObjects();
			}

			obj->initializePosition(x, z, y);
			obj->setDirection(ow, ox, oy, oz);

			ManagedReference<SceneObject*> parent = zone->getZoneServer()->getObject(parentID);

			if (parent != nullptr)
				parent->transferObject(obj, -1, true);
			else
				zone->transferObject(obj, -1, true);

			obj->createChildObjects();
		}

		planetObject.pop();
	}
}

void PlanetManagerImplementation::loadBadgeAreas(LuaObject* badges) {
	if (!badges->isValidTable())
		return;

	uint32 hashCode = STRING_HASHCODE("object/badge_area.iff");

	for (int i = 1; i <= badges->getTableSize(); ++i) {
		lua_State* L = badges->getLuaState();
		lua_rawgeti(L, -1, i);

		LuaObject badge(L);

		String badgeName = badge.getStringAt(1);
		float x = badge.getFloatAt(2);
		float y = badge.getFloatAt(3);
		int cellID = badge.getIntAt(4);
		float radius = badge.getFloatAt(5);
		int badgeID = badge.getIntAt(6);

		ManagedReference<BadgeActiveArea*> obj = server->getZoneServer()->createObject(hashCode, 0).castTo<BadgeActiveArea*>();

		Locker objLocker(obj);

		obj->setRadius(radius);
		obj->setBadge(badgeID);
		obj->initializePosition(x, 0, y);

		if (cellID != 0)
			obj->setCellObjectID(cellID);

		zone->transferObject(obj, -1, false);
		objLocker.release();
		badge.pop();
	}
}

void PlanetManagerImplementation::buildRegionNavAreas() {
	int totalRegions = regionMap.getTotalRegions();

	VectorMap<String, Vector<float>> navAreas;

	for (int i = 0; i < totalRegions; i++) {
		Region* region = regionMap.getRegion(i);

		if (region == nullptr || !region->shouldBuildNavmesh())
			continue;

		String name = region->getAreaName();

		if (name.contains(":")) {
			name = name.subString(name.lastIndexOf(':') + 1);
		}

		name = zone->getZoneName() + "_region_" + name;

		float x = region->getPositionX();
		float y = region->getPositionY();
		float radius = region->getRadius();

		if (region->getAreaShape() != nullptr) {
			Vector3 centerLoc = region->getAreaShape()->getAreaCenter();

			x = centerLoc.getX();
			y = centerLoc.getY();
		}

		Vector<float> location;
		location.add(x);
		location.add(y);
		location.add(radius);

		navAreas.put(name, location);
	}

	String zoneName = zone->getZoneName();
	info("Loading planet navAreas from navareas.db for zone: " + zoneName);

	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	ObjectDatabase* navAreasDatabase = dbManager->loadObjectDatabase("navareas", true, 0xFFFF, false);

	if (navAreasDatabase != nullptr) {
		int i = 0;

		try {
			ObjectDatabaseIterator iterator(navAreasDatabase);

			uint64 objectID;
			ObjectInputStream* objectData = new ObjectInputStream(2000);

			String zoneReference;

			while (iterator.getNextKeyAndValue(objectID, objectData)) {
				if (!Serializable::getVariable<String>(STRING_HASHCODE("SceneObject.zone"), &zoneReference, objectData)) {
					objectData->clear();
					continue;
				}

				if (zoneName != zoneReference) {
					objectData->clear();
					continue;
				}

				Reference<SceneObject*> object = server->getZoneServer()->getObject(objectID);

				if (object != nullptr) {
					NavArea* navArea = object.castTo<NavArea*>();

					if (navArea != nullptr) {
						++i;
						navMeshAreas.put(navArea->getMeshName(), navArea);
					}
				} else {
					error("Failed to deserialize nav area with objectID: " + String::valueOf(objectID));
				}

				objectData->clear();
			}

			delete objectData;
		} catch (DatabaseException& e) {
			error("Database exception in PlanetManagerImplementation::loadNavAreas(): " + e.getMessage());
		}

		bool log = i > 0;
		info(String::valueOf(i) + " nav areas loaded for " + zoneName + ".", log);
	} else {
		error("Could not load the navareas database.");
	}

	uint32 hashCode = STRING_HASHCODE("object/region_navmesh.iff");

	for (int i = 0; i < navAreas.size(); i++) {
		String name = navAreas.elementAt(i).getKey();

		Vector<float> location = navAreas.get(name);
		bool create = false;
		bool destroy = server->getZoneServer()->shouldDeleteNavAreas();

		if (navMeshAreas.contains(name)) {
			NavArea* area = navMeshAreas.get(name);

			if (area->getPositionX() != location.get(0) || area->getPositionY() != location.get(1) || area->getRadius() != location.get(2)) {
				destroy = true;
			}
		} else {
			create = true;
		}

		if (destroy) {
			ManagedReference<NavArea*> area = navMeshAreas.get(name);

			if (area != nullptr) {
				navMeshAreas.drop(name);

				Core::getTaskManager()->executeTask([area] {
					Locker locker(area);
					area->destroyObjectFromWorld(true);
					area->destroyObjectFromDatabase(true);
				}, "destroyNavAreaLambda");
			}

			create = true;
		}

		if (create) {
			ManagedReference<NavArea*> areaObject = server->getZoneServer()->createObject(hashCode, "navareas", 1).castTo<NavArea*>();

			Locker objLocker(areaObject);

			Vector3 position(location.get(0), 0, location.get(1));

			areaObject->initializeNavArea(position, location.get(2), zone, name);
			areaObject->disableMeshUpdates(true);
			navMeshAreas.put(name, areaObject);

			Locker locker(zone, areaObject);
			zone->transferObject(areaObject, -1, false);
		} else {
			NavArea* area = navMeshAreas.get(name);

			if (area != nullptr && !area->isNavMeshLoaded()) {
				area->updateNavMesh(area->getBoundingBox());
			}
		}
	}
}

void PlanetManagerImplementation::loadTravelFares() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("datatables/travel/travel.iff");

	if (iffStream == nullptr) {
		warning("Travel fares could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	//Initialize the rows so we can do a symmetric insert
	for(int i = 0; i < dtiff.getTotalRows(); i++) {
		VectorMap<String, int> planetFares;
		DataTableRow* row =  dtiff.getRow(i);
		String departurePlanet = "";
		row->getCell(0)->getValue(departurePlanet);
		travelFares.put(departurePlanet, planetFares);
	}

	//Insert values
	for(int i = 0; i < dtiff.getTotalRows(); i++) {
		DataTableRow* row =  dtiff.getRow(i);
		String departurePlanet = "";
		row->getCell(0)->getValue(departurePlanet);

		for(int j=i+1; j<dtiff.getTotalColumns(); j++) {
			String arrivalPlanet = dtiff.getColumnNameByIndex(j);
			int fare = 0;
			row->getCell(j)->getValue(fare);
			travelFares.get(departurePlanet).put(arrivalPlanet, fare);
			if(arrivalPlanet != departurePlanet)
				travelFares.get(arrivalPlanet).put(departurePlanet, fare);
		}
	}

	info("Loaded travel fares to " + String::valueOf(travelFares.size()) + " planets.");
}

int PlanetManagerImplementation::getTravelFare(const String& departurePlanet, const String& arrivalPlanet) {
	int fare = travelFares.get(departurePlanet).get(arrivalPlanet);
	return fare;
}

Reference<SceneObject*> PlanetManagerImplementation::loadSnapshotObject(WorldSnapshotNode* node, WorldSnapshotIff* wsiff, int& totalObjects) {
	uint64 objectID = node->getObjectID();
	String templateName = wsiff->getObjectTemplateName(node->getNameID());

	ZoneServer* zoneServer = server->getZoneServer();

	Reference<SceneObject*> object = zoneServer->getObject(objectID);

	++totalObjects;

	/*if (ConfigManager::instance()->isProgressMonitorActivated())
		printf("\r\tLoading snapshot objects: [%d] / [?]\t", totalObjects);*/

	//Object already exists, exit.
	if (object != nullptr)
		return nullptr;

	Reference<SceneObject*> parentObject = zoneServer->getObject(node->getParentID());

	String serverTemplate = templateName.replaceFirst("shared_", "");
	Vector3 position = node->getPosition();

	object = zoneServer->createClientObject(serverTemplate.hashCode(), objectID);

	Locker locker(object);

	object->initializePosition(position.getX(), position.getZ(), position.getY());
	object->setDirection(node->getDirection());

	if (parentObject != nullptr && parentObject->isBuildingObject() && object->isCellObject()) {
		CellObject* cell = cast<CellObject*>(object.get());
		BuildingObject* building = cast<BuildingObject*>(parentObject.get());

		Locker clocker(building, object);

		building->addCell(cell, node->getCellID());
	}

	if (parentObject != nullptr)
		parentObject->transferObject(object, -1);
	else if (node->getParentID() != 0)
		error("parent id " + String::valueOf(node->getParentID()));

	if (parentObject == nullptr) {
		//object->insertToZone(zone);
		Locker clocker(object);

		zone->transferObject(object, -1, true);
	}

	//Load child nodes
	for (int i = 0; i < node->getNodeCount(); ++i) {
		WorldSnapshotNode* childNode = node->getNode(i);

		if (childNode == nullptr)
			continue;

		loadSnapshotObject(childNode, wsiff, totalObjects);
	}

	//object->createChildObjects();

	return object;
}

void PlanetManagerImplementation::loadSnapshotObjects() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("snapshot/" + zone->getZoneName() + ".ws");

	if (iffStream == nullptr) {
		info("Snapshot wasn't found.", true);
		return;
	}

	Reference<WorldSnapshotIff*> wsiff = new WorldSnapshotIff();
	wsiff->readObject(iffStream);

	int totalObjects = 0;
	Vector<SceneObject*> objects;

	for (int i = 0; i < wsiff->getNodeCount(); ++i) {
		auto node = wsiff->getNode(i);

		if (node == nullptr)
			continue;

#ifdef PARALLEL_SNAPSHOT_LOADING
		++totalObjects;

		Core::getTaskManager()->executeTask([this, node, wsiff, totalObjects]() mutable {
			auto sceno = loadSnapshotObject(node, wsiff, totalObjects);

			if (sceno != nullptr) {
				Locker locker(sceno);

				sceno->createChildObjects();
			}
		}, "LoadSnapshotObjectLambda");

#else
		auto sceno = loadSnapshotObject(node, wsiff, totalObjects);

		if (sceno != nullptr) {
			objects.emplace(sceno);
		}
#endif
	}

#ifndef PARALLEL_SNAPSHOT_LOADING
	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* sceno = objects.get(i);

		Locker locker(sceno);

		sceno->createChildObjects();
	}
#endif

	delete iffStream;

	printf("\n");
	info("Loaded " + String::valueOf(totalObjects) + " client objects from world snapshot.", true);
}

bool PlanetManagerImplementation::isTravelToLocationPermitted(const String& departurePoint, const String& arrivalPlanet, const String& arrivalPoint) {
	//Check to see that the departure point exists.
	if (!isExistingPlanetTravelPoint(departurePoint))
		return false;

	//Check to see that the arrival planet exists.
	ManagedReference<Zone*> arrivalZone = zone->getZoneServer()->getZone(arrivalPlanet);

	if (arrivalZone == nullptr)
		return false;

	PlanetManager* arrivalPlanetManager = arrivalZone->getPlanetManager();

	//Check to see that the arrival point exists.
	if (!arrivalPlanetManager->isExistingPlanetTravelPoint(arrivalPoint))
		return false;

	//Check to see if incoming Travel is allowed
	if (!arrivalPlanetManager->isIncomingTravelAllowed(arrivalPoint))
		return false;

	//If both zones are the same, then intraplanetary travel is allowed.
	if (arrivalZone == zone)
		return true;

	//Check to see if interplanetary travel is allowed between both points.
	if (!isInterplanetaryTravelAllowed(departurePoint) || !arrivalPlanetManager->isInterplanetaryTravelAllowed(arrivalPoint))
		return false;

	return true;
}

void PlanetManagerImplementation::sendPlanetTravelPointListResponse(CreatureObject* player) {
	PlanetTravelPointListResponse* ptplr = new PlanetTravelPointListResponse(zone->getZoneName());
	planetTravelPointList->insertToMessage(ptplr, getNearestPlanetTravelPoint(player));

	player->sendMessage(ptplr);
}

PlanetTravelPoint* PlanetManagerImplementation::getNearestPlanetTravelPoint(SceneObject* object, float searchrange) {
#if DEBUG_TRAVEL
	auto callDesc = info(true);

	callDesc << "\033[45;30m" << __FUNCTION__ << "(object="
			<< object->getObjectNameStringIdName()
			<< ":" << object->getObjectID()
			<< ", searchrange=" << searchrange
			<< ") @ " << object->getWorldPosition().toString()
			<< "\033[0m\n\t";
#endif

	Reference<PlanetTravelPoint*> planetTravelPoint = getNearestPlanetTravelPoint(object->getWorldPosition(), searchrange);

#if DEBUG_TRAVEL

	if(planetTravelPoint == nullptr)
		callDesc << "\033[41;30mDID NOT FIND POINT IN RANGE \n";
	else
		callDesc << "\033[42;30mReturning: " << planetTravelPoint->toString() << "\n";

	callDesc << "\033[0m";
	callDesc.flush();
#endif
	return planetTravelPoint;
}

PlanetTravelPoint* PlanetManagerImplementation::getNearestPlanetTravelPoint(const Vector3& position, float range) {
	Reference<PlanetTravelPoint*> planetTravelPoint = nullptr;

	for (int i = 0; i < planetTravelPointList->size(); ++i) {
		const auto& ptp = planetTravelPointList->get(i);

		float dist = position.distanceTo(ptp->getDeparturePosition());

		if (dist < range) {
			range = dist;
			planetTravelPoint = ptp;
		}
	}

	return planetTravelPoint;
}

PlanetTravelPoint* PlanetManagerImplementation::getRandomStarport() {
	Vector<Reference<PlanetTravelPoint*> > planetStarports;

	for (int i = 0; i < planetTravelPointList->size(); ++i) {
		Reference<PlanetTravelPoint*> ptp = planetTravelPointList->get(i);

		if (ptp->isInterplanetary() && ptp->isIncomingAllowed())
			planetStarports.add(ptp);
	}

	return planetStarports.get(System::random(planetStarports.size() - 1));
}

Vector3 PlanetManagerImplementation::getRandomSpawnPoint() {
	Vector3 position;
	bool found = false;
	float minX = zone->getMinX(), maxX = zone->getMaxX();
	float minY = zone->getMinY(), maxY = zone->getMaxY();
	float diameterX = maxX - minX;
	float diameterY = maxY - minY;
	int retries = 20;

	while (!found && retries > 0) {
		position.setX(System::random(diameterX) + minX);
		position.setY(System::random(diameterY) + minY);

		found = isSpawningPermittedAt(position.getX(), position.getY(), 0);

		retries--;
	}

	if (retries == 0) {
		position.set(0, 0, 0);
	}

	return position;
}

Vector3 PlanetManagerImplementation::getInSightSpawnPoint(CreatureObject* creature, float minDistance, float maxDistance, float angle) {
	Vector3 position = creature->getPosition();

	do {
		for (int i = 0; i < 10; i++) {
			position = creature->getWorldCoordinate(minDistance + System::random(20), angle - System::random(2 * angle), true);

			if (noInterferingObjects(creature, position)) {
				return position;
			}
		}

		minDistance += 10;
		angle += 5;
	} while (maxDistance <= 120);

	return creature->getPosition();
}

bool PlanetManagerImplementation::noInterferingObjects(CreatureObject* creature, const Vector3& position) {
	CloseObjectsVector* vec = creature->getCloseObjects();

	if (vec == nullptr)
		return true;

	SortedVector<QuadTreeEntry*> closeObjects;
	vec->safeCopyTo(closeObjects);

	for (int j = 0; j < closeObjects.size(); j++) {
		SceneObject* obj = static_cast<SceneObject*>(closeObjects.get(j));

		SharedObjectTemplate* objectTemplate = obj->getObjectTemplate();

		if (objectTemplate != nullptr) {
			float radius = objectTemplate->getNoBuildRadius();

			if (radius > 0) {
				Vector3 objWorldPos = obj->getWorldPosition();

				if (objWorldPos.squaredDistanceTo(position) < radius * radius) {
					return false;
				}
			}

			if (objectTemplate->isSharedStructureObjectTemplate()) {
				if (StructureManager::instance()->isInStructureFootprint(cast<StructureObject*>(obj), position.getX(), position.getY(), 2)) {
					return false;
				}
			}
		}
	}

	return true;
}

void PlanetManagerImplementation::loadClientPoiData() {

	Locker locker(&poiMutex);

	if (clientPoiDataTable.size() != 0)
		return;

	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/clientpoi/clientpoi.iff");

	if (iffStream == nullptr) {
		error("ClientPoiData not found");
		return;
	}

	DataTableIff data;
	data.readObject(iffStream);

	clientPoiDataTable.readObject(&data);

	info("loaded " + String::valueOf(clientPoiDataTable.size()) + " client pois", true);

	delete iffStream;
}

void PlanetManagerImplementation::buildCityNavMeshes() {
	ReadLocker rLock(&regionMap);

	int numCityRegions = regionMap.getTotalCityRegions();
	bool forceRebuild = server->getZoneServer()->shouldDeleteNavAreas();

	for (int i = 0; i < numCityRegions; i++) {
		CityRegion* city = regionMap.getCityRegion(i);

		if (city == nullptr)
			continue;

		Locker locker(city);
		city->createNavMesh(NavMeshManager::MeshQueue, forceRebuild);
	}

	rLock.release();
}

void PlanetManagerImplementation::loadRegions() {
	Lua* lua = new Lua();
	lua->init();

	String planetName = zone->getZoneName();

	info(true) << "Loading " << planetName << " regions...";

	lua->runFile("scripts/managers/planet/" + planetName + "_regions.lua");
	LuaObject regionObjects = lua->getGlobalObject(planetName + "_regions");

	lua_State* s = regionObjects.getLuaState();

	for (int i = 1; i <= regionObjects.getTableSize(); ++i) {
		lua_rawgeti(s, -1, i);
		LuaObject regionObject(s);

		if (regionObject.isValidTable())
			readRegionObject(regionObject);

		regionObject.pop();
	}

	regionObjects.pop();

	delete lua;
	lua = nullptr;

	info(true) << "Loaded " + String::valueOf(regionMap.getTotalRegions()) + " regions.";
}

void PlanetManagerImplementation::readRegionObject(LuaObject& regionObject) {
	String name = regionObject.getStringAt(1);
	float x = regionObject.getFloatAt(2);
	float y = regionObject.getFloatAt(3);

#ifdef DEBUG_REGIONS
	info(true) << "readRegion -- Name: " << name << " x = " << x << " y = " << y;
#endif // DEBUG_REGIONS

	int type = regionObject.getIntAt(5);

	float radius = 0;
	float x2 = 0;
	float y2 = 0;
	float innerRadius = 0;
	float outerRadius = 0;

	LuaObject areaShapeObject = regionObject.getObjectAt(4);

	if (!areaShapeObject.isValidTable()) {
		error("Invalid area shape table for spawn region " + name);
		return;
	}

	int regionShape = areaShapeObject.getIntAt(1);

	if (regionShape == ActiveArea::CIRCLE) {
		radius = areaShapeObject.getFloatAt(2);

		if (radius <= 0)
			radius = 1.f;
	} else if (regionShape == ActiveArea::RECTANGLE) {
		x2 = areaShapeObject.getFloatAt(2);
		y2 = areaShapeObject.getFloatAt(3);
		int rectWidth = x2 - x;
		int rectHeight = y2 - y;

		if (!(type & ActiveArea::WORLDSPAWNAREA) && (rectWidth <= 0 || rectHeight <= 0)) {
			error("Invalid corner coordinates for rectangular spawn region " + name + ", total height: " + String::valueOf(rectHeight) + ", total width: " + String::valueOf(rectWidth));
			return;
		}
	} else if (regionShape == ActiveArea::RING) {
		innerRadius = areaShapeObject.getFloatAt(2);
		outerRadius = areaShapeObject.getFloatAt(3);

		if (innerRadius <= 0) {
			error("Invalid inner radius of " + String::valueOf(innerRadius) + " must be > 0 for ring spawn region " + name);
			return;
		} else if (outerRadius <= 0) {
			error("Invalid outer radius of " + String::valueOf(outerRadius) + " must be > 0 for ring spawn region " + name);
			return;
		}
	} else {
		error("Invalid area type of " + String::valueOf(regionShape) + " for spawn region " + name);
		return;
	}

	areaShapeObject.pop();

	if (!(type & ActiveArea::WORLDSPAWNAREA) && radius == 0 && x2 == 0 && y2 == 0 && innerRadius == 0 && outerRadius == 0)
		return;

	ManagedReference<Region*> region = nullptr;
	bool spawnAreaRegion = ((type & ActiveArea::SPAWNAREA) || (type & ActiveArea::WORLDSPAWNAREA));

	if (spawnAreaRegion) {
		region = dynamic_cast<Region*>(ObjectManager::instance()->createObject(STRING_HASHCODE("object/spawn_area.iff"), 0, "spawnareas"));
#ifdef DEBUG_REGIONS
		info(true) << " ~~~ Creating spawn_area object ~~~ ";
#endif // DEBUG_REGIONS
	} else {
		region = dynamic_cast<Region*>(ObjectManager::instance()->createObject(STRING_HASHCODE("object/region_area.iff"), 0, "regions"));
#ifdef DEBUG_REGIONS
		info(true) << " --- Creating region_area object --- ";
#endif // DEBUG_REGIONS
	}

	if (region == nullptr)
		return;

	Locker lock(region);

	region->setObjectName(name, false);
	region->setAreaName(name);

	if (regionShape == ActiveArea::RECTANGLE) {
		ManagedReference<RectangularAreaShape*> rectangularAreaShape = new RectangularAreaShape();

		Locker shapeLocker(rectangularAreaShape);

		rectangularAreaShape->setDimensions(x, y, x2, y2);
		float centerX = x + ((x2 - x) / 2);
		float centerY = y + ((y2 - y) / 2);

		rectangularAreaShape->setAreaCenter(centerX, centerY);

		region->setAreaShape(rectangularAreaShape);
	} else if (regionShape == ActiveArea::CIRCLE) {
		ManagedReference<CircularAreaShape*> circularAreaShape = new CircularAreaShape();

		Locker shapeLocker(circularAreaShape);

		circularAreaShape->setAreaCenter(x, y);

		if (radius > 0) {
			circularAreaShape->setRadius(radius);
		}

		region->setAreaShape(circularAreaShape);
	} else if (regionShape == ActiveArea::RING) {
		ManagedReference<RingAreaShape*> ringAreaShape = new RingAreaShape();

		Locker shapeLocker(ringAreaShape);

		ringAreaShape->setAreaCenter(x, y);
		ringAreaShape->setInnerRadius(innerRadius);
		ringAreaShape->setOuterRadius(outerRadius);

		region->setAreaShape(ringAreaShape);
	}

	region->setRegionFlags(type);

	CreatureManager* creatureMan = zone->getCreatureManager();

	if (spawnAreaRegion) {
#ifdef DEBUG_REGIONS
		info(true) << "Adding Spawn Area";
#endif // DEBUG_REGIONS
		ManagedReference<SpawnArea*> area = region.castTo<SpawnArea*>();

		if (creatureMan != nullptr && area != nullptr) {
			if (type & ActiveArea::SPAWNAREA) {
				area->setMaxSpawnLimit(regionObject.getIntAt(7));
				LuaObject spawnGroups = regionObject.getObjectAt(6);

				if (spawnGroups.isValidTable()) {
					Vector<uint32> groups;

					for (int i = 1; i <= spawnGroups.getTableSize(); i++) {
						uint32 groupHash = spawnGroups.getStringAt(i).hashCode();

						// TODO: REMOVE
						if (groupHash == STRING_HASHCODE("insert_spawnlist_here"))
							continue;

#ifdef DEBUG_REGIONS
						info(true) << "Adding Spawn Group: #" << i << " Name: " << spawnGroups.getStringAt(i);
#endif // DEBUG_REGIONS

						groups.add(spawnGroups.getStringAt(i).hashCode());
					}

					area->buildSpawnList(&groups);
				}

				spawnGroups.pop();

				// Add to Spawn Area Map
				creatureMan->addSpawnAreaToMap(name.hashCode(), area);
			}
		}
	}

	region->initializePosition(x, 0, y);
	zone->transferObject(region, -1, true);

	// Region is a City, add to cityRegionMap list
	if (type & ActiveArea::CITY) {
		ManagedReference<CityRegion*> cityRegion = new CityRegion();

		if (cityRegion == nullptr) {
			region->destroyObjectFromWorld(false);
			return;
		}

#ifdef DEBUG_REGIONS
		info(true) << "Adding City: " << name;
#endif // DEBUG_REGIONS

		Locker clocker(cityRegion, region);

		cityRegion->deploy();

		cityRegion->setRegionName(name);
		cityRegion->setZone(zone);

		cityRegion->addRegion(region);
		region->setCityRegion(cityRegion);

		// Attach Scenery
		ManagedReference<SceneObject*> scenery = nullptr;

		if (gcwManager != nullptr) {
			int strongholdFaction = gcwManager->isStrongholdCity(name);

			if (strongholdFaction == Factions::FACTIONIMPERIAL || name.contains("imperial")) {
				scenery = zone->getZoneServer()->createObject(STRING_HASHCODE("object/static/particle/particle_distant_ships_imperial.iff"), 0);
			} else if (strongholdFaction == Factions::FACTIONREBEL || name.contains("rebel")) {
				scenery = zone->getZoneServer()->createObject(STRING_HASHCODE("object/static/particle/particle_distant_ships_rebel.iff"), 0);
			} else {
				scenery = zone->getZoneServer()->createObject(STRING_HASHCODE("object/static/particle/particle_distant_ships.iff"), 0);
			}
		} else {
			scenery = zone->getZoneServer()->createObject(STRING_HASHCODE("object/static/particle/particle_distant_ships.iff"), 0);
		}

		if (scenery != nullptr) {
			Locker slocker(scenery, region);
			scenery->initializePosition(x, zone->getHeight(x, y) + 100, y);
			region->attachScenery(scenery);
		}

		regionMap.addCityRegion(cityRegion);

		// Register City on Map
		Reference<const PlanetMapCategory*> cityCat = TemplateManager::instance()->getPlanetMapCategoryByName("city");

		if (cityCat != nullptr)
			region->setPlanetMapCategory(cityCat);

		// Register with Planetary Map
		zone->registerObjectWithPlanetaryMap(region);
	} else {
		// Add Region to map
		regionMap.addRegion(region);
	}

#ifdef DEBUG_REGIONS
	info(true) << "FINISHED Loading Region -- Name: " << name;
#endif // DEBUG_REGIONS
}

bool PlanetManagerImplementation::validateClientCityInRange(CreatureObject* creature, float x, float y) {
	Vector3 testPosition(x, y, 0);

	Locker locker(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < regionMap.getTotalCityRegions(); ++i) {
		CityRegion* cityRegion = regionMap.getCityRegion(i);

		if (cityRegion == nullptr)
			continue;

		for (int j = 0; j < cityRegion->getRegionsCount(); ++j) {
			Region* activeRegion = cityRegion->getRegion(j);

			if (activeRegion == nullptr)
				continue;

			float radius = activeRegion->getRadius();

			if (radius < 512)
				radius = 512;

			float range = radius * 2;

			Vector3 position(activeRegion->getPositionX(), activeRegion->getPositionY(), 0);

			if (position.squaredDistanceTo(testPosition) <= range * range) {
				StringIdChatParameter msg("player_structure", "city_too_close");
				msg.setTO(cityRegion->getCityRegionName());

				creature->sendSystemMessage(msg);
				return false;
			}
		}
	}

	return true;
}

bool PlanetManagerImplementation::validateRegionName(const String& name) {
	String lowerCase = name.toLowerCase();
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (hasRegion(name) || hasRegion(lowerCase))
		return false;

	for (int i = 0; i < regionMap.getTotalRegions(); ++i) {
		String regionName = regionMap.getRegion(i)->getAreaName();

		if (regionName.beginsWith("@")) {
			String fullName = StringIdManager::instance()->getStringId(regionName.hashCode()).toString().toLowerCase();

			if ((!fullName.isEmpty()) && (lowerCase == fullName || fullName.contains(lowerCase) || lowerCase.contains(fullName)))
				return false;
		}
	}

	return true;
}

void PlanetManagerImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	terrainManager = new TerrainManager();
}


void PlanetManagerImplementation::finalize() {
	terrainManager = nullptr;
	weatherManager = nullptr;
	planetTravelPointList = nullptr;
	performanceLocations = nullptr;
	zone = nullptr;
	server = nullptr;

	if (gcwManager != nullptr) {
		gcwManager->stop();
		gcwManager = nullptr;
	}
}

bool PlanetManagerImplementation::isInRangeWithPoi(float x, float y, float range) {
	String zoneName = zone->getZoneName();

	if (!clientPoiDataTable.containsPlanet(zoneName))
		return false;

	Vector3 target(x, y, 0);

	const Vector<Reference<PoiData*> >& pois = clientPoiDataTable.getPois(zoneName);

	for (int i = 0; i < pois.size(); ++i) {
		if (pois.get(i)->getPosition().squaredDistanceTo(target) <= range * range)
			return true;
	}

	return false;
}

bool PlanetManagerImplementation::isInObjectsNoBuildZone(float x, float y, float extraMargin, bool checkFootprint) {
	auto hit = findObjectInNoBuildZone(x, y, extraMargin, checkFootprint);

	return hit != nullptr;
}

Reference<SceneObject* > PlanetManagerImplementation::findObjectInNoBuildZone(float x, float y, float extraMargin, bool checkFootprint) {
	SortedVector<QuadTreeEntry*> closeObjects;

	Vector3 targetPos(x, y, zone->getHeight(x, y));

	zone->getInRangeObjects(x, y, 512, &closeObjects, true, false);

	for (int i = 0; i < closeObjects.size(); ++i) {
		Reference<SceneObject*> obj = static_cast<SceneObject*>(closeObjects.get(i));

		SharedObjectTemplate* objectTemplate = obj->getObjectTemplate();

		if (objectTemplate != nullptr) {
			float radius = objectTemplate->getNoBuildRadius();

			// Only check objects with an actual NoBuildRadius
			if (radius > 0) {
				// Add margin to check
				radius += extraMargin;

				Vector3 objWorldPos = obj->getWorldPosition();

				if (objWorldPos.squaredDistanceTo(targetPos) < radius * radius) {
					return obj;
				}
			}

			// Check if it's within a structure's footprint
			if (checkFootprint && objectTemplate->isSharedStructureObjectTemplate()) {
				if (StructureManager::instance()->isInStructureFootprint(cast<StructureObject*>(obj.get()), x, y, extraMargin)) {
					return obj;
				}
			}
		}
	}

	return nullptr;
}

bool PlanetManagerImplementation::isSpawningPermittedAt(float x, float y, float margin, bool worldSpawnArea) {
	SortedVector<ActiveArea*> activeAreas;

	Vector3 targetPos(x, y, 0);

	if (!zone->isWithinBoundaries(targetPos))
		return false;

	zone->getInRangeActiveAreas(x, y, &activeAreas, true);

	for (int i = 0; i < activeAreas.size(); ++i) {
		ActiveArea* area = activeAreas.get(i);

		if (area == nullptr)
			continue;

		if (area->isCityRegion() || area->isNoSpawnArea()) {
			return false;
		}

		if (area->isRegion()) {
			Region* region = cast<Region*>(area);

			if (region != nullptr && region->isPlayerCity())
				return false;
		}

		if (worldSpawnArea && area->isNoWorldSpawnArea())
			return false;
	}

	if (isInObjectsNoBuildZone(x, y, margin)) {
		return false;
	}

	if (isInWater(x, y)) {
		return false;
	}

	if (terrainManager->getHighestHeightDifference(x - 10, y - 10, x + 10, y + 10) > 15.0)
		return false;

	return true;
}

bool PlanetManagerImplementation::isBuildingPermittedAt(float x, float y, SceneObject* object, float margin, bool checkFootprint) {
	SortedVector<ActiveArea*> activeAreas;

	Vector3 targetPos(x, y, 0);

	if (!zone->isWithinBoundaries(targetPos))
		return false;

	//targetPos.setZ(zone->getHeight(x, y)); not needed

	zone->getInRangeActiveAreas(x, y, &activeAreas, true);

	for (int i = 0; i < activeAreas.size(); ++i) {
		ActiveArea* area = activeAreas.get(i);

		if (area->isNoBuildZone()) {
			return false;
		}
	}

	if (isInObjectsNoBuildZone(x, y, margin, checkFootprint)) {
		return false;
	}

	if (isInWater(x, y)) {
		return false;
	}

	if (isInRangeWithPoi(x, y, 150))
		return false;

	return true;
}

bool PlanetManagerImplementation::isCampingPermittedAt(float x, float y, float margin) {
	SortedVector<ManagedReference<ActiveArea* > > activeAreas;

	Vector3 targetPos(x, y, zone->getHeight(x, y));

	zone->getInRangeActiveAreas(x, y, &activeAreas, true);

	for (int i = 0; i < activeAreas.size(); ++i) {
		ActiveArea* area = activeAreas.get(i);

		if (area == nullptr)
			continue;

		// Skip areas explicitly marked as camping allowed
		if (area->isCampingArea()) {
			continue;
		}

		// Honor no-build after checking for areas that camping is explicitly allowed
		if (area->isNoBuildZone()) {
			return false;
		}
	}

	if (isInWater(x, y)) {
		return false;
	}

	if (isInRangeWithPoi(x, y, 150))
		return false;

	return true;
}

Reference<SceneObject*> PlanetManagerImplementation::findObjectTooCloseToDecoration(float x, float y, float margin) {
	SortedVector<ManagedReference<QuadTreeEntry* > > closeObjects;

	Vector3 targetPos(x, y,0);

	zone->getInRangeObjects(x, y, 256, &closeObjects, true, false);

	for (int i = 0; i < closeObjects.size(); ++i) {

		Reference<SceneObject*> obj = cast<SceneObject*>(closeObjects.get(i).get());

		if(obj == nullptr || obj->isCreatureObject() || obj->getObjectTemplate() == nullptr)
			continue;

		Vector3 objVec(obj->getPositionX(), obj->getPositionY(),0);

		int squaredDistance = (obj->getObjectTemplate()->getNoBuildRadius() + margin) * (obj->getObjectTemplate()->getNoBuildRadius() + margin);

		if(objVec.squaredDistanceTo(targetPos) < squaredDistance){
			return obj;
		}

		if(obj->isStructureObject() && StructureManager::instance()->isInStructureFootprint(cast<StructureObject*>(obj.get()), x, y, margin) ){
				return obj;
		}
	}

	return nullptr;

}


Reference<SceneObject*> PlanetManagerImplementation::createTicket(const String& departurePoint, const String& arrivalPlanet, const String& arrivalPoint) {
	ManagedReference<SceneObject*> obj = server->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/travel/travel_ticket/base/base_travel_ticket.iff"), 1);

	if (obj == nullptr)
		return nullptr;

	if (!obj->isTangibleObject()) {
		obj->destroyObjectFromDatabase(true);
		return nullptr;
	}

	TangibleObject* tano = cast<TangibleObject*>( obj.get());

	if (!tano->isTicketObject()) {
		tano->destroyObjectFromDatabase(true);
		return nullptr;
	}

	TicketObject* ticket = cast<TicketObject*>( tano);
	ticket->setDeparturePlanet(zone->getZoneName());
	ticket->setDeparturePoint(departurePoint);
	ticket->setArrivalPlanet(arrivalPlanet);
	ticket->setArrivalPoint(arrivalPoint);

	return ticket;
}

bool PlanetManagerImplementation::checkShuttleStatus(CreatureObject* creature, CreatureObject* shuttle) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	Reference<ShuttleDepartureTask*> task = shuttleMap.get(shuttle->getObjectID());

	if (task == nullptr)
		return false;

	int seconds = task->getSecondsRemaining();

	if (!task->isLanded() && seconds > 0) {
		if (!task->isLanding()) {
			int minutes = seconds / 60;
			seconds -= 60 * minutes;

			StringBuffer message;
			message << "The next shuttle will be ready to board in ";

			if (minutes > 0)
				message << minutes << " minute" << (minutes > 1 ? "s" : "");

			if (seconds > 0) {
				if (minutes > 0)
					message << " and ";

				message << seconds << " second" << (seconds > 1 ? "s" : "");
			}

			message << ".";

			creature->sendSystemMessage(message.toString());
		} else {
			creature->sendSystemMessage("The shuttle is about to begin boarding.");
		}

		return false;
	}

	return true;
}

bool PlanetManagerImplementation::isInWater(float x, float y) {
	float z = zone->getHeight(x, y);
	float waterHeight = z;
	if(getTerrainManager()->getWaterHeight(x, y, waterHeight))
		if(waterHeight >= z)
			return true;

	return false;
}

float PlanetManagerImplementation::findClosestWorldFloor(float x, float y, float z, float swimHeight, IntersectionResults* intersections, CloseObjectsVector* closeObjects) {

	//SortedVector<IntersectionResult> intersections;

	Reference<IntersectionResults*> ref;

    if (intersections == nullptr) {
    	ref = intersections = new IntersectionResults();
    	CollisionManager::getWorldFloorCollisions(x, y, zone, intersections, closeObjects);
    }

	float terrainHeight = zone->getHeight(x, y);
	float diff = fabs(z - terrainHeight);
	float closestHeight = terrainHeight;

	for (int i = 0; i < intersections->size(); i++) {
		float newDiff = fabs(16384.f - intersections->get(i).getIntersectionDistance() - z);
		if ( newDiff < diff) {
			diff = newDiff;
			closestHeight = 16384.f - intersections->get(i).getIntersectionDistance();
		}
	}

	float waterHeight;
	bool result = getTerrainManager()->getWaterHeight(x, y, waterHeight);

	if (result && waterHeight > (closestHeight + swimHeight)) {
		closestHeight = waterHeight - swimHeight;
	}

	return closestHeight;
}

void PlanetManagerImplementation::addPlayerCityTravelPoint(PlanetTravelPoint* planetTravelPoint){

	planetTravelPointList->addPlayerCityTravelPoint(planetTravelPoint);

}

void PlanetManagerImplementation::removePlayerCityTravelPoint(const String& cityName){

	planetTravelPointList->removePlayerCityTravelPoint(cityName);

}

void PlanetManagerImplementation::scheduleShuttle(CreatureObject* shuttle, int shuttleType) {
	Locker clocket(_this.getReferenceUnsafeStaticCast(), shuttle);

	const uint64 oid = shuttle->getObjectID();

	if (shuttleMap.contains(oid)) {
		// this shuttle is already known, no need for a 2nd task
		return;
	}

	shuttle->setPosture(CreaturePosture::UPRIGHT);

	Reference<ShuttleDepartureTask*> task = new ShuttleDepartureTask(shuttle);

	switch (shuttleType) {
	case SHUTTLEPORT:
		task->setLandedTime(shuttleportLandedTime);
		task->setLandingTime(shuttleportLandingTime);
		task->setDepartedTime(shuttleportAwayTime);
		break;
	case STARPORT:
		task->setLandedTime(starportLandedTime);
		task->setLandingTime(starportLandingTime);
		task->setDepartedTime(starportAwayTime);
		break;
	}

	task->setShuttleType(shuttleType);

	shuttleMap.put(oid, task);

	task->schedule((task->getLandedTime() + task->getLandingTime()) * 1000);
}

int PlanetManagerImplementation::destroyEventObject(uint64 objectID) {
	if (spawnedEventObjects.contains(objectID)) {
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(objectID);

		if (object == nullptr) {
			spawnedEventObjects.drop(objectID);
			return 0;
		}

		Core::getTaskManager()->executeTask([object] () {
			Locker locker(object);

			if (object->isPersistent())
				object->destroyObjectFromDatabase(true);

			object->destroyObjectFromWorld(true);

		}, "DestroyEventObjectLambda");

		spawnedEventObjects.drop(objectID);

		return 1;
	} else if (spawnedEventStructures.contains(objectID)) {
		ManagedReference<StructureObject*> structure = server->getZoneServer()->getObject(objectID).castTo<StructureObject*>();

		if (structure == nullptr) {
			spawnedEventStructures.drop(objectID);
			return 0;
		}

		StructureManager::instance()->destroyStructure(structure);
		spawnedEventStructures.drop(objectID);
		return 1;
	}

	return 0;
}

int PlanetManagerImplementation::destroyAllEventObjects() {
	int counter = 0;
	SynchronizedSortedVector<uint64> objects(spawnedEventObjects);
	int size = objects.size();

	for (int i = 0; i < size; i++) {
		uint64 objectID = objects.get(i);
		counter += destroyEventObject(objectID);
	}

	SynchronizedSortedVector<uint64> structures(spawnedEventStructures);
	size = structures.size();

	for (int i = 0; i < size; i++) {
		uint64 objectID = structures.get(i);
		counter += destroyEventObject(objectID);
	}

	return counter;
}
