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
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/building/city/CityHallObject.h"

void RegionImplementation::sendGreetingMessage(PlayerCreature* player) {
	if (isStaticObject() || cityHall == NULL)
		return;

	StringIdChatParameter stringId("city/city", "city_enter_city");
	stringId.setTT(objectName.getCustomString());

	StringBuffer type;
	type << "@city/city:rank" << cityHall->getCityRank();

	stringId.setTO(type.toString());

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

	StringIdChatParameter stringId("city/city", "city_leave_city");
	stringId.setTO(objectName.getCustomString());

	player->sendSystemMessage(stringId);
}

void RegionImplementation::despawnCityObjects() {
	if (shuttleInstallation != NULL)
		shuttleInstallation->removeFromZone();
}
