/*
 * AffectorHeightTerrace.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORHEIGHTTERRACE_H_
#define AFFECTORHEIGHTTERRACE_H_


#include "../ProceduralRule.h"

class AffectorHeightTerrace : public ProceduralRule<'AHTR'>, public AffectorProceduralRule {
	float flatRatio;
	float height;

public:
	AffectorHeightTerrace() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0004':
			parseFromIffStream(iffStream, Version<'0004'>());
			break;
		default:
			System::out << "unknown AffectorHeightTerrace version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0004'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		flatRatio = iffStream->getFloat();
		height = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}

	void process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator) {
		if (transformValue == 0)
			return;

		if (height <= 0)
			return;

		//float var1 = height + height;
		float var1 = fmod(baseValue, height);

		if (baseValue == 0) {
			var1 += height;
		}

		float var2 = baseValue - var1;
		float var3 = height * flatRatio + var2;
		float var4 = height + var2;

		if (baseValue > var3) {
			var2 = (baseValue - var3) / (var4 - var3) * (var4 - var2) + var2;
		}

		baseValue = (var2 - baseValue) * transformValue + baseValue;
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};

#endif /* AFFECTORHEIGHTTERRACE_H_ */
