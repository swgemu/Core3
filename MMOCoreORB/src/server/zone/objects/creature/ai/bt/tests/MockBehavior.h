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
	MOCK_METHOD1(tick, int(AiAgent* a));
	MOCK_METHOD1(update,int(AiAgent* a));
	MOCK_METHOD1(onInitialize,void(AiAgent* a));
	MOCK_METHOD0(canObserve,bool());
	MOCK_METHOD2(onTerminate, void(AiAgent* a,int s));
	MOCK_METHOD1(observe, void(AiAgent* a));
};

}
}
}
}
}
}


#endif /* MOCKBEHAVIOUR_H_ */
