/*
 * BaseBoundingVolume.h
 *
 *  Created on: 03/20/2016
 *      Author: gslomin
 */

#ifndef BASEBOUNDINGVOLUME_H_
#define BASEBOUNDINGVOLUME_H_

#include "engine/engine.h"

class BaseBoundingVolume : public Logger {
protected:
	Sphere bsphere; // All volumes have an enclosing sphere
public:
	BaseBoundingVolume() : bsphere(Vector3(0, 0, 0), 0) { }
	virtual const AABB& getBoundingBox() = 0;
	virtual const Sphere& getBoundingSphere() {
		return bsphere;
	}
	
	virtual bool isBoundingBox() { return false; }
	virtual bool isCollisionMesh() { return false; }
	virtual bool isCompositeVolume() { return false; }
	virtual bool isComponentVolume() { return false; }
	virtual bool isDetailVolume() { return false; }
	
	virtual void read(IffStream *iff);
};

#endif /* BASEBOUNDINGVOLUME_H_ */
