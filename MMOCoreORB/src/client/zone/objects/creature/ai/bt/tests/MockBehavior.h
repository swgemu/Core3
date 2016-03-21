/*
 * MockBehaviour.h
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */
#include "gmock/gmock.h"
#include "server/zone/objects/creature/ai/bt/Behavior.h"

#ifndef MOCKBEHAVIOUR_H_
#define MOCKBEHAVIOUR_H_

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class MockBehavior: public Behavior {
public:
	MockBehavior(MockAiAgent* _agent, String className) : Behavior(_agent, className) {
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


#endif /* MOCKBEHAVIOUR_H_ */
