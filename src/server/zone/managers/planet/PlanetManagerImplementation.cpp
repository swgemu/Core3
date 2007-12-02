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

PlanetManagerImplementation::PlanetManagerImplementation(Zone* planet, ZoneProcessServerImplementation* serv) : PlanetManagerServant(), Mutex("PlanetManager") {
	zone = planet;
	
	server = serv;
	
	nextStaticObjectID = 0x50000000;
	
	shuttleTakeOffEvent = new ShuttleTakeOffEvent(this);
	shuttleLandingEvent = new ShuttleLandingEvent(this);
	
	buildingMap = new BuildingMap(10000);
	cellMap = new CellMap(10000);
	
	creatureManager = planet->getCreatureManager();
}

void PlanetManagerImplementation::init() {
	if (zone->getZoneID() == 8) {
		loadStaticPlanetObjects();
		if (shuttleMap.size() > 0)
			takeOffShuttles();
	}
	
	//loadBuildings();
}

void PlanetManagerImplementation::loadStaticPlanetObjects() {
	loadShuttles();	
	//loadGuildTerminals();
}

void PlanetManagerImplementation::loadShuttles() {
	lock();
	
	ShuttleCreature* shuttle;
	TravelTerminal* terminal;
	TicketCollector* colector;
	Coordinate* coordinates;
	
	coordinates = new Coordinate(-1093, 12.6, -3562);
	shuttle = creatureManager->spawnShuttle("tatooine", "Bestine", coordinates, -1078, -3564, 12.6);
	shuttleMap.put("Bestine", shuttle);
	
	TicketCollectorImplementation* colImpl = new TicketCollectorImplementation(shuttle, getNextStaticObjectID(), unicode("Ticket Collector"), "ticket_travel", -1090, 12.6, -3554.9);
	colImpl->setDirection(0, 0, -0.64, 0.76);
	colector = (TicketCollector*) colImpl->deploy();
	colector->insertToZone(zone);
	
	TravelTerminalImplementation* termImpl = new TravelTerminalImplementation(shuttle, getNextStaticObjectID(), -1092, 12.6, -3570.9);
	termImpl->setDirection(0, 0, -0.64, 0.76);
	terminal = (TravelTerminal*) termImpl->deploy();
	terminal->insertToZone(zone);

	
	coordinates = new Coordinate(47, 52.6, -5333);
	shuttle = creatureManager->spawnShuttle("tatooine", "Anchorhead", coordinates, 47, -5317, 52.6);
	shuttle->setDirection(0, 0, 0.70654386, 0.70766926); 
	shuttleMap.put("Anchorhead", shuttle);
 
	colImpl = new TicketCollectorImplementation(shuttle, getNextStaticObjectID(), unicode("Ticket Collector"), "ticket_travel", 38, 52.6, -5332);
	colector = (TicketCollector*) colImpl->deploy();
	colector->insertToZone(zone);
	
	termImpl = new TravelTerminalImplementation(shuttle, getNextStaticObjectID(), 54, 52.6, -5332);
	terminal = (TravelTerminal*) termImpl->deploy();
	terminal->insertToZone(zone);
	
	unlock();
}

void PlanetManagerImplementation::loadTrainers() {
}

void PlanetManagerImplementation::loadGuildTerminals() {
	lock();
	
	GuildTerminal* guildTerminal;
	
	GuildTerminalImplementation* guildImpl = new GuildTerminalImplementation(server->getGuildManager(), getNextStaticObjectID(), 44, 52, -5352);
	guildTerminal = (GuildTerminal*) guildImpl->deploy();
	guildTerminal->insertToZone(zone);
	
	unlock();
}

void PlanetManagerImplementation::loadBuildings() {
	int planetid = zone->getZoneID();
	
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
		
		if ((int) file.find("object/building/") >= 0) {
			BuildingObjectImplementation* buioImpl = new BuildingObjectImplementation(oid, true);
			BuildingObject* buio = (BuildingObject*) buioImpl->deploy();

			buio->setObjectCRC(String::hashCode(file));
			buio->setPosition(x, z, y);
			buio->setDirection(oX, oZ, oY, oW);
			//buio->insertToZone(zone);
			//zone->registerObject(buio);
			
			buildingMap->put(oid, buio);
		} else if ((int)file.find("object/cell/") >= 0) {
			BuildingObject* buio = buildingMap->get(parentId);
			
			CellObjectImplementation* cellImpl = new CellObjectImplementation(oid, buio);
			CellObject* cell = (CellObject*) cellImpl->deploy(); 
			
			cell->setObjectCRC(String::hashCode(file));
			cell->setPosition(x, z, y);
			cell->setDirection(oX, oZ, oY, oW);
			
			//buio->insertChild(cell, false);
			buio->addCell(cell);
			cellMap->put(oid, cell);
		}
	}
	delete result;
}

void PlanetManagerImplementation::landShuttles() {
	lock();
	
	shuttleMap.resetIterator();
	
	while (shuttleMap.hasNext()) {
		ShuttleCreature* shuttle = shuttleMap.getNextValue();
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
	
	shuttleMap.resetIterator();
	
	while (shuttleMap.hasNext()) {
		ShuttleCreature* shuttle = shuttleMap.getNextValue();
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

int64 PlanetManagerImplementation::getLandingTime() {
	lock();
	
	Time landing;
	
	landing = shuttleLandingEvent->getTimeStamp();

	unlock();
	
	return landing.miliDifference();
}

ShuttleCreature* PlanetManagerImplementation::getShuttle(const string& Shuttle) {
	lock();
	
	ShuttleCreature* shuttle = shuttleMap.get(Shuttle);
	
	unlock();
	
	return shuttle;
}
