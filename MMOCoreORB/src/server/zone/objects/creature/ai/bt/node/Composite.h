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
            Behavior* temp = ran.set(i, ran.get(index));
            ran.set(index, temp);
        }

        return ran;
    }

public:
	Composite(const String& className, const uint32 id, const String& argString = "")
		: Behavior(className, id, argString) {}

	Composite(const Composite& b)
		: Behavior(b), children(b.children) {}

	Composite& operator=(const Composite& b) {
		if (this == &b)
			return *this;

		Behavior::operator=(b);
		children = b.children;

		return *this;
	}

	virtual ~Composite() {}
	
	bool isComposite() {
		return true;
	}

	virtual void addChild(Reference<Behavior*> child) {
		assert(child != this);

		children.add(child);
	}

	String print() const;

	virtual bool checkConditions(AiAgent* agent) const {
		return children.size() > 0 && Behavior::checkConditions(agent);
	}

	Behavior::Status doAction(Reference<AiAgent*> agent) const;
};

}
}
}
}
}
}
}

#endif /* COMPOSITE_H_ */
