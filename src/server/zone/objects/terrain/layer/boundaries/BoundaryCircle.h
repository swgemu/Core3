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
	float centerX;
	float centerY;
	float radius;
	float radiusSquared;

public:
	BoundaryCircle() {
		//ruleType = BOUNDARYCIRCLE;
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

		centerX = iffStream->getFloat();
		centerY = iffStream->getFloat();
		radius = iffStream->getFloat();
		radiusSquared = radius * radius;
		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();

		if (featheringAmount < 0)
			featheringAmount = 0;
		else if (featheringAmount > 1)
			featheringAmount = 1;

		iffStream->closeChunk('DATA');
	}

	float process(float x, float y) {
		float v3 = centerX - x;
		float v4 = centerY - y;
		float result;

		float v8 = v4 * v4 + v3 * v3;

		if (v8 <= radiusSquared) {
			float v7 = (1.0 - featheringAmount) * radius;
			float v6 = v7 * v7;

			if (v8 > v6)
				result = 1.0 - (v8 - v6) / (radiusSquared - v6);
			else
				result = 1.0;

		} else {
			result = 0.0;
		}

		return result;
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};


#endif /* BOUNDARYCIRCLE_H_ */
