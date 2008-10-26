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
#include "MissionTerminalMap.h"
#include "../creature/CreatureManager.h"

#include "PlanetManager.h"

#include "AreaMap.h"
#include "../../objects/area/BaseArea.h"

class ShuttleTakeOffEvent;
class ShuttleLandingEvent;
class HarvesterSpawnEvent;
class InstallationSpawnEvent;
class TempInstallationSpawnEvent;
class TempInstallationDespawnEvent;

class Zone;
class CreatureManager;

class ZoneProcessServerImplementation;
class BuildingObject;

class ChatManager;

class PlanetManagerImplementation : public PlanetManagerServant, public Mutex, public Logger {
	Zone* zone;

	ZoneProcessServerImplementation* server;

	uint64 nextStaticObjectID;

	ShuttleMap* shuttleMap;
 	BuildingMap* buildingMap;
	CellMap* cellMap;
	TicketCollectorMap* ticketCollectorMap;
	TravelTerminalMap* travelTerminalMap;

	MissionTerminalMap* missionTerminalMap;
	VectorMap<uint64, CraftingStation*> craftingStationMap;

	ShuttleLandingEvent* shuttleLandingEvent;
	ShuttleTakeOffEvent* shuttleTakeOffEvent;

	InstallationSpawnEvent* installationSpawnEvent;

	TempInstallationSpawnEvent* tempInstallationSpawnEvent;
	TempInstallationDespawnEvent* tempInstallationDespawnEvent;

	VectorMap<uint64, TangibleObject*> staticTangibleObjectMap;

	CreatureManager* creatureManager;

	AreaMap * areaMap;

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

	bool isNoBuildArea(float x, float y);
	void addNoBuildArea(float minX, float maxX, float minY, float maxY, uint64 uid, uint8 reason = 0);
	void addNoBuildArea(NoBuildArea * area);
	void deleteNoBuildArea(NoBuildArea * area);
	NoBuildArea* createNoBuildArea(float minX, float maxX, float minY, float maxY, uint8 reason = 0);

private:
	void loadStaticPlanetObjects();
	void loadStaticTangibleObjects();
	void loadShuttles();
	void loadTrainers();
	int guessBuildingType(uint64 oid, string file);
	void loadBuildings();
	void loadPlayerStructures();
	void loadGuildTerminals();
	void loadVendorTerminals();
	void loadMissionTerminals();
	void loadCraftingStations();
	void loadNoBuildAreas();
	string getStationName(uint64 crc);


	BuildingObject* loadBuilding(uint64 oid, int planet);


	void clearShuttles();
	void clearBuildings();
	void clearTicketCollectors();
	void clearTravelTerminals();
	void clearMissionTerminals();
	void clearCraftingStations();
	void clearStaticTangibleObjects();


public:
	// getters
	ShuttleCreature* getShuttle(const string& Shuttle);

	inline CellObject* getCell(uint64 id) {
		return cellMap->get(id);
	}

	inline BuildingObject* getBuilding(uint64 id) {
		return buildingMap->get(id);
	}

	//change this to generic get terminal function if we move to unified terminal map:
	inline MissionTerminal* getMissionTerminal(uint64 oid) {
		return missionTerminalMap->get(oid);
	}

	int64 getLandingTime();

	uint64 getNextStaticObjectID(bool doLock = true);

	void placePlayerStructure(Player * player, uint64 objectID, float x, float y, int orient);

	inline uint32 getTravelFare(string departurePlanet, string arrivalPlanet) {
		return travelFare[Planet::getPlanetID(departurePlanet)][Planet::getPlanetID(arrivalPlanet)];
	}
	void spawnTempStructure(Player * player, DeedObject * deed, float x, float z, float y, float oX, float oZ, float oY, float oW);

	void spawnInstallation(Player * player, DeedObject * deed, float x, float z, float y, float oX, float oZ, float oY, float oW);

	void spawnHarvester(Player * player, DeedObject * deed, float x, float z, float y, float oX, float oZ, float oY, float oW);

	void spawnBuilding(Player * player, DeedObject * deed, float x, float z, float y, float oX, float oZ, float oY, float oW);

	void addPlayerCells(Player * player, BuildingObject * buio, int cellCount);
};

#endif
