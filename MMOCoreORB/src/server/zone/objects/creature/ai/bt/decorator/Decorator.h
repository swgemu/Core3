#ifndef DECORATOR_H_
#define DECORATOR_H_

#include "server/zone/objects/creature/ai/bt/Behavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace decorator {

class Decorator : public Behavior {
protected:
	Reference<Behavior*> child;

public:
	Decorator(const String& className, const uint32 id, const String& argString = "")
		: Behavior(className, id, argString) {}

	Decorator(const Decorator& b)
		: Behavior(b) {
		child = b.child;
	}

	Decorator& operator=(const Decorator& b) {
		if (this == &b)
			return *this;

		Behavior::operator=(b);
		child = b.child;

		return *this;
	}

	virtual ~Decorator() {}
	
	bool isDecorator() {
	    return true;
	}

	virtual void setChild(Reference<Behavior*> newChild) {
		assert(child != this);

		child = newChild;
	}

	String print() const {
    	StringBuffer stream;
    	stream << Behavior::print() << "[";
    	stream << child->print() << " ";
    	stream << "]";
    	return stream.toString();
    }

	virtual bool checkConditions(AiAgent* agent) const {
		return child != NULL && Behavior::checkConditions(agent);
	}

	Behavior::Status doAction(Reference<AiAgent*> agent) const {
    	if (!this->checkConditions(agent))
    		return INVALID; // TODO: should this be FAILURE?
    	
    	if (!agent->isRunningBehavior(id))
    		this->start(agent);
    	else
    		agent->popRunningChain();
    		
    	Behavior::Status result = this->execute(agent);
    	
    	if (result == RUNNING)
    		agent->addRunningID(id);
    	else
    		this->end(agent);
    	
    	return result;
    }
};

}
}
}
}
}
}
}

#endif /* DECORATOR_H_ */