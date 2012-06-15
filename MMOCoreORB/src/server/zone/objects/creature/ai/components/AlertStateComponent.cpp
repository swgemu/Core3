/*
 * AlertStateComponent.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: da
 */

#include "AlertStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"

uint16 AlertStateComponent::onEnter(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	if (host->isDead())
		return AiActor::DEAD;

	if (host->isInCombat())
		return AiActor::ATTACKED;

	host->showFlyText("npc_reaction/flytext", "alert", 0xFF, 0, 0);

	actor->activateMovementEvent();
	actor->activateRecovery();

	return AiActor::INTERESTED;
}

uint16 AlertStateComponent::doRecovery(AiActor* actor) {
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

	ManagedReference<SceneObject*> followObject = actor->getFollowObject();
	if (followObject == NULL || !host->isInRange(followObject, 128.f))
		return AiActor::FORGOT;

	if (isScared(host, followObject))
		return AiActor::SCARED;

	if (followObject->isCreatureObject() && actor->isAggressiveTo(followObject.castTo<CreatureObject*>()))
		return AiActor::ATTACKED;

	actor->activateRecovery();

	return AiActor::UNFINISHED;
}

uint16 AlertStateComponent::doMovement(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	checkNewAngle(actor);

	actor->activateMovementEvent();

	return AiActor::UNFINISHED;
}


