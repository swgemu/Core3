/*
 * WanderingStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef WANDERINGSTATECOMPONENT_H_
#define WANDERINGSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"

class WanderingStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		if (host->isDead())
			return AiActor::DEAD;

		if (host->isInCombat())
			return AiActor::ATTACKED;

		PatrolPointsVector* patrolPoints = actor->getPatrolPoints();
		patrolPoints->removeAll();

		// TODO: read patrol paths
		//PatrolPathTemplate* patrolPathTemplate = CreatureTemplateManager::instance()->getPatrolPathTemplate(actor->getCreatureTemplate()->getPatrolPathTemplate());
		WorldCoordinates homeLocation = actor->getHomeLocation()->getCoordinates();
		Coordinate position(homeLocation.getX(), homeLocation.getZ(), homeLocation.getY());
		position.randomizePosition(32);

		actor->activateRecovery();
		actor->activateMovementEvent();

		// don't wander in cells (this will be implemented with patrol paths)
		if (host->getParent() != NULL) {
			return AiActor::UNFINISHED;
		}

		setNextPosition(actor, position.getPositionX(), position.getPositionZ(), position.getPositionY(), NULL);

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

	float getSpeed(CreatureObject* host) {
		return host->getWalkSpeed();
	}
};


#endif /* WANDERINGSTATECOMPONENT_H_ */
