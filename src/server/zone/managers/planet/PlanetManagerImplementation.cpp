/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
 */

#include "events/ShuttleLandingEvent.h"
#include "events/ShuttleTakeOffEvent.h"

#include "events/WeatherChangeEvent.h"
#include "events/WeatherIncreaseEvent.h"
#include "events/WeatherDecreaseEvent.h"

#include "PlanetManagerImplementation.h"

#include "../../ZoneProcessServerImplementation.h"

#include "../../objects.h"

#include "../../objects/terrain/PlanetNames.h"

#include "../../objects/area/ActiveAreaTrigger.h"
#include "../../objects/area/BadgeActiveArea.h"

const uint32 PlanetManagerImplementation::travelFare[10][10] = {
		{ 100, 1000, 2000, 4000,    0,  500,    0,    0,  600, 3000},
		{1000,  100,    0,    0,    0,    0,    0,    0,    0,    0},
		{2000,    0,  100,    0,    0,    0,    0,    0,    0,    0},
		{4000,    0,    0,  100,    0, 1750,    0,    0,    0,    0},
		{   0,    0,    0,    0,  100, 1250,    0,    0, 1250,    0},
		{ 500,    0,    0, 1750, 1250,  100,  300,    0,  500,    0},
		{   0,    0,    0,    0,    0,  300,  100,    0,    0,    0},
		{   0,    0,    0,    0,    0,  300,    0,  100,    0,    0},
		{ 600,    0,    0,    0, 1250,  500,    0,    0,  100,    0},
		{3000,    0,    0,    0,    0,    0,    0,    0,    0,  100}
};

const float PlanetManagerImplementation::windDirection[8][2] = {
		{0.0f, 1.0f},    //N
		{1.0f, 1.0f},   //NE
		{1.0f, 0.0f},    //E
		{1.0f, -1.0f},  //SE
		{0.0f, -1.0f},   //S
		{-1.0f, -1.0f}, //SW
		{-1.0f, 0.0f},   //W
		{-1.0f, 1.0f}   //NW
};

PlanetManagerImplementation::PlanetManagerImplementation(Zone* planet, ZoneProcessServerImplementation* serv) :
	PlanetManagerServant(), Mutex("PlanetManager"), Logger() {
	zone = planet;

	server = serv;

	nextStaticObjectID = 0x50000000;

	shuttleTakeOffEvent = new ShuttleTakeOffEvent(this);
	shuttleLandingEvent = new ShuttleLandingEvent(this);

	weatherChangeEvent = new WeatherChangeEvent(this);
	weatherIncreaseEvent = new WeatherIncreaseEvent(this);
	weatherDecreaseEvent = new WeatherDecreaseEvent(this);

	shuttleMap = new ShuttleMap();
	ticketCollectorMap = new TicketCollectorMap(2000);
	travelTerminalMap = new TravelTerminalMap(2000);
	missionTerminalMap = new MissionTerminalMap(100);
	craftingStationMap.setNullValue(NULL);
	craftingStationMap.setInsertPlan(SortedVector<VectorMapEntry<uint64, CraftingStation*>*>::NO_DUPLICATE);
	staticTangibleObjectMap.setNullValue(NULL);
	staticTangibleObjectMap.setInsertPlan(SortedVector<VectorMapEntry<uint64, TangibleObject*>*>::NO_DUPLICATE);

	noBuildAreaMap = new NoBuildAreaMap();

	creatureManager = planet->getCreatureManager();
	structureManager = new StructureManager(zone, server);

	StringBuffer logName;
	logName << "PlanetManager" << zone->getZoneID();
	setLoggingName(logName.toString());

	windRow = System::random(7);

	if (zone->getZoneID() < 10) {
		weatherWindChange();
		weatherChange();
	}

	setLogging(false);
	setGlobalLogging(true);
}

