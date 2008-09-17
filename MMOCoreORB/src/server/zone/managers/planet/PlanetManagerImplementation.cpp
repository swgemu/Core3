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

#include "events/HarvesterSpawnEvent.h"
#include "events/InstallationSpawnEvent.h"
#include "events/TempInstallationSpawnEvent.h"
#include "events/TempInstallationDespawnEvent.h"

#include "PlanetManagerImplementation.h"

#include "../../ZoneProcessServerImplementation.h"

#include "../../objects.h"

#include "../../objects/terrain/PlanetNames.h"

#include "AreaMap.h"
#include "../../objects/area/BaseArea.h"

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

PlanetManagerImplementation::PlanetManagerImplementation(Zone* planet, ZoneProcessServerImplementation* serv) :
	PlanetManagerServant(), Mutex("PlanetManager"), Logger() {
	zone = planet;

	server = serv;

	nextStaticObjectID = 0x50000000;

	shuttleTakeOffEvent = new ShuttleTakeOffEvent(this);
	shuttleLandingEvent = new ShuttleLandingEvent(this);

	buildingMap = new BuildingMap(10000);
	cellMap = new CellMap(10000);
	shuttleMap = new ShuttleMap();
	ticketCollectorMap = new TicketCollectorMap(2000);
	travelTerminalMap = new TravelTerminalMap(2000);
	missionTerminalMap = new MissionTerminalMap(100);
	craftingStationMap.setNullValue(NULL);
	craftingStationMap.setInsertPlan(SortedVector<VectorMapEntry<uint64, CraftingStation*>*>::NO_DUPLICATE);

	creatureManager = planet->getCreatureManager();

	stringstream logName;
	logName << "PlanetManager" << zone->getZoneID();
	setLoggingName(logName.str());

	setLogging(false);
	setGlobalLogging(true);
}

PlanetManagerImplementation::~PlanetManagerImplementation() {
	delete cellMap;
	cellMap = NULL;

	delete buildingMap;
	buildingMap = NULL;

	delete shuttleMap;
	shuttleMap = NULL;

	delete ticketCollectorMap;
	ticketCollectorMap = NULL;

	delete travelTerminalMap;
	travelTerminalMap = NULL;

	delete missionTerminalMap;
	missionTerminalMap = NULL;

	delete shuttleTakeOffEvent;
	shuttleTakeOffEvent = NULL;

	delete shuttleLandingEvent;
	shuttleLandingEvent = NULL;
}

void PlanetManagerImplementation::init() {
	loadBuildings();
}

void PlanetManagerImplementation::start() {
	loadStaticPlanetObjects();

	if (shuttleMap->size() > 0)
		takeOffShuttles();

	loadPlayerStructures();
}

void PlanetManagerImplementation::stop() {
	lock();

	clearBuildings();
	clearShuttles();
	clearTicketCollectors();
	clearTravelTerminals();
	clearCraftingStations();

	unlock();
}

