#ifndef LOOKFORTARGETSPACE_H_
#define LOOKFORTARGETSPACE_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/ship/ai/btspace/decoratorspace/DecoratorSpace.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace decoratorspace {

class LookForTargetSpace : public DecoratorSpace {
public:
	LookForTargetSpace(const String& className, const uint32 id, const LuaObject& args) : DecoratorSpace(className, id, args) {
	}

	LookForTargetSpace(const LookForTargetSpace& b) : DecoratorSpace(b) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		// TODO: Create functiont to find targets nearby

		return FAILURE;
	}

	bool isInvalidTarget(CreatureObject* target, ShipAiAgent* agent) const {
		if (target == nullptr || target->getObjectID() == agent->getObjectID())
			return true;

		return false;
	}
};

} // namespace decoratorspace
} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // LOOKFORTARGETSPACE_H_
