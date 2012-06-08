/*
 * DeathStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef DEATHSTATECOMPONENT_H_
#define DEATHSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"

class DeathStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		float respawnTimer = actor->getRespawnTimer();
		if (respawnTimer <= 0)
			return AiActor::NONE; // no respawn, this will clean everything up

		/*
		 * TODO: redo RespawnCreatureTask to take AiActor
			Reference<Task*> task = new RespawnCreatureTask(_this, zone, level);
			task->schedule(respawnTimer * 1000);
		 */

		return AiActor::UNFINISHED;
	}

	uint16 doRecovery(AiActor* actor) {
		return AiActor::UNFINISHED;
	}

	uint16 doMovement(AiActor* actor) {
		return AiActor::UNFINISHED;
	}
};


#endif /* DEATHSTATECOMPONENT_H_ */
