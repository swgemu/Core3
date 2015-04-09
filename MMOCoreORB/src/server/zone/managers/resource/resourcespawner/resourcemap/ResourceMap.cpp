/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

/**
 * \file ResourceMap.cpp
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#include "ResourceMap.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

ResourceMap::ResourceMap() {
	setNoDuplicateInsertPlan();
	setNullValue(NULL);

	zoneResourceMap.setNoDuplicateInsertPlan();
	zoneResourceMap.setNullValue(NULL);

	typeResourceMap.setNullValue(NULL);
}

ResourceMap::~ResourceMap() {
	removeAll();
}

float ResourceMap::getDensityAt(const String& resourcename, String zoneName, float x, float y) {
	ManagedReference<ResourceSpawn* > resourceSpawn = get(resourcename.toLowerCase());
	return resourceSpawn->getDensityAt(zoneName, x, y);
}

void ResourceMap::add(const String& resname, ManagedReference<ResourceSpawn* > resourceSpawn) {
	put(resname.toLowerCase(), resourceSpawn);

	/// Index the resources by type, for resource deeds
	TypeResourceMap* typemap = typeResourceMap.get(resourceSpawn->getFinalClass());
	if(typemap == NULL) {
		typemap = new TypeResourceMap();
		typeResourceMap.put(resourceSpawn->getFinalClass(), typemap);
	}
	typemap->add(resourceSpawn);

	for(int i = 0; i < resourceSpawn->getSpawnMapSize(); ++i) {
		String zoneName = resourceSpawn->getSpawnMapZone(i);

		if (zoneName != "") {
			ZoneResourceMap* map = dynamic_cast<ZoneResourceMap*>(zoneResourceMap.get(zoneName));

			if(map == NULL) {
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

			if (map != NULL)
				map->drop(resourceSpawn->getName().toLowerCase());
		}
	}
}

void ResourceMap::remove(ManagedReference<ResourceSpawn* > resourceSpawn, String zoneName) {
	ZoneResourceMap* map = dynamic_cast<ZoneResourceMap*>(zoneResourceMap.get(zoneName));

	if (map != NULL)
		map->drop(resourceSpawn->getName().toLowerCase());
}

void ResourceMap::addToSuiListBox(SuiListBox* suil, const String& name) {

	TypeResourceMap* typemap = typeResourceMap.get(name);

	if(typemap == NULL) {
		suil->addMenuItem("No resources to display");
		return;
	}

	for(int i = 0; i < typemap->size(); ++i) {
		ManagedReference<ResourceSpawn*> spawn = typemap->get(i);

		if(spawn == NULL)
			continue;

		suil->addMenuItem(spawn->getName(), spawn->getObjectID());
	}

}

void ResourceMap::getTypeSubset(ResourceMap& subMap, const String& typeName) {
	for (int i = 0; i < size(); i++) {
		ManagedReference<ResourceSpawn*> spawn = get(i);
		if (spawn == NULL)
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
		if (spawn == NULL)
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
