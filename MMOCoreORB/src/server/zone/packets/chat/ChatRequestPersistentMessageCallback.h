/*
 * ChatRequestPersistentMessageCallback.h
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#ifndef CHATREQUESTPERSISTENTMESSAGECALLBACK_H_
#define CHATREQUESTPERSISTENTMESSAGECALLBACK_H_

#include "../MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatRequestPersistentMessageCallback : public MessageCallback {
	uint32 mailid;

public:
	ChatRequestPersistentMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server), mailid(0) {
	}

	void parse(Message* message) {
		message->shiftOffset(4); //skip spacer/unk
		mailid = message->parseInt();
	}

	void run() {
		ManagedReference<SceneObject*> scene = client->getPlayer();

		if (scene == NULL)
			return;

		CreatureObject* player = cast<CreatureObject*>(scene.get());

		if (player == NULL)
			return;

		ChatManager* chatManager = server->getChatManager();
		chatManager->handleRequestPersistentMsg(player, mailid);
	}

};


#endif /* CHATREQUESTPERSISTENTMESSAGECALLBACK_H_ */
