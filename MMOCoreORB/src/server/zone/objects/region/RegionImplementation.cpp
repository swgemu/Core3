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

void RegionImplementation::sendDepartingMessage(PlayerCreature* player) {
	if (isStaticObject())
		return;

	ParameterizedStringId stringId("city/city", "city_leave_city");
	stringId.setTO(objectName.getCustomString());

	player->sendSystemMessage(stringId);
}
