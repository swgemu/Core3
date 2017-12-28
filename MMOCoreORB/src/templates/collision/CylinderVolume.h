/*
 * CylinderVolume.h
 *
 *      Author: gslomin
 */

#ifndef CYLINDERVOLUME_H_
#define CYLINDERVOLUME_H_

#include "BaseBoundingVolume.h"
#include "engine/util/u3d/AABB.h"
#include "engine/util/u3d/Sphere.h"
#include "engine/util/u3d/Vector3.h"

namespace engine {
namespace util {
class IffStream;
}  // namespace util
}  // namespace engine

class CylinderVolume : public BaseBoundingVolume {
protected:
	AABB bbox;
public:
	Sphere base;
	float height;
	CylinderVolume() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)), base(Vector3(0, 0, 0), 0), height(0) { }
	virtual const AABB& getBoundingBox() const {
		return bbox;
	}
	virtual void read(IffStream *iff);

#ifdef OSG_RENDERER
	virtual osg::ref_ptr<osg::Node> draw() const;
#endif
};

#endif /* CYLINDERVOLUME_H_ */
