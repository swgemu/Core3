/*
 * AffectorExclude.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTOREXCLUDE_H_
#define AFFECTOREXCLUDE_H_


#include "../ProceduralRule.h"

class AffectorExclude : public ProceduralRule<'AEXC'>, public AffectorProceduralRule {

public:
	AffectorExclude() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown AffectorExclude version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		iffStream->closeChunk('DATA');
	}
};




#endif /* AFFECTOREXCLUDE_H_ */
