/*
 * BasicScreenPlayTest.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: TheAnswer
 */

#ifndef BASICSCREENPLAYTEST_CPP_
#define BASICSCREENPLAYTEST_CPP_

#include "gtest/gtest.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/conf/ConfigManager.h"

class BasicScreenPlayTest : public ::testing::Test {
public:

	BasicScreenPlayTest() {
		// Perform creation setup here.
		ConfigManager::instance()->loadConfigData();
	}

	~BasicScreenPlayTest() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};

TEST_F(BasicScreenPlayTest, ScreenPlayLuaInitialize) {
	DirectorManager::DEBUG_MODE = 1;

	lua_State* L = DirectorManager::instance()->getLuaInstance()->getLuaState();
	double ver = *lua_version(L);
	double reqVer = 503;

	ASSERT_EQ(ver, reqVer) << "Wrong version of Lua Installed: " << ver << ". Required version: " << reqVer;
	EXPECT_EQ(DirectorManager::instance()->runScreenPlays(), 0);
}

#endif /* BASICSCREENPLAYTEST_CPP_ */
