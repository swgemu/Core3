/*
 * RegionImplementation.cpp
 *
 *  Created on: 12/03/2010
 *      Author: victor
 */

#include "Region.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/creature/shuttle/ShuttleCreature.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/installation/shuttle/ShuttleInstallation.h"
#include "server/zone/objects/installation/bank/BankInstallation.h"
#include "server/zone/managers/planet/PlanetManager.h"

void RegionImplementation::sendGreetingMessage(PlayerCreature* player) {
	if (isStaticObject())
		return;

	ParameterizedStringId stringId("city/city", "city_enter_city");
	stringId.setTT(objectName.getCustomString());

	String type;

	if (radius == 150.f) {
		type = "Outpost";
	} else if (radius == 200.f) {
		type = "Village";
	} else if (radius == 300.f) {
		type = "Township";
	} else if (radius == 400.f) {
		type = "City";
	} else {
		type = "Metropolis";
	}

	stringId.setTO(type);

	player->sendSystemMessage(stringId);
}

void RegionImplementation::insertToZone(Zone* zone) {
	ActiveAreaImplementation::insertToZone(zone);

	if (!isInQuadTree())
		return;

	if (shuttleInstallation != NULL) {
		shuttleInstallation->spawnShuttleObjects();
	}

	zone->getPlanetManager()->addRegion(_this);
}

void RegionImplementation::sendDepartingMessage(PlayerCreature* player) {
	if (isStaticObject())
		return;

	ParameterizedStringId stringId("city/city", "city_leave_city");
	stringId.setTO(objectName.getCustomString());

	player->sendSystemMessage(stringId);
}

void RegionImplementation::despawnCityObjects() {
	if (shuttleInstallation != NULL)
		shuttleInstallation->removeFromZone();

	while (banks.size() > 0) {
		ManagedReference<BankInstallation*> bank = banks.get(0);

		bank->removeFromZone();

		banks.drop(bank);
	}
}
