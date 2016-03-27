/*
 * ChatAddModeratorToRoomCallback.h
 *
 *  Created on: Feb 16, 2016
 *      Author: Anakis
 */

#ifndef CHATADDMODERATORTOROOMCALLBACK_H_
#define CHATADDMODERATORTOROOMCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatAddModeratorToRoomCallback : public MessageCallback {
	String opeeName; //Player to op.
	String roomPath; //Room to op player in.
	int requestID;

public:
	ChatAddModeratorToRoomCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		opeeName = "";
		roomPath = "";
		requestID = 0;
	}

	void parse(Message* message) {
		String unused;

		message->parseAscii(unused); //Game name
		message->parseAscii(unused); //Galaxy name
		message->parseAscii(opeeName); //Player to op
		message->parseAscii(roomPath); //Path to room
		requestID = message->parseInt(); //Request ID

	}

	void run() {
		ManagedReference<CreatureObject*> oper = client->getPlayer();

		if (oper == NULL)
			return;

		ManagedReference<ChatManager*> chatManager = server->getChatManager();
		if (chatManager != NULL)
			chatManager->handleChatAddModerator(oper, opeeName, roomPath, requestID);
	}

};


#endif /* CHATADDMODERATORTOROOMCALLBACK_H_ */
