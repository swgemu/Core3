/*
 * TerrainCache.h
 *
 *  Created on: Aug 11, 2015
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_MANAGERS_TERRAIN_TERRAINCACHE_H_
#define SRC_SERVER_ZONE_MANAGERS_TERRAIN_TERRAINCACHE_H_

#include <utility>      // std::pair

#include "engine/engine.h"
#include "engine/log/Logger.h"
#include "engine/util/lru/SynchronizedLRUCache.h"
#include "engine/util/u3d/BasicQuadTree.h"
#include "system/platform.h"

class TerrainGenerator;
class TerrainManager;
namespace engine {
namespace util {
namespace u3d {
class QuadTreeEntryInterface;
}  // namespace u3d
}  // namespace util
}  // namespace engine

class TerrainCache : public SynchronizedLRUCache2<uint64, float, float, std::pair<QuadTreeEntryInterface*, float> >, public Logger {
public:
	typedef std::pair<QuadTreeEntryInterface*, float> lru_value_t;
	typedef SynchronizedLRUCache2<uint64, float, float, lru_value_t > lru_cache_t;

protected:
	BasicQuadTree quadTree;

	int clearCount;
	int clearHeightsCount;
	int evictCount;

	const float max, min;

public:
	TerrainCache(TerrainManager* terrainManager);

	~TerrainCache();

private:
	bool insert(const float& k, const float& k2, const lru_value_t& v);

	lru_value_t evict();

public:
	void clear(TerrainGenerator* layers);

	float getHeight(float x, float y);

	int getClearCount() {
		return clearCount;
	}

	int getClearHeightsCount() {
		return clearHeightsCount;
	}

	int getEvictCount() {
		return evictCount;
	}
};

#endif /* SRC_SERVER_ZONE_MANAGERS_TERRAIN_TERRAINCACHE_H_ */
