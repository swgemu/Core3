/*
 * AffectorHeightFractal.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORHEIGHTFRACTAL_H_
#define AFFECTORHEIGHTFRACTAL_H_

#include "../ProceduralRule.h"

class TerrainGenerator;

class AffectorHeightFractal : public ProceduralRule<'AHFR'> {
	int fractalId; // fractal group id in MGRP
	int operationType;
	float height;

public:
	AffectorHeightFractal() {

	}

	void process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator);

	void parseFromIffStream(engine::util::IffStream* iffStream) {
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

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0003'>) {
		informationHeader.readObject(iffStream);

		iffStream->openForm('DATA');

		iffStream->openChunk('PARM');

		fractalId = iffStream->getInt();
		operationType = iffStream->getInt();

		height = iffStream->getFloat();

		iffStream->closeChunk('PARM');
		iffStream->closeForm('DATA');
	}

	inline int getFractalId() {
		return fractalId;
	}

	inline float getHeight() {
		return height;
	}
};



#endif /* AFFECTORHEIGHTFRACTAL_H_ */
