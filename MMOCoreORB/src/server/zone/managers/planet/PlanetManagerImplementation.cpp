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

#include "server/zone/objects/tangible/terminal/ticketcollector/TicketCollector.h"
#include "server/zone/objects/tangible/terminal/travel/TravelTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/packets/player/PlanetTravelPointListResponse.h"
#include "server/zone/objects/area/BadgeActiveArea.h"

void PlanetManagerImplementation::initialize() {
	terrainManager = new TerrainManager(zone);

	numberOfCities = 0;

	info("Loading planet.");

	//TODO: Load from the TRE files.
	if (terrainManager->initialize("terrain/" + zone->getZoneName() + ".trn"))
		info("Loaded terrain file successfully.");
	else
		error("Failed to load terrain file.");

	loadRegions();

	loadLuaConfig();
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
		if (luaObject.getIntField("loadClientObjects") > 0)
			loadSnapshotObjects();
		else
			info("Client object loading disabled.");

		luaObject.pop();
	} else {
		warning("Configuration settings not found.");
	}

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

void PlanetManagerImplementation::startTravelRoutes() {
	//Load shuttleports first.
	SortedVector<ManagedReference<SceneObject*> > objs = zone->getPlanetaryObjectList("shuttleport");

	for (int i = 0; i < objs.size(); ++i)
		scheduleShuttleRoute(objs.get(i));

	//Now do the starports.
	objs = zone->getPlanetaryObjectList("starport");

	for (int i = 0; i < objs.size(); ++i)
		scheduleShuttleRoute(objs.get(i));
}

void PlanetManagerImplementation::scheduleShuttleRoute(SceneObject* starport) {
	//All starports have their shuttles outdoors, for obvious reasons, except for Theed...
	//SortedVector<ManagedReference<SceneObject*> > outdoorObjects = starport->getOutdoorChildObjects();

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

void PlanetManagerImplementation::loadRegions() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("datatables/clientregion/" + zone->getZoneName() + ".iff");

	if (iffStream == NULL) {
		info("No client regions found.", true);
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		String regionName;
		float x, y, radius;

		DataTableRow* row = dtiff.getRow(i);
		row->getCell(0)->getValue(regionName);
		row->getCell(1)->getValue(x);
		row->getCell(2)->getValue(y);
		row->getCell(3)->getValue(radius);

		regionMap.addRegion(zone, regionName, x, y, radius);
	}

	info("Added " + String::valueOf(regionMap.size()) + " client regions.", true);
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

	info("loading player regions", true);

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

	info(String("loaded " + String::valueOf(i)) + " player regions", true);
}

void PlanetManagerImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	terrainManager = new TerrainManager(zone);
}


void PlanetManagerImplementation::finalize() {
	delete terrainManager;
	terrainManager = NULL;
}

void PlanetManagerImplementation::sendPlanetTravelPointListResponse(PlayerCreature* player) {

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

