#ifndef TREE_SOCKET_H_
#define TREE_SOCKET_H_

#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/creature/ai/bt/BehaviorTreeSlot.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class TreeSocket : public Behavior {
protected:
	BehaviorTreeSlot slotID;

public:
	TreeSocket(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args), slotID(BehaviorTreeSlot::NONE) {
		parseArgs(args);
	}

	TreeSocket(const TreeSocket& b) : Behavior(b), slotID(b.slotID) {
	}

	TreeSocket& operator=(const TreeSocket& b) {
		if (this == &b)
			return *this;

		Behavior::operator=(b);
		slotID = b.slotID;
		return *this;
	}

	bool isSocket() const {
		return true;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		const Behavior* child = agent->getBehaviorTree(slotID);

		if (child == nullptr)
			return FAILURE;

		return child->doAction(agent);
	}

	void parseArgs(const LuaObject& args) {
		slotID = getArg<BehaviorTreeSlot>()(args, "slot");
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << getBehaviorTreeSlotName(slotID);

		return msg.toString();
	}

	const BehaviorTreeSlot& getSlotID() const {
		return slotID;
	}
};

} // namespace bt
} // namespace ai
} // namespace creature
} // namespace objects
} // namespace zone
} // namespace server

#endif // TREE_SOCKET_H_
