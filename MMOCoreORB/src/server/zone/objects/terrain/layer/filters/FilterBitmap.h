/*
 * FIlterBIT.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef FILTERBITMAP_H_
#define FILTERBITMAP_H_


#include "../ProceduralRule.h"

#include "FilterProceduralRule.h"

class TargaBitmap;

class FilterBitmap : public ProceduralRule<'FBIT'>, public FilterProceduralRule {
	int bitmapId;
	//int featharingType;
	//float featheringAmount;
	float min;
	float max;

	TargaBitmap* map;

public:
	FilterBitmap() : FilterProceduralRule(5), bitmapId(0), min(0), max(0), map(NULL) { //magic numbers from the client
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown FilterBIT version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openForm('DATA');

		iffStream->openChunk('PARM');

		//5 vars
		bitmapId = iffStream->getInt();
		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();
		min = iffStream->getFloat();
		max = iffStream->getFloat();

		iffStream->closeChunk('PARM');

		iffStream->closeForm('DATA');
	}

	float process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator, FilterRectangle* rect);

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};


#endif /* FILTERBIT_H_ */
