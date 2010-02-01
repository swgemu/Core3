/*
 * FilterHeight.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef FILTERHEIGHT_H_
#define FILTERHEIGHT_H_


#include "../ProceduralRule.h"

class FilterHeight : public ProceduralRule<'FHGT'> {
	float var1;
	float var2;
	int var3;
	float var4;

public:
	FilterHeight() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0002':
			parseFromIffStream(iffStream, Version<'0002'>());
			break;
		default:
			System::out << "unknown FilterHeight version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0002'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		var1 = iffStream->getFloat();
		var2 = iffStream->getFloat();
		var3 = iffStream->getInt();
		var4 = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};

#endif /* FILTERHEIGHT_H_ */
