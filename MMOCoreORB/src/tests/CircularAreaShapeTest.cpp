/*
 * CircularAreaShapeTest.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: loshult
 */

#include "gtest/gtest.h"
#include "server/zone/objects/area/areashapes/CircularAreaShape.h"

namespace server {
namespace zone {
namespace objects {
namespace area {
namespace areashapes {
namespace test {

class CircularAreaShapeTest : public ::testing::Test {
public:

	CircularAreaShapeTest() {
		// Perform creation setup here.
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
	Reference<CircularAreaShape*> circularAreaShape = new CircularAreaShape();
	EXPECT_EQ(circularAreaShape->getAreaCenter().getX(), 0);
	EXPECT_EQ(circularAreaShape->getAreaCenter().getY(), 0);
	EXPECT_EQ(circularAreaShape->getAreaCenter().getZ(), 0);
}

TEST_F(CircularAreaShapeTest, CircularAreaShapeHasRadiusEqualToZeroAfterCreation) {
	Reference<CircularAreaShape*> circularAreaShape = new CircularAreaShape();
	EXPECT_EQ(circularAreaShape->getRadius(), 0);
}

TEST_F(CircularAreaShapeTest, CircularAreaShapeHasRadiusSquareEqualToZeroAfterCreation) {
	Reference<CircularAreaShape*> circularAreaShape = new CircularAreaShape();
	EXPECT_EQ(circularAreaShape->getRadius2(), 0);
}

}
}
}
}
}
}
