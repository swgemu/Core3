#ifndef NOT_H_
#define NOT_H_

#include "server/zone/objects/creature/ai/bt/decorator/Decorator.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace decorator {

class Not : public Decorator 
{
public:
    Not(const String& className, const uint32 id, const String& argString = "")
        : Decorator(className, id, argString) {}
    
    Not(const Not& b)
        : Decorator(b) {}
    
    ~Not() {}
    
    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        assert(child != NULL);

        Behavior::Status result = child->doAction(agent);

        if (result == FAILURE)
            return SUCCESS;

        if (result == SUCCESS)
            return FAILURE;

       return result; 
    }
};

}
}
}
}
}
}
}

#endif // NOT_H_
