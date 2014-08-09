/*
 * CompositeBehavior
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef COMPOSITEBEHAVIOR_H_
#define COMPOSITEBEHAVIOR_H_

#include <cassert>

#include "engine/engine.h"
#include "Behavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class CompositeBehavior : public Behavior {
protected:
	Vector<Behavior*> children;
	uint32 currentPos;

public:
	virtual void addChild(Behavior* child) {
		assert(child != this);

		children.add(child);
	}

	Vector<Behavior*> getChildren() {
		return children;
	}

	void clearChildren() {
		children.removeAll();
	}

	CompositeBehavior(AiAgent* _agent, String className);

	CompositeBehavior(const CompositeBehavior& b);

	CompositeBehavior& operator=(const CompositeBehavior& b) {
		if (this == &b)
			return *this;

		agent = b.agent;
		result = b.result;
		parent = b.parent;
		interface = b.interface;
		children = b.children;
		currentPos = b.currentPos;

		return *this;
	}

	virtual ~CompositeBehavior() {
	}

	bool isComposite() {
		return true;
	}

	String print();

	virtual void childSucceeded() {
		endWithSuccess();
	}

	virtual void childFailed() {
		endWithFailure();
	}

	virtual bool checkConditions();

	virtual void start();

	virtual void doAction(bool directlyExecuted = false);
};

}
}
}
}
}
}
using namespace server::zone::objects::creature::ai::bt;
#endif /* COMPOSITEBEHAVIOR_H_ */
