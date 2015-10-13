/*
 * LuaBehavior.h
 *
 *  Created on: Sep 1, 2013
 *      Author: swgemu
 */

#ifndef LUABEHAVIOR_H_
#define LUABEHAVIOR_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {

namespace scene {
class SceneObject;
}

using namespace server::zone::objects::scene;

namespace creature {
namespace ai {
class AiAgent;
namespace bt {

class LuaBehavior : public Object {
public:

	LuaBehavior(const String& name);
	virtual ~LuaBehavior();

	LuaBehavior(const LuaBehavior& b) : Object() {
		className = b.className;
	}

	LuaBehavior& operator=(const LuaBehavior& b) {
		if (this == &b)
			return *this;

		className = b.className;

		return *this;
	}

	bool initialize();

	/**
	 * Script call to interface
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 */
	bool checkConditions(AiAgent* agent);

	/**
	 * Script call to interface
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 */
	void start(AiAgent* agent);

	/**
	 * Script call to interface
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 */
	float end(AiAgent* agent);

	/**
	 * Script call to interface
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 */
	int doAction(AiAgent* agent);

	/**
	 * Script call to interface
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 */
	int interrupt(AiAgent* agent, SceneObject* source, int64 msg);

	/**
	 * Script call to interface
	 * @pre { agent is locked }
	 * @post { agent is locked }
	 */
	bool doAwarenessCheck(AiAgent* agent, SceneObject* target);

	virtual uint16 getType();

	String print() {
		return this->className;
	}

protected:
	String className;
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;

#endif /* LUABEHAVIOR_H_ */