PlanetManagerImplementation::~PlanetManagerImplementation() {

	if (structureManager != NULL) {
		//structureManager->stop();

		structureManager->finalize();
		structureManager = NULL;
	}

	delete shuttleMap;
	shuttleMap = NULL;

	delete ticketCollectorMap;
	ticketCollectorMap = NULL;

	delete travelTerminalMap;
	travelTerminalMap = NULL;

	delete missionTerminalMap;
	missionTerminalMap = NULL;

	delete noBuildAreaMap;
	noBuildAreaMap = NULL;

	delete shuttleTakeOffEvent;
	shuttleTakeOffEvent = NULL;

	delete shuttleLandingEvent;
	shuttleLandingEvent = NULL;

	delete weatherChangeEvent;
	weatherChangeEvent = NULL;

	delete weatherIncreaseEvent;
	weatherIncreaseEvent = NULL;

	delete weatherDecreaseEvent;
	weatherDecreaseEvent = NULL;
}

void PlanetManagerImplementation::init() {
	structureManager->loadStructures();
}

void PlanetManagerImplementation::start() {
	loadStaticPlanetObjects();

	if (shuttleMap->size() > 0)
		takeOffShuttles();

	loadNoBuildAreas();

	loadBadgeAreas();
}

void PlanetManagerImplementation::stop() {
	lock();

	clearShuttles();
	clearTicketCollectors();
	clearTravelTerminals();
	clearCraftingStations();
	clearStaticTangibleObjects();
	structureManager->unloadStructures();

	unlock();
}

void PlanetManagerImplementation::loadNoBuildAreas() {
	StringBuffer query;
	query << "SELECT x, y, radius FROM no_build_areas WHERE zoneid = " << zone->getZoneID() << ";";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	while (result->next()) {
		float x = result->getFloat(0);
		float y = result->getFloat(1);
		float radius = result->getFloat(2);


		addNoBuildArea(x, y, radius);
	}

	delete result;
}

void PlanetManagerImplementation::loadBadgeAreas() {
	StringBuffer query;
	query << "SELECT x, y, z, badge_id FROM badge_areas WHERE planet_id = " << zone->getZoneID() << ";";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	while (result->next()) {
		float x = result->getFloat(0);
		float y = result->getFloat(1);
		float z = result->getFloat(2);
		uint8 badge_id = result->getInt(3);

		spawnActiveArea(new BadgeActiveArea(x,y,z, 100, badge_id));
	}

	delete result;
}

void PlanetManagerImplementation::addNoBuildArea(float x, float y, float radius) {
	lock();
	try {
		noBuildAreaMap->add(new Area(x, y, 0, radius));
	} catch (Exception e) {
		System::out << "Exception Caught in PlanetManagerImplementation::loadNoBuildAreas: "  << e.getMessage() << endl;
	} catch (...) {
		System::out << "Unspecified Exception Caught in PlanetManagerImplementation::loadNoBuildAreas" << endl;
	}
	unlock();
}

void PlanetManagerImplementation::loadStaticTangibleObjects() {
	lock();

	int planetid = zone->getZoneID();

	StringBuffer query;
	query << "SELECT * FROM statictangibleobjects WHERE zoneid = " << planetid << ";";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	while (result->next()) {
		uint64 parentId = result->getUnsignedLong(2);

		String name = result->getString(3);

		String file = result->getString(4);

		int type = result->getInt(5);

		String templatename = result->getString(6);

		float oX = result->getFloat(7);
		float oY = result->getFloat(8);
		float oZ = result->getFloat(9);
		float oW = result->getFloat(10);

		float x = result->getFloat(11);
		float z = result->getFloat(12);
		float y = result->getFloat(13);

		TangibleObject* tano = new TangibleObject(getNextStaticObjectID(false));

		tano->setName(name);
		tano->setParent(zone->lookupObject(parentId));
		tano->setObjectCRC(file.hashCode());
		tano->initializePosition(x, z, y);
		tano->setDirection(oX, oZ, oY, oW);
		tano->setObjectSubType(type);
		tano->setZoneProcessServer(server);
		tano->insertToZone(zone);

		staticTangibleObjectMap.put(tano->getObjectID(), tano);
	}

	delete result;

	unlock();
}



