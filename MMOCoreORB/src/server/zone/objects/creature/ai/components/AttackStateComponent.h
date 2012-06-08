/*
 * AttackStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef ATTACKSTATECOMPONENT_H_
#define ATTACKSTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"

class AttackStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		if (host->isDead())
			return AiActor::DEAD;

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

		if (!host->isInCombat())
			return AiActor::FORGOT;

		ThreatMap* threatMap = host->getThreatMap();
		CreatureObject* target = threatMap->getHighestThreatCreature();
		DeltaVector<ManagedReference<SceneObject* > >* defenderList = host->getDefenderList();
		Time lastDamageReceived = actor->getLastDamageReceived();

		if (target != NULL && !defenderList->contains(target) && (!target->isDead() && !target->isIncapacitated()) && target->isInRange(host, 128.f) && target->isAttackableBy(host) && lastDamageReceived.miliDifference() < 20000)
			host->addDefender(target);
		// threatmap.getHighestThreatCreature() checks for all these things, but it might still happen maybe?
		else if (target != NULL && defenderList->contains(target) && (target->isDead() || target->isIncapacitated() || !target->isInRange(host, 128.f) || !target->isAttackableBy(host))) {
			host->removeDefender(target);
			target = NULL;
		}

		// this is a failsafe, perhaps use threatmap to get another target instead of the defender list
		if (target == NULL && defenderList->size() > 0) {
			for (int i = 0; i < defenderList->size(); ++i) {
				SceneObject* tarObj = defenderList->get(i);

				if (tarObj->isCreatureObject()) {
					CreatureObject* targetCreature = cast<CreatureObject*>(tarObj);

					if (!targetCreature->isDead() && !targetCreature->isIncapacitated() && targetCreature->isInRange(host, 128.f) && targetCreature->isAttackableBy(host)) {
						target = targetCreature;

						break;
					}
				}
			}
		}

		if (!host->isInCombat() || defenderList->size() <= 0 || target == NULL)
			return AiActor::FORGOT;

		if (!target->isInRange(host, 128.f) || !target->isAttackableBy(host) || target->isDead() || target->isIncapacitated() || (target->hasState(CreatureState::PEACE) && (System::random(host->getLevel()) == 1))) {
			host->removeDefender(target);
			return AiActor::FORGOT;
		}

		if (host->getCommandQueue()->size() > 5)
			return AiActor::UNFINISHED;

		if (target != actor->getFollowObject()) {
			actor->setFollowObject(target);

			if (target != NULL)
				host->setDefender(target);
		}

		selectWeapon(actor);

		CreatureTemplate* npcTemplate = actor->getCreatureTemplate();
		CommandQueueActionVector* commandQueue = host->getCommandQueue();

		// attack selection
		if (npcTemplate != NULL && commandQueue->size() < 3) {
			// do special attack
			CreatureAttackMap* attackMap = npcTemplate->getAttacks();
			int attackNum = attackMap->getRandomAttackNumber();

			if (attackNum < 0 || attackNum >= attackMap->size()) {
				host->enqueueCommand(String("defaultattack").hashCode(), 0, target->getObjectID(), "");
			} else {
				String args = attackMap->getArguments(attackNum);

				if (!validateStateAttack(target, args)) {
					// do default attack
					host->enqueueCommand(String("defaultattack").hashCode(), 0, target->getObjectID(), "");
				} else {
					// queue special attack
					unsigned int actionCRC = attackMap->getCommand(attackNum).hashCode();
					host->enqueueCommand(actionCRC, 0, target->getObjectID(), args);
				}
			}
		} else if (npcTemplate == NULL)
			host->enqueueCommand(String("defaultattack").hashCode(), 0, target->getObjectID(), "");

		return AiActor::UNFINISHED;
	}

	uint16 doMovement(AiActor* actor) {
		PatrolPointsVector* patrolPoints = actor->getPatrolPoints();
		SceneObject* followObject = actor->getFollowObject();

		if (followObject != NULL) {
			patrolPoints->removeAll();
			setNextPosition(actor, followObject->getPositionX(), followObject->getPositionZ(), followObject->getPositionY(), followObject->getParent().get());
		} else
			return AiActor::FORGOT;

		return AiStateComponent::doMovement(actor);
	}

	float getMaxDistance(CreatureObject* host) {
		return host->getWeapon()->getIdealRange(true);
	}

	float getSpeed(CreatureObject* host) {
		return host->getRunSpeed();
	}
};


#endif /* ATTACKSTATECOMPONENT_H_ */
