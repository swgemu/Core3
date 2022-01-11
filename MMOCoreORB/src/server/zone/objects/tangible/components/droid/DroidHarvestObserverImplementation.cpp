/*
 * DroidPlaybackObserverImplementation.cpp
 */

#include "server/zone/objects/tangible/components/droid/DroidHarvestObserver.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "templates/params/ObserverEventType.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/tangible/components/droid/DroidHarvestModuleDataComponent.h"
#include "server/zone/objects/creature/events/DroidPlaybackEvent.h"

int DroidHarvestObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	Reference<DroidHarvestModuleDataComponent*> mod = module.get();

	if (mod == nullptr || !mod->isActive())
		return 1;

	ManagedReference<CreatureObject*> player = cast<CreatureObject*>(observable);

	if (player == nullptr)
		return 1;

	SceneObject* sceno = dynamic_cast<SceneObject*>(arg1);

	if (sceno == nullptr || sceno->isPlayerCreature())
		return 1;

	CreatureObject* target = dynamic_cast<CreatureObject*>(sceno);

	if (target == nullptr)
		return 1;

	if (eventType == ObserverEventType::KILLEDCREATURE && player->isInRange(target, 64.0f)) {
		mod->creatureHarvestCheck(target);
	}

	return 0;
}
