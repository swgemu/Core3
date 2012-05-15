/*
 * AffectorRiver.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef AFFECTORRIVER_H_
#define AFFECTORRIVER_H_

#include "../ProceduralRule.h"
#include "../Road.h"
#include "../Hdta.h"

class Point2D  {
public:
	float x, y;

	inline float getX() {
		return x;
	}

	inline float getY() {
		return y;
	}
};


class AffectorRiver : public ProceduralRule<'ARIV'>, public AffectorProceduralRule {
	Road road;
	Hdta hdta;

	int var1;

	Vector<Point2D*> positions;

	float var2;
	int var3;
	int var4;
	int var5;
	float var6;
	float var7;
	float var8;
	int var9;
	float var10;
	float var11;
	float var12;

	String var15;

public:
	AffectorRiver() {

	}

	~AffectorRiver() {
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
			System::out << "unknown AffectorRiver version 0x" << hex << version << endl;
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
			System::out << "Unknown type in AffectorRiver, expecting ROAD or HDTA!\n";
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
		var4 = iffStream->getInt();
		var5 = iffStream->getInt();
		var6 = iffStream->getFloat();
		var7 = iffStream->getFloat();
		var8 = iffStream->getFloat();
		var9 = iffStream->getInt();
		var10 = iffStream->getFloat();
		var11 = iffStream->getFloat();
		var12 = iffStream->getFloat();

		iffStream->getString(var15);

		iffStream->closeChunk('DATA');

		iffStream->closeForm('DATA');
	}
};


#endif /* AFFECTORRIVER_H_ */
