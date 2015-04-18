/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "../JediManager.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "engine/lua/MockLua.h"
#include "engine/lua/MockLuaFunction.h"
#include "server/zone/managers/director/MockDirectorManager.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::TypedEq;
using ::testing::An;

namespace server {
namespace zone {
namespace managers {
namespace jedi {
namespace tests {

class JediManagerTest : public ::testing::Test, public Logger {
public:
	JediManager* jediManager;

	JediManagerTest() : Logger("JediManagerTest"), jediManager(NULL) {
		// Perform creation setup here.
	}

	~JediManagerTest() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
		jediManager = new JediManager();
		jediManager->setJediManagerName("JediManager");
	}

	void TearDown() {
		// Perform clean up of common constructs here.
		delete jediManager;
	}

	void constructorDefaults(MockLua& mockLua) {
		EXPECT_CALL(mockLua, runFile(_)).Times(AnyNumber());
		EXPECT_CALL(mockLua, getGlobalInt(_)).Times(AnyNumber());
		EXPECT_CALL(mockLua, getGlobalString(_)).Times(AnyNumber());
		EXPECT_CALL(mockLua, setGlobalInt(_, _)).Times(AnyNumber());
		ON_CALL(mockLua, getGlobalString(_)).WillByDefault(Return(String("")));
	}
};

TEST_F(JediManagerTest, ShouldRunFileJediManagerLuaAtLoadConfiguration) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	EXPECT_CALL(mockLua, runFile(String("scripts/managers/jedi/jedi_manager.lua"))).Times(1);

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldReadTheJediProgressionTypeVariableAtLoadConfigurations) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	EXPECT_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillOnce(Return((int)JediManager::NOJEDIPROGRESSION /* gcc-4.4.5 cast-hack */));

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldRunTheHolocronJediManagerLuaFileIfHolocronJediProgressionIsConfigured) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return((int)JediManager::HOLOGRINDJEDIPROGRESSION /* gcc-4.4.5 cast-hack */));
	EXPECT_CALL(mockLua, runFile(String("scripts/managers/jedi/hologrind/hologrind_jedi_manager.lua"))).Times(1);

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldRunTheVillageJediManagerLuaFileIfVillageJediProgressionIsConfigured) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return((int)JediManager::VILLAGEJEDIPROGRESSION /* gcc-4.4.5 cast-hack */));
	EXPECT_CALL(mockLua, runFile(String("scripts/managers/jedi/village/village_jedi_manager.lua"))).Times(1);

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldReadTheCustomJediProgressionFileStringIfCustomJediProgressionIsConfigured) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return((int)JediManager::CUSTOMJEDIPROGRESSION /* gcc-4.4.5 cast-hack */));
	EXPECT_CALL(mockLua, getGlobalString(String("customJediProgressionFile"))).WillOnce(Return(String("scripts/managers/jedi/custom_jedi_manager.lua")));

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldLoadTheCustomJediProgressionFileIfCustomJediProgressionIsConfigured) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return((int)JediManager::CUSTOMJEDIPROGRESSION /* gcc-4.4.5 cast-hack */));
	EXPECT_CALL(mockLua, getGlobalString(String("customJediProgressionFile"))).WillOnce(Return(String("scripts/managers/jedi/custom_jedi_manager.lua")));
	EXPECT_CALL(mockLua, runFile(String("scripts/managers/jedi/custom_jedi_manager.lua"))).Times(1);

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldReadTheJediProgressionSystemNameAtLoadConfiguration) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return((int)JediManager::HOLOGRINDJEDIPROGRESSION /* gcc-4.4.5 cast-hack */));
	EXPECT_CALL(mockLua, getGlobalString(String("jediManagerName"))).WillOnce(Return(String("HologrindJediManager")));

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, OnPlayerCreatedShouldCallTheOnPlayerCreatedMethodInTheLuaJediManager) {
	MockLua mockLua;
	Reference<MockLuaFunction*> mockLuaFunction = new MockLuaFunction();
	Reference<MockDirectorManager*> mockDirectorManager = new MockDirectorManager();
	Reference<MockCreatureObject*> mockCreatureObject = new MockCreatureObject();

	EXPECT_CALL(*mockDirectorManager, getLuaInstance()).WillOnce(Return(&mockLua));
	EXPECT_CALL(mockLua, createFunction(String("JediManager"), String("onPlayerCreated"), 0)).WillOnce(Return(mockLuaFunction));
	EXPECT_CALL(*mockLuaFunction, addArgument(TypedEq<void*>(mockCreatureObject))).Times(1);
	EXPECT_CALL(*mockLuaFunction, callFunction()).Times(1);

	Reference<DirectorManager*> realDirectorManager = DirectorManager::instance();

	DirectorManager::setSingletonInstance(mockDirectorManager);

	jediManager->onPlayerCreated(mockCreatureObject);

	DirectorManager::setSingletonInstance(realDirectorManager);
}

