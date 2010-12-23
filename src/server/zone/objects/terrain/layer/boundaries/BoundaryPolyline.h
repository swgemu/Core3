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
	float lineWidth;

	float minX, minY, maxX, maxY;

public:
	BoundaryPolyline() {
		ruleType = BOUNDARYPOLYLINE;

		minX = 800000000;
		minY = 800000000;

		maxX = -80000000;
		minX = -80000000;
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

		initialize();
	}

	void initialize() {
		for(int i = 0; i < points.size(); ++i) {
			Point2D* point = points.get(i);

			if (point->x < minX)
				minX = point->x;

			if (point->y < minY)
				minY = point->y;

			if (point->x > maxX)
				maxX = point->x;

			if (point->y > maxY)
				maxY = point->y;
		}

		minX = minX - lineWidth;
		maxX = maxX + lineWidth;
		minY = minY - lineWidth;
		maxY = maxY + lineWidth;
	}

	float process(float x, float y) {
		if (x < minX)
			return 0.0;

		if (x > maxX || y < (double)minY )
			return 0.0;

		if ( y > maxY )
			return 0.0;

		double v16 = lineWidth * lineWidth;
		double v21 = 0;

		double v31 = v16;
		double v20, v19;

		double result = 0;

		for (int i = 0; i < points.size(); ++i) {
			Point2D* point = points.get(i);

			v20 = y - point->y;
			v19 = v20 * v20 + (x - point->x) * (x - point->x);
			if ( v19 < v16 ) {
				v21 = v19;
				v16 = v21;
			}
		}

		double v33, v35, v36, v26, v27, v25, v24, v28;

		for (int i = 0; i < points.size() - 1; ++i) {
			const Point2D* point = points.get(i);
			const Point2D* point2 = points.get(i + 1);

			v35 = point2->x - point->x;
			v24 = point2->y - point->y;
			v33 = v24;
			v36 = ((y -  point->y) * v33 + (x - point->x) * v35) / (v24 * v24 + v35 * v35);

			if ( v36 >= 0.0 ) {
				if ( v36 <= 1.0 ) {
					v26 = x - (v35 * v36 + point->x);
					v27 = y - (v33 * v36 +  point->y);
					v25 = v27 * v27 + v26 * v26;

					if ( v25 < v16 ) {
						v28 = v25;
						v16 = v28;
					}
				}
			}

		}

		if ( v16 >= v31 )
			return 0.0;

		double v29 = (1.0 - featheringAmount) * lineWidth;

		if ( v16 >= v29 * v29 )
			result = 1.0 - (sqrt(v16) - v29) / (lineWidth - v29);
		else
			result = 1.0;

		return result;
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};



#endif /* BOUNDARYPOLYLINE_H_ */
