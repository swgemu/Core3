/*
 * StructureManagerImplementation.h
 *
 *  Created on: Oct 25, 2008
 *      Author: swgemu
 */

#ifndef STRUCTUREMANAGERIMPLEMENTATION_H_
#define STRUCTUREMANAGERIMPLEMENTATION_H_


#include "engine/engine.h"

#include "../../Zone.h"
#include "../../ZoneServer.h"

#include "../../../db/ServerDatabase.h"
#include "../../objects/player/Player.h"

#include "../../objects/tangible/deed/DeedObject.h"
#include "../../objects/tangible/deed/DeedObjectImplementation.h"

#include "CellMap.h"
#include "BuildingMap.h"
#include "InstallationMap.h"

#include "StructureManager.h"


class ZoneServer;
class ZoneProcessServerImplementation;
class StructureManagerSaveStateEvent;
class InstallationSpawnEvent;
class InstallationDespawnEvent;
class TempInstallationSpawnEvent;
class TempInstallationDespawnEvent;

class Player;
class PlayerImplementation;


class StructureManagerImplementation : public StructureManagerServant, public Logger {
	Zone* zone;
	ZoneProcessServerImplementation* server;

 	BuildingMap* buildingMap;
	CellMap* cellMap;
	InstallationMap* installationMap;

	StructureManagerSaveStateEvent* structureManagerSaveStateEvent;

	InstallationSpawnEvent* installationSpawnEvent;
	InstallationDespawnEvent* installationDespawnEvent;
	TempInstallationSpawnEvent* tempInstallationSpawnEvent;
	TempInstallationDespawnEvent* tempInstallationDespawnEvent;
public:
	StructureManagerImplementation(Zone* zone, ZoneProcessServerImplementation* serv);
	~StructureManagerImplementation();

	void init();
	void initializeEvents();

	void loadStructures();
	void unloadStructures();

	void loadStaticBuildings();
	void loadPlayerStructures();

	void clearBuildings();
	void clearInstallations();

	void saveStructures(bool doSchedule = false);
	void saveBuildings();
	void saveInstallations();

	inline Zone* getZone() {
		return zone;
	}

	BuildingObject* findBuildingType(const String& word, float targetX, float targetY);
	int guessBuildingType(uint64 oid, String file);
	BuildingObject* loadStaticBuilding(uint64 oid, int planet);

	inline CellObject* getCell(uint64 id) {
		return cellMap->get(id);
	}

	inline BuildingObject* getBuilding(uint64 id) {
		return buildingMap->get(id);
	}

	// Player Installations
	void spawnTempStructure(Player *player, DeedObject *deed, float x, float z, float y, float oX, float oZ, float oY, float oW);
	void spawnInstallation(Player *player, DeedObject *deed, float x, float z, float y, float oX, float oZ, float oY, float oW);
	void spawnHarvester(Player *player, DeedObject *deed, float x, float z, float y, float oX, float oZ, float oY, float oW);

	void createInstallation(InstallationObject *inso);
	void saveInstallation(InstallationObject *inso);
	void deleteInstallation(InstallationObject *inso);

	// Player Buildings
	void spawnBuilding(Player *player, DeedObject *deed, float x, float z, float y, float oX, float oZ, float oY, float oW);
	void createPlayerCells(Player *player, BuildingObject *buio, int cellCount);
	void loadPlayerCells(BuildingObject * buio);

	void createBuilding(BuildingObject *buio);
	void saveBuilding(BuildingObject *buio);
	void deleteBuilding(BuildingObject *buio);
};


#endif /* STRUCTUREMANAGERIMPLEMENTATION_H_ */
