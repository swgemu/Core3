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

using ::testing::_;
using ::testing::Return;
using ::testing::AnyNumber;

namespace server {
namespace zone {
namespace managers {
namespace jedi {
namespace tests {

class JediManagerTest : public ::testing::Test {
public:
	JediManager* jediManager;

	JediManagerTest() {
		// Perform creation setup here.
	}

	~JediManagerTest() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
		jediManager = new JediManager();
	}

	void TearDown() {
		// Perform clean up of common constructs here.
		delete jediManager;
	}

	void constructorDefaults(MockLua& mockLua) {
		EXPECT_CALL(mockLua, runFile(_)).Times(AnyNumber());
		EXPECT_CALL(mockLua, getGlobalInt(_)).Times(AnyNumber());
		EXPECT_CALL(mockLua, getGlobalString(_)).Times(AnyNumber());
		ON_CALL(mockLua, getGlobalString(_)).WillByDefault(Return(String("")));
	}
};

TEST_F(JediManagerTest, ShouldRunFileJediManagerLuaAtLoadConfiguration) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	EXPECT_CALL(mockLua, runFile(String("scripts/managers/jedi_manager.lua"))).Times(1);

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

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return(JediManager::HOLOCRONJEDIPROGRESSION));
	EXPECT_CALL(mockLua, runFile(String("scripts/managers/holocron_jedi_manager.lua"))).Times(1);

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldRunTheVillageJediManagerLuaFileIfVillageJediProgressionIsConfigured) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return(JediManager::VILLAGEJEDIPROGRESSION));
	EXPECT_CALL(mockLua, runFile(String("scripts/managers/village_jedi_manager.lua"))).Times(1);

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldReadTheCustomJediProgressionFileStringIfCustomJediProgressionIsConfigured) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return(JediManager::CUSTOMJEDIPROGRESSION));
	EXPECT_CALL(mockLua, getGlobalString(String("customJediProgressionFile"))).WillOnce(Return(String("scripts/managers/custom_jedi_manager.lua")));

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldLoadTheCustomJediProgressionFileIfCustomJediProgressionIsConfigured) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return(JediManager::CUSTOMJEDIPROGRESSION));
	EXPECT_CALL(mockLua, getGlobalString(String("customJediProgressionFile"))).WillOnce(Return(String("scripts/managers/custom_jedi_manager.lua")));
	EXPECT_CALL(mockLua, runFile(String("scripts/managers/custom_jedi_manager.lua"))).Times(1);

	jediManager->loadConfiguration(&mockLua);
}

TEST_F(JediManagerTest, ShouldReadTheJediProgressionSystemNameAtLoadConfiguration) {
	MockLua mockLua;

	constructorDefaults(mockLua);

	ON_CALL(mockLua, getGlobalInt(String("jediProgressionType"))).WillByDefault(Return(JediManager::HOLOCRONJEDIPROGRESSION));
	EXPECT_CALL(mockLua, getGlobalString(String("jediManagerName"))).WillOnce(Return(String("HolocronJediManager")));

	jediManager->loadConfiguration(&mockLua);
}

//TODO Add test of the checkForceStatusCommand. Needs an updated engine.

}
}
}
}
}
