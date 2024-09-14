/*
 * AreaShapeTests.cpp
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"
#include "server/zone/objects/area/areashapes/CircularAreaShape.h"
#include "server/zone/objects/area/areashapes/RingAreaShape.h"
#include "server/zone/objects/area/areashapes/CuboidAreaShape.h"
#include "server/zone/objects/area/areashapes/SphereAreaShape.h"

using ::testing::_;
using ::testing::Return;

namespace server {
namespace zone {
namespace objects {
namespace area {
namespace areashapes {
namespace test {

class AreaShapeTests : public ::testing::Test {
public:
	AreaShapeTests() {
		// Perform creation setup here.
	}

	~AreaShapeTests() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};

// Rectangular Area
TEST_F(AreaShapeTests, RectangularAreaShapeHasItsCenterAtZeroZeroZeroAfterCreation) {
	Reference<RectangularAreaShape*> rectangularAreaShape = new RectangularAreaShape();

	EXPECT_EQ(rectangularAreaShape->getAreaCenter().getX(), 0);
	EXPECT_EQ(rectangularAreaShape->getAreaCenter().getY(), 0);
	EXPECT_EQ(rectangularAreaShape->getAreaCenter().getZ(), 0);
}

TEST_F(AreaShapeTests, RectangularAreaShapeHasRadiusEqualToZeroAfterCreation) {
	Reference<RectangularAreaShape*> rectangularAreaShape = new RectangularAreaShape();

	EXPECT_EQ(rectangularAreaShape->getRadius(), 0);
}

TEST_F(AreaShapeTests, RectangularAreaShapeShouldCallContainsPointOnTheAreaToCheckIntersectionWith) {
	Reference<RectangularAreaShape*> rectangularAreaShape = new RectangularAreaShape();
	Reference<MockAreaShape*> intersectsWith = new MockAreaShape();

	EXPECT_FALSE(rectangularAreaShape->intersectsWith(intersectsWith));
}

// Circular Area
TEST_F(AreaShapeTests, CircularAreaShapeHasItsCenterAtZeroZeroZeroAfterCreation) {
	Reference<CircularAreaShape*> circularAreaShape = new CircularAreaShape();
	EXPECT_EQ(circularAreaShape->getAreaCenter().getX(), 0);
	EXPECT_EQ(circularAreaShape->getAreaCenter().getY(), 0);
	EXPECT_EQ(circularAreaShape->getAreaCenter().getZ(), 0);
}

TEST_F(AreaShapeTests, CircularAreaShapeHasRadiusEqualToZeroAfterCreation) {
	Reference<CircularAreaShape*> circularAreaShape = new CircularAreaShape();
	EXPECT_EQ(circularAreaShape->getRadius(), 0);
}

TEST_F(AreaShapeTests, CircularAreaShapeHasRadiusSquareEqualToZeroAfterCreation) {
	Reference<CircularAreaShape*> circularAreaShape = new CircularAreaShape();
	EXPECT_EQ(circularAreaShape->getRadius2(), 0);
}

// Ring Area
TEST_F(AreaShapeTests, RingAreaShapeHasItsCenterAtZeroZeroZeroAfterCreation) {
	Reference<RingAreaShape*> ringAreaShape = new RingAreaShape();
	EXPECT_EQ(ringAreaShape->getAreaCenter().getX(), 0);
	EXPECT_EQ(ringAreaShape->getAreaCenter().getY(), 0);
	EXPECT_EQ(ringAreaShape->getAreaCenter().getZ(), 0);
}

TEST_F(AreaShapeTests, RingAreaShapeHasInnerRadiusEqualToZeroAfterCreation) {
	Reference<RingAreaShape*> ringAreaShape = new RingAreaShape();
	EXPECT_EQ(ringAreaShape->getInnerRadius(), 0);
}

TEST_F(AreaShapeTests, RingAreaShapeHasOuterRadiusEqualToZeroAfterCreation) {
	Reference<RingAreaShape*> ringAreaShape = new RingAreaShape();
	EXPECT_EQ(ringAreaShape->getOuterRadius(), 0);
}

TEST_F(AreaShapeTests, RingAreaShapeHasInnerRadiusSquareEqualToZeroAfterCreation) {
	Reference<RingAreaShape*> ringAreaShape = new RingAreaShape();
	EXPECT_EQ(ringAreaShape->getInnerRadius2(), 0);
}

TEST_F(AreaShapeTests, RingAreaShapeHasOuterRadiusSquareEqualToZeroAfterCreation) {
	Reference<RingAreaShape*> ringAreaShape = new RingAreaShape();
	EXPECT_EQ(ringAreaShape->getOuterRadius2(), 0);
}

// Sphere Area
TEST_F(AreaShapeTests, SphereShapeCreationTest) {
	Reference<SphereAreaShape*> sphereShape = new SphereAreaShape();

	EXPECT_EQ(sphereShape->getAreaCenter().getX(), 0);
	EXPECT_EQ(sphereShape->getAreaCenter().getY(), 0);
	EXPECT_EQ(sphereShape->getAreaCenter().getZ(), 0);
}

TEST_F(AreaShapeTests, SphereShapeRadiusTest) {
	Reference<SphereAreaShape*> sphereShape = new SphereAreaShape();

	EXPECT_EQ(sphereShape->getRadius(), 0);
	EXPECT_EQ(sphereShape->getRadius2(), 0);

	Locker lock(sphereShape);

	float newRadius = 1200;

	sphereShape->setRadius(newRadius);

	EXPECT_EQ(sphereShape->getRadius(), newRadius);
	EXPECT_EQ(sphereShape->getRadius2(), (newRadius * newRadius));
}

TEST_F(AreaShapeTests, SphereShapeContainsTest) {
	Reference<SphereAreaShape*> sphereShape = new SphereAreaShape();

	Locker lock(sphereShape);

	float newRadius = 1200;

	sphereShape->setRadius(newRadius);

	lock.release();

	EXPECT_TRUE(sphereShape->containsPoint(0, -1000, 0));

	EXPECT_TRUE(sphereShape->containsPoint(-500, -500, 0));

	EXPECT_TRUE(sphereShape->containsPoint(500, 500, 500));
}

// Cuboid Area
TEST_F(AreaShapeTests, CuboidShapeCreationTest) {
	Reference<CuboidAreaShape*> cuboidShape = new CuboidAreaShape();

	Vector3 centerPos = cuboidShape->getAreaCenter();

	EXPECT_EQ(centerPos.getX(), 0);
	EXPECT_EQ(centerPos.getY(), 0);
	EXPECT_EQ(centerPos.getZ(), 0);

	Locker lock(cuboidShape);

	cuboidShape->setDimensions(1000, 750, 500);

	lock.release();

	float length = cuboidShape->getLength();
	float width = cuboidShape->getWidth();
	float height = cuboidShape->getHeight();

	EXPECT_EQ(length, 1000);
	EXPECT_EQ(width, 750);
	EXPECT_EQ(height, 500);

	float minX = centerPos.getX() - (length / 2);
	float maxX = centerPos.getX() + (length / 2);
	float minY = centerPos.getY() - (width / 2);
	float maxY = centerPos.getY() + (width / 2);
	float minZ = centerPos.getZ() - (height / 2);
	float maxZ = centerPos.getZ() + (height / 2);

	EXPECT_EQ(cuboidShape->getMinX(), minX);
	EXPECT_EQ(cuboidShape->getMaxX(), minX);
	EXPECT_EQ(cuboidShape->getMinZ(), minX);
	EXPECT_EQ(cuboidShape->getMaxZ(), minX);
	EXPECT_EQ(cuboidShape->getMinY(), minX);
	EXPECT_EQ(cuboidShape->getMaxY(), minX);
}

TEST_F(AreaShapeTests, CuboidShapeContainsTest) {
	Reference<CuboidAreaShape*> cuboidShape = new CuboidAreaShape();

	Locker lock(cuboidShape);

	cuboidShape->setDimensions(1000, 750, 500);

	lock.release();

	EXPECT_TRUE(cuboidShape->containsPoint(-400, 0, 0));

	EXPECT_TRUE(cuboidShape->containsPoint(-400, 240, 370));

	EXPECT_TRUE(cuboidShape->containsPoint(400, -240, -370));
}

}
}
}
}
}
}
