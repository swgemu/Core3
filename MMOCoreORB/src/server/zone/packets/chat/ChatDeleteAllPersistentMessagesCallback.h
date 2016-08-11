#ifndef CHATDELETEALLPERSISTENTMESSAGESCALLBACK_H_
#define CHATDELETEALLPERSISTENTMESSAGESCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/chat/ChatManager.h"

class ChatDeleteAllPersistentMessagesCallback : public MessageCallback {
	uint64 playerID;
	uint64 targetID;

public:
	ChatDeleteAllPersistentMessagesCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server), playerID(0), targetID(0) {
	}

	void parse(Message* message) {
		playerID = message->parseLong();
		targetID = message->parseLong();
	}

	void run() {
		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(targetID);

		if (obj == NULL || !obj->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( obj.get());
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (creature == NULL || player == NULL)
			return;

		if (creature != player) {
			info("Player " + player->getDisplayedName() + " attempted to erase all persistent messages for player " + creature->getDisplayedName());
			return;
		}

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost == NULL)
			return;

		Locker locker(player);

		ghost->deleteAllPersistentMessages();
	}

};


#endif /* CHATDELETEALLPERSISTENTMESSAGESCALLBACK_H_ */
