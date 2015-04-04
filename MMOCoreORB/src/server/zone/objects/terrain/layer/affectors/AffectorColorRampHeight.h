/*
 * AffectorColorRampHeight.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORCOLORRAMPHEIGHT_H_
#define AFFECTORCOLORRAMPHEIGHT_H_

#include "../ProceduralRule.h"

class AffectorColorRampHeight : public ProceduralRule<'ACRH'>, public AffectorProceduralRule {
	int familyId;
	float min;
	float max;

	String shaderFile; //.tga

public:
	AffectorColorRampHeight() : familyId(0), min(0), max(0) {

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

		familyId = iffStream->getInt();
		min = iffStream->getFloat();
		max = iffStream->getFloat();

		iffStream->getString(shaderFile);

		iffStream->closeChunk('DATA');
	}
};

#endif /* AFFECTORCOLORRAMPHEIGHT_H_ */
