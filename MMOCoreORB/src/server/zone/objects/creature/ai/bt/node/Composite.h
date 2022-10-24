/*
 * Composite
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef COMPOSITE_H_
#define COMPOSITE_H_

#include "server/zone/objects/creature/ai/bt/Behavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace node {

class Composite : public Behavior {
protected:
	Vector<Reference<Behavior*> > children;

	Vector<Reference<Behavior*> > shuffleChildren() const {
		Vector<Reference<Behavior*> > ran = children;

		for (int i = 0; i < ran.size(); ++i) {
			int index = (int) System::random(ran.size() - 1 - i) + i;
			Reference<Behavior*> temp = ran.set(i, ran.get(index));
			ran.set(index, temp);
		}

		return ran;
	}

public:
	Composite(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	Composite(const Composite& b)
			: Behavior(b), children(b.children) {
	}

	Composite& operator=(const Composite& b) {
		if (this == &b)
			return *this;

		Behavior::operator=(b);
		children = b.children;

		return *this;
	}

	virtual ~Composite() {
	}

	bool isComposite() const {
		return true;
	}

	bool hasChild(Behavior* c) const {
		for (int idx = 0; idx < children.size(); ++idx)
			if (children.get(idx) == c)
				return true;

		return false;
	}

	Behavior* getChild(uint32 cID) const {
		for (int idx = 0; idx < children.size(); ++idx)
			if (children.get(idx)->getID() == cID)
				return children.get(idx);

		return NULL;
	}

	Vector<const Behavior*> getRecursiveChildList() const {
		Vector<const Behavior*> retVal;
		retVal.add(this);

		for (int idx = 0; idx < children.size(); ++idx) {
			retVal.addAll(children.get(idx)->getRecursiveChildList());
		}

		return retVal;
	}

	virtual void addChild(Reference<Behavior*> child) {
		assert(child != this);

		children.add(child);
	}

	String print() const;

	virtual bool checkConditions(AiAgent* agent) const {
		if (children.size() <= 0)
			return false;

		if (!Behavior::checkConditions(agent)) {
			return true;
		}

		return true;
	}

	Behavior::Status doAction(AiAgent* agent) const;
};

}
}
}
}
}
}
}

#endif /* COMPOSITE_H_ */
