/*
 * AffectorPAS.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORPAS_H_
#define AFFECTORPAS_H_


#include "../ProceduralRule.h"

class AffectorPassable : public ProceduralRule<'APAS'>, public AffectorProceduralRule {
	float var1, var2;

public:
	AffectorPassable() : var1(0), var2(0) {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown AffectorPAS version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		var1 = iffStream->getByte();
		var2 = iffStream->getInt();

		iffStream->closeChunk('DATA');
	}
};



#endif /* AFFECTORPAS_H_ */
