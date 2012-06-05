/*
 * StandingStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef STANDINGSTATECOMPONENT_H_
#define STANDINGSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"

class StandingStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		if (host->isDead())
			return AiActor::DEAD;

		if (host->isInCombat())
			return AiActor::ATTACKED;

		actor->getPatrolPoints()->removeAll();

		actor->activateRecovery();

		return AiActor::UNFINISHED;
	}

	uint16 doRecovery(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		if (host->isDead())
			return AiActor::DEAD;

		host->activateHAMRegeneration();
		host->activateStateRecovery();
		actor->activatePostureRecovery();

		if (host->isInCombat())
			return AiActor::ATTACKED;

		if (System::random(5) == 0)
			return AiActor::FINISHED;

		return AiActor::UNFINISHED;
	}

	uint16 doMovement(AiActor* actor) {
		return AiActor::UNFINISHED;
	}
};


#endif /* STANDINGSTATECOMPONENT_H_ */
