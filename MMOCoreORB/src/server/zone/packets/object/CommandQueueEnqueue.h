/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMMANDQUEUEENQUEUE_H_
#define COMMANDQUEUEENQUEUE_H_

#include "ObjectControllerMessage.h"
#include "../MessageCallback.h"

#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"

class CommandQueueEnqueue : public ObjectControllerMessage {
public:
	CommandQueueEnqueue(CreatureObject* creo, uint32 actioncnt, uint32 actionCRC) 
			: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0x116) {
		insertInt(actioncnt);
		insertInt(actionCRC);
		insertLong(creo->getTargetID());
		insertInt(0); // UnicodeString shit
	}

};

class CommandQueueEnqueueCallback : public MessageCallback {
	uint32 size;
	uint32 actionCount;
	uint32 actionCRC;
	uint64 targetID;

	UnicodeString arguments;

	ObjectControllerMessageCallback* objectControllerMain;

public:
	CommandQueueEnqueueCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		size(0), actionCount(0), actionCRC(0), targetID(0), objectControllerMain(objectControllerCallback) {

	}

	void parse(Message* message) {
		size = message->parseInt(); //?

		actionCount = message->parseInt();
		actionCRC = message->parseInt();

		targetID = message->parseLong();

		message->parseUnicode(arguments);
	}

	void run() {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer().get().get());

		if (player == NULL)
			return;

		//ObjectController* objectController = server->getZoneServer()->getObjectController();
		Time* commandCooldown = client->getCommandSpamCooldown();
		int commandCount = client->getCommandCount();
		uint64 miliDifference = commandCooldown->miliDifference();

		if (commandCount >= 5 && miliDifference < 1000) {
			//creature->clearQueueAction(actioncntr);
			player->clearQueueAction(actionCount);
			//player->sendSystemMessage("Please stop spamming commands");
		} else {
			if (miliDifference < 1000)
				client->increaseCommandCount();
			else {
				client->resetCommandCount();
				commandCooldown->updateToCurrentTime();
			}

			player->enqueueCommand(actionCRC, actionCount, targetID, arguments);
		}
	}
};

#endif /*COMMANDQUEUEENQUEUE_H_*/
