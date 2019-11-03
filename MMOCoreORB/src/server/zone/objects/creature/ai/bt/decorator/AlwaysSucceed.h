#ifndef ALWAYSSUCCEED_H_ 
#define ALWAYSSUCCEED_H_

#include "server/zone/objects/creature/ai/bt/decorator/Decorator.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace decorator {

class AlwaysSucceed: public Decorator {
public:
	AlwaysSucceed(const String& className, const uint32 id, const LuaObject& args)
			: Decorator(className, id, args) {
	}

	AlwaysSucceed(const AlwaysSucceed& b)
			: Decorator(b) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		assert(child != nullptr);

		Behavior::Status result = child->doAction(agent);

		if (result == RUNNING)
			agent->clearRunningChain();

		if (result == SUCCESS || result == FAILURE || result == RUNNING)
			return SUCCESS;

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

#endif // ALWAYSSUCCEED_H_