void PlanetManagerImplementation::clearShuttles() {
	if (shuttleTakeOffEvent->isQueued())
		server->removeEvent(shuttleTakeOffEvent);

	if (shuttleLandingEvent->isQueued())
		server->removeEvent(shuttleLandingEvent);

	shuttleMap->removeAll();
}


void PlanetManagerImplementation::clearTicketCollectors() {
	ticketCollectorMap->resetIterator();

	while (ticketCollectorMap->hasNext()) {
		TicketCollector* ticketCollector = ticketCollectorMap->getNextValue();
		ticketCollector->removeFromZone();

		ticketCollector->removeUndeploymentEvent();

		ticketCollector->finalize();
	}

	ticketCollectorMap->removeAll();

	info("cleared ticketCollectors");
}

void PlanetManagerImplementation::clearTravelTerminals() {
	travelTerminalMap->resetIterator();

	while (travelTerminalMap->hasNext()) {
		TravelTerminal* travelTerminal = travelTerminalMap->getNextValue();
		travelTerminal->removeFromZone();

		travelTerminal->removeUndeploymentEvent();

		travelTerminal->finalize();
	}

	travelTerminalMap->removeAll();

	info("cleared travelTerminals");
}

void PlanetManagerImplementation::clearMissionTerminals() {
	missionTerminalMap->resetIterator();

	while (travelTerminalMap->hasNext()) {
		MissionTerminal* missionTerminal = missionTerminalMap->getNextValue();
		missionTerminal->removeFromZone();

		missionTerminal->finalize();
	}

	missionTerminalMap->removeAll();

	info("cleared missionTerminals");
}

void PlanetManagerImplementation::clearCraftingStations() {
	for (int i = 0; i < craftingStationMap.size(); ++i) {
		CraftingStation* station = craftingStationMap.get(i);

		station->removeFromZone();

		station->removeUndeploymentEvent();

		station->finalize();
	}

	craftingStationMap.removeAll();

	info("cleared craftingStations");
}

void PlanetManagerImplementation::clearStaticTangibleObjects() {
	for (int i = 0; i < staticTangibleObjectMap.size(); ++i) {
		TangibleObject* tano = staticTangibleObjectMap.get(i);

		tano->removeFromZone();

		tano->removeUndeploymentEvent();

		tano->finalize();
	}

	staticTangibleObjectMap.removeAll();

	info("cleared staticTangibleObjectMap");
}

void PlanetManagerImplementation::loadStaticPlanetObjects() {
	loadShuttles();
	loadGuildTerminals();
	//loadVendorTerminals();
	loadCraftingStations();
	//loadMissionTerminals();
	loadStaticTangibleObjects();
	loadCloningTerminals();
	loadInsuranceTerminals();
	loadCloneSpawnPoints();
}

