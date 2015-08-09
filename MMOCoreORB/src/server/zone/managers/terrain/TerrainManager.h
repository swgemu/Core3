/*
 * TerrainManager.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef TERRAINMANAGER_H_
#define TERRAINMANAGER_H_


#include "engine/engine.h"
#include "server/zone/objects/terrain/TerrainAppearance.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

#include "engine/util/lru/SynchronizedLRUCache.h"

namespace server {
 namespace zone {
  class Zone;
 }
}

using namespace server::zone;

class ProceduralTerrainAppearance;

class TerrainManager : public Logger, public Object {
	Reference<TerrainAppearance*> terrainData;

	Zone* zone;

	SynchronizedLRUCache2<uint64, float, float, float>* heightCache;

public:
	TerrainManager(Zone* planet);
	TerrainManager(ManagedWeakReference<Zone*> planet);

	~TerrainManager();

	bool initialize(const String& terrainFile);

	inline bool getWaterHeight(float x, float y, float& waterHeight) {
		return terrainData->getWater(x, y, waterHeight);
	}

	/**
	 *  	|--------------- | x1,y1
	 *  	|----------------| <- stepping
	 *	    |----------------|
	 *  	|----------------|
	 *x0,y0 |----------------|
	 */
	float getHighestHeight(float x0, float y0, float x1, float y1, int stepping = 1);
	float getLowestHeight(float x0, float y0, float x1, float y1, int stepping = 1);
	float getHighestHeightDifference(float x0, float y0, float x1, float y1, int stepping = 1);

	int notifyPositionUpdate(CreatureObject* object);

	void addTerrainModification(float x, float y, const String& terrainModificationFilename, uint64 objectid);
	void removeTerrainModification(uint64 objectid);

	ProceduralTerrainAppearance* getProceduralTerrainAppearance();

	float getCachedHeight(float x, float y);
	float getUnCachedHeight(float x, float y);

	float getHeight(float x, float y);

	float getMin() {
		return terrainData->getSize() / 2 * -1;
	}

	float getMax() {
		return terrainData->getSize() / 2;
	}

	float getSize() {
		return terrainData->getSize();
	}

	int getCacheHitCount() {
		return heightCache->getHitCount();
	}

	int getCacheMissCount() {
		return heightCache->getMissCount();
	}
};


#endif /* TERRAINMANAGER_H_ */
