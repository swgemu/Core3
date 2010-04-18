/*
 * TerrainManager.cpp
 *
 *  Created on: 18/04/2010
 *      Author: victor
 */

#include "TerrainManager.h"

TerrainManager::TerrainManager(/*Zone* planet*/) {
	//zone = planet;
}

void TerrainManager::initialize(const String& terrainFile) {
	terrainData.load(terrainFile);
}

int TerrainManager::notify(SceneObject* object) {
	if (!object->isCreatureObject())
		return 0;

	CreatureObject* creature = (CreatureObject*) object;

	float waterHeight;

	if (creature->getParent() == NULL && getWaterHeight(creature->getPositionX(), creature->getPositionY(), waterHeight)) {
		//info("detected water height " + String::valueOf(waterHeight), true);

		float roundingPositionZ = floor(creature->getPositionZ() * 10) / 10;

		float result = waterHeight - creature->getSwimHeight();
		/*StringBuffer msg;
				msg << "swimHeight: " << swimHeight << " rounding:" << roundingPositionZ << " positionZ :" << positionZ << " waterHeight - swimHeight:" << result;
				info(msg.toString(), true);*/

		if (roundingPositionZ + 0.1f == result || roundingPositionZ - 0.1f == result) {
			//info("trying to set swimming state", true);
			creature->setState(CreatureState::SWIMMING);
		} else {
			creature->clearState(CreatureState::SWIMMING);
		}
	} else
		creature->clearState(CreatureState::SWIMMING);

	return 0;
}
