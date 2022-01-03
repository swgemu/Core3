/*
 * SingleUseBuffObserverImplementation.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: dannuic
 */

#include "server/zone/objects/creature/buffs/SingleUseBuffObserver.h"
#include "server/zone/objects/creature/buffs/SingleUseBuff.h"

#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/objects/creature/commands/QueueCommand.h"

int SingleUseBuffObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<SingleUseBuff* > buff = this->buff.get();

	if (buff == nullptr)
		return 1;

	ManagedReference<CreatureObject*> player = buff->getPlayer();

	if (player == nullptr)
		return 1;

	ZoneServer* zoneServer = player->getZoneServer();

	if (zoneServer == nullptr)
		return 1;

	ManagedReference<ObjectController*> objectController = zoneServer->getObjectController();

	unsigned int commandCRC = buff->getCommandCRC();
	const QueueCommand* queueCommand = objectController->getQueueCommand(commandCRC);

	SceneObject* creature = cast<SceneObject*>(observable);

	queueCommand->handleBuff(creature, arg1, (int)arg2);

	return 0;
}
