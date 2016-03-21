/*
 * PathNode.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef BOUNDINGVOLUMES_H_
#define BOUNDINGVOLUMES_H_

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
#endif /* BOUNDINGVOLUMES_H_ */
