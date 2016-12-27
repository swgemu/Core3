/*
 * TerrainManagerTest.cpp
 *
 *  Created on: Feb 22, 2014
 *      Author: swgemu
 */

#include "terrain/manager/TerrainManager.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::Return;

namespace terrain {
namespace manager {
namespace tests {

class TerrainManagerTest : public ::testing::Test, public Logger {
public:
	MockTerrainManager* terrainManager;

	TerrainManagerTest() : Logger("TerrainManagerTest"), terrainManager(NULL) {
		// Perform creation setup here.
	}

	~TerrainManagerTest() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
		terrainManager = new MockTerrainManager();
	}

	void TearDown() {
		// Perform clean up of common constructs here.
		delete terrainManager;
	}
};

TEST_F(TerrainManagerTest, GetHighestHeightShouldReturnTheHeighestPointInTheArea) {
	EXPECT_CALL(*terrainManager, getHeight(_, _)).Times(100).WillOnce(Return(1.0)).WillOnce(Return(-2.0)).WillOnce(Return(4.0)).WillRepeatedly(Return(-3.0));

	EXPECT_EQ(4.0, terrainManager->getHighestHeight(10, 10, 20, 20));
}

TEST_F(TerrainManagerTest, GetLowestHeightShouldReturnTheLowestPointInTheArea) {
	EXPECT_CALL(*terrainManager, getHeight(_, _)).Times(100).WillOnce(Return(1.0)).WillOnce(Return(-2.0)).WillOnce(Return(4.0)).WillRepeatedly(Return(-3.0));

	EXPECT_EQ(-3.0, terrainManager->getLowestHeight(10, 10, 20, 20));
}

TEST_F(TerrainManagerTest, GetHighestHeightDifferenceShouldReturnTheHeightDifference) {
	EXPECT_CALL(*terrainManager, getHeight(_, _)).Times(200).WillOnce(Return(1.0)).WillOnce(Return(-2.0)).WillOnce(Return(4.0)).WillRepeatedly(Return(-3.0));

	EXPECT_EQ(7.0, terrainManager->getHighestHeightDifference(10, 10, 20, 20));
}

}
}
}
