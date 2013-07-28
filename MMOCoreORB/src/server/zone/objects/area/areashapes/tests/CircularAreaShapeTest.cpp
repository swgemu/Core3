/*
 * CircularAreaShapeTest.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: loshult
 */

#include "gtest/gtest.h"
#include "../CircularAreaShape.h"

namespace server {
namespace zone {
namespace objects {
namespace area {
namespace areashapes {
namespace test {

class CircularAreaShapeTest : public ::testing::Test {
public:
	Reference<CircularAreaShape*> circularAreaShape;

	CircularAreaShapeTest() {
		// Perform creation setup here.
		circularAreaShape = new CircularAreaShape();
	}

	~CircularAreaShapeTest() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};

TEST_F(CircularAreaShapeTest, CircularAreaShapeHasItsCenterAtZeroZeroZeroAfterCreation) {
	EXPECT_EQ(circularAreaShape->getAreaCenter().getX(), 0);
	EXPECT_EQ(circularAreaShape->getAreaCenter().getY(), 0);
	EXPECT_EQ(circularAreaShape->getAreaCenter().getZ(), 0);
}

}
}
}
}
}
}
