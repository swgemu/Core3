/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMMANDQUEUEENQUEUE_H_
#define COMMANDQUEUEENQUEUE_H_

#include "ObjectControllerMessage.h"
#include "server/zone/packets/MessageCallback.h"

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

	const char* actionName;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	CommandQueueEnqueueCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		size(0), actionCount(0), actionCRC(0), targetID(0), actionName(nullptr), objectControllerMain(objectControllerCallback) {

	}

	void parse(Message* message) {
		size = message->parseInt(); //?

		actionCount = message->parseInt();
		actionCRC = message->parseInt();

		targetID = message->parseLong();

		message->parseUnicode(arguments);
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

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
			ObjectController* objectController = server->getObjectController();

			if (objectController) {
				QueueCommand* queueCommand = objectController->getQueueCommand(actionCRC);

				if (queueCommand) {
					actionName = queueCommand->getQueueCommandName();
				}
			}

			if (miliDifference < 1000)
				client->increaseCommandCount();
			else {
				client->resetCommandCount();
				commandCooldown->updateToCurrentTime();
			}

			player->enqueueCommand(actionCRC, actionCount, targetID, arguments, -1, actionCount&0x3FFFFFFF);
		}
	}

	const char* getTaskName() {
		if (actionName) {
			return actionName;
		} else {
			return Task::getTaskName();
		}
	}
};

#endif /*COMMANDQUEUEENQUEUE_H_*/
