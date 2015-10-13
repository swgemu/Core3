#ifndef SIMPLEACTIONS_H_
#define SIMPLEACTIONS_H_

#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/creature/ai/bt/BlackboardData.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

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

class StageWeapon : public Behavior {
public:
    StageWeapon(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString), weaponType(AiAgent::WEAPONDEFAULT) {}

    StageWeapon(const StageWeapon& a)
        : Behavior(a), weaponType(a.weaponType) {}

    StageWeapon& operator=(const StageWeapon& a) {
        if (this == &a)
            return *this;
        Behavior::operator=(a);
        weaponType = a.weaponType;
        return *this;
    }

    void parseArgs(const String& argString) {
        VectorMap<String, String> args = Behavior::fillArgs(argString);
        weaponType = getArg<uint32>()(args.get("weaponType"));
    }

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        // set selected weapon here. to avoid multiple weapon sets (which are heavy)
        // do some lightweight selection setting first. This means that the btree
        // designer must actually equip the weapon after the final selection has been made
        agent->writeBlackboard("stagedWeapon", BlackboardData(weaponType));
        return SUCCESS;
    }

private:
    uint32 weaponType;
};

class EquipStagedWeapon : public Behavior {
public:
    EquipStagedWeapon(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString) {}

    EquipStagedWeapon(const EquipStagedWeapon& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        if (!agent->peekBlackboard("stagedWeapon"))
            return FAILURE;

        uint32 weaponType = agent->readBlackboard("stagedWeapon").get<uint32>();
        agent->setWeapon(weaponType);
        return SUCCESS;
    }
};

class EraseBlackboard : public Behavior {
public:
    EraseBlackboard(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString), param("") {}

    EraseBlackboard(const EraseBlackboard& a)
        : Behavior(a), param(a.param) {}

    EraseBlackboard& operator=(const EraseBlackboard& a) {
        if (this == &a)
            return *this;
        Behavior::operator=(a);
        param = a.param;
        return *this;
    }

    void parseArgs(const String& argString) {
        VectorMap<String, String> args = Behavior::fillArgs(argString);
        param = args.get("param");
    }

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        agent->eraseBlackboard(param);
        return SUCCESS;
    }

private:
    String param;
};

}
}
}
}
}
}
}

#endif // SIMPLEACTIONS_H_
