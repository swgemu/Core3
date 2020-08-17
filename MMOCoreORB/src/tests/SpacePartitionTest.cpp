/*
 * TerrainManagerTest.cpp
 *
 *  Created on: Feb 22, 2014
 *      Author: swgemu
 */

#include "server/zone/managers/space/SpacePartitioningManager.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::Return;


namespace server {
namespace zone {
namespace managers {
namespace space {

class SpacePartitionManagerTest : public ::testing::Test, public Logger {
public:


	SpacePartitionManagerTest() : Logger("SpacePartitionManagerTest") {
		// Perform creation setup here.
	}

	~SpacePartitionManagerTest() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
         partition = new SpacePartitioningManager(64, 1024);
	}

	void TearDown() {
		// Perform clean up of common constructs here.
        delete partition;
	}


    SpacePartitioningManager* partition;
};

TEST_F(SpacePartitionManagerTest, AddSingleObserverAndObservableAndQuerySameCell) {


	SceneObject* object = new SceneObject();
	object->setPosition(50, 50, 50);

	SceneObject* observer = new SceneObject();
	observer->setPosition(40, 40, 40);

	partition->addObject(object);
	partition->addObserver(observer, 20);

	//distance is 17.320508

	Vector<SceneObject*> objects = partition->getCloseObjects(observer);

	EXPECT_EQ(objects.size(), 1);

	EXPECT_EQ(objects.elementAt(0), object);

}

TEST_F(SpacePartitionManagerTest, AddSingleObserverAndObservableAndQueryOuterCellPass) {

	//this object is in the outmost cell the one that has to be checked individually


	SceneObject* object = new SceneObject();
	object->setPosition(40, 40, 110);

	SceneObject* observer = new SceneObject();
	observer->setPosition(40, 40, 40);

	partition->addObject(object);
	partition->addObserver(observer, 70);

	//distance is 70

	Vector<SceneObject*> objects = partition->getCloseObjects(observer);

	EXPECT_EQ(objects.size(), 1);

	EXPECT_EQ(objects.elementAt(0), object);

}

TEST_F(SpacePartitionManagerTest, AddSingleObserverAndObservableAndQueryOuterCellFail) {

	//this object is in the outmost cell the one that has to be checked individually


	SceneObject* object = new SceneObject();
	object->setPosition(40, 40, 110);

	SceneObject* observer = new SceneObject();
	observer->setPosition(40, 40, 40);

	partition->addObject(object);
	partition->addObserver(observer, 69);

	//distance is 70

	Vector<SceneObject*> objects = partition->getCloseObjects(observer);

	EXPECT_EQ(objects.size(), 0);

}

}
}
}
}
