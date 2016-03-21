/*
 * SphereVolume.h
 *
 *  Created on: 03/20/2016
 *      Author: gslomin
 */

#ifndef SPHEREVOLUME_H_
#define SPHEREVOLUME_H_

#include "engine/engine.h"
#include "BaseBoundingVolume.h"

class SphereVolume : public BaseBoundingVolume {
protected:
	AABB bbox;
public:
	SphereVolume() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)) { }
	const AABB& getBoundingBox() {
		return bbox;
	}
	
	//virtual osg::ref_ptr<osg::Node> draw();
};

#endif /* SPHEREVOLUME_H_ */
