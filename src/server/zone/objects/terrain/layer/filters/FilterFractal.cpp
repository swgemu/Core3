/*
 * FilterFractal.cpp
 *
 *  Created on: 21/12/2010
 *      Author: victor
 */

#include "FilterFractal.h"

#include "../../TerrainGenerator.h"


float FilterFractal::process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator) {
	if (mfrc == NULL) {
		mfrc = terrainGenerator->getMfrc(fractalId);

		if (mfrc == NULL) {
			System::out << "error out of bounds fractal id for filter " << informationHeader.getDescription() << endl;

			return 1;
		}
	}

	float noiseResult = mfrc->getNoise(x, y, 0, 0) * var6;
	float result = 0;

	if (noiseResult > min && noiseResult < max) {
		float v9 = (max - min) * featheringAmount * 0.5;

		if (min + v9 <= noiseResult) {
			if (max - v9 >= noiseResult)
				result = 1.0;
			else
				result = (max - noiseResult) / v9;
		} else
			result = (noiseResult - min) / v9;
	} else
		result = 0;

	return result;
}

void FilterFractal::parseFromIffStream(engine::util::IffStream* iffStream) {
	uint32 version = iffStream->getNextFormType();

	iffStream->openForm(version);

	switch (version) {
	case '0005':
		parseFromIffStream(iffStream, Version<'0005'>());
		break;
	default:
		System::out << "unknown FilterFractal version 0x" << hex << version << endl;
		break;
	}

	iffStream->closeForm(version);
}

void FilterFractal::parseFromIffStream(engine::util::IffStream* iffStream, Version<'0005'>) {
	informationHeader.readObject(iffStream);

	iffStream->openForm('DATA');

	iffStream->openChunk('PARM');

	//6 vars
	fractalId = iffStream->getInt();
	featheringType = iffStream->getInt();
	featheringAmount = iffStream->getFloat();
	min = iffStream->getFloat();
	max = iffStream->getFloat();
	var6 = iffStream->getFloat();

	iffStream->closeChunk('PARM');

	iffStream->closeForm('DATA');
}

