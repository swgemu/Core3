/*
 * MapGroup.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef MAPGROUP_H_
#define MAPGROUP_H_


class MapGroup : public TemplateVariable<'MGRP'> {

public:

	MapGroup() {

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



#endif /* MAPGROUP_H_ */
