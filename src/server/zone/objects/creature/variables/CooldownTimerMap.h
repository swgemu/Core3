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
	Time* timeStamp;

public:
	CooldownTimer() : Variable() {
		timeStamp = NULL;
	}

	CooldownTimer(Time* timestamp) : Variable() {
		timeStamp = timestamp;
	}

	CooldownTimer(const CooldownTimer& obj) : Variable() {
		timeStamp = obj.timeStamp;
	}

	void operator=(Time* obj) {
		timeStamp = obj;
	}

	bool toString(String& str) {
		timeStamp->toString(str);

		return true;
	}

	bool parseFromString(const String& str, int version = 0) {
		if (timeStamp != NULL) {
			timeStamp->parseFromString(str);
		} else {
			Time newTimeStamp;
			newTimeStamp.parseFromString(str);

			if (!newTimeStamp.isPast())
				timeStamp = new Time(newTimeStamp);
			else
				return false;
		}

		return true;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		timeStamp->toBinaryStream(stream);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		if (timeStamp != NULL) {
			timeStamp->parseFromBinaryStream(stream);
		} else {
			Time newTimeStamp;
			newTimeStamp.parseFromBinaryStream(stream);

			if (!newTimeStamp.isPast())
				timeStamp = new Time(newTimeStamp);
			else
				return false;
		}

		return true;
	}

	Time* operator->() const {
		return timeStamp;
	}

	Time* get() const {
		return timeStamp;
	}

	operator Time*() const {
		return timeStamp;
	}


};

class CooldownTimerMap : public Object {
	HashTable<String, CooldownTimer> timers;

public:
	CooldownTimerMap() {
	}

	~CooldownTimerMap() {
		HashTableIterator<String, CooldownTimer> iterator = timers.iterator();

		while (iterator.hasNext())
			delete iterator.getNextValue().get();
	}

	bool isPast(const String& cooldownName) {
		Time* cooldown = timers.get(cooldownName);

		if (cooldown == NULL)
			return true;
		else
			return cooldown->isPast();
	}

	void updateToCurrentAndAddMili(const String& cooldownName, uint64 mili) {
		Time* cooldown = updateToCurrentTime(cooldownName);

		cooldown->addMiliTime(mili);
	}

	Time* updateToCurrentTime(const String& cooldownName) {
		Time* cooldown = timers.get(cooldownName);

		if (cooldown == NULL) {
			cooldown = new Time();
			timers.put(cooldownName, cooldown);
		} else {
			cooldown->updateToCurrentTime();
		}

		return cooldown;
	}

	void addMiliTime(const String& cooldownName, uint64 mili) {
		Time* cooldown = timers.get(cooldownName);

		if (cooldown == NULL) {
			cooldown = new Time();
			cooldown->addMiliTime(mili);
			timers.put(cooldownName, cooldown);
		} else {
			cooldown->addMiliTime(mili);
		}
	}

	Time* getTime(const String& cooldownName) {
		Time* cooldown = timers.get(cooldownName);

		if (cooldown == NULL)
			return NULL;
		else
			return cooldown;
	}


};


#endif /* COOLDOWNTIMERMAP_H_ */
