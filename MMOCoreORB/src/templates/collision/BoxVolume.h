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
	BoxVolume() : bbox(Vector3(), Vector3()) { }
	const AABB& getBoundingBox() const {
		return bbox;
	}

	void read(IffStream *iff);

	bool isBoundingBox() const {
		return true;
	}

#ifdef OSG_RENDERER
	osg::ref_ptr<osg::Node> draw() const;
#endif

};

#endif
