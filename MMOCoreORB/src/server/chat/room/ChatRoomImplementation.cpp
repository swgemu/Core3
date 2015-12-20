/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/chat/room/ChatRoom.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/packets/chat/ChatRoomList.h"
#include "server/zone/packets/chat/ChatOnDestroyRoom.h"
#include "server/zone/packets/chat/ChatOnLeaveRoom.h"
//#include "server/zone/packets/chat/ChatOnEnteredRoom.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/player/PlayerManager.h"

void ChatRoomImplementation::init(ZoneServer* serv, const String& parent, const String& roomName) {
	server = serv;
	manager = server->getChatManager();

	if (parent.isEmpty()) {
		fullPath = roomName;
	} else {
		parentPath = parent;
		fullPath = parentPath + "." + roomName;
	}

	name = roomName;

	roomID = Long::hashCode(_this.getReferenceUnsafeStaticCast()->_getObjectID());

	isPublicRoom = true;

	subRooms.setNullValue(NULL);

	playerList.setNoDuplicateInsertPlan();
	playerList.setNullValue(NULL);

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

void ChatRoomImplementation::addPlayer(CreatureObject* player, bool doLock) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (playerList.put(player->getFirstName(), player) == -1) {
		//return;
	}

	locker.release();

	Locker locker2(player);

	PlayerObject* ghost = player->getPlayerObject();

	ghost->addChatRoom(getRoomID());

	lastJoin.updateToCurrentTime();

}

void ChatRoomImplementation::removePlayer(CreatureObject* player, bool doLock) {
	Locker locker(player);

	PlayerObject* ghost = player->getPlayerObject();

	ghost->removeChatRoom(getRoomID());

	locker.release();

	Locker locker2(_this.getReferenceUnsafeStaticCast());

	ChatOnLeaveRoom* msg = new ChatOnLeaveRoom(_this.getReferenceUnsafeStaticCast(), player);
	broadcastMessage(msg);

	playerList.drop(player->getFirstName());

	//player->sendMessage(msg);
}

void ChatRoomImplementation::removePlayer(const String& player) {
	// Pre: player unlocked
	Locker locker(_this.getReferenceUnsafeStaticCast());

	ManagedReference<CreatureObject*> play = playerList.get(player);
	if (play == NULL)
		return;

	ChatOnLeaveRoom* msg = new ChatOnLeaveRoom(_this.getReferenceUnsafeStaticCast(), play);
	broadcastMessage(msg);

	playerList.drop(player);

	locker.release();

	Locker locker2(play);

	PlayerObject* ghost = play->getPlayerObject();

	ghost->removeChatRoom(getRoomID());

	//play->sendMessage(msg);
}

void ChatRoomImplementation::removeDisconnectingPlayer(CreatureObject* player) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (player == NULL)
		return;

	ChatOnLeaveRoom* msg = new ChatOnLeaveRoom(_this.getReferenceUnsafeStaticCast(), player);
	broadcastMessage(msg);

	playerList.drop(player->getFirstName());

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

void ChatRoomImplementation::removeAllPlayers() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < playerList.size(); i++) {
		ManagedReference<CreatureObject*> player = playerList.get(i);

		Locker clocker(player, _this.getReferenceUnsafeStaticCast());

		PlayerObject* ghost = player->getPlayerObject();

		ghost->removeChatRoom(getRoomID());
	}

	playerList.removeAll();
}


String ChatRoomImplementation::getGalaxyName() {
	return server->getGalaxyName();
}

String ChatRoomImplementation::getModeratorName(int index) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	String name = "";
	uint64 objectID = moderatorList.get(index);

	CreatureObject* moderator = server->getObject(objectID).castTo<CreatureObject*>();
	if (moderator == NULL)
		return name;

	name = moderator->getFirstName();

	return name;
}

String ChatRoomImplementation::getInvitedName(int index) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	String name = "";
	uint64 objectID = invitedList.get(index);

	CreatureObject* invited = server->getObject(objectID).castTo<CreatureObject*>();
	if (invited == NULL)
		return name;

	name = invited->getFirstName();

	return name;
}

String ChatRoomImplementation::getBannedName(int index) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	String name = "";
	uint64 objectID = bannedList.get(index);

	CreatureObject* banned = server->getObject(objectID).castTo<CreatureObject*>();
	if (banned == NULL)
		return name;

	name = banned->getFirstName();

	return name;
}
