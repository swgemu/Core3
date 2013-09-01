/*
 * LuaBehavior.h
 *
 *  Created on: Sep 1, 2013
 *      Author: swgemu
 */

#ifndef LUABEHAVIOR_H_
#define LUABEHAVIOR_H_

#include "Behavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class LuaBehavior: public Behavior {
public:

	LuaBehavior(String name);
	virtual ~LuaBehavior();
	virtual Status update(AiActor* actor);
	virtual void onInitialize(AiActor* actor);
	virtual void onTerminate(AiActor* actor, Status s);
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
