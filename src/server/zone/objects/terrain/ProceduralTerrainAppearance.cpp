/*
 * ProceduralTerrainAppearance.cpp
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#include "ProceduralTerrainAppearance.h"
#include "TerrainGenerator.h"
#include "TerrainMaps.h"
#include "layer/boundaries/Boundary.h"

ProceduralTerrainAppearance::ProceduralTerrainAppearance() : Logger("ProceduralTerrainAppearance") {
	terrainGenerator = new TerrainGenerator(this);
	terrainMaps = new TerrainMaps();
}

ProceduralTerrainAppearance::~ProceduralTerrainAppearance() {
	delete terrainGenerator;
	terrainGenerator = NULL;

	delete terrainMaps;
	terrainMaps = NULL;
}

bool ProceduralTerrainAppearance::load(const String& file) {
	IffStream* iffStream;

	try {
		iffStream = new IffStream(file);
	} catch (...) {
		iffStream = NULL;
		throw;
	}

	if (!iffStream->parseChunks())
		return false;

	readObject(iffStream);

	delete iffStream;
	iffStream = NULL;

	terrainGenerator->processLayers();

	info("loading finished", true);
	System::out << "water table boundaries " << waterBoundaries.size() << endl;

	return true;
}

void ProceduralTerrainAppearance::parseFromIffStream(engine::util::IffStream* iffStream) {
	uint32 version = iffStream->getNextFormType();

	iffStream->openForm(version);

	switch (version) {
	case '0014':
		parseFromIffStream(iffStream, Version<'0014'>());
		break;
	default:
		error("unknown version in ProceduralTerrainAppearance::parseFromIffStream " + String::valueOf(version));
		break;
	}

	iffStream->closeForm(version);
}

void ProceduralTerrainAppearance::parseFromIffStream(engine::util::IffStream* iffStream, Version<'0014'>) {
	iffStream->openChunk('DATA');

	iffStream->getString(terrainFile);

	info(terrainFile, true);

	size = iffStream->getFloat();
	chunkSize = iffStream->getFloat();
	tilesPerChunk = iffStream->getUnsignedInt();
	useGlobalWaterTable = iffStream->getUnsignedInt();
	globalWaterTableHeight = iffStream->getFloat();
	globalWaterTableShaderSize = iffStream->getFloat();

	iffStream->getString(globalWaterTableShader);

	float var9 = iffStream->getFloat();
	uint32 var10 = iffStream->getUnsignedInt();
	float var11 = iffStream->getFloat();
	float var12 = iffStream->getFloat();
	float var13 = iffStream->getFloat();
	uint32 var14 = iffStream->getUnsignedInt();
	uint32 var15 = iffStream->getUnsignedInt();
	float var16 = iffStream->getFloat();
	float var17 = iffStream->getFloat();
	float var18 = iffStream->getFloat();
	uint32 var19 = iffStream->getUnsignedInt();
	uint32 var20 = iffStream->getUnsignedInt();
	float var21 = iffStream->getFloat();
	float var22 = iffStream->getFloat();
	float var23 = iffStream->getFloat();
	uint32 var24 = iffStream->getUnsignedInt();
	float var25 = iffStream->getFloat();
	float var26 = iffStream->getFloat();
	float var27 = iffStream->getFloat();
	float var28 = iffStream->getFloat();
	uint32 var29 = iffStream->getUnsignedInt();

	iffStream->closeForm('DATA');

	terrainGenerator->readObject(iffStream);

	terrainMaps->readObject(iffStream);
}

bool ProceduralTerrainAppearance::getWater(float x, float y, float& waterHeight) {
	for (int i = 0; i < waterBoundaries.size(); ++i) {
		Boundary* boundary = waterBoundaries.get(i);

		if (boundary->containsPoint(x, y)) {
			waterHeight = boundary->getLocalWaterTableHeight();
			return true;
		}
	}

	return false;
}
