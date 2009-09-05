/*
 * MissionObjectImplementation.cpp
 *
 *  Created on: Sep 3, 2009
 *      Author: theanswer
 */

#include "MissionObject.h"
#include "server/zone/packets/mission/MissionObjectMessage6.h"

MissionObjectImplementation::MissionObjectImplementation(LuaObject* templateData) : SceneObjectImplementation(templateData) {
	setLoggingName("MissionObject");
}

void MissionObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending miso baselines");

	BaseMessage* tano6 = new MissionObjectMessage6(_this);
	player->sendMessage(tano6);
}
