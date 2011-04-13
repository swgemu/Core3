/*
 * RadialGroup.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef RADIALGROUP_H_
#define RADIALGROUP_H_


#include "TemplateVariable.h"
#include "RadialFamily.h"

class RadialGroup : public TemplateVariable<'RGRP'> {
	Vector<RadialFamily*> data;
public:

	~RadialGroup() {
		while (data.size() > 0)
			delete data.remove(0);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0003':
			parseFromIffStream(iffStream, Version<'0003'>());
			break;
		default:
			System::out << "unknown RGRP version " << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0003'>) {
		int number = iffStream->getSubChunksNumber();

		for (int i = 0; i < number; ++i) {
			RadialFamily* ffam = new RadialFamily();
			ffam->readObject(iffStream);

			data.add(ffam);
		}
	}

};



#endif /* RADIALGROUP_H_ */
