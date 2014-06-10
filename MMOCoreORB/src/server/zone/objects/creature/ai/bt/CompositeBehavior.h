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

class CompositeBehavior : public Behavior{
protected:
	Vector<Reference<Behavior*> > children;
	uint32 currentPos;

public:
	virtual void addChild(Behavior* child) {
		children.add(child);
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

	virtual void childSucceeded() = 0;
	virtual void childFailed() = 0;

	bool checkConditions() {
		return children.size() > 0 && Behavior::checkConditions();
	}

	void start() {
		currentPos = 0;
		Reference<Behavior*> currentChild = children.get(currentPos);
		if (currentChild == NULL)
			agent->error("NULL child or empty children list in CompositeBehavior");

		Behavior::start();
	}

	void doAction() {
		if (finished()) {
			Behavior::doAction();
			return;
		}

		Reference<Behavior*> currentChild = children.get(currentPos);

		if (currentChild == NULL) {
			agent->error("NULL child or empty children list in CompositeBehavior");
			endWithError();
			Behavior::doAction();
			return;
		}

		if (!currentChild->started())
			currentChild->start();

		if (currentChild->finished()) {
			currentChild->end();
			agent->setCurrentBehavior(this);
			if (currentChild->succeeded())
				this->childSucceeded();
			if (currentChild->failed())
				this->childFailed();
		} else {
			agent->setCurrentBehavior(currentChild);
			currentChild->doAction();
		}

		Behavior::doAction();
	}
};

}
}
}
}
}
}
using namespace server::zone::objects::creature::ai::bt;
#endif /* COMPOSITEBEHAVIOR_H_ */
