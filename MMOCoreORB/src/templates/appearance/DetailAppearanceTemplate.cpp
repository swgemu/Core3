
/*
 * DetailAppearanceTemplate.cpp
 *
 *  Created on: 10/12/2010
 *      Author: victor
 */

#include "DetailAppearanceTemplate.h"
#include "templates/manager/TemplateManager.h"

void DetailAppearanceTemplate::parse(IffStream* iffStream) {
	iffStream->openForm('DTLA');

	uint32 version = iffStream->getNextFormType();
	iffStream->openForm(version);

	AppearanceTemplate::readObject(iffStream);

	//if (iffStream->getNextFormType() == 'PIVT') {

	if (version != '0005') {
		iffStream->openChunk('PIVT');
		iffStream->closeChunk('PIVT');
	}
	//}

	Chunk* infoChunk = iffStream->openChunk('INFO');
	
	iffStream->closeChunk('INFO');

	Chunk* dataChunk = iffStream->openForm('DATA');

	int subChunks = dataChunk->getChunksSize();

	//loading last child only
	for (int i = 0; i < subChunks; ++i) {
		iffStream->openChunk('CHLD');

		int var1 = iffStream->getInt();

		String meshFile;
		iffStream->getString(meshFile);

		if (i == subChunks - 1) {
			AppearanceTemplate* templ = TemplateManager::instance()->getAppearanceTemplate("appearance/" + meshFile);
			firstMesh = templ;
		}

		iffStream->closeChunk('CHLD');
	}

	iffStream->closeForm('DATA');

	iffStream->closeForm(version);
	iffStream->closeForm('DTLA');
}
