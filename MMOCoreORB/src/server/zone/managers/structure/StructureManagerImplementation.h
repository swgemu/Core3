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

#ifndef STRUCTUREMANAGERIMPLEMENTATION_H_
#define STRUCTUREMANAGERIMPLEMENTATION_H_


#include "engine/engine.h"

#include "../../Zone.h"
#include "../../ZoneServer.h"

#include "../../../db/ServerDatabase.h"
#include "../../objects/player/Player.h"

#include "../../objects/tangible/deed/DeedObject.h"
#include "../../objects/tangible/deed/DeedObjectImplementation.h"

#include "../../objects/structure/building/cloningfacility/CloningFacility.h"

#include "CellMap.h"
#include "BuildingMap.h"
#include "InstallationMap.h"
#include "CloningFacilityMap.h"

#include "StructureManager.h"


class ZoneServer;
class ZoneProcessServerImplementation;

class StructureManagerSaveStateEvent;
class StructureMaintenanceEvent;

class Player;
class PlayerImplementation;


class StructureManagerImplementation : public StructureManagerServant, public Logger {
	Zone* zone;
	ZoneProcessServerImplementation* server;

 	BuildingMap* buildingMap;
	CellMap* cellMap;
	InstallationMap* installationMap;
	CloningFacilityMap* cloningFacilityMap;

	StructureManagerSaveStateEvent* structureManagerSaveStateEvent;
	StructureMaintenanceEvent* structureMaintenanceEvent;

	void init();

public:
	StructureManagerImplementation(Zone* zone, ZoneProcessServerImplementation* serv);
	~StructureManagerImplementation();

	//Cleanup mode.
	void serialize();
	void deserialize();

	void beginConstruction(Player* player, DeedObject* deed, float x, float z, uint8 orient = 0);
	void endConstruction(Player* player, DeedObject* deed, float x, float z, uint8 orient = 0);
	void createInstallation(Player* player, InstallationObject* installation, bool staticobject = false);
	void createBuilding(Player* player, BuildingObject* building, bool staticobject = false);

	void deleteStructure(SceneObject* structure);

	void loadStructures();
	void unloadStructures();

	void loadStaticBuildings();
	void loadPlayerStructures();

	void clearBuildings();
	void clearInstallations();

	void saveStructures(bool reschedule = false);
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

	inline CloningFacility* getCloningFacility(uint64 oid) {
		return cloningFacilityMap->get(oid);
	}

	CloningFacility* getClosestCloningFacility(Player* player);

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
