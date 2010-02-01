/*
 * AffectorShaderConstant.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef AFFECTORSHADERCONSTANT_H_
#define AFFECTORSHADERCONSTANT_H_


#include "../ProceduralRule.h"

class AffectorShaderConstant : public ProceduralRule<'ASCN'> {
	int var1, var2;
	float var3;

public:
	AffectorShaderConstant() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0001':
			parseFromIffStream(iffStream, Version<'0001'>());
			break;
		default:
			System::out << "unknown AffectorShaderConstant version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();
		var2 = iffStream->getInt();
		var3 = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};

#endif /* AFFECTORSHADERCONSTANT_H_ */
