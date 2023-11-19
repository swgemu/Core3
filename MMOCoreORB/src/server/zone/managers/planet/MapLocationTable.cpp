/*
 * MapLocationTable.cpp
 *
 *  Created on: 24/06/2010
 *      Author: victor
 */

#include "MapLocationTable.h"
#include "MapLocationType.h"
#include "templates/manager/PlanetMapCategory.h"
#include "templates/manager/PlanetMapSubCategory.h"
#include "server/zone/objects/scene/SceneObject.h"

void MapLocationTable::transferObject(SceneObject* object) {
	if (object == nullptr)
		return;

	// Get the objects Primary map category
	const PlanetMapCategory* pmc = object->getPlanetMapCategory();

	if (pmc == nullptr)
		return;

	// Get the primary category name
	String pmcName = pmc->getName();
	int index = locations.find(pmcName);

	// Primary Map Category is not on the list, add the new category
	if (index == -1) {
		SortedVector<MapLocationEntry> sorted;
		sorted.setNoDuplicateInsertPlan();

		MapLocationEntry entry(object);
		sorted.put(entry);

		locations.put(pmcName, sorted);

		return;
	}

	SortedVector<MapLocationEntry>& vector = locations.elementAt(index).getValue();
	MapLocationEntry entry(object);

	vector.put(entry);
}

void MapLocationTable::dropObject(SceneObject* object) {
	const PlanetMapCategory* pmc = object->getPlanetMapCategory();

	if (pmc == nullptr)
		return;

	int index = locations.find(pmc->getName());

	if (index == -1)
		return;

	SortedVector<MapLocationEntry>& vector = locations.elementAt(index).getValue();

	MapLocationEntry entry(object);
	vector.drop(entry);

	if (vector.isEmpty())
		locations.remove(index);
}

bool MapLocationTable::containsObject(SceneObject* object) const {
	const PlanetMapCategory* pmc = object->getPlanetMapCategory();

	if (pmc == nullptr)
		return false;

	int index = locations.find(pmc->getName());

	if (index == -1)
		return false;

	const SortedVector<MapLocationEntry>& vector = locations.elementAt(index).getValue();

	for (int i = 0; i < vector.size(); i++) {
		const auto& entry = vector.get(i);

		if (entry.getObjectID() == object->getObjectID()) {
			return true;
		}
	}

	return false;
}

void MapLocationTable::updateObjectsIcon(SceneObject* object, byte icon) {
	const PlanetMapCategory* pmc = object->getPlanetMapCategory();

	if (pmc == nullptr)
		return;

	int index = locations.find(pmc->getName());

	if (index == -1)
		return;

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

const SortedVector<MapLocationEntry>& MapLocationTable::getLocation(const String& name) const {
	int index = -1;

	for (int i = 0; i < locations.size(); ++i) {
		String locName = locations.elementAt(i).getKey();

		if (!locName.contains(name))
			continue;

		index = i;
		break;
	}

	return locations.elementAt(index).getValue();
}

int MapLocationTable::findLocation(const String& name) const {
	return locations.find(name);
}
