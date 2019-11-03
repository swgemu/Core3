#ifndef UNTILFAILURE_H_
#define UNTILFAILURE_H_

#include "server/zone/objects/creature/ai/bt/decorator/Decorator.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace decorator {

class UntilFailure : public Decorator {
public:
	UntilFailure(const String& className, const uint32 id, const LuaObject& args)
			: Decorator(className, id, args) {
	}

	UntilFailure(const UntilFailure& b)
			: Decorator(b) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		assert(child != nullptr);

		Behavior::Status result = child->doAction(agent);
		while (result == SUCCESS) {
			result = child->doAction(agent);
		}

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

#endif // UNTILFAILURE_H_