void PlanetManagerImplementation::loadShuttles() {
	int planetid = zone->getZoneID();
	String planetName = Planet::getPlanetName(zone->getZoneID());

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

			Coordinate * spawnCoords = new Coordinate(playerSpawnX, playerSpawnZ, playerSpawnY);

			ShuttleCreature * shuttle = creatureManager->spawnShuttle(planetName, shuttleName, spawnCoords, shuttleParentId, shuttlePosX, shuttlePosY, shuttlePosZ, tax, starport);
			shuttle->setDirection(0, 0, shuttleDirY, shuttleDirW);
			shuttle->setObjectCRC(shuttleCRC);
			shuttleMap->put(shuttleName, shuttle);

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

				TicketCollector * colector = new TicketCollector(shuttle, getNextStaticObjectID(false),
					UnicodeString("Ticket Collector"), "ticket_travel", collPosX, collPosZ, collPosY);
				colector->setZoneProcessServer(server);
				colector->setDirection(0, 0, collDirY, collDirW);
				colector->setParent(zone->lookupObject(collCellId));

				colector->insertToZone(zone);
				ticketCollectorMap->put(colector->getObjectID(), colector);
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

				TravelTerminal * terminal = new TravelTerminal(shuttle, getNextStaticObjectID(false),
									termPosX, termPosZ, termPosY);
				terminal->setZoneProcessServer(server);
				terminal->setDirection(0, 0, termDirY, termDirW);
				terminal->setParent(zone->lookupObject(termCellId));
				terminal->insertToZone(zone);
				travelTerminalMap->put(terminal->getObjectID(), terminal);
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

void PlanetManagerImplementation::loadTrainers() {
}

void PlanetManagerImplementation::loadGuildTerminals() {
	if (zone->getZoneID() == 8) {
		lock();

		//Anchorhead
		GuildTerminal* guildterminal = new GuildTerminal(server->getGuildManager(), getNextStaticObjectID(false), 41, 52, -5352);
		guildterminal->setDirection(0, 0, 0, 0);
		guildterminal->insertToZone(zone);

		guildterminal = new GuildTerminal(server->getGuildManager(), getNextStaticObjectID(false), 43, 52, -5352);
		guildterminal->setDirection(0, 0, 0, 0);
		guildterminal->insertToZone(zone);

		guildterminal = new GuildTerminal(server->getGuildManager(), getNextStaticObjectID(false), 47, 52, -5352);
		guildterminal->setDirection(0, 0, 0, 0);
		guildterminal->insertToZone(zone);

		guildterminal = new GuildTerminal(server->getGuildManager(), getNextStaticObjectID(false), 36, 53, -5351);
		guildterminal->setDirection(0, 0, 0, 0);
		guildterminal->insertToZone(zone);

		unlock();
	}



	if (zone->getZoneID() == 5) {
		lock();

		//Theed
		GuildTerminal* guildterminal = new GuildTerminal(server->getGuildManager(), getNextStaticObjectID(false), -4874, 6.41, 4189);
		guildterminal->setDirection(0, 0, -0.93603, 0.341851);
		guildterminal->insertToZone(zone);

		guildterminal = new GuildTerminal(server->getGuildManager(), getNextStaticObjectID(false), -4875, 6.41, 4190);
		guildterminal->setDirection(0, 0, -0.93603, 0.341851);
		guildterminal->insertToZone(zone);

		guildterminal = new GuildTerminal(server->getGuildManager(), getNextStaticObjectID(false), -4864, 6.41, 4182);
		guildterminal->setDirection(0, 0, -0.93603, 0.341851);
		guildterminal->insertToZone(zone);

		guildterminal = new GuildTerminal(server->getGuildManager(), getNextStaticObjectID(false), -4863, 6.41, 4181);
		guildterminal->setDirection(0, 0, -0.93603, 0.341851);
		guildterminal->insertToZone(zone);

		guildterminal = new GuildTerminal(server->getGuildManager(), getNextStaticObjectID(false), -4843, 6.41, 4164);
		guildterminal->setDirection(0, 0, -0.93603, 0.341851);
		guildterminal->insertToZone(zone);

		guildterminal = new GuildTerminal(server->getGuildManager(), getNextStaticObjectID(false), -4842, 6.41, 4163);
		guildterminal->setDirection(0, 0, -0.93603, 0.341851);
		guildterminal->insertToZone(zone);

		guildterminal = new GuildTerminal(server->getGuildManager(), getNextStaticObjectID(false), -4831, 6.41, 4152);
		guildterminal->setDirection(0, 0, -0.93603, 0.341851);
		guildterminal->insertToZone(zone);

		unlock();
	}

}

void PlanetManagerImplementation::loadCloningTerminals() {
	try {
		lock();

		StringBuffer query;
		query << "SELECT * FROM terminals WHERE type = 5 AND zoneid = " << zone->getZoneID() << " ORDER BY parentid;";

		ResultSet* resultSet = ServerDatabase::instance()->executeQuery(query);

		while (resultSet->next()) {
			uint64 parentId = resultSet->getUnsignedLong(1);

			float oX = resultSet->getFloat(3);
			float oZ = resultSet->getFloat(4);
			float oY = resultSet->getFloat(5);
			float oW = resultSet->getFloat(6);

			float X = resultSet->getFloat(7);
			float Z = resultSet->getFloat(8);
			float Y = resultSet->getFloat(9);

			SceneObject* parentCell = zone->lookupObject(parentId);

			if (parentCell != NULL) {
				SceneObject* buildingCell = parentCell;

				while (buildingCell->getParentID() > 0)
					buildingCell = buildingCell->getParent();

				BuildingObject* building = structureManager->getBuilding(buildingCell->getObjectID());

				if (building != NULL && building->isCloningFacility()) {
					CloningFacility* cloningFacility = (CloningFacility*) building;

					CloningTerminal* cloningTerminal = new CloningTerminal(getNextStaticObjectID(false), X, Z, Y);
					cloningTerminal->setDirection(oX, oZ, oY, oW);
					cloningTerminal->setParent(parentCell);
					cloningTerminal->setCloningFacility(cloningFacility);
					cloningTerminal->insertToZone(zone);

					cloningFacility->addCloningTerminal(cloningTerminal);
				}
			}
		}

		delete resultSet;
		unlock();
	} catch (DatabaseException& e) {
		error(e.getMessage());
		unlock();
	} catch (...) {
		error("Unreported exception caught in PlanetManagerImplementation::loadCloningTerminals()");
		unlock();
	}
}


void PlanetManagerImplementation::loadInsuranceTerminals() {
	try {
		lock();

		StringBuffer query;
		query << "SELECT * FROM terminals WHERE type = 6 AND zoneid = " << zone->getZoneID() << " ORDER BY parentid;";

		ResultSet* resultSet = ServerDatabase::instance()->executeQuery(query);

		while (resultSet->next()) {
			uint64 parentId = resultSet->getUnsignedLong(1);

			float oX = resultSet->getFloat(3);
			float oZ = resultSet->getFloat(4);
			float oY = resultSet->getFloat(5);
			float oW = resultSet->getFloat(6);

			float X = resultSet->getFloat(7);
			float Z = resultSet->getFloat(8);
			float Y = resultSet->getFloat(9);

			SceneObject* parentCell = zone->lookupObject(parentId);

			if (parentCell != NULL) {
				InsuranceTerminal* insuranceTerminal = new InsuranceTerminal(getNextStaticObjectID(false), X, Z, Y);
				insuranceTerminal->setDirection(oX, oZ, oY, oW);
				insuranceTerminal->setParent(parentCell);
				insuranceTerminal->insertToZone(zone);
			}
		}

		delete resultSet;
		unlock();
	} catch (DatabaseException& e) {
		error(e.getMessage());
		unlock();
	} catch (...) {
		error("Unreported exception caught in PlanetManagerImplementation::loadCloningTerminals()");
		unlock();
	}
}

void PlanetManagerImplementation::loadCloneSpawnPoints() {
	try {
		lock();

		StringBuffer query;
		query << "SELECT * FROM clone_spawn_points WHERE zoneid = " << zone->getZoneID() << " ORDER BY parentid;";

		ResultSet* resultSet = ServerDatabase::instance()->executeQuery(query);

		while (resultSet->next()) {
			uint64 parentId = resultSet->getUnsignedLong(8);

			float oX = resultSet->getFloat(1);
			float oZ = resultSet->getFloat(2);
			float oY = resultSet->getFloat(3);
			float oW = resultSet->getFloat(4);

			float X = resultSet->getFloat(5);
			float Z = resultSet->getFloat(6);
			float Y = resultSet->getFloat(7);

			SceneObject* parentCell = zone->lookupObject(parentId);

			if (parentCell != NULL) {
				SceneObject* buildingCell = parentCell;

				while (buildingCell->getParentID() > 0)
					buildingCell = buildingCell->getParent();

				BuildingObject* building = structureManager->getBuilding(buildingCell->getObjectID());

				if (building != NULL && building->isCloningFacility()) {
					CloningFacility* cloningFacility = (CloningFacility*) building;

					CloneSpawnPoint* spawnPoint = new CloneSpawnPoint(X, Z, Y);
					spawnPoint->setDirection(oX, oZ, oY, oW);
					spawnPoint->setParent(parentCell);

					cloningFacility->addSpawnPoint(spawnPoint);
				}
			}
		}

		delete resultSet;
		unlock();
	} catch (DatabaseException& e) {
		error(e.getMessage());
		unlock();
	} catch (...) {
		error("Unreported exception caught in PlanetManagerImplementation::loadCloningTerminals()");
		unlock();
	}
}

void PlanetManagerImplementation::loadVendorTerminals() {
	if (zone->getZoneID() != 8)
		return;

	lock();

	VendorTerminal* vendorTerminal = new VendorTerminal(zone->getZoneServer()->getBazaarManager(), getNextStaticObjectID(false), 46, 52, -5352);
	vendorTerminal->setDirection(0, 0, 0, 0);

	vendorTerminal->setZoneProcessServer(server);

	vendorTerminal->insertToZone(zone);

	unlock();
}

void PlanetManagerImplementation::loadMissionTerminals() {
	//The following code is temporary.
	//TODO: Have a discussion w/ team about having one single "terminal map"

	int planetId = zone->getZoneID();

	if (planetId != 0)
		return;

	lock();

	//tyren start term
	MissionTerminal* missionTerminal = new MissionTerminal(getNextStaticObjectID(false), -5100.0f, 21.0f, -2351.0f, planetId, MissionTerminalImplementation::TMASK_GENERAL);
	missionTerminal->setDirection(0, 0, 0, 0);

	missionTerminal->setZoneProcessServer(server);

	missionTerminal->insertToZone(zone);
	missionTerminalMap->put(missionTerminal->getObjectID(), missionTerminal);

	unlock();
}

void PlanetManagerImplementation::loadCraftingStations() {
	int planetid = zone->getZoneID();

	lock();

	String name;
	uint64 crc;

	StringBuffer query;
	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid << ";";

	try {
		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			uint64 oid = result->getUnsignedLong(1);

			uint64 parentId = result->getUnsignedLong(2);

			String file = result->getString(3);

			float oX = result->getFloat(4);
			float oY = result->getFloat(5);
			float oZ = result->getFloat(6);
			float oW = result->getFloat(7);

			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);

			float type = result->getFloat(11);

			if (file.indexOf("object/tangible/crafting/station/") != -1) {
				crc = file.hashCode();

				name = getStationName(crc);

				CraftingStation* station = new CraftingStation(oid, crc, UnicodeString(name), "public_crafting_station");

				station->setEffectiveness(50);

				station->initializePosition(x, z, y);
				station->setDirection(oX, oZ, oY, oW);
				station->insertToZone(zone);
				zone->registerObject(station);

				zone->getZoneServer()->addObject(station, true);

				craftingStationMap.put(oid, station);
			}
		}

		delete result;
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadCraftingStations()");
	}

	unlock();
}

