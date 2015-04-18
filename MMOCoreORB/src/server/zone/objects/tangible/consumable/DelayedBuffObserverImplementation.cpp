/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/objects/tangible/consumable/DelayedBuffObserver.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"


int DelayedBuffObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<DelayedBuff*> buff = this->buff.get();

	if (buff != NULL)
		buff->useCharge();

	return 0;

}
