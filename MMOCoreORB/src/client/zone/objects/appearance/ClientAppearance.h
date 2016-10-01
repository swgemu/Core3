#ifndef CLIENTAPPEARANCE_H_
#define CLIENTAPPEARANCE_H_
#include "templates/appearance/AppearanceTemplate.h"
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
class ClientAppearance {
public:
	const AppearanceTemplate* appearanceTemplate;
	
	ClientAppearance(const AppearanceTemplate *tmpl) {
		appearanceTemplate = tmpl;
	}
	
	const AppearanceTemplate* getAppearanceTemplate() {
		return appearanceTemplate;
	}
	
	virtual osg::ref_ptr<osg::Node> draw() {
		//TODO: If we got here, just draw the bounding volume
//		const BaseBoundingVolume *volume = appearanceTemplate->getBoundingVolume();
//		const BaseBoundingVolume *collisionVolume = appearanceTemplate->getCollisionVolume();
//		if(collisionVolume)
//			return collisionVolume->draw();
//		else if(volume)
//			return volume->draw();
		return NULL;
	}
};

#endif
