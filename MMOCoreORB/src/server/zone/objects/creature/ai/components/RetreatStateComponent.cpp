/*
 * RetreatStateComponent.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: da
 */

#include "RetreatStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"

uint16 RetreatStateComponent::onEnter(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	if (host->isDead())
		return AiActor::DEAD;

	host->setPvpStatusBitmask(0, true);
	actor->setFollowObject(NULL);
	host->clearCombatState(true);

	PatrolPoint* homeLocation = actor->getHomeLocation();
	homeLocation->setReached(false);

	PatrolPointsVector* patrolPoints = actor->getPatrolPoints();
	patrolPoints->removeAll();
	setNextPosition(actor, homeLocation->getPositionX(), homeLocation->getPositionZ(), homeLocation->getPositionY(), homeLocation->getCell());

	WorldCoordinates nextPosition;
	if (findNextPosition(actor, getMaxDistance(host), getSpeed(host), actor->getPatrolPoints(), &nextPosition))
		actor->setNextStepPosition(nextPosition.getX(), nextPosition.getZ(), nextPosition.getY(), nextPosition.getCell());
	else
		actor->setNextStepPosition(host->getPositionX(), host->getPositionZ(), host->getPositionY(), host->getParent().get());

	actor->activateMovementEvent();
	actor->activateRecovery();

	return AiActor::UNFINISHED;
}

uint16 RetreatStateComponent::doRecovery(AiActor* actor) {
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

uint16 RetreatStateComponent::doMovement(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	if (host->isDead())
		return AiActor::DEAD;

	return AiStateComponent::doMovement(actor);
}

void RetreatStateComponent::onExit(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return;

	CreatureTemplate* npcTemplate = actor->getCreatureTemplate();
	host->setPvpStatusBitmask(npcTemplate->getPvpBitmask(), true);
}

float RetreatStateComponent::getSpeed(CreatureObject* host) {
	return host->getRunSpeed();
}


