/*
 * ChatLeaveRoomCallback.h
 *
 *  Created on: Oct 11, 2015
 *      Author: Anakis
 */

#ifndef CHATLEAVEROOMCALLBACK_H_
#define CHATLEAVEROOMCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatLeaveRoomCallback : public MessageCallback {

	String roomPath;

public:
	ChatLeaveRoomCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		roomPath = "";
	}

	void parse(Message* message) {
		String blank = "";
		message->parseAscii(blank); //Game
		message->parseAscii(blank); //Galaxy
		message->parseAscii(blank); //Player Name
		message->parseAscii(roomPath);

	}

	void run() {
		ManagedReference<SceneObject*> scene = client->getPlayer();

		if (scene == NULL)
			return;

		CreatureObject* player = cast<CreatureObject*>(scene.get());

		if (player == NULL)
			return;

		Locker locker(player);

		ChatManager* chatManager = server->getChatManager();
		chatManager->handleChatLeaveRoom(player, roomPath);

	}

};




#endif /* CHATLEAVEROOMCALLBACK_H_ */
