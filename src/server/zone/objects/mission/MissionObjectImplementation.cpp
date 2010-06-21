/*
 * MissionObjectImplementation.cpp
 *
 *  Created on: Sep 3, 2009
 *      Author: theanswer
 */

#include "MissionObject.h"
#include "server/zone/packets/mission/MissionObjectMessage6.h"
#include "server/zone/packets/mission/MissionObjectMessage3.h"
#include "server/zone/packets/mission/MissionObjectDeltaMessage3.h"


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

void MissionObjectImplementation::setRefreshCounter(int ctr, bool notifyClient) {
	refreshCounter = ctr;

	if (!notifyClient)
		return;

	SceneObject* player = NULL;

	if (parent != NULL) {
		player = parent;

		while (!player->isPlayerCreature())
			player = player->getParent();
	}

	if (player != NULL) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this);
		delta->updateRefreshCount(ctr);
		delta->close();

		player->sendMessage(delta);
	}
}

void MissionObjectImplementation::setTypeCRC(uint32 crc, bool notifyClient) {
	if (typeCRC == crc)
		return;

	typeCRC = crc;

	if (!notifyClient)
		return;

	SceneObject* player = NULL;

	if (parent != NULL) {
		player = parent;

		while (!player->isPlayerCreature())
			player = player->getParent();
	}

	if (player != NULL) {
		MissionObjectDeltaMessage3* delta = new MissionObjectDeltaMessage3(_this);
		delta->updateTypeCRC(crc);
		delta->close();

		player->sendMessage(delta);
	}
}
