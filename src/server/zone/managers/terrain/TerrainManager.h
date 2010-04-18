/*
 * TerrainManager.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef TERRAINMANAGER_H_
#define TERRAINMANAGER_H_


#include "engine/engine.h"
#include "server/zone/objects/terrain/ProceduralTerrainAppearance.h"
#include "server/zone/objects/scene/SceneObjectObserver.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

class TerrainManager : public SceneObjectObserver {
	ProceduralTerrainAppearance terrainData;

	//Zone* zone;

public:
	TerrainManager(/*Zone* planet*/);

	void initialize(const String& terrainFile);

	inline bool getWaterHeight(float x, float y, float& waterHeight) {
		return terrainData.getWater(x, y, waterHeight);
	}

	int notify(SceneObject* object);
};


#endif /* TERRAINMANAGER_H_ */
