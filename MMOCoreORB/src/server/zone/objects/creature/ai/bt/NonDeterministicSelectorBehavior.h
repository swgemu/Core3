/*
 * NonDeterministicSelectorBehavior.h
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#ifndef NONDETERMINISTICSELECTORBEHAVIOR_H_
#define NONDETERMINISTICSELECTORBEHAVIOR_H_

#include "NonDeterministicBehavior.h"
#include "SelectorBehavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class NonDeterministicSelectorBehavior : public SelectorBehavior, public NonDeterministicBehavior {
public:
	NonDeterministicSelectorBehavior(AiAgent* _agent, const String& className) : CompositeBehavior(_agent, className), SelectorBehavior(_agent, className), NonDeterministicBehavior(_agent, className) {
	}
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;



#endif /* NONDETERMINISTICSELECTORBEHAVIOR_H_ */
