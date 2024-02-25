/*
 * CompositeSpace.h
 */

#ifndef COMPOSITESPACE_H_
#define COMPOSITESPACE_H_

#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace nodespace {

class CompositeSpace : public BehaviorSpace {
protected:
	Vector<Reference<BehaviorSpace*>> children;

	Vector<Reference<BehaviorSpace*>> shuffleChildren() const {
		Vector<Reference<BehaviorSpace*>> ran = children;

		for (int i = 0; i < ran.size(); ++i) {
			int index = (int)System::random(ran.size() - 1 - i) + i;

			Reference<BehaviorSpace*> temp = ran.set(i, ran.get(index));

			ran.set(index, temp);
		}

		return ran;
	}

public:
	CompositeSpace(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	CompositeSpace(const CompositeSpace& b) : BehaviorSpace(b), children(b.children) {
	}

	CompositeSpace& operator=(const CompositeSpace& b) {
		if (this == &b)
			return *this;

		BehaviorSpace::operator=(b);
		children = b.children;

		return *this;
	}

	virtual ~CompositeSpace() {
	}

	bool isCompositeSpace() const {
		return true;
	}

	bool hasChild(BehaviorSpace* c) const {
		for (int idx = 0; idx < children.size(); ++idx)
			if (children.get(idx) == c)
				return true;

		return false;
	}

	BehaviorSpace* getChild(uint32 cID) const {
		for (int idx = 0; idx < children.size(); ++idx)
			if (children.get(idx)->getID() == cID)
				return children.get(idx);

		return NULL;
	}

	Vector<const BehaviorSpace*> getRecursiveChildList() const {
		Vector<const BehaviorSpace*> retVal;
		retVal.add(this);

		for (int idx = 0; idx < children.size(); ++idx) {
			retVal.addAll(children.get(idx)->getRecursiveChildList());
		}

		return retVal;
	}

	virtual void addChild(Reference<BehaviorSpace*> child) {
		assert(child != this);

		children.add(child);
	}

	String print() const;

	virtual bool checkConditions(ShipAiAgent* agent) const {
		if (children.size() <= 0)
			return false;

		if (!BehaviorSpace::checkConditions(agent)) {
			return true;
		}

		return true;
	}

	BehaviorSpace::Status doAction(ShipAiAgent* agent) const;
};

} // namespace nodespace
} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif /* COMPOSITESPACE_H_ */
