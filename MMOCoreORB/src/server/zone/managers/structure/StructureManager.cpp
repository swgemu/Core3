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
#include "server/zone/templates/tangible/SharedBuildingObjectTemplate.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "server/zone/objects/tangible/sign/SignObject.h"
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
#include "server/zone/objects/player/sui/callbacks/StructureAssignDroidSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/NameStructureSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/StructurePayMaintenanceSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/StructureWithdrawMaintenanceSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/StructureSelectSignSuiCallback.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/terrain/layer/boundaries/BoundaryRectangle.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "tasks/DestroyStructureTask.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"

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
			if (!Serializable::getVariable<String>(STRING_HASHCODE("SceneObject.zone"),
					&zoneReference, objectData)) {
				objectData->clear();
				continue;
			}

			if (zoneName != zoneReference) {
				objectData->clear();
				continue;
			}

			Reference<SceneObject*> object = server->getObject(objectID);

			if (object != NULL) {
				++i;

				if(object->isGCWBase()){
					Zone* zone = object->getZone();

					if(zone == NULL)
						return;

					GCWManager* gcwMan = zone->getGCWManager();
					if(gcwMan == NULL)
						return;

					gcwMan->registerGCWBase(cast<BuildingObject*>(object.get()),false);

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

int StructureManager::getStructureFootprint(SharedObjectTemplate* objectTemplate, int angle, float& l0, float& w0, float& l1, float& w1) {
	SharedStructureObjectTemplate* serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(objectTemplate);

	if (serverTemplate == NULL)
		return 1;

	StructureFootprint* structureFootprint = serverTemplate->getStructureFootprint();
	//float l = 5; //Along the x axis.
	//float w = 5; //Along the y axis.

	if (structureFootprint != NULL) {
		//if (structureFootprint->getRowSize() > structureFootprint->getColSize())
		//	angle = angle + 180;

		float centerX = (structureFootprint->getCenterX() * 8) + 4;
		float centerY = (structureFootprint->getCenterY() * 8) + 4;

		//info ("centerX:" + String::valueOf(centerX) + " centerY:" + String::valueOf(centerY), true);

		float topLeftX = -centerX;
		float topLeftY = (structureFootprint->getRowSize() * 8 ) - centerY;

		float bottomRightX = (8 * structureFootprint->getColSize() - centerX);
		float bottomRightY = -centerY;

		w0 = MIN(topLeftX, bottomRightX);
		l0 = MIN(topLeftY, bottomRightY);

		w1 = MAX(topLeftX, bottomRightX);
		l1 = MAX(topLeftY, bottomRightY);

		Matrix4 translationMatrix;
		translationMatrix.setTranslation(0, 0, 0);

		float rad = (float)(angle) * Math::DEG2RAD;

		float cosRad = cos(rad);
		float sinRad = sin(rad);

		Matrix3 rot;
		rot[0][0] = cosRad;
		rot[0][2] = -sinRad;
		rot[1][1] = 1;
		rot[2][0] = sinRad;
		rot[2][2] = cosRad;

		Matrix4 rotateMatrix;
		rotateMatrix.setRotationMatrix(rot);

		Matrix4 moveAndRotate = (translationMatrix * rotateMatrix);

		Vector3 pointBottom(w0, 0, l0);
		Vector3 pointTop(w1, 0, l1);

		Vector3 resultBottom = pointBottom * moveAndRotate;
		Vector3 resultTop = pointTop * moveAndRotate;

		w0 = MIN(resultBottom.getX(), resultTop.getX());
		l0 = MIN(resultBottom.getZ(), resultTop.getZ());

		w1 = MAX(resultTop.getX(), resultBottom.getX());
		l1 = MAX(resultTop.getZ(), resultBottom.getZ());

		//info("objectTemplate:" + objectTemplate->getFullTemplateString() + " :" + structureFootprint->toString(), true);
		//info("angle:" + String::valueOf(angle) + " w0:" + String::valueOf(w0) + " l0:" + String::valueOf(l0) + " w1:" + String::valueOf(w1) + " l1:" + String::valueOf(l1), true);
	}

	return 0;
}

int StructureManager::placeStructureFromDeed(CreatureObject* creature, StructureDeed* deed, float x, float y, int angle) {
	ManagedReference<Zone*> zone = creature->getZone();

	//Already placing a structure?
	if (zone == NULL || creature->containsActiveSession(SessionFacadeType::PLACESTRUCTURE))
		return 1;

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	String serverTemplatePath = deed->getGeneratedObjectTemplate();

	if (deed->getFaction() != 0 && creature->getFaction() != deed->getFaction()) {
		creature->sendSystemMessage("You are not the correct faction");
		return 1;
	}

	Reference<SharedStructureObjectTemplate*> serverTemplate =
			dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

	//Check to see if this zone allows this structure.
	if (serverTemplate == NULL || !serverTemplate->isAllowedZone(zone->getZoneName())) {
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

	SortedVector<ManagedReference<QuadTreeEntry*> > inRangeObjects;
	zone->getInRangeObjects(x, y, 128, &inRangeObjects, true);

	float placingFootprintLength0, placingFootprintWidth0, placingFootprintLength1, placingFootprintWidth1;

	if (!getStructureFootprint(serverTemplate, angle, placingFootprintLength0, placingFootprintWidth0, placingFootprintLength1, placingFootprintWidth1)) {
		float x0 = x + placingFootprintWidth0;
		float y0 = y + placingFootprintLength0;
		float x1 = x + placingFootprintWidth1;
		float y1 = y + placingFootprintLength1;

		BoundaryRectangle placingFootprint(x0, y0, x1, y1);

		//info("placing center x:" + String::valueOf(x) + " y:" + String::valueOf(y), true);
		//info("placingFootprint x0:" + String::valueOf(x0) + " y0:" + String::valueOf(y0) + " x1:" + String::valueOf(x1) + " y1:" + String::valueOf(y1), true);

		for (int i = 0; i < inRangeObjects.size(); ++i) {
			SceneObject* scene = inRangeObjects.get(i).castTo<SceneObject*>();

			if (scene == NULL)
				continue;

			float l0 = -5; //Along the x axis.
			float w0 = -5; //Along the y axis.
			float l1 = 5;
			float w1 = 5;

			if (getStructureFootprint(scene->getObjectTemplate(), scene->getDirectionAngle(), l0, w0, l1, w1))
				continue;

			float xx0 = scene->getPositionX() + (w0 + 0.1);
			float yy0 = scene->getPositionY() + (l0 + 0.1);
			float xx1 = scene->getPositionX() + (w1 - 0.1);
			float yy1 = scene->getPositionY() + (l1 - 0.1);

			BoundaryRectangle rect(xx0, yy0, xx1, yy1);

			//info("existing footprint xx0:" + String::valueOf(xx0) + " yy0:" + String::valueOf(yy0) + " xx1:" + String::valueOf(xx1) + " yy1:" + String::valueOf(yy1), true);

			// check 4 points of the current rect
			if (rect.containsPoint(x0, y0)
					|| rect.containsPoint(x0, y1)
					|| rect.containsPoint(x1, y0)
					|| rect.containsPoint(x1, y1) ) {

				//info("existing footprint contains placing point", true);

				creature->sendSystemMessage("@player_structure:no_room"); //there is no room to place the structure here..

				return 1;
			}

			if (placingFootprint.containsPoint(xx0, yy0)
					|| placingFootprint.containsPoint(xx0, yy1)
					|| placingFootprint.containsPoint(xx1, yy0)
					|| placingFootprint.containsPoint(xx1, yy1)
					|| (xx0 == x0 && yy0 == y0 && xx1 == x1 && yy1 == y1)) {
				//info("placing footprint contains existing point", true);

				creature->sendSystemMessage("@player_structure:no_room"); //there is no room to place the structure here.

				return 1;
			}
		}
	}

	int rankRequired = serverTemplate->getCityRankRequired();

	if (city == NULL && rankRequired > 0) {
		creature->sendSystemMessage("@city/city:build_no_city"); // You must be in a city to place that structure.
		return 1;
	}

	if (city != NULL) {
		if (city->isZoningEnabled() && !city->hasZoningRights(creature->getObjectID())) {
			creature->sendSystemMessage("@player_structure:no_rights"); //You don't have the right to place that structure in this city. The mayor or one of the city milita must grant you zoning rights first.
			return 1;
		}

		if (rankRequired != 0 && city->getCityRank() < rankRequired) {
			StringIdChatParameter param("city/city", "rank_req"); // The city must be at least rank %DI (%TO) in order for you to place this structure.
			param.setDI(rankRequired);
			param.setTO("city/city", "rank" + String::valueOf(rankRequired));

			creature->sendSystemMessage(param);
			return 1;
		}

		if (serverTemplate->isCivicStructure() && !city->isMayor(creature->getObjectID()) ) {
				creature->sendSystemMessage("@player_structure:cant_place_civic");//"This structure must be placed within the borders of the city in which you are mayor."
				return 1;
		}

		if (serverTemplate->isUniqueStructure() && city->hasUniqueStructure(serverTemplate->getServerObjectCRC())) {
			creature->sendSystemMessage("@player_structure:cant_place_unique"); //This city can only support a single structure of this type.
			return 1;
		}
	}

	Locker _lock(deed, creature);


	if(serverTemplate->isDerivedFrom("object/building/faction_perk/base/shared_factional_building_base.iff")){
		Zone* zone = creature->getZone();
		if(zone == NULL)
			return 1;

		GCWManager* gcwMan = zone->getGCWManager();
		if(gcwMan == NULL)
			return 1;

		if(!gcwMan->canPlaceMoreBases(creature))
			return 1;
	}

	//Ensure that it is the correct deed, and that it is in a container in the creature's inventory.
	if (!deed->isASubChildOf(creature)) {
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

	ManagedReference<PlaceStructureSession*> session = new PlaceStructureSession(creature, deed);
	creature->addActiveSession(SessionFacadeType::PLACESTRUCTURE, session);

	//Construct the structure.
	session->constructStructure(x, y, angle);

	//Remove the deed from it's container.
	deed->destroyObjectFromWorld(true);

	return 0;
}

StructureObject* StructureManager::placeStructure(CreatureObject* creature,
		const String& structureTemplatePath, float x, float y, int angle, int persistenceLevel) {
	ManagedReference<Zone*> zone = creature->getZone();

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

	float w0 = -5; //Along the x axis.
	float l0 = -5; //Along the y axis.

	float l1 = 5;
	float w1 = 5;
	float zIncreaseWhenNoAvailableFootprint = 0.f; //TODO: remove this when it has been verified that all buildings have astructure footprint.

	if (structureFootprint != NULL) {
		//If the angle is odd, then swap them.
		getStructureFootprint(serverTemplate, angle, l0, w0, l1, w1);
	} else {
		if (!serverTemplate->isCampStructureTemplate())
			warning(
					"Structure with template '" + structureTemplatePath
							+ "' has no structure footprint.");
		zIncreaseWhenNoAvailableFootprint = 5.f;
	}

	if (floraRadius > 0 && !snapToTerrain)
		z = terrainManager->getHighestHeight(x + w0, y + l0, x + w1, y + l1, 1)
				+ zIncreaseWhenNoAvailableFootprint;

	String strDatabase = "playerstructures";

	bool bIsFactionBuilding = (serverTemplate->getGameObjectType()
			== SceneObjectType::FACTIONBUILDING);

	if (bIsFactionBuilding || serverTemplate->getGameObjectType() == SceneObjectType::TURRET) {
		strDatabase = "playerstructures";
	}

	ManagedReference<SceneObject*> obj =
			ObjectManager::instance()->createObject(
					structureTemplatePath.hashCode(), persistenceLevel, strDatabase);

	if (obj == NULL || !obj->isStructureObject()) {
		if (obj != NULL) {
			Locker locker(obj);
			obj->destroyObjectFromDatabase(true);
		}

		error(
				"Failed to create structure with template: "
						+ structureTemplatePath);
		return NULL;
	}

	StructureObject* structureObject = cast<StructureObject*>(obj.get());

	Locker sLocker(structureObject);

	structureObject->grantPermission("ADMIN", creature->getObjectID());
	structureObject->setOwner(creature->getObjectID());

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
	if (ghost != NULL) {
		ghost->addOwnedStructure(structureObject);
	}

	if(structureObject->isTurret() || structureObject->isMinefield()){
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

	zone->transferObject(structureObject, -1, true);

	structureObject->createChildObjects();

	structureObject->notifyStructurePlaced(creature);

	return structureObject;
}

int StructureManager::destroyStructure(StructureObject* structureObject) {
	Reference<DestroyStructureTask*> task = new DestroyStructureTask(structureObject);
	task->execute();

	return 0;
	/*ManagedReference<Zone*> zone = structureObject->getZone();

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
	return 0;*/
}

String StructureManager::getTimeString(uint32 timestamp) {

	if( timestamp == 0 ){
		return "";
	}

	static const String abbrvs[3] = { "minutes", "hours", "days" };

	static const int intervals[3] = { 60, 3600, 86400 };
	int values[3] = { 0, 0, 0 };

	StringBuffer str;

	for (int i = 2; i > -1; --i) {
		values[i] = floor((float) timestamp / intervals[i]);
		timestamp -= values[i] * intervals[i];

		if (values[i] > 0) {
			if (str.length() > 0){
				str << ", ";
			}

			str << values[i] << " " << abbrvs[i];
		}
	}

	return "(" + str.toString() + ")";
}

int StructureManager::declareResidence(CreatureObject* player, StructureObject* structureObject) {
	if (!structureObject->isBuildingObject()) {
		player->sendSystemMessage("@player_structure:residence_must_be_building"); //Your declared residence must be a building.
		return 1;
	}

	PlayerObject* ghost = player->getPlayerObject();

	if (!player->checkCooldownRecovery("declare_residence") && !ghost->isPrivileged()) {
		Time* timeremaining = player->getCooldownTime("declare_residence");
		StringIdChatParameter params("player_structure", "change_residence_time"); //You cannot change residence for %NO hours.
		params.setTO(String::valueOf(ceil(timeremaining->miliDifference() / -3600000.f)));

		player->sendSystemMessage(params);
		return 1;
	}

	ManagedReference<BuildingObject*> buildingObject = cast<BuildingObject*>(structureObject);

	if (!buildingObject->isOwnerOf(player)) {
		player->sendSystemMessage("@player_structure:declare_must_be_owner"); //You must be the owner of the building to declare residence.
		return 1;
	}


	uint64 objectid = player->getObjectID();

	uint64 declaredOidResidence = ghost->getDeclaredResidence();

	ManagedReference<BuildingObject*> declaredResidence = server->getObject(declaredOidResidence).castTo<BuildingObject*>();
	ManagedReference<CityRegion*> cityRegion = buildingObject->getCityRegion();

	CityManager* cityManager = server->getCityManager();

	if (declaredResidence != NULL) {
		if (declaredResidence == buildingObject) {
			player->sendSystemMessage("@player_structure:already_residence"); //This building is already your residence.
			return 1;
		}

		ManagedReference<CityRegion*> residentCity = declaredResidence->getCityRegion();

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

		if (cityRegion->isMayor(objectid) && structureObject != cityRegion->getCityHall()) {
			player->sendSystemMessage("@city/city:mayor_residence_change"); //As a city Mayor, your residence is always the city hall of the city in which you are mayor.  You cannot declare a new residence.
			return 1;
		}

		cityManager->registerCitizen(cityRegion, player);
	}

	//Set the characters home location to this structure.
	ghost->setDeclaredResidence(buildingObject);

	if(declaredResidence != NULL) {
		Locker oldLock(declaredResidence, player);
		declaredResidence->setResidence(false);
	}

	Locker newLock(buildingObject,player);
	buildingObject->setResidence(true);

	player->addCooldown("declare_residence", 24 * 3600 * 1000); //1 day

	return 0;
}

Reference<SceneObject*> StructureManager::getInRangeParkingGarage(SceneObject* obj, int range) {
	ManagedReference<Zone*> zone = obj->getZone();

	if (zone == NULL)
		return NULL;

	SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;
	CloseObjectsVector* closeObjectsVector = (CloseObjectsVector*) obj->getCloseObjects();

	if (closeObjectsVector == NULL) {
		zone->getInRangeObjects(obj->getPositionX(), obj->getPositionY(), 128, &closeSceneObjects, true);
	} else {
		closeObjectsVector->safeCopyTo(closeSceneObjects);
	}

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
	ManagedReference<DestroyStructureSession*> session = creature->getActiveSession(SessionFacadeType::DESTROYSTRUCTURE).castTo<DestroyStructureSession*>();

	if (session == NULL)
		return 0;

	ManagedReference<StructureObject*> structureObject =
			session->getStructureObject();

	if (structureObject == NULL)
		return 0;

	Locker _locker(structureObject);

	ManagedReference<StructureDeed*> deed =
			server->getObject(
					structureObject->getDeedObjectID()).castTo<StructureDeed*>();

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

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			ReadLocker rlocker(cell->getContainerLock());

			ManagedReference<SceneObject*> childObject =
					cell->getContainerObject(j);

			rlocker.release();

			if (childObject->isVendor())
				continue;

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
			server->getObject(declaredOidResidence).castTo<BuildingObject*>();

	if (declaredResidence == structure) {
		status->addMenuItem("@player_structure:declared_residency"); //You have declared your residency here.
	}

	if (structure->isPrivateStructure() && !structure->isCivicStructure()) {
		status->addMenuItem("@player_structure:structure_private"); //This structure is private
	} else {
		status->addMenuItem("@player_structure:structure_public"); //This structure is public
	}

	status->addMenuItem(
			"@player_structure:condition_prompt "
					+ String::valueOf(structure->getDecayPercentage()) + "%");

	if (!structure->isCivicStructure()) {

		// property tax
		float propertytax = 0.f;
		if(!structure->isCivicStructure() && structure->getCityRegion() != NULL){
			ManagedReference<CityRegion*> city = structure->getCityRegion().get();
			if(city != NULL){
				propertytax = city->getPropertyTax()/ 100.f * structure->getMaintenanceRate();
				status->addMenuItem(
							"@city/city:property_tax_prompt : "
									+ String::valueOf(ceil(propertytax))
									+  " cr/hr");
			}
		}

		// maintenance
		float secsRemainingMaint = 0.f;
		if( structure->getSurplusMaintenance() > 0 ){
			float totalrate = (float)structure->getMaintenanceRate() + propertytax;
			secsRemainingMaint = ((float)structure->getSurplusMaintenance() / totalrate)*3600;
		}

		status->addMenuItem(
			"@player_structure:maintenance_pool_prompt "
					+ String::valueOf( (int) floor( (float) structure->getSurplusMaintenance()))
					+ " "
					+ getTimeString( (uint32)secsRemainingMaint ) );

		status->addMenuItem(
			"@player_structure:maintenance_rate_prompt "
					+ String::valueOf(structure->getMaintenanceRate())
					+ " cr/hr");

		status->addMenuItem(
			"@player_structure:maintenance_mods_prompt "
					+ structure->getMaintenanceMods());
	}


	if (structure->isInstallationObject() && !structure->isGeneratorObject() && !structure->isCivicStructure()) {
		InstallationObject* installation = cast<InstallationObject*>(structure);

		float secsRemainingPower = 0.f;
		float basePowerRate = installation->getBasePowerRate();
		if((installation->getSurplusPower() > 0) && (basePowerRate != 0)){
			secsRemainingPower = ((float)installation->getSurplusPower() / (float)basePowerRate)*3600;
		}

		status->addMenuItem(
				"@player_structure:power_reserve_prompt "
						+ String::valueOf( (int) installation->getSurplusPower())
						+ " "
						+ getTimeString( (uint32)secsRemainingPower ) );

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
void StructureManager::promptMaintenanceDroid(StructureObject* structure, CreatureObject* creature) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	Vector<DroidObject*> droids;
	ManagedReference<SceneObject*> datapad = creature->getSlottedObject("datapad");
	if(datapad == NULL) {
		return;
	}
	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

		if (object != NULL && object->isPetControlDevice()) {
			PetControlDevice* device = cast<PetControlDevice*>( object.get());

			if (device->getPetType() == PetManager::DROIDPET) {
				DroidObject* pet = cast<DroidObject*>(device->getControlledObject());
				if (pet->isMaintenanceDroid()) {
					droids.add(pet);
				}
			}
		}
	}
	if (droids.size() == 0) {
		creature->sendSystemMessage("@player_structure:no_droids");
		return;
	}

	ManagedReference<SuiListBox*> box = new SuiListBox(creature,SuiWindowType::STRUCTURE_ASSIGN_DROID);
	box->setCallback(new StructureAssignDroidSuiCallback(creature->getZoneServer()));

	box->setPromptText("@sui:assign_droid_prompt");
	box->setPromptTitle("@sui:assign_droid_title"); // Configure Effects
	box->setOkButton(true, "@ok");

	// Check if player has a droid called with a maintenance module installed
	for (int i = 0; i < droids.size(); ++i) {
		DroidObject* droidObject = droids.elementAt(i);
		box->addMenuItem(droidObject->getDisplayedName(),droidObject->getObjectID());
	}
	box->setUsingObject(structure);
	ghost->addSuiBox(box);
	creature->sendMessage(box->generateMessage());

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

void StructureManager::promptWithdrawMaintenance(StructureObject* structure, CreatureObject* creature) {
	if (!structure->isGuildHall()) {
		return;
	}

	if (!structure->isOnAdminList(creature)) {
		creature->sendSystemMessage("@player_structure:withdraw_admin_only"); // You must be an administrator to remove credits from the treasury.
		return;
	}

	//Get the most up to date maintenance count.
	structure->updateStructureStatus();

	int surplusMaintenance = structure->getSurplusMaintenance();

	if (surplusMaintenance <= 0) {
		creature->sendSystemMessage("@player_structure:insufficient_funds_withdrawal"); // Insufficent funds for withdrawal.
		return;
	}

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	ManagedReference<SuiInputBox*> sui = new SuiInputBox(creature, SuiWindowType::STRUCTURE_MANAGE_MAINTENANCE);
	sui->setCallback(new StructureWithdrawMaintenanceSuiCallback(server));
	sui->setPromptTitle("@player_structure:withdraw_maintenance"); // Withdraw From Treasury
	sui->setUsingObject(structure);
	sui->setPromptText("@player_structure:treasury_prompt " + String::valueOf(surplusMaintenance)); // Treasury:

	ghost->addSuiBox(sui);
	creature->sendMessage(sui->generateMessage());
}

void StructureManager::promptSelectSign(StructureObject* structure, CreatureObject* player){

	if( !structure->isBuildingObject() )
		return;

	// Check building template has signs configured
	Reference<SharedBuildingObjectTemplate*> buildingTemplate = dynamic_cast<SharedBuildingObjectTemplate*>(structure->getObjectTemplate());
	if( buildingTemplate == NULL ){
		player->sendSystemMessage( "ERROR: Unable to get structure template" );
		return;
	}

	if( buildingTemplate->getShopSignsSize() == 0 ){
		player->sendSystemMessage( "This building does not have any additional signs configured" );
		return;
	}

	SuiListBox* signBox = new SuiListBox(player, SuiWindowType::STRUCTURE_SELECT_SIGN);
	signBox->setCallback(new StructureSelectSignSuiCallback(player->getZoneServer()));
	signBox->setPromptTitle("@player_structure:changesign_title"); // "Sign Selection"
	signBox->setPromptText("@player_structure:changesign_prompt"); // "Select the sign type that you would like to display"
	signBox->setUsingObject(structure);
	signBox->setCancelButton(true, "@cancel");

	// Loop over all configured signs and add them to the list
	for( int i=0; i < buildingTemplate->getShopSignsSize(); i++ ){

		SignTemplate* signTemplate = buildingTemplate->getShopSign(i);

		// suiItem string can't be empty
		if( signTemplate->getSuiItem().isEmpty() ){
			continue;
		}

		// Check required skill (if any)
		if( signTemplate->getRequiredSkill().isEmpty() ){
			signBox->addMenuItem( signTemplate->getSuiItem() );
		}
		else{
			if( player->hasSkill( signTemplate->getRequiredSkill() ) ){
				signBox->addMenuItem( signTemplate->getSuiItem() );
			}
		}
	}

	player->sendMessage(signBox->generateMessage());
	player->getPlayerObject()->addSuiBox(signBox);

}

void StructureManager::setSign(StructureObject* structure, CreatureObject* player, String signSuiItem ){

	if( !structure->isBuildingObject() )
		return;

	// Check building template has shop signs configured
	Reference<SharedBuildingObjectTemplate*> buildingTemplate = dynamic_cast<SharedBuildingObjectTemplate*>(structure->getObjectTemplate());
	if( buildingTemplate == NULL ){
		player->sendSystemMessage( "ERROR: Unable to get structure template" );
		return;
	}

	if( buildingTemplate->getShopSignsSize() == 0 ){
		player->sendSystemMessage( "This building does not have any signs configured" );
		return;
	}

	BuildingObject* building = cast<BuildingObject*>(structure);
	if( building == NULL )
		return;

	// Find matching sign in the template and change sign
	for( int i=0; i < buildingTemplate->getShopSignsSize(); i++){

		SignTemplate* signTemplate =  buildingTemplate->getShopSign(i);
		if( signTemplate->getSuiItem() == signSuiItem ){
			building->changeSign( signTemplate );
			return;
		}
	}

}

void StructureManager::payMaintenance(StructureObject* structure,
		CreatureObject* creature, int amount) {
	if (amount < 0)
		return;

	int currentMaint = structure->getSurplusMaintenance();

	if (currentMaint + amount > 100000000 || currentMaint + amount < currentMaint) {
		creature->sendSystemMessage("The maximum maintenance a house can hold is 100.000.000");
		return;
	}

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

	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost->hasAbility("maintenance_fees_1")){
		structure->setMaintenanceReduced(true);
	}else{
		structure->setMaintenanceReduced(false);
	}
}

void StructureManager::withdrawMaintenance(StructureObject* structure, CreatureObject* creature, int amount) {
	if (!structure->isGuildHall()) {
		return;
	}

	if (!structure->isOnAdminList(creature)) {
		creature->sendSystemMessage("@player_structure:withdraw_admin_only"); // You must be an administrator to remove credits from the treasury.
		return;
	}

	if (amount < 0)
		return;

	int currentMaint = structure->getSurplusMaintenance();

	if (currentMaint - amount < 0 || currentMaint - amount > currentMaint) {
		creature->sendSystemMessage("@player_structure:insufficient_funds_withdrawal"); // Insufficent funds for withdrawal.
		return;
	}

	StringIdChatParameter params("player_structure", "withdraw_credits"); // You withdraw %DI credits from the treasury.
	params.setDI(amount);

	creature->sendSystemMessage(params);

	creature->addCashCredits(amount);
	structure->subtractMaintenance(amount);
}

bool StructureManager::isInStructureFootprint(StructureObject* structure, float positionX, float positionY, int extraFootprintMargin){

	if(structure == NULL)
		return false;

	if(structure->getObjectTemplate() == NULL)
		return false;

	Reference<SharedStructureObjectTemplate*> serverTemplate =
				dynamic_cast<SharedStructureObjectTemplate*>(structure->getObjectTemplate());

	float placingFootprintLength0, placingFootprintWidth0, placingFootprintLength1, placingFootprintWidth1;

	if (getStructureFootprint(serverTemplate, structure->getDirectionAngle(), placingFootprintLength0, placingFootprintWidth0, placingFootprintLength1, placingFootprintWidth1) != 0)
		return false;

	float x0 = structure->getPositionX() + placingFootprintWidth0 + (placingFootprintWidth0 >= 0 ? extraFootprintMargin : (extraFootprintMargin * -1));
	float y0 = structure->getPositionY() + placingFootprintLength0 + (placingFootprintLength0 >= 0 ? extraFootprintMargin : (extraFootprintMargin * -1));
	float x1 = structure->getPositionX() + placingFootprintWidth1 + (placingFootprintWidth1 >= 0 ? extraFootprintMargin : (extraFootprintMargin * -1));
	float y1 = structure->getPositionY() + placingFootprintLength1 + (placingFootprintLength1 >= 0 ? extraFootprintMargin : (extraFootprintMargin * -1));

	BoundaryRectangle structureFootprint(x0, y0, x1, y1);

	return structureFootprint.containsPoint(positionX, positionY);

}
