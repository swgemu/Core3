/*
 * NonDeterministicBehavior.h
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#ifndef NONDETERMINISTICBEHAVIOR_H_
#define NONDETERMINISTICBEHAVIOR_H_

#include "CompositeBehavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class NonDeterministicBehavior : public virtual CompositeBehavior {
public:
	NonDeterministicBehavior(AiAgent* _agent, String className);
	void start();
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;





#endif /* NONDETERMINISTICBEHAVIOR_H_ */
