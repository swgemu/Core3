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

class DetailAppearanceTemplate : public AppearanceTemplate {
	AppearanceTemplate* firstMesh;

public:
	DetailAppearanceTemplate() {
		firstMesh = NULL;
	}

	~DetailAppearanceTemplate() {
	}

	void readObject(IffStream* templateData) {
		parse(templateData);
	}

	void parse(IffStream* iffStream);

	AppearanceTemplate* getFirstMesh() {
		return firstMesh;
	}

};

#endif /* DETAILAPPEARANCETEMPLATE_H_ */
