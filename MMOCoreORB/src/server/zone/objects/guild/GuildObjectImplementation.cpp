/*
 * GuildObjectImplementation.cpp
 *
 *  Created on: Oct 27, 2010
 *      Author: crush
 */

#include "GuildObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/scene/SceneObject.h"

void GuildObjectImplementation::sendBaselinesTo(SceneObject* player) {
}

void GuildObjectImplementation::broadcastMessage(BaseMessage* msg) {
}

void GuildObjectImplementation::broadcastMessage(PlayerCreature* player, BaseMessage* msg, bool sendSelf) {
}

void GuildObjectImplementation::addMember(SceneObject* player) {
}

void GuildObjectImplementation::removeMember(SceneObject* player) {
}

bool GuildObjectImplementation::hasMember(SceneObject* player) {
	return true;
}

void GuildObjectImplementation::startChatRoom() {

}

void GuildObjectImplementation::destroyChatRoom() {

}
