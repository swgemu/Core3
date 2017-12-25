/*
 * BasicTerrainTest.cpp
 *
 *  Created on: 06/09/2013
 *      Author: victor
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "templates/manager/DataArchiveStore.h"
#include "terrain/ProceduralTerrainAppearance.h"
#include "terrain/SpaceTerrainAppearance.h"
#include "conf/ConfigManager.h"

class BasicTerrainTest : public ::testing::Test {
public:

	BasicTerrainTest() {
		// Perform creation setup here.
		ConfigManager::instance()->loadConfigData();
		DataArchiveStore::instance()->loadTres(ConfigManager::instance()->getTrePath(), ConfigManager::instance()->getTreFiles());
	}

	~BasicTerrainTest() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
		//DataArchiveStore
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};

TEST_F(BasicTerrainTest, LoadTestTerrainTest) {
	IffStream* stream = DataArchiveStore::instance()->openIffFile("terrain/test_terrain.trn");

	ASSERT_TRUE(stream != NULL);

	ProceduralTerrainAppearance terrain;

	terrain.readObject(stream);

	delete stream;

	float x = -238;
	float y = -166;
	float res = terrain.getHeight(x, y);

	EXPECT_NEAR(res, 30.367649, 0.01);

	res = terrain.getHeight(-45.1, 49.0);

	EXPECT_NEAR(res, 83.3, 0.1);

	//printf("height at %f, %f is:%f\n", x, y, res);
}

TEST_F(BasicTerrainTest, LoadTestSpaceTerrain) {
	IffStream* stream = DataArchiveStore::instance()->openIffFile("terrain/space_corellia.trn");

	ASSERT_TRUE(stream != NULL);

	SpaceTerrainAppearance terrain;

	terrain.readObject(stream);

	delete stream;
}
