/*
 * Road.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef ROAD_H_
#define ROAD_H_


#include "../TemplateVariable.h"
#include "Segment.h"

class Road : public TemplateVariable<'ROAD'> {
	Vector<Segment*> sgmts;

public:
	Road() : IffTemplateVariable() {

	}

	~Road() {
		for (int i = 0; i < sgmts.size(); ++i)
			delete sgmts.get(i);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0001':
			parseFromIffStream(iffStream, Version<'0001'>());
			break;
		default:
			System::out << "unknown Road version " << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
		int number = iffStream->getSubChunksNumber();

		for (int i = 0; i < number; i++) {
			Segment* sgmt = new Segment();
			sgmt->readObject(iffStream);

			sgmts.add(sgmt);
		}
	}
};


#endif /* ROAD_H_ */
