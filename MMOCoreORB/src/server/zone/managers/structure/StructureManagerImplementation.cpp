/*
 * StructureManagerImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "engine/engine.h"

#include "server/db/ServerDatabase.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/Zone.h"

#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/building/city/CityHallObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"

#include "server/zone/objects/tangible/Container.h"
#include "server/zone/objects/tangible/terminal/gambling/GamblingTerminal.h"
#include "server/zone/objects/tangible/terminal/bank/BankTerminal.h"
#include "server/zone/objects/tangible/terminal/vendor/VendorTerminal.h"
#include "server/zone/objects/tangible/terminal/vendor/bazaar/BazaarTerminal.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/tangible/terminal/elevator/ElevatorTerminal.h"

#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/chat/ChatManager.h"

#include "server/zone/objects/tangible/deed/building/BuildingDeed.h"
#include "server/zone/objects/tangible/deed/installation/InstallationDeed.h"
#include "server/zone/objects/tangible/sign/SignObject.h"
#include "server/zone/objects/tangible/terminal/structure/StructureTerminal.h"
#include "server/zone/objects/tangible/tool/CraftingStation.h"

#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"

#include "server/zone/templates/tangible/SharedBuildingObjectTemplate.h"

#include "tasks/StructureConstructionCompleteTask.h"

#include "StructureManager.h"

#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/managers/minigames/events/GamblingEvent.h"

#include "server/zone/templates/footprint/StructureFootprint.h"
#include "server/zone/objects/region/CityRegion.h"

#include "server/zone/objects/player/sessions/PlaceStructureSession.h"

void StructureManagerImplementation::loadPlayerStructures() {

	StringBuffer msg;
	msg << "StructureManagerImplementation::loadPlayerStructures()";
	info(msg.toString());

	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	//dbManager->loadDatabases();

	ObjectDatabase* playerStructuresDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("playerstructures", true);

	if (playerStructuresDatabase == NULL) {
		error("StructureManagerImplementation::loadPlayerStructures(): There was an error loading the 'playerstructures' database.");

		return;
	}

	int i = 0;

	try {
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

			if (object != NULL) {
				//object->info("loaded player structure into world");
				++i;
			} else {
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
	}

	info(String::valueOf(i) + " player structures loaded", true);
}

int StructureManagerImplementation::placeStructureFromDeed(CreatureObject* creature, uint64 deedID, float x, float y, int angle) {
	ManagedReference<PlaceStructureSession*> session = dynamic_cast<PlaceStructureSession*>(creature->getActiveSession(SessionFacadeType::PLACESTRUCTURE));

	if (session == NULL)
		return 1;

	ManagedReference<Deed*> deed = session->getDeed();

	ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

	//Ensure that it is the correct deed, and that it is in a container in the creature's inventory.
	//NOTE: We don't need to null check inventory, because if inventory is NULL, then the isASubChildOf will fail.
	if (deed == NULL || deed->getObjectID() != deedID || !deed->isASubChildOf(inventory)) {

		creature->sendSystemMessage("@player_structure:no_possession"); //You no longer are in possession of the deed for this structure. Aborting construction.

		return session->cancelSession();
	}

	TemplateManager* templateManager = TemplateManager::instance();

	String serverTemplatePath = deed->getGeneratedObjectTemplate();
	SharedStructureObjectTemplate* serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

	if (serverTemplate == NULL)
		return session->cancelSession();

	//Check to see if this zone allows this structure.
	if (!serverTemplate->isAllowedZone(zone->getZoneName())) {
		creature->sendSystemMessage("@player_structure:wrong_planet"); //That deed cannot be used on this planet.
		return session->cancelSession();
	}

	ManagedReference<SceneObject*> ghost = creature->getSlottedObject("ghost");

	//Player specific logic.
	if (ghost != NULL && ghost->isPlayerObject()) {
		PlayerObject* player = (PlayerObject*) ghost.get();

		//Check that the creature has the ability required to place the structure.
		String abilityRequired = serverTemplate->getAbilityRequired();

		if (!abilityRequired.isEmpty() && !player->hasSkill(abilityRequired)) {
			creature->sendSystemMessage("@player_structure:" + abilityRequired);
			return session->cancelSession();
		}
	}

	//Validate that the structure can be placed at the given coordinates:
		//Ensure that no other objects impede on this structures footprint, or overlap any city regions or no build areas.
		//Make sure that it is the right zone.
		//Make sure that the player has zoning rights in the area.

	//Remove the deed from the inventory of the creature.
	//NOTE: deed's parent cannot be NULL here because it was already checked to be in inventory.
	deed->getParent()->removeObject(deed, true);

	//Construct the structure.
	session->constructStructure(x, y, angle);

	return 0;
}
/*
int StructureManagerImplementation::placeStructureFromDeed(PlayerCreature* player, uint64 deedID, float x, float y, int angle) {
	ZoneServer* zoneServer = player->getZoneServer();
	ObjectManager* objectManager = ObjectManager::instance();

	ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (playerObject == NULL || inventory == NULL)
		return 1;

	ManagedReference<SceneObject*> obj = zoneServer->getObject(deedID);

	if (obj == NULL || !obj->isDeedObject()) {
		player->sendSystemMessage("@player_structure:not_a_deed"); //That is not a deed.
		return 1;
	}

	if (!obj->isASubChildOf(player) && !obj->isASubChildOf(inventory)) {
		player->sendSystemMessage("@player_structure:no_possession"); //You no longer are in possession of the deed for this structure. Aborting construction.
		return 1;
	}

	Deed* deed = (Deed*) obj.get();

	String structureTemplateString = deed->getGeneratedObjectTemplate();
	uint32 structureTemplateCRC = structureTemplateString.hashCode();

	SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(structureTemplateCRC));

	if (ssot == NULL) {
		player->error("Invalid template (" + structureTemplateString + ") used in placeStructureFromDeed.");
		return 1;
	}

	String abilityRequired = ssot->getAbilityRequired();

	if (!abilityRequired.isEmpty() && !player->getPlayerObject()->hasSkill(abilityRequired)) {
		player->sendSystemMessage("@player_structure:" + abilityRequired);
		return 1;
	}

	PlanetManager* planetManager = zone->getPlanetManager();
	StringId errorStf;

	if (planetManager->isNoBuildArea(x, y, errorStf)) {
		StringIdChatParameter sendString("player_structure", "city_too_close"); //You cannot place here. It is too close to %TO.
		sendString.setTO(errorStf.getFile(), errorStf.getStringID());
		player->sendSystemMessage(sendString);

		return 1;
	}


	ManagedReference<Region*> region = planetManager->getRegion(x, y);
	ManagedReference<CityHallObject*> cityHall = NULL;

	uint8 reqRank = ssot->getCityRankRequired();

	if (region != NULL) {
		cityHall = region->getCityHall();

		if (cityHall != NULL) {
			uint8 cityRank = cityHall->getCityRank();

			if (cityHall->isZoningEnabled() && !cityHall->hasZoningRights(player->getObjectID())) {
				player->sendSystemMessage("@player_structure:no_rights"); //You don't have the right to place that structure in this city. The mayor or one of the city milita must grant you zoning rights first.
				return 1;
			}

			if (cityRank < reqRank) {
				StringIdChatParameter params;
				params.setStringId("@city/city:rank_req"); //The city must be at least rank %DI (%TO) in order for you to place this structure.
				params.setDI(reqRank);
				params.setTO("@city/city:rank" + String::valueOf(reqRank));

				player->sendSystemMessage(params);
				return 1;
			}
		}
	} else {
		if (reqRank > 0) {
			player->sendSystemMessage("@city/city:build_no_city"); //You must be in a city to place that structure.
			return 1;
		}
	}


	int lotsRemaining = player->getLotsRemaining();
	int lotsRequired = 0;

	//If the player is not an admin, then find out how many lots are required.
	if (playerObject != NULL && !playerObject->isPrivileged())
		lotsRequired = ssot->getLotSize();

	if (lotsRemaining < lotsRequired) {
		StringIdChatParameter stringId;
		stringId.setStringId("@player_structure:not_enough_lots"); //This structure requires %DI lots.
		stringId.setDI(lotsRequired);

		player->sendSystemMessage(stringId);
		return 1;
	}

	ManagedReference<SceneObject*> sobj = objectManager->createObject(structureTemplateCRC, 1, "playerstructures");

	//Make sure its a valid Structure Object
	if (sobj == NULL || !sobj->isStructureObject()) {
		if (sobj != NULL)
			sobj->destroyObjectFromDatabase(true);

		player->error("Object created was not a valid structure object in placeStructure.");
		return 1;
	}

	StructureObject* structureObject = (StructureObject*) sobj.get();

	//Check requisites.
	if (!structureObject->checkRequisitesForPlacement(player)) {
		structureObject->destroyObjectFromDatabase(true);
		return 1;
	}

	//Surplus Maintenance and Power
	if (deed->isBuildingDeed()) {
		BuildingDeed* buildingDeed = (BuildingDeed*) deed;

		structureObject->setSurplusMaintenance(buildingDeed->getSurplusMaintenance());
	}

	if (deed->isInstallationDeed()) {
		InstallationDeed* installationDeed = (InstallationDeed*) deed;

		structureObject->setSurplusMaintenance(installationDeed->getSurplusMaintenance());
		structureObject->setSurplusPower(installationDeed->getSurplusPower());
	}

	player->setLotsRemaining(lotsRemaining - lotsRequired);

	//Remove the deed from it's container.
	ManagedReference<SceneObject*> deedContainer = deed->getParent();

	if (deedContainer != NULL)
		deedContainer->removeObject(deed, true);

	Quaternion direction;
	Vector3 unity(0, 1, 0);
	direction.rotate(unity, angle);

	constructStructure(player, structureObject, ssot, deedID, x, y, direction);

	return 0;
}*/

