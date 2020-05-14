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
	lua = nullptr;
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
	float x2 = 0;
	float y2 = 0;
	float innerRadius = 0;
	float outerRadius = 0;

	LuaObject areaShapeObject = areaObj.getObjectAt(4);
	if (!areaShapeObject.isValidTable()) {
		error("Invalid area shape table for spawn region " + name);
		return;
	}

	int areaType = areaShapeObject.getIntAt(1);

	if (areaType == CIRCLE) {
		radius = areaShapeObject.getFloatAt(2);

		if (radius <= 0 && !(tier & WORLDSPAWNAREA)) {
			error("Invalid radius of " + String::valueOf(radius) + " must be > 0 for circular spawn region " + name);
			return;
		}
	} else if (areaType == RECTANGLE) {
		x2 = areaShapeObject.getFloatAt(2);
		y2 = areaShapeObject.getFloatAt(3);
		int rectWidth = x2 - x;
		int rectHeight = y2 - y;

		if (!(tier & WORLDSPAWNAREA) && (rectWidth <= 0 || rectHeight <= 0)) {
			error("Invalid corner coordinates for rectangular spawn region " + name + ", total height: " + String::valueOf(rectHeight) + ", total width: " + String::valueOf(rectWidth));
			return;
		}
	} else if (areaType == RING) {
		innerRadius = areaShapeObject.getFloatAt(2);
		outerRadius = areaShapeObject.getFloatAt(3);

		if (!(tier & WORLDSPAWNAREA)) {
			if (innerRadius <= 0) {
				error("Invalid inner radius of " + String::valueOf(innerRadius) + " must be > 0 for ring spawn region " + name);
				return;
			} else if (outerRadius <= 0) {
				error("Invalid outer radius of " + String::valueOf(outerRadius) + " must be > 0 for ring spawn region " + name);
				return;
			}
		}
	} else {
		error("Invalid area type of " + String::valueOf(areaType) + " for spawn region " + name);
		return;
	}

	areaShapeObject.pop();

	if (radius == 0 && x2 == 0 && y2 == 0 && innerRadius == 0 && outerRadius == 0)
		return;

	static const uint32 crc = STRING_HASHCODE("object/spawn_area.iff");

	ManagedReference<SpawnArea*> area = dynamic_cast<SpawnArea*>(ObjectManager::instance()->createObject(crc, 0, "spawnareas"));
	if (area == nullptr)
		return;

	Locker objLocker(area);

	StringId nameID(zone->getZoneName() + "_region_names", name);

	area->setObjectName(nameID, false);

	if (areaType == RECTANGLE) {
		ManagedReference<RectangularAreaShape*> rectangularAreaShape = new RectangularAreaShape();
		Locker shapeLocker(rectangularAreaShape);
		rectangularAreaShape->setDimensions(x, y, x2, y2);
		float centerX = x + ((x2 - x) / 2);
		float centerY = y + ((y2 - y) / 2);
		rectangularAreaShape->setAreaCenter(centerX, centerY);
		area->setAreaShape(rectangularAreaShape);
	} else if (areaType == CIRCLE) {
		ManagedReference<CircularAreaShape*> circularAreaShape = new CircularAreaShape();
		Locker shapeLocker(circularAreaShape);
		circularAreaShape->setAreaCenter(x, y);

		if (radius > 0)
			circularAreaShape->setRadius(radius);
		else
			circularAreaShape->setRadius(zone->getBoundingRadius());

		area->setAreaShape(circularAreaShape);
	} else if (areaType == RING) {
		ManagedReference<RingAreaShape*> ringAreaShape = new RingAreaShape();
		Locker shapeLocker(ringAreaShape);
		ringAreaShape->setAreaCenter(x, y);
		ringAreaShape->setInnerRadius(innerRadius);
		ringAreaShape->setOuterRadius(outerRadius);
		area->setAreaShape(ringAreaShape);
	}

	area->setTier(tier);
	area->initializePosition(x, 0, y);

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

		if (area != nullptr) {
			Locker locker(area);
			area->destroyObjectFromWorld(false);
		}
	}

	removeAll();
}
