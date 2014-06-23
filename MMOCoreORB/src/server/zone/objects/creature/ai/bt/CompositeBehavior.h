/*
 * CompositeBehavior
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef COMPOSITEBEHAVIOR_H_
#define COMPOSITEBEHAVIOR_H_

#include "Behavior.h"
#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class CompositeBehavior : public Behavior {
protected:
	Vector<Reference<Behavior*> > children;
	uint32 currentPos;

public:
	virtual void addChild(Behavior* child) {
		children.add(child);
	}

	Vector<Reference<Behavior*> > getChildren() {
		return children;
	}

	void clearChildren() {
		children.removeAll();
	}

	CompositeBehavior(AiAgent* _agent, String className) : Behavior(_agent, className) {
		currentPos = 0;
	}

	CompositeBehavior(const CompositeBehavior& b) : Behavior(b) {
		this->children = b.children;
		this->currentPos = b.currentPos;
	}

	CompositeBehavior& operator=(const CompositeBehavior& b) {
		if (this == &b)
			return *this;

		this->children = b.children;
		this->currentPos = b.currentPos;
		this->agent = b.agent;
		this->result = b.result;
		this->parent = b.parent;

		return *this;
	}

	bool isComposite() {
		return true;
	}

	String print() {
		StringBuffer stream;
		stream << Behavior::print() << " ";
		for (int i = 0; i < children.size(); i ++) {
			stream << children.get(i)->print() << " ";
		}
		return stream.toString();
	}

	virtual void childSucceeded() {
		endWithSuccess();
	}

	virtual void childFailed() {
		endWithFailure();
	}

	virtual bool checkConditions() {
		return children.size() > 0 && Behavior::checkConditions();
	}

	virtual void start();

	virtual void doAction();
};

}
}
}
}
}
}
using namespace server::zone::objects::creature::ai::bt;
#endif /* COMPOSITEBEHAVIOR_H_ */
