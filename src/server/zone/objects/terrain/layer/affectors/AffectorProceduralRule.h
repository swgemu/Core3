/*
 * AffectorProceduralRule.h
 *
 *  Created on: 21/12/2010
 *      Author: victor
 */

#ifndef AFFECTORPROCEDURALRULE_H_
#define AFFECTORPROCEDURALRULE_H_

#include "../ProceduralRule.h"

class TerrainGenerator;

class AffectorProceduralRule {

public:
	AffectorProceduralRule() {

	}

	virtual ~AffectorProceduralRule() {

	}

	virtual void process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator) {

	}

	virtual bool isEnabled() {
		return false;
	}

};

#endif /* AFFECTORPROCEDURALRULE_H_ */
