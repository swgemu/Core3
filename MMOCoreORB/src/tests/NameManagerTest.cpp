/*
 * NameManagerTest.cpp
 *
 * Created on: 11/17/2023
 * Author: hakry
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "conf/ConfigManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/name/NameManager.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::TypedEq;
using ::testing::An;

class NameManagerTest : public ::testing::Test {
protected:
	Reference<ZoneServer*> zoneServer;
	Reference<ZoneProcessServer*> processServer;
	NameManager* nameManager;

	int iterations;

public:
	NameManagerTest() {
	}

	~NameManagerTest() {
	}

	void SetUp() {
		// Perform setup of common constructs here.
		auto configManager = ConfigManager::instance();

		configManager->loadConfigData();
		configManager->setProgressMonitors(false);

		zoneServer = new ZoneServer(configManager);
		processServer = new ZoneProcessServer(zoneServer);

		nameManager = new NameManager(processServer);

		// Iteration count for NPC and resource names
		iterations = 1000;

		convertNames();
	}

	void TearDown() {
		// Perform clean up of common constructs here.
		processServer = nullptr;
		zoneServer = nullptr;
		nameManager = nullptr;
	}

	void convertNames() {
		File* file = new File("scripts/managers/name/convert_names.txt");
		FileReader* reader = new FileReader(file);

		File* tableFile = new File("scripts/managers/name/test_names.lua");
		FileWriter* tableWriter = new FileWriter(tableFile);

		tableWriter->writeLine("testTable = {");

		String line;

		while(reader->readLine(line)) {
			StringBuffer newLine;
			newLine << "	\"" << line << "\",";

			String newName = newLine.toString().replaceAll("\n", "");
			tableWriter->writeLine(newName);
		}

		reader->close();

		tableWriter->writeLine("}");
		tableWriter->close();

		delete reader;
		delete file;

		reader = nullptr;
		file = nullptr;

		delete tableWriter;
		delete tableFile;

		tableWriter = nullptr;
		tableFile = nullptr;
	}
};

TEST_F(NameManagerTest, CreatureNames) {
	bool passed = true;

	String name;

	for (int i = 0; i < iterations; ++i) {
		name = nameManager->makeCreatureName();

		if (name == "") {
			passed = false;
			break;
		}
	}

	ASSERT_EQ(passed, true);
}

TEST_F(NameManagerTest, ResourceNames) {
	bool passed = true;

	String name;

	for (int i = 0; i < iterations; ++i) {
		name = nameManager->generateResourceName("plain_resource");

		if (name == "") {
			passed = false;
			break;
		}
	}

	ASSERT_EQ(passed, true);
}

TEST_F(NameManagerTest, ProfanityTest) {
	bool filteredWords = false;

	Lua* lua = new Lua();
	lua->init();

	if (lua->runFile("scripts/managers/name/test_names.lua")) {
		Vector<String> testNames;

		LuaObject luaObject = lua->getGlobalObject("testTable");

		if (luaObject.isValidTable()) {
			for(int i = 1; i <= luaObject.getTableSize(); ++i) {
				String testName = luaObject.getStringAt(i);

				testNames.add(testName);
			}
		}

		luaObject.pop();

		delete lua;
		lua = nullptr;

		// Run test on List
		for (String name : testNames) {
			if (nameManager->validateReservedNames(name, NameManagerResult::DECLINED_PROFANE) == NameManagerResult::ACCEPTED)
				continue;

			filteredWords = true;

			//nameManager->info(true) << "Failed: " << name << " for profanity.";
		}
	}

	ASSERT_EQ(filteredWords, true);
}

TEST_F(NameManagerTest, DeveloperTest) {
	bool filteredWords = false;

	Lua* lua = new Lua();
	lua->init();

	if (lua->runFile("scripts/managers/name/test_names.lua")) {
		Vector<String> testNames;

		LuaObject luaObject = lua->getGlobalObject("testTable");

		if (luaObject.isValidTable()) {
			for(int i = 1; i <= luaObject.getTableSize(); ++i) {
				String testName = luaObject.getStringAt(i);

				testNames.add(testName);
			}
		}

		luaObject.pop();

		delete lua;
		lua = nullptr;

		// Run test on List
		for (String name : testNames) {
			if (nameManager->validateReservedNames(name, NameManagerResult::DECLINED_DEVELOPER) == NameManagerResult::ACCEPTED)
				continue;

			filteredWords = true;

			//nameManager->info(true) << "Failed: " << name << " for Staff reserved.";
		}
	}

	ASSERT_EQ(filteredWords, true);
}

TEST_F(NameManagerTest, FictionalTest) {
	bool filteredWords = false;

	Lua* lua = new Lua();
	lua->init();

	if (lua->runFile("scripts/managers/name/test_names.lua")) {
		Vector<String> testNames;

		LuaObject luaObject = lua->getGlobalObject("testTable");

		if (luaObject.isValidTable()) {
			for(int i = 1; i <= luaObject.getTableSize(); ++i) {
				String testName = luaObject.getStringAt(i);

				testNames.add(testName);
			}
		}

		luaObject.pop();

		delete lua;
		lua = nullptr;

		// Run test on List
		for (String name : testNames) {
			if (nameManager->validateReservedNames(name, NameManagerResult::DECLINED_FICT_RESERVED) == NameManagerResult::ACCEPTED)
				continue;

			filteredWords = true;

			//nameManager->info(true) << "Failed: " << name << " for fictional reserved.";
		}
	}

	ASSERT_EQ(filteredWords, true);
}