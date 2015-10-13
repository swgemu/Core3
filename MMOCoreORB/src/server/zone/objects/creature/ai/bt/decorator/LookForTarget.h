#ifndef LOOKFORTARGET_H_
#define LOOKFORTARGET_H_

#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/OptionBitmask.h"
#include "templates/params/creature/CreatureFlag.h"
#include "server/zone/objects/creature/ai/bt/decorator/Decorator.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace decorator {

class LookForTarget : public Decorator {
public:
    LookForTarget(const String& className, const uint32 id, const LuaObject& args)
        : Decorator(className, id, args) {}

    LookForTarget(const LookForTarget& b)
        : Decorator(b) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (   (agent->getOptionsBitmask() & OptionBitmask::AIENABLED) == 0
			|| agent->isDead()
			|| agent->isIncapacitated()
			|| (agent->getPvpStatusBitmask() == CreatureFlag::NONE && 
				!(agent->isDroidObject() && agent->isPet()))
			|| agent->getNumberOfPlayersInRange() <= 0
			|| agent->isRetreating()
			|| agent->isFleeing()
			|| agent->isInCombat()  )
			return FAILURE;

        assert(child != NULL);

		// if we have a follow object, then that is the only thing we pay attention to
		ManagedReference<SceneObject*> currObj = agent->getFollowObject().get();
		if (currObj != NULL) {
			agent->writeBlackboard("targetProspect", currObj);
			return child->doAction(agent);
		}
        
		// get targets we want to apply our child tree to
		// TODO: might have to fix numberOfPlayersInRange here
		CloseObjectsVector* vec = (CloseObjectsVector*) agent->getCloseObjects();
		if (vec == NULL)
			return FAILURE;

		SortedVector<QuadTreeEntry*> closeObjects;
		// TODO: randomize closeObjects as part of this copy
		vec->safeCopyTo(closeObjects);

		for (int i = 0; i < closeObjects.size(); ++i) {
			ManagedReference<SceneObject*> scene = static_cast<SceneObject*>(closeObjects.get(i));
			if (isInvalidTarget(scene->asCreatureObject(), agent))
				continue;

			agent->writeBlackboard("targetProspect", scene);

			Behavior::Status result = child->doAction(agent);
			if (result != FAILURE)
				return result;
		}

        return FAILURE;
    }

	bool isInvalidTarget(CreatureObject* target, AiAgent* agent) const {
		if (   target == agent
			|| target == NULL
			|| target->isVehicleObject()
			|| target->hasRidingCreature()
			|| target->getPvpStatusBitmask() == CreatureFlag::NONE
			|| target->isDead()
			|| target->isIncapacitated()
			|| target->isInvisible()
			|| agent->isCamouflaged(target)
			|| !agent->isAttackableBy(target)
			|| !target->isAttackableBy(agent) )
			return true;

		SceneObject* agentRoot = agent->getRootParent().get();
		SceneObject* targetRoot = target->getRootParent().get();

		uint64 agentParentID = agentRoot != NULL && agentRoot->isBuildingObject() ?
									agentRoot->getObjectID() : 0;
		uint64 targetParentID = targetRoot != NULL && targetRoot->isBuildingObject() ?
									targetRoot->getObjectID() : 0;

		if (agentParentID != targetParentID)
			return true;

		uint32 agentFaction = agent->getFaction();
		uint32 targetFaction = target->getFaction();

		if ((agentFaction != 0 && targetFaction == 0) ||
			(agentFaction == 0 && targetFaction != 0) )
			return true;

		return false;
	}
};

}
}
}
}
}
}
}

#endif // LOOKFORTARGET_H_
