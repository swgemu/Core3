/*
 * TerrainManager.cpp
 *
 *  Created on: 18/04/2010
 *      Author: victor
 */

#include "TerrainManager.h"
#include "server/zone/Zone.h"

TerrainManager::TerrainManager(Zone* planet) : Logger("TerrainManager") {
	zone = planet;
}

void TerrainManager::initialize(const String& terrainFile) {
	terrainData.load(terrainFile);
}

/**
 *  	|----------------| x1,y1
 *  	|----------------| <- stepping
 *	    |----------------|
 *  	|----------------|
 *x0,y0 |----------------|
 */
float TerrainManager::getHighestHeight(float x0, float y0, float x1, float y1, int stepping) {
	/*StringBuffer msg2;
	msg2 << "getHeights for (x0, y0) = (" << x0 << ", " << y0 << ") (x1, y1) = (" << x1 << ", " << y1 << ")";
	info(msg2.toString(), true);*/

	int deltaX = fabs(x1 - x0);
	int deltaY = fabs(y1 - y0);

	float maxHeight = 0.f;

	for (int i = y0; i < y0 + deltaY; i += stepping) {
		for (int j = x0; j < x0 + deltaX; j += stepping) {
			float height = zone->getHeight(j, i);

			/*StringBuffer msg;
			msg << "chicking x:" << j << " y:" << i;
			info(msg.toString(), true);*/

			if (height > maxHeight)
				maxHeight = height;
		}
	}

	return maxHeight;
}

int TerrainManager::notify(SceneObject* object) {
	if (!object->isCreatureObject())
		return 0;

	CreatureObject* creature = (CreatureObject*) object;

	float waterHeight;

	if (creature->getParent() == NULL && getWaterHeight(creature->getPositionX(), creature->getPositionY(), waterHeight)) {
		//info("detected water height " + String::valueOf(waterHeight), true);

		//float roundingPositionZ = floor(creature->getPositionZ() * 10) / 10;

		float result = waterHeight - creature->getSwimHeight();
		/*StringBuffer msg;
				msg << "swimHeight: " << creature->getSwimHeight() << " rounding:" << roundingPositionZ << " positionZ :" << creature->getPositionZ() << " waterHeight - swimHeight:" << result;
				info(msg.toString(), true);*/

		float err = fabs(creature->getPositionZ() - result);

		if (err < 0.2) {
			//info("trying to set swimming state", true);
			creature->setState(CreatureState::SWIMMING);
		} else {
			creature->clearState(CreatureState::SWIMMING);
		}
	} else
		creature->clearState(CreatureState::SWIMMING);

	return 0;
}
