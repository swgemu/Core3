/*
 * FilterProceduralRule.h
 *
 *  Created on: 21/12/2010
 *      Author: victor
 */

#ifndef FILTERPROCEDURALRULE_H_
#define FILTERPROCEDURALRULE_H_

#include "../ProceduralRule.h"

class TerrainGenerator;

class FilterProceduralRule {
protected:
	int featheringType; // Feathering type? Leftover?
	float featheringAmount;

public:
	FilterProceduralRule() {
		featheringType = 0;
	}

	virtual ~FilterProceduralRule() {

	}

	virtual float process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator) {
		return 0;
	}

	virtual bool isEnabled() {
		return false;
	}

	inline int getFeatheringType() {
		return featheringType;
	}

};


#endif /* FILTERPROCEDURALRULE_H_ */
