/*
 * RadialGroup.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef RADIALGROUP_H_
#define RADIALGROUP_H_


#include "TemplateVariable.h"

class RadialGroup : public TemplateVariable<'RGRP'> {

public:

	RadialGroup() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
		default:
			break;
		}
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {

	}

};



#endif /* RADIALGROUP_H_ */
