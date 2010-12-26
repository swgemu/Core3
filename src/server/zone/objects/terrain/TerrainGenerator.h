/*
 * TerrainGenerator.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef TERRAINGENERATOR_H_
#define TERRAINGENERATOR_H_

#include "engine/engine.h"

#include "TemplateVariable.h"
#include "ShadersGroup.h"
#include "RadialGroup.h"
#include "FloraGroup.h"
#include "EnvironmentGroup.h"
#include "MapGroup.h"
#include "LayersGroup.h"
#include "layer/Layer.h"

class ProceduralTerrainAppearance;

class TerrainGenerator : public TemplateVariable<'TGEN'> {
	ProceduralTerrainAppearance* terrain;

	ShadersGroup shaderGroup;
	RadialGroup radialGroup;
	FloraGroup floraGroup;
	EnvironmentGroup environmentGroup;
	MapGroup mapGroup;
	//MapGroup mapGroup2;
	LayersGroup layers;

public:
	TerrainGenerator(ProceduralTerrainAppearance* ptat) {
		terrain = ptat;
	}

	void processLayers();
	void processLayer(Layer* layer);

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>);

	inline MapGroup* getMapGroup() {
		return &mapGroup;
	}

	inline LayersGroup* getLayersGroup() {
		return &layers;
	}

	inline MapFractal* getMfrc(int idx) {
		return mapGroup.getMfrc(idx);
	}


};


#endif /* TERRAINGENERATOR_H_ */
