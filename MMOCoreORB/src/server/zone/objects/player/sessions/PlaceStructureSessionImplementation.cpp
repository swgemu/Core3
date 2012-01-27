/*
 * PlaceStructureSessionImplementation.cpp
 *
 *  Created on: Jun 13, 2011
 *      Author: crush
 */

#include "PlaceStructureSession.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/scene/SessionFacadeType.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/packets/player/EnterStructurePlacementModeMessage.h"
#include "server/zone/managers/structure/tasks/StructureConstructionCompleteTask.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/deed/installation/InstallationDeed.h"
#include "server/zone/objects/tangible/deed/building/BuildingDeed.h"

int PlaceStructureSessionImplementation::constructStructure(float x, float y, int angle) {
	positionX = x;
	positionY = y;
	directionAngle = angle;

	TemplateManager* templateManager = TemplateManager::instance();

	String serverTemplatePath = deedObject->getGeneratedObjectTemplate();
	Reference<SharedStructureObjectTemplate*> serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

	if (serverTemplate == NULL)
		return cancelSession(); //Something happened, the server template is not a structure template.

	String barricadeServerTemplatePath = serverTemplate->getConstructionMarkerTemplate();
	int constructionDuration = 100; //Set the duration for 100ms as a fall back if it doesn't have a barricade template.

	if (!barricadeServerTemplatePath.isEmpty()) {
		constructionBarricade = ObjectManager::instance()->createObject(barricadeServerTemplatePath.hashCode(), 0, "");

		if (constructionBarricade != NULL) {
			constructionBarricade->initializePosition(x, 0, y); //The construction barricades are always at the terrain height.
			constructionBarricade->rotate(angle + 180); //All construction barricades need to be rotated 180 degrees for some reason.
			//constructionBarricade->insertToZone(zone);
			zone->transferObject(constructionBarricade, -1, true);

			constructionDuration = serverTemplate->getLotSize() * 3000; //3 seconds per lot.
		}
	}

	Task* task = new StructureConstructionCompleteTask(creatureObject);
	task->schedule(constructionDuration);

	return 0;
}

int PlaceStructureSessionImplementation::completeSession() {
	if (constructionBarricade != NULL)
		constructionBarricade->destroyObjectFromWorld(true);

	String serverTemplatePath = deedObject->getGeneratedObjectTemplate();

	StructureManager* structureManager = zone->getStructureManager();
	ManagedReference<StructureObject*> structureObject = structureManager->placeStructure(creatureObject, serverTemplatePath, positionX, positionY, directionAngle);

	if (structureObject == NULL) {
		ManagedReference<SceneObject*> inventory = creatureObject->getSlottedObject("inventory");

		if (inventory != NULL)
			inventory->transferObject(deedObject, -1, true);

		return cancelSession();
	}

	structureObject->setDeedObjectID(deedObject->getObjectID());

	//TODO: Encapsulate this better?
	//Set the power and maintenance back from the deed to the structure.
	if (deedObject->isBuildingDeed()) {
		BuildingDeed* buildingDeed = cast<BuildingDeed*>( deedObject.get());
		structureObject->setSurplusMaintenance(buildingDeed->getSurplusMaintenance());
	} else if (deedObject->isInstallationDeed()) {
		InstallationDeed* installationDeed = cast<InstallationDeed*>( deedObject.get());
		structureObject->setSurplusMaintenance(installationDeed->getSurplusMaintenance());
		structureObject->setSurplusPower(installationDeed->getSurplusPower());
		ManagedReference<InstallationObject*> installationObject = cast<InstallationObject*>(structureObject.get());
		installationObject->setExtractionRate(installationDeed->getExtractionRate());
		installationObject->setHopperSizeMax(installationDeed->getHopperSizeMax());


	}

	ManagedReference<PlayerObject*> ghost = creatureObject->getPlayerObject();

	if (ghost != NULL) {
		ghost->addOwnedStructure(structureObject);

		//Create Waypoint
		ManagedReference<WaypointObject*> waypointObject = cast<WaypointObject*>( zone->getZoneServer()->createObject(String("object/waypoint/world_waypoint_blue.iff").hashCode(), 1));
		waypointObject->setCustomName(structureObject->getObjectName()->getDisplayedName());
		waypointObject->setActive(true);
		waypointObject->setPosition(positionX, 0, positionY);
		waypointObject->setPlanetCRC(zone->getZoneCRC());

		ghost->addWaypoint(waypointObject, false, true);

		//Create an email.
		ManagedReference<ChatManager*> chatManager = zone->getZoneServer()->getChatManager();

		if (chatManager != NULL) {
			UnicodeString subject = "@player_structure:construction_complete_subject";

			StringIdChatParameter emailBody("@player_structure:construction_complete");
			emailBody.setTO(structureObject->getObjectName());
			emailBody.setDI(ghost->getLotsRemaining());

			chatManager->sendMail("@player_structure:construction_complete_sender", subject, emailBody, creatureObject->getFirstName(), waypointObject);
		}

		if (structureObject->isBuildingObject()) {
			BuildingObject* building = cast<BuildingObject*>( structureObject.get());
			building->setCustomObjectName(creatureObject->getFirstName() + "'s House", true); //Set the house sign.
		}
	}

	return cancelSession(); //Canceling the session just removes the session from the player's map.
}
