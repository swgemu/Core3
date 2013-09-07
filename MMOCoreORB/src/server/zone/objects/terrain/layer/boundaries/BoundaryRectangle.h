/*
 * BoundaryRectangle.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef BOUNDARYRECTANGLE_H_
#define BOUNDARYRECTANGLE_H_


#include "../ProceduralRule.h"
#include "Boundary.h"
#include "../../ProceduralTerrainAppearance.h"

class BoundaryRectangle : public ProceduralRule<'BREC'>,  public Boundary {
	float x0;
	float y0;
	float x1;
	float y1;
	int var7;
	int localWaterTableEnabled;
	float localWaterTableHeight;
	float shaderSize;
	String shaderName;

    float newX0, newX1, newY0, newY1;

    /*
     * result of process() is modified based on this feathering types and then multiplied by the affectors
     * feathering types:
     * 1: x^2
     * 2: sqrt(x)
     * 3: x^2 * (3 - 2x)
     */

public:
	BoundaryRectangle() {
		//ruleType = BOUNDARYRECTANGLE;
	}

	BoundaryRectangle(float x0, float y0, float x1, float y1) {
		this->x0 = x0;
		this->x1 = x1;
		this->y0 = y0;
		this->y1 = y1;
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
		case '0002':
			parseFromIffStream(iffStream, Version<'0002'>());
			break;
		default:
			System::out << "unknown BoundaryRectangle version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0002'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		x0 = iffStream->getFloat();
		y0 = iffStream->getFloat();
		x1 = iffStream->getFloat();
		y1 = iffStream->getFloat();
		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();

		if (featheringAmount < 0)
			featheringAmount = 0;
		else if (featheringAmount > 1)
			featheringAmount = 1;

		iffStream->closeChunk('DATA');

		initialize();
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

		if (featheringAmount < 0)
			featheringAmount = 0;
		else if (featheringAmount > 1)
			featheringAmount = 1;

		var7 = iffStream->getInt();
		localWaterTableEnabled = iffStream->getInt(); // local water table enabled?
		localWaterTableHeight = iffStream->getFloat(); // local water table height
		shaderSize = iffStream->getFloat();
		iffStream->getString(shaderName);

		iffStream->closeChunk('DATA');

		initialize();
	}

	float getLocalWaterTableHeight() {
		return localWaterTableHeight;
	}

	float process(float x, float y) {
		/*v3 = this;
		  if ( *(_BYTE *)(this + 60) ) initialized to 0
		  {
		    v31 = x;
		    v32 = y;
		    sub_ABB330(this + 64, (int)&v33, (int)&v31);
		    x = v33;
		    y = v34;
		  }*/

		if (x < x0)
			return 0.0;

		if (x > x1 || y < (double)y0) {
			//System::out << "x > x1" << x << " " << x1 << " o y < y0" << y << " " << y0 << endl;
			return 0.0;
		}

		if (y > y1)
			return 0.0;

		if (featheringAmount == 0.0)
			return 1.0;

		if (!(x < newX1 || x > newX0 || y < newY1 || y > newY0))
			return 1.0;

		float v36 = x - x0;
		float v35 = x1 - x;
		float v34 = y - y0;
		y = y1 - y;
		x = x1 - x0;
		float v28 = y1 - y0;
		float v32 = v28;
		float* v27 = &v32;
		if ( v28 >= x )
			v27 = &x;

		float v30 = featheringAmount * *v27 * 0.5;
		float v29 = v30;
		if ( v36 < v30 )
			v29 = v36;
		if ( v35 < v29 )
			v29 = v35;
		if ( v34 < v29 )
			v29 = v34;
		if ( y < v29 )
			v29 = y;

		return v29 / v30;
	}

	void translateBoundary(float x, float y) {
		x0 += x;
		x1 += x;

		y0 += y;
		y1 += y;

		initialize();
	}

	void initialize() {
		if (x0 > x1) {
			double v1 = x0;
			x0 = x1;
			x1 = v1;
		}

		if (y0 > y1) {
			double v2 = y0;
			y0 = y1;
			y1 = v2;
		}

		float v3 = y1 - y0;

		if ((y1 - y0) >= (x1 - x0))
			v3 = (x1 - x0);

		double v7 = featheringAmount * v3 * 0.5;

		newX0 = v7 + x0;
		newY0 = v7 + y0;
		newX1 = x1 - v7;
		newY1 = y1 - v7;
	}

	float getMinX() {
		return x0;
	}

	float getMaxX() {
		return x1;
	}

	float getMinY() {
		return y0;
	}

	float getMaxY() {
		return y1;
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};



#endif /* BOUNDARYRECTANGLE_H_ */
