/*
 * SpaceZoneTest.cpp
 *
 *  Created on: 01/05/2023
 *      Author: Hakry
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "server/db/MySqlDatabase.h"
#include "server/db/ServerDatabase.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/area/space/SpaceActiveArea.h"
#include "conf/ConfigManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/login/objects/GalaxyList.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::TypedEq;
using ::testing::An;

class SpaceZoneTest : public ::testing::Test {
protected:
	ServerDatabase* database = nullptr;
	Reference<ZoneServer*> zoneServer;
	Reference<SpaceZone*> spaceZone;
	Reference<ZoneProcessServer*> processServer;
	AtomicLong nextObjectId;
	Reference<PlayerManager*> playerManager;
public:
	SpaceZoneTest() {
		// Perform creation setup here.
		nextObjectId = 1;
	}

	~SpaceZoneTest() {
		// Clean up.
	}

	void setDefaultComponents(SceneObject* object) {
		object->setContainerComponent("SpaceZoneContainerComponent");
		object->setSpaceZoneComponent("SpaceZoneComponent");
	}

	Reference<SceneObject*> createSceneObject() {
		Reference<SceneObject*> object = new SceneObject();
		setDefaultComponents(object);
		object->_setObjectID(nextObjectId.increment());
		object->initializeContainerObjectsMap();

		return object;
	}

	Reference<TangibleObject*> createTangibleObject() {
		Reference<TangibleObject*> object = new TangibleObject();
		setDefaultComponents(object);
		object->_setObjectID(nextObjectId.increment());
		object->initializeContainerObjectsMap();

		return object;
	}

	Reference<ShipObject*> createShipObject() {
		Reference<ShipObject*> object = new ShipObject();
		setDefaultComponents(object);
		object->_setObjectID(nextObjectId.increment());
		object->initializeContainerObjectsMap();

		return object;
	}

	Reference<SpaceActiveArea*> createActiveArea(bool mock = false) {
		Reference<SpaceActiveArea*> spaceActiveArea;

		if (mock) {
			spaceActiveArea = new MockSpaceActiveArea();
		} else {
			spaceActiveArea = new SpaceActiveArea();
		}

		setDefaultComponents(spaceActiveArea);
		spaceActiveArea->_setObjectID(nextObjectId.increment());
		spaceActiveArea->initializeContainerObjectsMap();

		return spaceActiveArea;
	}

	void SetUp() {
		// Perform setup of common constructs here.
		ConfigManager::instance()->loadConfigData();
		ConfigManager::instance()->setProgressMonitors(false);
		auto configManager = ConfigManager::instance();

		database = new ServerDatabase(configManager);
		zoneServer = new ZoneServer(configManager);
		processServer = new ZoneProcessServer(zoneServer);
		spaceZone = new SpaceZone(processServer, "test_space_zone");

		spaceZone->createContainerComponent();
		spaceZone->_setObjectID(1);
	}

	void TearDown() {
		// Perform clean up of common constructs here.
		if (database != nullptr) {
			delete database;
			database = nullptr;
		}

		if (playerManager != nullptr) {
			playerManager->finalize();
			playerManager = nullptr;
		}

		spaceZone = nullptr;
		processServer = nullptr;
		zoneServer = nullptr;
	}
};

TEST_F(SpaceZoneTest, SpaceActiveAreaTest) {
	Reference<MockSpaceActiveArea*> spaceActiveArea = createActiveArea(true).castTo<MockSpaceActiveArea*>();

	ON_CALL(*spaceActiveArea, getZone()).WillByDefault(Return(spaceZone));
	ON_CALL(*spaceActiveArea, getZoneUnsafe()).WillByDefault(Return(spaceZone));
	ON_CALL(*spaceActiveArea, getParent()).WillByDefault(Return(ManagedWeakReference<SceneObject*>(NULL)));
	EXPECT_CALL(*spaceActiveArea, getZone()).Times(AnyNumber());
	EXPECT_CALL(*spaceActiveArea, getZoneUnsafe()).Times(AnyNumber());
	EXPECT_CALL(*spaceActiveArea, getParent()).Times(AnyNumber());
	EXPECT_CALL(*spaceActiveArea, enqueueEnterEvent(_)).Times(AnyNumber());
	EXPECT_CALL(*spaceActiveArea, enqueueExitEvent(_)).Times(AnyNumber());

	Locker alocker(spaceActiveArea);

	spaceActiveArea->setRadius(512);
	spaceActiveArea->initializePosition(0, 0, 0);

	spaceZone->transferObject(spaceActiveArea, -1);

	alocker.release();

	Reference<ShipObject*> ship = createShipObject();

	Locker slocker(ship);

	ship->initializePosition(0, 0, 0);

	ASSERT_EQ(ship->getActiveAreasSize(), 0);

	spaceZone->transferObject(ship, -1);

	ASSERT_EQ(ship->getActiveAreasSize(), 1);

	ship->teleport(0, -600, 0);

	ASSERT_EQ(ship->getActiveAreasSize(), 0);

	ship->teleport(120, 120, 120);

	ASSERT_EQ(ship->getActiveAreasSize(), 1);

	slocker.release();

	Locker blocker(spaceActiveArea);

	spaceActiveArea->destroyObjectFromWorld(false);

	blocker.release();

	Locker s2locker(ship);

	ASSERT_EQ(ship->getActiveAreasSize(), 0);

	ship->destroyObjectFromWorld(false);
}

TEST_F(SpaceZoneTest, InRangeTest) {
	Reference<SceneObject*> scene = createSceneObject();

	Locker slocker(scene);

	spaceZone->transferObject(scene, -1);

	ASSERT_TRUE(scene->getZone() != nullptr);

	ASSERT_TRUE(scene->getZone()->isSpaceZone());

	SortedVector<ManagedReference<TreeEntry*> > objects;

	spaceZone->getInRangeObjects(0, 0, 0, 512, &objects, true);

	ASSERT_EQ(objects.size(), 1);

	scene->teleport(1000, 1000, 1000);

	objects.removeAll();

	spaceZone->getInRangeObjects(0, 0, 0, 128, &objects, true);

	ASSERT_EQ(objects.size(), 0);

	objects.removeAll();

	spaceZone->getInRangeObjects(1000, 1000, 1000, 128, &objects, true);

	ASSERT_EQ(objects.size(), 1);

	slocker.release();

	Reference<SceneObject*> scene2 = createSceneObject();

	Locker s2locker(scene2);

	scene2->initializePosition(1000, 1000, 1000);

	spaceZone->transferObject(scene2, -1);

	objects.removeAll();

	spaceZone->getInRangeObjects(1000, 1000, 1000, 128, &objects, true);

	ASSERT_EQ(objects.size(), 2);

	scene2->destroyObjectFromWorld(false);

	s2locker.release();

	Locker s3locker(scene);

	scene->destroyObjectFromWorld(false);

	objects.removeAll();

	spaceZone->getInRangeObjects(1000, 1000, 1000, 128, &objects, true);

	ASSERT_EQ(objects.size(), 0);
}