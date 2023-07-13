#ifndef ALWAYSFAIL_H_
#define ALWAYSFAIL_H_

#include "server/zone/objects/ship/ai/bt/decorator/Decorator.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace bt {
namespace decorator {

class AlwaysFail : public Decorator {
public:
	AlwaysFail(const String& className, const uint32 id, const LuaObject& args) : Decorator(className, id, args) {
	}

	AlwaysFail(const AlwaysFail& b) : Decorator(b) {
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		assert(child != nullptr);

		Behavior::Status result = child->doAction(agent);

		if (result == RUNNING)
			agent->clearRunningChain();

		if (result == SUCCESS || result == FAILURE || result == RUNNING)
			return FAILURE;

		return result;
	}
};

} // namespace decorator
} // namespace bt
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // ALWAYSFAIL_H_
