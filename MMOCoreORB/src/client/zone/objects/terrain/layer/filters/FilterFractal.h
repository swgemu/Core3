/*
 * FIlterFractal.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef FILTERFRACTAL_H_
#define FILTERFRACTAL_H_


#include "../ProceduralRule.h"
#include "FilterProceduralRule.h"

class TerrainGenerator;
class MapFractal;

class FilterFractal : public ProceduralRule<'FFRA'>, public FilterProceduralRule {
	int fractalId; // Fractal Group ID to modify (MGRP)
	float min;
	float max; // Scale/Stepping?
	float var6; // Scale/Stepping?
	MapFractal* mfrc;

public:
	FilterFractal() : FilterProceduralRule(1), fractalId(0), min(0), max(0), var6(0), mfrc(NULL) {
		filterType = HEIGHTTYPE;
	}

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0005'>);

	float process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator, FilterRectangle* rect);

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};

#endif /* FILTERFRACTAL_H_ */
