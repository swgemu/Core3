/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "ShuttleCreatureImplementation.h"
#include "ShuttleCreature.h"

#include "../../../Zone.h"

#include "../../../managers/planet/PlanetManager.h"

#include "../../player/Player.h"
#include "../../tangible/ticket/Ticket.h"
#include "../../terrain/PlanetNames.h"

ShuttleCreatureImplementation::ShuttleCreatureImplementation(const String& Planet, const String& City, Coordinate* playerSpawnPoint, uint64 oid, uint32 tax, bool starport)
		: ShuttleCreatureServant(oid) {
	planet = Planet;
	city = City;

	this->tax = tax;
	this->starport = starport;

	speciesName = "shuttle";

	stfName = "theme_park_name";

	objectCRC = 0x764DC035;

	setType(CreatureImplementation::SHUTTLE);

	optionsBitmask = 0x100;
	pvpStatusBitmask = 0;

	arrivalPoint = playerSpawnPoint;
}

ShuttleCreatureImplementation::~ShuttleCreatureImplementation() {
	delete arrivalPoint;
}

void ShuttleCreatureImplementation::doTakeOff() {
	setPosture(2);

	doCombatAnimation((ShuttleCreature*) _this, 0xAB290245, 0);
}

void ShuttleCreatureImplementation::doLanding() {
	setPosture(0);

	doCombatAnimation((ShuttleCreature*) _this, 0xAB290245, 0);
}

void ShuttleCreatureImplementation::sendPlayerTo(Player* player, Ticket* ticket) {
	try {
		String planet = ticket->getArrivalPlanet();
		String shuttle = ticket->getArrivalPoint();

		int id = Planet::getPlanetID(planet);

		if (id == -1)
			return;

		Zone* arrivalZone = server->getZoneServer()->getZone(id);

		if (arrivalZone == NULL)
			return;

		PlanetManager* planetManager = arrivalZone->getPlanetManager();
		ShuttleCreature* arrivalShuttle = planetManager->getShuttle(shuttle);

		if (arrivalShuttle != NULL) {
			Coordinate* coords = arrivalShuttle->getArrivalPoint();
			if (zone != arrivalZone) {
				player->deactivateCamo(false);
				player->setPosition(coords->getPositionX(), coords->getPositionZ(), coords->getPositionY());
				player->switchMap(id);
			} else
				player->doWarp(coords->getPositionX(), coords->getPositionY(), coords->getPositionZ(), 5.0f);
		}
	} catch (Exception& e) {
		error("exception caught in ShuttleCreatureImplementation::sendPlayerTo(Player* player, Ticket* ticket)");
		error(e.getMessage());

		e.printStackTrace();
	} catch (...) {
		error("unreported exception caught in ShuttleCreatureImplementation::sendPlayerTo(Player* player, Ticket* ticket)");
	}
}

int ShuttleCreatureImplementation::getArrivalTime() {
	PlanetManager* planetManager = zone->getPlanetManager();
	int64 land = planetManager->getLandingTime();

	return -(land / 1000);
}
