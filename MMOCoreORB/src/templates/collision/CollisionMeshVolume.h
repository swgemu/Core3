/*
 * CollisionMeshVolume.h
 *
 *  Created on: 03/20/2016
 *      Author: gslomin
 */

#ifndef COLLISIONMESHVOLUME_H_
#define COLLISIONMESHVOLUME_H_

#include "engine/engine.h"
#include "BaseBoundingVolume.h"

class CollisionMeshVolume : public BaseBoundingVolume {
protected:
	Vector<Vector3> verts;
	Vector<unsigned int> indicies;
	AABB bbox;
public:
	bool isCollisionMesh() { return true; }
	CollisionMeshVolume() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)){ }
	virtual void read(IffStream* iff);
	const AABB& getBoundingBox() {
		return bbox;
	}
	//virtual osg::ref_ptr<osg::Node> draw();
};

#endif /* COLLISIONMESHVOLUME_H_ */
