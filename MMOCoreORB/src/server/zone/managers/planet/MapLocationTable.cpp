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

	int index = locations.find(pmc->getName());

	if (index == -1) {
		SortedVector<MapLocationEntry> sorted;
		sorted.setNoDuplicateInsertPlan();

		MapLocationEntry entry(object);
		sorted.put(entry);

		locations.put(pmc->getName(), sorted);
	} else {
		SortedVector<MapLocationEntry>& vector = locations.elementAt(index).getValue();

		MapLocationEntry entry(object);
		vector.put(entry);
	}
}

void MapLocationTable::dropObject(SceneObject* object) {
	PlanetMapCategory* pmc = object->getPlanetMapCategory();

	if (pmc == NULL)
		return;

	int index = locations.find(pmc->getName());

	if (index != -1) {
		SortedVector<MapLocationEntry>& vector = locations.elementAt(index).getValue();

		MapLocationEntry entry(object);
		vector.drop(entry);

		if (vector.isEmpty())
			locations.remove(index);
	}
}

SortedVector<MapLocationEntry>& MapLocationTable::getLocation(const String& name) {
	return locations.get(name);
}

int MapLocationTable::findLocation(const String& name) {
	return locations.find(name);
}
