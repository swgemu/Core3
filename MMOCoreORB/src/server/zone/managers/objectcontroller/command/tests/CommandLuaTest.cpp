/*
 * CommandLuaTest.cpp
 *
 *  Created on: 20/10/2013
 *      Author: victor
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "templates/manager/DataArchiveStore.h"
#include "server/zone/managers/objectcontroller/command/CommandConfigManager.h"
#include "server/zone/managers/objectcontroller/command/CommandList.h"
#include "conf/ConfigManager.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"

class CommandLuaTest : public ::testing::Test {
public:
	Vector<uint32> animList;
	Logger logger;
	CommandConfigManager* man;
	CommandList* list;

	CommandLuaTest() : logger("CommandLuaTest") {
		// Perform creation setup here.
		ConfigManager::instance()->loadConfigData();
		DataArchiveStore::instance()->loadTres(ConfigManager::instance()->getTrePath(), ConfigManager::instance()->getTreFiles());
		man = new CommandConfigManager(NULL);
		list = new CommandList();
	}

	~CommandLuaTest() {
		delete man;
		delete list;
	}

	void SetUp() {
		// Perform setup of common constructs here.
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}

	void loadAnimList();
};

TEST_F(CommandLuaTest, LoadCommandLuas) {
	man->registerSpecialCommands(list);
	man->loadSlashCommandsFile();

	ASSERT_EQ(CommandConfigManager::ERROR_CODE, 0);
}

// This ensures that nobody inserts an invalid animation name, or uses an invalid generation type
TEST_F(CommandLuaTest, CheckAnimationCRCS) {
	loadAnimList();

	HashTableIterator<uint32, Reference<QueueCommand*> > iter = list->iterator();

	while (iter.hasNext()) {
		Reference<QueueCommand*> command = iter.getNextValue();

		if (command->isCombatCommand()) {
			CombatQueueCommand* combatCommand = command.castTo<CombatQueueCommand*>();
			uint8 animType = combatCommand->getAnimType();
			String commandName = combatCommand->getQueueCommandName();

			if (animType == CombatQueueCommand::GENERATE_NONE) {
				String anim = combatCommand->getAnimationString();
				if(!anim.isEmpty()) {
					ASSERT_TRUE(animList.contains(anim.hashCode()));
				}
			} else if (animType == CombatQueueCommand::GENERATE_RANGED) {
				String anim = combatCommand->generateAnimation(CombatManager::HIT_HEAD, 50, 25);
				ASSERT_TRUE(anim.endsWith("_light_face"));
				ASSERT_TRUE(animList.contains(anim.hashCode()));

				anim = combatCommand->generateAnimation(CombatManager::HIT_HEAD, 50, 200);
				ASSERT_TRUE(anim.endsWith("_medium_face"));
				ASSERT_TRUE(animList.contains(anim.hashCode()));

				anim = combatCommand->generateAnimation(CombatManager::HIT_BODY, 50, 25);
				ASSERT_TRUE(anim.endsWith("_light"));
				ASSERT_FALSE(anim.contains("_face"));
				ASSERT_TRUE(animList.contains(anim.hashCode()));

				anim = combatCommand->generateAnimation(CombatManager::HIT_BODY, 50, 200);
				ASSERT_TRUE(anim.endsWith("_medium"));
				ASSERT_FALSE(anim.contains("_face"));
				ASSERT_TRUE(animList.contains(anim.hashCode()));
			} else if (animType == CombatQueueCommand::GENERATE_INTENSITY) {
				String anim = combatCommand->generateAnimation(CombatManager::HIT_BODY, 50, 25);
				ASSERT_TRUE(anim.endsWith("_light"));
				ASSERT_FALSE(anim.contains("_face"));
				ASSERT_TRUE(animList.contains(anim.hashCode()));

				anim = combatCommand->generateAnimation(CombatManager::HIT_BODY, 50, 200);
				ASSERT_TRUE(anim.endsWith("_medium"));
				ASSERT_FALSE(anim.contains("_face"));
				ASSERT_TRUE(animList.contains(anim.hashCode()));
			}
		}
	}
}

void CommandLuaTest::loadAnimList() {

	IffStream *stream = DataArchiveStore::instance()->openIffFile("combat/combat_manager.iff");

	ASSERT_TRUE(stream != NULL);

	stream->openForm('CBTM');
	stream->openForm('0002');
	Chunk *form = NULL;
	try {
		while((form = stream->openForm('ENTR'))) {
			String str;
			form->getChunk(0)->readString(str);
			animList.add(str.hashCode());
			stream->closeForm('ENTR');
		}
	} catch (...) {
		// end of list throws exception
	}

	stream->closeForm('0002');
	stream->closeForm('CBTM');
	delete stream;
}
