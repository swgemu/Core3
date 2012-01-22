/*
 * DirectorSharedMemory.h
 *
 *  Created on: Jun 1, 2011
 *      Author: theanswer
 */

#ifndef DIRECTORSHAREDMEMORY_H_
#define DIRECTORSHAREDMEMORY_H_

#include "engine/engine.h"

class DirectorSharedMemory : public Object {
	HashTable<String, uint64> hashTable;

public:
	uint64 get(const String& k) {
		return hashTable.get(k);
	}

	void put(const String& k, uint64 v) {
		hashTable.put(k, v);
	}

	void remove(const String& k) {
		hashTable.remove(k);
	}

	void setNullValue(uint64 o) {
		hashTable.setNullValue(o);
	}

	Object* clone() {
		return ObjectCloner<DirectorSharedMemory>::clone(this);
	}

	Object* clone(void* object) {
		return TransactionalObjectCloner<DirectorSharedMemory>::clone(this);
	}
};

#endif /* DIRECTORSHAREDMEMORY_H_ */
