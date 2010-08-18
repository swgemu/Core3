/*
 * StructureManagerImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "engine/engine.h"

#include "server/db/ServerDatabase.h"

#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/zone/Zone.h"

#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/variables/ParameterizedStringId.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"

#include "server/zone/objects/tangible/terminal/bank/BankTerminal.h"
#include "server/zone/objects/tangible/terminal/bazaar/BazaarTerminal.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/terrain/PlanetNames.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/chat/ChatManager.h"

#include "server/zone/objects/tangible/deed/building/BuildingDeed.h"
#include "server/zone/objects/tangible/sign/SignObject.h"
#include "server/zone/objects/tangible/terminal/structure/StructureTerminal.h"
#include "server/zone/objects/tangible/tool/CraftingStation.h"

#include "server/zone/templates/tangible/SharedBuildingObjectTemplate.h"

#include "tasks/StructureConstructionCompleteTask.h"

#include "StructureManager.h"

#include "server/zone/objects/structure/StructureObject.h"

SortedVector<String> StructureManagerImplementation::listOfStaticBuildings;
SortedVector<String> StructureManagerImplementation::createdFiles;

StructureManagerImplementation::StructureManagerImplementation(Zone* zone, ZoneProcessServerImplementation* processor)
		: ManagedObjectImplementation() {

	StructureManagerImplementation::zone = zone;
	StructureManagerImplementation::server = processor;

	//TODO: Move this constructor to the idl
	templateManager = TemplateManager::instance();

	String managerName = "StructureManager ";
	setLoggingName(managerName + Planet::getPlanetName(zone->getZoneID()));

	setGlobalLogging(true);
	setLogging(false);
}

void StructureManagerImplementation::createLuaIncludes() {
	StringBuffer newFile;

	for (int i = 0; i < createdFiles.size(); ++i) {
		String file = createdFiles.get(i);

		String luaFile = file.replaceAll("iff", "aul");
		luaFile = luaFile.replaceAll("object/", "");
		luaFile = luaFile.replaceAll("shared_", "");


		//includeFile("group/group_object.lua")
		newFile << "includeFile(\"" << luaFile << "\")" << endl;
	}

	String completeName = "includeLuas.lua";

	try {
		File* writeFile = new File(completeName);
		FileOutputStream* writer = new FileOutputStream(writeFile);
		writer->write(newFile.toString());
		writer->close();

		delete writer;
		delete writeFile;

		info("created " + completeName, true);
	} catch (Exception& e) {
		error("exception caught creating " + completeName);
		error(e.getMessage());
	} catch (...) {
		error("unknown exception caught creating " + completeName);
	}
}

void StructureManagerImplementation::createNewLuas() {
	for (int i = 0; i < listOfStaticBuildings.size(); ++i) {
		String file = listOfStaticBuildings.get(i);

		if (createdFiles.contains(file))
			continue;

		String newFileName = file.replaceAll("shared_", "");

		String clientObjectName = file.replaceAll("/", "_");
		clientObjectName = clientObjectName.replaceAll(".iff", "");
		String serverObjectName = newFileName.replaceAll("/", "_");
		serverObjectName = serverObjectName.replaceAll(".iff", "");

		int mapType1 = 0, mapType2 = 0, mapType3 = 0, gameObjectType = -1;

		if (file.indexOf("building") != -1 && file.indexOf("cloning") != -1) {
			mapType1 = 5, mapType2 = 0, mapType3 = 0, gameObjectType = SceneObject::CLONINGBUILDING;
		} else if (file.indexOf("building") != -1 && (file.indexOf("starport") != -1 || file.indexOf("hangar") != -1)) {
			mapType1 = 15, mapType2 = 0, mapType3 = 0, gameObjectType = SceneObject::STARPORTBUILDING;
		} else if (file.indexOf("building") != -1 && file.indexOf("capitol") != -1) {
			mapType1 = 4, mapType2 = 0, mapType3 = 0, gameObjectType = SceneObject::CAPITOLBUILDING;
		} else if (file.indexOf("building") != -1 && file.indexOf("hospital") != -1) {
			mapType1 = 13, mapType2 = 0, mapType3 = 0, gameObjectType = SceneObject::MEDICALBUILDING;
		} else if (file.indexOf("building") != -1 && file.indexOf("cantina") != -1) {
			mapType1 = 3, mapType2 = 0, mapType3 = 0, gameObjectType = SceneObject::RECREATIONBUILDING;
		} else if (file.indexOf("building") != -1 && file.indexOf("hotel") != -1) {
			mapType1 = 12, mapType2 = 0, mapType3 = 0, gameObjectType = SceneObject::HOTELBUILDING;
		} else if (file.indexOf("building") != -1 && file.indexOf("guild") != -1) {

			if (file.indexOf("theater") != -1)
				mapType1 = 7, mapType2 = 10, mapType3 = 0, gameObjectType = SceneObject::THEATERBUILDING;
			else if (file.indexOf("combat") != -1)
				mapType1 = 7, mapType2 = 8, mapType3 = 0, gameObjectType = SceneObject::COMBATBUILDING;
			else if (file.indexOf("commerce") != -1)
				mapType1 = 7, mapType2 = 9, mapType3 = 0, gameObjectType = SceneObject::COMMERCEBUILDING;
			else if (file.indexOf("university") != -1)
				mapType1 = 7, mapType2 = 11, mapType3 = 0, gameObjectType = SceneObject::UNIVERSITYBUILDING;
		} else if (file.indexOf("garage") != -1) {
			mapType1 = 6, mapType2 = 0, mapType3 = 0, gameObjectType = SceneObject::GARAGEBUILDING;
		}


		StringBuffer newLua;

		newLua << serverObjectName << " = " << clientObjectName << ":new {" << endl;

		if (gameObjectType != -1)
				newLua << "\tgameObjectType = " << gameObjectType << "," << endl;

		newLua << "\tmapLocationsType1 = " << mapType1 << "," << endl
				<< "\tmapLocationsType2 = " << mapType2 << "," << endl
				<< "\tmapLocationsType3 = " << mapType3 << endl;

		newLua << "}" << endl << endl;

		newLua << "ObjectTemplates:addTemplate(" << serverObjectName << ", \"" << newFileName << "\")";

		String path = "scripts/";
		String luaFileName = newFileName.replaceAll("iff", "aul");

		String completeName = path + luaFileName;

		try {
			File* writeFile = new File(completeName);
			FileOutputStream* writer = new FileOutputStream(writeFile);
			writer->write(newLua.toString());
			writer->close();

			delete writer;
			delete writeFile;

			info("created " + completeName, true);
			createdFiles.put(file);
		} catch (Exception& e) {
			error("exception caught creating " + completeName);
			error(e.getMessage());
		} catch (...) {
			error("unknown exception caught creating " + completeName);
		}

	}

	createLuaIncludes();
}

void StructureManagerImplementation::loadStaticGarages() {
	int planetid = zone->getZoneID();
	ZoneServer* zoneServer = zone->getZoneServer();

	//lock();

	StringBuffer query;

	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid;
	query << " AND file LIKE '%garage%' AND type = 512;";

	ResultSet* result = NULL;

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		BuildingObject* building = NULL;
		uint64 objectID;
		String templateFile;
		float positionX, positionZ, positionY;
		int i = 0;

		while (result->next()) {
			objectID = result->getUnsignedLong(1);

			SceneObject* savedObject = zoneServer->getObject(objectID);

			if (savedObject != NULL)
				continue;

			templateFile = result->getString(3);

			String serverTemplate = templateFile.replaceAll("shared_", "");

			positionX = result->getFloat(8);
			positionZ = result->getFloat(9);
			positionY = result->getFloat(10);

			building = (BuildingObject*) zoneServer->createStaticObject(serverTemplate.hashCode(), objectID);
			building->setStaticObject(true);

			building->initializePosition(positionX, positionZ, positionY);
			building->insertToZone(zone);

			building->updateToDatabase();

			++i;
		}

		if (i > 0)
			info(String::valueOf(i) + " garages loaded", true);

	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadStaticBanks()\n");
	}

	delete result;
}

void StructureManagerImplementation::loadStaticMissionTerminals() {
	int planetid = zone->getZoneID();
	ZoneServer* zoneServer = zone->getZoneServer();

	uint32 bankCRC = String("object/tangible/terminal/shared_terminal_mission.iff").hashCode();
	uint32 serverCRC = String("object/tangible/terminal/terminal_mission.iff").hashCode();

	//lock();

	StringBuffer query;

	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid;
	query << " AND (file = 'object/tangible/terminal/shared_terminal_mission.iff' OR file = 'object/tangible/terminal/shared_terminal_mission_artisan.iff');";

	ResultSet* result = NULL;

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		MissionTerminal* missionTerminal = NULL;
		CellObject* cell = NULL;
		uint64 parentId = 0;
		uint64 objectID = 0;
		float positionX, positionZ, positionY;
		String file;

		while (result->next()) {
			parentId = result->getUnsignedLong(2);
			objectID = result->getUnsignedLong(1);
			file = result->getString(3);

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

			if (file.indexOf("artisan") != -1)
				serverCRC = String("object/tangible/terminal/terminal_mission_artisan.iff").hashCode();
			else
				serverCRC = String("object/tangible/terminal/terminal_mission.iff").hashCode();

			missionTerminal = (MissionTerminal*) zoneServer->createStaticObject(serverCRC, objectID);
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

void StructureManagerImplementation::loadStaticCraftingStations() {
	int planetid = zone->getZoneID();
	ZoneServer* zoneServer = zone->getZoneServer();

	//lock();

	StringBuffer query;

	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid;
	query << " AND file like '%object/tangible/crafting/station%';";

	ResultSet* result = NULL;

	try {
		result = ServerDatabase::instance()->executeQuery(query);

		CraftingStation* craftingStation = NULL;
		CellObject* cell = NULL;
		uint64 parentId = 0;
		uint64 objectID = 0;
		float positionX, positionZ, positionY;
		String file = "";
		uint32 serverCRC = 0;

		while (result->next()) {
			parentId = result->getUnsignedLong(2);
			objectID = result->getUnsignedLong(1);
			file = result->getString(3);

			if(file.indexOf("droid") != -1) {
				info("Ignoring template for " + file);
				continue;
			}

			file = file.replaceAll("shared_", "");
			serverCRC = file.hashCode();

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

					error("crafting station unknown parentid " + String::valueOf(parentId));
					continue;
				}
			} else
				cell = NULL;

			craftingStation = (CraftingStation*) zoneServer->createStaticObject(serverCRC, objectID);

			craftingStation->createChildObjects();

			if(craftingStation == NULL) {
				error("craftingstation '" + file + "' not created from template");
				continue;
			}

			craftingStation->setStaticObject(true);

			if (cell != NULL)
				cell->addObject(craftingStation, -1);

			craftingStation->initializePosition(positionX, positionZ, positionY);
			craftingStation->insertToZone(zone);

			if (cell != NULL)
				cell->updateToDatabase();
			else
				craftingStation->updateToDatabase();
		}
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadStaticCraftingStations()\n");
	}

	delete result;
}

void StructureManagerImplementation::loadStaticBazaars() {
	int planetid = zone->getZoneID();
	ZoneServer* zoneServer = zone->getZoneServer();
	PlanetManager* planetManager = zone->getPlanetManager();

	uint32 bazaarCRC = String("object/tangible/terminal/shared_terminal_bazaar.iff").hashCode();
	uint32 serverCRC = String("object/tangible/terminal/terminal_bazaar.iff").hashCode();

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
				/*if ((region = planetManager->getRegion(positionX, positionY)) == NULL) {
					StringBuffer msg;
					msg << "could not find region for bazaar " << dec << objectID;
					msg << " positionX " << positionX << " positionY " << positionY;
					error(msg.toString());
				}*/

				cell = NULL;
			} else {
				cell = zoneServer->getObject(parentId);
				/*SceneObject* buildingObject = cell->getParent();

				if ((region = planetManager->getRegion(buildingObject->getPositionX(), buildingObject->getPositionY())) == NULL) {
					StringBuffer msg;
					msg << "could not find region for bazaar " << dec << objectID << " parentid " << dec << parentId;
					msg << " positionX " << buildingObject->getPositionX() << " positionY " << buildingObject->getPositionY();
					error(msg.toString());
				}*/
			}

			//String regionCity = region->getName()->getStringID();

			bazaar = (BazaarTerminal*) zoneServer->createStaticObject(serverCRC, objectID);
			//bazaar->setBazaarRegion(regionCity);
			bazaar->setStaticObject(true);

			//region->addBazaar(bazaar);

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
	uint32 serverCRC = String("object/tangible/terminal/terminal_bank.iff").hashCode();

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

			bank = (BankTerminal*) zoneServer->createStaticObject(serverCRC, objectID);
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
			BuildingObject* building = NULL;

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

	//createNewLuas();

	//unlock();
}

