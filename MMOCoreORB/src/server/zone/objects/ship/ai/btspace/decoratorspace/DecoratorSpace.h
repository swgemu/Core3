#ifndef DECORATORSPACE_H_
#define DECORATORSPACE_H_

#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace decoratorspace {

class DecoratorSpace : public BehaviorSpace {
protected:
	Reference<BehaviorSpace*> child;

public:
	DecoratorSpace(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	DecoratorSpace(const DecoratorSpace& b) : BehaviorSpace(b) {
		child = b.child;
	}

	DecoratorSpace& operator=(const DecoratorSpace& b) {
		if (this == &b)
			return *this;

		BehaviorSpace::operator=(b);
		child = b.child;

		return *this;
	}

	virtual ~DecoratorSpace() {
	}

	bool isDecoratorSpace() const {
		return true;
	}

	bool hasChild(BehaviorSpace* c) const {
		return child == c;
	}

	BehaviorSpace* getChild(uint32 cID) const {
		if (child->getID() == cID)
			return child;

		return NULL;
	}

	Vector<const BehaviorSpace*> getRecursiveChildList() const {
		Vector<const BehaviorSpace*> retVal;
		retVal.add(this);

		retVal.addAll(child->getRecursiveChildList());

		return retVal;
	}

	virtual void setChild(Reference<BehaviorSpace*> newChild) {
		assert(child != this);

		child = newChild;
	}

	String print() const {
		StringBuffer stream;
		stream << BehaviorSpace::print() << "[";
		if (child != nullptr)
			stream << child->print();
		stream << "]";
		return stream.toString();
	}

	virtual bool checkConditions(ShipAiAgent* agent) const {
		if (child == nullptr)
			return false;

		if (!BehaviorSpace::checkConditions(agent)) {
			return true;
		}

		return true;
	}

	BehaviorSpace::Status doAction(ShipAiAgent* agent) const {
#ifdef DEBUG_SHIP_AI
		if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true) {
			StringBuffer msg;
			msg << "0x" << hex << id << " " << print().toCharArray();

			agent->info(true) << agent->getDisplayedName() << " ID: " << agent->getObjectID() << " - " << msg.toString();
		}
#endif // DEBUG_SHIP_AI

		if (!checkConditions(agent)) {
			return INVALID;
		}

		if (!agent->isRunningBehavior(id))
			this->start(agent);
		else
			agent->popRunningChain();

		BehaviorSpace::Status result = this->execute(agent);

#ifdef DEBUG_SHIP_AI
		if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true) {
			StringBuffer msg;

			msg << "0x" << hex << id << " " << print() << " result: " << result;
			agent->info(true) << agent->getDisplayedName() << " ID: " << agent->getObjectID() << " - " << msg.toString();
		}
#endif // DEBUG_SHIP_AI

		if (result == RUNNING)
			agent->addRunningID(id);
		else
			this->end(agent);

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

#endif /* DECORATORSPACE_H_ */
