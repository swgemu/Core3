/*
 * FIlterBIT.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef FILTERBIT_H_
#define FILTERBIT_H_


#include "../ProceduralRule.h"

#include "FilterProceduralRule.h"

class FilterBIT : public ProceduralRule<'FBIT'>, public FilterProceduralRule {
	int var1;
	int var2;
	float var3;
	float var4;
	float var5;

public:
	FilterBIT() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown FilterBIT version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openForm('DATA');

		iffStream->openChunk('PARM');

		//5 vars
		var1 = iffStream->getInt();
		var2 = iffStream->getInt();
		var3 = iffStream->getFloat();
		var4 = iffStream->getFloat();
		var5 = iffStream->getFloat();

		iffStream->closeChunk('PARM');

		iffStream->closeForm('DATA');
	}
};


#endif /* FILTERBIT_H_ */
