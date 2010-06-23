/*
 * NonPlayerCreatureObjectImplementation.cpp
 *
 *  Created on: 23/06/2010
 *      Author: victor
 */

#include "NonPlayerCreatureObject.h"
#include "events/CreatureThinkEvent.h"
#include "server/zone/managers/combat/CombatManager.h"

void NonPlayerCreatureObjectImplementation::doRecovery() {
	activateHAMRegeneration();
	activateStateRecovery();

	if (damageOverTimeList.hasDot() && damageOverTimeList.isNextTickPast()) {
		damageOverTimeList.activateDots(_this);
	}

	if (isInCombat() && defenderList.size() > 0) {
		SceneObject* targetToAttack = defenderList.get(0);

		if (targetToAttack->isCreatureObject()) {
			CreatureObject* creo = (CreatureObject*) targetToAttack;

			if (creo->isPeaced()) {
				removeDefender(creo);
			} else {
				setTargetID(creo->getObjectID(), true);

				if (commandQueue.size() == 0)
					enqueueCommand(0xA8FEF90A, 0, creo->getObjectID(), ""); // Do default attack
			}
		}
	}

	activateRecovery();
}

void NonPlayerCreatureObjectImplementation::activateRecovery() {
	if (thinkEvent == NULL) {
		thinkEvent = new CreatureThinkEvent(_this);

		thinkEvent->schedule(2000);
	}

	if (!thinkEvent->isScheduled())
		thinkEvent->schedule(2000);
}

int NonPlayerCreatureObjectImplementation::inflictDamage(TangibleObject* attacker, int damageType, int damage, bool destroy, bool notifyClient) {
	activateRecovery();

	return CreatureObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient);
}
