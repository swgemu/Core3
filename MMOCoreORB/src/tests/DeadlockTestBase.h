/*
 * DeadlockTestBase.h
 *
 *  Created on: 03/09/2013
 *      Author: victor
 */

#ifndef DEADLOCKTESTBASE_H_
#define DEADLOCKTESTBASE_H_

#include "TestCore.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define EXPECT_LOCKED(a) EXPECT_TRUE(a->isLockedByCurrentThread())
#define EXPECT_UNLOCKED(a) EXPECT_FALSE(a->isLockedByCurrentThread())
#define EXPECT_TOTAL_LOCKED(a) EXPECT_EQ(Thread::getCurrentThread()->getAcquiredLockables()->size(), a)
#define CLEAR_LOCK_TRACE() Thread::getCurrentThread()->getLockableTrace()->removeAll(); Thread::getCurrentThread()->getAcquiredLockables()->removeAll()

#define MOCK_LOCKS(Class, Ancestor)\
	protected:\
		bool _monitorLockable;\
	public:\
		Class(bool isMonitor = false) : _monitorLockable(isMonitor) { } \
		\
	void lock(bool doLock = true) { \
		if (doLock) {\
			Thread::getCurrentThread()->addAcquiredLockable(this, NULL, _monitorLockable); \
			DeadlockDetector::detectDeadlock(); \
		}\
		\
		Ancestor::lock(doLock); \
	} \
	\
	void unlock(bool doLock = true) { \
		if (!doLock) \
			return; \
			\
		Thread::getCurrentThread()->removeAcquiredLockable(this); \
		\
		Ancestor::unlock(doLock); \
	} \
	\
	void lock(Lockable* lockable) { \
		\
		if (lockable == NULL) \
		 	 throw DeadlockException(this, "Trying to crosslock against a null lockable!"); \
		\
		if (!lockable->isLockedByCurrentThread()) \
			throw DeadlockException(this, "Trying to crosslock against an unlocked lockable!"); \
		\
		Thread::getCurrentThread()->addAcquiredLockable(this, lockable, _monitorLockable); \
		DeadlockDetector::detectDeadlock(); \
		\
		Ancestor::lock(lockable); \
	} \
	\
	void lock(ManagedObject* obj) { \
		\
		if (obj == NULL) \
		 	 throw DeadlockException(this, "Trying to crosslock against a null lockable!"); \
		\
		if (!obj->isLockedByCurrentThread()) \
			throw DeadlockException(this, "Trying to crosslock against an unlocked lockable!"); \
		\
		Thread::getCurrentThread()->addAcquiredLockable(this, obj, _monitorLockable); \
		DeadlockDetector::detectDeadlock();\
		\
		Ancestor::lock(obj); \
	}\
 	 \
	inline bool isLockableMonitor() { \
		return _monitorLockable; \
	} \
	\
	inline void setLockableMonitor(bool val) { \
		_monitorLockable = val; \
	}


class DeadlockDetector {
public:
	static void detectDeadlock();
};

#endif /* DEADLOCKTESTBASE_H_ */
