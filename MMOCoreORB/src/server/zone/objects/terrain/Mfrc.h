/*
 * Mfrc.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef MFRC_H_
#define MFRC_H_

#include "TemplateVariable.h"

class Mfrc : public TemplateVariable<'MFRC'> {
	int seed;
	int biasType;
	float biasValue;
	int gainType;
	float gainValue;
	uint32 octaves;
	float octaveParam;
	float amplitude;
	float x_freq;
	float y_freq;
	uint32 x_offset;
	uint32 z_offset;
	uint32 useCombination;
public:
	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0001':
			parseFromIffStream(iffStream, Version<'0001'>());
			break;
		default:
			System::out << "unknown MFRC version " << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
		iffStream->openChunk('DATA');

		seed = iffStream->getInt();
		biasType = iffStream->getInt();
		biasValue = iffStream->getFloat();
		gainType = iffStream->getInt();
		gainValue = iffStream->getFloat();
		octaves = iffStream->getUnsignedInt();
		octaveParam = iffStream->getFloat();
		amplitude = iffStream->getFloat();
		x_freq = iffStream->getFloat();
		y_freq = iffStream->getFloat();
		x_offset = iffStream->getUnsignedInt();
		z_offset = iffStream->getUnsignedInt();
		useCombination = iffStream->getUnsignedInt();

		iffStream->closeChunk('DATA');
	}
};


#endif /* MFRC_H_ */
