/*
 * AffectorNoncollideFloraConstant.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORNONCOLLIDEFLORACONSTANT_H_
#define AFFECTORNONCOLLIDEFLORACONSTANT_H_

#include "../ProceduralRule.h"

class AffectorNoncollideFloraConstant : public ProceduralRule<'AFSC'> {
	int var1;
	int var2;
	int var3;
	int var4;
	float var5;

public:
	AffectorNoncollideFloraConstant() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0004':
			parseFromIffStream(iffStream, Version<'0004'>());
			break;
		default:
			System::out << "unknown AffectorNoncollideFloraConstant version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0004'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();
		var2 = iffStream->getInt();
		var3 = iffStream->getInt();
		var4 = iffStream->getInt();
		var5 = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};


#endif /* AFFECTORNONCOLLIDEFLORACONSTANT_H_ */
