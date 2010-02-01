/*
 * FloraGroup.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef FLORAGROUP_H_
#define FLORAGROUP_H_


#include "TemplateVariable.h"

class FloraGroup : public TemplateVariable<'FGRP'> {

public:

	FloraGroup() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0008':
			parseFromIffStream(iffStream, Version<'0008'>());
			break;
		default:
			System::out << "unknown FGRP version 0x" << hex << version;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0008'>) {

	}
};


#endif /* FLORAGROUP_H_ */
