/*
 * SpawnStateComponent.cpp
 *
 *  Created on: Jun 14, 2012
 *      Author: da
 */

#include "SpawnStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/managers/creature/CreatureManager.h"

uint16 SpawnStateComponent::onEnter(AiActor* actor) {
	Zone* zone = actor->getZone();
	if (zone == NULL)
		return AiActor::NONE;

	CreatureManager* cMgr = zone->getCreatureManager();
	if (cMgr == NULL)
		return AiActor::NONE;

	CreatureTemplate* npcTemplate = actor->getNpcTemplate()->get();
	if (npcTemplate == NULL)
		return AiActor::NONE;

	PatrolPoint* home = actor->getHomeLocation();
	if (home == NULL) // something bad happened, should always have a home point
		return AiActor::NONE;

	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	host->transferObject(actor, 4);
	actor->loadTemplateData(npcTemplate);
	host->setPosture(CreaturePosture::UPRIGHT, true);

	uint64 cellID = 0;
	if (home->getCell() != NULL)
		cellID = home->getCell()->getObjectID();

	cMgr->placeCreature(host, home->getPositionX(), home->getPositionZ(), home->getPositionY(), cellID);

	actor->activateRecovery();

	return AiActor::FINISHED;
}

uint16 SpawnStateComponent::doRecovery(AiActor* actor) {
	return onEnter(actor);
}

uint16 SpawnStateComponent::doMovement(AiActor* actor) {
	return onEnter(actor);
}

