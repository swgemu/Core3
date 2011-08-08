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
#include "server/zone/objects/scene/SessionFacadeType.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/packets/player/EnterStructurePlacementModeMessage.h"
#include "server/zone/managers/structure/tasks/StructureConstructionCompleteTask.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

int PlaceStructureSessionImplementation::initializeSession() {
	//Ensure that the deed can be placed in the current position.
	if (deedObject == NULL)
		return cancelSession();

	TemplateManager* templateManager = TemplateManager::instance();

	String serverTemplatePath = deedObject->getGeneratedObjectTemplate();
	SharedStructureObjectTemplate* serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

	//Ensure that enough lots exist to place the structure.

	if (serverTemplate == NULL)
		return cancelSession(); //Not a structure that is being created.

	String clientTemplatePath = templateManager->getTemplateFile(serverTemplate->getClientObjectCRC());

	//Add the session to the creature at this point.
	//TODO: Should this be done here, or before the session is initialized?
	creatureObject->addActiveSession(SessionFacadeType::PLACESTRUCTURE, _this);

	EnterStructurePlacementModeMessage* espmm = new EnterStructurePlacementModeMessage(deedObject->getObjectID(), clientTemplatePath);
	creatureObject->sendMessage(espmm);

	return 0;
}

int PlaceStructureSessionImplementation::constructStructure(float x, float y, int angle) {
	positionX = x;
	positionY = y;
	directionAngle = angle;

	TemplateManager* templateManager = TemplateManager::instance();

	String serverTemplatePath = deedObject->getGeneratedObjectTemplate();
	SharedStructureObjectTemplate* serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

	if (serverTemplate == NULL)
		return cancelSession(); //Something happened, the server template is not a structure template.

	//Subtract lots.

	String barricadeServerTemplatePath = serverTemplate->getConstructionMarkerTemplate();
	int constructionDuration = 100;

	if (!barricadeServerTemplatePath.isEmpty()) {
		constructionBarricade = ObjectManager::instance()->createObject(barricadeServerTemplatePath.hashCode(), 0, "");

		if (constructionBarricade != NULL) {
			constructionBarricade->initializePosition(x, 0, y); //The construction barricades are always at the terrain height.
			constructionBarricade->rotate(angle + 180); //All construction barricades need to be rotated 180 degrees for some reason.
			constructionBarricade->insertToZone(creatureObject->getZone());

			constructionDuration = serverTemplate->getLotSize() * 3000; //3 seconds per lot.
		}
	}

	//TODO: Do the barricade removal event.
	Task* task = new StructureConstructionCompleteTask(creatureObject);
	task->schedule(constructionDuration);

	return 0;
}

int PlaceStructureSessionImplementation::completeSession() {
	if (constructionBarricade != NULL)
		constructionBarricade->removeFromZone();

	String serverTemplatePath = deedObject->getGeneratedObjectTemplate();

	StructureManager* structureManager = creatureObject->getZone()->getStructureManager();
	ManagedReference<StructureObject*> structureObject = structureManager->placeStructure(creatureObject, serverTemplatePath, positionX, positionY, directionAngle);

	if (structureObject == NULL) {
		//The structure failed to create for some reason. Return the deed to the player, and refund lots.
		return cancelSession();
	}

	structureObject->setOwnerObjectID(creatureObject->getObjectID());
	structureObject->setDeedObjectID(deedObject->getObjectID());

	structureObject->grantPermission("ADMIN", creatureObject->getFirstName());

	ManagedReference<PlayerObject*> ghost = creatureObject->getPlayerObject();

	if (ghost == NULL)
		return cancelSession();

	ghost->addOwnedStructure(structureObject);

	//Create a waypoint.

	//Create an email.

	return cancelSession(); //Cancelling the session just removes the session from the player's map.
}




/*
 * 	ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();
	ManagedReference<WaypointObject*> waypointObject = NULL;

	if (playerObject != NULL) {
		String full = structureObject->getCustomObjectName().toString();

		if (full.isEmpty())
			structureObject->getObjectName()->getFullPath(full);

		String waypointTemplateString = "object/waypoint/world_waypoint_blue.iff";

		waypointObject = (WaypointObject*) zoneServer->createObject(waypointTemplateString.hashCode(), 1);
		waypointObject->setCustomName(full);
		waypointObject->setActive(true);
		waypointObject->setPosition(x, z, y);
		String planetName = zone->getZoneName();
		waypointObject->setPlanetCRC(planetName.hashCode());

		playerObject->addWaypoint(waypointObject, false, true);
	}

	//Create an email
	ManagedReference<ChatManager*> chatManager = zoneServer->getChatManager();

	if (chatManager != NULL) {
		StringIdChatParameter emailBody;
		emailBody.setStringId("@player_structure:construction_complete");
		emailBody.setTO(structureObject->getObjectName());
		emailBody.setDI(player->getLotsRemaining());
		UnicodeString subject = "@player_structure:construction_complete_subject";
		chatManager->sendMail("@player_structure:construction_complete_sender", subject, emailBody, player->getFirstName(), waypointObject);
	}
	*/
