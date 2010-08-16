/*
 * MapLocationTable.cpp
 *
 *  Created on: 24/06/2010
 *      Author: victor
 */

#include "MapLocationTable.h"
#include "server/zone/objects/scene/SceneObject.h"

void MapLocationTable::addObject(SceneObject* object) {
	uint8 type1 = object->getMapLocationsType1();
	uint8 type2 = object->getMapLocationsType2();
	uint8 type3 = object->getMapLocationsType3();

	if ((type1 == 0) && (type2 == 0) && (type3 == 0) /*&& !object->isPlayerCreature()*/)
		return;

	uint8 typeToRegister = type2;

	if (type2 == 0)
		typeToRegister = type1;

	int index = find(typeToRegister);

	if (index == -1) {
		SortedVector<MapLocationEntry> sorted;
		sorted.setNoDuplicateInsertPlan();

		MapLocationEntry entry(object, type1, type2, type3);
		sorted.put(entry);

		this->put(typeToRegister, sorted);
	} else {
		SortedVector<MapLocationEntry>* vector = &this->elementAt(index).getValue();

		MapLocationEntry entry(object, type1, type2, type3);
		vector->put(entry);
	}
}

void MapLocationTable::dropObject(SceneObject* object) {
	uint8 type2 = object->getMapLocationsType2();

	uint8 typeToRegister = type2;

	if (type2 == 0)
		typeToRegister = object->getMapLocationsType1();

	int index = find(typeToRegister);

	if (index != -1) {
		SortedVector<MapLocationEntry>* vector = &this->elementAt(index).getValue();

		MapLocationEntry entry(object, 0, type2, 0);
		vector->drop(entry);

		if (vector->size() == 0)
			this->remove(index);
	}
}