void PlanetManagerImplementation::loadPlayerStructures() {
	lock();

	int planetid = zone->getZoneID();

	stringstream query;
	query << "SELECT * FROM character_structures WHERE zoneid = " << planetid << ";";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	while (result->next()) {
		uint64 oid = result->getUnsignedLong(1);
		uint64 parentId = result->getUnsignedLong(2);

		string title = result->getString(3);

		string tempname = result->getString(4);

		uint64 crc = result->getUnsignedLong(5);

		string file = result->getString(6);

		float oX = result->getFloat(7);
		float oY = result->getFloat(8);
		float oZ = result->getFloat(9);
		float oW = result->getFloat(10);

		float x = result->getFloat(11);
		float z = result->getFloat(12);
		float y = result->getFloat(13);

		float type = result->getFloat(14);
		if ((int) file.find("object/building/") >= 0) {
			BuildingObject* buio = new BuildingObject(oid, true);

			buio->setObjectCRC(String::hashCode(file));
			buio->initializePosition(x, z, y);
			buio->setDirection(oX, oZ, oY, oW);
			//buio->insertToZone(zone);
			//zone->registerObject(buio);

			buildingMap->put(oid, buio);
		} else if ((int)file.find("object/cell/") >= 0) {
			BuildingObject* buio = buildingMap->get(parentId);

			if (buio == NULL)
				buio = loadBuilding(parentId, planetid);

			CellObject* cell = new CellObject(oid, buio);

			cell->setObjectCRC(String::hashCode(file));
			cell->initializePosition(x, z, y);
			cell->setDirection(oX, oZ, oY, oW);
			//cell->insertToZone(zone);
			zone->registerObject(cell);

			buio->addCell(cell);
			cellMap->put(oid, cell);
		} else if ((int)file.find("object/installation/") >= 0) {
			// Need to load player installations from DB here
			/*uint64 newId = getNextStaticObjectID(true);

			HarvesterObjectImplementation* hisoImpl =
				new HarvesterObjectImplementation(newId, tempname);

			hisoImpl->setObjectCRC(String::hashCode(file));
			hisoImpl->initializePosition(x, 9, y);
			hisoImpl->setDirection(oX, oZ, oY, oW);
			HarvesterObject* hiso = (HarvesterObject*) hisoImpl->deploy();
			hiso->insertToZone(zone);

			zone->registerObject(hiso);*/
		}
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

void PlanetManagerImplementation::clearBuildings() {
	buildingMap->resetIterator();

	while (buildingMap->hasNext()) {
		BuildingObject* building = buildingMap->next();
		building->removeFromZone();

		building->removeUndeploymentEvent();

		building->finalize();
	}

	buildingMap->removeAll();

	info("cleared buildings");
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

void PlanetManagerImplementation::loadStaticPlanetObjects() {
	loadShuttles();
	loadGuildTerminals();
	//loadVendorTerminals();
	loadCraftingStations();
	loadMissionTerminals();
}

void PlanetManagerImplementation::loadShuttles() {
	int planetid = zone->getZoneID();
	lock();

	ShuttleCreature* shuttle;
	TravelTerminal* terminal;
	TicketCollector* colector;
	Coordinate* coordinates;

	string planetName = Planet::getPlanetName(zone->getZoneID());

	stringstream query;
	query << "SELECT * FROM shuttles WHERE planet_id = " << planetid << ";";

	try {
		ResultSet* shut = ServerDatabase::instance()->executeQuery(query);

		while (shut->next()) {
			string shuttleName = shut->getString(2);
			float playerSpawnX = shut->getFloat(3);
			float playerSpawnY = shut->getFloat(4);
			float playerSpawnZ = shut->getFloat(5);
			float shutx = shut->getFloat(6);
			float shuty = shut->getFloat(7);
			float shutz = shut->getFloat(8);
			float shutdiry = shut->getFloat(9);
			float shutdirw = shut->getFloat(10);
			uint32	tax = shut->getInt(11);
			bool starport = shut->getInt(12);
			float colx = shut->getFloat(13);
			float coly = shut->getFloat(14);
			float tickdiry = shut->getFloat(15);
			float tickdirw = shut->getFloat(16);
			float termx = shut->getFloat(17);
			float termy = shut->getFloat(18);

			coordinates = new Coordinate(playerSpawnX, playerSpawnZ, playerSpawnY);
			shuttle = creatureManager->spawnShuttle(planetName, shuttleName, coordinates, shutx, shuty, shutz, tax, starport);
			shuttle->setDirection(0, 0, shutdiry, shutdirw);
			shuttleMap->put(shuttleName, shuttle);

			colector = new TicketCollector(shuttle, getNextStaticObjectID(false),
					unicode("Ticket Collector"), "ticket_travel", colx, playerSpawnZ, coly);
			colector->setZoneProcessServer(server);
			colector->setDirection(0, 0, tickdiry, tickdirw);

			colector->insertToZone(zone);
			ticketCollectorMap->put(colector->getObjectID(), colector);

			terminal = new TravelTerminal(shuttle, getNextStaticObjectID(false),
					termx, playerSpawnZ, termy);
			terminal->setZoneProcessServer(server);
			terminal->setDirection(0, 0, tickdiry, tickdirw);

			terminal->insertToZone(zone);
			travelTerminalMap->put(terminal->getObjectID(), terminal);
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

	if (planetId != 5)
		return;

	lock();

	MissionTerminal* missionTerminal = new MissionTerminal(getNextStaticObjectID(false), -4836.0f, 6.0f, 4155.0f, planetId, MissionTerminalImplementation::TMASK_GENERAL);
	missionTerminal->setDirection(0, 0, 0, 0);

	missionTerminal->setZoneProcessServer(server);

	missionTerminal->insertToZone(zone);
	missionTerminalMap->put(missionTerminal->getObjectID(), missionTerminal);

	unlock();
}

void PlanetManagerImplementation::loadBuildings() {
	int planetid = zone->getZoneID();

	lock();

	stringstream query;
	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid << ";";

	try {
		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			uint64 oid = result->getUnsignedLong(1);

			uint64 parentId = result->getUnsignedLong(2);

			string file = result->getString(3);

			float oX = result->getFloat(4);
			float oY = result->getFloat(5);
			float oZ = result->getFloat(6);
			float oW = result->getFloat(7);

			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);

			float type = result->getFloat(11);

			if ((int) file.find("object/cell/") >= 0) {
				BuildingObject* buio = buildingMap->get(parentId);

				if (buio == NULL)
					buio = loadBuilding(parentId, planetid);

				CellObject* cell = new CellObject(oid, buio);

				cell->setObjectCRC(String::hashCode(file));
				cell->initializePosition(x, z, y);
				cell->setDirection(oX, oZ, oY, oW);

				cell->setZoneProcessServer(server);
				zone->registerObject(cell);

				buio->addCell(cell);

				if (cellMap->put(oid, cell) != NULL) {
					error("Error CELL/BUILDING already exists\n");
					raise(SIGSEGV);
				}
			}
		}

		delete result;
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadBuildings()\n");
	}

	unlock();
}


BuildingObject* PlanetManagerImplementation::findBuildingType(const string& word, float targetX, float targetY) {
	lock();

	uint16 accumDistance, distance = 32768;
	BuildingObject* buiID = 0;

	buildingMap->resetIterator();

	while (buildingMap->hasNext()) {
		BuildingObject* building = buildingMap->next();

		if (word == "starport" && building->getBuildingType() == BuildingObjectImplementation::STARPORT) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "cloner" && building->getBuildingType() == BuildingObjectImplementation::CLONING_FACILITY) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "shuttle" && building->getBuildingType() == BuildingObjectImplementation::SHUTTLEPORT) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "HOTEL" && building->getBuildingType() == BuildingObjectImplementation::HOTEL) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "bank" && building->getBuildingType() == BuildingObjectImplementation::BANK) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "garage" && building->getBuildingType() == BuildingObjectImplementation::GARAGE) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "medical" && building->getBuildingType() == BuildingObjectImplementation::MEDICAL_CENTER) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "salon" && building->getBuildingType() == BuildingObjectImplementation::SALON) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}
	}

	unlock();

	return buiID;
}


