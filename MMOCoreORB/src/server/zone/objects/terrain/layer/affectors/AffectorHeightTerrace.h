/*
 * AffectorHeightTerrace.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORHEIGHTTERRACE_H_
#define AFFECTORHEIGHTTERRACE_H_


#include "../ProceduralRule.h"

class AffectorHeightTerrace : public ProceduralRule<'AHTR'> {
	float flatRatio;
	float height;

public:
	AffectorHeightTerrace() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0004':
			parseFromIffStream(iffStream, Version<'0004'>());
			break;
		default:
			System::out << "unknown AffectorHeightTerrace version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0004'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		flatRatio = iffStream->getFloat();
		height = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};

#endif /* AFFECTORHEIGHTTERRACE_H_ */
