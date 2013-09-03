/*
 * DeadlockTestBase.cpp
 *
 *  Created on: 03/09/2013
 *      Author: victor
 */

#include "DeadlockTestBase.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "server/zone/objects/scene/SceneObject.h"

class LockMockSceneObject : public MockSceneObject {
	MOCK_LOCKS(LockMockSceneObject, MockSceneObject);
};

class GeneralDeadlockTest : public ::testing::Test {
public:
	Reference<LockMockSceneObject*> sceneObject1;
	Reference<LockMockSceneObject*> sceneObject2;
	Reference<LockMockSceneObject*> sceneObject3;
	Reference<LockMockSceneObject*> sceneObject4;

	Reference<LockMockSceneObject*> monitor;

	GeneralDeadlockTest() {
		// Perform creation setup here.
	}

	~GeneralDeadlockTest() {
		// Clean up.
	}

	void SetUp() {
		// Perform setup of common constructs here.
		CLEAR_LOCK_TRACE();

		sceneObject1 = new LockMockSceneObject();
		sceneObject2 = new LockMockSceneObject();
		sceneObject3 = new LockMockSceneObject();
		sceneObject4 = new LockMockSceneObject();
		monitor = new LockMockSceneObject(true);
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};

TEST_F(GeneralDeadlockTest, CrossLockTest) {
	EXPECT_TOTAL_LOCKED(0);

	try {
		Locker locker(sceneObject1);
		Locker locker2(sceneObject2);

	} catch (DeadlockException& e) {
		SUCCEED();

		return;
	}

	FAIL() << "Cross lock not detected!";
}

TEST_F(GeneralDeadlockTest, CrossLockToNullTest) {
	EXPECT_TOTAL_LOCKED(0);

	try {
		Locker locker2(sceneObject2, NULL);

	} catch (DeadlockException& e) {
		SUCCEED();

		return;
	}

	FAIL() << "Cross lock to non-locked lockable not detected!";
}

TEST_F(GeneralDeadlockTest, CrossLockToUnlockedTest) {
	EXPECT_TOTAL_LOCKED(0);

	try {
		Locker locker2(sceneObject2, sceneObject1);

	} catch (DeadlockException& e) {
		SUCCEED();

		return;
	}

	FAIL() << "Cross lock to non-locked lockable not detected!";
}

TEST_F(GeneralDeadlockTest, ThreeLocksTest) {
	EXPECT_TOTAL_LOCKED(0);

	try {
		Locker locker(sceneObject1);
		Locker locker2(sceneObject2, sceneObject1);

		Locker locker3(sceneObject3);
	} catch (DeadlockException& e) {
		SUCCEED();

		return;
	}

	FAIL() << "Could not detect a deadlock with 3 locks!";
}

TEST_F(GeneralDeadlockTest, MonitorLockTest) {
	EXPECT_TOTAL_LOCKED(0);

	Locker locker(sceneObject1);

	Locker locker2(sceneObject2, sceneObject1);

	Locker locker3(monitor);

	EXPECT_TOTAL_LOCKED(3);
}

void DeadlockDetector::detectDeadlock() {
	ArrayList<LockableTrace>* trace = Thread::getCurrentThread()->getLockableTrace();

	ArrayList<Lockable*> locked;

	for (int i = 0; i < trace->size(); ++i) {
		LockableTrace* lock = &trace->get(i);

		if (lock->locked) {
			Lockable* lastLockable = locked.size() > 0 ? locked.get(locked.size() - 1) : NULL;
			LockableTrace* lastTrace = NULL;
			// find last lock with lastLockable

			for (int j = i - 1; j >= 0 && !lastTrace; --j) {
				LockableTrace* lockTrace = &trace->get(j);

				if (lockTrace->lockable == lastLockable && lockTrace->locked) {
					lastTrace = lockTrace;

					break;
				}
			}

			if (lastLockable != NULL) {
				if (lastTrace->monitorLike)
					throw DeadlockException(lock->lockable, "Monitor trying to perform a lock!");

				//ASSERT_FALSE(lastTrace->monitorLike) << "Monitor trying to perform a lock!";

				if (locked.size() < 2 && !lock->monitorLike && !lock->crossedTo) {
					throw DeadlockException(lock->lockable, "Locking a second object without a crosslock!");
				}

				//ASSERT_FALSE(locked.size() < 2 && !lock->monitorLike && !lock->crossedTo) << "Locking a second object without a crosslock!";

				if (locked.size() >= 2 && !lock->monitorLike) {
					throw DeadlockException(lock->lockable, "Locking an object that is not a monitor while there are 2 objects already locked!");
				}

				//ASSERT_FALSE(locked.size() >= 2 && !lock->monitorLike) << "Locking an object that is not a monitor while there are 2 objects already locked!";
			}

			locked.add(lock->lockable);
		} else if (!lock->locked)
			locked.removeElement(lock->lockable);
	}
}

