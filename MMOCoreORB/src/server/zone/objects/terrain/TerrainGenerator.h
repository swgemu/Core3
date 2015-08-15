/*
 * TerrainGenerator.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef TERRAINGENERATOR_H_
#define TERRAINGENERATOR_H_

#include "TemplateVariable.h"
#include "ShadersGroup.h"
#include "RadialGroup.h"
#include "FloraGroup.h"
#include "EnvironmentGroup.h"
#include "MapGroup.h"
#include "LayersGroup.h"
#include "layer/Layer.h"
#include "BitmapGroup.h"

class ProceduralTerrainAppearance;

class TerrainGenerator : public TemplateVariable<'TGEN'> {
	ProceduralTerrainAppearance* terrain;

	ShadersGroup shaderGroup;
	RadialGroup radialGroup;
	FloraGroup floraGroup;
	EnvironmentGroup environmentGroup;
	MapGroup mapGroup;
	BitmapGroup bitmapGroup;
	LayersGroup layers;

public:
	TerrainGenerator(ProceduralTerrainAppearance* ptat) {
		terrain = ptat;
	}

	void processLayers();
	void processLayer(Layer* layer);

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>);

	void addLayer(Layer* layer);
	void removeLayer(Layer* layer);

	bool getFullBoundaryCircle(float& centerX, float& centerY, float& radius);

	void getFullBoundaryCircle(Layer* layer, float& minX, float& minY, float& maxX, float& maxY);

	inline MapGroup* getMapGroup() {
		return &mapGroup;
	}

	inline LayersGroup* getLayersGroup() {
		return &layers;
	}

	inline BitmapGroup* getBitmapGroup() {
		return &bitmapGroup;
	}

	inline MapFractal* getMfrc(int idx) {
		return mapGroup.getMfrc(idx);
	}

};


#endif /* TERRAINGENERATOR_H_ */
