/*
 * PlanetManagerImplementation.cpp
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#include "PlanetManager.h"
#include "server/zone/objects/terrain/PlanetNames.h"

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
#include "server/zone/packets/player/TravelListResponseMessage.h"
#include "server/zone/objects/area/BadgeActiveArea.h"

void PlanetManagerImplementation::initialize() {
	terrainManager = new TerrainManager(zone);

	shuttleMap = new ShuttleMap();

	noBuildAreaMap = new NoBuildAreaMap();

	missionNpcs = new MissionTargetMap();

	performanceLocations = new MissionTargetMap();

	huntingTargets = new HuntingTargetMap();

	reconLocs = new MissionTargetMap();
	informants = new MissionTargetMap();

	int zoneID = zone->getZoneID();

	numberOfCities = 0;

	info("Loading planet...", true);

	//TODO: Load from the TRE files.
	if (terrainManager->initialize("terrain/" + zone->getPlanetName() + ".trn"))
		info("Loaded terrain file successfully.", true);
	else
		error("Failed to load terrain file.");

	loadLuaConfig();
	loadTravelFares();

	/*loadRegions();
	loadBadgeAreas();
	loadNoBuildAreas();
	loadPerformanceLocations();
	loadHuntingTargets();
	loadReconLocations();
	loadPlayerRegions();

	loadStaticTangibleObjects();*/

	structureManager = new StructureManager(zone, server);
	//structureManager->loadStructures();

	if (zone->getZoneID() < 10) { //No need for a weather manager in tutorial or corvette etc.
		weatherManager = new WeatherManager(zone);
		//weatherManager->initialize();
	}
}

void PlanetManagerImplementation::loadLuaConfig() {
	String planetName = zone->getPlanetName();

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/planet_manager.lua");

	//Get's the configuration settings object for this planet.
	LuaObject luaObject = lua->getGlobalObject(planetName);

	if (luaObject.isValidTable()) {
		if (luaObject.getIntField("loadClientObjects") > 0)
			loadSnapshotObjects();
		else
			info("Client object loading disabled.", true);

		luaObject.pop();
	} else {
		info("Configuration settings not found.", true);
	}

	delete lua;
	lua = NULL;
}

void PlanetManagerImplementation::loadTravelFares() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("datatables/travel/travel.iff");

	if (iffStream == NULL) {
		info("Travel fares could not be found.", true);
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	Vector<DataTableRow*> rows = dtiff.getRowsByColumn(0, zone->getPlanetName());

	if (rows.size() <= 0) {
		info("Travel fares could not be found.", true);
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

	info("Loaded travel fares to " + String::valueOf(travelFares.size()) + " planets.", true);
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

	object->createChildObjects();

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

	++totalObjects;
}

void PlanetManagerImplementation::loadSnapshotObjects() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("snapshot/" + zone->getPlanetName() + ".ws");

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

void PlanetManagerImplementation::loadStaticTangibleObjects() {
	//TODO: Deprecate this to load from lua files.
	StringBuffer query;

	query << "SELECT * FROM statictangibleobjects WHERE zoneid = " << zone->getZoneID() << ";";

	Reference<ResultSet*> result = NULL;

	int i = 0;

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			uint64 parentid = result->getUnsignedLong(2);
			String name = result->getString(3);
			String templateFile = result->getString(4);
			int templateType = result->getInt(5);
			String templateName = result->getString(6);
			float ox = result->getFloat(7);
			float oy = result->getFloat(8);
			float oz = result->getFloat(9);
			float ow = result->getFloat(10);
			float x = result->getFloat(11);
			float z = result->getFloat(12);
			float y = result->getFloat(13);

			if (z == 0 && parentid == 0)
				z = zone->getHeight(x, y);

			ManagedReference<SceneObject*> object = server->getZoneServer()->createObject(templateFile.hashCode(), 1);;

			if (object == NULL) {
				error("trying to spawn unknown tangible object " + templateFile);
			} else {
				ManagedReference<SceneObject*> parentObject;

				if (parentid != 0) {
					parentObject = server->getZoneServer()->getObject(parentid);

					if (parentObject != NULL && !parentObject->isCellObject()) {
						error("trying to set a parent that is not a cell to tangible objects");
						parentObject = NULL;
					}
				}

				if (parentObject != NULL)
					parentObject->addObject(object, -1);

				if (!name.isEmpty())
					object->setCustomObjectName(name, true);

				object->initializePosition(x, z, y);
				object->setDirection(ow, ox, oy, oz);

				object->insertToZone(zone);

				++i;
			}

		}

	} catch (Exception& e) {
		error(e.getMessage());
	}

	info("static creatures spawned: " + String::valueOf(i), true);
}

