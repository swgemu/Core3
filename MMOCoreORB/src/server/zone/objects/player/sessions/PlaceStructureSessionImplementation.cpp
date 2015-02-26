/*
 * PlaceStructureSessionImplementation.cpp
 *
 *  Created on: Jun 13, 2011
 *      Author: crush
 */

#include "server/zone/objects/player/sessions/PlaceStructureSession.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/structure/tasks/StructureConstructionCompleteTask.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/SessionFacadeType.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "server/zone/packets/player/EnterStructurePlacementModeMessage.h"
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/objects/area/areashapes/CircularAreaShape.h"
#include "server/zone/Zone.h"


int PlaceStructureSessionImplementation::constructStructure(float x, float y, int angle) {
	positionX = x;
	positionY = y;
	directionAngle = angle;

	TemplateManager* templateManager = TemplateManager::instance();

	String serverTemplatePath = deedObject->getGeneratedObjectTemplate();
	Reference<SharedStructureObjectTemplate*> serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

	if (serverTemplate == NULL || temporaryNoBuildZone != NULL)
		return cancelSession(); //Something happened, the server template is not a structure template or temporaryNoBuildZone already set.

	placeTemporaryNoBuildZone(serverTemplate);

	String barricadeServerTemplatePath = serverTemplate->getConstructionMarkerTemplate();
	int constructionDuration = 100; //Set the duration for 100ms as a fall back if it doesn't have a barricade template.

	if (!barricadeServerTemplatePath.isEmpty()) {
		constructionBarricade = ObjectManager::instance()->createObject(barricadeServerTemplatePath.hashCode(), 0, "");

		if (constructionBarricade != NULL) {
			constructionBarricade->initializePosition(x, 0, y); //The construction barricades are always at the terrain height.

			StructureFootprint* structureFootprint = serverTemplate->getStructureFootprint();

			if (structureFootprint != NULL && (structureFootprint->getRowSize() > structureFootprint->getColSize())) {
				angle = angle + 180;
			}

			constructionBarricade->rotate(angle); //All construction barricades need to be rotated 180 degrees for some reason.
			//constructionBarricade->insertToZone(zone);
			zone->transferObject(constructionBarricade, -1, true);

			constructionDuration = serverTemplate->getLotSize() * 3000; //3 seconds per lot.
		}
	}

	Reference<Task*> task = new StructureConstructionCompleteTask(creatureObject);
	task->schedule(constructionDuration);

	return 0;
}

void PlaceStructureSessionImplementation::placeTemporaryNoBuildZone(SharedStructureObjectTemplate* serverTemplate) {
	Reference<StructureFootprint*> structureFootprint =	serverTemplate->getStructureFootprint();

	//float temporaryNoBuildZoneWidth = structureFootprint->getLength() + structureFootprint->getWidth();

	ManagedReference<CircularAreaShape*> areaShape = new CircularAreaShape();
	// Guild halls are approximately 55 m long, 64 m radius will surely cover that in all directions.
	// Even if the placement coordinate aren't in the center of the building.
	areaShape->setRadius(64);
	areaShape->setAreaCenter(positionX, positionY);

	temporaryNoBuildZone = (zone->getZoneServer()->createObject(String("object/active_area.iff").hashCode(), 0)).castTo<ActiveArea*>();
	temporaryNoBuildZone->initializePosition(positionX, 0, positionY);
	temporaryNoBuildZone->setAreaShape(areaShape);
	temporaryNoBuildZone->setNoBuildArea(true);

	zone->transferObject(temporaryNoBuildZone, -1, true);
}

void PlaceStructureSessionImplementation::removeTemporaryNoBuildZone() {
	if (temporaryNoBuildZone != NULL) {
		temporaryNoBuildZone->destroyObjectFromWorld(true);
	}
}

int PlaceStructureSessionImplementation::completeSession() {
	if (constructionBarricade != NULL)
		constructionBarricade->destroyObjectFromWorld(true);

	String serverTemplatePath = deedObject->getGeneratedObjectTemplate();

	StructureManager* structureManager = StructureManager::instance();
	ManagedReference<StructureObject*> structureObject = structureManager->placeStructure(creatureObject, serverTemplatePath, positionX, positionY, directionAngle);

	removeTemporaryNoBuildZone();

	if (structureObject == NULL) {
		ManagedReference<SceneObject*> inventory = creatureObject->getSlottedObject("inventory");

		if (inventory != NULL)
			inventory->transferObject(deedObject, -1, true);

		return cancelSession();
	}

	structureObject->setDeedObjectID(deedObject->getObjectID());

	deedObject->notifyStructurePlaced(creatureObject, structureObject);

	ManagedReference<PlayerObject*> ghost = creatureObject->getPlayerObject();

	if (ghost != NULL) {

		//Create Waypoint
		ManagedReference<WaypointObject*> waypointObject = ( zone->getZoneServer()->createObject(String("object/waypoint/world_waypoint_blue.iff").hashCode(), 1)).castTo<WaypointObject*>();
		waypointObject->setCustomObjectName(structureObject->getDisplayedName(), false);
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
			BuildingObject* building = cast<BuildingObject*>(structureObject.get());
			if (building->getSignObject() != NULL) {
				building->setCustomObjectName(creatureObject->getFirstName() + "'s House", true); //Set the house sign.
			}
		}
	}

	return cancelSession(); //Canceling the session just removes the session from the player's map.
}
