/*
 * TerrainManager.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef TERRAINMANAGER_H_
#define TERRAINMANAGER_H_


#include "engine/engine.h"
#include "server/zone/objects/terrain/ProceduralTerrainAppearance.h"

class TerrainManager {
	String file;
	ProceduralTerrainAppearance terrainData;

	//Zone* zone;

public:
	TerrainManager(/*Zone* planet*/) {
		//zone = planet;
	}

	void initialize(const String& terrainFile) {
		file = terrainFile;
		terrainData.load(file);
	}
};


#endif /* TERRAINMANAGER_H_ */
