/*
 * BehaviourTest.cpp
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MockBehavior.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::AnyNumber;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::Sequence;
using ::testing::Assign;
using ::testing::DoAll;
using ::testing::Mock;

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace test {

class BehaviorTest : public ::testing::Test {
public:
	Reference<MockAiAgent*> agent;
	BehaviorTest() {
		// Perform creation setup here.
	}

	~BehaviorTest() {
		// Clean up.
	}

	void SetUp() {
		agent = new MockAiAgent();
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};
/*TEST_F(BehaviorTest, testInitialize) {
	MockBehavior mock;
	BehaviorTree tree;
	ON_CALL(mock,update(_)).WillByDefault(Return(Behavior::RUNNING));
	EXPECT_CALL(mock,onInitialize(_)).Times(AtLeast(1));
	EXPECT_CALL(mock,update(_)).Times(AtLeast(1));
	EXPECT_CALL(mock,canObserve()).Times(AtLeast(1));
	tree.start(&mock,actor);
	tree.tick(actor);

}
TEST_F(BehaviorTest, testUpdate) {
	MockBehavior mock;
	BehaviorTree tree;
	EXPECT_CALL(mock,onTerminate(_,_)).Times(AtLeast(0));
	EXPECT_CALL(mock,onInitialize(_)).Times(AtLeast(1));
	EXPECT_CALL(mock,update(_)).WillOnce(Return(Behavior::RUNNING));
	EXPECT_CALL(mock,canObserve()).Times(AtLeast(1));
	tree.start(&mock,actor);
	tree.tick(actor);
	EXPECT_CALL(mock,update(_)).WillOnce(Return(Behavior::RUNNING));
	tree.tick(actor);
}
TEST_F(BehaviorTest, testTerminate) {
	MockBehavior mock;
	BehaviorTree tree;
	EXPECT_CALL(mock,onTerminate(_,_)).Times(AtLeast(1));
	EXPECT_CALL(mock,canObserve()).Times(AtLeast(1));
	EXPECT_CALL(mock,onInitialize(_)).Times(AtLeast(1));
	EXPECT_CALL(mock,update(_)).WillOnce(Return(Behavior::RUNNING));
	tree.start(&mock,actor);
	tree.tick(actor);
	EXPECT_CALL(mock,update(_)).WillOnce(Return(Behavior::SUCCESS));
	tree.tick(actor);
}
TEST_F(BehaviorTest, testAbort) {
	MockBehavior mock;
	BehaviorTree tree;
	EXPECT_CALL(mock,onTerminate(_,_)).Times(AtLeast(0));
	EXPECT_CALL(mock,canObserve()).Times(AtLeast(0));
	EXPECT_CALL(mock,onInitialize(_)).Times(AtLeast(0));
	EXPECT_CALL(mock,update(_)).Times(AtLeast(0));
	tree.start(&mock,actor);
	tree.tick(NULL);

}
TEST_F(BehaviorTest, testSingleNodeTreePassAndFail) {
	int status[2] = { Behavior::SUCCESS,Behavior::FAILURE };
	for (int i=0; i<2; ++i) {
		BehaviorTree tree;
		MockSequenceBehavior mock(&tree,1);
		EXPECT_CALL(mock,onInitialize(_)).Times(AtLeast(1));
		EXPECT_CALL(mock,update(_)).WillOnce(Return(Behavior::RUNNING));
		EXPECT_CALL(mock,canObserve()).Times(AtLeast(1));
		tree.start(&mock,actor);
		tree.tick(actor);
		EXPECT_CALL(mock,update(_)).WillOnce(Return(status[i]));
		EXPECT_CALL(mock,onTerminate(_,_)).Times(AtLeast(1));
		EXPECT_CALL(mock,canObserve()).Times(AtLeast(1));
		tree.tick(actor);
		Mock::VerifyAndClearExpectations(&mock);
		actor->resetBehaviorList(&tree);
	}

}
TEST_F(BehaviorTest, testTwoNodesWithFailingBehavior) {
	BehaviorTree tree;
	MockSequenceBehavior mock(&tree,2);
	EXPECT_CALL(mock,onInitialize(_)).Times(AtLeast(1));
	EXPECT_CALL(mock,update(_)).WillOnce(Return(Behavior::RUNNING));
	EXPECT_CALL(mock,onTerminate(_,_)).Times(AtLeast(1));
	EXPECT_CALL(mock,canObserve()).Times(AtLeast(1));
	tree.start(&mock,actor);
	tree.tick(actor);
	EXPECT_CALL(mock,canObserve()).Times(AtLeast(1));
	EXPECT_CALL(mock,update(_)).WillOnce(Return(Behavior::FAILURE));
	tree.tick(actor);

}
TEST_F(BehaviorTest, testTwoNodeWithRunningBehavior) {
	BehaviorTree tree;
	MockSequenceBehavior mock(&tree,2);
	EXPECT_CALL(mock,onInitialize(_)).Times(AtLeast(1));
	EXPECT_CALL(mock,update(_)).WillOnce(Return(Behavior::RUNNING));
	EXPECT_CALL(mock,onTerminate(_,_)).Times(AtLeast(0));
	EXPECT_CALL(mock,canObserve()).Times(AtLeast(0));
	tree.start(&mock,actor);
	tree.tick(actor);
	EXPECT_CALL(mock,update(_)).WillOnce(Return(Behavior::RUNNING));
	tree.tick(actor);
}*/

}
}
}
}
}
}
}
