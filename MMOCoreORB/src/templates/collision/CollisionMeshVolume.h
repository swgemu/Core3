/*
 * CollisionMeshVolume.h
 *
 *  Created on: 03/20/2016
 *      Author: gslomin
 */

#ifndef COLLISIONMESHVOLUME_H_
#define COLLISIONMESHVOLUME_H_

#include <algorithm>

#include "BaseBoundingVolume.h"
#include "engine/util/u3d/AABB.h"
#include "engine/util/u3d/Vector3.h"
#include "system/util/Vector.h"

namespace engine {
namespace util {
class IffStream;
}  // namespace util
}  // namespace engine

class CollisionMeshVolume : public BaseBoundingVolume {
protected:
	Vector<Vector3> verts;
	Vector<unsigned int> indicies;
	AABB bbox;
public:
	bool isCollisionMesh() { return true; }
	CollisionMeshVolume() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)){ }
	virtual void read(IffStream* iff);
	const AABB& getBoundingBox() const {
		return bbox;
	}

#ifdef OSG_RENDERER
	virtual osg::ref_ptr<osg::Node> draw() const;
#endif
};

#endif /* COLLISIONMESHVOLUME_H_ */
