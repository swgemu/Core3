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

#include "server/zone/objects/tangible/terminal/bank/BankTerminal.h"
#include "server/zone/objects/tangible/terminal/bazaar/BazaarTerminal.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/terrain/PlanetNames.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/chat/ChatManager.h"

#include "server/zone/objects/tangible/deed/building/BuildingDeed.h"
#include "server/zone/objects/tangible/sign/SignObject.h"
#include "server/zone/objects/tangible/terminal/structure/StructureTerminal.h"

#include "server/zone/templates/tangible/SharedBuildingObjectTemplate.h"

#include "tasks/StructureConstructionCompleteTask.h"

#include "StructureManager.h"

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
			positionX = result->getFloat(8);
			positionZ = result->getFloat(9);
			positionY = result->getFloat(10);

			building = (BuildingObject*) zoneServer->createStaticObject(templateFile.hashCode(), objectID);
			building->setStaticObject(true);
			building->setStaticGarage(true);

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
				//buio->setDirection(oX, oZ, oY, oW);
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

	player->setLotsRemaining(lotsRemaining - lotsRequired);

	//player->sendDestroyTo(player);
	inventory->removeObject(obj, true);

	Quaternion direction;
	Vector3 unity(0, 1, 0);
	direction.rotate(unity, angle);

	constructStructure(player, ssot, deedID, x, y, direction);

	return 0;
}

int StructureManagerImplementation::constructStructure(PlayerCreature* player, SharedStructureObjectTemplate* structureTemplate, uint64 deedID, float x, float y, const Quaternion& direction) {
	player->info("constructing structure", true);
	String constructionMarkerTemplateString;
	uint64 constructionMarkerTemplateCRC = constructionMarkerTemplateString.hashCode();

	SharedObjectTemplate* constructionMarkerTemplate = templateManager->getTemplate(constructionMarkerTemplateCRC);

	if (constructionMarkerTemplate == NULL) {
		//Then skip the construction phase and go straight to placement.
		placeStructure(player, structureTemplate, deedID, x, y, direction);
		return 1;
	}

	//Create the construction object, insert it to zone.

	StructureConstructionCompleteTask* task = new StructureConstructionCompleteTask(_this, player, structureTemplate, deedID, x, y, direction);
	task->schedule(3000 * structureTemplate->getLotSize());
	player->info("scheduled place structure in " + String::valueOf(3000 * structureTemplate->getLotSize()) , true);

	return 0;
}

int StructureManagerImplementation::placeStructure(PlayerCreature* player, SharedStructureObjectTemplate* structureTemplate, uint64 deedID, float x, float y, const Quaternion& direction) {
	//Check to see what type of structure is being placed, then pass off execution.

	if (structureTemplate->isSharedBuildingObjectTemplate()) {
		SharedBuildingObjectTemplate* sbot = (SharedBuildingObjectTemplate*) structureTemplate;
		return placeBuilding(player, sbot, deedID, x, y, direction);

	} else if (structureTemplate->isSharedInstallationObjectTemplate()) {
		SharedInstallationObjectTemplate* siot = (SharedInstallationObjectTemplate*) structureTemplate;
		return placeInstallation(player, siot, deedID, x, y, direction);
	}

	player->info("no right template", true);

	return 1;
}

int StructureManagerImplementation::placeBuilding(PlayerCreature* player, SharedBuildingObjectTemplate* buildingTemplate, uint64 deedID, float x, float y, const Quaternion& direction) {
	ZoneServer* zserv = player->getZoneServer();
	ObjectManager* objectManager = ObjectManager::instance();
	TerrainManager* terrainManager = zone->getPlanetManager()->getTerrainManager();

	float z = zone->getHeight(x, y);

	/*if (z == 0)
		z = player->getPositionZ();*/

	float maxZ = terrainManager->getHighestHeight(x - 24, y - 24, x + 24, y + 24 , 4); // checking default 24x24 area with 4 stepping
	z = maxZ;

	int buioCRC = buildingTemplate->getFullTemplateString().hashCode();

	ManagedReference<BuildingObject*> buio = (BuildingObject*) objectManager->createObject(buioCRC, 1, "playerstructures");
	buio->createCellObjects();
	buio->setOwnerObjectID(player->getObjectID());
	buio->initializePosition(x, z, y);
	buio->setDirection(direction);
	buio->insertToZone(zone);

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
	String terminalTemplate = "object/tangible/terminal/shared_terminal_player_structure.iff";
	StructureTerminalLocation* structureTerminalLocation = buildingTemplate->getStructureTerminalLocation();

	if (structureTerminalLocation != NULL) {
		ManagedReference<StructureTerminal*> structureTerminal = (StructureTerminal*) zserv->createObject(terminalTemplate.hashCode(), 1);

		if (structureTerminal != NULL) {
			structureTerminal->initializePosition(structureTerminalLocation->getPositionX(), structureTerminalLocation->getPositionZ(), structureTerminalLocation->getPositionY());
			structureTerminal->setDirection(structureTerminalLocation->getDirection());
			structureTerminal->setBuildingObject(buio);

			//Add the structure terminal to the cell
			ManagedReference<CellObject*> cell = buio->getCell(structureTerminalLocation->getCellNumber());
			cell->addObject(structureTerminal, -1, true);
			cell->broadcastObject(structureTerminal, false);
			structureTerminal->insertToZone(zone);

			structureTerminal->updateToDatabase();
		}
	}

	//Store the deed's objectid so that if the player redeed's the structure, he/she can retrieve the deed from the database.
	buio->setDeedObjectID(deedID);

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

	return 0;
}

int StructureManagerImplementation::placeInstallation(PlayerCreature* player, SharedInstallationObjectTemplate* installationTemplate, uint64 deedID, float x, float y, const Quaternion& direction) {
	ZoneServer* zserv = player->getZoneServer();
	ObjectManager* objectManager = ObjectManager::instance();

	float z = zone->getHeight(x, y);
	//float z = player->getPositionZ();

	float maxZ = terrainManager->getHighestHeight(x - 24, y - 24, x + 24, y + 24 , 4); // checking default 24x24 area with 4 stepping
	z = maxZ;

	int installationTemplateCRC = installationTemplate->getFullTemplateString().hashCode();

	ManagedReference<InstallationObject*> installation = (InstallationObject*) objectManager->createObject(installationTemplateCRC, 1, "playerstructures");
	installation->setOwnerObjectID(player->getObjectID());
	installation->initializePosition(x, z, y);
	installation->setDirection(direction);
	installation->insertToZone(zone);

	//Store the deed's objectid so that if the player redeed's the structure, he/she can retrieve the deed from the database.
	installation->setDeedObjectID(deedID);

	installation->updateToDatabase();

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

int StructureManagerImplementation::destroyStructure(PlayerCreature* player, SceneObject* structure) {
	return 0;
}

int StructureManagerImplementation::redeedStructure(PlayerCreature* player, SceneObject* structure) {
	return 0;
}
