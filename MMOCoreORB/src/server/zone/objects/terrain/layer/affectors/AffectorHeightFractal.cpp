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

	Mfrc* mfrc = terrainGenerator->getMfrc(fractalId - 1);

	float noiseResult = mfrc->getNoise(x, y, 0, 0) * height;

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
