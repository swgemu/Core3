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

#include "ShipControlDevice.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/Zone.h"

void ShipControlDeviceImplementation::generateObject(CreatureObject* player) {
	//info("generating ship", true);
	return;

	ZoneServer* zoneServer = getZoneServer();

	Locker clocker(controlledObject, player);

	controlledObject->initializePosition(player->getPositionX(), player->getPositionZ() + 10, player->getPositionY());

	player->getZone()->transferObject(controlledObject, -1, true);
	//controlledObject->insertToZone(player->getZone());

	//removeObject(controlledObject, true);

	controlledObject->transferObject(player, 5, true);
	player->setState(CreatureState::PILOTINGSHIP);
	//controlledObject->inflictDamage(player, 0, System::random(50), true);

	updateStatus(1);

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != NULL)
		ghost->setTeleporting(true);
}

void ShipControlDeviceImplementation::storeObject(CreatureObject* player) {
	player->clearState(CreatureState::PILOTINGSHIP);

	Locker clocker(controlledObject, player);

	if (!controlledObject->isInQuadTree())
		return;

	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	zone->transferObject(player, -1, false);
	
	controlledObject->destroyObjectFromWorld(true);

	transferObject(controlledObject, 4, true);
	
	updateStatus(0);
}

void ShipControlDeviceImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	//ControlDeviceImplementation::fillObjectMenuResponse(menuResponse, player);

	if (!controlledObject->isInQuadTree()) {
		//menuResponse->addRadialMenuItem(60, 3, "Launch Ship"); //Launch
	} else
		menuResponse->addRadialMenuItem(61, 3, "Land Ship"); //Launch
	//menuResponse->addRadialMenuItem(61, 3, "Launch Ship"); //Launch
}
