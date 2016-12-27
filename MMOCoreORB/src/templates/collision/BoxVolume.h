/*
 * BoxVolume.h
 *
 *  Created on: 03/20/2016
 *      Author: gslomin
 */

#ifndef BOXVOLUME_H_
#define BOXVOLUME_H_

#include "BaseBoundingVolume.h"

class BoxVolume : public BaseBoundingVolume {
protected:
	AABB bbox;
public:
	bool isBoundingBox() { return true; }
	BoxVolume() : bbox(Vector3(), Vector3()) { }
	virtual void read(IffStream *iff);
	const AABB& getBoundingBox() const {
		return bbox;
	}

#ifdef OSG_RENDERER
	osg::ref_ptr<osg::Node> draw() const;
#endif

};

#endif
