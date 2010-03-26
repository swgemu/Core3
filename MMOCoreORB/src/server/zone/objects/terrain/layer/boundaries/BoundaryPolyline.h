/*
 * BoundaryPolyline.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef BOUNDARYPOLYLINE_H_
#define BOUNDARYPOLYLINE_H_


#include "../ProceduralRule.h"
#include "../affectors/AffectorRiver.h"
#include "Boundary.h"

class BoundaryPolyline : public ProceduralRule<'BPLN'>,  public Boundary {
	Vector<Point2D*> points;
	int featheringType;
	float featheringAmount;
	float lineWidth;


public:
	BoundaryPolyline() {
		ruleType = BOUNDARYPOLYLINE;
	}

	~BoundaryPolyline() {
		for (int i = 0; i < points.size(); ++i)
			delete points.get(i);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0001':
			parseFromIffStream(iffStream, Version<'0001'>());
			break;
		default:
			System::out << "unknown BoundaryPolyline version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		int count = iffStream->getInt();

		for (int i = 0; i < count; ++i) {
			Point2D* point = new Point2D();
			point->x = iffStream->getFloat();
			point->y = iffStream->getFloat();

			points.add(point);
		}

		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();
		lineWidth = iffStream->getFloat();

		iffStream->closeForm('DATA');
	}
};



#endif /* BOUNDARYPOLYLINE_H_ */
