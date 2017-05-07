/*
 * ZoneTest.cpp
 *
 *  Created on: 09/09/2013
 *      Author: victor
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "conf/ConfigManager.h"
#include "server/zone/managers/player/PlayerManager.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::TypedEq;
using ::testing::An;

class ZoneTest : public ::testing::Test {
protected:
	Reference<ZoneServer*> zoneServer;
	Reference<Zone*> zone;
	Reference<ZoneProcessServer*> processServer;
	AtomicLong nextObjectId;
	Reference<PlayerManager*> playerManager;
public:
	ZoneTest() {
		// Perform creation setup here.
		nextObjectId = 1;
	}

	~ZoneTest() {
		// Clean up.
	}

	void setDefaultComponents(SceneObject* object) {
		object->setContainerComponent("ContainerComponent");
		object->setZoneComponent("ZoneComponent");
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

	Reference<ActiveArea*> createActiveArea(bool mock = false) {
		Reference<ActiveArea*> activeArea;

		if (mock) {
			activeArea = new MockActiveArea();
		} else {
			activeArea = new ActiveArea();
		}
		setDefaultComponents(activeArea);
		activeArea->_setObjectID(nextObjectId.increment());
		activeArea->initializeContainerObjectsMap();

		return activeArea;
	}

	void SetUp() {
		// Perform setup of common constructs here.
		ConfigManager::instance()->loadConfigData();
		ConfigManager::instance()->setProgressMonitors(false);
		zoneServer = new ZoneServer(ConfigManager::instance());
		processServer = new ZoneProcessServer(zoneServer);
		zone = new Zone(processServer, "test_zone");
		zone->createContainerComponent();
		zone->_setObjectID(1);
	}

	void TearDown() {
		// Perform clean up of common constructs here.
		if (playerManager != NULL) {
			playerManager->finalize();
			playerManager = NULL;
		}

		zone = NULL;
		processServer = NULL;
		zoneServer = NULL;
	}
};

TEST_F(ZoneTest, PlayerManager) {
	playerManager = new PlayerManager( zoneServer, processServer );
}

TEST_F(ZoneTest, TreLoad) {
	TemplateManager::instance();

	ASSERT_EQ(TemplateManager::ERROR_CODE, 0);

	if (TemplateManager::instance()->loadedTemplatesCount == 0) {
		TemplateManager::instance()->loadLuaTemplates();
		ASSERT_EQ(TemplateManager::ERROR_CODE, 0);
	}
}

TEST_F(ZoneTest, ActiveAreaTest) {
	Reference<MockActiveArea*> activeArea = createActiveArea(true).castTo<MockActiveArea*>();
	EXPECT_CALL(*activeArea, enqueueEnterEvent(_)).Times(AnyNumber());
	EXPECT_CALL(*activeArea, enqueueExitEvent(_)).Times(AnyNumber());

	Locker alocker(activeArea);

	activeArea->setRadius(128);
	activeArea->initializePosition(0, 0, 0);

	zone->transferObject(activeArea, -1);

	alocker.release();

	Reference<TangibleObject*> tano = createTangibleObject();

	Locker slocker(tano);

	tano->initializePosition(0, 0, 0);

	ASSERT_EQ(tano->getActiveAreasSize(), 0);

	zone->transferObject(tano, -1);

	ASSERT_EQ(tano->getActiveAreasSize(), 1);

	tano->teleport(200, 0, 0);

	ASSERT_EQ(tano->getActiveAreasSize(), 0);

	tano->teleport(120, 0, 0);

	ASSERT_EQ(tano->getActiveAreasSize(), 1);

	slocker.release();

	Locker blocker(activeArea);

	activeArea->destroyObjectFromWorld(false);

	blocker.release();

	Locker s2locker(tano);

	ASSERT_EQ(tano->getActiveAreasSize(), 0);

	tano->destroyObjectFromWorld(false);
}

TEST_F(ZoneTest, InRangeTest) {
	Reference<SceneObject*> scene = createSceneObject();

	Locker slocker(scene);

	zone->transferObject(scene, -1);

	ASSERT_TRUE(scene->getZone() != NULL);

	SortedVector<ManagedReference<QuadTreeEntry*> > objects;

	zone->getInRangeObjects(0, 0, 128, &objects, true);

	ASSERT_EQ(objects.size(), 1);

	scene->teleport(1000, 1000, 1000);

	objects.removeAll();

	zone->getInRangeObjects(0, 0, 128, &objects, true);

	ASSERT_EQ(objects.size(), 0);

	objects.removeAll();

	zone->getInRangeObjects(1000, 1000, 128, &objects, true);

	ASSERT_EQ(objects.size(), 1);

	slocker.release();

	Reference<SceneObject*> scene2 = createSceneObject();

	Locker s2locker(scene2);

	scene2->initializePosition(1000, 1000, 1000);

	zone->transferObject(scene2, -1);

	objects.removeAll();

	zone->getInRangeObjects(1000, 1000, 128, &objects, true);

	ASSERT_EQ(objects.size(), 2);

	scene2->destroyObjectFromWorld(false);

	s2locker.release();

	Locker s3locker(scene);

	scene->destroyObjectFromWorld(false);

	objects.removeAll();

	zone->getInRangeObjects(1000, 1000, 128, &objects, true);

	ASSERT_EQ(objects.size(), 0);
}
