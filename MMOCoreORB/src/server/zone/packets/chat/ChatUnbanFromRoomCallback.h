/*
 * ChatUnbanFromRoomCallback.h
 *
 *  Created on: Feb 19, 2016
 *      Author: Anakis
 */

#ifndef CHATUNBANFROMROOMCALLBACK_H_
#define CHATUNBANFROMROOMCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatUnbanFromRoomCallback : public MessageCallback {
	String unbaneeName; //Player to unban.
	String roomPath; //Room to unban player from.
	int requestID;

public:
	ChatUnbanFromRoomCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		unbaneeName = "";
		roomPath = "";
		requestID = 0;
	}

	void parse(Message* message) {
		String unused;

		message->parseAscii(unused); //Game name
		message->parseAscii(unused); //Galaxy name
		message->parseAscii(unbaneeName); //Player unbanned
		message->parseAscii(roomPath); //Path to room
		requestID = message->parseInt(); //Request ID

	}

	void run() {
		ManagedReference<CreatureObject*> unbanner = client->getPlayer();

		if (unbanner == NULL)
			return;

		ManagedReference<ChatManager*> chatManager = server->getChatManager();
		if (chatManager != NULL)
			chatManager->handleChatUnbanPlayer(unbanner, unbaneeName, roomPath, requestID);
	}

};


#endif /* CHATUNBANFROMROOMCALLBACK_H_ */
