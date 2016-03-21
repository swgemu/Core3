/*
 * TerrainAppearance.h
 *
 *  Created on: 18/10/2013
 *      Author: victor
 */

#ifndef TERRAINAPPEARANCE_H_
#define TERRAINAPPEARANCE_H_

#include "engine/engine.h"

class TerrainAppearance : public Object {
public:
	virtual bool load(engine::util::IffStream* iffStream) = 0;
	virtual float getSize() = 0;

	virtual float getHeight(float x, float y) {
		return 0;
	}

	virtual bool getWater(float x, float y, float& waterHeight) {
		return false;
	}
};


#endif /* TERRAINAPPEARANCE_H_ */
