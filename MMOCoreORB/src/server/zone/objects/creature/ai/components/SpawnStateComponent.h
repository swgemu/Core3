/*
 * SpawnStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef SPAWNSTATECOMPONENT_H_
#define SPAWNSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/managers/creature/CreatureManager.h"

class SpawnStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor) {
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

		// TODO: spawn host and attach actor in ghost slot
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			host = cMgr->createCreature(cMgr->getTemplateToSpawn(npcTemplate->getTemplateName().hashCode()).hashCode());

		if (host != NULL) {
			actor->setHost(host);
			actor->loadTemplateData(npcTemplate);
			host->transferObject(actor, 4, false);
			cMgr->placeCreature(host, home->getPositionX(), home->getPositionZ(), home->getPositionY(), home->getCell()->getObjectID());

			return AiActor::FINISHED;
		}

		// something prevented the creature from spawning, schedule a recovery event to try again
		actor->activateRecovery();

		return AiActor::UNFINISHED;
	}

	uint16 doRecovery(AiActor* actor) {
		return onEnter(actor);
	}

	uint16 doMovement(AiActor* actor) {
		return onEnter(actor);
	}
};


#endif /* SPAWNSTATECOMPONENT_H_ */
