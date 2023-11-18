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

		convertList();
	}

	void TearDown() {
		// Perform clean up of common constructs here.
		processServer = nullptr;
		zoneServer = nullptr;
		nameManager = nullptr;
	}

	void convertList() {
		File* file = new File("scripts/managers/name/regex_words.txt");
		FileReader* reader = new FileReader(file);

		File* tableFile = new File("scripts/managers/name/test_list.lua");
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

TEST_F(NameManagerTest, CreatureNamesTest) {
	bool passed = true;

	Timer timer;
	timer.start();

	String name = "";

	for (int i = 0; i < iterations; ++i) {
		name = nameManager->makeCreatureName();

		if (name == "") {
			passed = false;
			break;
		}
	}

	uint64 stopTime = timer.stopMs();

	nameManager->info(true) << "NameManager CreatureNamesTest - Total Words: " << iterations << " Total Time: " << stopTime << "ms Avg Per Word: " << (stopTime / (iterations * 1.00f)) << "ms";

	ASSERT_TRUE(passed);
}

TEST_F(NameManagerTest, ResourceNamesTest) {
	bool passed = true;

	Timer timer;
	timer.start();

	String name = "";

	for (int i = 0; i < iterations; ++i) {
		name = nameManager->generateResourceName("plain_resource");

		if (name == "") {
			passed = false;
			break;
		}
	}

	uint64 stopTime = timer.stopMs();

	nameManager->info(true) << "NameManager ResourceNamesTest - Total Words: " << iterations << " Total Time: " << stopTime << "ms Avg Per Word: " << (stopTime / (iterations * 1.00f)) << "ms";

	ASSERT_TRUE(passed);
}
/*
TEST_F(NameManagerTest, NameFilterTest) {
	Lua* lua = new Lua();
	lua->init();

	Vector<String> testWords;

	if (lua->runFile("scripts/managers/name/test_list.lua")) {
		LuaObject luaObject = lua->getGlobalObject("testTable");

		if (luaObject.isValidTable()) {
			for(int i = 1; i <= luaObject.getTableSize(); ++i) {
				String testName = luaObject.getStringAt(i);

				testWords.add(testName);
			}
		}

		luaObject.pop();

		delete lua;
		lua = nullptr;
	}

	Timer timer;
	timer.start();

	int count = 0;

	// Run name filter check on List
	for (String word : testWords) {
		int result = nameManager->checkNamingFilter(word);

		count++;

		if (result == NameManagerResult::ACCEPTED)
			nameManager->info(true) << "Failed to filter: " << word;

		EXPECT_TRUE(result != 7); // NameManagerResult::ACCEPTED
	}

	uint64 stopTime = timer.stopMs();

	nameManager->info(true) << "NameManager NameFilterTest - Total Words: " << count << " Total Time: " << stopTime << "ms Avg Per Word: " << (stopTime / (count * 1.00f)) << "ms";
}
*/