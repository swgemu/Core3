#ifndef RECOVERYLIST_H_
#define RECOVERYLIST_H_

#include "engine/engine.h"
#include "events/CampRecoveryEvent.h"

class RecoveryList : public HashTable<uint64, CampRecoveryEvent*> , public HashTableIterator<uint64, CampRecoveryEvent*> {
	int hash(const uint64& key) {
        return Long::hashCode(key);
	}

public:
	RecoveryList() : HashTable<uint64, CampRecoveryEvent*>(3), HashTableIterator<uint64, CampRecoveryEvent*>(this) {
		setNullValue(NULL);
	}

	void put(uint64 playerID, CampRecoveryEvent* event) {
		HashTable<uint64, CampRecoveryEvent*>::put(playerID, event);
	}

	CampRecoveryEvent* getEvent(const uint64 playerID) {
		return HashTable<uint64,CampRecoveryEvent*>::get(playerID);
	}

};

#endif /*RECOVERYLIST_H_*/
