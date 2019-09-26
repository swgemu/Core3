/*
 * Boundary.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#pragma once

class ProceduralTerrainAppearance;

#include "../ProceduralRule.h"

class Boundary {
protected:
	InformationHeader informationHeader;

	int featheringType = 0;
	float featheringAmount = 0;

	const uint32 formType;

public:
	Boundary(uint32 formType) : formType(formType) {
	}

	virtual ~Boundary() {
	}

	virtual void executeRule(ProceduralTerrainAppearance* generator) {

	}

	void readObject(engine::util::IffStream* iffStream) {
		if (iffStream->openForm(formType) == nullptr)
			throw Exception("Incorrect form type " + String::valueOf(formType));

		parseFromIffStream(iffStream);

		iffStream->closeForm(formType);
	}

	virtual void parseFromIffStream(engine::util::IffStream* iffStream) = 0;


	virtual bool containsPoint(float x, float y) const = 0;

	virtual float checkInfluence(float x, float y) const = 0;

	virtual float getLocalWaterTableHeight() const {
		return -16000;
	}

	virtual float process(float x, float y) const = 0;

	inline int getFeatheringType() const {
		return featheringType;
	}

	virtual float getMinX() const = 0;
	virtual float getMaxX() const = 0;
	virtual float getMinY() const = 0;
	virtual float getMaxY() const = 0;

	virtual void translateBoundary(float x, float y) = 0;

	inline bool isEnabled() const {
		return informationHeader.isEnabled();
	}
};

