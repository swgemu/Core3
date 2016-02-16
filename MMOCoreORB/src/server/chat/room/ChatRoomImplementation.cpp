/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/chat/room/ChatRoom.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/packets/chat/ChatRoomList.h"
#include "server/zone/packets/chat/ChatOnDestroyRoom.h"
#include "server/zone/packets/chat/ChatOnLeaveRoom.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/player/PlayerManager.h"

void ChatRoomImplementation::init(ZoneServer* serv, ChatRoom* parent, const String& roomName) {
	server = serv;
	manager = server->getChatManager();

	name = roomName;
	roomID = Long::hashCode(_this.getReferenceUnsafeStaticCast()->_getObjectID());

	if (parent != NULL) {
		parentRoomID = parent->getRoomID();
		fullPath = parent->getFullPath() + "." + roomName;
	} else
		fullPath = roomName;

	playerList.setNoDuplicateInsertPlan();
	playerList.setNullValue(NULL);

	invitedList.setNoDuplicateInsertPlan();
	moderatorList.setNoDuplicateInsertPlan();
	bannedList.setNoDuplicateInsertPlan();

}

void ChatRoomImplementation::sendTo(CreatureObject* player) {
	ChatRoomList* crl = new ChatRoomList();
	crl->addChannel(_this.getReferenceUnsafeStaticCast());

	crl->insertChannelListCount();
	player->sendMessage(crl);
}

void ChatRoomImplementation::sendDestroyTo(CreatureObject* player) {
	ChatOnDestroyRoom* msg = new ChatOnDestroyRoom("SWG", server->getGalaxyName(), getOwnerName(), roomID);
	player->sendMessage(msg);
}

void ChatRoomImplementation::addPlayer(CreatureObject* player) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	playerList.put(player->getFirstName(), player);
	lastJoin.updateToCurrentTime();

	locker.release();

	Locker plocker(player);
	PlayerObject* ghost = player->getPlayerObject();
	ghost->addChatRoom(getRoomID());

}

void ChatRoomImplementation::removePlayer(CreatureObject* player, bool disconnecting) {
	if (player == NULL)
		return;

	if (!disconnecting) {
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		if (ghost != NULL)
			ghost->removeChatRoom(getRoomID());
	}

	ChatOnLeaveRoom* msg = new ChatOnLeaveRoom(_this.getReferenceUnsafeStaticCast(), player);
	broadcastMessage(msg);

	playerList.drop(player->getFirstName());

}

void ChatRoomImplementation::removeAllPlayers() {
	//Room prelocked
	for (int i = 0; i < playerList.size(); i++) {
		ManagedReference<CreatureObject*> player = playerList.get(i);
		if (player == NULL)
			continue;

		Locker clocker(player, _this.getReferenceUnsafeStaticCast());

		PlayerObject* ghost = player->getPlayerObject();
		if (ghost != NULL)
			ghost->removeChatRoom(getRoomID());
	}

	playerList.removeAll();
}

void ChatRoomImplementation::broadcastMessage(BaseMessage* msg) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < playerList.size(); ++i) {
		ManagedReference<CreatureObject*> player = playerList.get(i);

		if (player)
			player->sendMessage(msg->clone());
	}

	delete msg;
}

void ChatRoomImplementation::broadcastMessageCheckIgnore(BaseMessage* msg, String& senderName) {
	Locker locker(_this.getReferenceUnsafeStaticCast());
	String lowerName = senderName.toLowerCase();
	PlayerManager* playerManager = server->getPlayerManager();
	ManagedReference<CreatureObject*> sender = NULL;
	bool godMode = false;
	ManagedReference<PlayerObject*> senderPlayer = NULL;

	if (playerManager == NULL)
		return;

	sender = playerManager->getPlayer(lowerName);

	if (sender == NULL)
		return;

	senderPlayer = sender->getPlayerObject();

	if (senderPlayer == NULL)
		return;

	if (senderPlayer->hasGodMode())
		godMode = true;


	for (int i = 0; i < playerList.size(); ++i) {
		ManagedReference<CreatureObject*> player = playerList.get(i);

		if (player){
			PlayerObject* ghost = player->getPlayerObject();
			if (ghost == NULL)
				continue;

			if (!ghost->isIgnoring(lowerName) || godMode) {
				player->sendMessage(msg->clone());
			}
		}
	}

	delete msg;
}

String ChatRoomImplementation::getGalaxyName() {
	return server->getGalaxyName();
}

String ChatRoomImplementation::getModeratorName(int index) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	String name = "";
	uint64 objectID = moderatorList.get(index);

	CreatureObject* moderator = server->getObject(objectID).castTo<CreatureObject*>();
	if (moderator != NULL)
		name = moderator->getFirstName();

	return name;
}

String ChatRoomImplementation::getInvitedName(int index) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	String name = "";
	uint64 objectID = invitedList.get(index);

	CreatureObject* invited = server->getObject(objectID).castTo<CreatureObject*>();
	if (invited != NULL)
		name = invited->getFirstName();

	return name;
}

String ChatRoomImplementation::getBannedName(int index) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	String name = "";
	uint64 objectID = bannedList.get(index);

	CreatureObject* banned = server->getObject(objectID).castTo<CreatureObject*>();
	if (banned != NULL)
		name = banned->getFirstName();

	return name;
}

bool ChatRoomImplementation::checkEnterPermission(CreatureObject* player) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (player == NULL || !canEnterRoom)
		return false;

	switch (roomType) {
	case ChatRoom::DEFAULT:
		return true;
	case ChatRoom::AUCTION:
		return true;
	case ChatRoom::GUILD: {
		ManagedReference<GuildObject*> guild = player->getGuildObject().getReferenceUnsafeStaticCast();
		if (guild != NULL) {
			if (guild->getObjectID() == getOwnerID())
				return true;
		}
		return false;
	}
	case ChatRoom::GROUP: {
		ManagedReference<GroupObject*> group = player->getGroup();
		if (group != NULL) {
			if (group->getObjectID() == getOwnerID())
				return true;
		}
		return false;
	}
	case ChatRoom::PLANET: {
		ManagedReference<Zone*> zone = player->getZone();
		if (zone != NULL) {
			if (zone->getObjectID() == getOwnerID())
				return true;
		}
		return false;
	}
	case ChatRoom::CUSTOM:
		if (!hasBanned(player) && (isPublic() || hasInvited(player) || player->getObjectID() == getOwnerID()))
			return true;
		break;

	default:
		break;
	}

	return false;

}
