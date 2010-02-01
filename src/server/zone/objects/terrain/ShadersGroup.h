/*
 * SurfaceGroup.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef SHADERSGROUP_H_
#define SHADERSGROUP_H_

#include "TemplateVariable.h"

class ShadersGroup : public TemplateVariable<'SGRP'> {

public:

	ShadersGroup() {

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

#endif /* SURFACEGROUP_H_ */
