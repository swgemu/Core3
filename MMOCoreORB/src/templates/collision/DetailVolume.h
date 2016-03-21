/*
 * DetailVolume.h
 *
 *  Created on: 03/20/2016
 *      Author: gslomin
 */

#ifndef DETAILVOLUME_H_
#define DETAILVOLUME_H_

#include "engine/engine.h"
#include "CompositeVolume.h"

class DetailVolume : public CompositeVolume {
public:
	bool isDetailVolume() { return true; }
	DetailVolume() { }
	virtual void read(IffStream *iff);
	//virtual osg::ref_ptr<osg::Node> draw();
};
#endif /* DETAILVOLUME_H_ */
