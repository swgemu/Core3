/*
 * SpawnAreaMap.cpp
 *
 *  Created on: 12/08/2011
 *      Author: TheAnswer
 */

#include "SpawnAreaMap.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "templates/params/creature/CreatureFlag.h"
#include "server/zone/objects/area/areashapes/CircularAreaShape.h"
#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"
#include "server/zone/objects/area/areashapes/RingAreaShape.h"

void SpawnAreaMap::unloadMap() {
	noSpawnAreas.removeAll();

	for (int i = 0; i < size(); i++) {
		SpawnArea* area = get(i);

		if (area != nullptr) {
			Locker locker(area);
			area->destroyObjectFromWorld(false);
		}
	}

	removeAll();
}
