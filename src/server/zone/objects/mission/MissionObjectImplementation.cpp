/*
 * MissionObjectImplementation.cpp
 *
 *  Created on: Sep 3, 2009
 *      Author: theanswer
 */

#include "MissionObject.h"
#include "server/zone/packets/mission/MissionObjectMessage6.h"
#include "server/zone/packets/mission/MissionObjectMessage3.h"



void MissionObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	setLoggingName("MissionObject");
}

void MissionObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending miso baselines");

	BaseMessage* tano3 = new MissionObjectMessage3(_this);
	player->sendMessage(tano3);

	BaseMessage* tano6 = new MissionObjectMessage6(_this);
	player->sendMessage(tano6);
}
