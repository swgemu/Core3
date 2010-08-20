/*
 * ShuttleInstallationImplementation.cpp
 *
 *  Created on: 31/07/2010
 *      Author: victor
 */

#include "ShuttleInstallation.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/creature/shuttle/ShuttleCreature.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/terminal/ticketcollector/TicketCollector.h"
#include "server/zone/objects/tangible/terminal/travel/TravelTerminal.h"
#include "server/zone/Zone.h"

void ShuttleInstallationImplementation::spawnShuttleObjects() {
	if (activeArea == NULL || zone == NULL) {
		error("active area null");
		return;
	}

	CreatureManager* creatureManager = zone->getCreatureManager();
	uint32 shuttleCRC = String("object/creature/npc/theme_park/player_shuttle.iff").hashCode();

	ManagedReference<CreatureObject*> creatureObject = creatureManager->spawnCreature(shuttleCRC, positionX, positionZ, positionY);

	if (creatureObject == NULL || !creatureObject->isShuttleCreature()) {
		error("wrong shuttle crc");

		return;
	}

	shuttle = (ShuttleCreature*) creatureObject.get();

	Locker locker(shuttle);

	String shuttleName = activeArea->getCustomObjectName().toString();

	shuttle->setDirection(direction.getW(), 0, direction.getY(), 0);
	shuttle->setArrivalPoint(positionX, positionY, positionZ);
	shuttle->setStarport(false);
	shuttle->setTax(10);
	shuttle->setPlanet(zone->getPlanetName());
	shuttle->setCity(shuttleName);
	shuttle->updateZone(false);

	PlanetManager* planetManager = zone->getPlanetManager();
	planetManager->addShuttle(shuttleName, shuttle);

	shuttle->doTakeOff();

	locker.release();

	float directionRadians = direction.getRadians();

	float newX = ((14.41) * Math::sin(directionRadians) + 7.64 * Math::cos(directionRadians)) + positionX;
	float newY = ((14.41) * Math::cos(directionRadians) - 7.64 * Math::sin(directionRadians)) + positionY;

	ticketCollector = (TicketCollector*) zone->getZoneServer()->createObject(String("object/tangible/travel/ticket_collector/ticket_collector.iff").hashCode(), 0);

	Locker tlocker(ticketCollector);

	ticketCollector->setDirection(direction.getW(), 0, direction.getY(), 0);

	ticketCollector->initializePosition(newX, positionZ + 1, newY);
	ticketCollector->insertToZone(zone);
	ticketCollector->setShuttle(shuttle);

	tlocker.release();

	travelTerminal = (TravelTerminal*) zone->getZoneServer()->createObject(String("object/tangible/terminal/terminal_travel.iff").hashCode(), 0);

	newX = ((14.41) * Math::sin(directionRadians) + -7.64 * Math::cos(directionRadians)) + positionX;
	newY = ((14.41) * Math::cos(directionRadians) - -7.64 * Math::sin(directionRadians)) + positionY;

	Locker t2locker(travelTerminal);

	travelTerminal->setShuttle(shuttle);
	travelTerminal->setDirection(direction.getW(), 0, direction.getY(), 0);
	travelTerminal->initializePosition(newX, positionZ + 1, newY);
	travelTerminal->insertToZone(zone);
}

bool ShuttleInstallationImplementation::checkRequisitesForPlacement(PlayerCreature* player) {
	ManagedReference<ActiveArea*> playerArea = player->getActiveArea();

	//TODO: Check to make sure the player is the mayor of the city.
	if (playerArea == NULL || !playerArea->isRegion()) {
		player->sendSystemMessage("@player_structure:cant_place_civic"); //This structure must be placed within the borders of the city in which you are mayor.
		return false;
	}

	Region* region = (Region*) playerArea.get();

	if (region->getShuttle() != NULL) {
		player->sendSystemMessage("@player_structure:cant_place_unique"); //This city can only support a single structure of this type.
		return false;
	}

	return true;
}
