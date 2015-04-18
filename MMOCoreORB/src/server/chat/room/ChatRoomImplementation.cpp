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
#include "server/zone/packets/chat/ChatOnEnteredRoom.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/player/PlayerManager.h"

void ChatRoomImplementation::sendTo(CreatureObject* player) {
	ChatRoomList* crl = new ChatRoomList();
	crl->addChannel(_this.get());

	crl->insertChannelListCount();
	player->sendMessage(crl);
}

void ChatRoomImplementation::sendDestroyTo(CreatureObject* player) {
	ChatOnDestroyRoom* msg = new ChatOnDestroyRoom("SWG", server->getGalaxyName(), roomID);
	player->sendMessage(msg);
}

void ChatRoomImplementation::addPlayer(CreatureObject* player, bool doLock) {
	Locker locker(_this.get());

	if (playerList.put(player->getFirstName(), player) == -1) {
		//return;
	}

	ChatOnEnteredRoom* coer = new ChatOnEnteredRoom(server->getGalaxyName(), player->getFirstName(), roomID);
	player->sendMessage(coer);

	locker.release();

	Locker locker2(player);

	PlayerObject* ghost = player->getPlayerObject();

	ghost->addChatRoom(_this.get());


	/*ChatOnReceiveRoomInvitation* corri = new ChatOnReceiveRoomInvitation(name);
	player->sendMessage(corri);*/


}

void ChatRoomImplementation::removePlayer(CreatureObject* player, bool doLock) {
	Locker locker(player);

	PlayerObject* ghost = player->getPlayerObject();

	ghost->removeChatRoom(_this.get());

	locker.release();

	Locker locker2(_this.get());

	playerList.drop(player->getFirstName());

	ChatOnLeaveRoom* msg = new ChatOnLeaveRoom(_this.get(), player);
	player->sendMessage(msg);
}

void ChatRoomImplementation::removePlayer(const String& player) {
	// Pre: player unlocked
	Locker locker(_this.get());

	ManagedReference<CreatureObject*> play = playerList.get(player);
	playerList.drop(player);

	locker.release();

	if (play == NULL)
		return;

	Locker locker2(play);

	PlayerObject* ghost = play->getPlayerObject();

	ghost->removeChatRoom(_this.get());

	ChatOnLeaveRoom* msg = new ChatOnLeaveRoom(_this.get(), play);
	play->sendMessage(msg);
}

void ChatRoomImplementation::broadcastMessage(BaseMessage* msg) {
	Locker locker(_this.get());

	for (int i = 0; i < playerList.size(); ++i) {
		ManagedReference<CreatureObject*> player = playerList.get(i);

		if (player)
			player->sendMessage(msg->clone());
	}

	delete msg;
}

void ChatRoomImplementation::broadcastMessageCheckIgnore(BaseMessage* msg, String& senderName) {
	Locker locker(_this.get());
	String lowerName = senderName.toLowerCase();
	PlayerManager* playerManager = server->getPlayerManager();
	ManagedReference<CreatureObject*> sender = NULL;
	bool privileged = false;
	ManagedReference<PlayerObject*> senderPlayer = NULL;

	if (playerManager == NULL)
		return;

	sender = playerManager->getPlayer(lowerName);

	if (sender == NULL)
		return;

	senderPlayer = sender->getPlayerObject();

	if (senderPlayer == NULL)
		return;

	if (senderPlayer->isPrivileged())
		privileged = true;


	for (int i = 0; i < playerList.size(); ++i) {
		ManagedReference<CreatureObject*> player = playerList.get(i);

		if (player){
			PlayerObject* ghost = player->getPlayerObject();
			if (ghost == NULL)
				continue;

			if (!ghost->isIgnoring(lowerName) || privileged) {
				player->sendMessage(msg->clone());
			}
		}
	}

	delete msg;
}

void ChatRoomImplementation::removeAllPlayers() {
	Locker locker(_this.get());

	for (int i = 0; i < playerList.size(); i++) {
		ManagedReference<CreatureObject*> player = playerList.get(i);

		Locker clocker(player, _this.get());

		PlayerObject* ghost = player->getPlayerObject();

		ghost->removeChatRoom(_this.get());
	}

	playerList.removeAll();
}


String ChatRoomImplementation::getGalaxyName() {
	return server->getGalaxyName();
}
