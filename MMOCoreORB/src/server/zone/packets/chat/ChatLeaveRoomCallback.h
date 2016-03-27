/*
 * ChatLeaveRoomCallback.h
 *
 *  Created on: Oct 11, 2015
 *      Author: Anakis
 */

#ifndef CHATLEAVEROOMCALLBACK_H_
#define CHATLEAVEROOMCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatLeaveRoomCallback : public MessageCallback {

	String roomPath;
	String leavingName;

public:
	ChatLeaveRoomCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		roomPath = "";
		leavingName = "";
	}

	void parse(Message* message) {
		String unused = "";
		message->parseAscii(unused); //Game
		message->parseAscii(unused); //Galaxy
		message->parseAscii(leavingName); //Player Name
		message->parseAscii(roomPath); //Full room path

	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == NULL)
			return;

		ChatManager* chatManager = server->getChatManager();
		if (chatManager == NULL)
			return;

		String senderName = player->getFirstName().toLowerCase();

		if (senderName != leavingName.toLowerCase()) { //One player is kicking another from a room.
			chatManager->handleChatKickPlayer(player, leavingName, roomPath);
		} else { //Player is just trying to leave a room (or kicked himself).
			Locker locker(player);
			chatManager->handleChatLeaveRoom(player, roomPath);
		}
	}

};


#endif /* CHATLEAVEROOMCALLBACK_H_ */
