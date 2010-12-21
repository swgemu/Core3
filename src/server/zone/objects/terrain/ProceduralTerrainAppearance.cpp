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
#include "PerlinNoise.h"

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

	IffStream* iffStream = NULL;

	FileInputStream* fileStream = NULL;
	File* fileObject = NULL;

	try {
		fileObject = new File(file);

		fileObject->setReadOnly();

		if (!fileObject->exists()) {
			fileObject->close();
			delete fileObject;
			fileObject == NULL;
			return false;
		}

		fileStream = new FileInputStream(fileObject);
	} catch (...) {
		delete fileObject;
		fileObject->close();
		fileObject = NULL;
		info("could not open " + file);

		throw;
	}

	int size = fileObject->size();

	sys::byte* data = new byte[size];

	fileStream->read(data, size);

	fileStream->close();
	delete fileStream;
	delete fileObject;

	iffStream = new IffStream();

	if (iffStream != NULL) {
		try {
			if (!iffStream->parseChunks(data, size, file)) {
				delete iffStream;
				iffStream = NULL;
			}
		} catch (...) {
			delete iffStream;
			iffStream = NULL;
		}
	}

	delete [] data;

	if (iffStream != NULL) {
		readObject(iffStream);

		delete iffStream;
		iffStream = NULL;

		terrainGenerator->processLayers();


		info("loading finished", true);

		return true;
	} else
		return false;


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

int ProceduralTerrainAppearance::tests() {
	MapGroup* mapGroup = terrainGenerator->getMapGroup();
	LayersGroup* layersGroup = terrainGenerator->getLayersGroup();

	Vector<Layer*>* layers = layersGroup->getLayers();

	for (int i = 0; i < layers->size(); ++i) {
		Layer* layer = layers->get(i);

		Vector<Layer*>* children = layer->getChildren();

		Vector<TerrainRule*>* rules = layer->getRules();

	}

	//mapGroup->getMfrc(id - 1);
}