StructureObject* StructureManagerImplementation::placeStructure(CreatureObject* creature, const String& structureTemplatePath, float x, float y, int angle) {
	TerrainManager* terrainManager = zone->getPlanetManager()->getTerrainManager();
	SharedStructureObjectTemplate* serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(structureTemplatePath.hashCode()));

	if (serverTemplate == NULL)
		return NULL;

	float z = zone->getHeight(x, y);
	float floraRadius = serverTemplate->getClearFloraRadius();
	bool snapToTerrain = serverTemplate->getSnapToTerrain();

	Reference<StructureFootprint*> structureFootprint = serverTemplate->getStructureFootprint();

	float l = 5; //Along the x axis.
	float w = 5; //Along the y axis.

	if (structureFootprint != NULL) {
		//If the angle is odd, then swap them.
		l = (angle & 1) ? structureFootprint->getWidth() : structureFootprint->getLength();
		w = (angle & 1) ? structureFootprint->getLength() : structureFootprint->getWidth();
	}

	//Half the dimensions since we are starting from the center point and going outward.
	l /= 2;
	w /= 2;

	if (floraRadius > 0 && !snapToTerrain)
		z = terrainManager->getHighestHeight(x - w, y - l, x + w, y + l, 1);

	ManagedReference<SceneObject*> obj = ObjectManager::instance()->createObject(structureTemplatePath.hashCode(), 1, "playerstructures");

	if (obj == NULL || !obj->isStructureObject()) {
		if (obj != NULL)
			obj->destroyObjectFromDatabase(true);

		error("Failed to create structure with template: " + structureTemplatePath);
		return NULL;
	}

	StructureObject* structureObject = (StructureObject*) obj.get();

	if (structureObject->isBuildingObject())
		((BuildingObject*) structureObject)->createCellObjects();

	structureObject->setPublicStructure(serverTemplate->isPublicStructure());
	structureObject->initializePosition(x, z, y);
	structureObject->rotate(angle);
	structureObject->insertToZone(zone);
	structureObject->createChildObjects();

	structureObject->notifyStructurePlaced(creature);

	return structureObject;
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

	//int lotsRemaining = player->getLotsRemaining();

	//if (!player->getPlayerObject()->isPrivileged())
		//player->setLotsRemaining(lotsRemaining + structureObject->getLotSize());

	//If the deed object id is not 0, then the deed wasn't reclaimed.
	//NOTICE: This could potentially give an erroneous message if the deed never existed when the structure was placed.
	if (structureObject->getDeedObjectID() != 0)
		player->sendSystemMessage("@player_structure:structure_destroyed"); //Structure destroyed.
	else
		player->sendSystemMessage("@player_structure:deed_reclaimed"); //Structure destroyed and deed reclaimed.

	if (player->getDeclaredResidence() == structureObject)
		player->setDeclaredResidence(NULL);

	structureObject->destroyObjectFromDatabase(true);

	return 0;
}

