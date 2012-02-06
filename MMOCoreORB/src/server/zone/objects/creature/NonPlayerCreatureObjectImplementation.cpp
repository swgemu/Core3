/*
 * NonPlayerCreatureObjectImplementation.cpp
 *
 *  Created on: 23/06/2010
 *      Author: victor
 */

#include "NonPlayerCreatureObject.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "server/zone/templates/mobile/ConversationScreen.h"
#include "server/zone/managers/collision/CollisionManager.h"

//#define DEBUG

void NonPlayerCreatureObjectImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {

	AiAgentImplementation::notifyPositionUpdate(entry);

	if(getPvpStatusBitmask() == CreatureFlag::NONE)
		return;

	int radius = 32;

	if(getParent() != NULL && getParent()->isCellObject())
		radius = 12;

	int awarenessRadius = getFerocity() + radius;

	if(!entry->isInRange(_this, awarenessRadius))
		return;

#ifdef DEBUG
	info("Passed range check", true);
#endif

	SceneObject* scno = cast<SceneObject*>( entry);

	// don't worry about this if no one's around, and do it for any creature
	if (scno == _this || numberOfPlayersInRange <= 0  || !scno->isCreatureObject() || isRetreating() || isFleeing() || isInCombat())
		return;

	if (followObject == NULL || followObject == scno) {
		CreatureObject* creo = cast<CreatureObject*>(scno);

		if(creo->getPvpStatusBitmask() == CreatureFlag::NONE)
			return;

		/// If not in combat, ignore creatures in different cells
		if(!isInCombat() && getParent() != NULL) {
			if(getParent() != creo->getParent())
				return;
		}

		// TODO: determine if creature can be seen by this (mask scent, et. al.)

		// determine if creature can be a threat
		if (creo->isAiAgent()) {
			AiAgent* aio = cast<AiAgent*>(creo);
			if ((aio->getFerocity() <= 0 || getFerocity() <= 0) && aio->getLevel() >= getLevel())
				return;
		} else
			activateAwarenessEvent(creo);
	}

}

void NonPlayerCreatureObjectImplementation::doAwarenessCheck(Coordinate& start, uint64 time, CreatureObject* target) {

#ifdef DEBUG
	info("Starting doAwarenessCheck", true);
#endif

	if (isDead() || getZone() == NULL || time == 0)
		return;

	if(!isAggressiveTo(target))
		return;

#ifdef DEBUG
	info("Passed aggressive check", true);
#endif

	if(!CollisionManager::checkLineOfSight(target, _this))
		return;

#ifdef DEBUG
	info("Passed LOS check", true);
#endif

	// TODO: another formula that needs tweaking (after player levels get looked at)
	addDefender(target);

	activateRecovery();
	activateMovementEvent();
}
