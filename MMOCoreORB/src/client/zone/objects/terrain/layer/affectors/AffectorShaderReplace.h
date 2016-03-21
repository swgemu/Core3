/*
 * AffectorShaderReplace.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef AFFECTORSHADERREPLACE_H_
#define AFFECTORSHADERREPLACE_H_



#include "../ProceduralRule.h"

class AffectorShaderReplace : public ProceduralRule<'ASRP'>, public AffectorProceduralRule {
	int oldShaderId;
	int newShaderId;
	int featheringType;
	float featheringAmount;

public:
	AffectorShaderReplace() : oldShaderId(0), newShaderId(0), featheringType(0), featheringAmount(0) {

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

		oldShaderId = iffStream->getInt();
		newShaderId = iffStream->getInt();
		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};


#endif /* AFFECTORSHADERREPLACE_H_ */
