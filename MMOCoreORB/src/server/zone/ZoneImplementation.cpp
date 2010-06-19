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

#include "Zone.h"
//#include "ZoneServer.h"

/*#include "managers/creature/CreatureManager.h"
#include "managers/creature/CreatureManagerImplementation.h"

#include "managers/combat/CombatManager.h"

#include "managers/planet/PlanetManager.h"
#include "managers/planet/PlanetManagerImplementation.h"

#include "../chat/ChatManager.h"

#include "objects/scene/SceneObject.h"

#include "objects/creature/Creature.h"*/


//#include "ZoneImplementation.h"

#include "objects/terrain/PlanetNames.h"

#include "ZoneProcessServerImplementation.h"
#include "objects/scene/SceneObject.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/templates/SharedObjectTemplate.h"
#include "server/zone/packets/player/GetMapLocationsResponseMessage.h"

ZoneImplementation::ZoneImplementation(ZoneServer* serv, ZoneProcessServerImplementation* srv, int id) : ManagedObjectImplementation(), QuadTree(-8192, -8192, 8192, 8192) {
	zoneID = id;

	processor = srv;
	server = serv;

	//Weather
	weatherID = 0;
	weatherWindX = 1.0f;
	weatherWindY = -1.0f;
	weatherEnabled = true;

	heightMap = new HeightMap();

	mapLocations.setNoDuplicateInsertPlan();

	//galacticTime = new Time();

	planetManager = NULL;
}

void ZoneImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	processor = ZoneProcessServerImplementation::instance;

	//taskManager =

	heightMap = new HeightMap();

	mapLocations.setNoDuplicateInsertPlan();

	if (zoneID <= 9) {
		String planetName = Planet::getPlanetName(zoneID);

		heightMap->load("planets/" + planetName + "/" + planetName + ".hmap");
	}
}

void ZoneImplementation::startManagers() {
	//if (zoneID > 45) //TODO: Change back to 9 sometimes. We use Zone 10 (Space Corellia) as a "prison" for the CSRs sending bad players there
	//	return;

	if (zoneID <= 9) {
		String planetName = Planet::getPlanetName(zoneID);

		heightMap->load("planets/" + planetName + "/" + planetName + ".hmap");
	}

	planetManager = new PlanetManager(_this, processor);
	planetManager->initialize();

	creatureManager = new CreatureManager(_this, processor);
	creatureManager->deploy("CreatureManager", zoneID);
	creatureManager->initialize();
	planetManager->loadShuttles();

	/*creatureManager->init();

	planetManager = new PlanetManager(_this, processor);
	planetManager->deploy("PlanetManager", zoneID);

	planetManager->init();

	creatureManager->loadCreatures();

	planetManager->start();

	creatureManager->start();*/
}

void ZoneImplementation::stopManagers() {
	//if (zoneID > 45) //TODO: Change back to 9 sometimes. We use Zone 10 (Space Corellia) as a "prison" for the CSRs sending bad players there
	//	return;

	/*if (creatureManager != NULL) {
		creatureManager->stop();

		creatureManager->finalize();
		creatureManager = NULL;
	}

	if (planetManager != NULL) {
		planetManager->stop();

		planetManager->finalize();
		planetManager = NULL;
	}*/
}

/*void ZoneImplementation::registerObject(SceneObject* obj) {
	server->addObject(obj);
}

SceneObject* ZoneImplementation::lookupObject(uint64 oid) {
	return server->getObject(oid);
}

SceneObject* ZoneImplementation::deleteObject(uint64 oid) {
	return server->removeObject(oid);
}

SceneObject* ZoneImplementation::deleteObject(SceneObject* obj) {
	return server->removeObject(obj->getObjectID());
}

SceneObject* ZoneImplementation::deleteCachedObject(SceneObject* obj) {
	return server->removeCachedObject(obj->getObjectID());
}*/

float ZoneImplementation::getHeight(float x, float y) {
	return heightMap->getHeight(x, y);
}

void ZoneImplementation::insert(QuadTreeEntry* entry) {
	QuadTree::insert(entry);
}

void ZoneImplementation::remove(QuadTreeEntry* entry) {
	QuadTree::remove(entry);
}

void ZoneImplementation::update(QuadTreeEntry* entry) {
	QuadTree::update(entry);
}

void ZoneImplementation::inRange(QuadTreeEntry* entry, float range) {
	QuadTree::inRange(entry, range);
}

/*ChatManager* ZoneImplementation::getChatManager() {
	return server->getChatManager();
}*/

void ZoneImplementation::addSceneObject(SceneObject* object) {
	objectMap.put(object->getObjectID(), object);

	uint32 templateCRC = object->getServerObjectCRC();

	SharedObjectTemplate* templ = TemplateManager::instance()->getTemplate(templateCRC);

	if (templ != NULL) {
		int mapLoc1 = templ->getMapLocationsType1();
		int mapLoc2 = templ->getMapLocationsType2();
		int mapLoc3 = templ->getMapLocationsType3();

		if (mapLoc1 != 0 || mapLoc2 != 0 || mapLoc3 != 0 || object->isPlayerCreature()) {
			if (object->isPlayerCreature())
				mapLoc1 = 1;

			MapLocationEntry entry(object, mapLoc1, mapLoc2, mapLoc3);

			Locker locker(&mapLocations);
			mapLocations.put(object->getObjectID(), entry);
		}
	}
}

void ZoneImplementation::dropSceneObject(uint64 oid)  {
	objectMap.remove(oid);

	Locker locker(&mapLocations);
	mapLocations.drop(oid);
}

void ZoneImplementation::sendMapLocationsTo(const String& planetName, SceneObject* player) {
	GetMapLocationsResponseMessage* gmlr = new GetMapLocationsResponseMessage(planetName);

	mapLocations.rlock();

	SortedVector<String> cities;

	try {
		for (int i = 0; i < mapLocations.size(); ++i) {
			MapLocationEntry* entry = &mapLocations.get(i);
			SceneObject* object = entry->getObject();
			UnicodeString name;
			StringId* objectName = object->getObjectName();

			if (object->isBuildingObject()) {
				ActiveArea* area = object->getActiveArea();

				if (area != NULL) {
					objectName = area->getObjectName();
				}
			}

			name = objectName->getCustomString();

			if (name.length() == 0) {
				String fullPath;
				objectName->getFullPath(fullPath);

				name = fullPath;
			}

			if (entry->getType1() == 17) {
				if (!cities.contains(name.toString()))
					cities.put(name.toString());
				else
					continue;
			}

			float posX, posY;

			posX = object->getWorldPositionX();
			posY = object->getWorldPositionY();


			gmlr->addMapLocation(object->getObjectID(), name, posX,
					posY, entry->getType1(), entry->getType2(), entry->getType3());

		}

	} catch (Exception& e) {
		System::out << e.getMessage() << endl;
		e.printStackTrace();
	} catch (...) {
		System::out << "unreported exception caught in ZoneImplementation::sendMapLocationsTo" << endl;
	}

	mapLocations.runlock();

	//these will be used for other locations on the planet map
	gmlr->addBlankList();
	gmlr->addBlankList();

	//unknown
	gmlr->addFooter();

	player->sendMessage(gmlr);
}

float ZoneImplementation::getMinX() {
	return -8192;
}

float ZoneImplementation::getMaxX() {
	return 8192;
}

float ZoneImplementation::getMinY() {
	return -8192;
}

float ZoneImplementation::getMaxY() {
	return 8192;
}