int StructureManagerImplementation::redeedStructure(PlayerCreature* player, StructureObject* structureObject, bool destroy) {
	ZoneServer* zoneServer = player->getZoneServer();

	int surplusMaintenance = structureObject->getSurplusMaintenance();
	int redeedCost = structureObject->getRedeedCost();

	ManagedReference<SceneObject*> obj = zoneServer->getObject(structureObject->getDeedObjectID());

	if (obj != NULL && obj->isDeedObject()) {
		Deed* deed = (Deed*) obj.get();

		if (surplusMaintenance >= redeedCost) {
			//Enough surplus maintenance exists to redeed the structure.
			ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

			if (inventory != NULL) {
				if (!inventory->hasFullContainerObjects()) {
					//There is room in the inventory for the deed, set its values and put it in the inventory.
					if (deed->isBuildingDeed()) {
						BuildingDeed* buildingDeed = (BuildingDeed*) deed;

						buildingDeed->setSurplusMaintenance(surplusMaintenance - redeedCost);
					} else if (deed->isInstallationDeed()) {
						InstallationDeed* installationDeed = (InstallationDeed*) deed;

						installationDeed->setSurplusMaintenance(surplusMaintenance - redeedCost);

						if (structureObject->isInstallationObject())
							installationDeed->setSurplusPower(((InstallationObject*) structureObject)->getSurplusPower());
					}

					deed->sendTo(player, true);
					inventory->addObject(deed, -1, true);

					//Since we have retrieved the deed, set the structures deed id to 0 so that it doesn't get deleted from the database.
					structureObject->setDeedObjectID(0);
				} else {
					//The deed cant be returned to them because their inventory is full. Abort the deletion of the structure here.
					player->sendSystemMessage("@player_structure:inventory_full"); //This installation can not be redeeded because your inventory does not have room to put the deed.
					return 1;
				}
			}
		} else {
			//Not enough surplus maintenance existed to redeed the structure, destroy the deed but continue with structure destruction.
			deed->destroyObjectFromDatabase(true);
		}
	}

	if (destroy)
		destroyStructure(player, structureObject);

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

int StructureManagerImplementation::declareResidence(PlayerCreature* player, StructureObject* structureObject) {
	if (!structureObject->isBuildingObject()) {
		player->sendSystemMessage("@player_structure:residence_must_be_building"); //Your declared residence must be a building.
		return 1;
	}

	ManagedReference<BuildingObject*> declaredResidence = player->getDeclaredResidence();

	if (declaredResidence != NULL && declaredResidence->isCityHallBuilding()) {
		player->sendSystemMessage("@city/city:mayor_residence_change"); //As a city Mayor, your residence is always the city hall of the city in which you are mayor.  You cannot declare a new residence.
		return 1;
	}

	ManagedReference<BuildingObject*> buildingObject = (BuildingObject*) structureObject;

	if (!buildingObject->isOwnerOf(player)) {
		player->sendSystemMessage("@player_structure:declare_must_be_owner"); //You must be the owner of the building to declare residence.
		return 1;
	}

	//@player_structure:change_residence_time You cannot change residence for %NO hours.

	if (declaredResidence == buildingObject) {
		player->sendSystemMessage("@player_structure:already_residence"); //This building is already your residence.
		return 1;
	}

	if (declaredResidence == NULL) {
		player->sendSystemMessage("@player_structure:declared_residency"); //You have declared your residency here.
	} else {
		player->sendSystemMessage("@player_structure:change_residence"); //You change your residence to this building.
	}

	//Set the characters home location to this structure.
	player->setDeclaredResidence(buildingObject);


	//If in a city, add to the cities citizens
	ManagedReference<CityRegion*> cityRegion = buildingObject->getCityRegion();

	if (cityRegion == NULL)
		return 0; //Not in a city.

	/* TODO: Reimplement
	ManagedReference<CityHallObject*> cityHall = region->getCityHall();

	ManagedReference<CityManager*> cityManager = zone->getCityManager();

	if (cityHall != NULL && !cityHall->isCitizen(player->getObjectID()))
		cityManager->declareCitizenship(cityHall, player);

	//Just need to save the players declared residence
	player->updateToDatabaseWithoutChildren();
	*/

	return 0;
}

int StructureManagerImplementation::changePrivacy(PlayerCreature* player, StructureObject* structureObject) {
	SharedBuildingObjectTemplate* sbot = dynamic_cast<SharedBuildingObjectTemplate*>(templateManager->getTemplate(structureObject->getServerObjectCRC()));

	if (sbot != NULL && sbot->isAlwaysPublic()) {
		player->sendSystemMessage("@player_structure:force_public"); //This structure is always public.
		return 0;
	}

	// Check for a vendor before allowing the building to be set to private.
	if (structureObject->isPublicStructure() && structureObject->isBuildingObject()) {
		BuildingObject* buildo = (BuildingObject*) structureObject;

		for (int i = 0; i < buildo->getTotalCellNumber(); ++i) {
			CellObject* cell = buildo->getCell(i);
			if (cell == NULL)
				continue;

			for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				if (cell->getContainerObject(j)->isVendor()) {
					player->sendSystemMessage("@player_structure:vendor_no_private"); //A structure hosting a vendor cannot be declared private.
					return 0;
				}
			}
		}
	}

	structureObject->setPublicStructure(!structureObject->isPublicStructure());

	if (structureObject->isPublicStructure())
		player->sendSystemMessage("@player_structure:structure_now_public"); //This structure is now public
	else
		player->sendSystemMessage("@player_structure:structure_now_private"); //This structure is now private

	if (!structureObject->isBuildingObject())
		return 0;

	ManagedReference<BuildingObject*> buildingObject = (BuildingObject*) structureObject;

	bool allowEntry = buildingObject->isPublicStructure();
	int totalCells = buildingObject->getTotalCellNumber();

	Vector<BaseMessage*> cellMessages;

	for (int i = 0; i < totalCells; ++i) {
		ManagedReference<CellObject*> cell = buildingObject->getCell(i);

		if (cell == NULL)
			continue;

		UpdateCellPermissionsMessage* cellMessage = new UpdateCellPermissionsMessage(cell->getObjectID(), allowEntry);
		cellMessages.add(cellMessage);
	}

	Locker _locker(zone);

	int inRangeObjectCount = buildingObject->inRangeObjectCount();

	//All players outside, that are in range...
	for (int i = 0; i < inRangeObjectCount; ++i) {
		ManagedReference<SceneObject*> obj = (SceneObject*) buildingObject->getInRangeObject(i);;

		if (obj == NULL || !obj->isPlayerCreature() || obj == player)
			continue;


		PlayerCreature* targetPlayer = (PlayerCreature*) obj.get();

		//Permissions shouldnt change for the player if they are on the entry, access, or ban list.
		if (buildingObject->isOnBanList(targetPlayer))
			continue;

		if (buildingObject->isOnEntryList(targetPlayer))
			continue;

		if (buildingObject->isOnAccessList(targetPlayer))
			continue;

		for (int j = 0; j < cellMessages.size(); ++j)
			targetPlayer->sendMessage(cellMessages.get(j)->clone());
	}

	//Delete the messages...
	for (int i = 0; i < cellMessages.size(); ++i) {
		BaseMessage* msg = cellMessages.get(i);
		delete msg;
		msg = NULL;
	}

	_locker.release();

	//Send updates out to all players inside the building...
	for (int i = 0; i < buildingObject->getTotalCellNumber(); ++i) {
		ManagedReference<CellObject*> cellObject = (CellObject*) buildingObject->getCell(i);

		if (cellObject == NULL)
			continue;

		int cellObjectCount = cellObject->getContainerObjectsSize();

		for (int j = cellObjectCount - 1; j >= 0; --j) {
			ManagedReference<SceneObject*> obj = cellObject->getContainerObject(j);

			if (obj == NULL || !obj->isPlayerCreature() || obj == player)
				continue;

			PlayerCreature* targetPlayer = (PlayerCreature*) obj.get();

			Locker _locker(targetPlayer);

			buildingObject->updateCellPermissionsTo(targetPlayer);
		}
	}

	return 0;
}

SceneObject* StructureManagerImplementation::getInRangeParkingGarage(SceneObject* obj, int range) {
	if (obj->getZone() != zone)
		return NULL;

	Locker _locker(zone);

	for (int i = 0; i < obj->inRangeObjectCount(); ++i) {
		SceneObject* scno = (SceneObject*) obj->getInRangeObject(i);

		if (scno == obj)
			continue;

		if (scno->isGarage() && scno->isInRange(obj, range))
			return scno;
	}

	return NULL;
}
