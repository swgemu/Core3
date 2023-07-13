#ifndef UNTILSUCCESSSPACE_H_
#define UNTILSUCCESSSPACE_H_

#include "server/zone/objects/ship/ai/btspace/decoratorspace/DecoratorSpace.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace decoratorspace {

class UntilSuccessSpace : public DecoratorSpace {
public:
	UntilSuccessSpace(const String& className, const uint32 id, const LuaObject& args) : DecoratorSpace(className, id, args) {
	}

	UntilSuccessSpace(const UntilSuccessSpace& b) : DecoratorSpace(b) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		assert(child != nullptr);

		BehaviorSpace::Status result = child->doAction(agent);

		while (result == FAILURE) {
			result = child->doAction(agent);
		}

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

#endif // UNTILSUCCESSSPACE_H_
