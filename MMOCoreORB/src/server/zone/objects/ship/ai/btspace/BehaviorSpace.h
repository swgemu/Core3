/*
 * BehaviorSpace.h
 */

#ifndef BEHAVIORSPACE_H_
#define BEHAVIORSPACE_H_

#include "engine/engine.h"
#include "engine/lua/LuaObject.h"
#include <cassert>
#include "server/zone/objects/ship/ai/btspace/BlackboardDataSpace.h"
#include "BehaviorTreeSlotSpace.h"

#define _ARGPAIR(bigT, getter)                                                \
	template <>                                                               \
	struct getArg<bigT> {                                                     \
		bigT operator()(LuaObject args, const String& key) {                  \
			if (!args.isValidTable())                                         \
				return static_cast<bigT>(0);                                  \
			return static_cast<bigT>(args.getter(key));                       \
		}                                                                     \
		bigT operator()(LuaObject args, const String& key, bigT defaultVal) { \
			if (!args.isValidTable())                                         \
				return defaultVal;                                            \
			return static_cast<bigT>(args.getter(key, defaultVal));           \
		}                                                                     \
	};

namespace server {
namespace zone {
namespace objects {

namespace scene {
class SceneObject;
}

namespace ship {
namespace ai {

class ShipAiAgent;

namespace btspace {

template <typename T>
struct getArg {};
// String is special...
template <>
struct getArg<String> {
	String operator()(LuaObject args, const String& key, const char* defaultVal = "") {
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
_ARGPAIR(DataValSpace, getIntField)
_ARGPAIR(BehaviorTreeSlotSpace, getIntField)

namespace nodespace {
class CompositeSpace;
}

class BehaviorSpace : public Object {
protected:
	String className;
	uint32 id;
	WeakReference<BehaviorSpace*> parent; // the parent must be a Composite or a Decorator

public:
	enum Status {
		INVALID, // finished without result
		SUCCESS, // finished with success
		FAILURE, // finished with failure
		RUNNING, // running and not finished
		SUSPEND, // not yet started, or temporarily paused
	};

	/**
	 * Creates a new instance of the BehaviorSpace class
	 * @param _agent Reference to the AI agent (as a blackboard)
	 */
	BehaviorSpace(const String& className, const uint32 id, const LuaObject& args);

	BehaviorSpace(const BehaviorSpace& b) : Object(), className(b.className), id(b.id), parent(b.parent) {
	}

	BehaviorSpace& operator=(const BehaviorSpace& b) {
		if (this == &b)
			return *this;

		className = b.className;
		id = b.id;
		parent = b.parent;

		return *this;
	}

	virtual ~BehaviorSpace() {
	}

	virtual String print() const {
		return className;
	}

	virtual bool isCompositeSpace() const {
		return false;
	}

	virtual bool isDecoratorSpace() const {
		return false;
	}

	virtual bool isSocketSpace() const {
		return false;
	}

	void setParent(BehaviorSpace* parent_) {
		assert(parent_ != nullptr);
		assert(parent_->isCompositeSpace() || parent_->isDecoratorSpace());
		parent = parent_;
	}

	uint32 getID() const {
		return id;
	}

	BehaviorSpace* getParent() const {
		return parent.get();
	}

	virtual BehaviorSpace* getChild(uint32) const {
		return NULL;
	}

	virtual bool hasChild(BehaviorSpace*) const {
		return false;
	}

	virtual Vector<const BehaviorSpace*> getRecursiveChildList() const {
		Vector<const BehaviorSpace*> retVal;
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
	virtual bool checkConditions(ShipAiAgent* agent) const;

	/**
	 * Virtual to provide startup logic
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 * @param agent The agent performing the action
	 */
	virtual void start(ShipAiAgent* agent) const {
	}

	/**
	 * Virtual to provide execution logic
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 * @param agent The agent performing the action
	 * @param startIdx The start index for children (unused for leafs)
	 * @return The result of the execution
	 */
	virtual BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const = 0;

	/**
	 * Virtual to provide termination logic
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 * @param agent The agent performing the action
	 */
	virtual void end(ShipAiAgent* agent) const {
	}

public:
	/**
	 * Virtual to provide logic for each update
	 * @pre { agent is locked }
	 * @post { agent is locked, action is executed }
	 * @param agent The agent performing the action
	 * @return The result of the execution
	 */
	virtual BehaviorSpace::Status doAction(ShipAiAgent* agent) const;
};

} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif /* BEHAVIORSPACE_H_ */
