#ifndef FOLLOWACTIONS_H_
#define FOLLOWACTIONS_H_

#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/creature/ai/bt/BlackboardData.h"

#include "server/zone/objects/tangible/threat/ThreatMap.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace leaf {

class GetFollowFromThreatMap : public Behavior {
public:
    GetFollowFromThreatMap(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString) {}

    GetFollowFromThreatMap(const GetFollowFromThreatMap& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        agent->storeFollowObject();
        agent->setFollowObject(agent->getThreatMap()->getHighestThreatCreature());
        
        return agent->getFollowObject() != NULL ? SUCCESS : FAILURE;
    }
};

class GetFollowFromDefenders : public Behavior {
public:
    GetFollowFromDefenders(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString) {}

    GetFollowFromDefenders(const GetFollowFromDefenders& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        agent->storeFollowObject();
        agent->setFollowObject(agent->getMainDefender());
        
        return agent->getFollowObject() != NULL ? SUCCESS : FAILURE;
    }
};

class RestoreFollow : public Behavior {
public:
    RestoreFollow(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString) {}

    RestoreFollow(const RestoreFollow& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        agent->restoreFollowObject();
        return agent->getFollowObject() != NULL ? SUCCESS : FAILURE;
    }
};

class DropFollowFromDefenders : public Behavior {
public:
    DropFollowFromDefenders(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString) {}

    DropFollowFromDefenders(const DropFollowFromDefenders& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
	    ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	    agent->removeDefender(followCopy);
	    
        return agent->hasDefender(followCopy) ? FAILURE : SUCCESS;
    }
};

class SetDefenderFromFollow : public Behavior {
public:
    SetDefenderFromFollow(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString) {}

    SetDefenderFromFollow(const SetDefenderFromFollow& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
	    ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
	    agent->setDefender(followCopy);
	    
        return agent->hasDefender(followCopy) ? SUCCESS : FAILURE;
    }
};

class UpdateRangeToFollow : public Behavior {
public:
    UpdateRangeToFollow(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString) {}

    UpdateRangeToFollow(const UpdateRangeToFollow& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
        if (followCopy == NULL)
            return FAILURE;

        float dist = agent->getDistanceTo(followCopy) - followCopy->getTemplateRadius() - agent->getTemplateRadius();
        agent->writeBlackboard("followRange", BlackboardData(dist));

        return SUCCESS;
    }
};

}
}
}
}
}
}
}

#endif // FOLLOWACTIONS_H_
