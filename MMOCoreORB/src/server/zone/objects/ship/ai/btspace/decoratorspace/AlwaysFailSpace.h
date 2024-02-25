#ifndef ALWAYSFAILSPACE_H_
#define ALWAYSFAILSPACE_H_

#include "server/zone/objects/ship/ai/btspace/decoratorspace/DecoratorSpace.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace decoratorspace {

class AlwaysFailSpace : public DecoratorSpace {
public:
	AlwaysFailSpace(const String& className, const uint32 id, const LuaObject& args) : DecoratorSpace(className, id, args) {
	}

	AlwaysFailSpace(const AlwaysFailSpace& b) : DecoratorSpace(b) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		assert(child != nullptr);

		BehaviorSpace::Status result = child->doAction(agent);

		if (result == RUNNING)
			agent->clearRunningChain();

		if (result == SUCCESS || result == FAILURE || result == RUNNING)
			return FAILURE;

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

#endif // ALWAYSFAILSPACE_H_
