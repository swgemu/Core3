/*
 * BoundaryCircle.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef BOUNDARYCIRCLE_H_
#define BOUNDARYCIRCLE_H_

#include "../ProceduralRule.h"
#include "Boundary.h"

class BoundaryCircle : public ProceduralRule<'BCIR'>, public Boundary {
	float x;
	float y;
	float radius;
	int featheringType;
	float featheringAmount;

public:
	BoundaryCircle() {
		ruleType = BOUNDARYCIRCLE;
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0002':
			parseFromIffStream(iffStream, Version<'0002'>());
			break;
		default:
			System::out << "unknown BoundaryCircle version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0002'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		// 5 vars

		x = iffStream->getFloat();
		y = iffStream->getFloat();
		radius = iffStream->getFloat();
		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};


#endif /* BOUNDARYCIRCLE_H_ */
