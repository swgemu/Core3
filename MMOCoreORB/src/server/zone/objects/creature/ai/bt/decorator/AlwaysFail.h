#ifndef ALWAYSFAIL_H_ 
#define ALWAYSFAIL_H_

#include "server/zone/objects/creature/ai/bt/decorator/Decorator.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace decorator {

class AlwaysFail : public Decorator {
public:
    AlwaysFail(const String& className, const uint32 id, const String& argString = "")
        : Decorator(className, id, argString) {}

    AlwaysFail(const AlwaysFail& b)
        : Decorator(b) {}

    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
        assert(child != NULL);
        
        Behavior::Status result = child->doAction(agent);
        
        if (result == SUCCESS || result == FAILURE)
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

#endif // ALWAYSFAIL_H_