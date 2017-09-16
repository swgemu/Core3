/*
 * PlaceStructureSessionImplementation.cpp
 *
 *  Created on: Jun 13, 2011
 *      Author: crush
 */

#include "server/zone/objects/player/sessions/PlaceStructureSession.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/structure/tasks/StructureConstructionCompleteTask.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/objects/area/areashapes/CircularAreaShape.h"
#include "server/zone/Zone.h"


int PlaceStructureSessionImplementation::constructStructure(float x, float y, int angle) {
	ManagedReference<StructureDeed*> deed = deedObject.get();
	ManagedReference<Zone*> thisZone = zone.get();
	ManagedReference<CreatureObject*> creature = creatureObject.get();

	if (deed == NULL || thisZone == NULL || creature == NULL)
		return cancelSession();

	positionX = x;
	positionY = y;
	directionAngle = angle;

	TemplateManager* templateManager = TemplateManager::instance();

	String serverTemplatePath = deed->getGeneratedObjectTemplate();
	Reference<SharedStructureObjectTemplate*> serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

	if (serverTemplate == NULL || temporaryNoBuildZone.get() != NULL)
		return cancelSession(); //Something happened, the server template is not a structure template or temporaryNoBuildZone already set.

	placeTemporaryNoBuildZone(serverTemplate);

	String barricadeServerTemplatePath = serverTemplate->getConstructionMarkerTemplate();
	int constructionDuration = 100; //Set the duration for 100ms as a fall back if it doesn't have a barricade template.

	if (!barricadeServerTemplatePath.isEmpty()) {
		ManagedReference<SceneObject*> barricade = ObjectManager::instance()->createObject(barricadeServerTemplatePath.hashCode(), 0, "");

		if (barricade != NULL) {
			barricade->initializePosition(x, 0, y); //The construction barricades are always at the terrain height.

			StructureFootprint* structureFootprint = serverTemplate->getStructureFootprint();

			if (structureFootprint != NULL && (structureFootprint->getRowSize() > structureFootprint->getColSize())) {
				angle = angle + 180;
			}

			barricade->rotate(angle); //All construction barricades need to be rotated 180 degrees for some reason.

			Locker tLocker(barricade);

			thisZone->transferObject(barricade, -1, true);

			constructionDuration = serverTemplate->getLotSize() * 3000; //3 seconds per lot.

			constructionBarricade = barricade;
		}
	}

	Reference<Task*> task = new StructureConstructionCompleteTask(creature);
	task->schedule(constructionDuration);

	return 0;
}

void PlaceStructureSessionImplementation::placeTemporaryNoBuildZone(SharedStructureObjectTemplate* serverTemplate) {
	ManagedReference<Zone*> thisZone = zone.get();

	if (thisZone == NULL)
		return;

	Reference<StructureFootprint*> structureFootprint =	serverTemplate->getStructureFootprint();

	//float temporaryNoBuildZoneWidth = structureFootprint->getLength() + structureFootprint->getWidth();

	ManagedReference<CircularAreaShape*> areaShape = new CircularAreaShape();

	Locker alocker(areaShape);

	// Guild halls are approximately 55 m long, 64 m radius will surely cover that in all directions.
	// Even if the placement coordinate aren't in the center of the building.
	areaShape->setRadius(64);
	areaShape->setAreaCenter(positionX, positionY);

	ManagedReference<ActiveArea*> noBuildZone = (thisZone->getZoneServer()->createObject(STRING_HASHCODE("object/active_area.iff"), 0)).castTo<ActiveArea*>();

	Locker locker(noBuildZone);

	noBuildZone->initializePosition(positionX, 0, positionY);
	noBuildZone->setAreaShape(areaShape);
	noBuildZone->setNoBuildArea(true);

	thisZone->transferObject(noBuildZone, -1, true);

	temporaryNoBuildZone = noBuildZone;
}

void PlaceStructureSessionImplementation::removeTemporaryNoBuildZone() {
	ManagedReference<ActiveArea*> noBuildZone = temporaryNoBuildZone.get();

	if (noBuildZone != NULL) {
		Locker locker(noBuildZone);

		noBuildZone->destroyObjectFromWorld(true);
	}
}

int PlaceStructureSessionImplementation::completeSession() {
	ManagedReference<SceneObject*> barricade = constructionBarricade.get();

	if (barricade != NULL) {
		Locker locker(barricade);

		barricade->destroyObjectFromWorld(true);
	}

	ManagedReference<StructureDeed*> deed = deedObject.get();
	ManagedReference<CreatureObject*> creature = creatureObject.get();
	ManagedReference<Zone*> thisZone = zone.get();

	if (deed == NULL || creature == NULL || thisZone == NULL)
		return cancelSession();

	String serverTemplatePath = deed->getGeneratedObjectTemplate();

	StructureManager* structureManager = StructureManager::instance();
	ManagedReference<StructureObject*> structureObject = structureManager->placeStructure(creature, serverTemplatePath, positionX, positionY, directionAngle);

	removeTemporaryNoBuildZone();

	if (structureObject == NULL) {
		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if (inventory != NULL)
			inventory->transferObject(deed, -1, true);

		return cancelSession();
	}

	Locker clocker(structureObject, creature);

	structureObject->setDeedObjectID(deed->getObjectID());

	deed->notifyStructurePlaced(creature, structureObject);

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != NULL) {

		//Create Waypoint
		ManagedReference<WaypointObject*> waypointObject = ( thisZone->getZoneServer()->createObject(STRING_HASHCODE("object/waypoint/world_waypoint_blue.iff"), 1)).castTo<WaypointObject*>();

		Locker locker(waypointObject);

		waypointObject->setCustomObjectName(structureObject->getDisplayedName(), false);
		waypointObject->setActive(true);
		waypointObject->setPosition(positionX, 0, positionY);
		waypointObject->setPlanetCRC(thisZone->getZoneCRC());
		structureObject->setWaypointID(waypointObject->getObjectID());

		ghost->addWaypoint(waypointObject, false, true);

		locker.release();

		//Create an email.
		ManagedReference<ChatManager*> chatManager = thisZone->getZoneServer()->getChatManager();

		if (chatManager != NULL) {
			UnicodeString subject = "@player_structure:construction_complete_subject";

			StringIdChatParameter emailBody("@player_structure:construction_complete");
			emailBody.setTO(structureObject->getObjectName());
			emailBody.setDI(ghost->getLotsRemaining());

			chatManager->sendMail("@player_structure:construction_complete_sender", subject, emailBody, creature->getFirstName(), waypointObject);
		}

		if (structureObject->isBuildingObject()) {
			BuildingObject* building = cast<BuildingObject*>(structureObject.get());

			if (building->getSignObject() != NULL) {
				if (building->isCivicStructure() || building->isCommercialStructure())
					building->setCustomObjectName(structureObject->getDisplayedName(), true);
				else
					building->setCustomObjectName(creature->getFirstName() + "'s House", true);
			}
		}
	}

	return cancelSession(); //Canceling the session just removes the session from the player's map.
}
