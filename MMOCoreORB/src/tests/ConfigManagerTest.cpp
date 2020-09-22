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

	configManager->setFloat("Core3.TestFloat", 12345.6f);
	auto tmp3 = configManager->getFloat("Core3.TestFloat", 0.0);
	ASSERT_NE(tmp3, 0.0);

	configManager->setString("Core3.TestString", "This is a test");
	auto tmp4 = configManager->getString("Core3.TestString", "failed");
	ASSERT_EQ(tmp4, "This is a test");
}

TEST_F(ConfigManagerTest, CacheTest) {
	Timer timer;
	int totalReads = 1000000;

	configManager->setBool("Core3.TestBool", true);

	timer.start();
	for (int i = 0; i < totalReads; i++) {
		auto result = configManager->getBool("Core3.TestBool", false);
		ASSERT_TRUE(result);
	}
	timer.stop();

	auto msBase = (timer.getElapsedTime() / 1000000.0f);

	std::cerr << "[>>>>>>>>>>] " << totalReads << " base reads in " << msBase << " ms" << std::endl;

	auto tmp1 = configManager->setPvpMode(true);
	ASSERT_TRUE(tmp1);
	ASSERT_EQ(configManager->getUsageCounter("Core3.PvpMode"), 1);

	auto counter_start = configManager->getUsageCounter("Core3.PvpMode");

	timer.clear();
	timer.start();
	for (int i = 0; i < totalReads; i++) {
		auto result = configManager->getPvpMode();
		ASSERT_TRUE(result);
	}
	timer.stop();

	auto msCached = (timer.getElapsedTime() / 1000000.0f);

	std::cerr << "[>>>>>>>>>>] " << totalReads << " cached reads in " << msCached << " ms (" << (int)(msBase / msCached) << " x faster)" << std::endl;

	auto counter_end = configManager->getUsageCounter("Core3.PvpMode");

	ASSERT_EQ(counter_end, counter_start + 1);

	ASSERT_TRUE((msBase / msCached) > 5);
}

TEST_F(ConfigManagerTest, JSONTest) {
	String errMsg;
	StringBuffer buf;
	auto version_start = configManager->getConfigVersion();

	buf << "{"
		<< "  \"Core3\": {"
		<< "    \"TestBool\": false,"
		<< "    \"TestInt\": 87654321,"
		<< "    \"TestFloat\": 6.54321,"
		<< "    \"TestString\": \"tset a si sihT\","
		<< "    \"TestArray\": [ \"one\", \"two\", \"three\", \"four\", \"five\" ]"
		<< "  }"
		<< "}"
		;

	auto json = buf.toString();

	// Check failure when updateOnly = True
	std::cerr << "[>>>>>>>>>>] Expect Error about key not existing..." << std::endl;

	auto result = configManager->parseConfigJSON(json, errMsg, true);

	ASSERT_TRUE(!result);

	ASSERT_TRUE(errMsg.contains("Core3.Test"));

	// Should have been zero changes to values
	ASSERT_TRUE(version_start == configManager->getConfigVersion());

	errMsg = "";

	std::cerr << "[>>>>>>>>>>] Check with updateOnly = false" << std::endl;

	auto result2 = configManager->parseConfigJSON(json, errMsg, false);

	if (!result2) {
		std::cerr << "[   FAILED ] " << errMsg.toCharArray() << std::endl;
	}

	ASSERT_TRUE(result2);

	ASSERT_TRUE(errMsg.isEmpty());

	auto tmp1 = configManager->getInt("Core3.TestInt", 99999);
	ASSERT_EQ(tmp1, 87654321);

	auto tmp2 = configManager->getBool("Core3.TestBool", true);
	ASSERT_TRUE(!tmp2);

	auto tmp3 = configManager->getFloat("Core3.TestFloat", 0.0);
	ASSERT_EQ(tmp3, 6.54321f);

	auto tmp4 = configManager->getString("Core3.TestString", "failed");
	ASSERT_EQ(tmp4, "tset a si sihT");

	auto tmp5 = configManager->getStringVector("Core3.TestArray");
	ASSERT_TRUE(tmp5.get(0) == "one");
	ASSERT_TRUE(tmp5.get(1) == "two");
	ASSERT_TRUE(tmp5.get(2) == "three");
	ASSERT_TRUE(tmp5.get(3) == "four");
	ASSERT_TRUE(tmp5.get(4) == "five");

	auto version_end = configManager->getConfigVersion();

	// Version should increment everytime a value is changed
	ASSERT_TRUE(version_end > version_start);
}

TEST_F(ConfigManagerTest, DumpConfig) {
	configManager->dumpConfig(false);
}
