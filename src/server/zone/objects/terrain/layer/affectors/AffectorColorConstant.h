/*
 * AffectorColorConstant.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORCOLORCONSTANT_H_
#define AFFECTORCOLORCONSTANT_H_

#include "../ProceduralRule.h"

class AffectorColorConstant : public ProceduralRule<'ACCN'> {
	int var1;
	byte var2;
	byte var3;
	byte var4;

public:
	AffectorColorConstant() {

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

		var1 = iffStream->getInt();
		var2 = iffStream->getByte();
		var3 = iffStream->getByte();
		var4 = iffStream->getByte();

		iffStream->closeChunk('DATA');
	}
};


#endif /* AFFECTORCOLORCONSTANT_H_ */
