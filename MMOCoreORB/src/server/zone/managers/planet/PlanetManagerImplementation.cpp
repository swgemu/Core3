/*
 * PlanetManagerImplementation.cpp
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#include "PlanetManager.h"

#include "server/db/ServerDatabase.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/weather/WeatherManager.h"

#include "engine/util/iffstream/IffStream.h"
#include "server/zone/templates/snapshot/WorldSnapshotIff.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/templates/datatables/DataTableCell.h"

#include "server/zone/managers/planet/MapLocationType.h"

#include "server/zone/objects/tangible/terminal/ticketcollector/TicketCollector.h"
#include "server/zone/objects/tangible/terminal/travel/TravelTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/packets/player/PlanetTravelPointListResponse.h"
#include "server/zone/objects/area/BadgeActiveArea.h"

#include "server/zone/objects/region/CityRegion.h"

#include "PlanetTravelPoint.h"

void PlanetManagerImplementation::initialize() {
	terrainManager = new TerrainManager(zone);

	numberOfCities = 0;

	info("Loading planet.");

	//TODO: Load from the TRE files.
	if (terrainManager->initialize("terrain/" + zone->getZoneName() + ".trn"))
		info("Loaded terrain file successfully.");
	else
		error("Failed to load terrain file.");

	planetTravelPointList.setZoneName(zone->getZoneName());

	loadLuaConfig();

	loadClientRegions();
	loadSnapshotObjects();
	loadTravelFares();

	loadBadgeAreas();
	loadNoBuildAreas();
	loadPerformanceLocations();
	loadHuntingTargets();
	loadReconLocations();
	loadPlayerRegions();

	loadStaticTangibleObjects();

	structureManager = new StructureManager(zone, server);
	structureManager->loadStructures();

	weatherManager = new WeatherManager(zone);
	weatherManager->initialize();
}

void PlanetManagerImplementation::loadLuaConfig() {
	String planetName = zone->getZoneName();

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/planet_manager.lua");

	//Get's the configuration settings object for this planet.
	LuaObject luaObject = lua->getGlobalObject(planetName);

	if (luaObject.isValidTable()) {
		LuaObject planetTravelPointsTable = luaObject.getObjectField("planetTravelPoints");
		planetTravelPointList.readLuaObject(&planetTravelPointsTable);
		planetTravelPointsTable.pop();

		loadSnapshotObjects();
	} else {
		warning("Configuration settings not found.");
	}

	luaObject.pop();

	delete lua;
	lua = NULL;
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

	Vector<DataTableRow*> rows = dtiff.getRowsByColumn(0, zone->getZoneName());

	if (rows.size() <= 0) {
		warning("Travel fares could not be found.");
		return;
	}

	DataTableRow* row = rows.get(0);

	//We want to skip the initial column.
	for (int i = 1; i < dtiff.getTotalColumns(); ++i) {
		String planetName = dtiff.getColumnNameByIndex(i);
		int fare = 0;
		row->getCell(i)->getValue(fare);

		travelFares.put(planetName, fare);
	}

	info("Loaded travel fares to " + String::valueOf(travelFares.size()) + " planets.");
}

void PlanetManagerImplementation::loadSnapshotObject(WorldSnapshotNode* node, WorldSnapshotIff* wsiff, int& totalObjects) {
	uint64 objectID = node->getObjectID();
	String templateName = wsiff->getObjectTemplateName(node->getNameID());

	ZoneServer* zoneServer = server->getZoneServer();

	SceneObject* object = zoneServer->getObject(objectID);

	//Object already exists, exit.
	if (object != NULL)
		return;

	SceneObject* parentObject = zoneServer->getObject(node->getParentID());

	String serverTemplate = templateName.replaceFirst("shared_", "");
	Vector3 position = node->getPosition();

	object = zoneServer->createClientObject(serverTemplate.hashCode(), objectID);

	object->initializePosition(position.getX(), position.getZ(), position.getY());
	object->setDirection(node->getDirection());

	if (parentObject != NULL)
		parentObject->addObject(object, -1);

	if (parentObject == NULL || parentObject->isCellObject())
		object->insertToZone(zone);

	//Load child nodes
	for (int i = 0; i < node->getNodeCount(); ++i) {
		WorldSnapshotNode* childNode = node->getNode(i);

		if (childNode == NULL)
			continue;

		loadSnapshotObject(childNode, wsiff, totalObjects);
	}

	object->createChildObjects();

	++totalObjects;
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

	for (int i = 0; i < wsiff.getNodeCount(); ++i) {
		WorldSnapshotNode* node = wsiff.getNode(i);

		if (node == NULL)
			continue;

		loadSnapshotObject(node, &wsiff, totalObjects);
	}

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

	//If both zones are the same, then intraplanetary travel is allowed.
	if (arrivalZone == zone)
			return true;

	//Check to see if interplanetary travel is allowed between both points.
	if (!isInterplanetaryTravelAllowed(departurePoint) || !arrivalPlanetManager->isInterplanetaryTravelAllowed(arrivalPoint))
		return false;

	return true;
}

void PlanetManagerImplementation::sendPlanetTravelPointListResponse(PlayerCreature* player) {
	PlanetTravelPointListResponse* ptplr = new PlanetTravelPointListResponse(zone->getZoneName());
	planetTravelPointList.insertToMessage(ptplr);

	player->sendMessage(ptplr);
}

PlanetTravelPoint* PlanetManagerImplementation::getNearestPlanetTravelPoint(SceneObject* object, float range) {
	Reference<PlanetTravelPoint*> planetTravelPoint = NULL;

	for (int i = 0; i < planetTravelPointList.size(); ++i) {
		Reference<PlanetTravelPoint*> ptp = planetTravelPointList.get(i);

		Coordinate coord;
		coord.setPosition(ptp->getX(), ptp->getZ(), ptp->getY());

		float dist = object->getDistanceTo(&coord);

		if (dist < range) {
			range = dist;
			planetTravelPoint = ptp;
		}
	}

	return planetTravelPoint;
}

void PlanetManagerImplementation::loadStaticTangibleObjects() {
	//TODO: Deprecate this to load from lua files.
}

void PlanetManagerImplementation::loadNoBuildAreas() {
	//TODO: Deprecate. These should be loaded by their objects upon creation.
}

bool PlanetManagerImplementation::isNoBuildArea(float x, float y, StringId& fullAreaName) {
	return noBuildAreaMap.isNoBuildArea(x, y, fullAreaName);
}

void PlanetManagerImplementation::loadClientRegions() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("datatables/clientregion/" + zone->getZoneName() + ".iff");

	if (iffStream == NULL) {
		info("No client regions found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		String regionName;
		float x, y, radius;

		DataTableRow* row = dtiff.getRow(i);
		row->getValue(0, regionName);
		row->getValue(1, x);
		row->getValue(2, y);
		row->getValue(3, radius);

		ManagedReference<CityRegion*> cityRegion = cityRegionMap.get(regionName);

		//If the cityRegion hasn't already been created, then create it.
		if (cityRegion == NULL) {
			cityRegion = new CityRegion(regionName);
			cityRegionMap.put(regionName, cityRegion);
		}

		cityRegion->addActiveArea(zone, x, y, radius);

		//regionMap.addRegion(zone, regionName, x, y, radius);
	}

	info("Added " + String::valueOf(cityRegionMap.size()) + " client regions.");
}

void PlanetManagerImplementation::loadPlayerRegions() {
	StringBuffer msg;
	msg << "PlanetManagerImplementation::loadRegions()";
	info(msg.toString());
	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	//dbManager->loadDatabases();

	ObjectDatabase* cityRegionsDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("cityregions", true);

	if (cityRegionsDatabase == NULL)
		error("PlanetManagerImplementation::loadPlayerRegions(): There was an error loading the 'cityregions' database.");

	info("Loading player regions");

	int i = 0;

	try {
		uint64 currentZoneObjectID = zone->_getObjectID();
		ObjectDatabaseIterator iterator(cityRegionsDatabase);

		uint64 objectID;
		ObjectInputStream* objectData = new ObjectInputStream(2000);

		uint64 zoneObjectID = 0;
		int gameObjectType = 0;

		while (iterator.getNextKeyAndValue(objectID, objectData)) {
			if (!Serializable::getVariable<uint64>("zone", &zoneObjectID, objectData)) {
				objectData->clear();
				continue;
			}

			if (zoneObjectID != currentZoneObjectID) {
				objectData->clear();
				continue;
			}

			SceneObject* object = server->getZoneServer()->getObject(objectID);

			if (object != NULL) {
				//object->info("loaded player structure into world");
				++i;
			} else {
				error("could not load region " + String::hexvalueOf((int64)objectID));
			}

			objectData->clear();
		}

		delete objectData;

	} catch (DatabaseException& e) {
		StringBuffer err;
		err << "Loading Player Structures, exception: " << e.getMessage();
		error(err);
		return;
	}

	numberOfCities += i;

	info(String("Loaded " + String::valueOf(i)) + " player regions", true);
}

void PlanetManagerImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	terrainManager = new TerrainManager(zone);
}


void PlanetManagerImplementation::finalize() {
	delete terrainManager;
	terrainManager = NULL;
}

void PlanetManagerImplementation::loadBadgeAreas() {
}

void PlanetManagerImplementation::loadPerformanceLocations() {
	info("loading performance locations...", true);

	SortedVector<ManagedReference<SceneObject*> > planetaryLocs;
	planetaryLocs.setNoDuplicateInsertPlan();

	// get hotels
	planetaryLocs = zone->getPlanetaryObjectList("hotel");
	for (int j = 0; j < planetaryLocs.size(); j++) {
		SceneObject* obj = planetaryLocs.get(j);
		addPerformanceLocation(obj);
	}

	// get theaters
	planetaryLocs = zone->getPlanetaryObjectList("guild_theater");
	for (int j = 0; j < planetaryLocs.size(); j++) {
		SceneObject* obj = planetaryLocs.get(j);
		addPerformanceLocation(obj);
	}

	// get cantinas
	planetaryLocs.removeAll();
	planetaryLocs = zone->getPlanetaryObjectList("cantina");
	for (int j = 0; j < planetaryLocs.size(); j++) {
		SceneObject* obj = planetaryLocs.get(j);
		addPerformanceLocation(obj);
	}
}

void PlanetManagerImplementation::loadHuntingTargets() {
}


void PlanetManagerImplementation::loadReconLocations() {
	info("loading recon locations ...", true);
}

