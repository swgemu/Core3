/*
 * DeathStateComponent.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: da
 */

#include "DeathStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/objects/creature/events/RespawnCreatureTask.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"

uint16 DeathStateComponent::onEnter(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	Reference<DespawnCreatureTask*> despawn = dynamic_cast<DespawnCreatureTask*>(actor->getPendingTask("despawn"));

	if (despawn != NULL) {
		despawn->cancel();
		despawn->reschedule(45000);
	} else {
		despawn = new DespawnCreatureTask(actor);
		actor->addPendingTask("despawn", despawn, 45000);
	}

	return AiActor::UNFINISHED;
}

uint16 DeathStateComponent::doRecovery(AiActor* actor) {
	return AiActor::UNFINISHED;
}

uint16 DeathStateComponent::doMovement(AiActor* actor) {
	return AiActor::UNFINISHED;
}
