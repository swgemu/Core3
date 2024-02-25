#ifndef TREESOCKETSPACE_H_
#define TREESOCKETSPACE_H_

#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"
#include "server/zone/objects/ship/ai/btspace/BehaviorTreeSlotSpace.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {

class TreeSocketSpace : public BehaviorSpace {
protected:
	BehaviorTreeSlotSpace slotID;

public:
	TreeSocketSpace(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args), slotID(BehaviorTreeSlotSpace::NONESPACE) {
		parseArgs(args);
	}

	TreeSocketSpace(const TreeSocketSpace& b) : BehaviorSpace(b), slotID(b.slotID) {
	}

	TreeSocketSpace& operator=(const TreeSocketSpace& b) {
		if (this == &b)
			return *this;

		BehaviorSpace::operator=(b);
		slotID = b.slotID;
		return *this;
	}

	bool isSocketSpace() const {
		return true;
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		const BehaviorSpace* child = agent->getBehaviorTreeSpace(slotID);

		if (child == nullptr)
			return FAILURE;

		return child->doAction(agent);
	}

	void parseArgs(const LuaObject& args) {
		slotID = getArg<BehaviorTreeSlotSpace>()(args, "slot");
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << getBehaviorTreeSlotName(slotID);

		return msg.toString();
	}

	const BehaviorTreeSlotSpace& getSlotID() const {
		return slotID;
	}
};

} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // TREESOCKETSPACE_H_
