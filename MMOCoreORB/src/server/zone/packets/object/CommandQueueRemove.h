/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMMANDQUEUEREMOVE_H_
#define COMMANDQUEUEREMOVE_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "ObjectControllerMessageCallback.h"

class CommandQueueRemove : public ObjectControllerMessage {
public:
	CommandQueueRemove(CreatureObject* creo, uint32 actioncnt, float timer, uint32 tab1, uint32 tab2) 
			: ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x117) {
		insertInt(actioncnt);
		insertFloat(timer);
		insertInt(tab1);
		insertInt(tab2);
	}

};

class CommandQueueRemoveCallback : public MessageCallback {
	uint32 size;
	uint32 actionCount;
	uint32 actionCRC;

	ObjectControllerMessageCallback* objectControllerMain;

public:

	CommandQueueRemoveCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		size(0), actionCount(0), actionCRC(0), objectControllerMain(objectControllerCallback) {
	}

	void parse(Message* message) {
		size = message->parseInt(); //?

		actionCount = message->parseInt();
		actionCRC = message->parseInt();
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == NULL)
			return;

		//ObjectController* objectController = server->getZoneServer()->getObjectController();
		player->deleteQueueAction(actionCount);
	}

};

#endif /*COMMANDQUEUEREMOVE_H_*/
