/*
 * CompositeVolume.h
 *
 *  Created on: 03/20/2016
 *      Author: gslomin
 */

#ifndef COMPOSITEVOLUME_H_
#define COMPOSITEVOLUME_H_

#include "engine/engine.h"
#include "BaseBoundingVolume.h"

class CompositeVolume : public BaseBoundingVolume {
protected:
	Vector<BaseBoundingVolume*> volumes;
	AABB bbox;
public:
	bool isCompositeVolume() { return true; }
	CompositeVolume() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)){ }
	const AABB& getBoundingBox() {
		return bbox;
	}
	virtual void read(IffStream *iff);
	//virtual osg::ref_ptr<osg::Node> draw();
};

#endif /* COMPOSITEVOLUME_H_ */
