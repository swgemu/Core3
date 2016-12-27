/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OBJECTMAP_H_
#define OBJECTMAP_H_

#include "server/zone/objects/scene/SceneObject.h"

class ObjectMap : public Object {
	HashTable<uint64, ManagedReference<SceneObject*> > objects;

	int maxConnections;

public:
	ObjectMap() : objects(3000), maxConnections(50000) {
	}

	ObjectMap(int initsize) : objects(initsize), maxConnections(50000) {
	}

	ManagedReference<SceneObject*> put(uint64 oid, SceneObject* object) {
		return objects.put(oid, object);
	}

	ManagedReference<SceneObject*> remove(uint64 oid) {
		return objects.remove(oid);
	}

	HashTableIterator<uint64, ManagedReference<SceneObject*> > iterator() {
		return objects.iterator();
	}

	HashTable<uint64, ManagedReference<SceneObject*> >* getMap() {
		return &objects;
	}
};

#endif /*OBJECTMAP_H_*/
