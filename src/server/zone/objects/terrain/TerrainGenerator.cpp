/*
 * TerrainGenerator.cpp
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#include "TerrainGenerator.h"

#include "engine/engine.h"
#include "ProceduralTerrainAppearance.h"

void TerrainGenerator::processLayers() {
	Vector<Layer*>* layerVector = layers.getLayers();

	for (int i = 0; i < layerVector->size(); ++i) {
		processLayer(layerVector->get(i));
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
		System::out << "ASOIDJASOIDJAOSIJDAOISJD" << endl;
		//mapGroup2.readObject(iffStream);
	}

	layers.readObject(iffStream);

}
