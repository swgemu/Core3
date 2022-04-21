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
	HashTable<String, Vector3> vector3Table;
	HashTable<String, Vector<String>> stringVectorTable;

public:
	uint64 get(const String& k) const {
		return hashTable.get(k);
	}

	const String& getString(const String& k) const {
		return stringTable.get(k);
	}

	Vector3 getVector3(const String& k) const {
		return vector3Table.get(k);
	}

	Vector<String> getStringVector(const String& k) const {
		return stringVectorTable.get(k);
	}

	void put(const String& k, uint64 v) {
		hashTable.put(k, v);
	}

	void putString(const String& k, const String& v) {
		stringTable.put(k, v);
	}

	void putVector3(const String& k, const Vector3& v) {
		vector3Table.put(k, v);
	}

	void putStringVector(const String& k, const Vector<String>& v) {
		stringVectorTable.put(k, v);
	}

	void remove(const String& k) {
		hashTable.remove(k);
	}

	void removeString(const String& k) {
		stringTable.remove(k);
	}

	void removeVector3(const String& k) {
		vector3Table.remove(k);
	}

	void removeStringVector(const String& k) {
		stringVectorTable.remove(k);
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
