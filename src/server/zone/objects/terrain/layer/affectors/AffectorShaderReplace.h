/*
 * AffectorShaderReplace.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef AFFECTORSHADERREPLACE_H_
#define AFFECTORSHADERREPLACE_H_



#include "../ProceduralRule.h"

class AffectorShaderReplace : public ProceduralRule<'ASRP'> {
	int var1;
	int var2;
	int var3;
	float var4;

public:
	AffectorShaderReplace() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0001':
			parseFromIffStream(iffStream, Version<'0001'>());
			break;
		default:
			System::out << "unknown AffectorShaderReplace version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();
		var2 = iffStream->getInt();
		var3 = iffStream->getInt();
		var4 = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};


#endif /* AFFECTORSHADERREPLACE_H_ */
