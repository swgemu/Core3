/*
 * Hdta.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef HDTA_H_
#define HDTA_H_

#include "../TemplateVariable.h"
#include "Segment.h"

class Hdta : public TemplateVariable<'HDTA'> {
	Vector<Segment*> segments;

public:
	Hdta() : IffTemplateVariable() {
	}

	~Hdta() {
		for (int i = 0; i < segments.size(); ++i)
			delete segments.get(i);

		segments.removeAll();
	}

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>);
	void findNearestHeight(float& baseValue, float positionX, float positionY, float roadX, float roadY);
};

#endif /* HDTA_H_ */
