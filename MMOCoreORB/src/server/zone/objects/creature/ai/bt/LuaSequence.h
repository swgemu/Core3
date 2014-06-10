/*
 * LuaSequence.h
 *
 *  Created on: Sep 4, 2013
 *      Author: swgemu
 */

#ifndef LUASEQUENCE_H_
#define LUASEQUENCE_H_

#include "engine/engine.h"
#include "LuaBehavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class LuaSequence : public LuaBehavior {
protected:
	String className;

public:
	LuaSequence(String name);
	virtual ~LuaSequence();
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;

#endif /* LUASEQUENCE_H_ */
