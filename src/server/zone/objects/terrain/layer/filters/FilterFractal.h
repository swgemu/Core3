/*
 * FIlterFractal.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef FILTERFRACTAL_H_
#define FILTERFRACTAL_H_


#include "../ProceduralRule.h"

class TerrainGenerator;

class FilterFractal : public ProceduralRule<'FFRA'> {
	int fractalId; // Fractal Group ID to modify (MGRP)
	int featheringType;
	float featheringAmount;
	float min;
	float max; // Scale/Stepping?
	float var6; // Scale/Stepping?

public:
	FilterFractal() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
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

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0005'>) {
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

	float process(float x, float y, float& baseValue, TerrainGenerator* terrainGenerator);
};

#endif /* FILTERFRACTAL_H_ */
