/*
 * ContainerObjectsMap.cpp
 *
 *  Created on: 13/10/2012
 *      Author: victor
 */

#include "ContainerObjectsMap.h"
#include "server/zone/objects/scene/SceneObject.h"


ContainerObjectsMap::ContainerObjectsMap() {
	operationMode = NORMAL_LOAD;
	containerObjects.setNoDuplicateInsertPlan();

	oids = NULL;
}

ContainerObjectsMap::ContainerObjectsMap(const ContainerObjectsMap& c) {
	operationMode = NORMAL_LOAD;
	containerObjects.setNoDuplicateInsertPlan();

	oids = NULL;

	copyData(c);
}

ContainerObjectsMap::~ContainerObjectsMap() {
	if (oids != NULL) {
		delete oids;
		oids = NULL;
	}
}

void ContainerObjectsMap::copyData(const ContainerObjectsMap& c) {
	operationMode = c.operationMode;
	containerObjects = c.containerObjects;

	if (c.oids == NULL) {
		if (oids != NULL)
			delete oids;

		oids = NULL;
	} else {
		oids = new VectorMap<uint64, uint64>(*c.oids);
	}
}

ContainerObjectsMap& ContainerObjectsMap::operator=(const ContainerObjectsMap& c) {
	if (this == &c)
		return *this;

	copyData(c);

	return *this;
}

void ContainerObjectsMap::loadObjects() {
	if (oids == NULL)
		return;

	Locker locker(&loadMutex);

	if (oids == NULL)
		return;

	for (int i = 0; i < oids->size(); ++i) {
		uint64 oid = oids->elementAt(i).getKey();

		ManagedReference<SceneObject*> object = cast<SceneObject*>(Core::getObjectBroker()->lookUp(oid));

		if (object != NULL)
			containerObjects.put(oid, object);
	}

	delete oids;
	oids = NULL;
}

void ContainerObjectsMap::notifyLoadFromDatabase() {

}

bool ContainerObjectsMap::toBinaryStream(ObjectOutputStream* stream) {
	Locker locker(&loadMutex);

	if (oids != NULL)
		return oids->toBinaryStream(stream);
	else
		return containerObjects.toBinaryStream(stream);
}

bool ContainerObjectsMap::parseFromBinaryStream(ObjectInputStream* stream) {
	switch (operationMode) {
	case NORMAL_LOAD:
		return containerObjects.parseFromBinaryStream(stream);
	case DELAYED_LOAD:
		if (oids == NULL)
			oids = new VectorMap<uint64, uint64>();

		return oids->parseFromBinaryStream(stream);
	default:
		return containerObjects.parseFromBinaryStream(stream);
	}

	return false;
}

VectorMap<uint64, ManagedReference<SceneObject*> >* ContainerObjectsMap::getContainerObjects() {
	loadObjects();

	return &containerObjects;
}

ManagedReference<SceneObject*> ContainerObjectsMap::get(int index) {
	loadObjects();

	return containerObjects.get(index);
}

ManagedReference<SceneObject*> ContainerObjectsMap::get(uint64 oid) {
	loadObjects();

	return containerObjects.get(oid);
}

void ContainerObjectsMap::put(uint64 oid, SceneObject* object) {
	loadObjects();

	containerObjects.put(oid, object);
}

void ContainerObjectsMap::removeElementAt(int index) {
	Locker locker(&loadMutex);

	if (oids != NULL)
		oids->removeElementAt(index);
	else
		containerObjects.removeElementAt(index);
}

int ContainerObjectsMap::size() {
	loadObjects();

	return containerObjects.size();

	/*
	Locker locker(&loadMutex);

	if (oids != NULL)
		return oids->size();
	else
		return containerObjects.size();

		*/
}

bool ContainerObjectsMap::contains(uint64 oid) {
	Locker locker(&loadMutex);

	if (oids != NULL)
		return oids->contains(oid);
	else
		return containerObjects.contains(oid);
}

void ContainerObjectsMap::removeAll() {
	Locker locker(&loadMutex);

	if (oids != NULL)
		oids->removeAll();
	else
		containerObjects.removeAll();
}

void ContainerObjectsMap::drop(uint64 oid) {
	Locker locker(&loadMutex);

	if (oids != NULL)
		oids->drop(oid);
	else
		containerObjects.drop(oid);
}

