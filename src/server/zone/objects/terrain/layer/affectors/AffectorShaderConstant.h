/*
 * AffectorShaderConstant.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef AFFECTORSHADERCONSTANT_H_
#define AFFECTORSHADERCONSTANT_H_


#include "../ProceduralRule.h"

class AffectorShaderConstant : public ProceduralRule<'ASCN'>, public AffectorProceduralRule {
	int familyId; // shader family id to affect
	int featheringType;
	float featheringAmount; // how much to soften

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

		familyId = iffStream->getInt();
		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};

#endif /* AFFECTORSHADERCONSTANT_H_ */
