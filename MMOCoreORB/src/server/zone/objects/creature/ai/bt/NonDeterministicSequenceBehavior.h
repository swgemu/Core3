/*
 * NonDeterministicSequenceBehavior.h
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#ifndef NONDETERMINISTICSEQUENCEBEHAVIOR_H_
#define NONDETERMINISTICSEQUENCEBEHAVIOR_H_

#include "NonDeterministicBehavior.h"
#include "SequenceBehavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class NonDeterministicSequenceBehavior : public SequenceBehavior, public NonDeterministicBehavior {
public:
	NonDeterministicSequenceBehavior(AiAgent* _agent, String className) : CompositeBehavior(_agent, className), SequenceBehavior(_agent, className), NonDeterministicBehavior(_agent, className) {
	}
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;





#endif /* NONDETERMINISTICSEQUENCEBEHAVIOR_H_ */
