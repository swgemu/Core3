/*
 * StructureManagerImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "server/db/ServerDatabase.h"

#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/zone/Zone.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/region/Region.h"

#include "server/zone/objects/tangible/terminal/bank/BankTerminal.h"
#include "server/zone/objects/tangible/terminal/bazaar/BazaarTerminal.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/terrain/PlanetNames.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

#include "StructureManager.h"

StructureManagerImplementation::StructureManagerImplementation(Zone* zone, ZoneProcessServerImplementation* processor) :
	ManagedObjectImplementation() {
	StructureManagerImplementation::zone = zone;
	StructureManagerImplementation::server = processor;

	String managerName = "StructureManager ";
	setLoggingName(managerName + Planet::getPlanetName(zone->getZoneID()));

	setGlobalLogging(true);
	setLogging(false);
}

void StructureManagerImplementation::loadStaticMissionTerminals() {
	int planetid = zone->getZoneID();
	ZoneServer* zoneServer = zone->getZoneServer();

	uint32 bankCRC = String("object/tangible/terminal/shared_terminal_mission.iff").hashCode();

	//lock();

	StringBuffer query;

	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid;
	query << " AND file = 'object/tangible/terminal/shared_terminal_mission.iff';";

	ResultSet* result = NULL;

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		MissionTerminal* missionTerminal = NULL;
		CellObject* cell = NULL;
		uint64 parentId = 0;
		uint64 objectID = 0;
		float positionX, positionZ, positionY;

		while (result->next()) {
			parentId = result->getUnsignedLong(2);
			objectID = result->getUnsignedLong(1);

			SceneObject* savedObject = zoneServer->getObject(objectID);

			if (savedObject != NULL)
				continue;

			positionX = result->getFloat(8);
			positionZ = result->getFloat(9);
			positionY = result->getFloat(10);

			if (parentId != 0) {
				SceneObject* scene = zoneServer->getObject(parentId);

				if (scene != NULL && scene->isCellObject())
					cell = (CellObject*) scene;
				else {
					cell = NULL;

					error("mission terminal unknown parentid " + String::valueOf(parentId));
					continue;
				}
			} else
				cell = NULL;

			missionTerminal = (MissionTerminal*) zoneServer->createStaticObject(bankCRC, objectID);
			missionTerminal->setStaticObject(true);

			if (cell != NULL)
				cell->addObject(missionTerminal, -1);

			missionTerminal->initializePosition(positionX, positionZ, positionY);
			missionTerminal->insertToZone(zone);

			if (cell != NULL)
				cell->updateToDatabase();
			else
				missionTerminal->updateToDatabase();
		}
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadStaticBanks()\n");
	}

	delete result;
}

void StructureManagerImplementation::loadStaticBazaars() {
	int planetid = zone->getZoneID();
	ZoneServer* zoneServer = zone->getZoneServer();
	PlanetManager* planetManager = zone->getPlanetManager();

	uint32 bazaarCRC = String("object/tangible/terminal/shared_terminal_bazaar.iff").hashCode();

	StringBuffer query;

	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid;
	query << " AND file = 'object/tangible/terminal/shared_terminal_bazaar.iff';";

	ResultSet* result = NULL;

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		uint64 parentId = 0;
		uint64 objectID = 0;
		float positionX, positionZ, positionY;
		SceneObject* cell;
		BazaarTerminal* bazaar;

		while (result->next()) {
			parentId = result->getUnsignedLong(2);
			objectID = result->getUnsignedLong(1);

			SceneObject* savedObject = zoneServer->getObject(objectID);

			if (savedObject != NULL)
				continue;

			positionX = result->getFloat(8);
			positionZ = result->getFloat(9);
			positionY = result->getFloat(10);

			Region* region;
			//StringId region;

			if (parentId == 0) {
				if ((region = planetManager->getRegion(positionX, positionY)) == NULL) {
					StringBuffer msg;
					msg << "could not find region for bazaar " << dec << objectID;
					msg << " positionX " << positionX << " positionY " << positionY;
					error(msg.toString());
				}

				cell = NULL;
			} else {
				cell = zoneServer->getObject(parentId);
				SceneObject* buildingObject = cell->getParent();

				if ((region = planetManager->getRegion(buildingObject->getPositionX(), buildingObject->getPositionY())) == NULL) {
					StringBuffer msg;
					msg << "could not find region for bazaar " << dec << objectID << " parentid " << dec << parentId;
					msg << " positionX " << buildingObject->getPositionX() << " positionY " << buildingObject->getPositionY();
					error(msg.toString());
				}
			}

			String regionCity = region->getName()->getStringID();

			bazaar = (BazaarTerminal*) zoneServer->createStaticObject(bazaarCRC, objectID);
			bazaar->setBazaarRegion(regionCity);
			bazaar->setStaticObject(true);

			region->addBazaar(bazaar);

			if (cell != NULL)
				cell->addObject(bazaar, -1);

			bazaar->initializePosition(positionX, positionZ, positionY);
			bazaar->insertToZone(zone);

			if (cell != NULL)
				cell->updateToDatabase();
			else
				bazaar->updateToDatabase();
		}

	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadStaticBazaars()\n");
	}

	delete result;
}

void StructureManagerImplementation::loadStaticBanks() {
	int planetid = zone->getZoneID();
	ZoneServer* zoneServer = zone->getZoneServer();

	uint32 bankCRC = String("object/tangible/terminal/shared_terminal_bank.iff").hashCode();

	//lock();

	StringBuffer query;

	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid;
	query << " AND file = 'object/tangible/terminal/shared_terminal_bank.iff';";

	ResultSet* result = NULL;

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		BankTerminal* bank = NULL;
		CellObject* cell = NULL;
		uint64 parentId = 0;
		uint64 objectID = 0;
		float positionX, positionZ, positionY;

		while (result->next()) {
			parentId = result->getUnsignedLong(2);
			objectID = result->getUnsignedLong(1);

			SceneObject* savedObject = zoneServer->getObject(objectID);

			if (savedObject != NULL)
				continue;

			positionX = result->getFloat(8);
			positionZ = result->getFloat(9);
			positionY = result->getFloat(10);

			if (parentId != 0) {
				SceneObject* scene = zoneServer->getObject(parentId);

				if (scene != NULL && scene->isCellObject())
					cell = (CellObject*) scene;
				else {
					cell = NULL;

					error("bank unknown parentid " + String::valueOf(parentId));
					continue;
				}
			} else
				cell = NULL;

			bank = (BankTerminal*) zoneServer->createStaticObject(bankCRC, objectID);
			bank->setStaticObject(true);

			if (cell != NULL)
				cell->addObject(bank, -1);

			bank->initializePosition(positionX, positionZ, positionY);
			bank->insertToZone(zone);

			if (cell != NULL)
				cell->updateToDatabase();
			else
				bank->updateToDatabase();
		}
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadStaticBanks()\n");
	}

	delete result;

	//unlock();
}

void StructureManagerImplementation::loadStaticBuildings() {
	int planetid = zone->getZoneID();

	//lock();

	StringBuffer query;
	query << "SELECT parentid FROM staticobjects WHERE zoneid = " << planetid;
	query << " AND file = 'object/cell/shared_cell.iff' GROUP BY parentid;";

	try {
		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			BuildingObject * building = NULL;

			uint64 parentId = result->getUnsignedLong(0);

			building = loadStaticBuilding(parentId);

			if (building == NULL) {
				error("Can not add building "+ String::valueOf(parentId) + ". BUILDING DOES NOT EXIST");
				continue;
			}
		}

		delete result;
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadStaticBuildings()\n");
	}

	//unlock();
}

void StructureManagerImplementation::loadStaticCells(BuildingObject * building) {
	CellObject* cell = NULL;

	ZoneServer * zoneServer = zone->getZoneServer();

	StringBuffer query;
	query << "SELECT * FROM staticobjects WHERE file = 'object/cell/shared_cell.iff'";
	query << " AND parentid = " << building->getObjectID();

	try {
		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			uint64 oid = result->getLong(1);
			String file = result->getString(3);

			float oX = result->getFloat(4);
			float oY = result->getFloat(5);
			float oZ = result->getFloat(6);
			float oW = result->getFloat(7);

			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);

			info("loading cell (" + String::valueOf(oid) + ") from mysql db");

			cell = (CellObject*) server->getZoneServer()->createStaticObject(file.hashCode(), oid);

			if (cell == NULL) {
				error("cannot create static cell " + String::valueOf(oid));
				continue;
			}
			cell->initializePosition(x, z, y);
			cell->setDirection(oX, oZ, oY, oW);

			building->addCell(cell);
		}

		delete result;

	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadStaticBuilding");
	}
}

BuildingObject* StructureManagerImplementation::loadStaticBuilding(uint64 oid) {
	BuildingObject* buio = NULL;

	ZoneServer * zoneServer = zone->getZoneServer();

	try {
		ManagedWeakReference<SceneObject*> obj = zoneServer->getObject(oid);

		if (obj != NULL && obj->isBuildingObject()) {
			info("loading building (" + String::valueOf(oid) + ") from static object db");
			buio = (BuildingObject *) obj.get();

		} else {
			StringBuffer query;
			query << "SELECT * FROM staticobjects WHERE objectid = '" << oid << "';";
			ResultSet* result = ServerDatabase::instance()->executeQuery(query);

			if (result->next()) {
				info("loading building (" + String::valueOf(oid) + ") from mysql db");


				String file = result->getString(3);

				float oX = result->getFloat(4);
				float oY = result->getFloat(5);
				float oZ = result->getFloat(6);
				float oW = result->getFloat(7);

				float x = result->getFloat(8);
				float z = result->getFloat(9);
				float y = result->getFloat(10);

				info("trying to create " + file);

				buio = (BuildingObject*) server->getZoneServer()->createStaticObject(file.hashCode(), oid);

				if (buio == NULL) {
					return NULL;
				}

				buio->initializePosition(x, z, y);
				buio->setDirection(oX, oZ, oY, oW);
				buio->setStaticBuilding(true);

				loadStaticCells(buio);

				buio->insertToZone(zone);

				buio->updateToDatabase();
			}

			delete result;
		}
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadStaticBuilding");
	}

	return buio;
}

void StructureManagerImplementation::loadPlayerStructures() {
/*
	StringBuffer msg;
	msg << "StructureManagerImplementation::loadPlayerStructures()";
	info(msg.toString());

	try {
		int planetid = zone->getZoneID();
		uint64 currentZoneObjectID = zone->_getObjectID();

		// This is very unefficient, only do it on server load.
		ObjectDatabase* objectDatabase = ObjectManager::instance()->getObjectDatabase();

		ObjectDatabaseIterator iterator(objectDatabase);

		uint64 objectID;
		ObjectInputStream* objectData = new ObjectInputStream(2000);

		uint64 zoneObjectID = 0;
		int gameObjectType = 0;

		while (iterator.getNextKeyAndValue(objectID, objectData)) {
			if (!Serializable::getVariable<uint64>("zone", &zoneObjectID, objectData)) {
				objectData->clear();
				continue;
			}

			if (!Serializable::getVariable<int>("gameObjectType", &gameObjectType, objectData)) {
				objectData->clear();
				continue;
			}

			if (zoneObjectID != currentZoneObjectID || gameObjectType != 512) {
				objectData->clear();
				continue;
			}

			SceneObject* object = server->getZoneServer()->getObject(objectID);

			if (object != NULL)
				object->info("loaded player building into world", true);
			else {
				error("could not load player building " + String::valueOf(objectID));
			}

			objectData->clear();
		}

		delete objectData;

	} catch (DatabaseException& e) {
		StringBuffer err;
		err << "Loading Player Structures, exception: " << e.getMessage();
		error(err);
		return;
	} catch (...) {
		throw Exception("problem in StructureManagerImplementation::loadPlayerStructures()");
	}
*/
}

