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

#ifndef PLANETMANAGERIMPLEMENTATION_H_
#define PLANETMANAGERIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../../db/ServerDatabase.h"

#include "../../objects.h"

#include "../../Zone.h"

#include "ShuttleMap.h"
#include "CellMap.h"
#include "BuildingMap.h"
#include "TicketCollectorMap.h"
#include "TravelTerminalMap.h"
#include "../creature/CreatureManager.h"

#include "PlanetManager.h"

class ShuttleTakeOffEvent;
class ShuttleLandingEvent;

class Zone;
class CreatureManager;

class ZoneProcessServerImplementation;
class BuildingObject;

class PlanetManagerImplementation : public PlanetManagerServant, public Mutex, public Logger {
	Zone* zone;

	ZoneProcessServerImplementation* server;

	uint64 nextStaticObjectID;

	ShuttleMap* shuttleMap;
	BuildingMap* buildingMap;
	CellMap* cellMap;
	TicketCollectorMap* ticketCollectorMap;
	TravelTerminalMap* travelTerminalMap;
	VectorMap<uint64, CraftingStation*> craftingStationMap;

	ShuttleLandingEvent* shuttleLandingEvent;
	ShuttleTakeOffEvent* shuttleTakeOffEvent;

	CreatureManager* creatureManager;

	static const uint32 travelFare[10][10];

public:
	PlanetManagerImplementation(Zone* zone, ZoneProcessServerImplementation* serv);
	~PlanetManagerImplementation();

	void init();
	void start();

	void stop();

	void landShuttles();
	void takeOffShuttles();

	void sendPlanetTravelPointListResponse(Player* player);

	BuildingObject* findBuildingType(const string& word, float targetX, float targetY);

private:
	void loadStaticPlanetObjects();
	void loadShuttles();
	void loadTrainers();
	int guessBuildingType(uint64 oid, string file);
	void loadBuildings();
	void loadGuildTerminals();
	void loadVendorTerminals();

	void loadCraftingStations();
	string getStationName(uint64 crc);

	BuildingObject* loadBuilding(uint64 oid, int planet);

	void clearShuttles();
	void clearBuildings();
	void clearTicketCollectors();
	void clearTravelTerminals();
	void clearCraftingStations();

public:
	// getters
	ShuttleCreature* getShuttle(const string& Shuttle);

	inline CellObject* getCell(uint64 id) {
		return cellMap->get(id);
	}

	inline BuildingObject* getBuilding(uint64 id) {
		return buildingMap->get(id);
	}

	int64 getLandingTime();

	uint64 getNextStaticObjectID(bool doLock = true);

	inline uint32 getTravelFare(string departurePlanet, string arrivalPlanet) {
		return travelFare[Planet::getPlanetID(departurePlanet)][Planet::getPlanetID(arrivalPlanet)];
	}
};

#endif
