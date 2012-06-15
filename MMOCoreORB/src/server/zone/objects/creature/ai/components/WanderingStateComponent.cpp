/*
 * WanderingStateComponent.cpp
 *
 *  Created on: Jun 14, 2012
 *      Author: da
 */

#include "WanderingStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"

uint16 WanderingStateComponent::onEnter(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	if (host->isDead())
		return AiActor::DEAD;

	if (host->isInCombat())
		return AiActor::ATTACKED;

	// don't wander in cells (this will be implemented with patrol paths)
	if (host->getParent() != NULL) {
		return AiActor::FINISHED;
	}

	PatrolPointsVector* patrolPoints = actor->getPatrolPoints();
	patrolPoints->removeAll();

	// TODO: read patrol paths
	//PatrolPathTemplate* patrolPathTemplate = CreatureTemplateManager::instance()->getPatrolPathTemplate(actor->getCreatureTemplate()->getPatrolPathTemplate());
	WorldCoordinates homeLocation = actor->getHomeLocation()->getCoordinates();
	Coordinate position(homeLocation.getX(), homeLocation.getZ(), homeLocation.getY());
	position.randomizePosition(32);

	actor->activateRecovery();
	actor->activateMovementEvent();

	setNextPosition(actor, position.getPositionX(), position.getPositionZ(), position.getPositionY(), NULL);

	WorldCoordinates nextPosition;
	if (findNextPosition(actor, getMaxDistance(host), getSpeed(host), actor->getPatrolPoints(), &nextPosition))
		actor->setNextStepPosition(nextPosition.getX(), nextPosition.getZ(), nextPosition.getY(), nextPosition.getCell());
	else
		actor->setNextStepPosition(host->getPositionX(), host->getPositionZ(), host->getPositionY(), host->getParent().get());

	return AiActor::UNFINISHED;
}

uint16 WanderingStateComponent::doRecovery(AiActor* actor) {
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

float WanderingStateComponent::getSpeed(CreatureObject* host) {
	return host->getWalkSpeed();
}

