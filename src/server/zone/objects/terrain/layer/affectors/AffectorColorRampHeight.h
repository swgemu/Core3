/*
 * AffectorColorRampHeight.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORCOLORRAMPHEIGHT_H_
#define AFFECTORCOLORRAMPHEIGHT_H_

#include "../ProceduralRule.h"

class AffectorColorRampHeight : public ProceduralRule<'ACRH'> {
	int var1;
	float var2;
	float var3;

	String var4;

public:
	AffectorColorRampHeight() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown AffectorColorRampHeight version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();
		var2 = iffStream->getFloat();
		var3 = iffStream->getFloat();

		iffStream->getString(var4);

		iffStream->closeChunk('DATA');
	}
};

#endif /* AFFECTORCOLORRAMPHEIGHT_H_ */
