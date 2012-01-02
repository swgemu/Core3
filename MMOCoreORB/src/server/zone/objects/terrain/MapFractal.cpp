/*
 * Mfrc.cpp
 *
 *  Created on: 18/12/2010
 *      Author: victor
 */

#include "engine/engine.h"
#include "MapFractal.h"

double MapFractal::log05 = log(0.5);

using namespace trn::ptat;

MapFractal::MapFractal() {
	noise = NULL;
	rand = NULL;

	unkown = false;
}

float MapFractal::getNoise(float x, float y, int i, int j) {
	float v39 = x * xFrequency;
	float v41 = y * yFrequency;

	double result = 0;

	switch (combination) {
	case 0:
	case 1:
		result = calculateCombination1(v39, v41);
		break;
	case 2:
		result = calculateCombination2(v39, v41);
		break;
	case 3:
		result = calculateCombination3(v39, v41);
		break;
	case 4:
		result = calculateCombination4(v39, v41);
		break;
	case 5:
		result = calculateCombination5(v39, v41);
		break;
	}

	if (bias) {
		result = pow(result, log(biasValue) / log05);
	}

	if (gainType) {
		if (result < 0.001) {
			result = 0;

			return result;
		}

		if (result > 0.999) {
			result = 1.0;

			return result;
		}

		double v40 = log(1.0 - gainValue) / log05;

		if (result < 0.5) {
			result = pow(result * 2, v40) * 0.5;

			return result;
		}

		result = 1.0 - pow((1.0 - result) * 2, v40) * 0.5;
	}

	return result;
}

void MapFractal::parseFromIffStream(engine::util::IffStream* iffStream) {
	uint32 version = iffStream->getNextFormType();

	iffStream->openForm(version);

	switch (version) {
	case '0001':
		parseFromIffStream(iffStream, Version<'0001'>());
		break;
	default:
		//System::out << "unknown MFRC version " << version << endl;
		break;
	}

	iffStream->closeForm(version);
}

void MapFractal::parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
	iffStream->openChunk('DATA');


	int seed = iffStream->getInt();
	setSeed(seed);
	////System::out << "setting seed to:" << seed << endl;
	bias = iffStream->getInt();
	////System::out << "setting bias to:" << bias << endl;

	biasValue = iffStream->getFloat();

	////System::out << "setting biasValue to:" << biasValue << endl;
	gainType = iffStream->getInt();

	//System::out << "setting gainType to:" << gainType << endl;
	gainValue = iffStream->getFloat();

	//System::out << "setting gainValue to:" << gainValue << endl;

	octaves = iffStream->getUnsignedInt();

	//System::out << "setting octaves to:" << octaves << endl;
	octavesParam = iffStream->getFloat();
	setAmplitude(iffStream->getFloat());
	//System::out << "setting amplitude to:" << amplitude << endl;

	xFrequency = iffStream->getFloat();
	yFrequency = iffStream->getFloat();
	xOffset = iffStream->getFloat();
	zOffset = iffStream->getFloat();
	combination = iffStream->getUnsignedInt();

	iffStream->closeChunk('DATA');
}

double MapFractal::calculateCombination1(float v39, float v41) {
	float v48 = 1, v47 = 1;
	double result = 0;

	float v42 = v41 + zOffset; // + 16 = z.offset
	float v36 = v39 + xOffset; // + 12 = x.offset
	float v33 = 0;
	double coord[2];

	for (int i = 0; i < octaves; ++i) {
		coord[0] = v36 * v48;
		coord[1] = v42 * v48;

		v33 = noise->noise2(coord) * v47 + v33;
		v48 = v48 * octavesParam; // + 24 octaves param
		v47 = v47 * amplitude; // + 28 amplitude
	}

	if (unkown) // v6 + 52 initialized to 0
		v33 = sin(v33 + v39);

	result = (v33 * offset32 + 1.0) * 0.5; //  v6 + 32 initialized to 1.0

	return result;
}

