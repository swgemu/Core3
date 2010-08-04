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

	float directionRadians = direction.getRadians();

	float newX = ((14.41) * Math::sin(directionRadians) + 7.64 * Math::cos(directionRadians)) + positionX;
	float newY = ((14.41) * Math::cos(directionRadians) - 7.64 * Math::sin(directionRadians)) + positionY;

	ticketCollector = (TicketCollector*) zone->getZoneServer()->createObject(String("object/tangible/travel/ticket_collector/ticket_collector.iff").hashCode(), 0);

	ticketCollector->setDirection(direction.getW(), 0, direction.getY(), 0);

	ticketCollector->initializePosition(newX, positionZ + 1, newY);
	ticketCollector->insertToZone(zone);
	ticketCollector->setShuttle(shuttle);

	travelTerminal = (TravelTerminal*) zone->getZoneServer()->createObject(String("object/tangible/terminal/terminal_travel.iff").hashCode(), 0);

	newX = ((14.41) * Math::sin(directionRadians) + -7.64 * Math::cos(directionRadians)) + positionX;
	newY = ((14.41) * Math::cos(directionRadians) - -7.64 * Math::sin(directionRadians)) + positionY;

	travelTerminal->setShuttle(shuttle);
	travelTerminal->setDirection(direction.getW(), 0, direction.getY(), 0);
	travelTerminal->initializePosition(newX, positionZ + 1, newY);
	travelTerminal->insertToZone(zone);
}

bool ShuttleInstallationImplementation::checkRequisitesForPlacement(PlayerCreature* player) {
	ManagedReference<ActiveArea*> playerArea = player->getActiveArea();

	if (playerArea == NULL || !playerArea->isRegion()) {
		//TODO: find correct string
		player->sendSystemMessage("You need to be in a city to place a shuttleport");
		return false;
	}

	Region* region = (Region*) playerArea.get();

	if (region->getShuttle() != NULL) {
		//TODO: find correct string
		player->sendSystemMessage("This city has a shuttleport already");
		return false;
	}

	return true;
}
