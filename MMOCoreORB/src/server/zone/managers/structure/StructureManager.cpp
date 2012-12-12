/*
 * StructureManager.cpp
 *
 *  Created on: 01/08/2012
 *      Author: swgemu
 */

#include "StructureManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/conf/ConfigManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sessions/PlaceStructureSession.h"
#include "server/zone/objects/player/sessions/DestroyStructureSession.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/callbacks/StructurePayUncondemnMaintenanceSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/FindLostItemsSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/DeleteAllItemsSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/StructureStatusSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/NameStructureSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/StructurePayMaintenanceSuiCallback.h"
#include "server/zone/managers/stringid/StringIdManager.h"

#include "server/zone/managers/gcw/GCWManager.h"

void StructureManager::loadPlayerStructures(const String& zoneName) {

	info("Loading player structures from playerstructures.db");

	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	ObjectDatabase* playerStructuresDatabase =
			ObjectDatabaseManager::instance()->loadObjectDatabase(
					"playerstructures", true);

	if (playerStructuresDatabase == NULL) {
		error("Could not load the player structures database.");
		return;
	}

	int i = 0;

	try {
		ObjectDatabaseIterator iterator(playerStructuresDatabase);

		uint64 objectID;
		ObjectInputStream* objectData = new ObjectInputStream(2000);

		String zoneReference;

		while (iterator.getNextKeyAndValue(objectID, objectData)) {
			if (!Serializable::getVariable<String>("SceneObject.zone",
					&zoneReference, objectData)) {
				objectData->clear();
				continue;
			}

			if (zoneName != zoneReference) {
				objectData->clear();
				continue;
			}

			SceneObject* object = server->getObject(objectID);

			if (object != NULL) {
				++i;

				if(object->isGCWBase()){
					Zone* zone = object->getZone();

					if(zone == NULL)
						return;

					GCWManager* gcwMan = zone->getGCWManager();
					if(gcwMan == NULL)
						return;

					gcwMan->registerGCWBase(cast<BuildingObject*>(object),false);

				}

				if (ConfigManager::instance()->isProgressMonitorActivated())
					printf("\r\tLoading player structures [%d] / [?]\t", i);
			} else {
				error(
						"Failed to deserialize structure with objectID: "
								+ String::valueOf(objectID));
			}

			objectData->clear();
		}

		delete objectData;
	} catch (DatabaseException& e) {
		error(
				"Database exception in StructureManager::loadPlayerStructures(): "
						+ e.getMessage());
	}

	info(String::valueOf(i) + " player structures loaded for " + zoneName + ".",
			true);

}

