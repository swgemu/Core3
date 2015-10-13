/*
 * Sequence
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "server/zone/objects/creature/ai/bt/node/Composite.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace node {

class Sequence : public Composite {
public:
	Sequence(const String& className, const uint32 id, const String& argString = "")
		: Composite(className, id, argString) {}
	
	virtual Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const;
};

}
}
}
}
}
}
}

#endif /* SEQUENCE_H_ */
