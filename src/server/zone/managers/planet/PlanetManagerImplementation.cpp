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

#include "PlanetManagerImplementation.h"

#include "../../ZoneProcessServerImplementation.h"

#include "../../objects.h"

#include "../../objects/terrain/PlanetNames.h"

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
}

void PlanetManagerImplementation::stop() {
	lock();
	
	clearBuildings();
	clearShuttles();
	clearTicketCollectors();
	clearTravelTerminals();
	
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

		travelTerminal->finalize();
	}
	
	travelTerminalMap->removeAll();
	
	info("cleared travelTerminals");
}

void PlanetManagerImplementation::loadStaticPlanetObjects() {
	loadShuttles();	
	//loadGuildTerminals();
	//loadVendorTerminals();
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
		float colx = shut->getFloat(11);
		float coly = shut->getFloat(12);
		float tickdiry = shut->getFloat(13);
		float tickdirw = shut->getFloat(14);
		float termx = shut->getFloat(15);
		float termy = shut->getFloat(16);
		
		coordinates = new Coordinate(playerSpawnX, playerSpawnZ, playerSpawnY);
		shuttle = creatureManager->spawnShuttle(planetName, shuttleName, coordinates, shutx, shuty, shutz);
		shuttle->setDirection(0, 0, shutdiry, shutdirw);
		shuttleMap->put(shuttleName, shuttle);

		TicketCollectorImplementation* colImpl = new TicketCollectorImplementation(shuttle, getNextStaticObjectID(false), 
				unicode("Ticket Collector"), "ticket_travel", colx, playerSpawnZ, coly);
		colImpl->setZoneProcessServer(server);
		colImpl->setDirection(0, 0, tickdiry, tickdirw);
		colector = (TicketCollector*) colImpl->deploy();
		colector->insertToZone(zone);
		ticketCollectorMap->put(colImpl->getObjectID(), colector);

		TravelTerminalImplementation* termImpl = new TravelTerminalImplementation(shuttle, getNextStaticObjectID(false), 
				termx, playerSpawnZ, termy);
		termImpl->setZoneProcessServer(server);
		termImpl->setDirection(0, 0, tickdiry, tickdirw);
		terminal = (TravelTerminal*) termImpl->deploy();
		terminal->insertToZone(zone);
		travelTerminalMap->put(terminal->getObjectID(), terminal); 
	}
	delete shut;
	
	unlock();
	
}

	


void PlanetManagerImplementation::loadTrainers() {
}

void PlanetManagerImplementation::loadGuildTerminals() {
	if(zone->getZoneID() != 8)
		return;
	
	lock();
	
	GuildTerminalImplementation* guildImpl = new GuildTerminalImplementation(server->getGuildManager(), getNextStaticObjectID(false), 44, 52, -5352);
	
	GuildTerminal* guildTerminal = (GuildTerminal*) guildImpl->deploy();
	guildTerminal->insertToZone(zone);
	
	unlock();
}

void PlanetManagerImplementation::loadVendorTerminals() {
	if(zone->getZoneID() != 8)
		return;
	
	lock();
	
	VendorTerminalImplementation* termImpl = new VendorTerminalImplementation(zone->getZoneServer()->getBazaarManager(), getNextStaticObjectID(false), 46, 52, -5352);
	termImpl->setDirection(0, 0, 0, 0);
	
	termImpl->setZoneProcessServer(server);
	
	VendorTerminal* vendorTerminal = (VendorTerminal*) termImpl->deploy();
	vendorTerminal->insertToZone(zone);
	
	unlock();
}

void PlanetManagerImplementation::loadBuildings() {
	int planetid = zone->getZoneID();
	
	if (planetid != 8)
		return;
	
	lock();
	
	stringstream query;
	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid << ";";
	
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
			
			CellObjectImplementation* cellImpl = new CellObjectImplementation(oid, buio);
			CellObject* cell = (CellObject*) cellImpl->deploy(); 
			
			cell->setObjectCRC(String::hashCode(file));
			cell->initializePosition(x, z, y);
			cell->setDirection(oX, oZ, oY, oW);
			//cell->insertToZone(zone);
			zone->registerObject(cell);
			
			buio->addCell(cell);
			cellMap->put(oid, cell);
		}
	}
	
	delete result;
	
	unlock();
}

BuildingObject* PlanetManagerImplementation::loadBuilding(uint64 oid, int planet) {
	stringstream query;
	query << "SELECT * FROM staticobjects WHERE zoneid = '" << planet << "' AND objectid = '" << oid << "';";
		
	ResultSet* result = ServerDatabase::instance()->executeQuery(query);
	
	BuildingObject* buio = NULL;

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
		
		BuildingObjectImplementation* buioImpl = new BuildingObjectImplementation(oid, true);
		buioImpl->setZoneProcessServer(server);
		
		buio = (BuildingObject*) buioImpl->deploy();

		buio->setObjectCRC(String::hashCode(file));
			
		buio->initializePosition(x, z, y);
		buio->setDirection(oX, oZ, oY, oW);
		
		buio->insertToZone(zone);
		//zone->registerObject(buio);

		buildingMap->put(oid, buio);
	}
	
	delete result;
	
	return buio;
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
			cout << "exception in PlanetManagerImplementation::landShuttles()";
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
			cout << "exception in PlanetManagerImplementation::takeOffShuttles()";
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
		
		msg->addPoint(shuttle->getCity(), shuttle->getPositionX(), shuttle->getPositionZ(), shuttle->getPositionY());
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
	
	uint64 nextId = server->getZoneServer()->getNextCreatureID();
	
	unlock(doLock);
	
	return nextId;
}
