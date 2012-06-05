/*
 * SpawnStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef SPAWNSTATECOMPONENT_H_
#define SPAWNSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"

class SpawnStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		// TODO: spawn host and attach actor in ghost slot
		// TODO: move spawning to here through creatureManager

		actor->activateRecovery();

		return AiActor::UNFINISHED;
	}

	uint16 doRecovery(AiActor* actor) {
		return onEnter(actor);
	}

	uint16 doMovement(AiActor* actor) {
		return onEnter(actor);
	}
};


#endif /* SPAWNSTATECOMPONENT_H_ */
