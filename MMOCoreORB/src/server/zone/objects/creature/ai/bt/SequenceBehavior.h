/*
 * SequenceBehavior
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef SEQUENCEBEHAVIOR_H_
#define SEQUENCEBEHAVIOR_H_

#include "CompositeBehavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class SequenceBehavior : public virtual CompositeBehavior {
public:
	SequenceBehavior(AiAgent* _agent, const String& className);
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

#endif /* SEQUENCEBEHAVIOR_H_ */
