/*
 * AffectorRadialConstant.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORRADIALCONSTANT_H_
#define AFFECTORRADIALCONSTANT_H_

#include "../ProceduralRule.h"

class AffectorRadialConstant : public ProceduralRule<'AFDN'> {
	int var1;
	int var2;
	int var3;
	int var4;
	float var5;

public:
	AffectorRadialConstant() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0002':
			parseFromIffStream(iffStream, Version<'0002'>());
			break;
		default:
			System::out << "unknown AffectorRadialConstant version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0002'>) {
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



#endif /* AFFECTORRADIALCONSTANT_H_ */
