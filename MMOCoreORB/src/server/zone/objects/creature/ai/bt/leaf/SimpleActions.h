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
        : Behavior(className, id, argString), numPoints(0), distFromHome(0.0) {
		parseArgs(argString);
	}

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
        : Behavior(className, id, argString), clearDefenders(false) {
		parseArgs(argString);
	}

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

class WriteBlackboard : public Behavior {
public:
    WriteBlackboard(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString) {
		data.setNoDuplicateInsertPlan();
		parseArgs(argString);
	}

    WriteBlackboard(const WriteBlackboard& a)
        : Behavior(a), data(a.data) {}

    WriteBlackboard& operator=(const WriteBlackboard& a) {
        if (this == &a)
            return *this;
        Behavior::operator=(a);
        data = a.data;
        return *this;
    }

    void parseArgs(const String& argString) {
        VectorMap<String, String> args = Behavior::fillArgs(argString);

		for (int i = 0; i < args.size(); ++i) {
			auto entry = args.SortedVector<VectorMapEntry<String, String> >::get(i);
			data.put(entry.getKey(), entry.getValue().hashCode());
		}
    }

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		for (int i = 0; i < data.size(); ++i) {
			auto entry = data.SortedVector<VectorMapEntry<String, uint32> >::get(i);
			agent->writeBlackboard(entry.getKey(), entry.getValue());
		}

        return SUCCESS;
    }

private:
    VectorMap<String, uint32> data;
};

class EraseBlackboard : public Behavior {
public:
    EraseBlackboard(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString), param("") {
		parseArgs(argString);
	}

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

class SelectAttack : public Behavior {
public:
    SelectAttack(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString), attackNum(-1) {
		parseArgs(argString);
	}

    SelectAttack(const SelectAttack& a)
        : Behavior(a), attackNum(a.attackNum) {}

    SelectAttack& operator=(const SelectAttack& a) {
        if (this == &a)
            return *this;
        Behavior::operator=(a);
        attackNum = a.attackNum;
        return *this;
    }

    void parseArgs(const String& argString) {
        VectorMap<String, String> args = Behavior::fillArgs(argString);
		args.setNullValue("-1");
        attackNum = getArg<int>()(args.get("attackNum"));
    }

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (agent->peekBlackboard("attackType")) {
			if (agent->readBlackboard("attackType").get<uint32>() == static_cast<uint32>(DataVal::DEFAULT))
				return agent->selectDefaultAttack() ? SUCCESS : FAILURE;
			if (agent->readBlackboard("attackType").get<uint32>() == static_cast<uint32>(DataVal::RANDOM))
				return agent->selectSpecialAttack(-1) ? SUCCESS : FAILURE;
		}

        return agent->selectSpecialAttack(attackNum) ? SUCCESS : FAILURE;
    }

private:
    int attackNum;
};

class FindNextPosition : public Behavior {
public:
    FindNextPosition(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString) {}

    FindNextPosition(const FindNextPosition& a)
        : Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		DataVal mode = DataVal::WALK;
        if (agent->peekBlackboard("moveMode"))
            mode = static_cast<DataVal>(agent->readBlackboard("moveMode").get<uint32>());

        return agent->findNextPosition(agent->getMaxDistance(), mode == DataVal::WALK) ? SUCCESS : FAILURE;
    }
};

class Leash : public Behavior {
public:
    Leash(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString) {}

    Leash(const Leash& a)
        :Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        agent->leash();
        return SUCCESS;
    }
};

class CompleteMove : public Behavior {
public:
    CompleteMove(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString) {}

    CompleteMove(const CompleteMove& a)
        :Behavior(a) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        return agent->completeMove() ? SUCCESS : FAILURE;
    }
};

class Wait : public Behavior {
public:
    Wait(const String& className, const uint32 id, const String& argString = "")
        : Behavior(className, id, argString), duration(-1.f) {
		parseArgs(argString);
	}

    Wait(const Wait& a)
        : Behavior(a), duration(a.duration) {}

    Wait& operator=(const Wait& a) {
        if (this == &a)
            return *this;
        Behavior::operator=(a);
        duration = a.duration;
        return *this;
    }

    void parseArgs(const String& argString) {
        VectorMap<String, String> args = Behavior::fillArgs(argString);
        duration = getArg<float>()(args.get("duration"));
    }

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        agent->setWait((int)(duration*1000));

        return RUNNING;
    }

private:
    float duration;
};

}
}
}
}
}
}
}

#endif // SIMPLEACTIONS_H_
