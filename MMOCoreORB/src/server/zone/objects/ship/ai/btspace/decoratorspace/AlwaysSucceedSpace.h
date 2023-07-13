#ifndef ALWAYSSUCCEEDSPACE_H_
#define ALWAYSSUCCEEDSPACE_H_

#include "server/zone/objects/ship/ai/btspace/decoratorspace/DecoratorSpace.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace decoratorspace {

class AlwaysSucceedSpace : public DecoratorSpace {
public:
	AlwaysSucceedSpace(const String& className, const uint32 id, const LuaObject& args) : DecoratorSpace(className, id, args) {
	}

	AlwaysSucceedSpace(const AlwaysSucceedSpace& b) : DecoratorSpace(b) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		assert(child != nullptr);

		BehaviorSpace::Status result = child->doAction(agent);

		if (result == RUNNING)
			agent->clearRunningChain();

		if (result == SUCCESS || result == FAILURE || result == RUNNING)
			return SUCCESS;

		return result;
	}
};

} // namespace decoratorspace
} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // ALWAYSSUCCEEDSPACE_H_
