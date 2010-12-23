/*
 * AffectorColorRampFractal.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORCOLORRAMPFRACTAL_H_
#define AFFECTORCOLORRAMPFRACTAL_H_

#include "../ProceduralRule.h"

class AffectorColorRampFractal : public ProceduralRule<'ACRF'>, public AffectorProceduralRule {
	int familyId; // fractal family id
	byte var2;
	String shaderFile; // .tga

public:
	AffectorColorRampFractal() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0001':
			parseFromIffStream(iffStream, Version<'0001'>());
			break;
		default:
			System::out << "unknown AffectorColorRampFractal version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
		informationHeader.readObject(iffStream);

		iffStream->openForm('DATA');

		iffStream->openChunk('PARM');

		familyId = iffStream->getInt();
		var2 = iffStream->getByte();

		iffStream->getString(shaderFile);

		iffStream->closeChunk('PARM');

		iffStream->closeForm('DATA');
	}
};




#endif /* AFFECTORCOLORRAMPFRACTAL_H_ */
