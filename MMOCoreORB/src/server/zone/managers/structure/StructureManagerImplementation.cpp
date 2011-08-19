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
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

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
#include "server/zone/objects/player/sessions/DestroyStructureSession.h"
#include "server/zone/objects/player/sui/callbacks/DeleteAllItemsSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/FindLostItemsSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/StructureStatusSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/NameStructureSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/StructureManageMaintenanceSuiCallback.h"

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
	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	if (!planetManager->isBuildingPermittedAt(x, y)) {
		creature->sendSystemMessage("@player_structure:not_permitted"); //Building is not permitted here.
		return 1;
	}

	if (creature->containsActiveSession(SessionFacadeType::PLACESTRUCTURE))
		return 1;

	ManagedReference<Deed*> deed = dynamic_cast<Deed*>(server->getZoneServer()->getObject(deedID));

	Locker _lock(deed, creature);

	ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

	//Ensure that it is the correct deed, and that it is in a container in the creature's inventory.
	if (deed == NULL || !deed->isASubChildOf(inventory)) {
		creature->sendSystemMessage("@player_structure:no_possession"); //You no longer are in possession of the deed for this structure. Aborting construction.
		return 1;
	}

	TemplateManager* templateManager = TemplateManager::instance();

	String serverTemplatePath = deed->getGeneratedObjectTemplate();
	Reference<SharedStructureObjectTemplate*> serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

	//Check to see if this zone allows this structure.
	if (serverTemplate == NULL || !serverTemplate->isAllowedZone(zone->getZoneName())) {
		creature->sendSystemMessage("@player_structure:wrong_planet"); //That deed cannot be used on this planet.
		return 1;
	}

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != NULL) {
		String abilityRequired = serverTemplate->getAbilityRequired();

		if (!abilityRequired.isEmpty() && !ghost->hasSkill(abilityRequired)) {
			creature->sendSystemMessage("@player_structure:" + abilityRequired);
			return 1;
		}

		int lots = serverTemplate->getLotSize();

		if (!ghost->hasLotsRemaining(lots)) {
			StringIdChatParameter param("@player_structure:not_enough_lots");
			param.setDI(lots);
			creature->sendSystemMessage(param);
			return 1;
		}
	}

	//Validate that the structure can be placed at the given coordinates:
		//Ensure that no other objects impede on this structures footprint, or overlap any city regions or no build areas.
		//Make sure that the player has zoning rights in the area.

	ManagedReference<PlaceStructureSession*> session = new PlaceStructureSession(creature, deed);
	creature->addActiveSession(SessionFacadeType::PLACESTRUCTURE, session);

	//Construct the structure.
	session->constructStructure(x, y, angle);

	//Remove the deed from it's container.
	deed->getParent()->removeObject(deed, true);

	return 0;
}
/*
int StructureManagerImplementation::placeStructureFromDeed(CreatureObject* player, uint64 deedID, float x, float y, int angle) {
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
		z = terrainManager->getHighestHeight(x - w, y - l, x + w, y + l, 1) + 2.f; //Add a little extra to help with terrain issues.

	ManagedReference<SceneObject*> obj = ObjectManager::instance()->createObject(structureTemplatePath.hashCode(), 1, "playerstructures");

	if (obj == NULL || !obj->isStructureObject()) {
		if (obj != NULL)
			obj->destroyObjectFromDatabase(true);

		error("Failed to create structure with template: " + structureTemplatePath);
		return NULL;
	}

	StructureObject* structureObject = (StructureObject*) obj.get();
	structureObject->setOwnerObjectID(creature->getObjectID());
	structureObject->grantPermission("ADMIN", creature->getFirstName());

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

int StructureManagerImplementation::destroyStructure(StructureObject* structureObject) {
	float x = structureObject->getPositionX();
	float y = structureObject->getPositionY();
	float z = zone->getHeight(x, y);

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
					CreatureObject* playerCreature = (CreatureObject*) obj.get();

					playerCreature->teleport(x, z, y, 0);
				}
			}
		}
	}

	//Get the owner of the structure, and remove the structure from their possession.
	ManagedReference<SceneObject*> owner = zone->getZoneServer()->getObject(structureObject->getOwnerObjectID());

	if (owner != NULL) {
		ManagedReference<SceneObject*> ghost = owner->getSlottedObject("ghost");

		if (ghost != NULL && ghost->isPlayerObject()) {
			PlayerObject* playerObject = (PlayerObject*) ghost.get();
			playerObject->removeOwnedStructure(structureObject);
		}
	}

	structureObject->removeFromZone();
	structureObject->destroyObjectFromDatabase(true);

	return 0;
}

String StructureManagerImplementation::getTimeString(uint32 timestamp) {
	String abbrvs[4] = {"seconds", "minutes", "hours", "days"};

	int intervals[4] = {1, 60, 3600, 86400};
	int values[4] = {0, 0, 0, 0};

	StringBuffer str;

	for (int i = 3; i > -1; --i) {
		values[i] = floor((float)timestamp / intervals[i]);
		timestamp -= values[i] * intervals[i];

		if (values[i] > 0) {
			if (str.length() > 0)
				str << ",";

			str << ((i == 0) ? " and " : " ") << values[i] << " " << abbrvs[i];
		}
	}

	return str.toString();
}

int StructureManagerImplementation::declareResidence(CreatureObject* player, StructureObject* structureObject) {
	if (!structureObject->isBuildingObject()) {
		player->sendSystemMessage("@player_structure:residence_must_be_building"); //Your declared residence must be a building.
		return 1;
	}

	PlayerObject* ghost = player->getPlayerObject();

	ManagedReference<BuildingObject*> declaredResidence = ghost->getDeclaredResidence();

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
	ghost->setDeclaredResidence(buildingObject);


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

int StructureManagerImplementation::redeedStructure(CreatureObject* creature) {
	ManagedReference<DestroyStructureSession*> session = dynamic_cast<DestroyStructureSession*>(creature->getActiveSession(SessionFacadeType::DESTROYSTRUCTURE));

	if (session == NULL)
		return 0;

	ManagedReference<StructureObject*> structureObject = session->getStructureObject();

	if (structureObject == NULL)
		return 0;

	ManagedReference<Deed*> deed = dynamic_cast<Deed*>(zone->getZoneServer()->getObject(structureObject->getDeedObjectID()));
	structureObject->setDeedObjectID(0); //Set this to 0 so the deed doesn't get destroyed with the structure.

	int maint = structureObject->getSurplusMaintenance();
	int redeedCost = structureObject->getRedeedCost();

	if (deed != NULL && maint >= redeedCost) {
		Locker _lock(deed, structureObject);

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if (inventory == NULL || inventory->isContainerFull()) {
			creature->sendSystemMessage("@player_structure:inventory_full"); //This installation can not be redeeded because your inventory does not have room to put the deed.
			creature->sendSystemMessage("@player_structure:deed_reclaimed_failed"); //Structure destroy and deed reclaimed FAILED!
			return session->cancelSession();
		} else {
			//TODO: Find a cleaner way of handling this.
			if (deed->isBuildingDeed())
				((BuildingDeed*) deed.get())->setSurplusMaintenance(maint - redeedCost);
			else if (deed->isInstallationDeed()) {
				InstallationDeed* installationDeed = (InstallationDeed*) deed.get();
				installationDeed->setSurplusMaintenance(maint - redeedCost);
				installationDeed->setSurplusPower(structureObject->getSurplusPower());
			}

			inventory->addObject(deed, -1, true);
			creature->sendSystemMessage("@player_structure:deed_reclaimed"); //Structure destroyed and deed reclaimed.
		}
	} else {
		creature->sendSystemMessage("@player_structure:structure_destroyed"); //Structured destroyed.
	}

	destroyStructure(structureObject);

	return session->cancelSession();
}

void StructureManagerImplementation::promptDeleteAllItems(CreatureObject* creature, StructureObject* structure) {
	ManagedReference<SuiMessageBox*> sui = new SuiMessageBox(creature, 0x00);
	sui->setUsingObject(structure);
	sui->setPromptTitle("@player_structure:delete_all_items"); //Delete All Items
	sui->setPromptText("@player_structure:delete_all_items_d"); //This command will delete every object in your house.  Are you ABSOLUTELY sure you want to destroy every object in your house?
	sui->setCancelButton(true, "@cancel");
	sui->setCallback(new DeleteAllItemsSuiCallback(server->getZoneServer()));

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != NULL) {
		ghost->addSuiBox(sui);
		creature->sendMessage(sui->generateMessage());
	}
}

void StructureManagerImplementation::promptFindLostItems(CreatureObject* creature, StructureObject* structure) {
	ManagedReference<SuiMessageBox*> sui = new SuiMessageBox(creature, 0x00);
	sui->setUsingObject(structure);
	sui->setPromptTitle("@player_structure:move_first_item"); //Find Lost Items
	sui->setPromptText("@player_structure:move_first_item_d"); //This command will move the first item in your house to your location...
	sui->setCallback(new FindLostItemsSuiCallback(server->getZoneServer()));

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != NULL) {
		ghost->addSuiBox(sui);
		creature->sendMessage(sui->generateMessage());
	}
}

void StructureManagerImplementation::moveFirstItemTo(CreatureObject* creature, StructureObject* structure) {
	if (!structure->isBuildingObject())
		return;

	ManagedReference<BuildingObject*> building = (BuildingObject*) structure;

	Locker _lock(building, creature);

	for (int i = 0; i < building->getTotalCellNumber(); ++i) {
		ManagedReference<CellObject*> cell = building->getCell(i);

		int size = cell->getContainerObjectsSize();

		for (int i = 0; i < size; ++i) {
			ManagedReference<SceneObject*> childObject = cell->getContainerObject(i);

			if (!building->containsChildObject(childObject) && !childObject->isCreatureObject()) {
				childObject->teleport(creature->getPositionX(), creature->getPositionZ(), creature->getPositionY(), creature->getParentID());
				creature->sendSystemMessage("@player_structure:moved_first_item"); //The first item in your house has been moved to your location.
				return;
			}
		}
	}
}

void StructureManagerImplementation::reportStructureStatus(CreatureObject* creature, StructureObject* structure) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	//Close the window if it is already open.
	ghost->closeSuiWindowType(SuiWindowType::STRUCTURE_STATUS);

	ManagedReference<SuiListBox*> status = new SuiListBox(creature, SuiWindowType::STRUCTURE_STATUS);
	status->setPromptTitle("@player_structure:structure_status_t"); //Structure Status
	status->setPromptText("@player_structure:structure_name_prompt " + structure->getObjectName()->getDisplayedName()); //Structure Name:
	status->setUsingObject(structure);
	status->setOkButton(true, "@refresh");
	status->setCancelButton(true, "@cancel");
	status->setCallback(new StructureStatusSuiCallback(server->getZoneServer()));

	ManagedReference<SceneObject*> ownerObject = server->getZoneServer()->getObject(structure->getOwnerObjectID());

	if (ownerObject != NULL && ownerObject->isCreatureObject()) {
		CreatureObject* owner = (CreatureObject*) ownerObject.get();
		status->addMenuItem("@player_structure:owner_prompt " + owner->getFirstName());
	}

	ManagedReference<SceneObject*> declaredResidence = ghost->getDeclaredResidence();

	if (declaredResidence == structure) {
		status->addMenuItem("@player_structure:declared_residency"); //You have declared your residency here.
	}

	if (structure->isPrivateStructure()) {
		status->addMenuItem("@player_structure:structure_private"); //This structure is private
	} else {
		status->addMenuItem("@player_structure:structure_public"); //This structure is public
	}

	status->addMenuItem("@player_structure:condition_prompt " + String::valueOf((int) ((structure->getMaxCondition() - structure->getConditionDamage()) / structure->getMaxCondition() * 100)) + "%");
	//TODO: Calculate how much time is remaining on the current maintenance pool.
	/*
	ssmpool << dec << "@player_structure:maintenance_pool_prompt " << maintpool; //Maintenance Pool:

	if (maintpool > 0) {
		uint32 seconds = (uint32) floor(((float) maintpool) / (((float) maintrate) / 3600.0f));
		ssmpool << dec << " (" << getTimeString(seconds) << ")";
	}
	*/
	status->addMenuItem("@player_structure:maintenance_pool_prompt " + String::valueOf((int) floor(structure->getSurplusMaintenance())));
	status->addMenuItem("@player_structure:maintenance_rate_prompt " + String::valueOf(structure->getBaseMaintenanceRate()) + " cr/hr");

	if (structure->isInstallationObject()) {
		InstallationObject* installation = (InstallationObject*) structure;

		status->addMenuItem("@player_structure:power_reserve_prompt " + String::valueOf((int) installation->getSurplusPower()));
		status->addMenuItem("@player_structure:power_consumption_prompt " + String::valueOf((int) installation->getBasePowerRate()) + " @player_structure:units_per_hour");
	}

	if (structure->isBuildingObject()) {
		BuildingObject* building = (BuildingObject*) structure;

		status->addMenuItem("@player_structure:items_in_building_prompt " + String::valueOf(building->getCurrentNumberOfPlayerItems())); //Number of Items in Building:
	}

	ghost->addSuiBox(status);
	creature->sendMessage(status->generateMessage());
}