TEST_F(JediManagerTest, OnPlayerLoggedInShouldCallTheOnPlayerLoggedInMethodInTheLuaJediManager) {
	MockLua mockLua;
	Reference<MockLuaFunction*> mockLuaFunction = new MockLuaFunction();
	Reference<MockDirectorManager*> mockDirectorManager = new MockDirectorManager();
	Reference<MockCreatureObject*> mockCreatureObject = new MockCreatureObject();

	EXPECT_CALL(*mockDirectorManager, getLuaInstance()).WillOnce(Return(&mockLua));
	EXPECT_CALL(mockLua, createFunction(String("JediManager"), String("onPlayerLoggedIn"), 0)).WillOnce(Return(mockLuaFunction));
	EXPECT_CALL(*mockLuaFunction, addArgument(TypedEq<void*>(mockCreatureObject))).Times(1);
	EXPECT_CALL(*mockLuaFunction, callFunction()).Times(1);

	Reference<DirectorManager*> realDirectorManager = DirectorManager::instance();

	DirectorManager::setSingletonInstance(mockDirectorManager);

	jediManager->onPlayerLoggedIn(mockCreatureObject);

	DirectorManager::setSingletonInstance(realDirectorManager);
}

TEST_F(JediManagerTest, OnPlayerLoggedOutShouldCallTheOnPlayerLoggedOutMethodInTheLuaJediManager) {
	MockLua mockLua;
	Reference<MockLuaFunction*> mockLuaFunction = new MockLuaFunction();
	Reference<MockDirectorManager*> mockDirectorManager = new MockDirectorManager();
	Reference<MockCreatureObject*> mockCreatureObject = new MockCreatureObject();

	EXPECT_CALL(*mockDirectorManager, getLuaInstance()).WillOnce(Return(&mockLua));
	EXPECT_CALL(mockLua, createFunction(String("JediManager"), String("onPlayerLoggedOut"), 0)).WillOnce(Return(mockLuaFunction));
	EXPECT_CALL(*mockLuaFunction, addArgument(TypedEq<void*>(mockCreatureObject))).Times(1);
	EXPECT_CALL(*mockLuaFunction, callFunction()).Times(1);

	Reference<DirectorManager*> realDirectorManager = DirectorManager::instance();

	DirectorManager::setSingletonInstance(mockDirectorManager);

	jediManager->onPlayerLoggedOut(mockCreatureObject);

	DirectorManager::setSingletonInstance(realDirectorManager);
}

TEST_F(JediManagerTest, CheckForceStatusCommandShouldCallTheCheckForceStatusCommandMethodInTheLuaJediManager) {
	MockLua mockLua;
	Reference<MockLuaFunction*> mockLuaFunction = new MockLuaFunction();
	Reference<MockDirectorManager*> mockDirectorManager = new MockDirectorManager();
	Reference<MockCreatureObject*> mockCreatureObject = new MockCreatureObject();

	EXPECT_CALL(*mockDirectorManager, getLuaInstance()).WillOnce(Return(&mockLua));
	EXPECT_CALL(mockLua, createFunction(String("JediManager"), String("checkForceStatusCommand"), 0)).WillOnce(Return(mockLuaFunction));
	EXPECT_CALL(*mockLuaFunction, addArgument(TypedEq<void*>(mockCreatureObject))).Times(1);
	EXPECT_CALL(*mockLuaFunction, callFunction()).Times(1);

	Reference<DirectorManager*> realDirectorManager = DirectorManager::instance();

	DirectorManager::setSingletonInstance(mockDirectorManager);

	jediManager->checkForceStatusCommand(mockCreatureObject);

	DirectorManager::setSingletonInstance(realDirectorManager);
}

TEST_F(JediManagerTest, UseItemShouldCallTheUseItemMethodInTheLuaJediManager) {
	MockLua mockLua;
	Reference<MockLuaFunction*> mockLuaFunction = new MockLuaFunction();
	Reference<MockDirectorManager*> mockDirectorManager = new MockDirectorManager();
	Reference<MockCreatureObject*> mockCreatureObject = new MockCreatureObject();
	Reference<MockSceneObject*> mockSceneObject = new MockSceneObject();

	EXPECT_CALL(*mockDirectorManager, getLuaInstance()).WillOnce(Return(&mockLua));
	EXPECT_CALL(mockLua, createFunction(String("JediManager"), String("useItem"), 0)).WillOnce(Return(mockLuaFunction));
	EXPECT_CALL(*mockLuaFunction, addArgument(An<void*>())).Times(2);
	EXPECT_CALL(*mockLuaFunction, addArgument(An<int>())).Times(1);
	EXPECT_CALL(*mockLuaFunction, callFunction()).Times(1);

	Reference<DirectorManager*> realDirectorManager = DirectorManager::instance();

	DirectorManager::setSingletonInstance(mockDirectorManager);

	jediManager->useItem(mockSceneObject, JediManager::ITEMHOLOCRON, mockCreatureObject);

	DirectorManager::setSingletonInstance(realDirectorManager);
}


}
}
}
}
}