void StructureManagerImplementation::loadStaticCells(BuildingObject * building) {
	CellObject* cell = NULL;

	ZoneServer * zoneServer = zone->getZoneServer();

	StringBuffer query;
	query << "SELECT * FROM staticobjects WHERE file = 'object/cell/shared_cell.iff'";
	query << " AND parentid = " << building->getObjectID() << " order by objectid asc";

	uint32 cellCRC = String("object/cell/cell.iff").hashCode();

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

			cell = (CellObject*) server->getZoneServer()->createStaticObject(cellCRC, oid);

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

				file = file.replaceAll("shared_", "");

				info("trying to create " + file);

				buio = (BuildingObject*) server->getZoneServer()->createStaticObject(file.hashCode(), oid);

				if (buio == NULL) {
					error("could not create " + file);
					return NULL;
				}

				buio->initializePosition(x, z, y);
				//float fw, float fx, float fy, float fz
				buio->setDirection(oW, oX, oY, oZ);
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

	StringBuffer msg;
	msg << "StructureManagerImplementation::loadPlayerStructures()";
	info(msg.toString());
	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	//dbManager->loadDatabases();

	ObjectDatabase* playerStructuresDatabase = ObjectDatabaseManager::instance()->loadDatabase("playerstructures", true);

	if (playerStructuresDatabase == NULL)
		info("StructureManagerImplementation::loadPlayerStructures(): There was an error loading the 'playerstructures' database.", true);

	try {
		int planetid = zone->getZoneID();
		uint64 currentZoneObjectID = zone->_getObjectID();
		ObjectDatabaseIterator iterator(playerStructuresDatabase);

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

			if (zoneObjectID != currentZoneObjectID) {
				objectData->clear();
				continue;
			}

			SceneObject* object = server->getZoneServer()->getObject(objectID);

			if (object != NULL)
				object->info("loaded player structure into world", true);
			else {
				error("could not load structure " + String::valueOf(objectID));
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
}

int StructureManagerImplementation::placeStructureFromDeed(PlayerCreature* player, uint64 deedID, float x, float y, int angle) {
	ZoneServer* zoneServer = player->getZoneServer();

	ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();
	ManagedReference<SceneObject*> obj = zoneServer->getObject(deedID);
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (obj == NULL || !obj->isDeedObject()) {
		//Invalid deed object message.
		player->error("invalid deed object");
		return 1;
	}

	if (inventory == NULL || !obj->isASubChildOf(inventory)) {
		//No longer in possession of deed, or deed doesn't belong to you message.
		player->error("deed is not in inventory");
		return 1;
	}

	ManagedReference<Deed*> deed = (Deed*) obj.get();

	String structureTemplateString = deed->getGeneratedObjectTemplate();
	uint32 structureTemplateCRC = structureTemplateString.hashCode();

	SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(structureTemplateCRC));

	if (ssot == NULL) {
		//Invalid template type returned or it didn't exist.
		player->error("invalid template");
		return 1;
	}

	PlanetManager* planetManager = zone->getPlanetManager();
	StringId errorStf;

	if (planetManager->isNoBuildArea(x, y, errorStf)) {
		ParameterizedStringId sendString("player_structure", "city_too_close");
		sendString.setTO(errorStf.getFile(), errorStf.getStringID());

		player->sendSystemMessage(sendString);

		return 1;
	}

	ManagedReference<ActiveArea*> area = player->getActiveArea();


	if (area != NULL) {
		if (area->isRegion()) {

			if (area->isStaticObject()) {
				player->sendSystemMessage("You cant place a structure here");
				return 1;
			}
		} else {
			player->sendSystemMessage("You cant place a structure here");
			return 1;
		}
	}

	if (!ssot->isAllowedZone(zone->getZoneID())) {
		//Message about wrong planet.
		player->error("invalid planet");
		return 1;
	}

	//Check that they can place at this location.
		//A method that accepts a structure template, and x, y coordinates.

	int lotsRemaining = player->getLotsRemaining();
	int lotsRequired = 0;

	//If the player is not an admin, then find out how many lots are required.
	if (playerObject != NULL && !playerObject->isPrivileged())
		lotsRequired = ssot->getLotSize();

	if (lotsRemaining < lotsRequired) {
		ParameterizedStringId stringId;
		stringId.setStringId("@player_structure:not_enough_lots"); //This structure requires %DI lots.
		stringId.setDI(lotsRequired);

		player->sendSystemMessage(stringId);
		return 1;
	}

	ObjectManager* objectManager = ObjectManager::instance();
	ManagedReference<SceneObject*> structure = objectManager->createObject(ssot->getServerObjectCRC(), 1, "playerstructures");

	bool success = false;

	if (structure->isBuildingObject()) {
		success = ((BuildingObject*)structure.get())->checkRequisitesForPlacement(player);

	} else if (structure->isInstallationObject()) {
		success = ((InstallationObject*)structure.get())->checkRequisitesForPlacement(player);
	} else {
		error("structure not a building object nor a installation object for deed " + TemplateManager::instance()->getTemplateFile(deed->getServerObjectCRC()));

		return 1;
	}

	if (!success) {
		structure->destroyObjectFromDatabase(true);

		return 1;
	}

	player->setLotsRemaining(lotsRemaining - lotsRequired);

	inventory->removeObject(obj, true);

	Quaternion direction;
	Vector3 unity(0, 1, 0);
	direction.rotate(unity, angle);

	constructStructure(player, ssot, structure, deedID, x, y, direction);

	return 0;
}

int StructureManagerImplementation::constructStructure(PlayerCreature* player, SharedStructureObjectTemplate* structureTemplate, SceneObject* structure, uint64 deedID, float x, float y, const Quaternion& direction) {
	player->info("constructing structure", true);
	String constructionMarkerTemplateString;
	uint64 constructionMarkerTemplateCRC = constructionMarkerTemplateString.hashCode();

	SharedObjectTemplate* constructionMarkerTemplate = templateManager->getTemplate(constructionMarkerTemplateCRC);

	if (constructionMarkerTemplate == NULL) {
		//Then skip the construction phase and go straight to placement.
		placeStructure(player, structureTemplate, structure, deedID, x, y, direction);
		return 1;
	}

	//Create the construction object, insert it to zone.

	StructureConstructionCompleteTask* task = new StructureConstructionCompleteTask(_this, player, structureTemplate, deedID, x, y, direction, structure);
	task->schedule(3000 * structureTemplate->getLotSize());
	player->info("scheduled place structure in " + String::valueOf(3000 * structureTemplate->getLotSize()) , true);

	return 0;
}

int StructureManagerImplementation::placeStructure(PlayerCreature* player, SharedStructureObjectTemplate* structureTemplate, SceneObject* structure,  uint64 deedID, float x, float y, const Quaternion& direction) {
	//Check to see what type of structure is being placed, then pass off execution.

	if (structureTemplate->isSharedBuildingObjectTemplate()) {
		SharedBuildingObjectTemplate* sbot = (SharedBuildingObjectTemplate*) structureTemplate;
		return placeBuilding(player, sbot, structure, deedID, x, y, direction);

	} else if (structureTemplate->isSharedInstallationObjectTemplate()) {
		SharedInstallationObjectTemplate* siot = (SharedInstallationObjectTemplate*) structureTemplate;
		return placeInstallation(player, siot, structure, deedID, x, y, direction);
	}

	player->error("no right template");

	return 1;
}

int StructureManagerImplementation::placeBuilding(PlayerCreature* player, SharedBuildingObjectTemplate* buildingTemplate,  SceneObject* structure, uint64 deedID, float x, float y, const Quaternion& direction) {
	ZoneServer* zserv = player->getZoneServer();
	ObjectManager* objectManager = ObjectManager::instance();
	TerrainManager* terrainManager = zone->getPlanetManager()->getTerrainManager();

	float z = zone->getHeight(x, y);

	float floraRadius = buildingTemplate->getClearFloraRadius();
	bool snapToTerrain = buildingTemplate->getSnapToTerrain();

	int width = buildingTemplate->getWidth() + 1;
	int length = buildingTemplate->getLength() + 1;

	if (floraRadius > 0 && !snapToTerrain) {
		float maxZ = terrainManager->getHighestHeight(x - width, y - length, x + width, y + length , 4); // checking default 24x24 area with 4 stepping
		z = maxZ;
	}

	int buioCRC = buildingTemplate->getFullTemplateString().hashCode();

	if (!structure->isBuildingObject()) {
		error("structure is not a building object in StructureManagerImplementation::placeBuilding");
		return 1;
	}

	ManagedReference<BuildingObject*> buio = (BuildingObject*) structure;
	buio->createCellObjects();
	buio->createChildObjects();
	buio->setOwnerObjectID(player->getObjectID());
	buio->initializePosition(x, z, y);
	buio->setDirection(direction);
	buio->insertToZone(zone);

	StringBuffer msg;
	msg << "inserted to zone (posX, posZ, posY) = (" << x << ", " << z << ", " << y << ") dir rad = " << buio->getDirection()->getDegrees();
	info(msg.toString(), true);

	/*
	//Create a sign
	String signTemplate = buildingTemplate->getSignTemplate();
	ManagedReference<SignObject*> structureSign = (SignObject*) zserv->createObject(signTemplate.hashCode(), 1);

	if (structureSign != NULL) {
		structureSign->initializePosition(buio->getPositionX() + 16.0f, buio->getPositionZ() + 1.0f, buio->getPositionY());
		structureSign->setDirection(buio->getDirection());
		UnicodeString signName = player->getFirstName() + "'s House";
		structureSign->setObjectName(signName);
		buio->setSignObject(structureSign);
		structureSign->insertToZone(zone);
		structureSign->updateToDatabase();
	}*/

	//Create a structure terminal
	String terminalTemplate = "object/tangible/terminal/terminal_player_structure.iff";
	StructureTerminalLocation* structureTerminalLocation = buildingTemplate->getStructureTerminalLocation();

	if (structureTerminalLocation != NULL) {
		ManagedReference<CellObject*> cell = buio->getCell(structureTerminalLocation->getCellNumber());

		if (cell != NULL) {
			ManagedReference<StructureTerminal*> structureTerminal = (StructureTerminal*) zserv->createObject(terminalTemplate.hashCode(), 1);

			if (structureTerminal != NULL) {
				structureTerminal->initializePosition(structureTerminalLocation->getPositionX(), structureTerminalLocation->getPositionZ(), structureTerminalLocation->getPositionY());
				structureTerminal->setDirection(structureTerminalLocation->getDirection());
				structureTerminal->setStructureObject(buio);

				//Add the structure terminal to the cell
				cell->addObject(structureTerminal, -1, true);
				cell->broadcastObject(structureTerminal, false);
				structureTerminal->insertToZone(zone);

				structureTerminal->updateToDatabase();
			}
		}
	}

	//Store the deed's objectid so that if the player redeed's the structure, he/she can retrieve the deed from the database.
	buio->setDeedObjectID(deedID);
	buio->notifyStructurePlaced(player);

	buio->updateToDatabase();

	//Send out email informing the user that their construction has completed successfully.
	ManagedReference<ChatManager*> chatManager = zserv->getChatManager();

	if (chatManager != NULL) {
		ParameterizedStringId emailBody;
		emailBody.setStringId("@player_structure:construction_complete");
		emailBody.setTO(buio->getObjectName());
		emailBody.setDI(player->getLotsRemaining());
		UnicodeString subject = "@player_structure:construction_complete_subject";
		chatManager->sendMail("@player_structure:construction_complete_sender", subject, emailBody, player->getFirstName());
	}

	//Waypoint
	ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();

	if (playerObject != NULL) {
		String full;
		if (buio->getCustomObjectName().isEmpty())
			buio->getObjectName()->getFullPath(full);
		else
			full = buio->getCustomObjectName().toString();

		String waypointTemplate("object/waypoint/world_waypoint_blue.iff");
		ManagedReference<WaypointObject*> waypointObject = (WaypointObject*) zserv->createObject(waypointTemplate.hashCode(), 1);
		waypointObject->setCustomName(full);
		waypointObject->setActive(true);
		waypointObject->setPosition(x, z, y);
		waypointObject->setPlanetCRC(zone->getPlanetName().hashCode());
		playerObject->addWaypoint(waypointObject, true);
	}

	return 0;
}

int StructureManagerImplementation::placeInstallation(PlayerCreature* player, SharedInstallationObjectTemplate* installationTemplate, SceneObject* structure, uint64 deedID, float x, float y, const Quaternion& direction) {
	ZoneServer* zserv = player->getZoneServer();
	ObjectManager* objectManager = ObjectManager::instance();
	TerrainManager* terrainManager = zone->getPlanetManager()->getTerrainManager();

	float z = zone->getHeight(x, y);

	float floraRadius = installationTemplate->getClearFloraRadius();
	bool snapToTerrain = installationTemplate->getSnapToTerrain();

	int width = installationTemplate->getWidth() + 1;
	int length = installationTemplate->getLength() + 1;

	if (floraRadius > 0 && !snapToTerrain) {
		float maxZ = terrainManager->getHighestHeight(x - width, y - length, x + width, y + length, 4); // checking default 24x24 area with 4 stepping
		z = maxZ;
	}

	int installationTemplateCRC = installationTemplate->getFullTemplateString().hashCode();

	if (!structure->isInstallationObject()) {
		error("structure is not an installation object in StructureManagerImplementation::placeInstallation");
		return 1;
	}

	ManagedReference<InstallationObject*> installation = (InstallationObject*) structure;
	installation->setOwnerObjectID(player->getObjectID());
	installation->createChildObjects();
	installation->initializePosition(x, z, y);
	installation->setDirection(direction);

	installation->insertToZone(zone);

	StringBuffer msg;
	msg << "inserted to zone (posX, posZ, posY) = (" << x << ", " << z << ", " << y << ") dir rad = " << installation->getDirection()->getDegrees();
	info(msg.toString(), true);

	//Store the deed's objectid so that if the player redeed's the structure, he/she can retrieve the deed from the database.
	installation->setDeedObjectID(deedID);
	installation->notifyStructurePlaced(player);
	installation->updateToDatabase();

	//Waypoint
	ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();

	if (playerObject != NULL) {
		String full;
		if (installation->getCustomObjectName().isEmpty())
			installation->getObjectName()->getFullPath(full);
		else
			full = installation->getCustomObjectName().toString();

		String waypointTemplate("object/waypoint/world_waypoint_blue.iff");
		ManagedReference<WaypointObject*> waypointObject = (WaypointObject*) zserv->createObject(waypointTemplate.hashCode(), 1);
		waypointObject->setCustomName(full);
		waypointObject->setActive(true);
		waypointObject->setPosition(x, z, y);
		waypointObject->setPlanetCRC(zone->getPlanetName().hashCode());
		playerObject->addWaypoint(waypointObject, true);
	}

	//Send out email informing the user that their construction has completed successfully.
	ManagedReference<ChatManager*> chatManager = zserv->getChatManager();

	if (chatManager != NULL) {
		ParameterizedStringId emailBody;
		emailBody.setStringId("@player_structure:construction_complete");
		emailBody.setTO(installation->getObjectName());
		emailBody.setDI(player->getLotsRemaining());
		UnicodeString subject = "@player_structure:construction_complete_subject";
		chatManager->sendMail("@player_structure:construction_complete_sender", subject, emailBody, player->getFirstName());
	}

	return 0;
}

int StructureManagerImplementation::destroyStructure(PlayerCreature* player, StructureObject* structureObject) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return 0;

	float x = structureObject->getPositionX();
	float y = structureObject->getPositionY();
	float z = structureObject->getZone()->getHeight(x, y);

	if (structureObject->isBuildingObject()) {
		ManagedReference<BuildingObject*> buildingObject = (BuildingObject*) structureObject;

		for (int i = 0; i < buildingObject->getTotalCellNumber(); ++i) {
			ManagedReference<CellObject*> cellObject = buildingObject->getCell(i);

			int childObjects = cellObject->getContainerObjectsSize();

			if (cellObject == NULL || childObjects <= 0)
				continue;

			//Traverse the vector backwards since the size will change as objects are removed.
			for (int j = childObjects - 1; j >= 0; --j) {
				ManagedReference<SceneObject*> obj = cellObject->getContainerObject(j);

				if (obj->isPlayerCreature()) {
					ManagedReference<PlayerCreature*> playerCreature = (PlayerCreature*) obj.get();

					playerCreature->teleport(x, z, y, 0);
				}
			}
		}
	}

	structureObject->removeFromZone();

	int lotsRemaining = player->getLotsRemaining();

	player->setLotsRemaining(lotsRemaining + structureObject->getLotSize());

	structureObject->destroyObjectFromDatabase(true);

	player->sendSystemMessage("@player_structure:structure_destroyed"); //Structure destroyed.

	return 0;
}

