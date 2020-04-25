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
	const String skillWithSneakAbility = "combat_rifleman_speed_03";
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

	Reference<SkillManager*> getSkillManager() {
		Reference<SkillManager*> skillManager = new SkillManager();
		skillManager->loadLuaConfig();
		skillManager->loadClientData();
		return skillManager;
	}
};

TEST_F(CreatureObjectTest, CreatureObjectDoesNotHaveCoverStateAfterCreation) {
	Reference<CreatureObject*> creature = createCreatureObject();

	EXPECT_EQ(creature->hasState(CreatureState::COVER), false);
}

TEST_F(CreatureObjectTest, CreatureObjectIsImmovableWhenTakingCoverWithoutSneak) {
	Reference<CreatureObject*> creature = createCreatureObject();

	Locker locker(creature);
	creature->setPosture(CreaturePosture::UPRIGHT);
	EXPECT_GT(creature->getSpeedMultiplierMod(), 0.f);

	creature->setCoverState();

	EXPECT_EQ(creature->hasState(CreatureState::COVER), true);
	EXPECT_EQ(creature->getSpeedMultiplierMod(), 0.f);
}

TEST_F(CreatureObjectTest, CreatureObjectCanMoveWhenTakingCoverWithSneak) {
	Reference<CreatureObject*> creature = createCreatureObject();
	Reference<SkillManager*> skillManager = getSkillManager();

	Locker locker(creature);
	creature->setPosture(CreaturePosture::UPRIGHT);

	creature->addSkill(skillManager->getSkill(skillWithSneakAbility));
	EXPECT_GT(creature->getSpeedMultiplierMod(), 0.f);

	creature->setCoverState();

	EXPECT_EQ(creature->hasState(CreatureState::COVER), true);
	EXPECT_GT(creature->getSpeedMultiplierMod(), 0.f);
}

TEST_F(CreatureObjectTest, CreatureObjectTakingCoverBeforeLearningSneakAbility) {
	Reference<CreatureObject*> creature = createCreatureObject();
	Reference<SkillManager*> skillManager = getSkillManager();

	Locker locker(creature);
	creature->setPosture(CreaturePosture::UPRIGHT);

	creature->setCoverState();

	EXPECT_EQ(creature->hasState(CreatureState::COVER), true);
	EXPECT_EQ(creature->getSpeedMultiplierMod(), 0.f);

	creature->addSkill(skillManager->getSkill(skillWithSneakAbility));
	EXPECT_EQ(creature->hasState(CreatureState::COVER), true);
	EXPECT_GT(creature->getSpeedMultiplierMod(), 0.f);
}

TEST_F(CreatureObjectTest, CreatureObjectTakingCoverAfterLoosingSneakAbility) {
	Reference<CreatureObject*> creature = createCreatureObject();
	Reference<SkillManager*> skillManager = getSkillManager();

	Locker locker(creature);
	creature->setPosture(CreaturePosture::UPRIGHT);

	creature->addSkill(skillManager->getSkill(skillWithSneakAbility));
	EXPECT_GT(creature->getSpeedMultiplierMod(), 0.f);

	creature->setCoverState();

	EXPECT_EQ(creature->hasState(CreatureState::COVER), true);
	EXPECT_GT(creature->getSpeedMultiplierMod(), 0.f);

	creature->removeSkill(skillManager->getSkill(skillWithSneakAbility));

	EXPECT_EQ(creature->hasState(CreatureState::COVER), true);
	EXPECT_EQ(creature->getSpeedMultiplierMod(), 0.f);
}

TEST_F(CreatureObjectTest, VerifyCreatureObjectSpeedModifiersForDifferentPostures) {
	Reference<CreatureObject*> creature = createCreatureObject();
	Reference<SkillManager*> skillManager = getSkillManager();

	Locker locker(creature);
	creature->setPosture(CreaturePosture::UPRIGHT);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 1.f);
	creature->setPosture(CreaturePosture::CROUCHED);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.5f);
	creature->setPosture(CreaturePosture::PRONE);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.25f);
	creature->setPosture(CreaturePosture::SNEAKING);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.5f);
	creature->setPosture(CreaturePosture::BLOCKING);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.f);
	creature->setPosture(CreaturePosture::CLIMBING);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.25f);
	creature->setPosture(CreaturePosture::FLYING);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.f);
	creature->setPosture(CreaturePosture::LYINGDOWN);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.15f);
	creature->setPosture(CreaturePosture::SITTING);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.f);
	creature->setPosture(CreaturePosture::SKILLANIMATING);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 1.f);
	creature->setPosture(CreaturePosture::DRIVINGVEHICLE);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.f);
	creature->setPosture(CreaturePosture::RIDINGCREATURE);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.f);
	creature->setPosture(CreaturePosture::KNOCKEDDOWN);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.f);
	creature->setPosture(CreaturePosture::INCAPACITATED);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.f);
	creature->setPosture(CreaturePosture::DEAD);
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.f);

	creature->setPosture(CreaturePosture::UPRIGHT);
	creature->setCoverState();
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.f);
	creature->addSkill(skillManager->getSkill(skillWithSneakAbility));
	EXPECT_FLOAT_EQ(creature->getSpeedMultiplierMod(), 0.125f);
}

}
}
}
}
}