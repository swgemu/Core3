/*
 * DroidPlaybackObserverImplementation.cpp
 */

#include <stddef.h>

#include "server/zone/objects/tangible/components/droid/DroidPersonalityModuleDataComponent.h"
#include "server/zone/objects/tangible/components/droid/DroidPersonalityObserver.h"
#include "system/lang/ref/Reference.h"
#include "system/lang/ref/WeakReference.h"
#include "system/platform.h"

namespace engine {
namespace core {
class ManagedObject;
}  // namespace core
namespace util {
class Observable;
}  // namespace util
}  // namespace engine

int DroidPersonalityObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	Reference<DroidPersonalityModuleDataComponent*> mod = module.get();

	if (mod == NULL)
		return 1;

	// check params we should have the player around here
	mod->notifyEvent(eventType,arg1, arg2);

	return 0;
}
