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
	int filterType;

public:
	const static int HEIGHTTYPE = 0x100;
	const static int ENVIRONMENT = 0x200;


	FilterProceduralRule() {
		featheringType = 0;
		filterType = 0;
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

	inline int getFilterType() {
		return filterType;
	}

};


#endif /* FILTERPROCEDURALRULE_H_ */