int StructureManager::placeStructureFromDeed(CreatureObject* creature,
		StructureDeed* deed, float x, float y, int angle) {
	ManagedReference<Zone*> zone = creature->getZone();

	//Already placing a structure?
	if (zone == NULL
			|| creature->containsActiveSession(
					SessionFacadeType::PLACESTRUCTURE))
		return 1;

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	String serverTemplatePath = deed->getGeneratedObjectTemplate();

	if (deed->getFaction() != 0
			&& creature->getFaction() != deed->getFaction()) {
		creature->sendSystemMessage("You are not the correct faction");
		return 1;
	}
	Reference<SharedStructureObjectTemplate*> serverTemplate =
			dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(
					serverTemplatePath.hashCode()));

	//Check to see if this zone allows this structure.
	if (serverTemplate == NULL
			|| !serverTemplate->isAllowedZone(zone->getZoneName())) {
		creature->sendSystemMessage("@player_structure:wrong_planet"); //That deed cannot be used on this planet.
		return 1;
	}

	if (!planetManager->isBuildingPermittedAt(x, y, creature)) {
		creature->sendSystemMessage("@player_structure:not_permitted"); //Building is not permitted here.
		return 1;
	}

	SortedVector<ManagedReference<ActiveArea*> > objects;
	zone->getInRangeActiveAreas(x, y, &objects, true);

	ManagedReference<CityRegion*> city;

	for (int i = 0; i < objects.size(); ++i) {
		ActiveArea* area = objects.get(i).get();

		if (!area->isRegion())
			continue;

		city = dynamic_cast<Region*>(area)->getCityRegion();

		if (city != NULL)
			break;
	}

	int rankRequired = serverTemplate->getCityRankRequired();

	if (city == NULL && rankRequired > 0) {
		creature->sendSystemMessage("@city/city:build_no_city");
		return 1;
	}

	if (city != NULL) {
		if (city->isZoningEnabled()
				&& !city->hasZoningRights(creature->getObjectID())) {
			creature->sendSystemMessage("@player_structure:no_rights"); //You don't have the right to place that structure in this city. The mayor or one of the city milita must grant you zoning rights first.
			return 1;
		}

		if (rankRequired != 0 && city->getCityRank() < rankRequired) {
			StringIdChatParameter param("city/city", "rank_req");
			param.setDI(rankRequired);
			param.setTO("city/city", "rank" + String::valueOf(rankRequired));

			creature->sendSystemMessage(param);
			return 1;
		}

		if (serverTemplate->isUniqueStructure()
				&& city->hasUniqueStructure(
						serverTemplate->getServerObjectCRC())) {
			creature->sendSystemMessage("@player_structure:cant_place_unique"); //This city can only support a single structure of this type.
			return 1;
		}
	}

	Locker _lock(deed, creature);

	//Ensure that it is the correct deed, and that it is in a container in the creature's inventory.
	if (deed == NULL || !deed->isASubChildOf(creature)) {
		creature->sendSystemMessage("@player_structure:no_possession"); //You no longer are in possession of the deed for this structure. Aborting construction.
		return 1;
	}

	TemplateManager* templateManager = TemplateManager::instance();

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != NULL) {
		String abilityRequired = serverTemplate->getAbilityRequired();

		if (!abilityRequired.isEmpty() && !ghost->hasAbility(abilityRequired)) {
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

	ManagedReference<PlaceStructureSession*> session =
			new PlaceStructureSession(creature, deed);
	creature->addActiveSession(SessionFacadeType::PLACESTRUCTURE, session);

	//Construct the structure.
	session->constructStructure(x, y, angle);

	//Remove the deed from it's container.
	deed->destroyObjectFromWorld(true);

	return 0;
}

StructureObject* StructureManager::placeStructure(CreatureObject* creature,
		const String& structureTemplatePath, float x, float y, int angle) {
	ManagedReference<Zone*> zone = creature->getZone();

	info("placestructure from manager",true);
	if (zone == NULL)
		return NULL;

	TerrainManager* terrainManager =
			zone->getPlanetManager()->getTerrainManager();
	SharedStructureObjectTemplate* serverTemplate =
			dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(
					structureTemplatePath.hashCode()));

	if (serverTemplate == NULL) {
		info("server template is null");
		return NULL;

	}
	float z = zone->getHeight(x, y);

	float floraRadius = serverTemplate->getClearFloraRadius();
	bool snapToTerrain = serverTemplate->getSnapToTerrain();

	Reference<StructureFootprint*> structureFootprint =
			serverTemplate->getStructureFootprint();

	float l = 5; //Along the x axis.
	float w = 5; //Along the y axis.
	float zIncreaseWhenNoAvailableFootprint = 0.f; //TODO: remove this when it has been verified that all buildings have astructure footprint.

	if (structureFootprint != NULL) {
		//If the angle is odd, then swap them.
		l = (angle & 1) ? structureFootprint->getWidth() :
				structureFootprint->getLength();
		w = (angle & 1) ? structureFootprint->getLength() :
				structureFootprint->getWidth();
	} else {
		if (!serverTemplate->isCampStructureTemplate())
			warning(
					"Structure with template '" + structureTemplatePath
							+ "' has no structure footprint.");
		zIncreaseWhenNoAvailableFootprint = 5.f;
	}

	//Half the dimensions since we are starting from the center point and going outward.
	l /= 2;
	w /= 2;

	if (floraRadius > 0 && !snapToTerrain)
		z = terrainManager->getHighestHeight(x - w, y - l, x + w, y + l, 1)
				+ zIncreaseWhenNoAvailableFootprint;

	String strDatabase = "playerstructures";

	bool bIsFactionBuilding = (serverTemplate->getGameObjectType()
			== SceneObjectType::FACTIONBUILDING);

	if (bIsFactionBuilding || serverTemplate->getGameObjectType() == SceneObjectType::TURRET) {
		strDatabase = "playerstructures";
	}

	ManagedReference<SceneObject*> obj =
			ObjectManager::instance()->createObject(
					structureTemplatePath.hashCode(), 1, strDatabase);

	if (obj == NULL || !obj->isStructureObject()) {
		if (obj != NULL)
			obj->destroyObjectFromDatabase(true);

		error(
				"Failed to create structure with template: "
						+ structureTemplatePath);
		return NULL;
	}

	StructureObject* structureObject = cast<StructureObject*>(obj.get());
	structureObject->setOwnerObjectID(creature->getObjectID());
	structureObject->grantPermission("ADMIN", creature->getFirstName());
	structureObject->setOwnerName(creature->getFirstName());

	if(structureObject->isTurret()){
		structureObject->setFaction(creature->getFaction());
	}

	BuildingObject* buildingObject = NULL;
	if (structureObject->isBuildingObject()) {
		buildingObject = cast<BuildingObject*>(structureObject);
		if (buildingObject != NULL)
			buildingObject->createCellObjects();
	}
	structureObject->setPublicStructure(serverTemplate->isPublicStructure());
	structureObject->initializePosition(x, z, y);
	structureObject->rotate(angle);
	//structureObject->insertToZone(zone);
	zone->transferObject(structureObject, -1, true);
	structureObject->createChildObjects();

	structureObject->notifyStructurePlaced(creature);

	return structureObject;
}

