/*
 * MapLocationTable.cpp
 *
 *  Created on: 24/06/2010
 *      Author: victor
 */

#include "MapLocationTable.h"
#include "templates/manager/PlanetMapCategory.h"
#include "server/zone/objects/scene/SceneObject.h"

void MapLocationTable::transferObject(SceneObject* object) {
	PlanetMapCategory* pmc = object->getPlanetMapSubCategory();

	if (pmc == NULL)
		pmc = object->getPlanetMapCategory();

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
	PlanetMapCategory* pmc = object->getPlanetMapSubCategory();

	if (pmc == NULL)
		pmc = object->getPlanetMapCategory();

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

bool MapLocationTable::containsObject(SceneObject* object) {
	PlanetMapCategory* pmc = object->getPlanetMapSubCategory();

	if (pmc == NULL)
		pmc = object->getPlanetMapCategory();

	if (pmc == NULL)
		return false;

	int index = locations.find(pmc->getName());

	if (index != -1) {
		SortedVector<MapLocationEntry>& vector = locations.elementAt(index).getValue();

		for (int i = 0; i < vector.size(); i++) {
			MapLocationEntry entry = vector.get(i);

			if (entry.getObjectID() == object->getObjectID()) {
				return true;
			}
		}
	}

	return false;
}

void MapLocationTable::updateObjectsIcon(SceneObject* object, byte icon) {
	PlanetMapCategory* pmc = object->getPlanetMapSubCategory();

	if (pmc == NULL)
		pmc = object->getPlanetMapCategory();

	if (pmc == NULL)
		return;

	int index = locations.find(pmc->getName());

	if (index != -1) {
		SortedVector<MapLocationEntry>& vector = locations.elementAt(index).getValue();

		for (int i = 0; i < vector.size(); i++) {
			MapLocationEntry entry = vector.get(i);

			if (entry.getObjectID() == object->getObjectID()) {
				vector.drop(entry);
				entry.setIcon(icon);
				vector.put(entry);
				return;
			}
		}
	}
}

SortedVector<MapLocationEntry>& MapLocationTable::getLocation(const String& name) {
	return locations.get(name);
}

int MapLocationTable::findLocation(const String& name) {
	return locations.find(name);
}
