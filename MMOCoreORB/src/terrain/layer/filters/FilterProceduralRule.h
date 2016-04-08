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

class FilterRectangle {
public:
	float minX, maxX, minY, maxY;
};

class FilterProceduralRule {
protected:
	int featheringType; // Feathering type? Leftover?
	float featheringAmount;
	int filterType;

	int internalType;

public:
	const static int HEIGHTTYPE = 0x100;
	const static int ENVIRONMENT = 0x200;

	const static int HEIGHT = 0;
	const static int FRACTAL = 1;
	const static int SLOPE = 2;
	const static int DIRECTION = 3;
	const static int SHADER = 4;
	const static int BITMAP = 5;

	FilterProceduralRule(int type) : featheringType(0), featheringAmount(0), filterType(0), internalType(type) {
	}

	virtual ~FilterProceduralRule() {

	}

	virtual float process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator, FilterRectangle* rect) {
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

	inline int getInternalType() {
		return internalType;
	}

	inline bool isType(int type) {
		return internalType == type;
	}

};


#endif /* FILTERPROCEDURALRULE_H_ */