int StructureManager::destroyStructure(StructureObject* structureObject) {
	ManagedReference<Zone*> zone = structureObject->getZone();

	if (zone == NULL)
		return 0;

	float x = structureObject->getPositionX();
	float y = structureObject->getPositionY();
	float z = zone->getHeight(x, y);

	if (structureObject->isBuildingObject()) {
		ManagedReference<BuildingObject*> buildingObject =
				cast<BuildingObject*>(structureObject);

		for (uint32 i = 1; i <= buildingObject->getTotalCellNumber(); ++i) {
			ManagedReference<CellObject*> cellObject = buildingObject->getCell(
					i);

			int childObjects = cellObject->getContainerObjectsSize();

			if (cellObject == NULL || childObjects <= 0)
				continue;

			//Traverse the vector backwards since the size will change as objects are removed.
			for (int j = childObjects - 1; j >= 0; --j) {
				ManagedReference<SceneObject*> obj =
						cellObject->getContainerObject(j);

				if (obj->isPlayerCreature()) {
					CreatureObject* playerCreature =
							cast<CreatureObject*>(obj.get());

					playerCreature->teleport(x, z, y, 0);
				}
			}
		}

	}

	//Get the owner of the structure, and remove the structure from their possession.
	ManagedReference<SceneObject*> owner = zone->getZoneServer()->getObject(
			structureObject->getOwnerObjectID());

	if (owner != NULL) {
		ManagedReference<SceneObject*> ghost = owner->getSlottedObject("ghost");

		if (ghost != NULL && ghost->isPlayerObject()) {
			PlayerObject* playerObject = cast<PlayerObject*>(ghost.get());
			playerObject->removeOwnedStructure(structureObject);
		}
	}

	structureObject->destroyObjectFromWorld(true);
	structureObject->destroyObjectFromDatabase(true);
	structureObject->notifyObservers(ObserverEventType::OBJECTDESTRUCTION, structureObject, 0);
	return 0;
}

String StructureManager::getTimeString(uint32 timestamp) {
	String abbrvs[4] = { "seconds", "minutes", "hours", "days" };

	int intervals[4] = { 1, 60, 3600, 86400 };
	int values[4] = { 0, 0, 0, 0 };

	StringBuffer str;

	for (int i = 3; i > -1; --i) {
		values[i] = floor((float) timestamp / intervals[i]);
		timestamp -= values[i] * intervals[i];

		if (values[i] > 0) {
			if (str.length() > 0)
				str << ",";

			str << ((i == 0) ? " and " : " ") << values[i] << " " << abbrvs[i];
		}
	}

	return str.toString();
}

