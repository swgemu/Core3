#ifndef CHATDELETEALLPERSISTENTMESSAGESCALLBACK_H_
#define CHATDELETEALLPERSISTENTMESSAGESCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"

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
			StringIdChatParameter emptyFail("ui_pm", "delete_all_mail_fail"); // Unable to empty the mailbox of %TT.
			emptyFail.setTT(creature->getDisplayedName());
			player->sendSystemMessage(emptyFail);
			return;
		}

		PlayerObject* ghost = player->getPlayerObject();
		StringIdChatParameter emptyPass("ui_pm", "delete_all_mail_success"); //	You have successfully emptied the mailbox of %TT.
		emptyPass.setTT(player->getDisplayedName());

		if (ghost == NULL)
			return;

		Locker locker(player);

		ghost->deleteAllPersistentMessages();
		player->sendSystemMessage(emptyPass);
	}

};


#endif /* CHATDELETEALLPERSISTENTMESSAGESCALLBACK_H_ */