void PlanetManagerImplementation::loadNoBuildAreas() {
	//TODO: Deprecate. These should be loaded by their objects upon creation.
	StringBuffer query;
	query << "SELECT * FROM no_build_zones WHERE planet_id = " << zone->getZoneID() << ";";

	Reference<ResultSet*> result = ServerDatabase::instance()->executeQuery(query);

	while (result->next()) {
		float x = result->getFloat(5);
		float y = result->getFloat(6);
		float radius = result->getFloat(7);

		String zoneType = result->getString(4);
		String file = result->getString(3);
		String name = result->getString(2);

		if (zoneType == "poi_badge") {
			name = file;
			file = "clientpoi_n";
		} if (zoneType == "poi") {
			file = "clientpoi_n";
		}

		String fullName = "@" + file + ":" + name;

		uint32 crc = String("object/region_area.iff").hashCode();

		Region* region = (Region*) ObjectManager::instance()->createObject(crc, 0, "");
		region->initializePosition(x, 0, y);
		region->setRadius(radius);
		region->setClientObject(true);
		StringId* objectName = region->getObjectName();
		objectName->setStringId(fullName);

		//Region* region = new Region(fullName, x, y, radius /* + 300 */);
		//region->deploy();
		noBuildAreaMap->add(region);

		//addNoBuildArea(x, y, radius + 300); // Adding 500 as a buffer for spawns since this patch doesn't need buildings
	}
}

bool PlanetManagerImplementation::isNoBuildArea(float x, float y, StringId& fullAreaName) {
	return noBuildAreaMap->isNoBuildArea(x, y, fullAreaName);
}

void PlanetManagerImplementation::loadRegions() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("datatables/clientregion/" + zone->getPlanetName() + ".iff");

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
		int planetid = zone->getZoneID();
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

void PlanetManagerImplementation::loadShuttles() {
	info("loading shuttles", true);

	int planetid = zone->getZoneID();
	String planetName = Planet::getPlanetName(zone->getZoneID());

	CreatureManager* creatureManager = zone->getCreatureManager();

	Locker locker(_this);

	try {
		StringBuffer query;
		query << "SELECT * FROM transports WHERE planet_id = " << planetid << ";";

		Reference<ResultSet*> shut = ServerDatabase::instance()->executeQuery(query);

		while (shut->next()) {
			uint32 shuttleId = shut->getUnsignedInt(0);
			String shuttleName = shut->getString(2);
			uint64 shuttleParentId = shut->getUnsignedLong(3);
			float shuttlePosX = shut->getFloat(4);
			float shuttlePosY = shut->getFloat(5);
			float shuttlePosZ = shut->getFloat(6);
			float shuttleDirY = shut->getFloat(7);
			float shuttleDirW = shut->getFloat(8);
			float playerSpawnX = shut->getFloat(9);
			float playerSpawnY = shut->getFloat(10);
			float playerSpawnZ = shut->getFloat(11);
			bool starport = shut->getInt(12);
			uint32	tax = shut->getInt(13);
			uint64 shuttleCRC = shut->getUnsignedLong(14);

			CreatureObject* creatureObject = creatureManager->spawnCreature(shuttleCRC, shuttlePosX, shuttlePosZ, shuttlePosY, shuttleParentId);

			if (creatureObject == NULL || !creatureObject->isShuttleCreature()) {
				error("wrong crc");

				continue;
			}

			ShuttleCreature* shuttle = (ShuttleCreature*) creatureObject;

			shuttle->setDirection(shuttleDirW, 0, shuttleDirY, 0);
			shuttle->setArrivalPoint(playerSpawnX, playerSpawnY, playerSpawnZ);
			shuttle->setStarport(starport);
			shuttle->setTax(tax);
			shuttle->setPlanet(planetName);
			shuttle->setCity(shuttleName);

			shuttleMap->put(shuttleName, shuttle);

			shuttle->doTakeOff();

			StringBuffer query2;
			query2 << "SELECT parent, pos_x, pos_y, pos_z, dir_y, dir_w FROM ticket_collectors WHERE transport_id = " << shuttleId << ";";

			Reference<ResultSet*> collectors = ServerDatabase::instance()->executeQuery(query2);

			while (collectors->next()) {
				uint64 collCellId = collectors->getUnsignedLong(0);
				float collPosX = collectors->getFloat(1);
				float collPosY = collectors->getFloat(2);
				float collPosZ = collectors->getFloat(3);
				float collDirY = collectors->getFloat(4);
				float collDirW = collectors->getFloat(5);

				TicketCollector* colector = (TicketCollector*) zone->getZoneServer()->createObject(String("object/tangible/travel/ticket_collector/ticket_collector.iff").hashCode(), 0);
				SceneObject* cell = zone->getZoneServer()->getObject(collCellId);

				if (cell != NULL)
					cell->addObject(colector, -1);

				colector->setDirection(collDirW, 0, collDirY, 0);
				colector->initializePosition(collPosX, collPosZ, collPosY);
				colector->insertToZone(zone);
				colector->setShuttle(shuttle);
			}

			StringBuffer query3;
			query3 << "SELECT parent, pos_x, pos_y, pos_z, dir_y, dir_w FROM ticket_terminals WHERE transport_id = " << shuttleId << ";";

			Reference<ResultSet*> terminals = ServerDatabase::instance()->executeQuery(query3);

			while (terminals->next()) {
				uint64 termCellId = terminals->getUnsignedLong(0);
				float termPosX = terminals->getFloat(1);
				float termPosY = terminals->getFloat(2);
				float termPosZ = terminals->getFloat(3);
				float termDirY = terminals->getFloat(4);
				float termDirW = terminals->getFloat(5);

				TravelTerminal* travel = (TravelTerminal*) zone->getZoneServer()->createObject(String("object/tangible/terminal/terminal_travel.iff").hashCode(), 0);
				SceneObject* cellPar = zone->getZoneServer()->getObject(termCellId);

				if (cellPar != NULL)
					cellPar->addObject(travel, -1);

				travel->setShuttle(shuttle);
				travel->setDirection(termDirW, 0, termDirY, 0);
				travel->initializePosition(termPosX, termPosZ, termPosY);
				travel->insertToZone(zone);
			}

		}
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}
}

