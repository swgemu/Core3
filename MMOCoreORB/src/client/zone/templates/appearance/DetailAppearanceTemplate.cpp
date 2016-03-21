/*
 * DetailAppearanceTemplate.cpp
 *
 *  Created on: 10/12/2010
 *      Author: victor
 */

#include "DetailAppearanceTemplate.h"
#include "zone/managers/templates/TemplateManager.h"
#include "zone/templates/appearance/FloorMesh.h"
osg::ref_ptr<osg::Node> DetailAppearanceTemplate::draw() {
	osg::ref_ptr<osg::Group> group(new osg::Group);
	
	if(floorName.isEmpty() == false) {
		FloorMesh *floor = TemplateManager::instance()->getFloorMesh(floorName);
		if(floor == NULL) {
			static Logger logger;
			logger.error("Invalid floor mesh in detail appearance template: " + floorName);
			
		} else {
			group->addChild(floor->draw());
		}
		
	}
	//group->addChild(AppearanceTemplate::draw());
//	if(collisionVolume != NULL)
//		group->addChild(collisionVolume->draw());
//	else if(volume != NULL)
//		group->addChild(volume->draw());
//	else
		group->addChild(firstMesh->draw());
	
	return group;
}

void DetailAppearanceTemplate::parse(IffStream* iffStream) {
	
	String templateName = iffStream->getFileName();
//	
//	floorName = templateName.subString(templateName.lastIndexOf('/'));
//	floorName = floorName.subString(0, floorName.lastIndexOf('.'));
//	
//	floorName = "appearance/collision" + floorName + "_collision_floor.flr";
//	FloorMesh *floor = TemplateManager::instance()->getFloorMesh(floorName);
//	if(floor == NULL)
	floorName = "";
	
	iffStream->openForm('DTLA');

	uint32 version = iffStream->getNextFormType();
	iffStream->openForm(version);
	
	uint32 fuckOff = 1;
	if(iffStream->getFileName() == "appearance/mun_nboo_garage_s01_u01.apt")
		fuckOff = 57;

	AppearanceTemplate::readObject(iffStream);

	//if (iffStream->getNextFormType() == 'PIVT') {
	
	if (version != '0005') {
		iffStream->openChunk('PIVT');
		iffStream->closeChunk('PIVT');
	}
	//}

	Chunk* infoChunk = iffStream->openChunk('INFO');

	/*                int totalINFOSize = infoChunk->getDataSize();

        for (int i = 0; i < totalINFOSize; i += 12) {
            int var1 = iffStream->getInt();
            float var2 = iffStream->getFloat();
            float var3 = iffStream->getFloat();
        }
	 */
	iffStream->closeChunk('INFO');

	Chunk* dataChunk = iffStream->openForm('DATA');

	int subChunks = dataChunk->getChunksSize();

	//loading first child only
	for (int i = 0; i < subChunks-1; ++i) {
		iffStream->openChunk('CHLD');
		iffStream->closeChunk('CHLD');
	}
	
	iffStream->openChunk('CHLD');
	
	int var1 = iffStream->getInt();
	
	String meshFile;
	iffStream->getString(meshFile);
	
	AppearanceTemplate* templ = TemplateManager::instance()->getAppearanceTemplate("appearance/" + meshFile);
	
	if(firstMesh == NULL)
		firstMesh = templ;
	
	iffStream->closeChunk('CHLD');

	iffStream->closeForm('DATA');

	iffStream->closeForm(version);
	iffStream->closeForm('DTLA');
}
