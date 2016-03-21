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
	AffectorShaderReplace() {
		affectorType = AffectorProceduralRule::SHADER;
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

	void process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator, TerrainChunk* chunk, int i, int j) {
		//System::out << "processing AffectorEnvironment value:" << environmentId << endl;
		if (transformValue == 0)
			return;

		if (baseValue == oldShaderId)
			baseValue = (float)newShaderId;


		if (chunk != NULL) {
			if (chunk->getShader(i, j) == oldShaderId)
				chunk->setShader(i, j, newShaderId);
		}
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};


#endif /* AFFECTORSHADERREPLACE_H_ */
