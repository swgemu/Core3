/*
 * Behaviour.h
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "engine/engine.h"
#include <cassert>

namespace server {
namespace zone {
namespace objects {

namespace scene {
class SceneObject;
}

namespace creature {
namespace ai {

class AiAgent;

namespace bt {

namespace node {
class Composite;
}

class Behavior : public Object {
protected:
	String className;
	uint32 id;
	Reference<Behavior*> parent; // the parent must be a Composite or a Decorator

public:
	enum Status {
		INVALID,   // finished without result
		SUCCESS,   // finished with success
		FAILURE,   // finished with failure
		RUNNING,   // running and not finished
		SUSPEND,   // not yet started, or temporarily paused
	};
	
	/**
	 * Creates a new instance of the Behavior class
	 * @param _agent Reference to the AI agent (as a blackboard)
	 */
	Behavior(const String& className, const uint32 id, const String& argString = "")
		: Object(), className(className), id(id), parent(NULL) {}

	Behavior(const Behavior& b) 
		: Object(), className(b.className), id(b.id), parent(b.parent) {}

	Behavior& operator=(const Behavior& b) {
		if (this == &b)
			return *this;

		className = b.className;
		id = b.id;
		parent = b.parent;

		return *this;
	}

	virtual ~Behavior() {}

	virtual String print() const {
		return className;
	}
	
	virtual bool isComposite() const {
		return false;
	}
	
	virtual bool isDecorator() const {
		return false;
	}
	
	void setParent(Behavior* parent_) {
		assert(parent_ != NULL && (parent_->isComposite() || parent_->isDecorator()));
		parent = parent_;
	}
	
	uint32 getID() const {
		return id;
	}

	Behavior* getParent() const {
		return parent;
	}

protected:
	/**
	 * Parses an argument string to set the arguments at initialization
	 * @pre {}
	 * @post {}
	 * @param argString colon-delimited string of =-delimited argument pairs
	 * @return a vectormap of keyed string arguments.
	 */
	static VectorMap<String, String> fillArgs(const String& argString) {
		StringTokenizer argTokens(argString);
		argTokens.setDelimeter(":");
		
		VectorMap<String, String> args;
		args.setNullValue("");
		
		while (argTokens.hasMoreTokens()) {
			String arg;
			argTokens.getStringToken(arg);
			
			int eqPos = arg.indexOf("=");
			if (eqPos == -1) continue;
			
			String argKey = arg.subString(0, eqPos).trim();
			String argVal = arg.subString(eqPos + 1, arg.length()).trim();
			
			args.put(argKey, argVal);
		}
		
		return args;
	}

	/**
	 * Virtual to check to see if the behavior can be updated
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 * @param agent The agent performing the action
	 * @return true if we can update, false if not
	 */
	virtual bool checkConditions(AiAgent* agent) const;

	/**
	 * Virtual to provide startup logic
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 * @param agent The agent performing the action
	 */
	virtual void start(AiAgent* agent) const {}

	/**
	 * Virtual to provide execution logic
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 * @param agent The agent performing the action
	 * @param startIdx The start index for children (unused for leafs)
	 * @return The result of the execution
	 */
	virtual Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const = 0;

	/**
	 * Virtual to provide termination logic
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 * @param agent The agent performing the action
	 */
	virtual void end(AiAgent* agent) const {}

public:
	/**
	 * Virtual to provide logic for each update
	 * @pre { agent is locked }
	 * @post { agent is locked, action is executed }
	 * @param agent The agent performing the action
	 * @return The result of the execution
	 */
	virtual Behavior::Status doAction(Reference<AiAgent*> agent) const;
};

}
}
}
}
}
}

#endif /* BEHAVIOR_H_ */
