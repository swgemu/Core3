/*
 * FilterProceduralRule.h
 *
 *  Created on: 21/12/2010
 *      Author: victor
 */

#ifndef FILTERPROCEDURALRULE_H_
#define FILTERPROCEDURALRULE_H_

#include "../InformationHeader.h"

class TerrainGenerator;

class FilterRectangle {
public:
	float minX, maxX, minY, maxY;
};

class FilterProceduralRule {
protected:
	InformationHeader informationHeader;

	int featheringType; // Feathering type? Leftover?
	float featheringAmount;
	int filterType;

	int internalType;
	const uint32 formType;

public:
	const static int HEIGHTTYPE = 0x100;
	const static int ENVIRONMENT = 0x200;

	const static int HEIGHT = 0;
	const static int FRACTAL = 1;
	const static int SLOPE = 2;
	const static int DIRECTION = 3;
	const static int SHADER = 4;
	const static int BITMAP = 5;

	FilterProceduralRule(int type, uint32 formType) : featheringType(0),
		featheringAmount(0), filterType(0), internalType(type), formType(formType) {
	}

	virtual ~FilterProceduralRule() {

	}

	virtual float process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator, FilterRectangle* rect) {
		return 0;
	}

	void readObject(engine::util::IffStream* iffStream) {
		if (iffStream->openForm(formType) == nullptr)
			throw Exception("Incorrect form type " + String::valueOf(formType));

		parseFromIffStream(iffStream);

		iffStream->closeForm(formType);
	}

	virtual void parseFromIffStream(engine::util::IffStream* iffStream) {

	}

	inline bool isEnabled() const {
		return informationHeader.isEnabled();
	}

	inline int getFeatheringType() const {
		return featheringType;
	}

	inline int getFilterType() const {
		return filterType;
	}

	inline int getInternalType() const {
		return internalType;
	}

	inline bool isType(int type) const {
		return internalType == type;
	}

};


#endif /* FILTERPROCEDURALRULE_H_ */
