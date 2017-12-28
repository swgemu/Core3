/*
 * TerrainGenerator.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef TERRAINGENERATOR_H_
#define TERRAINGENERATOR_H_

#include "BitmapGroup.h"
#include "EnvironmentGroup.h"
#include "FloraGroup.h"
#include "LayersGroup.h"
#include "MapGroup.h"
#include "RadialGroup.h"
#include "ShadersGroup.h"
#include "TemplateVariable.h"
#include "layer/Layer.h"
#include "terrain/layer/../TemplateVariable.h"

class Layer;
class MapFractal;
class ProceduralTerrainAppearance;
namespace engine {
namespace util {
class IffStream;
}  // namespace util
}  // namespace engine

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
