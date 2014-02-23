/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

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

	JediManagerTest() : Logger("JediManagerTest") {
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

	EXPECT_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillOnce(Return(JediManager::NOJEDIPROGRESSION));

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldRunTheHolocronJediManagerLuaFileIfHolocronJediProgressionIsConfigured) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return(JediManager::HOLOGRINDJEDIPROGRESSION));
	EXPECT_CALL(mockLua, runFile(String("scripts/managers/jedi/hologrind/hologrind_jedi_manager.lua"))).Times(1);

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldRunTheVillageJediManagerLuaFileIfVillageJediProgressionIsConfigured) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return(JediManager::VILLAGEJEDIPROGRESSION));
	EXPECT_CALL(mockLua, runFile(String("scripts/managers/jedi/village/village_jedi_manager.lua"))).Times(1);

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldReadTheCustomJediProgressionFileStringIfCustomJediProgressionIsConfigured) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return(JediManager::CUSTOMJEDIPROGRESSION));
	EXPECT_CALL(mockLua, getGlobalString(String("customJediProgressionFile"))).WillOnce(Return(String("scripts/managers/jedi/custom_jedi_manager.lua")));

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldLoadTheCustomJediProgressionFileIfCustomJediProgressionIsConfigured) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return(JediManager::CUSTOMJEDIPROGRESSION));
	EXPECT_CALL(mockLua, getGlobalString(String("customJediProgressionFile"))).WillOnce(Return(String("scripts/managers/jedi/custom_jedi_manager.lua")));
	EXPECT_CALL(mockLua, runFile(String("scripts/managers/jedi/custom_jedi_manager.lua"))).Times(1);

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldReadTheJediProgressionSystemNameAtLoadConfiguration) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return(JediManager::HOLOGRINDJEDIPROGRESSION));
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
