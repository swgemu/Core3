/*
 * MockBehaviorSequence.h
 *
 *  Created on: Aug 28, 2013
 *      Author: swgemu
 */

#ifndef MOCKSEQUENCEBEHAVIOR_H_
#define MOCKSEQUENCEBEHAVIOR_H_
#include "gmock/gmock.h"
#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "MockBehavior.h"
#include "server/zone/objects/creature/ai/bt/SequenceBehavior.h"
#include "server/zone/objects/creature/ai/bt/BehaviorTree.h"


namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class MockSequenceBehavior: public SequenceBehavior {
public:
	MockSequenceBehavior(BehaviorTree *tree, uint32 size) : SequenceBehavior(tree) {
		for(uint32 i=0;i<size;i++) {
			children.add(new MockBehavior());
		}
	}
	~MockSequenceBehavior() {
		int c = children.size();
		for(int i=0;i<c;i++) {
			Behavior* b = children.remove(0);
			delete b;
		}
	}
	MOCK_METHOD1(tick, int(AiActor* a));
	MOCK_METHOD1(update,int(AiActor* a));
	MOCK_METHOD1(onInitialize,void(AiActor* a));
	MOCK_METHOD0(canObserve,bool());
	MOCK_METHOD2(onTerminate, void(AiActor* a,int s));
	MOCK_METHOD1(observe, void(AiActor* a));
    MockBehavior& operator[](uint32 index)
    {
        return *static_cast<MockBehavior*>(children.get(index));
    }
};

}
}
}
}
}
}


#endif /* MOCKSEQUENCEBEHAVIOR_H_ */
