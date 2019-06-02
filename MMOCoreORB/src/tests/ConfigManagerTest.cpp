/*
 * ConfigManagerTest.cpp
 *
 *  Created on: 05/19/2019
 *      Author: lordkator
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "conf/ConfigManager.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::TypedEq;
using ::testing::An;

class ConfigManagerTest : public ::testing::Test {
protected:
	ConfigManager* configManager = nullptr;
public:
	ConfigManagerTest() {
		configManager = ConfigManager::instance();
		configManager->loadConfigData();
	}

	~ConfigManagerTest() {
		configManager = nullptr;
	}

	void SetUp() {
	}

	void TearDown() {
	}
};

TEST_F(ConfigManagerTest, StringTest) {
	auto tmp1 = configManager->getString("Core3.InactiveAccountText", "Account Disabled");
	auto tmp2 = configManager->getInactiveAccountText();
	ASSERT_EQ(tmp1, tmp2);
}

TEST_F(ConfigManagerTest, BoolTest) {
	auto tmp1 = configManager->getMakeZone();
	ASSERT_TRUE(tmp1);
}

TEST_F(ConfigManagerTest, Int16Test) {
	const uint16& dbPort = configManager->getDBPort();
	ASSERT_EQ(dbPort, 3306);
}

TEST_F(ConfigManagerTest, EnabledZones) {
	auto enabledZones = configManager->getEnabledZones();
	ASSERT_TRUE(enabledZones.size() != 0);

	std::cerr << "[>>>>>>>>>>] ZonesEnabled = { '";

	for (int i = 0;i < enabledZones.size(); i++) {
		std::cerr << (i == 0 ? "" : "', '") <<  enabledZones.get(i).toCharArray();
	}

	std::cerr << "' }" << std::endl;
}

TEST_F(ConfigManagerTest, TreFiles) {
	auto treFilesToLoad = configManager->getTreFiles();
	ASSERT_TRUE(treFilesToLoad.size() != 0);

	// Make sure it's not sorted
	ASSERT_TRUE(treFilesToLoad.get(0) == "default_patch.tre");

	std::cerr << "[>>>>>>>>>>] TreFiles = { '";

	for (int i = 0;i < treFilesToLoad.size(); i++) {
		std::cerr << (i == 0 ? "" : "', '") <<  treFilesToLoad.get(i).toCharArray();
	}

	std::cerr << "' }" << std::endl;
}

TEST_F(ConfigManagerTest, SetTest) {
	auto curVal = configManager->isProgressMonitorActivated();
	configManager->setProgressMonitors(!curVal);
	auto newVal = configManager->isProgressMonitorActivated();
	ASSERT_TRUE(curVal != newVal);
}

TEST_F(ConfigManagerTest, DynamicTest) {
	configManager->setInt("Core3.TestInt", 12345);
	auto tmp1 = configManager->getInt("Core3.TestInt", 99999);
	ASSERT_EQ(tmp1, 12345);

	configManager->setBool("Core3.TestBool", true);
	auto tmp2 = configManager->getBool("Core3.TestBool", false);
	ASSERT_TRUE(tmp2);

	configManager->setFloat("Core3.TestFloat", 12345.6);
	auto tmp3 = configManager->getFloat("Core3.TestFloat", 0.0);
	ASSERT_NE(tmp3, 0.0);

	configManager->setString("Core3.TestString", "This is a test");
	auto tmp4 = configManager->getString("Core3.TestString", "failed");
	ASSERT_EQ(tmp4, "This is a test");
}

TEST_F(ConfigManagerTest, DumpConfig) {
	configManager->dumpConfig(false);
}