int StructureManager::declareResidence(CreatureObject* player,
		StructureObject* structureObject) {
	if (!structureObject->isBuildingObject()) {
		player->sendSystemMessage(
				"@player_structure:residence_must_be_building"); //Your declared residence must be a building.
		return 1;
	}

	if (!player->checkCooldownRecovery("declare_residence")) {
		Time* timeremaining = player->getCooldownTime("declare_residence");
		StringIdChatParameter params("player_structure",
				"change_residence_time"); //You cannot change residence for %NO hours.
		params.setTO(
				String::valueOf(
						ceil(timeremaining->miliDifference() / -3600000.f)));

		player->sendSystemMessage(params);
		return 1;
	}

	ManagedReference<BuildingObject*> buildingObject =
			cast<BuildingObject*>(structureObject);

	if (!buildingObject->isOwnerOf(player)) {
		player->sendSystemMessage("@player_structure:declare_must_be_owner"); //You must be the owner of the building to declare residence.
		return 1;
	}

	PlayerObject* ghost = player->getPlayerObject();
	uint64 objectid = player->getObjectID();

	uint64 declaredOidResidence = ghost->getDeclaredResidence();

	ManagedReference<BuildingObject*> declaredResidence =
			cast<BuildingObject*>(server->getObject(declaredOidResidence));
	ManagedReference<CityRegion*> cityRegion = buildingObject->getCityRegion();

	CityManager* cityManager = server->getCityManager();

	if (declaredResidence != NULL) {
		if (declaredResidence == buildingObject) {
			player->sendSystemMessage("@player_structure:already_residence"); //This building is already your residence.
			return 1;
		}

		ManagedReference<CityRegion*> residentCity =
				declaredResidence->getCityRegion();

		if (residentCity != NULL) {
			Locker lock(residentCity, player);

			if (residentCity->isMayor(objectid)) {
				player->sendSystemMessage("@city/city:mayor_residence_change"); //As a city Mayor, your residence is always the city hall of the city in which you are mayor.  You cannot declare a new residence.
				return 1;
			}

			cityManager->unregisterCitizen(residentCity, player);
		}

		player->sendSystemMessage("@player_structure:change_residence"); //You change your residence to this building.
	} else {
		player->sendSystemMessage("@player_structure:declared_residency"); //You have declared your residency here.
	}

	if (cityRegion != NULL) {
		Locker lock(cityRegion, player);

		if (cityRegion->isMayor(objectid)) {
			player->sendSystemMessage("@city/city:mayor_residence_change"); //As a city Mayor, your residence is always the city hall of the city in which you are mayor.  You cannot declare a new residence.
			return 1;
		}

		cityManager->registerCitizen(cityRegion, player);
	}

	//Set the characters home location to this structure.
	ghost->setDeclaredResidence(buildingObject);

	player->addCooldown("declare_residence", 24 * 3600 * 1000); //1 day

	return 0;
}

SceneObject* StructureManager::getInRangeParkingGarage(SceneObject* obj,
		int range) {
	ManagedReference<Zone*> zone = obj->getZone();

	if (zone == NULL)
		return NULL;

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

	zone->getInRangeObjects(obj->getPositionX(), obj->getPositionY(), 128,
			&closeSceneObjects, true);

	for (int i = 0; i < closeSceneObjects.size(); ++i) {
		SceneObject* scno = cast<SceneObject*>(closeSceneObjects.get(i).get());

		if (scno == obj)
			continue;

		if (scno->isGarage() && scno->isInRange(obj, range))
			return scno;
	}

	return NULL;
}