void StructureManagerImplementation::promptNameStructure(CreatureObject* creature, StructureObject* structure) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(creature, SuiWindowType::OBJECT_NAME);
	inputBox->setUsingObject(structure);
	inputBox->setPromptTitle("@base_player:set_name"); //Set Name
	inputBox->setPromptText("@player_structure:structure_name_prompt"); //Structure Name:
	inputBox->setMaxInputSize(128);
	inputBox->setCallback(new NameStructureSuiCallback(server->getZoneServer()));
	inputBox->setForceCloseDistance(32.f);

	ghost->addSuiBox(inputBox);
	creature->sendMessage(inputBox->generateMessage());
}

void StructureManagerImplementation::promptManageMaintenance(CreatureObject* creature, StructureObject* structure, bool allowWithdrawal) {
	int availableCredits = creature->getCashCredits();

	if (availableCredits <= 0) {
		creature->sendSystemMessage("@player_structure:no_money"); //You do not have any money to pay maintenance.
		return;
	}

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	//Get the most up to date maintenance count.
	structure->updateStructureStatus();

	int surplusMaintenance = (int) floor(structure->getSurplusMaintenance());

	ManagedReference<SuiTransferBox*> sui = new SuiTransferBox(creature, SuiWindowType::STRUCTURE_MANAGE_MAINTENANCE);
	sui->setCallback(new StructureManageMaintenanceSuiCallback(server->getZoneServer()));
	sui->setPromptTitle("@player_structure:select_amount"); //Select Amount
	sui->setUsingObject(structure);
	sui->setPromptText("@player_structure:select_maint_amount \n@player_structure:current_maint_pool " + String::valueOf(surplusMaintenance));
	sui->addFrom("@player_structure:total_funds", String::valueOf(availableCredits), String::valueOf(availableCredits), "1");
	sui->addTo("@player_structure:to_pay", "0", "0", "1");

	ghost->addSuiBox(sui);
	creature->sendMessage(sui->generateMessage());
}
