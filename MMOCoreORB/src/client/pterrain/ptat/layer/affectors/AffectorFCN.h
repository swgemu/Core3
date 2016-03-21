/*
 * AffectorFCN.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORFCN_H_
#define AFFECTORFCN_H_

#include "../ProceduralRule.h"

class AffectorFCN : public ProceduralRule<'AFCN'>, public AffectorProceduralRule {
	int familyId;
	int var2;
	int flag; //add/remove
	int featheringType;
	float featheringAmount;

public:
	AffectorFCN() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0004':
			parseFromIffStream(iffStream, Version<'0004'>());
			break;
		default:
			System::out << "unknown AffectorFCN version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0004'>) {
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

#endif /* AFFECTORFCN_H_ */
