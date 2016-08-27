/*
 * RectangularAreaShapeTest.cpp
 *
 *  Created on: Jul 29, 2013
 *      Author: loshult
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"

using ::testing::_;
using ::testing::Return;

namespace server {
namespace zone {
namespace objects {
namespace area {
namespace areashapes {
namespace test {

class RectangularAreaShapeTest : public ::testing::Test {
public:
	Reference<RectangularAreaShape*> rectangularAreaShape;
	Reference<MockAreaShape*> intersectsWith;

	RectangularAreaShapeTest() {
		// Perform creation setup here.
	}

	~RectangularAreaShapeTest() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
		rectangularAreaShape = new RectangularAreaShape();
		intersectsWith = new MockAreaShape();
	}

	void TearDown() {
		// Perform clean up of common constructs here.
		rectangularAreaShape = NULL;
		intersectsWith = NULL;
	}
};

TEST_F(RectangularAreaShapeTest, RectangularAreaShapeHasItsCenterAtZeroZeroZeroAfterCreation) {
	EXPECT_EQ(rectangularAreaShape->getAreaCenter().getX(), 0);
	EXPECT_EQ(rectangularAreaShape->getAreaCenter().getY(), 0);
	EXPECT_EQ(rectangularAreaShape->getAreaCenter().getZ(), 0);
}

TEST_F(RectangularAreaShapeTest, RectangularAreaShapeHasRadiusEqualToZeroAfterCreation) {
	EXPECT_EQ(rectangularAreaShape->getRadius(), 0);
}

TEST_F(RectangularAreaShapeTest, RectangularAreaShapeShouldCallContainsPointOnTheAreaToCheckIntersectionWith) {
	EXPECT_CALL(*intersectsWith, containsPoint(_)).Times(1);

	EXPECT_FALSE(rectangularAreaShape->intersectsWith(intersectsWith));
}

TEST_F(RectangularAreaShapeTest, IntersectsWithShouldReturnTrueIfContainsPointReturnsTrueFromTheAreaShape) {
	EXPECT_CALL(*intersectsWith, containsPoint(_)).WillOnce(Return(true));

	EXPECT_TRUE(rectangularAreaShape->intersectsWith(intersectsWith));
}

}
}
}
}
}
}