double MapFractal::calculateCombination2(float v39, float v41) {
	float v34 = 0;
	float v42 = v39 + xOffset;
	float v43 = v41 + zOffset; // + 16 = z.offset
	float v48 = 1.0;
	float v47 = 1.0;
	double result = 0;
	double coord[2];

	for (int i = 0; i < octaves; ++i) {
		coord[0] = v42 * v48;;
		coord[1] = v43 * v48;

		v34 = (1.0 - fabs(noise->noise2(coord))) * v47 + v34;
		v48 = v48 * octavesParam;  // + 24 octaves param
		v47 = v47 * amplitude; // + 28 amplitude
	}

	if (unkown) //v6 + 52 initialized to 0
		v34 = sin(v34 + v39);

	result = v34 * offset32; //

	return result;
}

double MapFractal::calculateCombination3(float v39, float v41) {
	float v48 = 1.0;
	float v47 = 1.0;
	double result = 0;
	float v34 = 0;
	float v44 = v41 + zOffset; // + 16 = z.offset
	float v22 = v39 + xOffset;;

	double coord[2];

	for (int i = 0; i < octaves; ++i) {
		coord[0] = v22 * v48;;
		coord[1] = v44 * v48;;

		v34 = fabs(noise->noise2(coord)) * v47 + v34;
		v48 = v48 * octavesParam; // + 24 octaves param
		v47 = v47 * amplitude;  // + 28 amplitude
	}

	if (unkown) //v6 + 52 initialized to 0
		v34 = sin(v34 + v39);

	result = v34 * offset32; //

	return result;
}

double MapFractal::calculateCombination4(float v39, float v41) {
	float v34 = 0;
	float v26;
	float v45 = v41 + zOffset; // + 16 = z.offset
	float v37 = v39 + xOffset; //  + 12 = x.offset
	double coord[2];

	float v48 = 1.0;
	float v47 = 1.0;
	double result = 0;

	for (int i = 0; i < octaves; ++i) {
		coord[0] = v37 * v48;
		coord[1] = v45 * v48;

		v26 = noise->noise2(coord);
		if ( v26 >= 0.0 ) {
			if ( v26 > 1.0 )
				v26 = 1.0;
		} else {
			v26 = 0.0;
		}

		v34 = (1.0 - v26) * v47 + v34;
		v48 = v48 * octavesParam; // + 24 octaves param
		v47 = v47 * amplitude; // + 28 amplitude
	}

	if (unkown) //v6 + 52 initialized to 0
		v34 = sin(v34 + v39);

	result = v34 * offset32; //

	return result;
}

double MapFractal::calculateCombination5(float v39, float v41) {
	float v34 = 0;
	float v30;
	float v46 = v41 + zOffset; //  + 16 = z.offset
	float v38 = v39 + xOffset; //  + 12 = x.offset
	double coord[2];
	double result = 0;

	float v48 = 1.0;
	float v47 = 1.0;

	for (int i = 0; i < octaves; ++i) {
		coord[0] = v38 * v48;
		coord[1] = v46 * v48;

		v30 = noise->noise2(coord); //

		if ( v30 >= 0.0 ) {
			if (v30 > 1.0)
				v30 = 1.0;
		} else {
			v30 = 0.0;
		}

		v34 = v30 * v47 + v34;
		v48 = v48 * octavesParam; // v6 + 24 octaves param
		v47 = v47 * amplitude; // v6 + 28 amplitude
	}

	if (unkown) //v6 + 52 initialized to 0
		v34 = sin(v34 + v39);

	result = v34 * offset32; //

	return result;
}

void MapFractal::setSeed(int seed) {
	delete noise;
	delete rand;

	rand = new Random();
	rand->setSeed(seed);

	noise = new PerlinNoise(rand);
	double coord[2];
	coord[0] = 0, coord[1] = 0;

	noise->noise2(coord); //initialize
}
