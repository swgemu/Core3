/*
 * StandingStateComponent.cpp
 *
 *  Created on: Jun 14, 2012
 *      Author: da
 */

#include "StandingStateComponent.h"
#include "server/zone/objects/creature/ai/AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"

	uint16 StandingStateComponent::onEnter(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		if (host->isDead())
			return AiActor::DEAD;

		if (host->isInCombat())
			return AiActor::ATTACKED;

		actor->getPatrolPoints()->removeAll();

		actor->setNextStepPosition(host->getPositionX(), host->getPositionZ(), host->getPositionY(), host->getParent().get());
		actor->getNextStepPosition()->setReached(true);

		actor->activateRecovery();

		return AiActor::UNFINISHED;
	}

	uint16 StandingStateComponent::doRecovery(AiActor* actor) {
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

	uint16 StandingStateComponent::doMovement(AiActor* actor) {
		if (System::random(5) == 1)
			return AiActor::FINISHED;

		return AiActor::UNFINISHED;
	}