String PlanetManagerImplementation::getStationName(uint64 crc){
	String name = "";

	if (crc == 0xAF09A3F0)
		name = "Clothing and Armor Public Crafting Station";

	if (crc == 0x2FF7F78B)
		name = "Food and Chemical Public Crafting Station";

	if (crc == 0x17929444)
		name = "Starship Public Crafting Station";

	if (crc == 0x1BABCF4B)
		name = "Structure and Furniture Public Crafting Station";

	if (crc == 0x72719FEA)
		name = "Weapon, Droid, and General Public Crafting Station";

	return name;
}

void PlanetManagerImplementation::placePlayerStructure(Player * player,
		uint64 objectID, float x, float y, int orient) {
	try {

		if (isNoBuildArea(x,y)) {
			player->sendSystemMessage("You can not build here.");
			return;
		}

		DeedObject * deed = (DeedObject*) player->getInventoryItem(objectID);

		if (deed == NULL)
			return;

		float oX, oY, oZ, oW;

		switch(orient) {
			case 0:
				oX = 0;
				oY = 0;
				oZ = 0;
				oW = 1;
				break;
			case 1:
				oX = 0;
				oY = 0.707106;
				oZ = 0;
				oW = 0.707106;
				break;
			case 2:
				oX = 0;
				oY = 1;
				oZ = 0;
				oW = 0;
				break;
			case 3:
				oX = 0;
				oY = -0.707106;
				oZ = 0;
				oW = 0.707106;
				break;
		}

		structureManager->spawnTempStructure(player, deed, x, zone->getHeight(x, y), y, oX, oZ, oY, oW);
	}
	catch(...) {
		System::out << "Exception in PlanetManagerImplementation::placePlayerStructure\n";
	}
}



