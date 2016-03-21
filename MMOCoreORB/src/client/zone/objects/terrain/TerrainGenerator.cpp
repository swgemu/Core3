/*
 * TerrainGenerator.cpp
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#include "ProceduralTerrainAppearance.h"
#include "TerrainGenerator.h"

void TerrainGenerator::processLayers() {
	Vector<Layer*>* layerVector = layers.getLayers();

	for (int i = 0; i < layerVector->size(); ++i) {
		processLayer(layerVector->get(i));
	}
}

bool TerrainGenerator::getFullBoundaryCircle(float& centerX, float& centerY, float& radius) {
	Vector<Layer*>* layerVector = layers.getLayers();

	float minX = FLT_MAX;
	float minY = minX;

	float maxX = -FLT_MAX;
	float maxY = maxX;

	for (int i = 0; i < layerVector->size(); ++i) {
		Layer* layer = layerVector->get(i);

		if (layer->isEnabled()) {
			getFullBoundaryCircle(layer, minX, minY, maxX, maxY);
		}
	}

	if (minX == FLT_MAX || minY == FLT_MAX || maxX == -FLT_MAX || maxY == -FLT_MAX)
		return false;

	Vector3 boxmin(minX, minY, 0);
	Vector3 boxmax(maxX, maxY, 0);

	AABB box(boxmin, boxmax);

	Vector3 center = box.center();
	Vector3 extents = box.extents();

	radius = extents.length();
	centerX = center.getX();
	centerY = center.getY();

	return true;
}

void TerrainGenerator::getFullBoundaryCircle(Layer* layer, float& minX, float& minY, float& maxX, float& maxY) {
	Vector<Boundary*>* boundaries = layer->getBoundaries();

	for (int i = 0; i < boundaries->size(); ++i) {
		Boundary* boundary = boundaries->get(i);

		if (!boundary->isEnabled())
			continue;

		float boundaryMinX = boundary->getMinX();
		float boundaryMinY = boundary->getMinY();

		float boundaryMaxX = boundary->getMaxX();
		float boundaryMaxY = boundary->getMaxY();

		if (boundaryMinX < minX)
			minX = boundaryMinX;

		if (boundaryMinY < minY)
			minY = boundaryMinY;

		if (boundaryMaxX > maxX)
			maxX = boundaryMaxX;

		if (boundaryMaxY > maxY)
			maxY = boundaryMaxY;
	}

	Vector<Layer*>* childrenLayers = layer->getChildren();

	for (int i = 0; i < childrenLayers->size(); ++i) {
		Layer* child = childrenLayers->get(i);

		if (child->isEnabled()) {
			getFullBoundaryCircle(child, minX, minY, maxX, maxY);
		}
	}
}

void TerrainGenerator::processLayer(Layer* layer) {
	Vector<Boundary*>* terrainRules = layer->getBoundaries();

	for (int i = 0; i < terrainRules->size(); ++i) {
		terrainRules->get(i)->executeRule(terrain);
	}

	Vector<Layer*>* childrenLayers = layer->getChildren();

	for (int i = 0; i < childrenLayers->size(); ++i)
		processLayer(childrenLayers->get(i));
}

void TerrainGenerator::parseFromIffStream(engine::util::IffStream* iffStream) {
	uint32 version = iffStream->getNextFormType();

	iffStream->openForm(version);

	switch (version) {
	case '0000':
		parseFromIffStream(iffStream, Version<'0000'>());
		break;
	default:
		System::out << "error unknown TGEN version" << endl;
		break;
	}

	iffStream->closeForm(version);
}

void TerrainGenerator::parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
	shaderGroup.readObject(iffStream);
	floraGroup.readObject(iffStream);
	radialGroup.readObject(iffStream);
	environmentGroup.readObject(iffStream);
	mapGroup.readObject(iffStream);

	uint32 type = iffStream->getNextFormType();

	if (type == 'MGRP') {
		bitmapGroup.readObject(iffStream);

		type = iffStream->getNextFormType();
	}

	if (type == 'LAYR') {
		Layer* layer = new Layer();
		layer->readObject(iffStream);

		layers.getLayers()->add(layer);
	} else
		layers.readObject(iffStream);

}

void TerrainGenerator::addLayer(Layer* layer) {
	layers.getLayers()->add(layer);
}

void TerrainGenerator::removeLayer(Layer* layer) {
	layers.getLayers()->removeElement(layer);
}
