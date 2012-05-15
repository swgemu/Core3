/*
 * ChatSendToRoomCallback.h
 *
 *  Created on: 30/12/2009
 *      Author: victor
 */

#ifndef CHATSENDTOROOMCALLBACK_H_
#define CHATSENDTOROOMCALLBACK_H_

#include "../MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatSendToRoomCallback : public MessageCallback {
	UnicodeString chatMessage;
	uint32 roomID;
	uint32 counter;

public:
	ChatSendToRoomCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->parseUnicode(chatMessage);

		message->shiftOffset(4); //?

		roomID = message->parseInt();

		counter = message->parseInt();

	}

	void run() {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer());

		if (player == NULL)
			return;

		ChatManager* chatManager = server->getZoneServer()->getChatManager();
		chatManager->handleChatRoomMessage(player, chatMessage, roomID, counter);
	}

};


#endif /* CHATSENDTOROOMCALLBACK_H_ */