void PlanetManagerImplementation::landShuttles() {
	lock();

	shuttleMap->resetIterator();

	while (shuttleMap->hasNext()) {
		ShuttleCreature* shuttle = shuttleMap->getNextValue();
		try {
			shuttle->wlock();

			shuttle->doLanding();

			shuttle->unlock();
		} catch (...) {
			error("exception in PlanetManagerImplementation::landShuttles()");
			shuttle->unlock();
		}
	}

	server->addEvent(shuttleTakeOffEvent, 90000); // time + 30 of the landing animation

	unlock();
}

void PlanetManagerImplementation::takeOffShuttles() {
	lock();

	shuttleMap->resetIterator();

	while (shuttleMap->hasNext()) {
		ShuttleCreature* shuttle = shuttleMap->getNextValue();
		try {
			shuttle->wlock();

			shuttle->doTakeOff();

			shuttle->unlock();
		} catch (...) {
			error("exception in PlanetManagerImplementation::takeOffShuttles()");
			shuttle->unlock();
		}
	}

	server->addEvent(shuttleLandingEvent, 300000);

	unlock();
}

void PlanetManagerImplementation::sendPlanetTravelPointListResponse(Player* player) {
	lock();

	TravelListResponseMessage* msg = new TravelListResponseMessage(Planet::getPlanetName(zone->getZoneID()));

	shuttleMap->resetIterator();

	while (shuttleMap->hasNext()) {
		ShuttleCreature* shuttle = shuttleMap->getNextValue();

		Coordinate * arrivalPoint = shuttle->getArrivalPoint();

		msg->addPoint(shuttle->getCity(), arrivalPoint->getPositionX(), arrivalPoint->getPositionZ(), arrivalPoint->getPositionY(), shuttle->getTax(), shuttle->isStarport());
	}

	unlock();

	msg->generateMessage();

	player->sendMessage(msg);
}

