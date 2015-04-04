/*
 * FilterSlope.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef FILTERSLOPE_H_
#define FILTERSLOPE_H_


#include "../ProceduralRule.h"
#include "FilterProceduralRule.h"

#define defaultValue 1.5707964

class FilterSlope : public ProceduralRule<'FSLP'>, public FilterProceduralRule {
	float minAngle; // +32
	float max; // +40
	float maxAngle; // +28
	float min; //+36

	//const static float defaultValue = 1.5707964;

public:
	FilterSlope() : FilterProceduralRule(2), minAngle(0), max(0), maxAngle(0), min(0) {
		filterType = HEIGHTTYPE;
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0002':
			parseFromIffStream(iffStream, Version<'0002'>());
			break;
		default:
			System::out << "unknown FilderSlope version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void setMinAngle(float newAngle) {
		if (newAngle >= 0) {
			if (newAngle <= defaultValue) {
				minAngle = newAngle;
				max = sin(defaultValue - newAngle);
			} else {
				minAngle = defaultValue;
				max = 0;
			}
		} else {
			minAngle = 0;
			max = sin(defaultValue);
		}
	}

	void setMaxAngle(float newAngle) {
		if (newAngle >= 0) {
			if (newAngle <= defaultValue) {
				maxAngle = newAngle;
				min = sin(defaultValue - newAngle);
			} else {
				maxAngle = defaultValue;
				min = 0;
			}
		} else {
			maxAngle = 0;
			min = sin(defaultValue);
		}
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0002'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		minAngle = iffStream->getFloat();
		setMinAngle(M_PI * minAngle * 0.005555555690079927);

		maxAngle = iffStream->getFloat();

		setMaxAngle(M_PI * maxAngle * 0.005555555690079927);

		featheringType = iffStream->getInt();

		featheringAmount = iffStream->getFloat();

		if (featheringAmount > 1)
			featheringAmount = 1;
		else if (featheringAmount < 0)
			featheringAmount = 0;

		iffStream->closeChunk('DATA');
	}

	float process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator) {
		float result;

		if (baseValue > min && baseValue < max) {
			float v7 = max - min * featheringAmount * 0.5;

			if (min + v7 <= baseValue) {
				if (max - v7 >= baseValue) {
					result = 1.0;
				} else {
					result = (max - baseValue) / v7;
				}
			} else
				result = (baseValue - min) / v7;
		} else
			result = 0;

		return result;
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};

#endif /* FILTERSLOPE_H_ */
