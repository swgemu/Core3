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
#include <osg/Node>
#include <osg/Geometry>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>

class AppearanceTemplate/* : public IffTemplate*/ {
	String floorName;

	
public:
	virtual void readObject(IffStream* iffStream) {
		iffStream->openForm('APPR');
		if(iffStream->getNextFormType() == '0003') {
			iffStream->openChunk();
			while(iffStream->getRemainingSubChunksNumber() > 0) {
				uint32 type = iffStream->getNextFormType();
				iffStream->openChunk();
				if(type == 'FLOR') {
					iffStream->openChunk();
					bool hasFloor = iffStream->getByte();
					if(hasFloor)
						iffStream->getString(floorName);
					iffStream->closeChunk();
				}
				
				iffStream->closeChunk();
			}
			
			iffStream->closeChunk();
		}
		//ignoring this atm
		iffStream->closeForm('APPR');
	}

	virtual ~AppearanceTemplate() {

	}
	
	String getFloorName() {
		return floorName;
	}

	//void readObject(IffStream* templateData) = 0;

	virtual AppearanceTemplate* getFirstMesh() {
		return NULL;
	}
	
	virtual osg::ref_ptr<osg::Node> draw() = 0;
};

#endif /* APPEARANCETEMPLATE_H_ */
