/*
 * AffectorHeightConstant.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORHEIGHTCONSTANT_H_
#define AFFECTORHEIGHTCONSTANT_H_

#include "../ProceduralRule.h"

class TerrainGenerator;

class AffectorHeightConstant : public ProceduralRule<'AHCN'>, public AffectorProceduralRule {
	int operationType; // id?
	float height;

public:
	AffectorHeightConstant() {
		affectorType = HEIGHTCONSTANT;
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown AffectorHeightConstant version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		operationType = iffStream->getInt();
		height = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}

	void process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator) {
		if (transformValue == 0)
			return;

		float result;

		switch (operationType) {
		case 1:
			result = transformValue * height + baseValue;
			break;
		case 2:
			result = baseValue - transformValue * height;
			break;
		case 3:
			result = baseValue + (baseValue * height - baseValue) * transformValue;
			break;
		case 4:
			result = 0;
			break;
		default:
			result = (1.0 - transformValue) * baseValue + transformValue * height;
		}

		baseValue = result;
	}

	inline float getHeight() {
		return height;
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};




#endif /* AFFECTORHEIGHTCONSTANT_H_ */
