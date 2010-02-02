/*
 * AffectorHeightFractal.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORHEIGHTFRACTAL_H_
#define AFFECTORHEIGHTFRACTAL_H_


#include "../ProceduralRule.h"

class AffectorHeightFractal : public ProceduralRule<'AHFR'> {
	int fractalId; // fractal group id in MGRP
	int var2;
	float height;

public:
	AffectorHeightFractal() {

	}

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
		var2 = iffStream->getInt();
		height = iffStream->getFloat();

		iffStream->closeChunk('PARM');
		iffStream->closeForm('DATA');
	}
};



#endif /* AFFECTORHEIGHTFRACTAL_H_ */
