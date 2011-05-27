/*
 * NonPlayerCreatureObjectImplementation.cpp
 *
 *  Created on: 23/06/2010
 *      Author: victor
 */

#include "NonPlayerCreatureObject.h"

void NonPlayerCreatureObjectImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	AiAgentImplementation::notifyPositionUpdate(entry);

	SceneObject* scno = (SceneObject*) entry;

	// don't worry about this if no one's around, and do it for any creature
	if (scno == _this || numberOfPlayersInRange <= 0  || !scno->isCreatureObject() || isRetreating() || isFleeing() || isInCombat())
		return;

	if (followObject == NULL || followObject == scno) {
		CreatureObject* creo = (CreatureObject*)scno;

		// TODO: determine if creature can be seen by this (mask scent, et. al.)

		// determine if creature can be a threat
		if (creo->isAiAgent()) {
			AiAgent* aio = (AiAgent*)creo;
			if ((aio->getFerocity() <= 0 || getFerocity() <= 0) && aio->getLevel() >= getLevel())
				return;
		} else
			activateAwarenessEvent(creo);
	}

}

void NonPlayerCreatureObjectImplementation::doAwarenessCheck(Coordinate& start, uint64 time, CreatureObject* target) {
	if (isDead() || getZone() == NULL || time == 0 || !isAggressiveTo(target))
		return;

	// TODO: another formula that needs tweaking (after player levels get looked at)
	float range = getLevel() / target->getLevel();
	if (target->isPlayerCreature())
		range /= 10;

	if (target->isInRange(_this, range))
		addDefender(target);

	activateRecovery();
	activateMovementEvent();
}
