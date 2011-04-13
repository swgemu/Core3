#ifndef CAMPVISITORLIST_H_
#define CAMPVISITORLIST_H_

#include "engine/engine.h"

class CampVisitorList : public HashTable<uint64, uint64> , public HashTableIterator<uint64, uint64> {
	int hash(const uint64& key) {
        return Long::hashCode(key);
	}

public:
	CampVisitorList() : HashTable<uint64, uint64>(3) {
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
