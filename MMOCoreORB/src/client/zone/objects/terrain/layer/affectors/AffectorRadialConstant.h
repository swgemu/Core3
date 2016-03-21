/*
 * AffectorRadialConstant.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORRADIALCONSTANT_H_
#define AFFECTORRADIALCONSTANT_H_

#include "../ProceduralRule.h"

class AffectorRadialConstant : public ProceduralRule<'AFDN'>, public AffectorProceduralRule {
	int familyId;
	int var2;
	int flag; // add/remove
	int featheringType;
	float featheringAmount;

public:
	AffectorRadialConstant() : familyId(0), var2(0), flag(0), featheringType(0), featheringAmount(0) {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0002':
			parseFromIffStream(iffStream, Version<'0002'>());
			break;
		default:
			System::out << "unknown AffectorRadialConstant version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0002'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		familyId = iffStream->getInt();
		var2 = iffStream->getInt();
		flag = iffStream->getInt();
		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};



#endif /* AFFECTORRADIALCONSTANT_H_ */
