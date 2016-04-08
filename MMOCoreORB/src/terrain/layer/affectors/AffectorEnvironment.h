/*
 * AffectorEnvironment.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORENVIRONMENT_H_
#define AFFECTORENVIRONMENT_H_

#include "../ProceduralRule.h"

class AffectorEnvironment : public ProceduralRule<'AENV'>, public AffectorProceduralRule {
	int environmentId;
	int var2;
	float weight;

public:
	AffectorEnvironment(): environmentId(0), var2(0), weight(0) {
		affectorType = ENVIRONMENT;
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown AffectorEnvironment version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		environmentId = iffStream->getInt();
		var2 = iffStream->getInt();
		weight = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}

	void process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator) {
		//System::out << "processing AffectorEnvironment value:" << environmentId << endl;
		baseValue = (float)environmentId;
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};



#endif /* AFFECTORENVIRONMENT_H_ */
