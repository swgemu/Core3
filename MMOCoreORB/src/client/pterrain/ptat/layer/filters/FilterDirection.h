/*
 * FilterDirection.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef FILTERDIRECTION_H_
#define FILTERDIRECTION_H_


#include "FilterProceduralRule.h"

class FilterDirection : public ProceduralRule<'FDIR'>, public FilterProceduralRule {
	float minDegree;//+20h
	float min;//+28h
	float maxDegree;
	float max;

public:
	FilterDirection() {
		filterType = 0;
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

	/*void setMinDegree(float deg) {
		minDegree = deg;

		if (-M_PI >= minDegree) {
			minDegree = -M_PI
		}
	}*/

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		minDegree = iffStream->getFloat();

		//setMinAngle(M_PI * minDegree * 0.005555555690079927);

		maxDegree = iffStream->getFloat();
		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};



#endif /* FILTERDIRECTION_H_ */
