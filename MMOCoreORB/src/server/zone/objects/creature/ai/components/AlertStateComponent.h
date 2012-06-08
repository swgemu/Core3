/*
 * AlertStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef ALERTSTATECOMPONENT_H_
#define ALERTSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"

class AlertStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor) {
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

		ManagedReference<SceneObject*> followObject = actor->getFollowObject();
		if (followObject == NULL || !host->isInRange(followObject, 128.f))
			return AiActor::FORGOT;

		if (isScared(host, followObject))
			return AiActor::SCARED;

		actor->activateRecovery();

		return AiActor::INTERESTED;
	}

	uint16 doMovement(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		if (host->isDead())
			return AiActor::DEAD;

		if (host->isInCombat())
			return AiActor::ATTACKED;

		ManagedReference<SceneObject*> followObject = actor->getFollowObject();
		if (followObject == NULL || !host->isInRange(followObject, 128.f))
			return AiActor::FORGOT;

		if (isScared(host, followObject))
			return AiActor::SCARED;

		host->setDirection(atan2(followObject->getPositionX() - host->getPositionX(), followObject->getPositionX() - host->getPositionX()));
		checkNewAngle(actor);

		actor->activateMovementEvent();

		return AiActor::INTERESTED;
	}
};


#endif /* ALERTSTATECOMPONENT_H_ */
