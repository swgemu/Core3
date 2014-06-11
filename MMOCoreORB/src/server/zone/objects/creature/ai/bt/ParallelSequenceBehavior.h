/*
 * ParallelSequenceBehavior.h
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#ifndef PARALLELSEQUENCEBEHAVIOR_H_
#define PARALLELSEQUENCEBEHAVIOR_H_

#include "ParallelBehavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class ParallelSequenceBehavior : public ParallelBehavior {
public:
	ParallelSequenceBehavior(AiAgent* _agent, String className);
	void finish();
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;





#endif /* PARALLELSEQUENCEBEHAVIOR_H_ */
