/*
 * DroidPlaybackObserverImplementation.cpp
 */

#include "server/zone/objects/tangible/components/droid/DroidHarvestObserver.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/tangible/components/droid/DroidHarvestModuleDataComponent.h"
#include "server/zone/objects/creature/events/DroidPlaybackEvent.h"

int DroidHarvestObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	// check params we should have the player around here
	if (eventType == ObserverEventType::DESTINATIONREACHED) {
		module->harvestDestinationReached();
		return 0;
	}

	SceneObject* sceno = dynamic_cast<SceneObject*>(arg1);
	if (sceno == NULL) {
		return 1;
	}
	if(sceno->isPlayerCreature()) {
		return 1;
	}
	CreatureObject* target = dynamic_cast<CreatureObject*>(sceno);
	if (target == NULL) {
		return 1;
	}
	// make a task and lock the module to run it.

	if (eventType == ObserverEventType::KILLEDCREATURE) {
		// observable needs to be the droid owner, arg1 should be the target
		module->creatureHarvestCheck(target);
	}
	return 0;
}
