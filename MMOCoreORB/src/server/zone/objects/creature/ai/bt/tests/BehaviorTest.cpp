/*
 * BehaviourTest.cpp
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MockBehaviour.h"
#include "../BehaviorTree.h"

using ::testing::AtLeast;
using ::testing::Return;

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace test {

class BehaviorTest : public ::testing::Test {
public:

	BehaviorTest() {
		// Perform creation setup here.
	}

	~BehaviorTest() {
		// Clean up.
	}

	void SetUp() {
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};
TEST(BehaviorTest, TaskInitialize) {
	MockBehaviour mock;
	BehaviorTree tree;
	ON_CALL(mock,tick()).WillByDefault(Return(RUNNING));
	ON_CALL(mock,update()).WillByDefault(Return(RUNNING));
	EXPECT_CALL(mock,onInitialize()).Times(AtLeast(1));
	tree.start(&mock);
	tree.tick();

}

}
}
}
}
}
}
}
