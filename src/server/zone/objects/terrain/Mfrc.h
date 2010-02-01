/*
 * Mfrc.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef MFRC_H_
#define MFRC_H_

#include "TemplateVariable.h"

class Mfrc : public TemplateVariable<'MFRC'> {
	int var1;
	int var2;
	float var3;
	int var4;
	float var5;
	uint32 var6;
	float var7;
	float var8;
	float var9;
	float var10;
	uint32 var11;
	uint32 var12;
	uint32 var13;
public:
	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0001':
			parseFromIffStream(iffStream, Version<'0001'>());
			break;
		default:
			System::out << "unknown MFRC version " << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();
		var2 = iffStream->getInt();
		var3 = iffStream->getFloat();
		var4 = iffStream->getInt();
		var5 = iffStream->getFloat();
		var6 = iffStream->getUnsignedInt();
		var7 = iffStream->getFloat();
		var8 = iffStream->getFloat();
		var9 = iffStream->getFloat();
		var10 = iffStream->getFloat();
		var11 = iffStream->getUnsignedInt();
		var12 = iffStream->getUnsignedInt();
		var13 = iffStream->getUnsignedInt();

		iffStream->closeChunk('DATA');
	}
};


#endif /* MFRC_H_ */
