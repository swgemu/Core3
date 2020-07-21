#include "gtest/gtest.h"
#include "engine/util/u3d/Quaternion.h"

class QuaternionTest : public ::testing::Test {
public:

	QuaternionTest() {
		// Perform creation setup here.
	}

	~QuaternionTest() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};

#define EXPECT_VECTOR3_EQ(val1, val2) \
    EXPECT_FLOAT_EQ(val1.getX(), val2.getX()); \
    EXPECT_FLOAT_EQ(val1.getY(), val2.getY()); \
    EXPECT_FLOAT_EQ(val1.getZ(), val2.getZ())

TEST_F(QuaternionTest, RingAreaShapeHasItsCenterAtZeroZeroZeroAfterCreation) {
    Quaternion v = Quaternion(0, 1, 0, 0);

	// No rotation.
    v.rotate(Vector3(0, 1, 0), 0);
	EXPECT_VECTOR3_EQ(v, Vector3(1, 0, 0));

	// Rotate four times in 90 degree increments, a full turn.
    v.rotate(Vector3(0, 1, 0), 90);
	EXPECT_VECTOR3_EQ(v, Vector3(0, 0, -1));
    v.rotate(Vector3(0, 1, 0), 90);
	EXPECT_VECTOR3_EQ(v, Vector3(-1, 0, 0));
    v.rotate(Vector3(0, 1, 0), 90);
	EXPECT_VECTOR3_EQ(v, Vector3(0, 0, 1));
    v.rotate(Vector3(0, 1, 0), 90);
	EXPECT_VECTOR3_EQ(v, Vector3(1, 0, 0));

	// Tests taken from http://www.tobynorris.com/work/prog/csharp/quatview/help/case_1.htm
	v = Quaternion(0, 0.6, 0.8, 0);
	v.rotate(Vector3(0, 0, 1), -30);
	EXPECT_VECTOR3_EQ(v, Vector3(0.91961521, 0.3928203, 0));
	v.rotate(Vector3(0, 0, 1), 60);
	EXPECT_VECTOR3_EQ(v, Vector3(0.11961526, 0.99282026, 0));
}