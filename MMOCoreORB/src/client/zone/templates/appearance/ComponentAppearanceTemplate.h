/*
 * ComponentAppearanceTemplate.h
 *
 *  Created on: 10/12/2010
 *      Author: victor
 */

#ifndef COMPONENTAPPEARANCETEMPLATE_H_
#define COMPONENTAPPEARANCETEMPLATE_H_

#include "engine/engine.h"
#include "AppearanceTemplate.h"
#include "zone/managers/templates/TemplateManager.h"
#include <osg/Node>
#include <osg/Geometry>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>


class ComponentAppearanceTemplate : public AppearanceTemplate {

	Vector<Matrix4> transforms;
	Vector<AppearanceTemplate*> meshes;

public:
	ComponentAppearanceTemplate() {
	}

	~ComponentAppearanceTemplate() {
	}
	
	osg::ref_ptr<osg::Node> draw() {
		//info("Drawing ComponentAppearanceTemplate " + TemplateManager::instance()->getAppearanceTemplateString(this), true);
		osg::Group* group = new osg::Group();
		
		for(int i=0; i<meshes.size(); i++) {
			osg::MatrixTransform * transform  = new osg::MatrixTransform( );
			
			Matrix4 ourTransform = transforms.get(i);
			osg::Matrix matrix(ourTransform[0][0], ourTransform[0][1], ourTransform[0][2], ourTransform[0][3],
							   ourTransform[1][0], ourTransform[1][1], ourTransform[1][2], ourTransform[1][3],
							   ourTransform[2][0], ourTransform[2][1], ourTransform[2][2], ourTransform[2][3],
							   0, 0, 0, 1);
			
			
			transform->setMatrix( matrix );
			
			transform->addChild(meshes.get(i)->draw());
			
			group->addChild(transform);

		}
		
		return group;

	}


	void readObject(IffStream* templateData) {
		parse(templateData);
	}

	void parse(IffStream* iffStream) {
		iffStream->openForm('CMPA');

		uint32 version = iffStream->getNextFormType();
		
		
		if(iffStream->getFileName().contains("mun_nboo_garage"))
		   version = version;
		   
		iffStream->openForm(version);

		AppearanceTemplate::readObject(iffStream);

		if(iffStream->getNextFormType() == 'RADR') {
			iffStream->openForm('RADR');
			iffStream->closeForm('RADR');
		}

		int subChunks = iffStream->getRemainingSubChunksNumber();// dataChunk->getChunksSize();

		//loading first child only
		for (int i = 0; i < subChunks; ++i) {
			
//			if(iffStream->getNextFormType() != 'PART') {
//				//info("Unknown chunk type " + iffStream->getNextFormType(), true);
//				iffStream->openChunk();
//				iffStream->closeChunk();
//				continue;
//			}
			
			Chunk *chunk = iffStream->openChunk();
			if(chunk->getChunkID() != 'PART') {
				iffStream->closeChunk();
				static Logger logger;
				logger.info("Skipping ComponentAppearance Chunk Type " + String::valueOf(chunk->getChunkID()), true);
				continue;
			}

			// int var1 = iffStream->getInt();

			/*QString str;
	                    iffStream->getString(str);*/

			String meshFile;
			iffStream->getString(meshFile);

			AppearanceTemplate* tmpl = TemplateManager::instance()->getAppearanceTemplate("appearance/" + meshFile);
			
			Matrix4 mat;
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 4; y++)
				{
					mat[x][y] = iffStream->getFloat();
				}
			}

			if(tmpl != NULL) {
				transforms.add(mat);
				meshes.add(tmpl);
			}
			
			iffStream->closeChunk();
		}

		iffStream->closeForm(version);
		iffStream->closeForm('CMPA');
	}

	AppearanceTemplate* getMesh(int index) {
		return meshes.get(index);
	}
	
	int getNumMeshes() {
		return meshes.size();
	}
	
	Matrix4 getTransform(int index) {
		transforms.get(index);
	}

};

#endif /* COMPONENTAPPEARANCETEMPLATE_H_ */
