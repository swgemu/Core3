/*
 * TerrainCache.cpp
 *
 *  Created on: Aug 15, 2015
 *      Author: TheAnswer
 */

#include "TerrainCache.h"
#include "TerrainManager.h"

#include "terrain/TerrainGenerator.h"

#include "system/util/Vector.h"

#define CACHE_CAPACITY 1024 * 1024
#define CACHE_MIN_ACCESS_COUNT 5
#define QT_MIN_SQUARE 16

namespace detail {
	inline uint64 hashPosition(const float x, const float y) {
		union {
			uint32 uval;
			float fval;
		} v;

		v.fval = x ;

		uint32 val1 = v.uval;

		v.fval = y;

		uint32 val2 = v.uval;

		uint64 hash = val1;

		return (hash << 32) | val2;
	}
}

class HeightQuadTreeEntry : public QuadTreeEntryInterface {
	float x, y;
public:
	HeightQuadTreeEntry(float x, float y) : x(x), y(y) {
	}

	int compareTo(const QuadTreeEntryInterfaceBase<BasicQuadTreeNode>* obj) const override {
		auto oid = getObjectID();
		auto targetOid = obj->getObjectID();

		if (oid < targetOid)
			return 1;
		else if (oid > targetOid)
			return -1;
		else
			return 0;
	}

	uint64 getObjectID() const override {
		return detail::hashPosition(x, y);
	}

	float getPositionX() const override {
		return x;
	}

	float getPositionY() const override {
		return y;
	}
};

class HeightCacheFunction : public LRUFunction2<uint64, float, float,
	Pair<QuadTreeEntryInterface*, float> > {
	TerrainManager* terrainData;

public:
	HeightCacheFunction(TerrainManager* app) : terrainData(app) {

	}

	TerrainCache::lru_value_t run(const float& k, const float& k2) override {
		float height = terrainData->getUnCachedHeight(k , k2);

		return make_pair(new HeightQuadTreeEntry(k, k2), height);
	}

	uint64 hash(const float& k, const float& k2) const override {
		return detail::hashPosition(k, k2);
	}
};

TerrainCache::TerrainCache(TerrainManager* terrainManager)
	: SynchronizedLRUCache2<uint64, float, float, Pair<QuadTreeEntryInterface*, float>>(new HeightCacheFunction(terrainManager), CACHE_CAPACITY, CACHE_MIN_ACCESS_COUNT),
	  Logger("TerrainCache"),
	  quadTree(terrainManager->getMin(), terrainManager->getMin(), terrainManager->getMax(), terrainManager->getMax(), QT_MIN_SQUARE),
	  clearCount(0),
	  clearHeightsCount(0),
	  evictCount(0),
	  max(terrainManager->getMax()),
	  min(terrainManager->getMin()) {
}

TerrainCache::~TerrainCache() {
	while (getSize() > 0) {
		evict();
	}
}

bool TerrainCache::insert(const float& k, const float& k2, const lru_value_t& v) {
	Locker writeLock(getLock());

	bool result = lru_cache_t::insert(k, k2, v);

	if (!result) {
		delete v.first;

		return result;
	}

	if (k >= max || k2 >= max
			|| k <= min || k2 <= min) {
		warning() << "position  (" << k << ", " << k2 << ") out of planet/cache bounds: ["
				<< min << ", " << max << "]";
	} else {
		quadTree.insert(v.first);
	}

	return true;
}

TerrainCache::lru_value_t TerrainCache::evict() {
	lru_value_t value = lru_cache_t::evict();

	quadTree.remove(value.first);

	delete value.first;

	++evictCount;

	return value;
}

float TerrainCache::getHeight(float x, float y) {
	lru_value_t result = (*this)(x, y);

	return result.second;
}

void TerrainCache::clear(TerrainGenerator* generator) {
	float centerX, centerY, radius;

	bool result = generator->getFullBoundaryCircle(centerX, centerY, radius);

	if (!result)
		return;

	Vector<QuadTreeEntryInterface*> heightsToDelete;

	Locker writeLock(getLock());

	++clearCount;

	clearHeightsCount += quadTree.inRange(centerX, centerY, radius, heightsToDelete);

	for (int i = 0; i < heightsToDelete.size(); ++i) {
		HeightQuadTreeEntry* entry = static_cast<HeightQuadTreeEntry*>(heightsToDelete.get(i));

		remove(entry->getObjectID());

		quadTree.remove(entry);

		delete entry;
	}
}
