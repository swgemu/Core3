/*
 * FilterShader.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef FILTERSHADER_H_
#define FILTERSHADER_H_


#include "../ProceduralRule.h"
#include "FilterProceduralRule.h"

class FilterShader : public ProceduralRule<'FSHD'>, public FilterProceduralRule {
	int shaderId;

public:
	FilterShader() : FilterProceduralRule(4), shaderId(0) {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown FilterShader version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		shaderId = iffStream->getInt();

		iffStream->closeChunk('DATA');
	}
};

#endif /* FILTERSHADER_H_ */