int StructureManagerImplementation::redeedStructure(PlayerCreature* player, StructureObject* structureObject, bool destroy) {
	if (structureObject->getDeedObjectID() == 0) {
		//No deed exists for this structure.
		return 0;
	}

	ZoneServer* zoneServer = player->getZoneServer();

	ManagedReference<SceneObject*> obj = zoneServer->getObject(structureObject->getDeedObjectID());

	if (obj != NULL && obj->isDeedObject()) {
		ManagedReference<Deed*> deed = (Deed*) obj.get();

		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if (inventory != NULL) {
			inventory->addObject(deed, -1, true);
		}
	}

	//Since we have retrieved the deed, set the structures deed id to 0 so that it doesn't get deleted.
	structureObject->setDeedObjectID(0);

	if (destroy)
		destroyStructure(player, structureObject);

	return 0;
}

int StructureManagerImplementation::sendDestroyConfirmTo(PlayerCreature* player, StructureObject* structureObject) {
	if (structureObject == NULL)
		return 0;

	if (!structureObject->isOwnerOf(player)) {
		player->sendSystemMessage("@player_structure:destroy_must_be_owner"); //You must be the owner to destroy a structure.
		return 0;
	}

	String full;
	if (structureObject->getCustomObjectName().isEmpty())
		structureObject->getObjectName()->getFullPath(full);
	else
		full = structureObject->getCustomObjectName().toString();

	String red = "\\#FF6347";
	String green = "\\#32CD32";
	String close = "\\#.";

	String no = red + " @player_structure:can_redeed_no_suffix " + close;
	String yes = green + " @player_structure:can_redeed_yes_suffix " + close;

	String redeed = (structureObject->isRedeedable()) ? yes : no;

	StringBuffer maint;
	maint << "@player_structure:redeed_maintenance " << ((structureObject->isRedeedable()) ? green : red) << structureObject->getSurplusMaintenance() << "/" << structureObject->getRedeedCost() << close;

	StringBuffer entry;
	entry << "@player_structure:confirm_destruction_d1 ";
	entry << "@player_structure:confirm_destruction_d2 \n\n";
	entry << "@player_structure:confirm_destruction_d3a ";
	entry << green << " @player_structure:confirm_destruction_d3b " << close << " ";
	entry << "@player_structure:confirm_destruction_d4 \n";
	entry << "@player_structure:redeed_confirmation " << redeed;

	StringBuffer cond;
	cond << "@player_structure:redeed_condition \\#32CD32 " << (structureObject->getMaxCondition() - structureObject->getConditionDamage()) << "/" << structureObject->getMaxCondition() << "\\#.";

	SuiListBox* destroybox = new SuiListBox(player, SuiWindowType::STRUCTURE_DESTROY_CONFIRM);
	destroybox->setCancelButton(true, "@no");
	destroybox->setOkButton(true, "@yes");
	destroybox->setUsingObject(structureObject);
	destroybox->setPromptTitle(full);
	destroybox->setPromptText(entry.toString());
	destroybox->addMenuItem("@player_structure:can_redeed_alert " + redeed);
	destroybox->addMenuItem(cond.toString());
	destroybox->addMenuItem(maint.toString());

	player->addSuiBox(destroybox);
	player->sendMessage(destroybox->generateMessage());

	return 0;
}