int StructureManager::redeedStructure(CreatureObject* creature) {
	ManagedReference<DestroyStructureSession*> session =
			dynamic_cast<DestroyStructureSession*>(creature->getActiveSession(
					SessionFacadeType::DESTROYSTRUCTURE));

	if (session == NULL)
		return 0;

	ManagedReference<StructureObject*> structureObject =
			session->getStructureObject();

	if (structureObject == NULL)
		return 0;

	Locker _locker(structureObject);

	ManagedReference<StructureDeed*> deed =
			dynamic_cast<StructureDeed*>(server->getObject(
					structureObject->getDeedObjectID()));

	int maint = structureObject->getSurplusMaintenance();
	int redeedCost = structureObject->getRedeedCost();

	if (deed != NULL && structureObject->isRedeedable()) {
		Locker _lock(deed, structureObject);

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject(
				"inventory");

		if (inventory == NULL || inventory->isContainerFull()) {
			creature->sendSystemMessage("@player_structure:inventory_full"); //This installation can not be redeeded because your inventory does not have room to put the deed.
			creature->sendSystemMessage(
					"@player_structure:deed_reclaimed_failed"); //Structure destroy and deed reclaimed FAILED!
			return session->cancelSession();
		} else {
			deed->setSurplusMaintenance(maint - redeedCost);
			deed->setSurplusPower(structureObject->getSurplusPower());

			structureObject->setDeedObjectID(0); //Set this to 0 so the deed doesn't get destroyed with the structure.

			destroyStructure(structureObject);

			inventory->transferObject(deed, -1, true);
			inventory->broadcastObject(deed, true);
			creature->sendSystemMessage("@player_structure:deed_reclaimed"); //Structure destroyed and deed reclaimed.
		}
	} else {
		destroyStructure(structureObject);
		creature->sendSystemMessage("@player_structure:structure_destroyed"); //Structured destroyed.
	}

	return session->cancelSession();
}

void StructureManager::promptDeleteAllItems(CreatureObject* creature,
		StructureObject* structure) {
	ManagedReference<SuiMessageBox*> sui = new SuiMessageBox(creature, 0x00);
	sui->setUsingObject(structure);
	sui->setPromptTitle("@player_structure:delete_all_items"); //Delete All Items
	sui->setPromptText("@player_structure:delete_all_items_d"); //This command will delete every object in your house.  Are you ABSOLUTELY sure you want to destroy every object in your house?
	sui->setCancelButton(true, "@cancel");
	sui->setCallback(new DeleteAllItemsSuiCallback(server));

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != NULL) {
		ghost->addSuiBox(sui);
		creature->sendMessage(sui->generateMessage());
	}
}

void StructureManager::promptFindLostItems(CreatureObject* creature,
		StructureObject* structure) {
	ManagedReference<SuiMessageBox*> sui = new SuiMessageBox(creature, 0x00);
	sui->setUsingObject(structure);
	sui->setPromptTitle("@player_structure:move_first_item"); //Find Lost Items
	sui->setPromptText("@player_structure:move_first_item_d"); //This command will move the first item in your house to your location...
	sui->setCallback(new FindLostItemsSuiCallback(server));

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != NULL) {
		ghost->addSuiBox(sui);
		creature->sendMessage(sui->generateMessage());
	}
}

void StructureManager::moveFirstItemTo(CreatureObject* creature,
		StructureObject* structure) {
	if (!structure->isBuildingObject())
		return;

	ManagedReference<BuildingObject*> building =
			cast<BuildingObject*>(structure);

	Locker _lock(building, creature);

	for (uint32 i = 1; i <= building->getTotalCellNumber(); ++i) {
		ManagedReference<CellObject*> cell = building->getCell(i);

		int size = cell->getContainerObjectsSize();

		for (int j = 0; j < size; ++j) {
			ManagedReference<SceneObject*> childObject =
					cell->getContainerObject(j);

			//if (!building->containsChildObject(childObject) && !childObject->isCreatureObject()) {
			if (creature->getParent() != NULL
					&& !building->containsChildObject(childObject)
					&& !childObject->isCreatureObject()) {
				if (creature->getParent().get()->getParent().get()
						== childObject->getParent().get()->getParent().get()) {

					childObject->teleport(creature->getPositionX(),
							creature->getPositionZ(), creature->getPositionY(),
							creature->getParentID());
					creature->sendSystemMessage(
							"@player_structure:moved_first_item"); //The first item in your house has been moved to your location.
				}

				return;
			}
		}
	}
}

