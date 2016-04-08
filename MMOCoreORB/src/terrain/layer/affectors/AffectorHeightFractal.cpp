/*
 * AffectorHeightFractal.cpp
 *
 *  Created on: 18/12/2010
 *      Author: victor
 */

#include "AffectorHeightFractal.h"
#include "../../TerrainGenerator.h"

void AffectorHeightFractal::process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator) {
	if (transformValue == 0)
		return;

	if (mfrc == NULL) {
		mfrc = terrainGenerator->getMfrc(fractalId);

		if (mfrc == NULL) {
			System::out << "error out of bounds fractal id for affector " << informationHeader.getDescription() << endl;

			return;
		}
	}

	float noiseResult = mfrc->getNoise(x, y, 0, 0) * height;

	//System::out << "noiseResult " << noiseResult << " height:" << height << endl;

	float result;

	switch (operationType) {
	case 1:
		result = baseValue + noiseResult * transformValue;
		break;
	case 2:
		result = baseValue - noiseResult * transformValue;
		break;
	case 3:
		result = baseValue + (noiseResult * baseValue - baseValue) * transformValue;
		break;
	case 4:
		result = baseValue;
		break;
	default:
		result = baseValue + (noiseResult - baseValue) * transformValue;
		break;
	}

	baseValue = result;
}

void AffectorHeightFractal::parseFromIffStream(engine::util::IffStream* iffStream) {
	uint32 version = iffStream->getNextFormType();

	iffStream->openForm(version);

	switch (version) {
	case '0003':
		parseFromIffStream(iffStream, Version<'0003'>());
		break;
	default:
		System::out << "unknown AffectorHeightFractal version 0x" << hex << version << endl;
		break;
	}

	iffStream->closeForm(version);
}

void AffectorHeightFractal::parseFromIffStream(engine::util::IffStream* iffStream, Version<'0003'>) {
	informationHeader.readObject(iffStream);

	iffStream->openForm('DATA');

	iffStream->openChunk('PARM');

	fractalId = iffStream->getInt();
	operationType = iffStream->getInt();

	height = iffStream->getFloat();

	iffStream->closeChunk('PARM');
	iffStream->closeForm('DATA');
}
