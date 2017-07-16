/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/chat/room/ChatRoom.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"

#include "server/zone/packets/chat/ChatRoomList.h"
#include "server/zone/packets/chat/ChatOnDestroyRoom.h"
#include "server/zone/packets/chat/ChatOnLeaveRoom.h"
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
#ifdef LOCKFREE_BCLIENT_BUFFERS
	msg->acquire();
#endif

	ReadLocker locker(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < playerList.size(); ++i) {
		ManagedReference<CreatureObject*>& player = playerList.get(i);

		if (player != NULL) {
#ifdef LOCKFREE_BCLIENT_BUFFERS
			player->sendMessage(msg);
#else
			player->sendMessage(msg->clone());
#endif
		}
	}

#ifdef LOCKFREE_BCLIENT_BUFFERS
	msg->release();
#else
	delete msg;
#endif
}

void ChatRoomImplementation::broadcastMessages(Vector<BaseMessage*>* messages) {
#ifdef LOCKFREE_BCLIENT_BUFFERS
	for (int j = 0; j < messages->size(); ++j) {
		BaseMessage* msg = messages->getUnsafe(j);
		msg->acquire();
	}
#endif

	ReadLocker locker(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < playerList.size(); ++i) {
		ManagedReference<CreatureObject*>& player = playerList.get(i);

		for (int j = 0; j < messages->size(); ++j) {
			BaseMessage* msg = messages->get(j);
#ifdef LOCKFREE_BCLIENT_BUFFERS
			player->sendMessage(msg);
#else
			player->sendMessage(msg->clone());
#endif
		}
	}

	for (int j = 0; j < messages->size(); ++j) {
#ifdef LOCKFREE_BCLIENT_BUFFERS
		messages->get(j)->release();
#else
		delete messages->get(j);
#endif
	}

	messages->removeAll();
}

void ChatRoomImplementation::broadcastMessageCheckIgnore(BaseMessage* msg, const String& senderName) {
	PlayerManager* playerManager = server->getPlayerManager();
	String lowerName = senderName.toLowerCase();

	ManagedReference<CreatureObject*> sender = NULL;
	ManagedReference<PlayerObject*> senderPlayer = NULL;

	bool godMode = false;

	if (playerManager == NULL) {
		delete msg;
		return;
	}

	sender = playerManager->getPlayer(lowerName);

	if (sender == NULL) {
		delete msg;
		return;
	}

	senderPlayer = sender->getPlayerObject();

	if (senderPlayer == NULL) {
		delete msg;
		return;
	}

	if (senderPlayer->hasGodMode())
		godMode = true;

#ifdef LOCKFREE_BCLIENT_BUFFERS
	msg->acquire();
#endif

	ReadLocker locker(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < playerList.size(); ++i) {
		ManagedReference<CreatureObject*>& player = playerList.get(i);

		if (player != nullptr) {
			PlayerObject* ghost = player->getPlayerObject();
			if (ghost == NULL)
				continue;

			if (!ghost->isIgnoring(lowerName) || godMode) {
#ifdef LOCKFREE_BCLIENT_BUFFERS
				player->sendMessage(msg);
#else
				player->sendMessage(msg->clone());
#endif
			}
		}
	}

#ifdef LOCKFREE_BCLIENT_BUFFERS
	msg->release();
#else
	delete msg;
#endif
}

String ChatRoomImplementation::getGalaxyName() {
	return server->getGalaxyName();
}

String ChatRoomImplementation::getModeratorName(int index) {
	ReadLocker locker(_this.getReferenceUnsafeStaticCast());

	uint64 objectID = moderatorList.get(index);
	auto playerManager = server->getPlayerManager();

	return playerManager->getPlayerName(objectID);
}

String ChatRoomImplementation::getInvitedName(int index) {
	ReadLocker locker(_this.getReferenceUnsafeStaticCast());

	uint64 objectID = invitedList.get(index);
	auto playerManager = server->getPlayerManager();

	return playerManager->getPlayerName(objectID);
}

String ChatRoomImplementation::getBannedName(int index) {
	ReadLocker locker(_this.getReferenceUnsafeStaticCast());

	uint64 objectID = bannedList.get(index);
	auto playerManager = server->getPlayerManager();

	return playerManager->getPlayerName(objectID);
}

int ChatRoomImplementation::checkEnterPermission(CreatureObject* player) {
	/* Error Codes:
	 * 0: [Room] You have joined the channel. (SUCCESS)
	 * 6: Chatroom [Room path] does not exist! (NOROOM)
	 * 12: You cannot join [Room path] because you have been banned. (INVALIDBANSTATE)
	 * 13: You cannot join [Room path] because you are not invited to the room. (NOTINVITED)
	 * Default: Chatroom '%TU (room name)' join failed for an unknown reason. (FAIL)
	 */

	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (player == NULL || !canEnterRoom)
		return ChatManager::NOTINVITED;

	switch (roomType) {
	case ChatRoom::DEFAULT:
		return ChatManager::SUCCESS;
	case ChatRoom::AUCTION:
		return ChatManager::SUCCESS;
	case ChatRoom::GUILD: {
		ManagedReference<GuildObject*> guild = player->getGuildObject().getReferenceUnsafeStaticCast();
		if (guild != NULL) {
			if (guild->getObjectID() == getOwnerID())
				return ChatManager::SUCCESS;
		}
		return ChatManager::NOTINVITED;
	}
	case ChatRoom::GROUP: {
		ManagedReference<GroupObject*> group = player->getGroup();
		if (group != NULL) {
			if (group->getObjectID() == getOwnerID())
				return ChatManager::SUCCESS;
		}
		return ChatManager::NOTINVITED;
	}
	case ChatRoom::PLANET: {
		ManagedReference<Zone*> zone = player->getZone();
		if (zone != NULL) {
			if (zone->getObjectID() == getOwnerID())
				return ChatManager::SUCCESS;
		}
		return ChatManager::NOTINVITED;
	}
	case ChatRoom::CUSTOM:
		if (hasBanned(player))
			return ChatManager::INVALIDBANSTATE;
		if (isPrivate() && (!hasInvited(player) && player->getObjectID() != getOwnerID()))
			return ChatManager::NOTINVITED;

		return ChatManager::SUCCESS;

	default:
		break;
	}

	return ChatManager::FAIL;
}

CreatureObject* ChatRoomImplementation::getPlayer(int idx) {
	ReadLocker locker(_this.getReferenceUnsafeStaticCast());

	return playerList.get(idx);
}
