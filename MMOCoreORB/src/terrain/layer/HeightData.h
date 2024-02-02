/*
 *  HeightData.h
 *
 *  Created on: 31/01/2010
 *  Author: victor
 */

#ifndef HEIGHTDATA_H_
#define HEIGHTDATA_H_

#include "../TemplateVariable.h"
#include "Segment.h"

// #define DEBUG_AFFECTOR_ROAD

class HeightData : public TemplateVariable<'HDTA'> {
	Vector<Segment*> segments;

public:
	HeightData() : IffTemplateVariable() {
	}

	~HeightData() {
		for (int i = 0; i < segments.size(); ++i)
			delete segments.get(i);

		segments.removeAll();
	}

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>);
	void findNearestHeight(float& baseValue, Vector3 worldPosition, Vector3 roadStart, Vector3 roadCenter, float direction);
};

#endif /* HEIGHTDATA_H_ */
