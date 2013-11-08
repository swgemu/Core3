/*
 * CommandLuaTest.cpp
 *
 *  Created on: 20/10/2013
 *      Author: victor
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "server/zone/managers/templates/DataArchiveStore.h"
#include "server/zone/managers/objectcontroller/command/CommandConfigManager.h"
#include "server/zone/managers/objectcontroller/command/CommandList.h"
#include "server/conf/ConfigManager.h"

class CommandLuaTest : public ::testing::Test {
public:

	CommandLuaTest() {
		// Perform creation setup here.
		ConfigManager::instance()->loadConfigData();
		DataArchiveStore::instance()->loadTres(ConfigManager::instance()->getTrePath(), ConfigManager::instance()->getTreFiles());
	}

	~CommandLuaTest() {
	}

	void SetUp() {
		// Perform setup of common constructs here.
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};

TEST_F(CommandLuaTest, LoadCommandLuas) {
	CommandConfigManager* man = new CommandConfigManager(NULL);
	CommandList* list = new CommandList();

	man->registerSpecialCommands(list);
	man->loadSlashCommandsFile();


	ASSERT_EQ(CommandConfigManager::ERROR_CODE, 0);

	delete man;
}
