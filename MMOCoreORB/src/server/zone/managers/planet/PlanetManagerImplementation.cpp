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
#include "conf/ConfigManager.h"
#include "PlanetTravelPoint.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/collision/NavMeshManager.h"

ClientPoiDataTable PlanetManagerImplementation::clientPoiDataTable;
Mutex PlanetManagerImplementation::poiMutex;

void PlanetManagerImplementation::initialize() {
	numberOfCities = 0;

	info("Loading planet.");

	planetTravelPointList->setZoneName(zone->getZoneName());

	loadLuaConfig();
	loadTravelFares();

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
	if (gcwManager != NULL)
		gcwManager->start();
}

void PlanetManagerImplementation::loadLuaConfig() {
	String planetName = zone->getZoneName();

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/planet_manager.lua");

	//Get's the configuration settings object for this planet.
	LuaObject luaObject = lua->getGlobalObject(planetName);

	if (luaObject.isValidTable()) {

		bool weatherEnabled = luaObject.getIntField("weatherEnabled");
		if(weatherEnabled) {
			weatherManager = new WeatherManager(zone);
			weatherManager->initialize();
		} else {
			info("Weather Disabled", true);
		}

		bool gcwEnabled = luaObject.getIntField("gcwEnabled");
		if(gcwEnabled) {
			gcwManager = new GCWManager(zone);
			gcwManager->initialize();
		}

		LuaObject outposts = luaObject.getObjectField("outpostRegionNames");
		loadClientRegions(&outposts);

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

		LuaObject navAreas = luaObject.getObjectField("navAreas");
		loadNavAreas(&navAreas);
		navAreas.pop();

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
	  starportLandingTime = 120;

	ReadLocker rLock(&regionMap);
	int numRegions = regionMap.getTotalRegions();
	bool forceRebuild = server->getZoneServer()->shouldDeleteNavAreas();
	for (int i=0; i<numRegions; i++) {
		CityRegion* city = regionMap.getRegion(i);
		Locker locker(city);
		city->createNavMesh(NavMeshManager::MeshQueue, forceRebuild);
	}

	rLock.release();

	delete lua;
	lua = NULL;
}

void PlanetManagerImplementation::loadPlanetObjects(LuaObject* luaObject) {
	if (!luaObject->isValidTable())
		return;

	for (int i = 1; i <= luaObject->getTableSize(); ++i) {
		lua_State* L = luaObject->getLuaState();
		lua_rawgeti(L, -1, i);

		LuaObject planetObject(L);

		String templateFile = planetObject.getStringField("templateFile");

		ManagedReference<SceneObject*> obj = ObjectManager::instance()->createObject(templateFile.hashCode(), 0, "");

		if (obj != NULL) {
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

			if (parent != NULL)
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

void PlanetManagerImplementation::loadNavAreas(LuaObject* areas) {
	VectorMap<String, Vector<float>> configAreas;

	if (areas->isValidTable()) {
		for (int i = 1; i <= areas->getTableSize(); ++i) {
			lua_State* L = areas->getLuaState();
			lua_rawgeti(L, -1, i);

			LuaObject areaTable(L);

			String name = areaTable.getStringAt(1);
			Vector<float> locs;
			locs.add(areaTable.getFloatAt(2));
			locs.add(areaTable.getFloatAt(3));
			locs.add(areaTable.getFloatAt(4));

			configAreas.put(name, locs);

			areaTable.pop();
		}
	}

	String zoneName = zone->getZoneName();
	info("Loading planet navAreas from navareas.db for zone: " + zoneName);

	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	ObjectDatabase* navAreasDatabase = dbManager->loadObjectDatabase("navareas", true, 0xFFFF, false);

	if (navAreasDatabase != NULL) {
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

				if (object != NULL) {
					NavArea* navArea = object.castTo<NavArea*>();

					if (navArea != NULL) {
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

	for (int i = 0; i < configAreas.size(); i++) {
		String name = configAreas.elementAt(i).getKey();
		Vector<float> loc = configAreas.get(name);
		bool create = false, destroy = server->getZoneServer()->shouldDeleteNavAreas();

		if (navMeshAreas.contains(name)) {
			NavArea* area = navMeshAreas.get(name);

			if (area->getPositionX() != loc.get(0) || area->getPositionY() != loc.get(1) || area->getRadius() != loc.get(2)) {
				destroy = true;
			}
		} else {
			create = true;
		}

		if (destroy) {
			ManagedReference<NavArea*> area = navMeshAreas.get(name);

			if (area != NULL) {
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
			Vector3 position(loc.get(0), 0, loc.get(1));
			areaObject->initializeNavArea(position, loc.get(2), zone, name);
			areaObject->disableMeshUpdates(true);
			navMeshAreas.put(name, areaObject);

			Locker locker(zone, areaObject);
			zone->transferObject(areaObject, -1, false);
		} else {
			NavArea* area = navMeshAreas.get(name);

			if (area != NULL && !area->isNavMeshLoaded()) {
				area->updateNavMesh(area->getBoundingBox());
			}
		}
	}
}

void PlanetManagerImplementation::loadTravelFares() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("datatables/travel/travel.iff");

	if (iffStream == NULL) {
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

	if (ConfigManager::instance()->isProgressMonitorActivated())
		printf("\r\tLoading snapshot objects: [%d] / [?]\t", totalObjects);

	//Object already exists, exit.
	if (object != NULL)
		return NULL;

	Reference<SceneObject*> parentObject = zoneServer->getObject(node->getParentID());

	String serverTemplate = templateName.replaceFirst("shared_", "");
	Vector3 position = node->getPosition();

	object = zoneServer->createClientObject(serverTemplate.hashCode(), objectID);

	Locker locker(object);

	object->initializePosition(position.getX(), position.getZ(), position.getY());
	object->setDirection(node->getDirection());

	if (parentObject != NULL && parentObject->isBuildingObject() && object->isCellObject()) {
		CellObject* cell = cast<CellObject*>(object.get());
		BuildingObject* building = cast<BuildingObject*>(parentObject.get());

		Locker clocker(building, object);

		building->addCell(cell, node->getCellID());
	}

	if (parentObject != NULL)
		parentObject->transferObject(object, -1);
	else if (node->getParentID() != 0)
		error("parent id " + String::valueOf(node->getParentID()));

	if (parentObject == NULL) {
		//object->insertToZone(zone);
		Locker clocker(object);

		zone->transferObject(object, -1, true);
	}

	//Load child nodes
	for (int i = 0; i < node->getNodeCount(); ++i) {
		WorldSnapshotNode* childNode = node->getNode(i);

		if (childNode == NULL)
			continue;

		loadSnapshotObject(childNode, wsiff, totalObjects);
	}

	//object->createChildObjects();

	return object;
}

void PlanetManagerImplementation::loadSnapshotObjects() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("snapshot/" + zone->getZoneName() + ".ws");

	if (iffStream == NULL) {
		info("Snapshot wasn't found.", true);
		return;
	}

	WorldSnapshotIff wsiff;
	wsiff.readObject(iffStream);

	int totalObjects = 0;

	Vector<SceneObject*> objects(1000, 1000);

	for (int i = 0; i < wsiff.getNodeCount(); ++i) {
		WorldSnapshotNode* node = wsiff.getNode(i);

		if (node == NULL)
			continue;

		SceneObject* object = loadSnapshotObject(node, &wsiff, totalObjects);

		if (object != NULL)
			objects.add(object);
	}

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* sceno = objects.get(i);

		Locker locker(sceno);

		sceno->createChildObjects();
	}

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

	if (arrivalZone == NULL)
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
	StringBuffer callDesc;

	callDesc << "getNearestPlanetTravelPoint("
			<< object->getObjectNameStringIdName()
			<< ":" << object->getObjectID()
			<< ", " << searchrange
			<< ") @ " << object->getWorldPosition().toString();
#endif

	Reference<PlanetTravelPoint*> planetTravelPoint = getNearestPlanetTravelPoint(object->getWorldPosition(), searchrange);

#if DEBUG_TRAVEL

	if(planetTravelPoint == NULL)
		callDesc << ": DID NOT FIND POINT IN RANGE";
	else
		callDesc << ": returning: " << planetTravelPoint->toString();

	info(callDesc, true);
#endif
	return planetTravelPoint;
}

PlanetTravelPoint* PlanetManagerImplementation::getNearestPlanetTravelPoint(const Vector3& position, float range) {
	Reference<PlanetTravelPoint*> planetTravelPoint = NULL;

	for (int i = 0; i < planetTravelPointList->size(); ++i) {
		Reference<PlanetTravelPoint*> ptp = planetTravelPointList->get(i);

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

void PlanetManagerImplementation::loadClientPoiData() {

	Locker locker(&poiMutex);

	if (clientPoiDataTable.size() != 0)
		return;

	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/clientpoi/clientpoi.iff");

	if (iffStream == NULL) {
		error("ClientPoiData not found");
		return;
	}

	DataTableIff data;
	data.readObject(iffStream);

	clientPoiDataTable.readObject(&data);

	info("loaded " + String::valueOf(clientPoiDataTable.size()) + " client pois", true);

	delete iffStream;
}

void PlanetManagerImplementation::loadClientRegions(LuaObject* outposts) {
	VectorMap<String, Vector<float> > outpostData;

	if (outposts->isValidTable()) {
		for (int i = 1; i <= outposts->getTableSize(); ++i) {
			lua_State* L = outposts->getLuaState();
			lua_rawgeti(L, -1, i);

			LuaObject outpost(L);

			if (outpost.isValidTable()) {
				String name = outpost.getStringField("name");
				Vector<float> coords;
				coords.add(outpost.getFloatField("x"));
				coords.add(outpost.getFloatField("y"));
				outpostData.put(name, coords);
			}

			outpost.pop();
		}
	}

	outposts->pop();

	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("datatables/clientregion/" + zone->getZoneName() + ".iff");

	Reference<PlanetMapCategory*> cityCat = TemplateManager::instance()->getPlanetMapCategoryByName("city");

	if (iffStream == NULL) {
		info("No client regions found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	String zoneName = zone->getZoneName();
	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		String regionName;
		float x, y, radius;

		DataTableRow* row = dtiff.getRow(i);
		row->getValue(0, regionName);
		row->getValue(1, x);
		row->getValue(2, y);
		row->getValue(3, radius);

		for (int i = 0; i < outpostData.size(); i++) {
			if (x == outpostData.get(i).get(0) && y == outpostData.get(i).get(1)) {
				regionName = outpostData.elementAt(i).getKey();
			}
		}

		ManagedReference<CityRegion*> cityRegion = regionMap.getRegion(regionName);

		if (cityRegion == NULL) {
			cityRegion = new CityRegion();

			Locker locker(cityRegion);
			cityRegion->deploy();
			cityRegion->setRegionName(regionName);
			cityRegion->setZone(zone);

			regionMap.addRegion(cityRegion);
		}

		Locker locker(cityRegion);

		ManagedReference<Region*> region = cityRegion->addRegion(x, y, radius, false);

		locker.release();

		if (region != NULL) {
			Locker rlocker(region);

			if (cityRegion->getRegionsCount() == 1) {//Register the first region only.
				region->setPlanetMapCategory(cityCat);
				zone->registerObjectWithPlanetaryMap(region);
			}

			region->setMunicipalZone(true);

			ManagedReference<SceneObject*> scenery = NULL;

			if (gcwManager != NULL) {
				int strongholdFaction = gcwManager->isStrongholdCity(regionName);

				if (strongholdFaction == Factions::FACTIONIMPERIAL || regionName.contains("imperial")) {
					scenery = zone->getZoneServer()->createObject(STRING_HASHCODE("object/static/particle/particle_distant_ships_imperial.iff"), 0);
				} else if (strongholdFaction == Factions::FACTIONREBEL || regionName.contains("rebel")) {
					scenery = zone->getZoneServer()->createObject(STRING_HASHCODE("object/static/particle/particle_distant_ships_rebel.iff"), 0);
				} else {
					scenery = zone->getZoneServer()->createObject(STRING_HASHCODE("object/static/particle/particle_distant_ships.iff"), 0);
				}
			} else {
				scenery = zone->getZoneServer()->createObject(STRING_HASHCODE("object/static/particle/particle_distant_ships.iff"), 0);
			}

			Locker slocker(scenery, region);
			scenery->initializePosition(x, zone->getHeight(x, y) + 100, y);
			region->attachScenery(scenery);
		}

		ManagedReference<ActiveArea*> noBuild = zone->getZoneServer()->createObject(STRING_HASHCODE("object/active_area.iff"), 0).castTo<ActiveArea*>();

		Locker areaLocker(noBuild);

		noBuild->initializePosition(x, 0, y);

		ManagedReference<CircularAreaShape*> areaShape = new CircularAreaShape();

		Locker shapeLocker(areaShape);

		areaShape->setRadius(radius * 2);
		areaShape->setAreaCenter(x, y);
		noBuild->setAreaShape(areaShape);
		noBuild->setRadius(radius * 2);
		noBuild->setNoBuildArea(true);
		// Cities already have "Municipal" protection so the structure no-build should not apply to camps
		noBuild->setCampingPermitted(true);

		Locker zoneLocker(zone);

		zone->transferObject(noBuild, -1, true);
	}

	info("Added " + String::valueOf(regionMap.getTotalRegions()) + " client regions.");

	delete iffStream;
}

bool PlanetManagerImplementation::validateClientCityInRange(CreatureObject* creature, float x, float y) {
	Vector3 testPosition(x, y, 0);

	Locker locker(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < regionMap.getTotalRegions(); ++i) {
		CityRegion* region = regionMap.getRegion(i);

		for (int j = 0; j < region->getRegionsCount(); ++j) {
			Region* activeRegion = region->getRegion(j);
			float radius = activeRegion->getRadius();

			if (radius < 512)
				radius = 512;

			float range = radius * 2;

			Vector3 position(activeRegion->getPositionX(), activeRegion->getPositionY(), 0);

			if (position.squaredDistanceTo(testPosition) <= range * range) {
				StringIdChatParameter msg("player_structure", "city_too_close");
				msg.setTO(region->getRegionName());

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
		String regionName = regionMap.getRegion(i)->getRegionName();

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
	terrainManager = NULL;
	weatherManager = NULL;
	planetTravelPointList = NULL;
	performanceLocations = NULL;
	zone = NULL;
	server = NULL;

	if (gcwManager != NULL) {
		gcwManager->stop();
		gcwManager = NULL;
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

bool PlanetManagerImplementation::isInObjectsNoBuildZone(float x, float y, float extraMargin) {
	SortedVector<QuadTreeEntry*> closeObjects;

	Vector3 targetPos(x, y, zone->getHeight(x, y));

	zone->getInRangeObjects(x, y, 512, &closeObjects, true, false);

	for (int i = 0; i < closeObjects.size(); ++i) {
		SceneObject* obj = static_cast<SceneObject*>(closeObjects.get(i));

		SharedObjectTemplate* objectTemplate = obj->getObjectTemplate();

		if (objectTemplate != NULL) {
			float radius = objectTemplate->getNoBuildRadius();

			// Only check objects with an actual NoBuildRadius
			if (radius > 0) {
				// Add margin to check
				radius += extraMargin;

				Vector3 objWorldPos = obj->getWorldPosition();

				if (objWorldPos.squaredDistanceTo(targetPos) < radius * radius) {
					return true;
				}
			}

			// Check if it's within a structure's footprint
			if (objectTemplate->isSharedStructureObjectTemplate()) {
				if (StructureManager::instance()->isInStructureFootprint(cast<StructureObject*>(obj), x, y, extraMargin)) {
					return true;
				}
			}
		}
	}

	return false;
}

bool PlanetManagerImplementation::isSpawningPermittedAt(float x, float y, float margin) {
	SortedVector<ActiveArea*> activeAreas;

	Vector3 targetPos(x, y, 0);

	if (!zone->isWithinBoundaries(targetPos))
		return false;

	targetPos.setZ(zone->getHeight(x, y));

	zone->getInRangeActiveAreas(x, y, &activeAreas, true);
	zone->getInRangeActiveAreas(x, y, margin + 64.f, &activeAreas, true);

	for (int i = 0; i < activeAreas.size(); ++i) {
		ActiveArea* area = activeAreas.get(i);

		if (area->isRegion() || area->isMunicipalZone() || area->isNoSpawnArea()) {
			return false;
		}
	}

	if (isInObjectsNoBuildZone(x, y, margin)) {
		return false;
	}

	if (isInWater(x, y)) {
		return false;
	}

	if (isInRangeWithPoi(x, y, 150))
		return false;

	if (terrainManager->getHighestHeightDifference(x - 10, y - 10, x + 10, y + 10) > 15.0)
		return false;

	return true;
}

bool PlanetManagerImplementation::isBuildingPermittedAt(float x, float y, SceneObject* object, float margin) {
	SortedVector<ActiveArea*> activeAreas;

	Vector3 targetPos(x, y, 0);

	if (!zone->isWithinBoundaries(targetPos))
		return false;

	//targetPos.setZ(zone->getHeight(x, y)); not needed

	zone->getInRangeActiveAreas(x, y, &activeAreas, true);

	for (int i = 0; i < activeAreas.size(); ++i) {
		ActiveArea* area = activeAreas.get(i);

		if (area->isNoBuildArea()) {
			return false;
		}
	}

	if (isInObjectsNoBuildZone(x, y, margin)) {
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

		// Skip areas explicitly marked as camping allowed
		if (area->isCampingPermitted()) {
			continue;
		}

		// Honor no-build after checking for areas that camping is explicitly allowed
		if (area->isNoBuildArea()) {
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

		ManagedReference<SceneObject*> obj = cast<SceneObject*>(closeObjects.get(i).get());

		if(obj == NULL || obj->isCreatureObject() || obj->getObjectTemplate() == NULL)
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

	return NULL;

}


Reference<SceneObject*> PlanetManagerImplementation::createTicket(const String& departurePoint, const String& arrivalPlanet, const String& arrivalPoint) {
	ManagedReference<SceneObject*> obj = server->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/travel/travel_ticket/base/base_travel_ticket.iff"), 1);

	if (obj == NULL)
		return NULL;

	if (!obj->isTangibleObject()) {
		obj->destroyObjectFromDatabase(true);
		return NULL;
	}

	TangibleObject* tano = cast<TangibleObject*>( obj.get());

	if (!tano->isTicketObject()) {
		tano->destroyObjectFromDatabase(true);
		return NULL;
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

	if (task == NULL)
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

    if (intersections == NULL) {
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

	shuttleMap.put(oid, task);


	task->schedule((task->getLandedTime() + task->getLandingTime()) * 1000);
}