void PlanetManagerImplementation::loadCraftingStations() {
	int planetid = zone->getZoneID();

	lock();

	string name;
	uint64 crc;

	stringstream query;
	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid << ";";

	try {
		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			uint64 oid = result->getUnsignedLong(1);

			uint64 parentId = result->getUnsignedLong(2);

			string file = result->getString(3);

			float oX = result->getFloat(4);
			float oY = result->getFloat(5);

			float oZ = result->getFloat(6);
			float oW = result->getFloat(7);

			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);

			float type = result->getFloat(11);

			if ((int) file.find("object/tangible/crafting/station/") >= 0) {

				crc = String::hashCode(file);

				name = getStationName(crc);

				CraftingStation* station = new CraftingStation(oid, crc, unicode(name), "public_crafting_station");

				station->setEffectiveness(22);

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

string PlanetManagerImplementation::getStationName(uint64 crc){
	string name = "";

	if(crc == 0xAF09A3F0)
		name = "Clothing and Armor Public Crafting Station";

	if(crc == 0x2FF7F78B)
		name = "Food and Chemical Public Crafting Station";

	if(crc == 0x17929444)
		name = "Starship Public Crafting Station";

	if(crc == 0x1BABCF4B)
		name = "Structure and Furniture Public Crafting Station";

	if(crc == 0x72719FEA)
		name = "Weapon, Droid, and General Public Crafting Station";

	return name;
}

int PlanetManagerImplementation::guessBuildingType(uint64 oid, string file) {
	// Special buildings
	switch (oid)
	{
	// Cantinas
	case 1076941: // Tatooine	Mos Eisley	Cantina (Lucky Despot)
		return BuildingObjectImplementation::CANTINA;
	case 1153495: // Tatooine	Mos Entha	Cantina (The Fallen Star)
		return BuildingObjectImplementation::CANTINA;
	case 3355385: // Tatooine - Anchorhead Cantina
		return BuildingObjectImplementation::CANTINA;
	case 9925364: // Endor - Research Outpost Cantina
		return BuildingObjectImplementation::CANTINA;
	case 6645602: // Endor - Smuggler's Outpost Cantina
		return BuildingObjectImplementation::CANTINA;
	case 1028489: // Tatooine - Bestine Cantina
		return BuildingObjectImplementation::CANTINA;
	case 3035375: // Yavin IV - Labor Outpost Cantina
		return BuildingObjectImplementation::CANTINA;
	case 7925448: // Yavin IV - Mining Outpost Cantina
		return BuildingObjectImplementation::CANTINA;

		// Taverns
	case 6205563: // Dantooine	Mining Outpost	Tavern
		return BuildingObjectImplementation::TAVERN;
	case 6205495: // Dantooine	Pirate Outpost	Tavern
		return BuildingObjectImplementation::TAVERN;
	case 1213343: // Tatooine	Anchorhead	Tavern
		return BuildingObjectImplementation::TAVERN;
	case 1154120: // Tatooine	Mos Taike	Tavern
		return BuildingObjectImplementation::TAVERN;
	case 6955366: // Dathomir	Trade Outpost	Tavern
		return BuildingObjectImplementation::TAVERN;

		// Medical Centers
	case 1414856: // Endor	Smuggler's Outpost	Medical Center
		return BuildingObjectImplementation::MEDICAL_CENTER;
	case 1414867: // Endor	Research Outpost	Medical Center
		return BuildingObjectImplementation::MEDICAL_CENTER;
	case 2835549: // Dathomir	Science Outpost	Medical Center
		return BuildingObjectImplementation::MEDICAL_CENTER;
	case 3035371: // Yavin IV	Labor Outpost	Medical Center
		return BuildingObjectImplementation::MEDICAL_CENTER;
	case 7925474: // Yavin IV	Mining Outpost	Medical Center
		return BuildingObjectImplementation::MEDICAL_CENTER;

		// Museum
	case 1028167: //Tatooine	Bestine	Museum
		return BuildingObjectImplementation::MUSEUM;

		// Junk Shop
	case 1255995: // Tatooine	Mos Espa	Watto�s Junk Shop
		return BuildingObjectImplementation::JUNKSHOP;
	}

	if ((int) file.find("_cantina_") >= 0)
		return BuildingObjectImplementation::CANTINA;
	if ((int) file.find("_cloning_") >= 0)
		return BuildingObjectImplementation::CLONING_FACILITY;
	if ((int) file.find("_starport_") >= 0)
		return BuildingObjectImplementation::STARPORT;
	if ((int) file.find("_shuttleport_") >= 0)
		return BuildingObjectImplementation::SHUTTLEPORT;
	if ((int) file.find("_hotel_") >= 0)
		return BuildingObjectImplementation::HOTEL;
	if ((int) file.find("_bank_") >= 0)
		return BuildingObjectImplementation::BANK;
	if ((int) file.find("_capitol_") >= 0)
		return BuildingObjectImplementation::CAPITOL;
	if ((int) file.find("_garage_") >= 0)
		return BuildingObjectImplementation::GARAGE;
	if ((int) file.find("_hospital_") >= 0)
		return BuildingObjectImplementation::MEDICAL_CENTER;
	if ((int) file.find("_guild_university_") >= 0)
		return BuildingObjectImplementation::GUILD_UNIVERSITY;
	if ((int) file.find("_guild_theater_") >= 0)
		return BuildingObjectImplementation::GUILD_THEATER;
	if ((int) file.find("_guild_combat_") >= 0)
		return BuildingObjectImplementation::GUILD_COMBAT;
	if ((int) file.find("_guild_commerce_") >= 0)
		return BuildingObjectImplementation::GUILD_COMMERCE;
	if ((int) file.find("_salon_") >= 0)
		return BuildingObjectImplementation::SALON;
	if ((int) file.find("_barracks_") >= 0)
		return BuildingObjectImplementation::BARRACKS;


	/*BuildingObjectImplementation::SF_REBEL_FORWARD_BASE;
	BuildingObjectImplementation::SF_IMPERIAL_FORWARD_BASE;
	BuildingObjectImplementation::SF_REBEL_MINOR_BASE;
	BuildingObjectImplementation::SF_IMPERIAL_MINOR_BASE;
	BuildingObjectImplementation::SF_REBEL_MAJOR_BASE;
	BuildingObjectImplementation::SF_IMPERIAL_MAJOR_BASE;
	BuildingObjectImplementation::SF_REBEL_HQ;
	BuildingObjectImplementation::SF_IMPERIAL_HQ;
	BuildingObjectImplementation::REBEL_FORWARD_BASE;
	BuildingObjectImplementation::IMPERIAL_FORWARD_BASE;
	BuildingObjectImplementation::REBEL_MINOR_BASE;
	BuildingObjectImplementation::IMPERIAL_MINOR_BASE;
	BuildingObjectImplementation::REBEL_MAJOR_BASE;
	BuildingObjectImplementation::IMPERIAL_MAJOR_BASE;
	BuildingObjectImplementation::REBEL_HQ;
	BuildingObjectImplementation::IMPERIAL_HQ;*/

	return BuildingObjectImplementation::UNKNOWN;
}

BuildingObject* PlanetManagerImplementation::loadBuilding(uint64 oid, int planet) {
	BuildingObject* buio = NULL;

	stringstream query;
	query << "SELECT * FROM staticobjects WHERE zoneid = '" << planet << "' AND objectid = '" << oid << "';";

	try {
		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		if (result->next()) {
			uint64 oid = result->getUnsignedLong(1);
			uint64 parentId = result->getUnsignedLong(2);

			string file = result->getString(3);

			float oX = result->getFloat(4);
			float oY = result->getFloat(5);
			float oZ = result->getFloat(6);
			float oW = result->getFloat(7);

			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);

			float type = result->getFloat(11);

			buio = new BuildingObject(oid, true);
			buio->setZoneProcessServer(server);

			buio->setObjectCRC(String::hashCode(file));

			buio->setBuildingType(guessBuildingType(oid, file));

			buio->initializePosition(x, z, y);
			buio->setDirection(oX, oZ, oY, oW);

			buio->insertToZone(zone);

			if (buildingMap->put(oid, buio) != NULL) {
				error("Error CELL/BUILDING already exists\n");
				raise(SIGSEGV);
			}
		}

		delete result;
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadBuilding");
	}

	return buio;
}

void PlanetManagerImplementation::placePlayerStructure(Player * player,
		uint64 objectID, float x, float y, int orient) {
	try {

		DeedObject * deed = (DeedObject*) player->getInventoryItem(objectID);

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

		spawnTempStructure(player, deed, x, player->getPositionZ(), y, oX, oZ, oY, oW);

cout << "Deed is = " << deed->getDeedSubType() << endl;
		switch(deed->getDeedSubType()) {
			case DeedObjectImplementation::HARVESTER:

				spawnHarvester(player, deed, x, player->getPositionZ(), y, oX, oZ, oY, oW);
				break;

			case DeedObjectImplementation::GENERATOR:
			case DeedObjectImplementation::FACTORY:

				spawnInstallation(player, deed, x, player->getPositionZ(), y, oX, oZ, oY, oW);
				break;

			case DeedObjectImplementation::BUILDING:

				spawnBuilding(player, deed, x, player->getPositionZ(), y, oX, oZ, oY, oW);
				break;

			default:
				break;
		}
	}
	catch(...) {
		cout << "Exception in PlanetManagerImplementation::placePlayerStructure\n";
	}
}
void PlanetManagerImplementation::spawnTempStructure(Player * player,
		DeedObject * deed, float x, float z, float y, float oX, float oZ,
		float oY, float oW) {

	InstallationObject* inso = new InstallationObject(player->getNewItemID(), deed);

	//inso->setObjectID(player->getNewItemID());
	inso->setObjectCRC(String::hashCode(deed->getTargetTempFile()));
	inso->setObjectSubType(0);
	inso->initializePosition(x, z, y);
	inso->setDirection(oX, oZ, oY, oW);
	inso->setOwner(player->getFirstName());
	inso->setZoneProcessServer(server);

	tempInstallationSpawnEvent = new TempInstallationSpawnEvent(player, inso);
	tempInstallationDespawnEvent = new TempInstallationDespawnEvent(inso);

	//server->addEvent(tempInstallationSpawnEvent, 20);
	//server->addEvent(tempInstallationDespawnEvent, 5000);
}
void PlanetManagerImplementation::spawnInstallation(Player * player,
		DeedObject * deed, float x, float z, float y, float oX, float oZ,
		float oY, float oW) {

	InstallationObject* inso = new InstallationObject(player->getNewItemID(), deed);

	//inso->setObjectID(player->getNewItemID());
	inso->setObjectCRC(String::hashCode(deed->getTargetFile()));
	inso->initializePosition(x, z, y);
	inso->setDirection(oX, oZ, oY, oW);
	inso->setOwner(player->getFirstName());
	inso->setZoneProcessServer(server);

	installationSpawnEvent = new InstallationSpawnEvent(player, inso);

	server->addEvent(installationSpawnEvent, 5500);
}

void PlanetManagerImplementation::spawnHarvester(Player * player,
		DeedObject * deed, float x, float z, float y, float oX, float oZ,
		float oY, float oW) {

	cout << "PlanetManagerImplementation::spawnHarvester" << endl;
	HarvesterObject*  hino = new HarvesterObject(player->getNewItemID(), deed);

	//hino->setObjectID(player->getNewItemID());
	hino->setObjectCRC(String::hashCode(deed->getTargetFile()));
	hino->initializePosition(x, z, y);
	hino->setDirection(oX, oZ, oY, oW);
	hino->setOwner(player->getFirstName());
	hino->setZoneProcessServer(server);

	cout << "PlanetManagerImplementation::spawnHarvester, creating event" << endl;
	harvesterSpawnEvent = new HarvesterSpawnEvent(player, hino);

	server->addEvent(harvesterSpawnEvent, 5500);
	cout << "PlanetManagerImplementation::did spawnHarvester, creating event" << endl;
}

void PlanetManagerImplementation::spawnBuilding(Player * player,
		DeedObject * thedeed, float x, float z, float y, float oX, float oZ,
		float oY, float oW) {
	PlayerHouseDeed * deed = (PlayerHouseDeed *) thedeed;

	cout << "spawning building" << endl;


	BuildingObject* buio = new BuildingObject(player->getNewItemID(), false);
	buio->setZoneProcessServer(server);

	buio->setObjectCRC(String::hashCode(deed->getTargetFile()));
	buio->initializePosition(x, z, y);
	buio->setDirection(oX, oZ, oY, oW);

	//zone->registerObject(buio);



	cout << "adding player cells: " << deed->getCellCount() << endl;
	addPlayerCells(player, buio, deed->getCellCount());

	//return;

	buio->insertToZone(zone);


	buildingMap->put(buio->getObjectID(), buio);
}
void PlanetManagerImplementation::addPlayerCells(Player * player, BuildingObject * buio, int cellCount) {

	for(int i = 1; i <= cellCount; ++i){
		// Get new cell object ID
		cout << "adding cell" << endl;
		uint64 oid = player->getNewItemID();

		CellObject* cell = new CellObject(oid, buio, i); // server->getZoneServer()->getNextCellID()

		cell->setObjectCRC(String::hashCode("object/cell/shared_cell.iff"));
		cell->initializePosition(0, 0, 0);
		cell->setDirection(0, 0, 1, 0); // void SceneObject::setDirection(float x, float z, float y, float w) {
		//cell->insertToZone(zone);
		zone->registerObject(cell);

		buio->addCell(cell);
		cellMap->put(oid, cell);
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
	//cout << "Requested travel list for:" << Planet::getPlanetName(zone->getZoneID()) << "\n";

	shuttleMap->resetIterator();

	while (shuttleMap->hasNext()) {
		ShuttleCreature* shuttle = shuttleMap->getNextValue();

		msg->addPoint(shuttle->getCity(), shuttle->getPositionX(), shuttle->getPositionZ(), shuttle->getPositionY(), shuttle->getTax(), shuttle->isStarport());
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

ShuttleCreature* PlanetManagerImplementation::getShuttle(const string& Shuttle) {
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
