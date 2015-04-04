/*
 * AffectorColorConstant.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORCOLORCONSTANT_H_
#define AFFECTORCOLORCONSTANT_H_

#include "../ProceduralRule.h"
#include "AffectorProceduralRule.h"

class AffectorColorConstant : public ProceduralRule<'ACCN'>, public AffectorProceduralRule {
	int id; // never tested
	byte r;
	byte g;
	byte b;

public:
	AffectorColorConstant() : id(0), r(0), g(0), b(0) {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown AffectorColorConstant version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		id = iffStream->getInt();
		r = iffStream->getByte();
		g = iffStream->getByte();
		b = iffStream->getByte();

		iffStream->closeChunk('DATA');
	}
};


#endif /* AFFECTORCOLORCONSTANT_H_ */