int StructureManagerImplementation::sendDestroyCodeTo(PlayerCreature* player, StructureObject* structureObject) {
	if (structureObject == NULL)
		return 0;

	if (!structureObject->isOwnerOf(player)) {
		player->sendSystemMessage("@player_structure:destroy_must_be_owner"); //You must be the owner to destroy a structure.
		return 0;
	}

	//Generate a new destroy code.
	uint32 destroyCode = structureObject->generateDestroyCode();

	String red = "\\#FF6347";
	String green = "\\#32CD32";
	String close = "\\#.";

	String no = red + " @player_structure:will_not_redeed_confirm " + close;
	String yes = green + " @player_structure:will_redeed_confirm " + close;

	String redeed = (structureObject->isRedeedable()) ? yes : no;

	StringBuffer entry;
	entry << "@player_structure:your_structure_prefix ";
	entry << redeed << " @player_structure:will_redeed_suffix \n\n";
	entry << "Code: " << destroyCode;

	SuiInputBox* destroycodebox = new SuiInputBox(player, SuiWindowType::STRUCTURE_DESTROY_CODE, 0);
	destroycodebox->setUsingObject(structureObject);
	destroycodebox->setPromptTitle("@player_structure:confirm_destruction_t"); //Confirm Structure Deletion
	destroycodebox->setPromptText(entry.toString());
	destroycodebox->setCancelButton(true, "@cancel");
	destroycodebox->setMaxInputSize(6);

	player->addSuiBox(destroycodebox);
	player->sendMessage(destroycodebox->generateMessage());
	return 0;
}

