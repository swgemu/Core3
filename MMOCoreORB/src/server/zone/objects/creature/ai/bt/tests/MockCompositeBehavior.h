/*
 * MockBehaviorSequence.h
 *
 *  Created on: Aug 28, 2013
 *      Author: swgemu
 */

#ifndef MOCKCOMPOSITEBEHAVIOR_H_
#define MOCKCOMPOSITEBEHAVIOR_H_

#include "gmock/gmock.h"
#include "MockBehavior.h"
#include "server/zone/objects/creature/ai/bt/CompositeBehavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class MockCompositeBehavior: public CompositeBehavior {
public:
	MockCompositeBehavior(AiAgent* _agent, String className, uint32 size) : CompositeBehavior(_agent, className) {
		for(uint32 i=0; i<size; i++) {
			children.add(new MockBehavior());
		}
	}

	~MockCompositeBehavior() {
		children.removeAll();
	}

	MOCK_METHOD0(checkConditions, bool());
	MOCK_METHOD0(start, void());
	MOCK_METHOD0(end, void());
	MOCK_METHOD0(doAction, void());
};

}
}
}
}
}
}


#endif /* MOCKCOMPOSITEBEHAVIOR_H_ */
