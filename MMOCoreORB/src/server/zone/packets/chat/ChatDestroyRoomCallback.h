/*
 * ChatDestroyRoomCallback.h
 *
 *  Created on: Oct 11, 2015
 *      Author: Anakis
 */

#ifndef CHATDESTROYROOMCALLBACK_H_
#define CHATDESTROYROOMCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatDestroyRoomCallback : public MessageCallback {
	int roomID;
	int requestID;

public:
	ChatDestroyRoomCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		roomID = 0;
		requestID = 0;
	}

	void parse(Message* message) {
		roomID = message->parseInt();
		requestID = message->parseInt();
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == NULL)
			return;

		ChatManager* chatManager = server->getChatManager();
		if (chatManager != NULL)
			chatManager->handleChatDestroyRoom(player, roomID, requestID);
	}

};


#endif /* CHATDESTROYROOMCALLBACK_H_ */
