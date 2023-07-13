#ifndef NOT_H_
#define NOT_H_

#include "server/zone/objects/creature/ai/bt/decorator/Decorator.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace bt {
namespace decorator {

class Not : public Decorator {
public:
	Not(const String& className, const uint32 id, const LuaObject& args) : Decorator(className, id, args) {
	}

	Not(const Not& b) : Decorator(b) {
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		assert(child != nullptr);

		Behavior::Status result = child->doAction(agent);

		if (result == FAILURE)
			return SUCCESS;

		if (result == SUCCESS)
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

#endif // NOT_H_
