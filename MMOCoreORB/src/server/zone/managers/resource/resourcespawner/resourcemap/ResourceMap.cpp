/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file ResourceMap.cpp
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#include "ResourceMap.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

ResourceMap::ResourceMap() {
	setNoDuplicateInsertPlan();
	setNullValue(nullptr);

	zoneResourceMap.setNoDuplicateInsertPlan();
	zoneResourceMap.setNullValue(nullptr);

	typeResourceMap.setNullValue(nullptr);
}

ResourceMap::~ResourceMap() {
	removeAll();

	while (typeResourceMap.size() > 0) {
		TypeResourceMap* map = typeResourceMap.get(0);
		delete map;
		typeResourceMap.remove(0);
	}

	while (zoneResourceMap.size() > 0) {
		ZoneResourceMap* map = zoneResourceMap.get(0);
		delete map;
		zoneResourceMap.remove(0);
	}
}

float ResourceMap::getDensityAt(const String& resourcename, String zoneName, float x, float y) const {
	const auto& resourceSpawn = get(resourcename.toLowerCase());
	return resourceSpawn->getDensityAt(zoneName, x, y);
}

void ResourceMap::add(const String& resname, ManagedReference<ResourceSpawn* > resourceSpawn) {
	put(resname.toLowerCase(), resourceSpawn);

	/// Index the resources by type, for resource deeds
	TypeResourceMap* typemap = typeResourceMap.get(resourceSpawn->getFinalClass());
	if(typemap == nullptr) {
		typemap = new TypeResourceMap();
		typeResourceMap.put(resourceSpawn->getFinalClass(), typemap);
	}
	typemap->add(resourceSpawn);

	for(int i = 0; i < resourceSpawn->getSpawnMapSize(); ++i) {
		String zoneName = resourceSpawn->getSpawnMapZone(i);

		if (zoneName != "") {
			ZoneResourceMap* map = dynamic_cast<ZoneResourceMap*>(zoneResourceMap.get(zoneName));

			if(map == nullptr) {
				map = new ZoneResourceMap();
				zoneResourceMap.put(zoneName, map);
			}

			map->put(resourceSpawn->getName().toLowerCase(), resourceSpawn);
		}
	}
}
/**
 * Even though we want to drop items from the
 * Zone maps, we need to keep all spawns in the
 * ResourceMap for lookup.
 */
void ResourceMap::remove(ManagedReference<ResourceSpawn* > resourceSpawn) {

	for(int i = 0; i < resourceSpawn->getSpawnMapSize(); ++i) {
		String zoneName = resourceSpawn->getSpawnMapZone(i);

		if (zoneName != "") {
			ZoneResourceMap* map = dynamic_cast<ZoneResourceMap*>(zoneResourceMap.get(zoneName));

			if (map != nullptr)
				map->drop(resourceSpawn->getName().toLowerCase());
		}
	}
}

void ResourceMap::remove(ManagedReference<ResourceSpawn* > resourceSpawn, String zoneName) {
	ZoneResourceMap* map = dynamic_cast<ZoneResourceMap*>(zoneResourceMap.get(zoneName));

	if (map != nullptr)
		map->drop(resourceSpawn->getName().toLowerCase());
}

void ResourceMap::addToSuiListBox(SuiListBox* suil, const String& name) {

	TypeResourceMap* typemap = typeResourceMap.get(name);

	if(typemap == nullptr) {
		suil->addMenuItem("No resources to display");
		return;
	}

	SortedVector<ManagedReference<ResourceSpawn*>> spawns;

	for(int i = 0; i < typemap->size(); ++i) {
		ManagedReference<ResourceSpawn*> spawn = typemap->get(i);

		if(spawn == nullptr)
			continue;

		spawns.put(spawn);
	}

	for(int i = 0; i < spawns.size(); ++i){
		suil->addMenuItem(spawns.get(i)->getName(), spawns.get(i)->getObjectID());
	}

}

void ResourceMap::getTypeSubset(ResourceMap& subMap, const String& typeName) {
	for (int i = 0; i < size(); i++) {
		ManagedReference<ResourceSpawn*> spawn = get(i);
		if (spawn == nullptr)
			continue;

		for (int j = 0; j < 8; j++) {
			String thisClassName = spawn->getStfClass(j);
			if (thisClassName.isEmpty())
				continue;

			if (thisClassName == typeName)
				subMap.add(spawn->getName().toLowerCase(), spawn);
		}
	}
}

void ResourceMap::getAttributeSubset(ResourceMap& subMap, const String& attributeName) {
	for (int i = 0; i < size(); i++) {
		ManagedReference<ResourceSpawn*> spawn = get(i);
		if (spawn == nullptr)
			continue;

		for (int j = 0; j < 12; j++) {
			String thisAttributeName = "";
			int value = spawn->getAttributeAndValue(thisAttributeName, j);
			if (thisAttributeName.isEmpty())
				continue;

			if (thisAttributeName == attributeName)
				subMap.add(spawn->getName().toLowerCase(), spawn);
		}
	}
}
