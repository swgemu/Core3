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
#include "conf/ConfigManager.h"

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

	ASSERT_EQ(*lua_version(L), 503) << "Wrong version of Lua Installed: " << *lua_version(L) << ". Required version: " << 503;
	EXPECT_EQ(DirectorManager::instance()->runScreenPlays(), 0);
}

#endif /* BASICSCREENPLAYTEST_CPP_ */
