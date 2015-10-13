#ifndef SIMPLEACTIONS_H_
#define SIMPLEACTIONS_H_

#include "server/zone/objects/creature/ai/bt/Behavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace leaf {
    
class GeneratePatrol : public Behavior {
public:
    GeneratePatrol(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString), numPoints(0), distFromHome(0.0) {}

    GeneratePatrol(const GeneratePatrol& a)
        : Behavior(a), numPoints(a.numPoints), distFromHome(a.distFromHome) {}

    GeneratePatrol& operator=(const GeneratePatrol& a) {
        if (this == &a)
            return *this;
        Behavior::operator=(a);
        numPoints = a.numPoints;
        distFromHome = a.distFromHome;
        return *this;
    }
    
    void parseArgs(const String& argString) {
        VectorMap<String, String> args = Behavior::fillArgs(argString);
        numPoints = getArg<int>()(args.get("numPoints"));
        distFromHome = getArg<float>()(args.get("distFromHome"));
    }
    
    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        return agent->generatePatrol(numPoints, distFromHome) ? SUCCESS : FAILURE;
    }

private:
    int numPoints;
    float distFromHome;
};


class ExitCombat : public Behavior {
public:
    ExitCombat(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString), clearDefenders(false) {}

    ExitCombat(const ExitCombat& a)
        : Behavior(a), clearDefenders(a.clearDefenders) {}
    
    ExitCombat& operator=(const ExitCombat& a) {
        if (this == &a)
            return *this;
        Behavior::operator=(a);
        clearDefenders = a.clearDefenders;
        return *this;
    }

    void parseArgs(const String& argString) {
        VectorMap<String, String> args = Behavior::fillArgs(argString);
        clearDefenders = getArg<int>()(args.get("clearDefenders"));
    }
    
    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        agent->clearCombatState(clearDefenders);
        agent->setOblivious();
        
        return !agent->isInCombat() && agent->getFollowState() == AiAgent::OBLIVIOUS ?
                SUCCESS : FAILURE;
    }

private:
    bool clearDefenders;
};

}
}
}
}
}
}
}

#endif // SIMPLEACTIONS_H_