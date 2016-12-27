/*
 * ProceduralTerrainTemplate.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef PROCEDURALTERRAINAPPEARANCE_H_
#define PROCEDURALTERRAINAPPEARANCE_H_

#include "TemplateVariable.h"
#include "TerrainAppearance.h"
#include "engine/util/u3d/AABB.h"

class TerrainGenerator;
class Boundary;
class TerrainMaps;

class Layer;

class ProceduralTerrainAppearance : public TemplateVariable<'PTAT'>, public Logger, public TerrainAppearance {
	TerrainGenerator* terrainGenerator;

	Vector<Boundary*> waterBoundaries;

	TerrainMaps* terrainMaps;

	//float defaultHeight;

	String terrainFile;
	float size;
	float chunkSize;
	uint32 tilesPerChunk;

	uint32 useGlobalWaterTable;
	float globalWaterTableHeight;
	float globalWaterTableShaderSize;
	String globalWaterTableShader;

	float timeCycle;

	uint32 floraCollidableMinDistance;
	float floraCollidableMaxDistance;
	float floraCollidableTileSize;
	float floraCollidableTileBorder;
	float floraCollidableSeed;

	uint32 floraNonCollidableMinDistance;
	float floraNonCollidableMaxDistance;
	float floraNonCollidableTileSize;
	float floraNonCollidableTileBorder;
	float floraNonCollidableSeed;

	uint32 radialNearMinDistance;
	float radialNearMaxDistance;
	float radialNearTileSize;
	float radialNearTileBorder;
	float radialNearSeed;

	float radialFarMinDistance;
	float radialFarMaxDistance;
	float radialFarTileSize;
	float radialFarTileBorder;
	float radialFarSeed;

	ReadWriteLock guard;

	HashTable<uint64, TerrainGenerator*> terrainModifications;

	Vector<TerrainGenerator*> customTerrain;

protected:
	float calculateFeathering(float value, int featheringType);
	float processTerrain(Layer* layer, float x, float y, float& baseValue, float affectorTransformValue, int affectorType);
	Layer* getLayerRecursive(float x, float y, Layer* rootParent);
	Layer* getLayer(float x, float y);

	void translateBoundaries(Layer* layer, float x, float y);
	void setHeight(Layer* layer, float height);

public:
	ProceduralTerrainAppearance();
	~ProceduralTerrainAppearance();

	bool load(engine::util::IffStream* iffStream);

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, uint32 version);

	void insertWaterBoundary(Boundary* boundary) {
		waterBoundaries.add(boundary);
	}

	void getWaterBoundariesInAABB(const AABB& bounds, Vector<const Boundary*>* boundariesOut) const;

	/**
	 * Returns the size of the terrain.
	 * @return float The size of the terrain.
	 */
	float getSize() {
		return size;
	}

	bool getWater(float x, float y, float& waterHeight);
	float getHeight(float x, float y);
	int getEnvironmentID(float x, float y);

	float getGlobalWaterTableHeight() {
		return globalWaterTableHeight;
	}

	bool getUseGlobalWaterTable() {
		return useGlobalWaterTable;
	}
	ReadWriteLock* getGuard() {
		return &guard;
	}

	float getDistanceBetweenPoles() {
		return chunkSize / (tilesPerChunk * 2.0f);
	}

	TerrainGenerator* addTerrainModification(engine::util::IffStream* terrainGeneratorIffStream, float x, float y, uint64 objectid);
	TerrainGenerator* removeTerrainModification(uint64 objectid);

};

#endif /* PROCEDURALTERRAINAPPEARANCE_H_ */
