/*
 * BoundaryRectangle.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef BOUNDARYRECTANGLE_H_
#define BOUNDARYRECTANGLE_H_


#include "../ProceduralRule.h"
#include "../affectors/AffectorRiver.h"
#include "Boundary.h"
#include "../../ProceduralTerrainAppearance.h"

class BoundaryRectangle : public ProceduralRule<'BREC'>,  public Boundary {
	float x0;
	float y0;
	float x1;
	float y1;
	int featheringType;
	float featheringAmount; // how much to soften sides (like on a hill)
	int var7;
	int localWaterTableEnabled;
	float localWaterTableHeight;
	float shaderSize;
	String shaderName;

public:
	BoundaryRectangle() {
		ruleType = BOUNDARYRECTANGLE;
	}

	~BoundaryRectangle() {

	}

	void executeRule(ProceduralTerrainAppearance* generator) {
		if (localWaterTableEnabled != 0)
			generator->insertWaterBoundary(this);
	}

	bool containsPoint(float X, float Y) {
		//System::out << "checking in rectangle if contains point" << endl;
		float w = fabs(x1 - x0);
		float h = fabs(y1 - y0);

		/*if ((w + h) < 0) {
			// At least one of the dimensions is negative...
			return false;
		}*/
		// Note: if either dimension is zero, tests below must return false...
		if (X < x0 || Y < y0) {
			return false;
		}

		w += x0;
		h += y0;
		// overflow || intersect
		return ((w < x0 || w > X) && (h < y0 || h > Y));
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0003':
			parseFromIffStream(iffStream, Version<'0003'>());
			break;
		default:
			System::out << "unknown BoundaryRectangle version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0003'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		x0 = iffStream->getFloat();
		y0 = iffStream->getFloat();
		x1 = iffStream->getFloat();
		y1 = iffStream->getFloat();
		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();
		var7 = iffStream->getInt();
		localWaterTableEnabled = iffStream->getInt(); // local water table enabled?
		localWaterTableHeight = iffStream->getFloat(); // local water table height
		shaderSize = iffStream->getFloat();
		iffStream->getString(shaderName);

		iffStream->closeChunk('DATA');
	}


	float getLocalWaterTableHeight() {
		return localWaterTableHeight;
	}
};



#endif /* BOUNDARYRECTANGLE_H_ */
