/*
 * LuaSequence.h
 *
 *  Created on: Sep 4, 2013
 *      Author: swgemu
 */

#ifndef LUASEQUENCE_H_
#define LUASEQUENCE_H_

#include "SequenceBehavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class LuaSequence: public SequenceBehavior {
public:
	LuaSequence();
	virtual ~LuaSequence();
	void setTree(BehaviorTree* tree) {
		this->tree = tree;
	}
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;

#endif /* LUASEQUENCE_H_ */
