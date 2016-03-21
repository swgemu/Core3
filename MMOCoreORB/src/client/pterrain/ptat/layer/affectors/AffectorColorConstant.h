/*
 * AffectorColorConstant.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORCOLORCONSTANT_H_
#define AFFECTORCOLORCONSTANT_H_

#include "../ProceduralRule.h"
#include "AffectorProceduralRule.h"

class AffectorColorConstant : public ProceduralRule<'ACCN'>, public AffectorProceduralRule {
	int id; // never tested
	byte r;
	byte g;
	byte b;

public:
	AffectorColorConstant() {
		affectorType = AffectorProceduralRule::COLOR;
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0000':
			parseFromIffStream(iffStream, Version<'0000'>());
			break;
		default:
			System::out << "unknown AffectorColorConstant version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		id = iffStream->getInt();
		r = iffStream->getByte();
		g = iffStream->getByte();
		b = iffStream->getByte();

		iffStream->closeChunk('DATA');
	}

	void process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator, TerrainChunk* chunk, int i, int j) {
		if (transformValue == 0)
			return;

		unsigned int color = 0;

		color += 255;
		color = color << 8;

		color &= 0xFFFFFF00;

		color += r;
		color = color << 8;

		color &= 0xFFFFFF00;

		color += g;
		color = color << 8;

		color &= 0xFFFFFF00;

		color += b;
		//color = color << 8;


		/*
		color += r;
		color = color << 8;

		color += g;
		color = color << 8;

		color += b;
		color = color << 8;

		color += 255; //alpha
		*/

		baseValue = (float) color;


		if (chunk != NULL) {
			chunk->setColor(j, i, color);
		}
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};


#endif /* AFFECTORCOLORCONSTANT_H_ */
