/*
 * TerrainManager.cpp
 *
 *  Created on: 18/04/2010
 *      Author: victor
 */

#include "TerrainManager.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/objects/terrain/ProceduralTerrainAppearance.h"
#include "server/zone/objects/terrain/SpaceTerrainAppearance.h"

TerrainManager::TerrainManager(Zone* planet) : Logger("TerrainManager") {
	zone = planet;
}

TerrainManager::TerrainManager(ManagedWeakReference<Zone*> planet) : Logger("TerrainManager") {
	zone = planet.get();
}

bool TerrainManager::initialize(const String& terrainFile) {
	IffStream* iffStream = TemplateManager::instance()->openIffFile(terrainFile);

	if (iffStream == NULL)
		return false;

	if (iffStream->getNextFormType() == 'PTAT') {
		terrainData = new ProceduralTerrainAppearance();
	} else if (iffStream->getNextFormType() == 'STAT') {
		terrainData = new SpaceTerrainAppearance();
	}

	bool val = terrainData->load(iffStream);

	delete iffStream;

	return val;
}

/**
 *  	|----------------| x1,y1
 *  	|----------------| <- stepping
 *	    |----------------|
 *  	|----------------|
 *x0,y0 |----------------|
 */
float TerrainManager::getHighestHeight(float x0, float y0, float x1, float y1, int stepping) {
	int deltaX = (int)fabs(x1 - x0);
	int deltaY = (int)fabs(y1 - y0);

	float maxHeight = -16000.f;

	for (int i = (int)y0; i < (int)y0 + deltaY; i += stepping) {
		for (int j = (int)x0; j < (int)x0 + deltaX; j += stepping) {
			float height = zone->getHeight(j, i);

			if (height > maxHeight)
				maxHeight = height;
		}
	}

	return maxHeight;
}

float TerrainManager::getLowestHeight(float x0, float y0, float x1, float y1, int stepping) {
	int deltaX = (int)fabs(x1 - x0);
	int deltaY = (int)fabs(y1 - y0);

	float minHeight = 16000.f;

	for (int i = (int)y0; i < (int)y0 + deltaY; i += stepping) {
		for (int j = (int)x0; j < (int)x0 + deltaX; j += stepping) {
			float height = zone->getHeight(j, i);

			if (height < minHeight)
				minHeight = height;
		}
	}

	return minHeight;
}

float TerrainManager::getHighestHeightDifference(float x0, float y0, float x1, float y1, int stepping) {
	return getHighestHeight(x0, y0, x1, y1, stepping) - getLowestHeight(x0, y0, x1, y1, stepping);
}

int TerrainManager::notifyPositionUpdate(CreatureObject* object) {
	CreatureObject* creature = cast<CreatureObject*>( object);

	float waterHeight;

	if (creature->getParent() == NULL && getWaterHeight(creature->getPositionX(), creature->getPositionY(), waterHeight)) {

		if (creature->getPositionZ() + creature->getSwimHeight()- waterHeight < 0.2) {

			if (creature->hasState(CreatureState::ONFIRE))
				creature->healDot(CreatureState::ONFIRE, 100);
		}
	}

	return 0;
}

void TerrainManager::addTerrainModification(float x, float y, const String& terrainModificationFilename, uint64 objectid) {
	ProceduralTerrainAppearance* ptat = dynamic_cast<ProceduralTerrainAppearance*>(terrainData.get());

	if (ptat == NULL)
		return;

	IffStream* stream = TemplateManager::instance()->openIffFile(terrainModificationFilename);

	if (stream == NULL) {
		error("could not find custom terrain file: " + terrainModificationFilename);
		return;
	}

	if (ptat->addTerrainModification(stream, x, y, objectid) == NULL) {
		error("could not add custom terrain file: " + terrainModificationFilename);
	}

	delete stream;
}

void TerrainManager::removeTerrainModification(uint64 objectid) {
	ProceduralTerrainAppearance* ptat = dynamic_cast<ProceduralTerrainAppearance*>(terrainData.get());

	if (ptat == NULL)
		return;

	ptat->removeTerrainModification(objectid);
}

ProceduralTerrainAppearance* TerrainManager::getProceduralTerrainAppearance() {
	return dynamic_cast<ProceduralTerrainAppearance*>(terrainData.get());
}
