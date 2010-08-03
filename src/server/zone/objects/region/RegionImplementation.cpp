/*
 * RegionImplementation.cpp
 *
 *  Created on: 12/03/2010
 *      Author: victor
 */

#include "Region.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/Zone.h"

void RegionImplementation::sendGreetingMessage(PlayerCreature* player) {
	if (isStaticObject())
		return;

	ParameterizedStringId stringId("city/city", "city_enter_city");
	stringId.setTT(objectName.getCustomString());
	stringId.setTO(zone->getPlanetName());

	player->sendSystemMessage(stringId);
}

void RegionImplementation::sendDepartingMessage(PlayerCreature* player) {
	if (isStaticObject())
		return;

	ParameterizedStringId stringId("city/city", "city_leave_city");
	stringId.setTT(objectName.getCustomString());
	stringId.setTO(zone->getPlanetName());

	player->sendSystemMessage(stringId);
}
