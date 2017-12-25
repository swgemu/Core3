#include "gtest/gtest.h"
#include "server/zone/objects/area/areashapes/RingAreaShape.h"

namespace server {
namespace zone {
namespace objects {
namespace area {
namespace areashapes {
namespace test {

class RingAreaShapeTest : public ::testing::Test {
public:

	RingAreaShapeTest() {
		// Perform creation setup here.
	}

	~RingAreaShapeTest() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};

TEST_F(RingAreaShapeTest, RingAreaShapeHasItsCenterAtZeroZeroZeroAfterCreation) {
	Reference<RingAreaShape*> ringAreaShape = new RingAreaShape();
	EXPECT_EQ(ringAreaShape->getAreaCenter().getX(), 0);
	EXPECT_EQ(ringAreaShape->getAreaCenter().getY(), 0);
	EXPECT_EQ(ringAreaShape->getAreaCenter().getZ(), 0);
}

TEST_F(RingAreaShapeTest, RingAreaShapeHasInnerRadiusEqualToZeroAfterCreation) {
	Reference<RingAreaShape*> ringAreaShape = new RingAreaShape();
	EXPECT_EQ(ringAreaShape->getInnerRadius(), 0);
}

TEST_F(RingAreaShapeTest, RingAreaShapeHasOuterRadiusEqualToZeroAfterCreation) {
	Reference<RingAreaShape*> ringAreaShape = new RingAreaShape();
	EXPECT_EQ(ringAreaShape->getOuterRadius(), 0);
}

TEST_F(RingAreaShapeTest, RingAreaShapeHasInnerRadiusSquareEqualToZeroAfterCreation) {
	Reference<RingAreaShape*> ringAreaShape = new RingAreaShape();
	EXPECT_EQ(ringAreaShape->getInnerRadius2(), 0);
}

TEST_F(RingAreaShapeTest, RingAreaShapeHasOuterRadiusSquareEqualToZeroAfterCreation) {
	Reference<RingAreaShape*> ringAreaShape = new RingAreaShape();
	EXPECT_EQ(ringAreaShape->getOuterRadius2(), 0);
}

}
}
}
}
}
}