int64 PlanetManagerImplementation::getLandingTime() {
	lock();

	Time landing;

	landing = shuttleLandingEvent->getTimeStamp();

	unlock();

	return landing.miliDifference();
}

ShuttleCreature* PlanetManagerImplementation::getShuttle(const String& Shuttle) {
	lock();

	ShuttleCreature* shuttle = shuttleMap->get(Shuttle);

	unlock();

	return shuttle;
}

uint64 PlanetManagerImplementation::getNextStaticObjectID(bool doLock) {
	lock(doLock);

	//uint64 nextId = ++nextStaticObjectID;

	uint64 nextId = server->getZoneServer()->getNextID();
	//uint64 nextId = server->getZoneServer()->getNextCreatureID();

	unlock(doLock);

	return nextId;
}

bool PlanetManagerImplementation::isNoBuildArea(float x, float y) {
	return noBuildAreaMap->isNoBuildArea(x,y);
}

void PlanetManagerImplementation::weatherChange() {
	if (!zone->isWeatherEnabled())
			return;

	//Set the desired target weather.
    int random = System::random(99);

    if (random < 75) { //Set clear weather. //75%
    	targetWeatherID = 0;

    } else if (random >= 75 && random < 85){ //Set cloudy weather. //10%
    	targetWeatherID = 1;

    } else if (random >= 85 && random < 94) { //Set light storm. //9%
    	targetWeatherID = 2;

    } else if (random >= 94 && random < 98) { //Set moderate storm. //4%
    	targetWeatherID = 3;

    } else if (random >= 98) { //Set severe storm. //2%
    	targetWeatherID = 4;
    }

    uint32 currentWeatherID = zone->getWeatherID();
	int weatherDifference = (int)targetWeatherID - (int)currentWeatherID;

	if (weatherDifference < 0) {
		weatherTransition(-1); //Decrease the weather severity.

	} else if (weatherDifference > 0) {
		weatherTransition(1); //Increase the weather severity.
	}

	//Queue the next weather change.
    uint32 newWeatherDelay = 2700000 + System::random(4500000); //45-120 minutes
    server->addEvent(weatherChangeEvent, newWeatherDelay);
}

