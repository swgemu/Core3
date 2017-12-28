/*
 * SingleUseBuffObserverImplementation.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: dannuic
 */

#include <stddef.h>
#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/SingleUseBuff.h"
#include "server/zone/objects/creature/buffs/SingleUseBuffObserver.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "system/lang/ref/Reference.h"
#include "system/platform.h"

namespace engine {
namespace core {
class ManagedObject;
}  // namespace core
namespace util {
class Observable;
}  // namespace util
}  // namespace engine
namespace server {
namespace zone {
namespace objects {
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
}  // namespace zone
}  // namespace server

int SingleUseBuffObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<SingleUseBuff* > buff = this->buff.get();

	if (buff == NULL)
		return 1;

	ManagedReference<CreatureObject*> player = buff->getPlayer();
	if (player == NULL)
		return 1;

	ManagedReference<ObjectController*> objectController = player->getZoneServer()->getObjectController();

	unsigned int commandCRC = buff->getCommandCRC();
	QueueCommand* queueCommand = objectController->getQueueCommand(commandCRC);

	SceneObject* creature = cast<SceneObject*>( observable);

	queueCommand->handleBuff(creature, arg1, (int)arg2);

	return 0;
}