String StructureManagerImplementation::getTimeString(uint32 timestamp) {
	String abbrvs[4] = {"seconds", "minutes", "hours", "days"};

	int intervals[4] = {1, 60, 3600, 86400};
	int values[4] = {0, 0, 0, 0};

	StringBuffer str;

	for (int i = 3; i > -1; --i) {
		values[i] = floor(timestamp / intervals[i]);
		timestamp -= values[i] * intervals[i];

		if (values[i] > 0) {
			if (str.length() > 0)
				str << ",";

			str << ((i == 0) ? " and " : " ") << values[i] << " " << abbrvs[i];
		}
	}

	return str.toString();
}

int StructureManagerImplementation::sendStructureStatusTo(PlayerCreature* player, StructureObject* structureObject) {
	//TODO: Add in extra status information for administrators.
	ManagedReference<SuiListBox*> statusBox = new SuiListBox(player, SuiWindowType::STRUCTURE_STATUS);
	statusBox->setPromptTitle("@player_structure:structure_status_t"); //Structure Status

	if (structureObject->isInstallationObject())
		((InstallationObject*) structureObject)->updateInstallationWork();

	String full;
	if (structureObject->getCustomObjectName().isEmpty())
		structureObject->getObjectName()->getFullPath(full);
	else
		full = structureObject->getCustomObjectName().toString();

	statusBox->setPromptText("@player_structure:structure_name_prompt " + full); //Structure Name:

	ManagedReference<PlayerCreature*> playerCreature = (PlayerCreature*) structureObject->getZoneServer()->getObject(structureObject->getOwnerObjectID());
	statusBox->addMenuItem("@player_structure:owner_prompt  " + playerCreature->getFirstName());

	if (structureObject->isBuildingObject()) {
		ManagedReference<BuildingObject*> buildingObject = (BuildingObject*) structureObject;

		if (buildingObject->isDeclaredResidency())
			statusBox->addMenuItem("@player_structure:declared_residency"); //You have declared your residency here.
	}

	if (structureObject->isPublicStructure())
		statusBox->addMenuItem("@player_structure:structure_public"); //This structure is public
	else
		statusBox->addMenuItem("@player_structure:structure_private"); //This structure is private

	StringBuffer sscond, ssmpool, ssmrate, ssppool, ssprate, ssnitems;

	sscond << dec << "@player_structure:condition_prompt " << ((int) (((structureObject->getMaxCondition() - structureObject->getConditionDamage()) / structureObject->getMaxCondition()) * 100)) << "%";
	statusBox->addMenuItem(sscond.toString());

	int maintpool = structureObject->getSurplusMaintenance();
	int maintrate = structureObject->getBaseMaintenanceRate();

	ssmpool << dec << "@player_structure:maintenance_pool_prompt " << maintpool; //Maintenance Pool:

	if (maintpool > 0) {
		uint32 seconds = (uint32) floor(((float) maintpool) / (((float) maintrate) / 3600.0f));
		ssmpool << dec << " (" << getTimeString(seconds) << ")";
	}

	statusBox->addMenuItem(ssmpool.toString());

	ssmrate << dec << "@player_structure:maintenance_rate_prompt " << maintrate << " cr/hr";
	statusBox->addMenuItem(ssmrate.toString());

	if (structureObject->isInstallationObject() && !((InstallationObject*) structureObject)->isGeneratorObject()) {
		ssppool << dec << "@player_structure:power_reserve_prompt " << (int) structureObject->getSurplusPower();
		statusBox->addMenuItem(ssppool.toString());

		ssprate << dec << "@player_structure:power_consumption_prompt " << (int) structureObject->getBasePowerRate() << " @player_structure:units_per_hour";
		statusBox->addMenuItem(ssprate.toString());
	}

	if (structureObject->isBuildingObject())
		//TODO: Count items that can be picked up by the player (exclude terminals like structure, elevator, guild)...
		ssnitems << dec << "@player_structure:items_in_building_prompt " << (int) 0; //Number of Items in Building:

	player->addSuiBox(statusBox);
	player->sendMessage(statusBox->generateMessage());

	return 0;
}

