/*
 * AffectorRoad.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef AFFECTORROAD_H_
#define AFFECTORROAD_H_


#include "../ProceduralRule.h"
#include "../Road.h"
#include "../Hdta.h"
#include "AffectorRiver.h"

class AffectorRoad : public ProceduralRule<'AROA'>, public AffectorProceduralRule {
	Road road;
	Hdta hdta;

	int var1;

	Vector<Point2D*> positions;

	float var2;
	int var3;
	int featheringType;
	float featheringAmount;
	int var6;
	float var7;

public:
	AffectorRoad() : var1(0), var2(0), var3(0), featheringType(0), featheringAmount(0), var6(0), var7(0) {

	}

	~AffectorRoad() {
		for (int i = 0; i < positions.size(); ++i)
			delete positions.get(i);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0005':
			parseFromIffStream(iffStream, Version<'0005'>());
			break;
		default:
			System::out << "unknown AffectorRoad version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0005'>) {
		informationHeader.readObject(iffStream);

		iffStream->openForm('DATA');

		uint32 type = iffStream->getNextFormType();

		switch (type) {
		case ('ROAD'):
			road.readObject(iffStream);
			break;
		case ('HDTA'):
			hdta.readObject(iffStream);
			break;
		default:
			System::out << "Unknown type in AffectorRoad, expecting ROAD or HDTA!\n";
			break;
		}

		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();

		for (int i = 0; i < var1; i++) {
			Point2D* pos = new Point2D();
			pos->x = iffStream->getFloat();
			pos->y = iffStream->getFloat();

			positions.add(pos);
		}

		var2 = iffStream->getFloat();
		var3 = iffStream->getInt();
		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();
		var6 = iffStream->getInt();
		var7 = iffStream->getFloat();

		iffStream->closeChunk('DATA');

		iffStream->closeForm('DATA');
	}
};

#endif /* AFFECTORROAD_H_ */
