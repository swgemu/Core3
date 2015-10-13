#ifndef CHECKS_H_
#define CHECKS_H_

#include "server/zone/objects/creature/ai/bt/Behavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace leaf {

// helper enum to ensure we have exactly one template realization per check typedef
enum CheckType {
    CHECK_POSTURE,
    CHECK_DESTINATION,
    CHECK_FOLLOWSTATE,
    CHECK_HASFOLLOW,
    CHECK_FOLLOWHASSTATE,
    CHECK_FOLLOWINRANGE,
    CHECK_FOLLOWATTACKABLE,
    CHECK_FOLLOWAGGRESSION,
    CHECK_FOLLOWDEAD,
    CHECK_FOLLOWINCAPPED,
    CHECK_FOLLOWDESTROYED,
    CHECK_RANDOMLEVEL,
    CHECK_LASTCOMMAND
};

// template class to reduce repeated code. Do this instead of inheritance so we
// don't have to retype the ctors (which would be exactly the same)
template <typename val_type, CheckType C>
class _Check : public Behavior {
public:
    _Check(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString), checkVar((val_type)(0)) {}

    _Check(const _Check& c)
        : Behavior(c), checkVar(c.checkVar) {}

    _Check& operator=(const _Check& c) {
        if (this == &c)
            return *this;
        Behavior::operator=(c);
        checkVar = c.checkVar;
        return *this;
    }
    
    void parseArgs(const String& argString) {
        VectorMap<String, String> args = Behavior::fillArgs(argString);
        checkVar = getArg<val_type>()(args.get("condition"));
    }
    
    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        assert(agent != NULL);

        return check(agent) ? SUCCESS : FAILURE;
    }
    
    bool check(AiAgent*) const;

private:
    val_type checkVar;
};

typedef _Check<uint32, CHECK_POSTURE> CheckPosture;
template <> bool CheckPosture::check(AiAgent* agent) const;

typedef _Check<int32, CHECK_DESTINATION> CheckDestination;
template <> bool CheckDestination::check(AiAgent* agent) const;

typedef _Check<int32, CHECK_FOLLOWSTATE> CheckFollowState;
template <> bool CheckFollowState::check(AiAgent* agent) const;

typedef _Check<int32, CHECK_HASFOLLOW> CheckHasFollow;
template <> bool CheckHasFollow::check(AiAgent* agent) const;

typedef _Check<uint64, CHECK_FOLLOWHASSTATE> CheckFollowHasState;
template <> bool CheckFollowHasState::check(AiAgent* agent) const;

typedef _Check<float, CHECK_FOLLOWINRANGE> CheckFollowInRange;
template <> bool CheckFollowInRange::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_FOLLOWATTACKABLE> CheckFollowAttackable;
template <> bool CheckFollowAttackable::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_FOLLOWAGGRESSION> CheckFollowAggression;
template <> bool CheckFollowAggression::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_FOLLOWDEAD> CheckFollowDead;
template <> bool CheckFollowDead::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_FOLLOWINCAPPED> CheckFollowIncapped;
template <> bool CheckFollowIncapped::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_FOLLOWDESTROYED> CheckFollowDestroyed;
template <> bool CheckFollowDestroyed::check(AiAgent* agent) const;

typedef _Check<uint32, CHECK_RANDOMLEVEL> CheckRandomLevel;
template <> bool CheckRandomLevel::check(AiAgent* agent) const;

typedef _Check<uint32, CHECK_LASTCOMMAND> CheckLastCommand;
template <> bool CheckLastCommand::check(AiAgent* agent) const;

}
}
}
}
}
}
}

#endif // CHECKS_H_