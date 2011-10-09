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
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/packets/player/PlanetTravelPointListResponse.h"
#include "server/zone/objects/area/BadgeActiveArea.h"

#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"

#include "PlanetTravelPoint.h"

void PlanetManagerImplementation::initialize() {
	terrainManager = new TerrainManager(zone);

	noBuildAreaMap = new NoBuildAreaMap();

	missionNpcs = new MissionTargetMap();

	performanceLocations = new MissionTargetMap();

	huntingTargets = new HuntingTargetMap();

	reconLocs = new MissionTargetMap();
	informants = new MissionTargetMap();

	numberOfCities = 0;

	info("Loading planet.");

	if (terrainManager->initialize("terrain/" + zone->getZoneName() + ".trn"))
		info("Loaded terrain file successfully.");
	else
		error("Failed to load terrain file.");

	planetTravelPointList->setZoneName(zone->getZoneName());

	loadClientRegions();
	loadLuaConfig();
	loadTravelFares();

	loadBadgeAreas();
	loadNoBuildAreas();
	loadPerformanceLocations();
	loadHuntingTargets();
	loadReconLocations();
	loadPlayerRegions();

	loadStaticTangibleObjects();

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
		planetTravelPointList->readLuaObject(&planetTravelPointsTable);
		planetTravelPointsTable.pop();

		loadSnapshotObjects();

		LuaObject planetObjectsTable = luaObject.getObjectField("planetObjects");
		loadPlanetObjects(&planetObjectsTable);
		planetObjectsTable.pop();
	} else {
		warning("Configuration settings not found.");
	}

	luaObject.pop();

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

		ManagedReference<SceneObject*> obj = cast<SceneObject*>( ObjectManager::instance()->createObject(templateFile.hashCode(), 0, ""));

		if (obj != NULL) {
			float x = planetObject.getFloatField("x");
			float y = planetObject.getFloatField("y");
			float z = planetObject.getFloatField("z");
			float ox = planetObject.getFloatField("ox");
			float oy = planetObject.getFloatField("oy");
			float oz = planetObject.getFloatField("oz");
			float ow = planetObject.getFloatField("ow");
			uint64 parentID = planetObject.getLongField("parent");

			obj->initializePosition(x, z, y);
			obj->setDirection(ow, ox, oy, oz);
			//TODO: Parent
			//obj->insertToZone(zone);
			zone->addObject(obj, -1, true);
		}

		planetObject.pop();
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

SceneObject* PlanetManagerImplementation::loadSnapshotObject(WorldSnapshotNode* node, WorldSnapshotIff* wsiff, int& totalObjects) {
	uint64 objectID = node->getObjectID();
	String templateName = wsiff->getObjectTemplateName(node->getNameID());

	ZoneServer* zoneServer = server->getZoneServer();

	SceneObject* object = zoneServer->getObject(objectID);

	//Object already exists, exit.
	if (object != NULL)
		return NULL;

	SceneObject* parentObject = zoneServer->getObject(node->getParentID());

	String serverTemplate = templateName.replaceFirst("shared_", "");
	Vector3 position = node->getPosition();

	object = zoneServer->createClientObject(serverTemplate.hashCode(), objectID);

	object->initializePosition(position.getX(), position.getZ(), position.getY());
	object->setDirection(node->getDirection());

	if (parentObject != NULL)
		parentObject->addObject(object, -1);

	if (parentObject == NULL || parentObject->isCellObject())
		//object->insertToZone(zone);
		zone->addObject(object, -1, true);

	//Load child nodes
	for (int i = 0; i < node->getNodeCount(); ++i) {
		WorldSnapshotNode* childNode = node->getNode(i);

		if (childNode == NULL)
			continue;

		loadSnapshotObject(childNode, wsiff, totalObjects);
	}

	//object->createChildObjects();

	++totalObjects;

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

	for (int i = 0; i < objects.size(); ++i)
		objects.get(i)->createChildObjects();

	delete iffStream;

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

void PlanetManagerImplementation::sendPlanetTravelPointListResponse(CreatureObject* player) {
	PlanetTravelPointListResponse* ptplr = new PlanetTravelPointListResponse(zone->getZoneName());
	planetTravelPointList->insertToMessage(ptplr);

	player->sendMessage(ptplr);
}

PlanetTravelPoint* PlanetManagerImplementation::getNearestPlanetTravelPoint(SceneObject* object, float range) {
	Reference<PlanetTravelPoint*> planetTravelPoint = NULL;

	for (int i = 0; i < planetTravelPointList->size(); ++i) {
		Reference<PlanetTravelPoint*> ptp = planetTravelPointList->get(i);

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
	return noBuildAreaMap->isNoBuildArea(x, y, fullAreaName);
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

		ManagedReference<CityRegion*> cityRegion = cityRegionMap->getRegion(regionName);

		//If the cityRegion hasn't already been created, then create it.
		if (cityRegion == NULL) {
			cityRegion = new CityRegion(regionName);
			cityRegionMap->addRegion(cityRegion);
		}

		cityRegion->addActiveArea(zone, x, y, radius);
	}

	info("Added " + String::valueOf(cityRegionMap->getTotalRegions()) + " client regions.");
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

bool PlanetManagerImplementation::isBuildingPermittedAt(float x, float y) {
	if (cityRegionMap->getCityRegionAt(x, y) == NULL)
		return true;

	return false;
}


void PlanetManagerImplementation::loadReconLocations() {
	info("loading recon locations ...", true);
}

SceneObject* PlanetManagerImplementation::createTicket(const String& departurePoint, const String& arrivalPlanet, const String& arrivalPoint) {
	ManagedReference<SceneObject*> obj = server->getZoneServer()->createObject(String("object/tangible/travel/travel_ticket/base/base_travel_ticket.iff").hashCode(), 1);

	if (obj == NULL || !obj->isTangibleObject())
		return NULL;

	TangibleObject* tano = cast<TangibleObject*>( obj.get());

	if (!tano->isTicketObject())
		return tano;

	TicketObject* ticket = cast<TicketObject*>( tano);
	ticket->setDeparturePlanet(zone->getZoneName());
	ticket->setDeparturePoint(departurePoint);
	ticket->setArrivalPlanet(arrivalPlanet);
	ticket->setArrivalPoint(arrivalPoint);

	return ticket;
}

bool PlanetManagerImplementation::checkShuttleStatus(CreatureObject* creature, CreatureObject* shuttle) {
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
