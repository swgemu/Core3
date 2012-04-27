/*
 * SingleUseBuffObserverImplementation.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: dannuic
 */

#include "SingleUseBuffObserver.h"
#include "SingleUseBuff.h"

#include "server/zone/managers/objectcontroller/ObjectController.h"
//#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/objects/creature/commands/QueueCommand.h"

int SingleUseBuffObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<CreatureObject*> player = buff->getPlayer();
	if (player == NULL)
		return 1;

	ManagedReference<ObjectController*> objectController = player->getZoneServer()->getObjectController();

	unsigned int commandCRC = buff->getCommandCRC();
	QueueCommand* queueCommand = objectController->getQueueCommand(commandCRC);

	queueCommand->dropBuff(arg1, (int)arg2);

	player->removeBuff(buff);

	return 0;
}



