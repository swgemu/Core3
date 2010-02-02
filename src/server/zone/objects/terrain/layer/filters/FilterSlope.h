/*
 * FilterSlope.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef FILTERSLOPE_H_
#define FILTERSLOPE_H_


#include "../ProceduralRule.h"

class FilterSlope : public ProceduralRule<'FSLP'> {
	float minAngle;
	float maxAngle;
	int featheringType;
	float featheringDistance; // I have seen this set to 0.1 with type set to 0. Removed flora from slopes on dant

public:
	FilterSlope() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0002':
			parseFromIffStream(iffStream, Version<'0002'>());
			break;
		default:
			System::out << "unknown FilderSlope version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0002'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		minAngle = iffStream->getFloat();
		maxAngle = iffStream->getFloat();
		featheringType = iffStream->getInt();
		featheringDistance = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};

#endif /* FILTERSLOPE_H_ */
