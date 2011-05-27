/*
 * RegionImplementation.cpp
 *
 *  Created on: 12/03/2010
 *      Author: victor
 */

#include "Region.h"
#include "server/zone/objects/player/PlayerCreature.h"
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

	if (cityHall->isBanned(player->getObjectID()))
		player->sendSystemMessage("@city/city:youre_city_banned"); //You are banned from this city and may not use any of its public services and structures.
}

void RegionImplementation::insertToZone(Zone* zone) {
	ActiveAreaImplementation::insertToZone(zone);

	Locker locker(_this);

	if (!isInQuadTree())
		return;

	//zone->getPlanetManager()->addRegion(_this);
}

void RegionImplementation::sendDepartingMessage(PlayerCreature* player) {
	if (isStaticObject())
		return;

	StringIdChatParameter stringId("city/city", "city_leave_city");
	stringId.setTO(objectName.getCustomString());

	player->sendSystemMessage(stringId);
}

void RegionImplementation::despawnCityObjects() {
}
