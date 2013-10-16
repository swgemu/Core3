/*
 * SingleUseBuffObserverImplementation.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: dannuic
 */

#include "server/zone/objects/creature/buffs/SingleUseBuffObserver.h"
#include "server/zone/objects/creature/buffs/SingleUseBuff.h"

#include "server/zone/managers/objectcontroller/ObjectController.h"
//#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/objects/creature/commands/QueueCommand.h"

int SingleUseBuffObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<SingleUseBuff* > buff = this->buff.get();

	if (buff == NULL)
		return 1;

	ManagedReference<CreatureObject*> player = buff.get()->getPlayer();
	if (player == NULL)
		return 1;

	ManagedReference<ObjectController*> objectController = player->getZoneServer()->getObjectController();

	unsigned int commandCRC = buff.get()->getCommandCRC();
	QueueCommand* queueCommand = objectController->getQueueCommand(commandCRC);

	SceneObject* creature = cast<SceneObject*>( observable);

	queueCommand->handleBuff(creature, arg1, (int)arg2);

	return 0;
}



