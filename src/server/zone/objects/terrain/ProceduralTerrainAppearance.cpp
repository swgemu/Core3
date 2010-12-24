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
	waterBoundaries.removeAll();

	delete terrainGenerator;
	delete terrainMaps;

	terrainGenerator = new TerrainGenerator(this);
	terrainMaps = new TerrainMaps();


	setLoggingName("ProceduralTerrainAppearance " + file);

	info("trying to open", true);

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
		error("could not open " + file);

		throw;
	}

	info("fileobject opened", true);

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

				error("false on parsing chunks");
			}
		} catch (Exception& e) {
			delete iffStream;
			iffStream = NULL;

			e.printStackTrace();
			error("error parsing chunks");
		} catch (...) {
			delete iffStream;
			iffStream = NULL;

			error("error parsing chunks");
		}
	}

	delete [] data;

	if (iffStream != NULL) {
		info("loading..", true);

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

Vector<Boundary*> ProceduralTerrainAppearance::getBoundaries(float x, float y) {
	LayersGroup* layersGroup = terrainGenerator->getLayersGroup();

	Vector<Layer*>* layers = layersGroup->getLayers();

	for (int i = 0; i < layers->size(); ++i) {
		Layer* layer = layers->get(i);

		Vector<Layer*>* children = layer->getChildren();

		//Vector<TerrainRule*>* rules = layer->getRules();

	}

	return NULL;
}

Layer* ProceduralTerrainAppearance::getLayerRecursive(float x, float y, Layer* rootParent) {
	Layer* returnLayer = NULL;

	Vector<Boundary*>* boundaries = rootParent->getBoundaries();

	for (int i = 0; i < boundaries->size(); ++i) {
		float result = boundaries->get(i)->process(x, y);

		if (result != 0)
			return rootParent;
	}

	Vector<Layer*>* children = rootParent->getChildren();

	for (int i = 0; i < children->size(); ++i) {
		Layer* layer = children->get(i);

		returnLayer = getLayerRecursive(x, y, layer);

		if (returnLayer != NULL)
			return returnLayer;
	}

	return returnLayer;
}

Layer* ProceduralTerrainAppearance::getLayer(float x, float y) {
	Layer* returnLayer = NULL;

	LayersGroup* layersGroup = terrainGenerator->getLayersGroup();

	Vector<Layer*>* layers = layersGroup->getLayers();

	for (int i = 0; i < layers->size(); ++i) {
		Layer* layer = layers->get(i);

		if (!layer->isEnabled())
			continue;

		returnLayer = getLayerRecursive(x, y, layer);

		if (returnLayer != NULL)
			return returnLayer;
		//Vector<TerrainRule*>* rules = layer->getRules();
	}

	return returnLayer;
}

float ProceduralTerrainAppearance::calculateFeathering(float value, int featheringType) {
	/* 1: x^2
	 * 2: sqrt(x)
	 * 3: x^2 * (3 - 2x)
	 */


	float result = value;

	switch (featheringType) {
	case 1:
		result = result * result;
		break;
	case 2:
		result = sqrt(result);
		break;
	case 3:
		result = result * result * (3 - 2 * result);
		break;
	case 0:
		result = result;
		break;
	default:
		result = 0;
		break;
	}

	return result;
}

float ProceduralTerrainAppearance::processHeight(Layer* layer, float x, float y, float& baseValue, float affectorTransformValue, bool& found) {
	Vector<Boundary*>* boundaries = layer->getBoundaries();
	Vector<AffectorProceduralRule*>* affectors = layer->getAffectors();
	Vector<FilterProceduralRule*>* filters = layer->getFilters();

	float transformValue = 0;

	bool hasBoundaries = false;

	for (int i = 0; i < boundaries->size(); ++i) {
		Boundary* boundary = boundaries->get(i);

		if (!boundary->isEnabled()) {
			continue;
		} else
			hasBoundaries = true;

		float result = boundary->process(x, y);

		int featheringType = boundary->getFeatheringType();

		result = calculateFeathering(result, featheringType);

		if (result > transformValue)
			transformValue = result;

		if (transformValue >= 1) {
			found = true;
			break;
		}
	}

	if (!hasBoundaries)
		transformValue = 1.0;

	if (layer->invertBoundaries())
		transformValue = 1.0 - transformValue;

	if (transformValue != 0) {
		found = true;

		for (int i = 0; i < filters->size(); ++i) {
			FilterProceduralRule* filter = filters->get(i);

			if (!filter->isEnabled())
				continue;

			float result = filter->process(x, y, transformValue, baseValue, terrainGenerator);

			int featheringType = filter->getFeatheringType();

			result = calculateFeathering(result, featheringType);

			if (transformValue > result)
				transformValue = result;

			if (transformValue == 0)
				break;
		}

		if (layer->invertFilters())
			transformValue = 1.0 - transformValue;

		if (transformValue != 0) {
			for (int i = 0; i < affectors->size(); ++i) {
				AffectorProceduralRule* affector = affectors->get(i);

				if (!affector->isEnabled())
					continue;

				affector->process(x, y, transformValue * affectorTransformValue, baseValue, terrainGenerator);
			}
		}

	}

	Vector<Layer*>* children = layer->getChildren();

	if (children->size() != 0) {
		for (int i = 0; i < children->size(); ++i) {
			Layer* layer = children->get(i);

			if (layer->isEnabled())
				processHeight(layer, x, y, baseValue, affectorTransformValue * transformValue, found);
		}
	}

	return transformValue;
}

float ProceduralTerrainAppearance::getHeight(float x, float y) {

	//-5576, 1048
	Layer* foundLayer = getLayer(x, y);

	float affectorTransform = 1.0;

	bool found = false;

	if (foundLayer != NULL) {

		info("found layer " + foundLayer->getDescription(), true);

		float singleTraverse = 0.f;

		processHeight(foundLayer, x, y, singleTraverse, affectorTransform, found);

		info("single traverse height ... is " + String::valueOf(singleTraverse), true);

		Layer* root = foundLayer;

		while (root->getParent() != NULL)
			root = root->getParent();

		float rootTraverse = 0;
		affectorTransform = 1.0;

		processHeight(root, x, y, rootTraverse, affectorTransform, found);

		info("root traverse height ... is " + String::valueOf(rootTraverse), true);

	}

	float fullTraverse = 0;

	LayersGroup* layersGroup = terrainGenerator->getLayersGroup();

	Vector<Layer*>* layers = layersGroup->getLayers();

	affectorTransform = 1.0;

	float transformValue = 0;

	found = false;

	for (int i = 0; i < layers->size(); ++i) {
		//fullTraverse = 0;

		Layer* layer = layers->get(i);

		if (layer->isEnabled())
			transformValue = processHeight(layer, x, y, fullTraverse, affectorTransform, found);
		//Vector<TerrainRule*>* rules = layer->getRules();
	}


	info("full traverse height ... is " + String::valueOf(fullTraverse), true);


	return 0;
}
