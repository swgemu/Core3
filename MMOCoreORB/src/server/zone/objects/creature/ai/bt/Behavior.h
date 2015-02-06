/*
 * Behaviour.h
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/ai/bt/LuaBehavior.h"

namespace server {
namespace zone {
namespace objects {

namespace scene {
class SceneObject;
}

namespace creature {

class AiAgent;

namespace ai {
namespace bt {

class CompositeBehavior;

class Behavior {
protected:
	ManagedReference<AiAgent*> agent; // this is like the blackboard
	uint8 result;
	Behavior* parent; // the parent must be a composite
	Reference<LuaBehavior*> interface;
	uint32 id;

public:
	/**
	 * Creates a new instance of the Behavior class
	 * @param _agent Reference to the AI agent (as a blackboard)
	 */
	Behavior(AiAgent* _agent, String className);

	Behavior(const Behavior& b) {
		agent = b.agent;
		result = b.result;
		parent = b.parent;
		interface = b.interface;
		id = b.id;
	}

	Behavior& operator=(const Behavior& b) {
		if (this == &b)
			return *this;

		agent = b.agent;
		result = b.result;
		parent = b.parent;
		interface = b.interface;
		id = b.id;

		return *this;
	}

	virtual ~Behavior() {
	}

	inline void setID(uint32 _id) {
		this->id = _id;
	}

	virtual bool isComposite() {
		return false;
	}

	LuaBehavior* getInterface() {
		return interface;
	}

	virtual String print() {
		return interface->print();
	}

	/**
	 * Virtual to check to see if the behavior can be updated
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 * @return true if we can update, false if not
	 */
	virtual bool checkConditions() {
		if (interface != NULL)
			return interface->checkConditions(agent);

		return false;
	}

	/**
	 * Virtual to provide startup logic
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 */
	virtual void start();

	/**
	 * Virtual to provide termination logic
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 */
	virtual void end();

	/**
	 * Virtual to provide logic for each update
	 * @pre { agent is locked }
	 * @post { agent is locked, action is exectued }
	 * @param directlyExecuted boolean that is true if the parent is to be executed immediately after this finishes
	 */
	virtual void doAction(bool directlyExecuted = false);

	virtual int interrupt(SceneObject* source, int64 msg) {
		return interface->interrupt(agent.get(), source, msg);
	}

	/**
	 * Virtual to ensure that we should do an awareness check
	 */
	virtual bool doAwarenessCheck(SceneObject* target) {
		if (interface != NULL)
			return interface->doAwarenessCheck(agent.get(), target);

		return false;
	}

	/**
	 * End the behavior with success
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 */
	void endWithSuccess();

	/**
	 * End the behavior with failure
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 */
	void endWithFailure();

	/**
	 * End the behavior with an error
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 */
	void endWithError();

	/**
	 * setter and getter for the parent (to set up the actual tree)
	 */
	void setParent(Behavior* _parent) {
		this->parent = _parent;
	}

	Behavior* getParent() {
		return parent;
	}

	uint8 getStatus() {
		return result;
	}

	void setStatus(uint8 s) {
		this->result = s;
	}

	/**
	 * Status getters
	 */
	bool succeeded();

	bool failed();

	bool finished();

	bool started();

};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;
#endif /* BEHAVIOR_H_ */
