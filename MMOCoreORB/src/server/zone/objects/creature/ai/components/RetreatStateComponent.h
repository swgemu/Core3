/*
 * RetreatStateComponent.h
 *
 *  Created on: Jun 3, 2012
 *      Author: da
 */

#ifndef RETREATSTATECOMPONENT_H_
#define RETREATSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"

class RetreatStateComponent : public AiStateComponent {
	uint16 onEnter(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		if (host->isDead())
			return AiActor::DEAD;

		PatrolPoint* homeLocation = actor->getHomeLocation();
		homeLocation->setReached(false);

		PatrolPointsVector* patrolPoints = actor->getPatrolPoints();
		patrolPoints->removeAll();
		setNextPosition(actor, homeLocation->getPositionX(), homeLocation->getPositionZ(), homeLocation->getPositionY(), homeLocation->getCell());

		actor->activateMovementEvent();
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

		actor->activateRecovery();

		return AiActor::UNFINISHED;
	}

	uint16 doMovement(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		if (host->isDead())
			return AiActor::DEAD;

		ManagedReference<SceneObject*> followObject = actor->getFollowObject();
		if (followObject == NULL || !host->isInRange(followObject, 128.f))
			return AiActor::FORGOT;

		return AiStateComponent::doMovement(actor);
	}

	float getSpeed(CreatureObject* host) {
		return host->getRunSpeed();
	}

};


#endif /* RETREATSTATECOMPONENT_H_ */
