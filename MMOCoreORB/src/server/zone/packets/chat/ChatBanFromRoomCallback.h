/*
 * ChatBanFromRoomCallback.h
 *
 *  Created on: Feb 18, 2016
 *      Author: Anakis
 */

#ifndef CHATBANFROMROOMCALLBACK_H_
#define CHATBANFROMROOMCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatBanFromRoomCallback : public MessageCallback {
	String baneeName; //Player to ban.
	String roomPath; //Room to ban the player from.
	int requestID;

public:
	ChatBanFromRoomCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		baneeName = "";
		roomPath = "";
		requestID = 0;
	}

	void parse(Message* message) {
		String unused;

		message->parseAscii(unused); //Game name
		message->parseAscii(unused); //Galaxy name
		message->parseAscii(baneeName); //Player to ban
		message->parseAscii(roomPath); //Path to room
		requestID = message->parseInt(); //Request ID

	}

	void run() {
		ManagedReference<CreatureObject*> banner = client->getPlayer();

		if (banner == NULL)
			return;

		ManagedReference<ChatManager*> chatManager = server->getChatManager();
		if (chatManager != NULL)
			chatManager->handleChatBanPlayer(banner, baneeName, roomPath, requestID);
	}

};


#endif /* CHATBANFROMROOMCALLBACK_H_ */
