/*
 * ChatCreateRoomCallback.h
 *
 *  Created on: Oct 7, 2015
 *      Author: Anakis
 */

#ifndef CHATCREATEROOMCALLBACK_H_
#define CHATCREATEROOMCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatCreateRoomCallback : public MessageCallback {
	uint8 moderationFlag; //0=not-moderated, 1=moderated
	uint8 permissionFlag; //0=private, 1=public
	String roomPath; //"SWG.Bria.group.281263685532.GroupChat.RoomName"
	String roomTitle;
	int requestID;
	short unknown;

public:
	ChatCreateRoomCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		moderationFlag = 0;
		permissionFlag = 0;
		roomPath = "";
		roomTitle = "";
		requestID = 0;
		unknown = 0;

		setCustomTaskQueue("slowQueue");
	}

	void parse(Message* message) {
		permissionFlag = message->parseByte();
		moderationFlag = message->parseByte();
		unknown = message->parseShort(); //not used, always 0.
		message->parseAscii(roomPath);
		message->parseAscii(roomTitle);
		requestID = message->parseInt();

	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == NULL)
			return;

		ChatManager* chatManager = server->getChatManager();
		if (chatManager != NULL)
			chatManager->handleChatCreateRoom(player, permissionFlag, moderationFlag, roomPath, roomTitle, requestID);
	}

};


#endif /* CHATCREATEROOMCALLBACK_H_ */
