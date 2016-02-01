/*
 * ChatEnterRoomByIdCallback.h
 *
 *  Created on: Nov 5, 2010
 *      Author: oru
 */

#ifndef CHATENTERROOMBYIDCALLBACK_H_
#define CHATENTERROOMBYIDCALLBACK_H_


#include "../MessageCallback.h"
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
		ManagedReference<SceneObject*> scene = client->getPlayer();

		if (scene == NULL)
			return;

		CreatureObject* player = cast<CreatureObject*>(scene.get());

		if (player == NULL)
			return;

		ChatManager* chatManager = server->getChatManager();
		chatManager->handleChatEnterRoomById(player, roomID, requestID);

	}

};




#endif /* CHATENTERROOMBYIDCALLBACK_H_ */
