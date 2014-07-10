/*
 * ParallelSelectorBehavior.h
 *
 *  Created on: Jun 11, 2014
 *      Author: swgemu
 */

#ifndef PARALLELSELECTORBEHAVIOR_H_
#define PARALLELSELECTORBEHAVIOR_H_

#include "ParallelBehavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class ParallelSelectorBehavior : public ParallelBehavior {
public:
	ParallelSelectorBehavior(AiAgent* _agent, String className);
	void finish();
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;





#endif /* PARALLELSELECTORBEHAVIOR_H_ */
