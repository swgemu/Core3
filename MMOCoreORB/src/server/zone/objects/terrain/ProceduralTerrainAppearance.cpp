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
#include "layer/affectors/AffectorHeightConstant.h"
#include "PerlinNoise.h"

ProceduralTerrainAppearance::ProceduralTerrainAppearance() : Logger("ProceduralTerrainAppearance") {
	terrainGenerator = new TerrainGenerator(this);
	terrainMaps = new TerrainMaps();

	//float defaultHeight;

	size = 0;
	chunkSize = 0;
	tilesPerChunk = 0;

	useGlobalWaterTable = 0;
	globalWaterTableHeight = 0;
	globalWaterTableShaderSize = 0;

	timeCycle = 0;

	floraCollidableMinDistance = 0;
	floraCollidableMaxDistance = 0;
	floraCollidableTileSize = 0;
	floraCollidableTileBorder = 0;
	floraCollidableSeed = 0;

	floraNonCollidableMinDistance = 0;
	floraNonCollidableMaxDistance = 0;
	floraNonCollidableTileSize = 0;
	floraNonCollidableTileBorder = 0;
	floraNonCollidableSeed = 0;

	radialNearMinDistance = 0;
	radialNearMaxDistance = 0;
	radialNearTileSize = 0;
	radialNearTileBorder = 0;
	radialNearSeed = 0;

	radialFarMinDistance = 0;
	radialFarMaxDistance = 0;
	radialFarTileSize = 0;
	radialFarTileBorder = 0;
	radialFarSeed = 0;
}

ProceduralTerrainAppearance::~ProceduralTerrainAppearance() {
	delete terrainGenerator;
	terrainGenerator = NULL;

	delete terrainMaps;
	terrainMaps = NULL;
}

bool ProceduralTerrainAppearance::load(IffStream* iffStream) {
	waterBoundaries.removeAll();

	delete terrainGenerator;
	delete terrainMaps;

	terrainGenerator = new TerrainGenerator(this);
	terrainMaps = new TerrainMaps();

	readObject(iffStream);

	terrainGenerator->processLayers();

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
	ReadLocker locker(&guard);

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
		//result = result;
		break;
	default:
		result = 0;
		break;
	}

	return result;
}

float ProceduralTerrainAppearance::processTerrain(Layer* layer, float x, float y, float& baseValue, float affectorTransformValue, int affectorType) {
	Vector<Boundary*>* boundaries = layer->getBoundaries();
	Vector<AffectorProceduralRule*>* affectors = layer->getAffectors();
	Vector<FilterProceduralRule*>* filters = layer->getFilters();

	float transformValue = 0;

	bool hasBoundaries = false;

	FilterRectangle rect;
	rect.minX = FLT_MAX, rect.maxX = FLT_MIN, rect.minY = FLT_MAX, rect.maxY = FLT_MIN;

	for (int i = 0; i < boundaries->size(); ++i) {
		Boundary* boundary = boundaries->get(i);

		if (!boundary->isEnabled()) {
			continue;
		} else
			hasBoundaries = true;

		float result = boundary->process(x, y);

		if (result != 0.0) {
			if (boundary->getMinX() < rect.minX)
				rect.minX = boundary->getMinX();

			if (boundary->getMaxX() > rect.maxX)
				rect.maxX = boundary->getMaxX();

			if (boundary->getMinY() < rect.minY)
				rect.minY = boundary->getMinY();

			if (boundary->getMaxY() > rect.maxY)
				rect.maxY = boundary->getMaxY();
		}

		int featheringType = boundary->getFeatheringType();

		result = calculateFeathering(result, featheringType);

		if (result > transformValue)
			transformValue = result;

		if (transformValue >= 1) {
			break;
		}
	}

	if (!hasBoundaries)
		transformValue = 1.0;

	if (layer->invertBoundaries())
		transformValue = 1.0 - transformValue;

	if (transformValue != 0) {
		for (int i = 0; i < filters->size(); ++i) {
			FilterProceduralRule* filter = filters->get(i);

			if (!filter->isEnabled())
				continue;

			/*if (!(filter->getFilterType() & affectorType))
				continue;*/

			float result = filter->process(x, y, transformValue, baseValue, terrainGenerator, &rect);

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

				/*if (!affector->isEnabled()) filtered in height affectors vector
					continue;*/

				if (affector->isEnabled() && (affector->getAffectorType() & affectorType))
					affector->process(x, y, transformValue * affectorTransformValue, baseValue, terrainGenerator);
			}


			Vector<Layer*>* children = layer->getChildren();

			for (int i = 0; i < children->size(); ++i) {
				Layer* layer = children->get(i);

				if (layer->isEnabled()) {
					processTerrain(layer, x, y, baseValue, affectorTransformValue * transformValue, affectorType);
				}
			}

		}

	}

	return transformValue;
}

