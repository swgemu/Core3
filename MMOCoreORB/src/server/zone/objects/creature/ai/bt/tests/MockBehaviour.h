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

class MockBehaviour: public Behavior {
public:
	MOCK_METHOD0(tick, Status());
	MOCK_METHOD0(update,Status());
	MOCK_METHOD0(onInitialize,void());
	MOCK_METHOD0(canObserve,bool());
	MOCK_METHOD1(onTerminate, void(Status s));
	MOCK_METHOD1(observe, void(Status s));
};

}
}
}
}
}
}


#endif /* MOCKBEHAVIOUR_H_ */
