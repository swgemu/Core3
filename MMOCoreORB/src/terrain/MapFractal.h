/*
 * Mfrc.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef MFRC_H_
#define MFRC_H_

#include "TemplateVariable.h"
#include "Random.h"
#include "PerlinNoise.h"

class MapFractal : public TemplateVariable<'MFRC'> {
	PerlinNoise* noise;
	trn::ptat::Random* rand;

	int bias;
	float biasValue;
	int gainType;
	float gainValue;
	int octaves;
	float octavesParam;
	float amplitude;
	float xFrequency;
	float yFrequency;
	float xOffset;
	float zOffset;
	int combination;

	bool unkown;

	static double log05;

	float offset32;

public:
	MapFractal();

	~MapFractal() {
		delete noise;
		noise = NULL;

		delete rand;
		rand = NULL;
	}

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>);

	float getNoise(float x, float y, int i = 0, int  j = 0);
	float getNoise(float x, int i = 0, int j = 0);

	double calculateCombination1(float v39);
	double calculateCombination1(float xfreq, float yfreq);
	double calculateCombination2(float xfreq, float yfreq);
	double calculateCombination3(float xfreq, float yfreq);
	double calculateCombination4(float xfreq, float yfreq);
	double calculateCombination5(float xfreq, float yfreq);

	void setSeed(int seed);

	inline void setBias(int bias) {
		this->bias = bias; // bias
	}

	inline void setBiasValue(float value) {
		biasValue = value; // bias value
	}

	inline void setGainType(int type) {
		gainType = type; // gain type
	}

	inline void setGainValue(float val) {
		gainValue = val; // gain value
	}

	inline void setOctaves(int octaves) {
		this->octaves = octaves; // octaves
	}

	inline void setOctavesParam(float param) {
		octavesParam = param; // octaves param
	}

	void setAmplitude(float ampl) {
		amplitude = ampl;

		offset32 = 0.f;

		float v3 = 0;
		float v2 = 1.0;

		for (int i = 0; i < octaves; ++i) {
			v3 = v3 + v2;
			v2 = v2 * amplitude;
		}

		offset32 = v3;

		if (offset32 != 0)
			offset32 = 1.0 / offset32;
	}

	inline void setXFreq(float xfreq) {
		xFrequency = xfreq; // x.freq
	}

	inline void setYFreq(float yfreq) {
		yFrequency = yfreq; // y.freq
	}

	inline void setZOffset(float offset) {
		zOffset = offset; // z.offset
	}

	inline void setXOffset(float offset) {
		xOffset = offset; // x.offset
	}

	inline void setCombination(int comb) {
		combination = comb; // combination
	}
};


#endif /* MFRC_H_ */
