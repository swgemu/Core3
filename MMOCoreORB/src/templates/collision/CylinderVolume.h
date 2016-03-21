/*
 * CylinderVolume.h
 *
 *      Author: gslomin
 */

#ifndef CYLINDERVOLUME_H_
#define CYLINDERVOLUME_H_

#include "engine/engine.h"
#include "BaseBoundingVolume.h"

class CylinderVolume : public BaseBoundingVolume {
protected:
	AABB bbox;
public:
	Sphere base;
	float height;
	CylinderVolume() : base(Vector3(0, 0, 0), 0), bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)) { }
	virtual const AABB& getBoundingBox() {
		return bbox;
	}
	virtual void read(IffStream *iff);
	//virtual osg::ref_ptr<osg::Node> draw();
};
#endif /* CYLINDERVOLUME_H_ */