int ProceduralTerrainAppearance::getEnvironmentID(float x, float y) {
	ReadLocker locker(&guard);

	float affectorTransform = 1.0;

	float transformValue = 0;
	float fullTraverse = 0;

	int count = 0;
	TerrainGenerator* terrain = terrainGenerator;

	do {
		LayersGroup* layersGroup = terrain->getLayersGroup();

		Vector<Layer*>* layers = layersGroup->getLayers();

		for (int i = 0; i < layers->size(); ++i) {
			Layer* layer = layers->get(i);

			if (layer->isEnabled())
				transformValue = processTerrain(layer, x, y, fullTraverse, affectorTransform, AffectorProceduralRule::ENVIRONMENT);
		}
	} while (count < customTerrain.size() && (terrain = customTerrain.get(count++)));

	//info("full traverse height ... is " + String::valueOf(fullTraverse) + " in mili:" + String::valueOf(start.miliDifference()), true);

	return fullTraverse;
}

float ProceduralTerrainAppearance::getHeight(float x, float y) {
	ReadLocker locker(&guard);

	float affectorTransform = 1.0;

	float transformValue = 0;
	float fullTraverse = 0;

	int count = 0;
	TerrainGenerator* terrain = terrainGenerator;

	do {
		LayersGroup* layersGroup = terrain->getLayersGroup();

		Vector<Layer*>* layers = layersGroup->getLayers();

		for (int i = 0; i < layers->size(); ++i) {
			Layer* layer = layers->get(i);

			if (layer->isEnabled())
				transformValue = processTerrain(layer, x, y, fullTraverse, affectorTransform, AffectorProceduralRule::HEIGHTTYPE);
		}
	} while (count < customTerrain.size() && (terrain = customTerrain.get(count++)));

	//info("full traverse height ... is " + String::valueOf(fullTraverse) + " in mili:" + String::valueOf(start.miliDifference()), true);

	return fullTraverse;
}

void ProceduralTerrainAppearance::translateBoundaries(Layer* layer, float x, float y) {
	Vector<Boundary*>* boundaries = layer->getBoundaries();

	for (int j = 0; j < boundaries->size(); ++j) {
		Boundary* boundary = boundaries->get(j);

		boundary->translateBoundary(x, y);
	}

	Vector<Layer*>* children = layer->getChildren();

	for (int i = 0; i < children->size(); ++i) {
		Layer* child = children->get(i);

		if (child->isEnabled()) {
			translateBoundaries(child, x, y);
		}
	}
}

void ProceduralTerrainAppearance::setHeight(Layer* layer, float height) {
	Vector<AffectorProceduralRule*>* affectors = layer->getAffectors();

	for (int i = 0; i < affectors->size(); ++i) {
		AffectorProceduralRule* affector = affectors->get(i);

		AffectorHeightConstant* heightAffector = dynamic_cast<AffectorHeightConstant*>(affector);

		if (heightAffector != NULL && (heightAffector->getHeight() == 0) && (heightAffector->getOperationType() == 0)) {
			heightAffector->setHeight(height);
		}
	}

	Vector<Layer*>* children = layer->getChildren();

	for (int i = 0; i < children->size(); ++i) {
		Layer* child = children->get(i);

		if (child->isEnabled()) {
			setHeight(child, height);
		}
	}
}

TerrainGenerator* ProceduralTerrainAppearance::addTerrainModification(engine::util::IffStream* terrainGeneratorIffStream, float x, float y, uint64 objectid) {
	TerrainGenerator* terrain = new TerrainGenerator(this);

	try {
		terrain->parseFromIffStream(terrainGeneratorIffStream, Version<'0000'>());
	} catch (Exception& e) {
		error("could not deserialize terrain modification iff file");
		error(e.getMessage());
		delete terrain;
		return NULL;
	}

	Vector<Layer*>* layers = terrain->getLayersGroup()->getLayers();

	float currentHeight = getHeight(x, y);

	for (int i = 0; i < layers->size(); ++i) {
		Layer* layer = layers->get(i);

		if (layer->isEnabled()) {
			translateBoundaries(layer, x, y);

			setHeight(layer, currentHeight);
		}
	}

	Locker locker(&guard);

	TerrainGenerator* oldLayer = terrainModifications.put(objectid, terrain);
	customTerrain.add(terrain);

	if (oldLayer != NULL) {
		customTerrain.removeElement(oldLayer);
		delete oldLayer;
	}

	return terrain;
}

void ProceduralTerrainAppearance::removeTerrainModification(uint64 objectid) {
	Locker locker(&guard);

	TerrainGenerator* layer = terrainModifications.remove(objectid);

	if (layer == NULL)
		return;

	customTerrain.removeElement(layer);

	delete layer;
}
