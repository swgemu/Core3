/*
 * AiCreatureComponent.h
 *
 *  Created on: Feb 15, 2012
 *      Author: da
 */

#ifndef AICREATURECOMPONENT_H_
#define AICREATURECOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/components/AiInterfaceComponent.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/creature/Creature.h"

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

class AiCreatureComponent : public AiInterfaceComponent, public Logger {
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
		if (!scno->isCreatureObject() && !cast<CreatureObject*>(scno)->isCreature())
			return;

		if (target->getDistanceTo(scno) >= 128.f)
			return;

		Reference<Creature*> ai = cast<Creature*>(scno);

#ifdef DEBUG
		info("Starting doAwarenessCheck", true);
#endif

		if (ai->isDead() || ai->getZone() == NULL || time == 0 || target->isDead())
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

		if(ai->isCamouflaged(target))
			return;

		// calculate average speed
		Vector3 deltaV(target->getPositionX() - start.getPositionX(), target->getPositionY() - start.getPositionY(), 0);
		float avgSpeed = deltaV.squaredLength() / (time) * 1000000;

		// set frightened or threatened
		// TODO: weight this by ferocity/level difference
		Reference<SceneObject*> followObject = ai->getFollowObject();

		if (!ai->isInCombat()) {
			if (ai->isStalker() && ai->isAggressiveTo(target)) {
				if (followObject == NULL)
					ai->setStalkObject(target);
				else if (avgSpeed <= (target->getWalkSpeed() * target->getWalkSpeed()))
					ai->addDefender(target);
			} else if (ai->isAggressiveTo(target))
				ai->addDefender(target);
			else if (avgSpeed <= (target->getWalkSpeed() * target->getWalkSpeed())) {
				ai->setOblivious();
			} else if (followObject == NULL) {
				ai->setWatchObject(target);
				ai->showFlyText("npc_reaction/flytext", "alert", 0xFF, 0, 0);
			} else if (followObject->isCreatureObject() && target == followObject) {
				ManagedReference<CreatureObject*> creo = dynamic_cast<CreatureObject*>(followObject.get());
				// determine if frightened or threatened
				if (creo->isAiAgent()) {
					AiAgent* aio = cast<AiAgent*>(creo.get());
					if (ai->getFerocity() > aio->getFerocity() && ai->getLevel() >= aio->getLevel())
						ai->addDefender(aio);
					else if (ai->getLevel() < aio->getLevel()) {
						if (!ai->tryRetreat())
							ai->runAway(target);
					} else
						ai->setOblivious();
				} else if (creo->isPlayerCreature()) {
					CreatureObject* play = cast<CreatureObject*>(creo.get());
					// TODO: tweak this formula based on feedback
					if ((ai->getFerocity() * ai->getLevel() / 4) < play->getLevel()) {
						if (!ai->tryRetreat())
							ai->runAway(target);
					} else
						ai->addDefender(play);
				}
			}
		}

		ai->activateRecovery();
		ai->activateMovementEvent();
	}
};

#endif /* AICREATURECOMPONENT_H_ */
