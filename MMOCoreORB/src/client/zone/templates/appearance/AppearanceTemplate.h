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
public:
	String floorName;
	AABB bbox;
	Sphere bsphere;
	
public:
	virtual void readObject(IffStream* iffStream) {
		iffStream->openForm('APPR');
		if(iffStream->getNextFormType() == '0003') {
			iffStream->openForm('0003');
			while(iffStream->getRemainingSubChunksNumber() > 0) {
				uint32 type = iffStream->getNextFormType();
				if(type == 'FLOR') {
					iffStream->openChunk();
					iffStream->openChunk();
					bool hasFloor = iffStream->getByte();
					if(hasFloor)
						iffStream->getString(floorName);
					iffStream->closeChunk();
					iffStream->closeChunk();
				} else if(type == 'EXBX') {
					iffStream->openForm('EXBX');
					iffStream->openForm('0001');
					iffStream->openForm('EXSP');
					iffStream->openForm('0001');
					iffStream->openChunk('SPHR');
					Vector3 center;
					float radius;
					center.setX(iffStream->getFloat());
					center.setY(iffStream->getFloat());
					center.setZ(iffStream->getFloat());
					
					radius = iffStream->getFloat();
					bsphere = Sphere(center, radius);
					iffStream->closeChunk('SPHR');
					iffStream->closeForm('0001');
					iffStream->closeForm('EXSP');
					
					
					iffStream->openChunk('BOX ');
					Vector3 min, max;
					max.setX(iffStream->getFloat());
					max.setY(iffStream->getFloat());
					max.setZ(iffStream->getFloat());
					
					min.setX(iffStream->getFloat());
					min.setY(iffStream->getFloat());
					min.setZ(iffStream->getFloat());
					bbox = AABB(min, max);
					iffStream->closeChunk('BOX');
					iffStream->closeForm('0001');
					iffStream->closeForm('EXBX');
					
				}else {
					iffStream->openForm(type);
					iffStream->closeForm(type);
				}
			}
			
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
	
	AppearanceTemplate() : bbox(Vector3(0, 0, 0), Vector3(0, 0, 0)), bsphere(Vector3(0, 0, 0), 0) {
		
	}
	
	String getFloorName() {
		return floorName;
	}

	//void readObject(IffStream* templateData) = 0;

	virtual AppearanceTemplate* getFirstMesh() {
		return this;
	}
	
	virtual osg::ref_ptr<osg::Node> draw() = 0;
};

#endif /* APPEARANCETEMPLATE_H_ */
