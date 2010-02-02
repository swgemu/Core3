/*
 * FilterDirection.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef FILTERDIRECTION_H_
#define FILTERDIRECTION_H_


#include "../ProceduralRule.h"

class FilterDirection : public ProceduralRule<'FDIR'> {
	float minDegree;
	float maxDegree;
	int var3; // Feathering type? Leftover?
	float var4;

public:
	FilterDirection() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown FilterDirection version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		minDegree = iffStream->getFloat();
		maxDegree = iffStream->getFloat();
		var3 = iffStream->getInt();
		var4 = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};



#endif /* FILTERDIRECTION_H_ */
