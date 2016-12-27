/*
 * SpawnAreaMap.cpp
 *
 *  Created on: 12/08/2011
 *      Author: TheAnswer
 */

#include "SpawnAreaMap.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/area/areashapes/CircularAreaShape.h"
#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"
#include "server/zone/objects/area/areashapes/RingAreaShape.h"

void SpawnAreaMap::loadMap(Zone* z) {
	zone = z;
	String planetName = zone->getZoneName();

	setLoggingName("SpawnAreaMap " + planetName);

	lua->init();

	try {
		loadRegions();
	} catch (Exception& e) {
		error(e.getMessage());
	}

	lua->deinit();

	delete lua;
	lua = NULL;
}

void SpawnAreaMap::loadRegions() {
	String planetName = zone->getZoneName();

	lua->runFile("scripts/managers/spawn_manager/" + planetName + "_regions.lua");

	LuaObject obj = lua->getGlobalObject(planetName + "_regions");

	if (obj.isValidTable()) {
		info("loading spawn areas...", true);

		lua_State* s = obj.getLuaState();

		for (int i = 1; i <= obj.getTableSize(); ++i) {
			lua_rawgeti(s, -1, i);
			LuaObject areaObj(s);

			if (areaObj.isValidTable()) {
				readAreaObject(areaObj);
			}

			areaObj.pop();
		}
	}

	obj.pop();

	for (int i = 0; i < size(); ++i) {
		SpawnArea* area = get(i);

		Locker locker(area);

		for (int j = 0; j < noSpawnAreas.size(); ++j) {
			SpawnArea* notHere = noSpawnAreas.get(j);

			if (area->intersectsWith(notHere)) {
				area->addNoSpawnArea(notHere);
			}
		}
	}
}

void SpawnAreaMap::readAreaObject(LuaObject& areaObj) {
	String name = areaObj.getStringAt(1);
	float x = areaObj.getFloatAt(2);
	float y = areaObj.getFloatAt(3);
	int tier = areaObj.getIntAt(5);

	if (tier == UNDEFINEDAREA)
		return;

	float radius = 0;
	float width = 0;
	float height = 0;
	float innerRadius = 0;
	float outerRadius = 0;

    LuaObject areaShapeObject = areaObj.getObjectAt(4);
    if (areaShapeObject.isValidTable()) {
        if (areaShapeObject.getIntAt(1) == 1) {
            radius = areaShapeObject.getFloatAt(2);
        } else if (areaShapeObject.getIntAt(1) == 2) {
            width = areaShapeObject.getFloatAt(2);
            height = areaShapeObject.getFloatAt(3);
        } else if (areaShapeObject.getIntAt(1) == 3) {
        	innerRadius = areaShapeObject.getFloatAt(2);
        	outerRadius = areaShapeObject.getFloatAt(3);
        }
        areaShapeObject.pop();
    } else {
    	areaShapeObject.pop();
        radius = areaObj.getFloatAt(4);
        width = 0;
        height = 0;
    }

	if (radius == 0 && width == 0 && height == 0 && innerRadius == 0 && outerRadius == 0)
		return;

	static const uint32 crc = STRING_HASHCODE("object/spawn_area.iff");

	ManagedReference<SpawnArea*> area = dynamic_cast<SpawnArea*>(ObjectManager::instance()->createObject(crc, 0, "spawnareas"));
	if (area == NULL)
		return;

	Locker objLocker(area);

	StringId nameID(zone->getZoneName() + "_region_names", name);

	area->setObjectName(nameID, false);

	if (height > 0 && width > 0) {
		ManagedReference<RectangularAreaShape*> rectangularAreaShape = new RectangularAreaShape();
		Locker shapeLocker(rectangularAreaShape);
		rectangularAreaShape->setAreaCenter(x, y);
		rectangularAreaShape->setDimensions(height, width);
		area->setAreaShape(rectangularAreaShape);
	} else if (radius > 0) {
		ManagedReference<CircularAreaShape*> circularAreaShape = new CircularAreaShape();
		Locker shapeLocker(circularAreaShape);
		circularAreaShape->setAreaCenter(x, y);
		circularAreaShape->setRadius(radius);
		area->setAreaShape(circularAreaShape);
	} else if (innerRadius > 0 && outerRadius > 0) {
		ManagedReference<RingAreaShape*> ringAreaShape = new RingAreaShape();
		Locker shapeLocker(ringAreaShape);
		ringAreaShape->setAreaCenter(x, y);
		ringAreaShape->setInnerRadius(innerRadius);
		ringAreaShape->setOuterRadius(outerRadius);
		area->setAreaShape(ringAreaShape);
	} else {
		ManagedReference<CircularAreaShape*> circularAreaShape = new CircularAreaShape();
		Locker shapeLocker(circularAreaShape);
		circularAreaShape->setAreaCenter(x, y);
		circularAreaShape->setRadius(zone->getBoundingRadius());
		area->setAreaShape(circularAreaShape);
	}

	area->setTier(tier);

	if (tier & SPAWNAREA) {
		area->setMaxSpawnLimit(areaObj.getIntAt(7));
		LuaObject spawnGroups = areaObj.getObjectAt(6);

		if (spawnGroups.isValidTable()) {
			Vector<uint32> groups;

			for (int i = 1; i <= spawnGroups.getTableSize(); i++) {
				groups.add(spawnGroups.getStringAt(i).hashCode());
			}

			area->buildSpawnList(&groups);
		}

		spawnGroups.pop();
	}

	if ((radius != -1) && !(tier & WORLDSPAWNAREA)) {
		zone->transferObject(area, -1, true);
	} else {
		if (tier & WORLDSPAWNAREA) {
			worldSpawnAreas.add(area);
		}

		area->setZone(zone);
	}

	area->updateToDatabase();

	put(nameID.getStringID().hashCode(), area);

	if (tier & NOSPAWNAREA) {
		area->setNoSpawnArea(true);
		noSpawnAreas.add(area);
	}

	if (tier & NOBUILDZONEAREA) {
		area->setNoBuildArea(true);
	}

}

void SpawnAreaMap::unloadMap() {
	noSpawnAreas.removeAll();
	worldSpawnAreas.removeAll();

	for (int i = 0; i < size(); i++) {
		SpawnArea* area = get(i);

		if (area != NULL) {
			Locker locker(area);
			area->destroyObjectFromWorld(false);
		}
	}

	removeAll();
}
