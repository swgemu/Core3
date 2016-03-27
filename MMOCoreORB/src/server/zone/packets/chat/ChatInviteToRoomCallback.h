/*
 * ChatInviteToRoomCallback.h
 *
 *  Created on: Feb 11, 2016
 *      Author: Anakis
 */

#ifndef CHATINVITETOROOMCALLBACK_H_
#define CHATINVITETOROOMCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatInviteToRoomCallback : public MessageCallback {
	String inviteeName; //Player to invite.
	String roomPath; //Room to invite player to.
	int requestID;

public:
	ChatInviteToRoomCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		inviteeName = "";
		roomPath = "";
		requestID = 0;
	}

	void parse(Message* message) {
		String unused;

		message->parseAscii(unused); //Game name
		message->parseAscii(unused); //Galaxy name
		message->parseAscii(inviteeName); //Player invited
		message->parseAscii(roomPath); //Path to room
		requestID = message->parseInt(); //Request ID

	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == NULL)
			return;

		ManagedReference<ChatManager*> chatManager = server->getChatManager();
		if (chatManager != NULL)
			chatManager->handleChatInvitePlayer(player, inviteeName, roomPath, requestID);
	}

};


#endif /* CHATINVITETOROOMCALLBACK_H_ */
