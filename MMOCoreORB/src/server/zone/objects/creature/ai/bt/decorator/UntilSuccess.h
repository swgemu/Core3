#ifndef UNTILSUCCESS_H_
#define UNTILSUCCESS_H_

#include "server/zone/objects/creature/ai/bt/decorator/Decorator.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace decorator {

class UntilSuccess : public Decorator {
public:
	UntilSuccess(const String& className, const uint32 id, const LuaObject& args)
			: Decorator(className, id, args) {
	}

	UntilSuccess(const UntilSuccess& b)
			: Decorator(b) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		assert(child != nullptr);

		Behavior::Status result = child->doAction(agent);
		while (result == FAILURE) {
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

#endif // UNTILSUCCESS_H_
