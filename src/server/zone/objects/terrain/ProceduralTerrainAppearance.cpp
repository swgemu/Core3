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

	useGlobalWaterTable = 0;
}

ProceduralTerrainAppearance::~ProceduralTerrainAppearance() {
	delete terrainGenerator;
	terrainGenerator = NULL;

	delete terrainMaps;
	terrainMaps = NULL;
}

bool ProceduralTerrainAppearance::load(const String& file) {
	setLoggingName(getLoggingName() + " " + file);

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

	//info(terrainFile);

	size = iffStream->getFloat();
	chunkSize = iffStream->getFloat();
	tilesPerChunk = iffStream->getUnsignedInt();
	useGlobalWaterTable = iffStream->getUnsignedInt();
	globalWaterTableHeight = iffStream->getFloat();
	globalWaterTableShaderSize = iffStream->getFloat();

	iffStream->getString(globalWaterTableShader);

	timeCycle = iffStream->getFloat(); // i have docs on how this works somewhere..

	floraCollidableMinDistance = iffStream->getUnsignedInt();
	floraCollidableMaxDistance = iffStream->getFloat();
	floraCollidableTileSize = iffStream->getFloat();
	floraCollidableTileBorder = iffStream->getFloat();
	floraCollidableSeed = iffStream->getUnsignedInt();

	floraNonCollidableMinDistance = iffStream->getUnsignedInt();
	floraNonCollidableMaxDistance = iffStream->getFloat();
	floraNonCollidableTileSize = iffStream->getFloat();
	floraNonCollidableTileBorder = iffStream->getFloat();
	floraNonCollidableSeed = iffStream->getUnsignedInt();

	radialNearMinDistance = iffStream->getUnsignedInt();
	radialNearMaxDistance = iffStream->getFloat();
	radialNearTileSize = iffStream->getFloat();
	radialNearTileBorder = iffStream->getFloat();
	radialNearSeed = iffStream->getUnsignedInt();

	radialFarMinDistance = iffStream->getFloat();
	radialFarMaxDistance = iffStream->getFloat();
	radialFarTileSize = iffStream->getFloat();
	radialFarTileBorder = iffStream->getFloat();
	radialFarSeed = iffStream->getUnsignedInt();

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

	if (useGlobalWaterTable != 0) {
		waterHeight = globalWaterTableHeight;
		return true;
	}

	return false;
}
