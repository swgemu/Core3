/*
 * SpawnAreaImplementation.cpp
 *
 *  Created on: 11/12/2011
 *      Author: victor
 */

#include "SpawnArea.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/area/areashapes/AreaShape.h"

Vector3 SpawnAreaImplementation::getRandomPosition(SceneObject* player) {
	Vector3 position;
	bool positionFound = false;
	int retries = 10;

	while (!positionFound && retries-- > 0) {
		if (getZone() != NULL && areaShape->getRadius() >= getZone()->getBoundingRadius()) {
			position = areaShape->getRandomPosition(player->getWorldPosition(), 64.0f, 256.0f);
		} else {
			position = areaShape->getRandomPosition();
		}
		positionFound = true;

		for (int i = 0; i < noSpawnAreas.size(); ++i) {
			SpawnArea* noSpawnArea = noSpawnAreas.get(i);

			if (noSpawnArea->containsPoint(position.getX(), position.getY())) {
				positionFound = false;
				break;
			}
		}
	}

	if (!positionFound) {
		position.set(0, 0, 0);
	}

	return position;
}
