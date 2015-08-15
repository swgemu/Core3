/*
 * TerrainCache.h
 *
 *  Created on: Aug 11, 2015
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_MANAGERS_TERRAIN_TERRAINCACHE_H_
#define SRC_SERVER_ZONE_MANAGERS_TERRAIN_TERRAINCACHE_H_

#include <utility>      // std::pair

#include "engine/util/lru/SynchronizedLRUCache.h"
#include "engine/util/u3d/BasicQuadTree.h"

class TerrainManager;
class TerrainGenerator;
class QuadTreeEntryInterface;

class TerrainCache : public SynchronizedLRUCache2<uint64, float, float, std::pair<QuadTreeEntryInterface*, float> > {
protected:
	typedef std::pair<QuadTreeEntryInterface*, float> lru_value_t;
	typedef SynchronizedLRUCache2<uint64, float, float, lru_value_t > lru_cache_t;

	BasicQuadTree quadTree;

	int clearCount;
	int clearHeightsCount;

public:
	TerrainCache(TerrainManager* terrainManager);

	bool insert(const float& k, const float& k2, const lru_value_t& v);

	void clear(TerrainGenerator* layers);

	lru_value_t evict();

	float getHeight(float x, float y);

	int getClearCount() {
		return clearCount;
	}

	int getClearHeightsCount() {
		return clearHeightsCount;
	}
};


#endif /* SRC_SERVER_ZONE_MANAGERS_TERRAIN_TERRAINCACHE_H_ */
