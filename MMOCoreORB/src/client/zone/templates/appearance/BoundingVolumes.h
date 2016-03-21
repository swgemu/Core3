/*
 * PathNode.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef BOUNDINGVOLUMES_H_
#define BOUNDINGVOLUMES_H_

#include "engine/engine.h"
#include <osg/Node>
#include <osg/Geometry>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>

class BaseBoundingVolume : public Logger {
protected:
	Sphere bsphere;
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
	virtual osg::ref_ptr<osg::Node> draw() = 0;
};

class BoxVolume : public BaseBoundingVolume {
protected:
	AABB bbox;
public:
	bool isBoundingBox() { return true; }
	BoxVolume() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)) { }
	virtual void read(IffStream *iff);
	const AABB& getBoundingBox() {
		return bbox;
	}
	virtual osg::ref_ptr<osg::Node> draw();
};

class SphereVolume : public BaseBoundingVolume {
protected:
	AABB bbox;
public:
	SphereVolume() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)) { }
	const AABB& getBoundingBox() {
		return bbox;
	}
	
	virtual osg::ref_ptr<osg::Node> draw();
};

class MeshVolume : public BaseBoundingVolume {
protected:
	Vector<Vector3> verts;
	Vector<unsigned int> indicies;
	AABB bbox;
public:
	bool isCollisionMesh() { return true; }
	MeshVolume() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)){ }
	virtual void read(IffStream* iff);
	const AABB& getBoundingBox() {
		return bbox;
	}
	virtual osg::ref_ptr<osg::Node> draw();
};

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
	virtual osg::ref_ptr<osg::Node> draw();
};

class ComponentVolume : public CompositeVolume {
public:
	bool isComponentVolume() { return true; }
	ComponentVolume() { }
		virtual void read(IffStream *iff);
};

class DetailVolume : public CompositeVolume {
public:
	bool isDetailVolume() { return true; }
	DetailVolume() { }
	virtual void read(IffStream *iff);
	virtual osg::ref_ptr<osg::Node> draw();
};

class BoundingVolumeList : public Vector<BaseBoundingVolume*> {
public:
	BoundingVolumeList() { }
	void read(IffStream *iff);
	static BaseBoundingVolume* getVolume(IffStream *iff);
};

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
	virtual osg::ref_ptr<osg::Node> draw();
};
#endif /* BOUNDINGVOLUMES_H_ */
