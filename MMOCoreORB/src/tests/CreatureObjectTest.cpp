#include "gtest/gtest.h"

#include "server/db/MySqlDatabase.h"
#include "server/db/ServerDatabase.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace test {

class CreatureObjectTest : public ::testing::Test {
protected:
	ServerDatabase* database = nullptr;
	Reference<ZoneServer*> zoneServer;
	Reference<Zone*> zone;
	Reference<ZoneProcessServer*> processServer;
	AtomicLong nextObjectId;
public:

	CreatureObjectTest() {
		// Perform creation setup here.
		nextObjectId = 1;
		ConfigManager::instance()->loadConfigData();
		ConfigManager::instance()->setProgressMonitors(false);
		auto configManager = ConfigManager::instance();

		database = new ServerDatabase(configManager);
		zoneServer = new ZoneServer(configManager);
		processServer = new ZoneProcessServer(zoneServer);
		zone = new Zone(processServer, "test_zone");
		zone->createContainerComponent();
		zone->_setObjectID(1);

		CreaturePosture::instance()->loadMovementData();
	}

	~CreatureObjectTest() {
		// Clean up.
		if (database != nullptr) {
			delete database;
			database = nullptr;
		}

		zone = nullptr;
		processServer = nullptr;
		zoneServer = nullptr;
	}

	void SetUp() {
		// Perform setup of common constructs here.
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}

    Reference<CreatureObject*> createCreatureObject() {
	    Reference<CreatureObject*> creature = new CreatureObject();

		creature->setContainerComponent("ContainerComponent");
		creature->setZoneComponent("ZoneComponent");
		creature->_setObjectID(nextObjectId.increment());
		creature->initializeContainerObjectsMap();

        return creature;
    }
};

TEST_F(CreatureObjectTest, CreatureObjectDoesNotHaveCoverStateAfterCreation) {
	Reference<CreatureObject*> creature = createCreatureObject();

	EXPECT_EQ(creature->hasState(CreatureState::COVER), false);
}

TEST_F(CreatureObjectTest, CreatureObjectTakeCoverWithoutSneak) {
	Reference<CreatureObject*> creature = createCreatureObject();

	Locker locker(creature);
    creature->setPosture(CreaturePosture::UPRIGHT);
	EXPECT_GT(creature->getSpeedMultiplierMod(), 0.f);

	creature->setCoverState();

	EXPECT_EQ(creature->hasState(CreatureState::COVER), true);
	EXPECT_EQ(creature->getSpeedMultiplierMod(), 0.f);
}

TEST_F(CreatureObjectTest, CreatureObjectTakeCoverWithSneak) {
	Reference<CreatureObject*> creature = createCreatureObject();
    Reference<SkillManager*> skillManager = new SkillManager();
	skillManager->loadLuaConfig();
	skillManager->loadClientData();

	Locker locker(creature);
    creature->setPosture(CreaturePosture::UPRIGHT);

	creature->addSkill(skillManager->getSkill("combat_rifleman_speed_03"));
	EXPECT_EQ(creature->hasSkill("combat_rifleman_speed_03"), true);
	EXPECT_GT(creature->getSpeedMultiplierMod(), 0.f);

	creature->setCoverState();

	EXPECT_EQ(creature->hasState(CreatureState::COVER), true);
	EXPECT_GT(creature->getSpeedMultiplierMod(), 0.f);
}

}
}
}
}
}