int StructureManagerImplementation::handlePayMaintenance(PlayerCreature* player, StructureObject* structureObject) {
	try {
		StringBuffer sstext, sscash, ssmaintenance;

		ManagedReference<SuiTransferBox*> maintenanceBox = new SuiTransferBox(player, SuiWindowType::STRUCTURE_MANAGE_MAINTENANCE);
		maintenanceBox->setUsingObject(structureObject);
		maintenanceBox->setPromptTitle("@player_structure:select_amount");

		sstext << "@player_structure:select_maint_amount \n"
			   << "@player_structure:current_maint_pool " << (int) structureObject->getSurplusMaintenance();
		maintenanceBox->setPromptText(sstext.toString());

		sscash << player->getCashCredits();
		ssmaintenance << structureObject->getSurplusMaintenance();

		maintenanceBox->addFrom("@player_structure:total_funds", sscash.toString(), sscash.toString(), "1");
		maintenanceBox->addTo("@player_structure:to_pay", ssmaintenance.toString(), ssmaintenance.toString(), "1");

		player->addSuiBox(maintenanceBox);
		player->sendMessage(maintenanceBox->generateMessage());

	} catch(...) {
		error("unreported exception in InstallationObjectImplementation::handleStructureManageMaintenance");
	}

	return 0;
}

