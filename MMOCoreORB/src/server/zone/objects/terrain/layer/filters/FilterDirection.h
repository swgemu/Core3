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
	float maxDegree; // +1ch
	float max; // +24h

public:
	FilterDirection()  : FilterProceduralRule(3) {
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

	void setMinDegree(float deg) {
		minDegree = deg;

		if (-M_PI >= minDegree) {
			minDegree = -M_PI;
		}

		min = minDegree * 1 / (2 * M_PI);
	}

	void setMaxDegree(float deg) {
		maxDegree = deg;

		if (deg >= M_PI) {
			maxDegree = M_PI;
		}

		max = maxDegree * 1 / (2 * M_PI);
	}
/*
	//Disabled in the server(only need height) because cant filter by direction and have affectors that affect height in this layer or sublayers(soe format rule apparently)
	float process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator, FilterRectangle* rect) {
		//double v6[2];
		 * v1 = sqrt(x*x + y*y + z*z)...dx = 1 / v1 * x
		 * atan2(dy, dx) / 2pi + 0.5
		//float v6 = *(_DWORD *)(*(_DWORD *)(a6 + 0x3C) + 8) + 12 * (i + j * **(_DWORD **)(a6 + 0x3C));
		//float v7 = atan2(*(float *)(v6 + 8), *(float *)v6) * one_div_2pi + 0.5;
		float v12 = v7;
		float result;

		if ( v7 >= this->min && v12 <= (long double)this->max ) {
			float v9 = (this->max - this->min) * this->featheringAmount * 0.5;
			if ( v9 + this->min > v12 || this->max - v9 < v12 ) {
				float v11 = this->max - v12;
				float v13 = v12 - this->min;

				float v10 = v9;
				if ( v11 < v9 )
					v10 = v11;
				if ( v13 < v10 )
					v10 = v13;

				result = v10 / v9;
			} else {
				result = 1.0;
			}
		} else {
			result = 0;
		}

		return result;
	}
	*/

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		minDegree = iffStream->getFloat();
		setMinDegree(minDegree);

		//setMinAngle(M_PI * minDegree * 0.005555555690079927);

		maxDegree = iffStream->getFloat();
		setMaxDegree(maxDegree);

		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};



#endif /* FILTERDIRECTION_H_ */