void PlanetManagerImplementation::sendPlanetTravelPointListResponse(PlayerCreature* player) {
	lock();

	TravelListResponseMessage* msg = new TravelListResponseMessage(Planet::getPlanetName(zone->getZoneID()));

	HashTableIterator<String,  ManagedReference<ShuttleCreature*> > iter = shuttleMap->iterator();

	while (iter.hasNext()) {
		ShuttleCreature* shuttle = iter.getNextValue();

		float x, y, z;
		shuttle->getArrivalPoint(x, y, z);

		msg->addPoint(shuttle->getCity(), x, z, y, shuttle->getTax(), shuttle->isStarport());
	}

	unlock();

	msg->generateMessage();

	player->sendMessage(msg);
}


void PlanetManagerImplementation::loadBadgeAreas() {
	StringBuffer query;
	query << "SELECT x, y, z, badge_id FROM badge_areas WHERE planet_id = " << zone->getZoneID() << ";";

	Reference<ResultSet*> result = ServerDatabase::instance()->executeQuery(query);

	uint32 crc = String("object/badge_area.iff").hashCode();

	while (result->next()) {

		float x = result->getFloat(0);
		float y = result->getFloat(1);
		float z = result->getFloat(2);
		uint32 badgeId = result->getInt(3);

		BadgeActiveArea* area = (BadgeActiveArea*) zone->getZoneServer()->createObject(crc, 0);
		area->setBadge(badgeId);
		area->setRadius(100);
		area->initializePosition(x, z, y);
		area->insertToZone(zone);
	}
}

void PlanetManagerImplementation::loadPerformanceLocations() {
	info("loading performance locations...", true);

	SortedVector<ManagedReference<SceneObject*> > planetaryLocs;
	planetaryLocs.setNoDuplicateInsertPlan();

	// get hotels
	planetaryLocs = zone->getPlanetaryObjectList(12);
	for (int j = 0; j < planetaryLocs.size(); j++) {
		SceneObject* obj = planetaryLocs.get(j);
		addPerformanceLocation(obj);
	}

	// get theaters
	planetaryLocs = zone->getPlanetaryObjectList(10);
	for (int j = 0; j < planetaryLocs.size(); j++) {
		SceneObject* obj = planetaryLocs.get(j);
		addPerformanceLocation(obj);
	}

	// get cantinas
	planetaryLocs.removeAll();
	planetaryLocs = zone->getPlanetaryObjectList(3);
	for (int j = 0; j < planetaryLocs.size(); j++) {
		SceneObject* obj = planetaryLocs.get(j);
		addPerformanceLocation(obj);
	}
}

void PlanetManagerImplementation::loadHuntingTargets() {
	StringBuffer query;
	query << "SELECT file1,file2,level from mission_manager_hunt_types WHERE zoneid=" << zone->getZoneID() << ";";

	Reference<ResultSet*> result = NULL;

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			String templateName = result->getString(0);
			String templateNameAlt = result->getString(1);
			int level = result->getInt(2);

			addHuntingTargetTemplate(templateName, templateNameAlt, level);
		}
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}
}


void PlanetManagerImplementation::loadReconLocations() {
	info("loading recon locations ...", true);

	StringBuffer query;
	query << "SELECT * from mission_manager_recon_locs WHERE zoneid=" << zone->getZoneID() << ";";

	Reference<ResultSet*> result = NULL;

	ManagedReference<TangibleObject*> location = NULL;

	try {
		result = ServerDatabase::instance()->executeQuery(query);
		int i = 0;

		while (result->next()) {
			String tempName = result->getString(2);
			int tempType = result->getInt(3);
			float ox = result->getFloat(4);
			float oy = result->getFloat(5);
			float oz = result->getFloat(6);
			float ow = result->getFloat(7);
			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);

			location = dynamic_cast<TangibleObject*>(zone->getZoneServer()->createObject(tempName.hashCode(), 1));

			location->initializePosition(x, zone->getHeight(x, y), y);
			location->setDirection(ow, ox, oy, oz);
			location->setOptionsBitmask(0x108);
			location->setPvpStatusBitmask(0);
			location->insertToZone(zone);

			location->updateToDatabase();

			addReconLoc(location);

			++i;
		}

		if (i > 0)
			info(String::valueOf(i) + " recon locations loaded", true);
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}
}


