/*
 * SphereVolume.h
 *
 *  Created on: 03/20/2016
 *      Author: gslomin
 */

#ifndef SPHEREVOLUME_H_
#define SPHEREVOLUME_H_

#include "BaseBoundingVolume.h"

class SphereVolume : public BaseBoundingVolume {
protected:
	AABB bbox;
public:
	SphereVolume() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)) { }
	const AABB& getBoundingBox() const {
		return bbox;
	}
#ifdef OSG_RENDERER
	virtual osg::ref_ptr<osg::Node> draw() const;
#endif
};

#endif /* SPHEREVOLUME_H_ */
