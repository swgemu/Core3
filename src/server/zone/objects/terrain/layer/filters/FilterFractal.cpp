/*
 * FilterFractal.cpp
 *
 *  Created on: 21/12/2010
 *      Author: victor
 */

#include "FilterFractal.h"

#include "../../TerrainGenerator.h"


float FilterFractal::process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator) {
	Mfrc* mfrc = terrainGenerator->getMfrc(fractalId);

	if (mfrc == NULL) {
		System::out << "error out of bounds fractal id for affector " << informationHeader.getDescription() << endl;

		return 1;
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
