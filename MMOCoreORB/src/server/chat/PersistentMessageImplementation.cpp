/*
 * PersistentMessageImplementation.cpp
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#include "server/chat/PersistentMessage.h"
#include "server/chat/StringIdChatParameterVector.h"
#include "server/chat/WaypointChatParameterVector.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/chat/ChatPersistentMessageToClient.h"
#include "system/lang/Long.h"
#include "system/lang/ref/WeakReference.h"
#include "system/platform.h"
#include "system/thread/Locker.h"

namespace server {
namespace chat {
class StringIdChatParameter;
class WaypointChatParameter;
}  // namespace chat
}  // namespace server

int PersistentMessageImplementation::getMailID() {
	return Long::hashCode(_this.getReferenceUnsafeStaticCast()->_getObjectID());
}

uint64 PersistentMessageImplementation::getObjectID() {
	return _this.getReferenceUnsafeStaticCast()->_getObjectID();
}

void PersistentMessageImplementation::sendTo(CreatureObject* player, bool sendBody) {
	Locker _lock(_this.getReferenceUnsafeStaticCast());

	ChatPersistentMessageToClient* mail = new ChatPersistentMessageToClient(_this.getReferenceUnsafeStaticCast(), player->getZoneServer()->getGalaxyName(), sendBody);
	player->sendMessage(mail);
}


void PersistentMessageImplementation::addStringIdParameter(StringIdChatParameter& param) {
	stringIdParameters.add(param);
}

void PersistentMessageImplementation::addWaypointParameter(WaypointChatParameter& param) {
	waypointParameters.add(param);
}
