/*
 * Behaviour.h
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "engine/engine.h"
#include "engine/lua/LuaObject.h"
#include <cassert>
#include "BlackboardData.h"
#include "BehaviorTreeSlot.h"

#define _ARGPAIR(bigT, getter) \
template <> \
struct getArg<bigT> { \
	bigT operator()(LuaObject args, const String& key) { \
		if (!args.isValidTable()) \
			return static_cast<bigT>(0); \
		return static_cast<bigT>(args.getter(key)); \
	} \
	bigT operator()(LuaObject args, const String& key, bigT defaultVal) { \
		if (!args.isValidTable()) \
			return defaultVal; \
		return static_cast<bigT>(args.getter(key, defaultVal)); \
	} \
};

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

template<typename T> struct getArg {
};
// String is special...
template<> struct getArg<String> {
	String operator()(LuaObject args, const String& key,
			const char* defaultVal = "") {
		return args.getStringField(key, defaultVal);
	}
};
_ARGPAIR(int32, getSignedIntField)
_ARGPAIR(uint32, getIntField)
_ARGPAIR(uint64, getLongField)
_ARGPAIR(float, getFloatField)
_ARGPAIR(bool, getBooleanField)
_ARGPAIR(uint8, getByteField)
_ARGPAIR(uint16, getShortField)
_ARGPAIR(DataVal, getIntField)
_ARGPAIR(BehaviorTreeSlot, getIntField)

namespace node {
class Composite;
}

class Behavior: public Object {
protected:
	String className;
	uint32 id;
	WeakReference<Behavior*> parent; // the parent must be a Composite or a Decorator

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
	Behavior(const String& className, const uint32 id, const LuaObject& args);

	Behavior(const Behavior& b) :
			Object(), className(b.className), id(b.id), parent(b.parent) {
	}

	Behavior& operator=(const Behavior& b) {
		if (this == &b)
			return *this;

		className = b.className;
		id = b.id;
		parent = b.parent;

		return *this;
	}

	virtual ~Behavior() {
	}

	virtual String print() const {
		return className;
	}

	virtual bool isComposite() const {
		return false;
	}

	virtual bool isDecorator() const {
		return false;
	}

	virtual bool isSocket() const {
		return false;
	}

	void setParent(Behavior* parent_) {
		assert(parent_ != nullptr);
		assert(parent_->isComposite() || parent_->isDecorator());
		parent = parent_;
	}

	uint32 getID() const {
		return id;
	}

	Behavior* getParent() const {
		return parent.get();
	}

	virtual Behavior* getChild(uint32) const {
		return NULL;
	}

	virtual bool hasChild(Behavior*) const {
		return false;
	}

	virtual Vector<const Behavior*> getRecursiveChildList() const {
		Vector<const Behavior*> retVal;
		retVal.add(this);
		return retVal;
	}

protected:
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
	virtual void start(AiAgent* agent) const {
	}

	/**
	 * Virtual to provide execution logic
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 * @param agent The agent performing the action
	 * @param startIdx The start index for children (unused for leafs)
	 * @return The result of the execution
	 */
	virtual Behavior::Status execute(AiAgent* agent,
			unsigned int startIdx = 0) const = 0;

	/**
	 * Virtual to provide termination logic
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 * @param agent The agent performing the action
	 */
	virtual void end(AiAgent* agent) const {
	}

public:
	/**
	 * Virtual to provide logic for each update
	 * @pre { agent is locked }
	 * @post { agent is locked, action is executed }
	 * @param agent The agent performing the action
	 * @return The result of the execution
	 */
	virtual Behavior::Status doAction(AiAgent* agent) const;
};

}
}
}
}
}
}

#endif /* BEHAVIOR_H_ */
