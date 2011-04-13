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

class AppearanceTemplate/* : public IffTemplate*/ {
public:
	virtual void readObject(IffStream* iffStream) {
		iffStream->openForm('APPR');
		//ignoring this atm
		iffStream->closeForm('APPR');
	}

	//void readObject(IffStream* templateData) = 0;

	virtual AppearanceTemplate* getFirstMesh() {
		return NULL;
	}
};

#endif /* APPEARANCETEMPLATE_H_ */
