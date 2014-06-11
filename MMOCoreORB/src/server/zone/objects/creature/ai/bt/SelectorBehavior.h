/*
 * SelectorBehavior.h
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#ifndef SELECTORBEHAVIOR_H_
#define SELECTORBEHAVIOR_H_

#include "CompositeBehavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class SelectorBehavior : public virtual CompositeBehavior {
public:
	SelectorBehavior(AiAgent* _agent, String className);
	void childSucceeded();
	void childFailed();
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;

#endif /* SELECTORBEHAVIOR_H_ */
