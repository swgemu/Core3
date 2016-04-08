/*
 * Hdta.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef HDTA_H_
#define HDTA_H_


#include "../TemplateVariable.h"
#include "Segment.h"

class Hdta : public TemplateVariable<'HDTA'> {
	Vector<Segment*> sgmts;


public:
	Hdta() : IffTemplateVariable() {

	}

	~Hdta() {
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



#endif /* HDTA_H_ */
