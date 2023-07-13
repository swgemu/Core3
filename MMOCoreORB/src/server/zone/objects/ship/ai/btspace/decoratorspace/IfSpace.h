#ifndef IFSPACE_H_
#define IFSPACE_H_

#include "server/zone/objects/ship/ai/btspace/decoratorspace/DecoratorSpace.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace decoratorspace {

class IfSpace : public DecoratorSpace {
public:
	IfSpace(const String& className, const uint32 id, const LuaObject& args) : DecoratorSpace(className, id, args) {
	}

	IfSpace(const IfSpace& b) : DecoratorSpace(b) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		assert(child != nullptr);

		return child->doAction(agent);
	}
};

} // namespace decoratorspace
} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // IFSPACE_H_
