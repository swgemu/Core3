/*
 * AffectorHeightFractal.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORHEIGHTFRACTAL_H_
#define AFFECTORHEIGHTFRACTAL_H_

#include "../ProceduralRule.h"
#include "AffectorProceduralRule.h"
class TerrainGenerator;
class MapFractal;

class AffectorHeightFractal : public ProceduralRule<'AHFR'>, public AffectorProceduralRule {
	int fractalId; // fractal group id in MGRP
	int operationType;
	float height;
	MapFractal* mfrc;

public:
	AffectorHeightFractal() {
		mfrc = NULL;
		affectorType = HEIGHTFRACTAL;
	}

	void process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator);

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0003'>);

	inline int getFractalId() {
		return fractalId;
	}

	inline float getHeight() {
		return height;
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};



#endif /* AFFECTORHEIGHTFRACTAL_H_ */