int StructureManagerImplementation::handleWithdrawMaintenance(PlayerCreature* player, StructureObject* structureObject) {
	/**
		string/en/player_structure.stf	withdrawal_failed		Withdrawal from treasury failed.
		string/en/player_structure.stf	withdraw_admin_only		You must be an administrator to remove credits from the treasury.
		string/en/player_structure.stf	withdraw_credits		You withdraw %DI credits from the treasury.
		string/en/player_structure.stf	withdraw_maintenance	Withdraw From Treasury
		string/en/player_structure.stf	withdraw_vendor_d		Enter the amount of credits you would like to withdraw from the maintenance account.
	 */
	return 0;
}

int StructureManagerImplementation::handleDeclareResidency(PlayerCreature* player, StructureObject* structureObject) {
	if (!structureObject->isBuildingObject()) {
		player->sendSystemMessage("@player_structure:residence_must_be_building"); //Your declared residence must be a building.
		return 1;
	}

	ManagedReference<BuildingObject*> buildingObject = (BuildingObject*) structureObject;

	//TODO: Register the building with the city if possible...

	if (!buildingObject->isOwnerOf(player)) {
		player->sendSystemMessage("@player_structure:declare_must_be_owner"); //You must be the owner of the building to declare residence.
		return 1;
	}

	if (buildingObject->isDeclaredResidency()) {
		player->sendSystemMessage("@player_structure:already_residence"); //This building is already your residence.
		return 1;
	}

	buildingObject->setDeclaredResidency(true);

	player->sendSystemMessage("@player_structure:change_residence"); //You change your residence to this building.

	//TODO: Input time limit on changing residence.

	return 0;
}

int StructureManagerImplementation::handlePrivacyChange(PlayerCreature* player, StructureObject* structureObject) {
	structureObject->setPublicStructure(!structureObject->isPublicStructure());

	if (structureObject->isPublicStructure())
		player->sendSystemMessage("@player_structure:structure_now_public"); //This structure is now public
	else
		player->sendSystemMessage("@player_structure:structure_now_private"); //This structure is now private

	//TODO: Update all players in the area with the cell permission changes...

	return 0;
}

int StructureManagerImplementation::sendStructureNamePromptTo(PlayerCreature* player, StructureObject* structureObject) {
	ManagedReference<SuiInputBox*> setTheName = new SuiInputBox(player, SuiWindowType::OBJECT_NAME, 0x00);

	setTheName->setPromptTitle("@sui:set_name_title");
	setTheName->setPromptText("@sui:set_name_prompt");
	setTheName->setUsingObject(structureObject);

	player->addSuiBox(setTheName);
	player->sendMessage(setTheName->generateMessage());

	return 0;
}
