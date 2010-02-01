/*
 * ProceduralTerrainTemplate.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef PROCEDURALTERRAINAPPEARANCE_H_
#define PROCEDURALTERRAINAPPEARANCE_H_

#include "TemplateVariable.h"

class TerrainGenerator;
class Boundary;
class TerrainMaps;

class ProceduralTerrainAppearance : public TemplateVariable<'PTAT'>, public Logger {
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

public:
	ProceduralTerrainAppearance();
	~ProceduralTerrainAppearance();

	bool load(const String& file);

	void parseFromIffStream(engine::util::IffStream* iffStream);

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0014'>);

	void insertWaterBoundary(Boundary* boundary) {
		waterBoundaries.add(boundary);
	}

	bool getWater(float x, float y, float& waterHeight);
};


#endif /* PROCEDURALTERRAINAPPEARANCE_H_ */
