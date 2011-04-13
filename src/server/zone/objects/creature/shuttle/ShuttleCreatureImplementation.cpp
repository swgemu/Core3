/*
 * ShuttleCreatureImplementation.cpp
 *
 *  Created on: 30/05/2010
 *      Author: victor
 */

#include "ShuttleCreature.h"
#include "ShuttleLandingEvent.h"
#include "ShuttleTakeOffEvent.h"

#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/zone/objects/terrain/PlanetNames.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/planet/PlanetManager.h"

int64 ShuttleCreatureImplementation::getLandingTime() {
	Time landing = shuttleLandingEvent->getNextExecutionTime();

	return landing.miliDifference();
}


void ShuttleCreatureImplementation::sendPlayerTo(PlayerCreature* player, TicketObject* ticket) {
	if (zone == NULL)
		return;

	try {
		String planet = ticket->getArrivalPlanet();
		String shuttle = ticket->getArrivalPoint();

		int id = Planet::getPlanetID(planet);

		if (id == -1)
			return;

		Zone* arrivalZone = getZoneServer()->getZone(id);

		if (arrivalZone == NULL)
			return;

		PlanetManager* planetManager = arrivalZone->getPlanetManager();
		ShuttleCreature* arrivalShuttle = planetManager->getShuttle(shuttle);

		if (arrivalShuttle != NULL) {
			float x, z, y;

			arrivalShuttle->getArrivalPoint(x, y, z);

			player->switchZone(id, x, z, y);

			//info("called switched zone", true);
		} else {
			error("unknown arrival shuttle for destination " + shuttle);
		}

	} catch (Exception& e) {
		error("exception caught in ShuttleCreatureImplementation::sendPlayerTo(Player* player, Ticket* ticket)");
		error(e.getMessage());

		e.printStackTrace();
	}
}

void ShuttleCreatureImplementation::doTakeOff() {
	int landin = 300000;

	if (shuttleTakeOffEvent == NULL)
		shuttleTakeOffEvent = new ShuttleTakeOffEvent(_this);
	if (shuttleLandingEvent == NULL) {
		shuttleLandingEvent = new ShuttleLandingEvent(_this);
		landin = System::random(landin);
	}

	setPosture(2);

	doCombatAnimation((ShuttleCreature*) _this, 0xAB290245, 0);

	shuttleLandingEvent->schedule(landin);
}

void ShuttleCreatureImplementation::doLanding() {
	setPosture(0);

	doCombatAnimation((ShuttleCreature*) _this, 0xAB290245, 0);

	shuttleTakeOffEvent->schedule(90000);
}
