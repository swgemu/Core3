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
    GetFollowFromThreatMap(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

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
    GetFollowFromDefenders(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

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
    RestoreFollow(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

    RestoreFollow(const RestoreFollow& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        agent->restoreFollowObject();
        return agent->getFollowObject() != NULL ? SUCCESS : FAILURE;
    }
};

class DropFollowFromDefenders : public Behavior {
public:
    DropFollowFromDefenders(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

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
    SetDefenderFromFollow(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

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
    UpdateRangeToFollow(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

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

class SetFollowState : public Behavior {
public:
	SetFollowState(const String& className, const uint32 id, const LuaObject& args)
		: Behavior (className, id, args), state(0) {
		parseArgs(args);
	}

	SetFollowState(const SetFollowState& a)
		: Behavior(a), state(a.state) {}

	SetFollowState& operator=(const SetFollowState& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		state = a.state;
		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
        if (followCopy == NULL)
            return FAILURE;
		
		switch (state) {
		case AiAgent::OBLIVIOUS:
			agent->setOblivious();
			break;
		case AiAgent::WATCHING:
			agent->setWatchObject(followCopy);
			break;
		case AiAgent::STALKING:
			agent->setStalkObject(followCopy);
			break;
		case AiAgent::FOLLOWING:
			agent->setFollowObject(followCopy);
			break;
		case AiAgent::PATROLLING:
		case AiAgent::FLEEING:
		case AiAgent::LEASHING:
		default:
			agent->setFollowState(state);
			break;
		};

        return SUCCESS;
	}

    void parseArgs(const LuaObject& args) {
        state = getArg<int32>()(args, "state");
    }

private:
	uint32 state;
};

class CalculateAggroMod : public Behavior {
public:
	CalculateAggroMod(const String& className, const uint32 id, const LuaObject& args)
		: Behavior(className, id, args) {}
	
	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
		if (followCopy == NULL || !followCopy->isCreatureObject())
			return FAILURE;

		CreatureObject* followCreo = followCopy->asCreatureObject();

		float mod = MAX(0.04f, MIN(1 - (followCreo->getLevel() - agent->getLevel())/20.f, 1.2f));
		agent->writeBlackboard("aggroMod", mod);

		return agent->peekBlackboard("aggroMod") ? SUCCESS : FAILURE;
	}
};

class RunAway : public Behavior {
public:
	RunAway(const String& className, const uint32 id, const LuaObject& args)
		: Behavior(className, id, args), dist(0.f) {
		parseArgs(args);
	}

	RunAway(const RunAway& b)
		: Behavior(b), dist(b.dist) {}
	
	RunAway& operator=(const RunAway& b) {
		if (this == &b)
			return *this;
		Behavior::operator=(b);
		dist = b.dist;
		return *this;
	}
	
	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
		if (followCopy == NULL || !followCopy->isCreatureObject())
			return FAILURE;

		float aggroMod = 1.f;
		if (agent->peekBlackboard("aggroMod"))
			aggroMod = agent->readBlackboard("aggroMod").get<float>();

		int radius = agent->getAggroRadius();
		if (radius == 0) radius = AiAgent::DEFAULTAGGRORADIUS;

		agent->runAway(followCopy->asCreatureObject(), dist - radius*aggroMod);
		return SUCCESS;
	}

	void parseArgs(const LuaObject& args) {
		dist = getArg<float>()(args, "dist");
	}

private:
	float dist;
};

}
}
}
}
}
}
}

#endif // FOLLOWACTIONS_H_