void StructureManager::reportStructureStatus(CreatureObject* creature,
		StructureObject* structure) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	//Close the window if it is already open.
	ghost->closeSuiWindowType(SuiWindowType::STRUCTURE_STATUS);

	ManagedReference<SuiListBox*> status = new SuiListBox(creature,
			SuiWindowType::STRUCTURE_STATUS);
	status->setPromptTitle("@player_structure:structure_status_t"); //Structure Status
	status->setPromptText(
			"@player_structure:structure_name_prompt "
					+ structure->getDisplayedName()); //Structure Name:
	status->setUsingObject(structure);
	status->setOkButton(true, "@refresh");
	status->setCancelButton(true, "@cancel");
	status->setCallback(new StructureStatusSuiCallback(server));

	ManagedReference<SceneObject*> ownerObject = server->getObject(
			structure->getOwnerObjectID());

	if (ownerObject != NULL && ownerObject->isCreatureObject()) {
		CreatureObject* owner = cast<CreatureObject*>(ownerObject.get());
		status->addMenuItem(
				"@player_structure:owner_prompt " + owner->getFirstName());
	}

	uint64 declaredOidResidence = ghost->getDeclaredResidence();

	ManagedReference<BuildingObject*> declaredResidence =
			cast<BuildingObject*>(server->getObject(declaredOidResidence));

	if (declaredResidence == structure) {
		status->addMenuItem("@player_structure:declared_residency"); //You have declared your residency here.
	}

	if (structure->isPrivateStructure()) {
		status->addMenuItem("@player_structure:structure_private"); //This structure is private
	} else {
		status->addMenuItem("@player_structure:structure_public"); //This structure is public
	}

	status->addMenuItem(
			"@player_structure:condition_prompt "
					+ String::valueOf(structure->getDecayPercentage()) + "%");
	//TODO: Calculate how much time is remaining on the current maintenance pool.
	status->addMenuItem(
			"@player_structure:maintenance_pool_prompt "
					+ String::valueOf(
							(int) floor(
									(float) structure->getSurplusMaintenance())));
	status->addMenuItem(
			"@player_structure:maintenance_rate_prompt "
					+ String::valueOf(structure->getMaintenanceRate())
					+ " cr/hr");

	// property tax
	if(!structure->isCivicStructure() && structure->getCityRegion() != NULL){
		ManagedReference<CityRegion*> city = structure->getCityRegion().get();
		if(city != NULL){
			float propertytax = city->getPropertyTax();
			status->addMenuItem(
							"@city/city:property_tax_prompt : "
									+ String::valueOf(ceil( propertytax / 100.f * structure->getMaintenanceRate()))
									+  " cr/hr");
		}
	}

	status->addMenuItem(
			"@player_structure:maintenance_mods_prompt "
					+ structure->getMaintenanceMods());


	if (structure->isInstallationObject() && !structure->isGeneratorObject()) {
		InstallationObject* installation = cast<InstallationObject*>(structure);

		status->addMenuItem(
				"@player_structure:power_reserve_prompt "
						+ String::valueOf(
								(int) installation->getSurplusPower()));
		status->addMenuItem(
				"@player_structure:power_consumption_prompt "
						+ String::valueOf(
								(int) installation->getBasePowerRate())
						+ " @player_structure:units_per_hour");
	}

	if (structure->isBuildingObject()) {
		BuildingObject* building = cast<BuildingObject*>(structure);

		status->addMenuItem(
				"@player_structure:items_in_building_prompt "
						+ String::valueOf(
								building->getCurrentNumberOfPlayerItems())); //Number of Items in Building:
	}

	ghost->addSuiBox(status);
	creature->sendMessage(status->generateMessage());
}

void StructureManager::promptNameStructure(CreatureObject* creature,
		StructureObject* structure, TangibleObject* object) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(creature,
			SuiWindowType::OBJECT_NAME);
	if (object == NULL) {
		inputBox->setUsingObject(structure);
	} else {
		inputBox->setUsingObject(object);
	}
	inputBox->setPromptTitle("@base_player:set_name"); //Set Name
	inputBox->setPromptText("@player_structure:structure_name_prompt"); //Structure Name:
	inputBox->setMaxInputSize(128);
	inputBox->setCallback(new NameStructureSuiCallback(server));
	inputBox->setForceCloseDistance(32);

	ghost->addSuiBox(inputBox);
	creature->sendMessage(inputBox->generateMessage());
}

