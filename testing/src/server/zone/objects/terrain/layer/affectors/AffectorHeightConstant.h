/*
 * AffectorHeightConstant.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORHEIGHTCONSTANT_H_
#define AFFECTORHEIGHTCONSTANT_H_


#include "../ProceduralRule.h"

class AffectorHeightConstant : public ProceduralRule<'AHCN'> {
	int var1; // id?
	float height;

public:
	AffectorHeightConstant() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown AffectorHeightConstant version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();
		height = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}
};




#endif /* AFFECTORHEIGHTCONSTANT_H_ */
