#ifndef ALWAYSSUCCEED_H_
#define ALWAYSSUCCEED_H_

#include "server/zone/objects/ship/ai/bt/decorator/Decorator.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace bt {
namespace decorator {

class AlwaysSucceed : public Decorator {
public:
	AlwaysSucceed(const String& className, const uint32 id, const LuaObject& args) : Decorator(className, id, args) {
	}

	AlwaysSucceed(const AlwaysSucceed& b) : Decorator(b) {
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		assert(child != nullptr);

		Behavior::Status result = child->doAction(agent);

		if (result == RUNNING)
			agent->clearRunningChain();

		if (result == SUCCESS || result == FAILURE || result == RUNNING)
			return SUCCESS;

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

#endif // ALWAYSSUCCEED_H_
