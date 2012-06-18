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
	HashTable<String, String> stringTable;

public:
	uint64 get(const String& k) {
		return hashTable.get(k);
	}

	String getString(const String& k) {
		return stringTable.get(k);
	}

	void put(const String& k, uint64 v) {
		hashTable.put(k, v);
	}

	void putString(const String& k, const String& v) {
		stringTable.put(k, v);
	}

	void remove(const String& k) {
		hashTable.remove(k);
	}

	void removeString(const String& k) {
		stringTable.remove(k);
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
