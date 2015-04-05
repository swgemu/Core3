/*
 * CooldownTimerMap.h
 *
 *  Created on: 26/05/2010
 *      Author: victor
 */

#ifndef COOLDOWNTIMERMAP_H_
#define COOLDOWNTIMERMAP_H_

#include "engine/engine.h"

class CooldownTimer : public Variable {
	Time timeStamp;

public:
	CooldownTimer() : Variable() {
		//timeStamp = NULL;
	}

	CooldownTimer(const Time& timestamp) : Variable() {
		timeStamp = timestamp;
	}

	CooldownTimer(const CooldownTimer& obj) : Variable() {
		timeStamp = obj.timeStamp;
	}

	CooldownTimer& operator=(const CooldownTimer& tim) {
		timeStamp = tim.timeStamp;

		return *this;
	}

	void operator=(Time obj) {
		timeStamp = obj;
	}

	bool toString(String& str) {
		timeStamp.toString(str);

		return true;
	}

	bool parseFromString(const String& str, int version = 0) {
		Time parsed;

		parsed.parseFromString(str);

		if (parsed.isPast())
			return false;

		timeStamp = parsed;

		return true;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		timeStamp.toBinaryStream(stream);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		Time parsed;

		parsed.parseFromBinaryStream(stream);

		if (parsed.isPast())
			return false;

		timeStamp = parsed;

		return true;
	}

	bool isPast() {
		return timeStamp.isPast();
	}

	void addMiliTime(uint64 mtime) {
		timeStamp.addMiliTime(mtime);
	}

	/*Time& get() {
		return timeStamp;
	}

	operator Time*() const {
		return &timeStamp;
	}*/

	Time* getTime() {
		return &timeStamp;
	}


};

class CooldownTimerMap : public Object {
	HashTable<String, CooldownTimer> timers;
	Mutex cooldownMutex;

public:
	CooldownTimerMap() : timers(1, 1) {
	}

	CooldownTimerMap(const CooldownTimerMap& map) : Object(), cooldownMutex() {
		timers = map.timers;
	}

	~CooldownTimerMap() {
	}

	CooldownTimerMap& operator=(const CooldownTimerMap& map) {
		if (this == &map)
			return *this;

		timers = map.timers;
		cooldownMutex = map.cooldownMutex;

		return *this;
	}

	bool isPast(const String& cooldownName) {
		Locker locker(&cooldownMutex);

		if (!timers.containsKey(cooldownName))
			return true;

		return timers.get(cooldownName).isPast();
	}

	void updateToCurrentAndAddMili(const String& cooldownName, uint64 mili) {
		Locker locker(&cooldownMutex);

		Time* cooldown = updateToCurrentTime(cooldownName);

		cooldown->addMiliTime(mili);
	}

	Time* updateToCurrentTime(const String& cooldownName) {
		Locker locker(&cooldownMutex);

		if (!timers.containsKey(cooldownName)) {
			timers.put(cooldownName, Time());
		}

		Time* cooldown = timers.get(cooldownName).getTime();
		cooldown->updateToCurrentTime();

		return cooldown;
	}

	void addMiliTime(const String& cooldownName, uint64 mili) {
		Locker locker(&cooldownMutex);

		if (!timers.containsKey(cooldownName)) {
			timers.put(cooldownName, Time());
		}

		Time* cooldown = timers.get(cooldownName).getTime();
		cooldown->addMiliTime(mili);
	}

	Time* getTime(const String& cooldownName) {
		Locker locker(&cooldownMutex);

		if (!timers.containsKey(cooldownName))
			return NULL;

		Time* cooldown = timers.get(cooldownName).getTime();

		return cooldown;
	}

	Object* clone() {
		return ObjectCloner<CooldownTimerMap>::clone(this);
	}

	Object* clone(void* object) {
		return TransactionalObjectCloner<CooldownTimerMap>::clone(this);
	}


};


#endif /* COOLDOWNTIMERMAP_H_ */
