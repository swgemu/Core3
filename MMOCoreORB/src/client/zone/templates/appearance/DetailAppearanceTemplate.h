/*
 * DetailAppearanceTemplate.h
 *
 *  Created on: 10/12/2010
 *      Author: victor
 */

#ifndef DETAILAPPEARANCETEMPLATE_H_
#define DETAILAPPEARANCETEMPLATE_H_

#include "engine/engine.h"
#include "AppearanceTemplate.h"
#include <osg/Node>
#include <osg/Geometry>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>


class DetailAppearanceTemplate : public AppearanceTemplate {
	AppearanceTemplate* firstMesh;
	
public:
	DetailAppearanceTemplate() {
		firstMesh = NULL;
	}
	
	~DetailAppearanceTemplate() {
	}
	
	void readObject(IffStream* templateData) {
		if(templateData->getFileName() == "appearance/mun_nboo_garage_s01_u01.apt")
			parse(templateData);
		else
			parse(templateData);
	}
	
	void parse(IffStream* iffStream);
	
	AppearanceTemplate* getFirstMesh() {
		return this;
	}
	
	osg::ref_ptr<osg::Node> draw();
};

#endif /* DETAILAPPEARANCETEMPLATE_H_ */