void StructureManager::promptPayUncondemnMaintenance(CreatureObject* creature,
		StructureObject* structure) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL) {
		return;
	}

	int uncondemnCost = -structure->getSurplusMaintenance();

	ManagedReference<SuiMessageBox*> sui;
	String text;

	if (creature->getCashCredits() + creature->getBankCredits()
			>= uncondemnCost) {
		//Owner can un-condemn the structure.
		sui = new SuiMessageBox(creature,
				SuiWindowType::STRUCTURE_UNCONDEMN_CONFIRM);
		if (sui == NULL) {
			//TODO: what message should be shown here?
			return;
		}

		//TODO: investigate sui packets to see if it is possible to send StringIdChatParameter directly.
		String textStringId =
				"@player_structure:structure_condemned_owner_has_credits";
		text =
				StringIdManager::instance()->getStringId(
						textStringId.hashCode()).toString();
		text = text.replaceFirst("%DI", String::valueOf(uncondemnCost));

		sui->setCancelButton(true, "@cancel");
		sui->setCallback(
				new StructurePayUncondemnMaintenanceSuiCallback(server));
	} else {
		//Owner cannot un-condemn the structure.
		sui = new SuiMessageBox(creature, SuiWindowType::NONE);
		if (sui == NULL) {
			//TODO: what message should be shown here?
			return;
		}

		//TODO: investigate sui packets to see if it is possible to send StringIdChatParameter directly.
		String textStringId =
				"@player_structure:structure_condemned_owner_no_credits";
		text =
				StringIdManager::instance()->getStringId(
						textStringId.hashCode()).toString();
		text = text.replaceFirst("%DI", String::valueOf(uncondemnCost));

		sui->setCancelButton(false, "@cancel");
	}

	sui->setPromptText(text);
	sui->setOkButton(true, "@ok");
	sui->setPromptTitle("@player_structure:fix_condemned_title");
	sui->setUsingObject(structure);

	ghost->addSuiBox(sui);
	creature->sendMessage(sui->generateMessage());
}

void StructureManager::promptPayMaintenance(StructureObject* structure,
		CreatureObject* creature, SceneObject* terminal) {
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

	int surplusMaintenance = (int) floor(
			(float) structure->getSurplusMaintenance());

	ManagedReference<SuiTransferBox*> sui = new SuiTransferBox(creature,
			SuiWindowType::STRUCTURE_MANAGE_MAINTENANCE);
	sui->setCallback(new StructurePayMaintenanceSuiCallback(server));
	sui->setPromptTitle("@player_structure:select_amount"); //Select Amount
	sui->setUsingObject(structure);
	sui->setPromptText(
			"@player_structure:select_maint_amount \n@player_structure:current_maint_pool "
					+ String::valueOf(surplusMaintenance));
	sui->addFrom("@player_structure:total_funds",
			String::valueOf(availableCredits),
			String::valueOf(availableCredits), "1");
	sui->addTo("@player_structure:to_pay", "0", "0", "1");

	ghost->addSuiBox(sui);
	creature->sendMessage(sui->generateMessage());
}

void StructureManager::payMaintenance(StructureObject* structure,
		CreatureObject* creature, int amount) {
	if (!creature->isInRange(structure, 16.f)
			&& creature->getRootParent() != structure) {
		creature->sendSystemMessage("@player_structure:pay_out_of_range"); //You have moved out of range of your original /payMaintenance target. Aborting...
		return;
	}

	int cash = creature->getCashCredits();

	if (cash < amount) {
		creature->sendSystemMessage("@player_structure:insufficient_funds"); //You have insufficient funds to make this deposit.
		return;
	}

	StringIdChatParameter params("base_player", "prose_pay_success"); //You successfully make a payment of %DI credits to %TT.
	params.setTT(structure->getDisplayedName());
	params.setDI(amount);

	creature->sendSystemMessage(params);

	creature->subtractCashCredits(amount);
	structure->addMaintenance(amount);
}
