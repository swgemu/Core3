/*
 * PersistentMessageImplementation.cpp
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#include "PersistentMessage.h"
#include "server/zone/packets/chat/ChatPersistentMessageToClient.h"
#include "server/zone/objects/player/PlayerCreature.h"

int PersistentMessageImplementation::getMailID() {
	return Long::hashCode(_this->_getObjectID());
}

uint64 PersistentMessageImplementation::getObjectID() {
	return _this->_getObjectID();
}

void PersistentMessageImplementation::sendTo(PlayerCreature* player, bool sendBody) {
	Locker _lock(_this);

	ChatPersistentMessageToClient* mail = new ChatPersistentMessageToClient(_this, sendBody);
	player->sendMessage(mail);
}


void PersistentMessageImplementation::addStringIdParameter(StringIdChatParameter& param) {
	stringIdParameters.add(param);
}

void PersistentMessageImplementation::addWaypointParameter(WaypointChatParameter& param) {
	waypointParameters.add(param);
}
