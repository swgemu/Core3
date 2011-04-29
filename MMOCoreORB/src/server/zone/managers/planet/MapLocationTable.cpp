/*
 * MapLocationTable.cpp
 *
 *  Created on: 24/06/2010
 *      Author: victor
 */

#include "MapLocationTable.h"
#include "server/zone/managers/templates/PlanetMapCategory.h"
#include "server/zone/objects/scene/SceneObject.h"

void MapLocationTable::addObject(SceneObject* object) {
	PlanetMapCategory* pmc = object->getPlanetMapCategory();

	if (pmc == NULL)
		return;

	int index = find(pmc->getName());

	if (index == -1) {
		SortedVector<MapLocationEntry> sorted;
		sorted.setNoDuplicateInsertPlan();

		MapLocationEntry entry(object);
		sorted.put(entry);

		put(pmc->getName(), sorted);
	} else {
		SortedVector<MapLocationEntry>* vector = &this->elementAt(index).getValue();

		MapLocationEntry entry(object);
		vector->put(entry);
	}
}

void MapLocationTable::dropObject(SceneObject* object) {
	PlanetMapCategory* pmc = object->getPlanetMapCategory();

	if (pmc == NULL)
		return;

	int index = find(pmc->getName());

	if (index != -1) {
		SortedVector<MapLocationEntry>* vector = &this->elementAt(index).getValue();

		MapLocationEntry entry(object);
		vector->drop(entry);

		if (vector->size() == 0)
			remove(index);
	}
}
