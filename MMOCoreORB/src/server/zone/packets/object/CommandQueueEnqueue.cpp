#include "server/zone/objects/creature/CreatureObject.h"

#include "ObjectControllerMessage.h"
#include "ObjectControllerMessageCallback.h"
#include "CommandQueueEnqueue.h"

#include "server/zone/managers/objectcontroller/ObjectController.h"

#include "server/zone/objects/creature/commands/QueueCommand.h"

CommandQueueEnqueueCallback::CommandQueueEnqueueCallback(ObjectControllerMessageCallback* objectControllerCallback) :
	MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
	size(0), actionCount(0), actionCRC(0), targetID(0), actionName(nullptr), objectControllerMain(objectControllerCallback) {

}

void CommandQueueEnqueueCallback::parse(Message* message) {
	size = message->parseInt(); //?

	actionCount = message->parseInt();
	actionCRC = message->parseInt();

	targetID = message->parseLong();

	message->parseUnicode(arguments);
}

void CommandQueueEnqueueCallback::run() {
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
			const QueueCommand* queueCommand = objectController->getQueueCommand(actionCRC);

			if (queueCommand) {
				actionName = queueCommand->getQueueCommandName().toCharArray();
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

const char* CommandQueueEnqueueCallback::getTaskName() {
	if (actionName) {
		return actionName;
	} else {
		return Task::getTaskName();
	}
}
