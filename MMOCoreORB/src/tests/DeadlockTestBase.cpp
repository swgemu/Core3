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


class DISABLED_GeneralDeadlockTestBase : public ::testing::Test {
public:
	Reference<LockMockSceneObject*> sceneObject1;
	Reference<LockMockSceneObject*> sceneObject2;
	Reference<LockMockSceneObject*> sceneObject3;
	Reference<LockMockSceneObject*> sceneObject4;

	Reference<LockMockSceneObject*> monitor;

	DISABLED_GeneralDeadlockTestBase() {
		// Perform creation setup here.
	}

	~DISABLED_GeneralDeadlockTestBase() {
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
		CLEAR_LOCK_TRACE();

		sceneObject1 = nullptr;
		sceneObject2 = nullptr;
		sceneObject3 = nullptr;
		sceneObject4 = nullptr;
		monitor = nullptr;
	}
};

TEST_F(DISABLED_GeneralDeadlockTestBase, CrossLockTest) {
	EXPECT_TOTAL_LOCKED(0);

	try {
		Locker locker(sceneObject1);
		Locker locker2(sceneObject2);

	} catch (DeadlockException& e) {
		SUCCEED();

		return;
	}

	FAIL() << "Cross lock deadlock not detected!";
}
/*
TEST_F(DISABLED_GeneralDeadlockTestBase, CrossLockToNullTest) {
	EXPECT_TOTAL_LOCKED(0);

	try {
		Locker locker2(sceneObject2, nullptr);

	} catch (DeadlockException& e) {
		SUCCEED();

		return;
	}

	FAIL() << "Cross lock to null lockable not detected!";
}

TEST_F(DISABLED_GeneralDeadlockTestBase, CrossLockToUnlockedTest) {
	EXPECT_TOTAL_LOCKED(0);

	try {
		Locker locker2(sceneObject2, sceneObject1);

	} catch (DeadlockException& e) {
		SUCCEED();

		return;
	}

	FAIL() << "Cross lock to non-locked lockable not detected!";
}
*/
TEST_F(DISABLED_GeneralDeadlockTestBase, ThreeLocksTest) {
	EXPECT_TOTAL_LOCKED(0);

	try {
		Locker locker(sceneObject1);
		Locker locker2(sceneObject2, sceneObject1);

		Locker locker3(sceneObject3);
	} catch (DeadlockException& e) {
		SUCCEED();

		return;
	}

	FAIL() << "Could not detect a 3 way deadlock!";
}

TEST_F(DISABLED_GeneralDeadlockTestBase, MonitorLockTest) {
	EXPECT_TOTAL_LOCKED(0);

	Locker locker(sceneObject1);

	Locker locker2(sceneObject2, sceneObject1);

	Locker locker3(monitor);

	EXPECT_TOTAL_LOCKED(3);
}

TEST_F(DISABLED_GeneralDeadlockTestBase, MultipleLocksTest) {
	EXPECT_TOTAL_LOCKED(0);

	Locker locker(sceneObject1);

	Locker locker2(sceneObject2, sceneObject1);

	Locker locker3(monitor);

	EXPECT_TOTAL_LOCKED(3);

	locker3.release();

	Locker locker4(monitor);

	EXPECT_TOTAL_LOCKED(3);

	locker4.release();

	locker2.release();

	Locker locker5(monitor);

	EXPECT_TOTAL_LOCKED(2);

	locker5.release();

	Locker locker6(sceneObject3, sceneObject1);

	EXPECT_TOTAL_LOCKED(2);
}

void DeadlockDetector::detectDeadlock() {
	ArrayList<LockableTrace>* trace = Thread::getCurrentThread()->getLockableTrace();

	ArrayList<Lockable*> locked;

	for (int i = 0; i < trace->size(); ++i) {
		LockableTrace* lock = &trace->get(i);

		if (lock->locked) {
			Lockable* lastLockable = locked.size() > 0 ? locked.get(locked.size() - 1) : nullptr;
			LockableTrace* lastTrace = nullptr;
			// find last lock with lastLockable

			for (int j = i - 1; j >= 0 && !lastTrace; --j) {
				LockableTrace* lockTrace = &trace->get(j);

				if (lockTrace->lockable == lastLockable && lockTrace->locked) {
					lastTrace = lockTrace;

					break;
				}
			}

			if (lastLockable != nullptr) {
				if (lastTrace != nullptr && lastTrace->monitorLike)
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

