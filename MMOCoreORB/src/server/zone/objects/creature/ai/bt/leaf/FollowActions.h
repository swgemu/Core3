#ifndef FOLLOWACTIONS_H_
#define FOLLOWACTIONS_H_

#include "server/zone/objects/creature/ai/AiAgent.h"
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

class GetProspectFromThreatMap : public Behavior {
public:
    GetProspectFromThreatMap(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

    GetProspectFromThreatMap(const GetProspectFromThreatMap& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> tar = agent->getThreatMap()->getHighestThreatCreature();
		if (tar == NULL)
			return FAILURE;

		agent->writeBlackboard("targetProspect", tar);
        
        return SUCCESS;
    }
};

class GetProspectFromDefenders : public Behavior {
public:
    GetProspectFromDefenders(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

    GetProspectFromDefenders(const GetProspectFromDefenders& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> tar = agent->getMainDefender();
		if (tar == NULL)
			return FAILURE;

		agent->writeBlackboard("targetProspect", tar);
        
        return SUCCESS;
    }
};

class GetProspectFromTarget : public Behavior {
public:
    GetProspectFromTarget(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

    GetProspectFromTarget(const GetProspectFromTarget& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> tar = agent->getTargetFromTargetsDefenders();
		if (tar == NULL)
			return FAILURE;

		agent->writeBlackboard("targetProspect", tar);
        
        return SUCCESS;
    }
};

class GetProspectFromCommand : public Behavior {
public:
    GetProspectFromCommand(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

    GetProspectFromCommand(const GetProspectFromCommand& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->isPet())
			return FAILURE;

		Reference<PetControlDevice*> cd = agent->getControlDevice().castTo<PetControlDevice*>();
		if (cd == NULL)
			return FAILURE;

		ManagedReference<SceneObject*> tar = cd->getLastCommandTarget().get();
		if (tar == NULL)
			return FAILURE;

		agent->writeBlackboard("targetProspect", tar);
        
        return SUCCESS;
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

class DropProspectFromDefenders : public Behavior {
public:
    DropProspectFromDefenders(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

    DropProspectFromDefenders(const DropProspectFromDefenders& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("targetProspect"))
			return SUCCESS;

	    ManagedReference<SceneObject*> tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();
		if (tar == NULL)
			return SUCCESS;

	    agent->removeDefender(tar);
	    
        return agent->hasDefender(tar) ? FAILURE : SUCCESS;
    }
};

class SetDefenderFromProspect : public Behavior {
public:
    SetDefenderFromProspect(const String& className, const uint32 id, const LuaObject& args)
        : Behavior(className, id, args) {}

    SetDefenderFromProspect(const SetDefenderFromProspect& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("targetProspect"))
			return FAILURE;

	    ManagedReference<SceneObject*> tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();
		if (tar == NULL)
			return FAILURE;

		// note: this also sets the follow object (and sets the state to FOLLOWING)
	    agent->setDefender(tar);
	    
        return agent->getMainDefender() == tar ? SUCCESS : FAILURE;
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
	    ManagedReference<SceneObject*> tar = NULL;
		if (agent->peekBlackboard("targetProspect"))
			tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

        if (tar == NULL && 
			(state == AiAgent::WATCHING || state == AiAgent::STALKING || state == AiAgent::FOLLOWING))
            return FAILURE;
		
		switch (state) {
		case AiAgent::OBLIVIOUS:
			agent->setOblivious();
			break;
		case AiAgent::WATCHING:
			agent->setWatchObject(tar);
			break;
		case AiAgent::STALKING:
			agent->setStalkObject(tar);
			break;
		case AiAgent::FOLLOWING:
			agent->setFollowObject(tar);
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
	    ManagedReference<SceneObject*> tar = NULL;
		if (agent->peekBlackboard("targetProspect"))
			tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

		if (tar == NULL || !tar->isCreatureObject())
			return FAILURE;

		CreatureObject* tarCreo = tar->asCreatureObject();

		float mod = MAX(0.04f, MIN(1 - (tarCreo->getLevel() - agent->getLevel())/20.f, 1.2f));
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
	    ManagedReference<SceneObject*> tar = NULL;
		if (agent->peekBlackboard("targetProspect"))
			tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

		if (tar == NULL || !tar->isCreatureObject())
			return FAILURE;

		float aggroMod = 1.f;
		if (agent->peekBlackboard("aggroMod"))
			aggroMod = agent->readBlackboard("aggroMod").get<float>();

		int radius = agent->getAggroRadius();
		if (radius == 0) radius = AiAgent::DEFAULTAGGRORADIUS;

		agent->runAway(tar->asCreatureObject(), dist - radius*aggroMod);
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
