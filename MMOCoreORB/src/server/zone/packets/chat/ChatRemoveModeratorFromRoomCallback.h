/*
 * ChatRemoveModeratorFromRoomCallback.h
 *
 *  Created on: Feb 13, 2016
 *      Author: Anakis
 */

#ifndef CHATREMOVEMODERATORFROMROOMCALLBACK_H_
#define CHATREMOVEMODERATORFROMROOMCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatRemoveModeratorFromRoomCallback : public MessageCallback {
	String deopeeName; //Player to deop.
	String roomPath; //Room to deop the player in.
	int requestID;

public:
	ChatRemoveModeratorFromRoomCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		deopeeName = "";
		roomPath = "";
		requestID = 0;
	}

	void parse(Message* message) {
		String unused;

		message->parseAscii(unused); //Game name
		message->parseAscii(unused); //Galaxy name
		message->parseAscii(deopeeName); //Player to deop
		message->parseAscii(roomPath); //Path to room
		requestID = message->parseInt(); //requestID

	}

	void run() {
		ManagedReference<CreatureObject*> deoper = client->getPlayer();

		if (deoper == NULL)
			return;

		ManagedReference<ChatManager*> chatManager = server->getChatManager();
		if (chatManager != NULL)
			chatManager->handleChatRemoveModerator(deoper, deopeeName, roomPath, requestID);
	}

};


#endif /* CHATREMOVEMODERATORFROMROOMCALLBACK_H_ */
