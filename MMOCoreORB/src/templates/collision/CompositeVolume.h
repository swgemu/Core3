/*
 * CompositeVolume.h
 *
 *  Created on: 03/20/2016
 *      Author: gslomin
 */

#ifndef COMPOSITEVOLUME_H_
#define COMPOSITEVOLUME_H_

#include <algorithm>

#include "BaseBoundingVolume.h"
#include "engine/util/u3d/AABB.h"
#include "engine/util/u3d/Vector3.h"
#include "system/lang/ref/Reference.h"
#include "system/util/Vector.h"

namespace engine {
namespace util {
class IffStream;
}  // namespace util
}  // namespace engine

class CompositeVolume : public BaseBoundingVolume {
protected:
	Vector<Reference<BaseBoundingVolume*> > volumes;
	AABB bbox;
public:
	bool isCompositeVolume() { return true; }
	CompositeVolume() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)){ }
	const AABB& getBoundingBox() const {
		return bbox;
	}
	virtual void read(IffStream *iff);
#ifdef OSG_RENDERER
	virtual osg::ref_ptr<osg::Node> draw() const;
#endif
};

#endif /* COMPOSITEVOLUME_H_ */
