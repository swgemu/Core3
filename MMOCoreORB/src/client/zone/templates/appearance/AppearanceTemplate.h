/*
 * AppearanceTemplate.h
 *
 *  Created on: 11/12/2010
 *      Author: victor
 */

#ifndef APPEARANCETEMPLATE_H_
#define APPEARANCETEMPLATE_H_

#include "engine/engine.h"
#include "../IffTemplate.h"
#include "zone/templates/appearance/BoundingVolumes.h"
#include <osg/Node>
#include <osg/Geometry>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>
class MeshData;
class AppearanceTemplate/* : public IffTemplate*/ {
public:
	String floorName;
	BaseBoundingVolume *volume;
	BaseBoundingVolume *collisionVolume;
	
public:
	virtual void readObject(IffStream* iffStream) {
		
		
		
		iffStream->openForm('APPR');
		if(iffStream->getNextFormType() == '0003') {
			iffStream->openForm('0003');
			volume = BoundingVolumeList::getVolume(iffStream);
			collisionVolume = BoundingVolumeList::getVolume(iffStream);
			
			
			iffStream->openForm('HPTS');
			
			// Skip loading hardpoints
			iffStream->closeForm('HPTS');
			
			iffStream->openForm('FLOR');
			iffStream->openChunk('DATA');
			bool hasFloor = iffStream->getByte();
			if(hasFloor)
				iffStream->getString(floorName);
			iffStream->closeChunk('DATA');
			iffStream->closeForm('FLOR');
			
			iffStream->closeForm('0003');
		} else {
			static Logger logger;
			logger.info("Unknown appearance template chunk", true);
		}
		//ignoring this atm
		iffStream->closeForm('APPR');
	}

	virtual ~AppearanceTemplate() {

	}
	
	AppearanceTemplate() {
		collisionVolume = NULL;
		volume = NULL;
	}
	
	String getFloorName() {
		return floorName;
	}
//	
//	AABB getAABB() {
//		return bbox;
//	}
//	
//	Sphere getSphere() {
//		return bsphere;
//	}

	//void readObject(IffStream* templateData) = 0;

	virtual AppearanceTemplate* getFirstMesh() {
		return this;
	}
	virtual Vector<MeshData*> getTransformedMeshData(Matrix4 transform) {
		Vector<MeshData*> dummy;
		return dummy;
	}
	virtual osg::ref_ptr<osg::Node> draw() = 0;// {
//		if(collisionVolume)
//			return collisionVolume->draw();
//		else if(volume)
//			return volume->draw();
//	}
};

#endif /* APPEARANCETEMPLATE_H_ */
