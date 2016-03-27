/*
 * ChatUninviteFromRoomCallback.h
 *
 *  Created on: Feb 13, 2016
 *      Author: Anakis
 */

#ifndef CHATUNINVITEFROMROOMCALLBACK_H_
#define CHATUNINVITEFROMROOMCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatUninviteFromRoomCallback : public MessageCallback {
	String uninviteeName; //Player to uninvite.
	String roomPath; //Room to uninvite player from.
	int requestID;

public:
	ChatUninviteFromRoomCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		uninviteeName = "";
		roomPath = "";
		requestID = 0;
	}

	void parse(Message* message) {
		String unused;

		message->parseAscii(unused); //Game name
		message->parseAscii(unused); //Galaxy name
		message->parseAscii(uninviteeName); //Player uninvited
		message->parseAscii(roomPath); //Path to room
		requestID = message->parseInt(); //requestID

	}

	void run() {
		ManagedReference<CreatureObject*> uninviter = client->getPlayer();

		if (uninviter == NULL)
			return;

		ManagedReference<ChatManager*> chatManager = server->getChatManager();
		if (chatManager != NULL)
			chatManager->handleChatUninvitePlayer(uninviter, uninviteeName, roomPath, requestID);
	}

};


#endif /* CHATUNINVITEFROMROOMCALLBACK_H_ */
