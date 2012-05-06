/*
 * AiNPCComponent.h
 *
 *  Created on: Feb 15, 2012
 *      Author: da
 */

#ifndef AINPCCOMPONENT_H_
#define AINPCCOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/components/AiInterfaceComponent.h"
#include "server/zone/managers/collision/CollisionManager.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
class SceneObject;
}
namespace creature {
class CreatureObject;
class AiAgent;
}
}
}
}

using namespace server::zone::objects::scene;
using namespace server::zone::objects::creature;

class AiNPCComponent : public AiInterfaceComponent, public Logger {
public:
	void notifyPositionUpdate(SceneObject* scno, QuadTreeEntry* entry) {
		// TODO: all of this logic will change soon, this is just a placeholder from the old code
		if(!scno->isCreatureObject())
			return;

		Reference<CreatureObject*> creo = cast<CreatureObject*>(scno);

		if (creo->isDead())
			return;

		if (!creo->isAiAgent())
			return;

		Reference<AiAgent*> ai = cast<AiAgent*>(creo.get());

		if (ai->getPvpStatusBitmask() == CreatureFlag::NONE)
			return;

		int radius = 32;

		if(ai->getParent() != NULL && ai->getParent()->isCellObject())
			radius = 12;

		int awarenessRadius = ai->getFerocity() + radius;

		if(!entry->isInRange(scno, awarenessRadius))
			return;

		Reference<SceneObject*> scnoEntry = cast<SceneObject*>( entry);

		// don't worry about this if no one's around, and do it for any creature
		if (scnoEntry == scno || ai->getNumberOfPlayersInRange() <= 0  || !scnoEntry->isCreatureObject() || ai->isRetreating() || ai->isFleeing() || ai->isInCombat())
			return;

		if (ai->getFollowObject() == NULL || ai->getFollowObject() == scnoEntry) {
			Reference<CreatureObject*> creoEntry = cast<CreatureObject*>( scnoEntry.get());

			if(creoEntry->getPvpStatusBitmask() == CreatureFlag::NONE)
				return;

			if(ai->isConcealed(creoEntry))
				return;

			/// If not in combat, ignore creatures in different cells
			if(!ai->isInCombat() && ai->getParent() != NULL) {
				if(ai->getParent() != creoEntry->getParent())
					return;
			}

			// TODO: determine if creature can be seen by this (mask scent, et. al.)

			// determine if creature can be a threat
			if (creoEntry->isAiAgent()) {
				Reference<AiAgent*> aio = cast<AiAgent*>(creoEntry.get());
				if ((aio->getFerocity() <= 0 || ai->getFerocity() <= 0) && aio->getLevel() >= ai->getLevel())
					return;
			} else if (ai->isAttackableBy(creoEntry) && ai->isInRange(scnoEntry, 15) && !creoEntry->isDead()) { //no aigent<->aigent combat for now
				ai->activateAwarenessEvent(creoEntry);
			}
		}
	}

	void doAwarenessCheck(SceneObject* scno, Coordinate& start, uint64 time, CreatureObject* target) {
		if (!scno->isCreatureObject() && !cast<CreatureObject*>(scno)->isAiAgent())
			return;

		if (target->getDistanceTo(scno) >= 128.f)
			return;

		Reference<AiAgent*> ai = cast<AiAgent*>(scno);

#ifdef DEBUG
		info("Starting doAwarenessCheck", true);
#endif

		if (ai->isDead() || ai->getZone() == NULL || time == 0)
			return;

		if(!ai->isAggressiveTo(target))
			return;

#ifdef DEBUG
		info("Passed aggressive check", true);
#endif

		if(!CollisionManager::checkLineOfSight(target, ai))
			return;

#ifdef DEBUG
		info("Passed LOS check", true);
#endif

		if (!ai->isInCombat())
		// TODO: another formula that needs tweaking (after player levels get looked at)
			ai->addDefender(target);

		ai->activateRecovery();
		ai->activateMovementEvent();
	}
};

#endif /* AINPCCOMPONENT_H_ */
