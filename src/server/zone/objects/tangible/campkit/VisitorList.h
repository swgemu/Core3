#ifndef VISITORLIST_H_
#define VISITORLIST_H_

#include "engine/engine.h"

class VisitorList : public HashTable<uint64, uint64> , public HashTableIterator<uint64, uint64> {
	int hash(const uint64& key) {
        return Long::hashCode(key);
	}

public:
	VisitorList() : HashTable<uint64, uint64>(3), HashTableIterator<uint64, uint64>(this) {
		setNullValue(0);
	}

	void put(uint64 playerID, uint64 time) {
		HashTable<uint64, uint64>::put(playerID, time);
	}

	uint64 getTime(const uint64 playerID) {
		return HashTable<uint64,uint64>::get(playerID);
	}

};

#endif /*VISITORLIST_H_*/
