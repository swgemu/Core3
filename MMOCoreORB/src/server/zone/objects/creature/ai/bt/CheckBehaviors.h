#ifndef CHECKBEHAVIORS_H_
#define CHECKBEHAVIORS_H_

#include "Behavior.h"
#include "server/zone/objects/creature/CreaturePosture.h"
#include "server/zone/managers/creature/PetManager.h"

// helper macro to re-implement all the necessary constructors
// this is unneccesary in c++11 with access to a smarter using,
// but since we can't guarantee c++11, this will do.
// in the future, if we guarantee c++11, all we need to do is 
// 'using Behavior::Behavior'
#define _CHECK(class_name, check) \
class class_name : public Behavior \
{ \
    class_name(AiAgent* _agent, const String& className) \
        : Behavior(_agent, className) {} \
    class_name(const class_name& c) \
        : Behavior(c) {} \
    class_name& operator=(const class_name& c) { \
        Behavior::operator=(c); \
        return *this; \
    } \
    bool checkConditions() { \
        Reference<AiAgent*> strongRef = agent.get(); \
        return strongRef && strongRef->##check; \
    } \
};

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
 
_CHECK(CheckUpright, getPosture() == CreaturePosture::UPRIGHT)
_CHECK(CheckOblivious, getFollowState() == AiAgent::OBLIVIOUS)
_CHECK(CheckDestination, setDestination() > 0)
_CHECK(CheckPetAttack, getLastCommand() == PetManager::ATTACK)
_CHECK(CheckPetGuard, getLastCommand() == PetManager::GUARD)
_CHECK(CheckPetSpecialAttack1, getLastCommand() == PetManager::SPECIAL_ATTACK1)
_CHECK(CheckPetSpecialAttack2, getLastCommand() == PetManager::SPECIAL_ATTACK2)
_CHECK(CheckPetPatrol, getLastCommand() == PetManager::PATROL)

}
}
}
}
}
}

#endif // CHECKBEHAVIORS_H_