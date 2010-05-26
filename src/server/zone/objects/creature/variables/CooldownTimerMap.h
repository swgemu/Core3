/*
 * CooldownTimerMap.h
 *
 *  Created on: 26/05/2010
 *      Author: victor
 */

#ifndef COOLDOWNTIMERMAP_H_
#define COOLDOWNTIMERMAP_H_

#include "engine/engine.h"

class CooldownTimerMap : private HashTable<String, Time*> {
	int hash(const String& k) {
		return k.hashCode();
	}

public:
	CooldownTimerMap() : HashTable<String, Time*>() {
		setNullValue(NULL);
	}

	~CooldownTimerMap() {
		HashTableIterator<String, Time*> iterator(((HashTable<String, Time*>*) this));

		while (iterator.hasNext())
			delete iterator.getNextValue();
	}

	bool isPast(const String& cooldownName) {
		Time* cooldown = HashTable<String, Time*>::get(cooldownName);

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
		Time* cooldown = HashTable<String, Time*>::get(cooldownName);

		if (cooldown == NULL) {
			cooldown = new Time();
			HashTable<String, Time*>::put(cooldownName, cooldown);
		} else {
			cooldown->updateToCurrentTime();
		}

		return cooldown;
	}

	void addMiliTime(const String& cooldownName, uint64 mili) {
		Time* cooldown = HashTable<String, Time*>::get(cooldownName);

		if (cooldown == NULL) {
			cooldown = new Time();
			cooldown->addMiliTime(mili);
			HashTable<String, Time*>::put(cooldownName, cooldown);
		} else {
			cooldown->addMiliTime(mili);
		}
	}
};


#endif /* COOLDOWNTIMERMAP_H_ */
