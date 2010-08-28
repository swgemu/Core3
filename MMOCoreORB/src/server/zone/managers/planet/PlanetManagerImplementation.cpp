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
#include "server/zone/objects/tangible/terminal/ticketcollector/TicketCollector.h"
#include "server/zone/objects/tangible/terminal/travel/TravelTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/player/TravelListResponseMessage.h"
#include "server/zone/objects/area/BadgeActiveArea.h"
#include "TravelFare.h"

void PlanetManagerImplementation::initialize() {
	terrainManager = new TerrainManager(zone);

	int zoneID = zone->getZoneID();

	if (zoneID < 10) {
		String planetName = Planet::getPlanetName(zoneID);

		setLoggingName("PlanetManager " + planetName);

		terrainManager->initialize("planets/" + planetName + "/" + planetName + ".trn");
	}

	info("loading planet...", true);

	loadRegions();
	loadBadgeAreas();
	loadNoBuildAreas();
	loadPerformanceLocations();
	loadHuntingTargets();

	structureManager = new StructureManager(zone, server);
	structureManager->loadStructures();
}


void PlanetManagerImplementation::loadNoBuildAreas() {
	StringBuffer query;
	query << "SELECT * FROM no_build_zones WHERE planet_id = " << zone->getZoneID() << ";";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

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
		region->setStaticObject(true);
		StringId* objectName = region->getObjectName();
		objectName->setStringId(fullName);

		//Region* region = new Region(fullName, x, y, radius /* + 300 */);
		//region->deploy();
		noBuildAreaMap.add(region);

		//addNoBuildArea(x, y, radius + 300); // Adding 500 as a buffer for spawns since this patch doesn't need buildings
	}

	delete result;
}

bool PlanetManagerImplementation::isNoBuildArea(float x, float y, StringId& fullAreaName) {
	return noBuildAreaMap.isNoBuildArea(x, y, fullAreaName);
}

void PlanetManagerImplementation::loadRegions() {
	int zoneID = zone->getZoneID();

	String managerName = "PlanetManager ";
	setLoggingName(managerName + Planet::getPlanetName(zoneID));

	if (zoneID > 9)
		return;

	ResultSet* result = NULL;

	try {
		StringBuffer query;
		query << "SELECT * from clientregion_" << Planet::getPlanetName(zoneID);

		result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			String fullName = result->getString(0);

			float x = result->getFloat(1);
			float y = result->getFloat(2);
			float radius = result->getFloat(3);

			regionMap.addRegion(zone, fullName, x, y, radius);
		}
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unknown exception caught in void PlanetManagerImplementation::loadRegions()");
	}

	delete result;

	if (regionMap.size() != 0) {
		StringBuffer msg;
		msg << "loaded " << regionMap.size() << " client regions";
		info(msg.toString(), true);
	}
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

	lock();
	try {
		StringBuffer query;
		query << "SELECT * FROM transports WHERE planet_id = " << planetid << ";";

		ResultSet* shut = ServerDatabase::instance()->executeQuery(query);

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

			shuttleMap.put(shuttleName, shuttle);

			shuttle->doTakeOff();

			StringBuffer query2;
			query2 << "SELECT parent, pos_x, pos_y, pos_z, dir_y, dir_w FROM ticket_collectors WHERE transport_id = " << shuttleId << ";";

			ResultSet* collectors = ServerDatabase::instance()->executeQuery(query2);

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

			delete collectors;

			StringBuffer query3;
			query3 << "SELECT parent, pos_x, pos_y, pos_z, dir_y, dir_w FROM ticket_terminals WHERE transport_id = " << shuttleId << ";";

			ResultSet* terminals = ServerDatabase::instance()->executeQuery(query3);

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

			delete terminals;

		}

		delete shut;

	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadShuttles()");
	}

	unlock();
}

uint32 PlanetManagerImplementation::getTravelFare(const String& departurePlanet, const String& arrivalPlanet) {
	return travelFare[Planet::getPlanetID(departurePlanet)][Planet::getPlanetID(arrivalPlanet)];
}

void PlanetManagerImplementation::sendPlanetTravelPointListResponse(PlayerCreature* player) {
	lock();

	TravelListResponseMessage* msg = new TravelListResponseMessage(Planet::getPlanetName(zone->getZoneID()));

	shuttleMap.resetIterator();

	while (shuttleMap.hasNext()) {
		ShuttleCreature* shuttle = shuttleMap.getNextValue();

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

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

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

	delete result;
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

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	while (result->next()) {
		String templateName = result->getString(0);
		String templateNameAlt = result->getString(1);
		int level = result->getInt(2);

		addHuntingTargetTemplate(templateName, templateNameAlt, level);
	}

	delete result;
}

