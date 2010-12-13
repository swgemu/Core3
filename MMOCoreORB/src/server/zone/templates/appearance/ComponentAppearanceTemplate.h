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
#include "server/zone/managers/templates/TemplateManager.h"

class ComponentAppearanceTemplate : public AppearanceTemplate {
	AppearanceTemplate* firstMesh;

public:
	ComponentAppearanceTemplate() {
		firstMesh = NULL;
	}

	~ComponentAppearanceTemplate() {
	}


	void readObject(IffStream* templateData) {
		parse(templateData);
	}

	void parse(IffStream* iffStream) {
		iffStream->openForm('CMPA');

		uint32 version = iffStream->getNextFormType();
		iffStream->openForm(version);

		AppearanceTemplate::readObject(iffStream);

		iffStream->openForm('RADR');
		iffStream->closeForm('RADR');

		int subChunks = iffStream->getRemainingSubChunksNumber();// dataChunk->getChunksSize();

		//loading first child only
		for (int i = 0; i < 1 /*subChunks*/; ++i) {
			iffStream->openChunk('PART');

			// int var1 = iffStream->getInt();

			/*QString str;
	                    iffStream->getString(str);*/

			String meshFile;
			iffStream->getString(meshFile);

			AppearanceTemplate* templ = TemplateManager::instance()->getAppearanceTemplate("appearance/" + meshFile);

			if (i == 0)
				firstMesh = templ->getFirstMesh();

			iffStream->closeChunk('PART');
		}

		iffStream->closeForm(version);
		iffStream->closeForm('CMPA');
	}

	AppearanceTemplate* getFirstMesh() {
		return firstMesh;
	}

};

#endif /* COMPONENTAPPEARANCETEMPLATE_H_ */
