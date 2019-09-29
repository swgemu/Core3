/*
 * ChatEnterRoomByIdCallback.h
 *
 *  Created on: Nov 5, 2010
 *      Author: oru
 */

#ifndef CHATENTERROOMBYIDCALLBACK_H_
#define CHATENTERROOMBYIDCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatEnterRoomByIdCallback : public MessageCallback {
	uint32 requestID;
	uint32 roomID;

public:
	ChatEnterRoomByIdCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server), requestID(0), roomID(0) {
	}

	void parse(Message* message) {
		requestID = message->parseInt();
		roomID = message->parseInt();
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr)
			return;

		ChatManager* chatManager = server->getChatManager();
		if (chatManager != nullptr)
			chatManager->handleChatEnterRoomById(player, roomID, requestID);
	}

};


#endif /* CHATENTERROOMBYIDCALLBACK_H_ */
