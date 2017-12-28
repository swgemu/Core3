/*
 * DroidPlaybackObserverImplementation.cpp
 */

#include <stddef.h>
#include <algorithm>

#include "engine/core/ManagedObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/components/droid/DroidHarvestModuleDataComponent.h"
#include "server/zone/objects/tangible/components/droid/DroidHarvestObserver.h"
#include "system/lang/ref/Reference.h"
#include "system/lang/ref/WeakReference.h"
#include "system/platform.h"
#include "templates/params/ObserverEventType.h"

namespace engine {
namespace util {
class Observable;
}  // namespace util
}  // namespace engine

int DroidHarvestObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	Reference<DroidHarvestModuleDataComponent*> mod = module.get();

	if (mod == NULL)
		return 1;

	ManagedReference<CreatureObject*> player = cast<CreatureObject*>(observable);

	if (player == NULL)
		return 1;

	// check params we should have the player around here
	if (eventType == ObserverEventType::DESTINATIONREACHED) {
		mod->harvestDestinationReached();
		return 0;
	}

	SceneObject* sceno = dynamic_cast<SceneObject*>(arg1);

	if (sceno == NULL || sceno->isPlayerCreature())
		return 1;

	CreatureObject* target = dynamic_cast<CreatureObject*>(sceno);

	if (target == NULL)
		return 1;

	// make a task and lock the module to run it.

	if (eventType == ObserverEventType::KILLEDCREATURE && player->isInRange(target, 256.0f)) {
		// observable needs to be the droid owner, arg1 should be the target
		mod->creatureHarvestCheck(target);
	}

	return 0;
}
