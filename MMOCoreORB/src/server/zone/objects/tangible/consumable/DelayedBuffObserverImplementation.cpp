/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include <stddef.h>
#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/objects/tangible/consumable/DelayedBuffObserver.h"
#include "system/lang/ref/Reference.h"
#include "system/platform.h"
#include "system/thread/Locker.h"

namespace engine {
namespace core {
class ManagedObject;
}  // namespace core
namespace util {
class Observable;
}  // namespace util
}  // namespace engine

int DelayedBuffObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<DelayedBuff*> buff = this->buff.get();

	if (buff != NULL) {
		Locker locker(buff);

		buff->useCharge();
	}

	return 0;
}
