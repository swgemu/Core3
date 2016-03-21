/*
 * BoxVolume.h
 *
 *  Created on: 03/20/2016
 *      Author: gslomin
 */

#ifndef BOXVOLUME_H_
#define BOXVOLUME_H_

#include "engine/engine.h"
#include "BaseBoundingVolume.h"

class BoxVolume : public BaseBoundingVolume {
protected:
	AABB bbox;
public:
	bool isBoundingBox() { return true; }
	
	BoxVolume() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)) { }
	
	virtual void read(IffStream *iff);
	
	const AABB& getBoundingBox() {
		return bbox;
	}
};

#endif