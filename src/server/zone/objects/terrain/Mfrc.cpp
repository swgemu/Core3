/*
 * Mfrc.cpp
 *
 *  Created on: 18/12/2010
 *      Author: victor
 */

#include "engine/engine.h"
#include "Mfrc.h"

double Mfrc::log05 = log(0.5);

Mfrc::Mfrc() {
	noise = NULL;
	rand = NULL;
}

float Mfrc::getNoise(float x, float y, int i, int j) {
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
		result = pow(log(biasValue) / log05, result);
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
			result = pow(v40, result + result) * 0.5;

			return result;
		}

		result = 1.0 - pow(v40, 1.0 - result + 1.0 - result) * 0.5;
	}

	return result;
}

void Mfrc::parseFromIffStream(engine::util::IffStream* iffStream) {
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

void Mfrc::parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
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

double Mfrc::calculateCombination1(float v39, float v41) {
	float v48 = 1, v47 = 1;
	double result = 0;

	float v42 = v41 + zOffset; // + 16 = z.offset
	float v36 = v39 + xOffset; // + 12 = x.offset
	float v15, v16, v33 = 0;
	double coord[2];

	for (int i = 0; i < octaves; ++i) {
		v15 = v42 * v48;
		v16 = v36 * v48;

		coord[0] = v16;
		coord[1] = v15;

		v33 = noise->noise2(coord) * v47 + v33;
		v48 = v48 * octavesParam; // + 24 octaves param
		v47 = v47 * amplitude; // + 28 amplitude
	}

	if (false) // v6 + 52 initialized to 0
		v33 = sin(v33 + v39);

	result = (v33 * offset32 + 1.0) * 0.5; //  v6 + 32 initialized to 1.0

	return result;
}

double Mfrc::calculateCombination2(float v39, float v41) {
	float v34 = 0;
	float v43 = v41 + zOffset; // + 16 = z.offset
	float v19, v18, v20;
	float v48 = 1.0;
	float v47 = 1.0;
	double result = 0;
	double coord[2];

	for (int i = 0; i < octaves; ++i) {
		v19 = v43 * v48;
		v18 = v39 + xOffset; //  + 12 = x.offset
		v20 = v18 * v48;

		coord[0] = v20;
		coord[1] = v19;

		v34 = (1.0 - fabs(noise->noise2(coord))) * v47 + v34;
		v48 = v48 * octavesParam;  // + 24 octaves param
		v47 = v47 * amplitude; // + 28 amplitude
	}

	if (false) //v6 + 52 initialized to 0
		v34 = sin(v34 + v39);

	result = v34 * offset32; //

	return result;
}

double Mfrc::calculateCombination3(float v39, float v41) {
	float v48 = 1.0;
	float v47 = 1.0;
	double result = 0;
	float v34 = 0;
	float v44 = v41 + zOffset; // + 16 = z.offset
	float v23, v22, v24;

	double coord[2];

	for (int i = 0; i < octaves; ++i) {
		v23 = v44 * v48;
		v22 = v39 + xOffset; //  + 12 = x.offset
		v24 = v22 * v48;

		coord[0] = v24;
		coord[1] = v23;

		v34 = fabs(noise->noise2(coord)) * v47 + v34;
		v48 = v48 * octavesParam; // + 24 octaves param
		v47 = v47 * amplitude;  // + 28 amplitude
	}

	if (false) //v6 + 52 initialized to 0
		v34 = sin(v34 + v39);

	result = v34 * offset32; //

	return result;
}

double Mfrc::calculateCombination4(float v39, float v41) {
	float v34 = 0;
	float v27, v28, v26;
	float v45 = v41 + zOffset; // + 16 = z.offset
	float v37 = v39 + xOffset; //  + 12 = x.offset
	double coord[2];

	float v48 = 1.0;
	float v47 = 1.0;
	double result = 0;

	for (int i = 0; i < octaves; ++i) {
		v27 = v45 * v48;
		v28 = v37 * v48;

		coord[0] = v28;
		coord[1] = v27;

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

	if (false) //v6 + 52 initialized to 0
		v34 = sin(v34 + v39);

	result = v34 * offset32; //

	return result;
}

double Mfrc::calculateCombination5(float v39, float v41) {
	float v34 = 0;
	float v31, v32, v30;
	float v46 = v41 + zOffset; //  + 16 = z.offset
	float v38 = v39 + xOffset; //  + 12 = x.offset
	double coord[2];
	double result = 0;

	float v48 = 1.0;
	float v47 = 1.0;

	for (int i = 0; i < octaves; ++i) {
		v31 = v46 * v48;
		v32 = v38 * v48;

		coord[0] = v32;
		coord[1] = v31;

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

	if (false) //v6 + 52 initialized to 0
		v34 = sin(v34 + v39);

	result = v34 * offset32; //

	return result;
}