void PlanetManagerImplementation::weatherTransition(int direction) {
	if (!zone->isWeatherEnabled())
			return;

	zone->changeWeatherID(direction);

	if (zone->getWeatherID() >= 3 && System::random(2) == 2)
		weatherWindChange();

	weatherUpdatePlayers();

    //See if we need to queue another increase or decrease event.
    uint32 currentWeatherID = zone->getWeatherID();
	int weatherDifference = (int)targetWeatherID - (int)currentWeatherID;

	int delay = 180000 + System::random(600000); //3-13 minutes
    if (weatherDifference < 0) { //Decrease the weather severity.
		server->addEvent(weatherDecreaseEvent, delay);
	}

	if (weatherDifference > 0) { //Increase the weather severity.
		server->addEvent(weatherIncreaseEvent, delay);
	}
}

void PlanetManagerImplementation::weatherWindChange() {
	if (windRow == 0) {
		switch (System::random(1)) {
			case 0:
				windRow = 1;
				break;
			case 1:
				windRow = 7;
				break;
		}

	} else if (windRow == 7) {
		switch (System::random(1)) {
		case 0:
			windRow = 6;
			break;
		case 1:
			windRow = 0;
			break;
		}

	} else if (windRow > 0 && windRow < 7){
		switch (System::random(1)) {
		case 0:
			windRow++;
			break;
        case 1:
			windRow--;
			break;
		}

	} else {
		windRow = 2;
	}
	zone->setWeatherWindX(windDirection[windRow][0]);
    zone->setWeatherWindY(windDirection[windRow][1]);
}

void PlanetManagerImplementation::weatherUpdatePlayers() {
    bool serverLoading = zone->getZoneServer()->isServerLoading();
    if (serverLoading)
    	return;

    playerManager = server->getPlayerManager();
    if (playerManager == NULL)
    	return;

    playerMap = playerManager->getPlayerMap();
    if (playerMap == NULL)
    	return;

    try {
    	playerMap->lock();
    	playerMap->resetIterator(false);
    	Player* player;

    	while (playerMap->hasNext(false)) {
    		player = playerMap->next(false);

    		if (player != NULL) {
    			playerMap->unlock();

    			try {
    				player->wlock();

    				int playerZone = player->getZoneIndex();

    				if (playerZone == zone->getZoneID() && player->isOnline() && !player->isLoading()) {
    					player->updateWeather();
    				}

    				player->unlock();

    			} catch (...) {
    				player->unlock();
    			}

    			playerMap->lock();
    		}
    	}

    	playerMap->unlock();

    } catch (...) {
    	error("unreported exception caught in PlanetManagerImplementation::updatePlayerWeather()");
    	playerMap->unlock();
    }
}

void PlanetManagerImplementation::weatherRemoveEvents() {
	if (weatherChangeEvent->isQueued()) {
		server->removeEvent(weatherChangeEvent);
	}

	if (weatherIncreaseEvent->isQueued()) {
		server->removeEvent(weatherIncreaseEvent);
	}

	if (weatherDecreaseEvent->isQueued()) {
		server->removeEvent(weatherDecreaseEvent);
	}
}

ActiveAreaTrigger* PlanetManagerImplementation::spawnActiveArea(ActiveArea * area) {

	lock();

	ActiveAreaTrigger * trigger = new ActiveAreaTrigger(area);

	trigger->setObjectID(getNextStaticObjectID(false));
	trigger->initializePosition(area->getX(), area->getZ(), area->getY());
	trigger->setZoneProcessServer(server);
	trigger->insertToZone(zone);

	unlock();

	return trigger;
}

void PlanetManagerImplementation::removeActiveAreaTrigger(ActiveAreaTrigger* trigger) {
	trigger->lock();
	trigger->removeFromZone();
	trigger->removeUndeploymentEvent();
	trigger->finalize();
}
