/*
 * AttackStateComponent.cpp
 *
 *  Created on: Jun 12, 2012
 *      Author: da
 */

#include "AttackStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/objects/creature/events/CommandQueueTask.h"

uint16 AttackStateComponent::onEnter(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	if (host->isDead())
		return AiActor::DEAD;

	//actor->info("AttackState::onEnter", true);

	SceneObject* target = host->getThreatMap()->getHighestThreatCreature();
	if (target == NULL)
		target = actor->getFollowObject();

	if (target == NULL)
		return AiActor::FORGOT;

	actor->setDefender(target);

	actor->activateMovementEvent();
	actor->activateRecovery();

	return AiActor::UNFINISHED;
}

uint16 AttackStateComponent::doRecovery(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	if (host->isDead())
		return AiActor::DEAD;

	host->activateHAMRegeneration();
	host->activateStateRecovery();
	actor->activatePostureRecovery();

	//host->info("Past activations", true);

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

			if (tarObj == NULL) host->info("NULL tarObj in defenderList", true);

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

	//host->info("non-null target", true);

	if (!target->isInRange(host, 128.f) || !target->isAttackableBy(host) || target->isDead() || target->isIncapacitated() /*|| (target->hasState(CreatureState::PEACE) && (System::random(host->getLevel()) == 1))*/) {
		host->removeDefender(target);
		return AiActor::FORGOT;
	}

	//host->info("valid target", true);

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

	uint32 attackCRC = String("defaultattack").hashCode();
	String args = "";

	// attack selection
	if (npcTemplate != NULL && commandQueue->size() < 3) {
		// do special attack
		CreatureAttackMap* attackMap = npcTemplate->getAttacks();
		int attackNum = attackMap->getRandomAttackNumber();
		String attackArgs = attackMap->getArguments(attackNum);

		if (attackNum >= 0 && attackNum < attackMap->size() && validateStateAttack(target, attackArgs)) {
			// queue special attack
			attackCRC = attackMap->getCommand(attackNum).hashCode();
			args = attackArgs;
		}
	}

	Reference<Task*> cqt = new CommandQueueTask(host, attackCRC, target->getObjectID(), args);
	cqt->execute();

	//host->info("all the way through", true);

	return AiActor::UNFINISHED;
}

uint16 AttackStateComponent::doMovement(AiActor* actor) {
	//actor->info("AttackState::doMovement", true);

	PatrolPointsVector* patrolPoints = actor->getPatrolPoints();
	SceneObject* followObject = actor->getFollowObject();

	if (followObject != NULL) {
		patrolPoints->removeAll();
		setNextPosition(actor, followObject->getPositionX(), followObject->getPositionZ(), followObject->getPositionY(), followObject->getParent().get());

		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		WorldCoordinates nextPosition;
		if (findNextPosition(actor, getMaxDistance(host), getSpeed(host), actor->getPatrolPoints(), &nextPosition))
			actor->setNextStepPosition(nextPosition.getX(), nextPosition.getZ(), nextPosition.getY(), nextPosition.getCell());
		else
			actor->setNextStepPosition(host->getPositionX(), host->getPositionZ(), host->getPositionY(), host->getParent().get());
	} else
		return AiActor::FORGOT;

	checkNewAngle(actor);

	actor->activateMovementEvent(); // ensure that while a creature is in combat, they are always checking for movement

	return AiStateComponent::doMovement(actor);
}
