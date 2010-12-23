/*
 * BoundaryPolygon.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef BOUNDARYPOLYGON_H_
#define BOUNDARYPOLYGON_H_


#include "../ProceduralRule.h"
#include "../affectors/AffectorRiver.h"
#include "Boundary.h"
#include "../../ProceduralTerrainAppearance.h"


class BoundaryPolygon : public ProceduralRule<'BPOL'>,  public Boundary {
	Vector<Point2D*> vertices;
	int localWaterTableEnabled;
	float localWaterTableHeight;
	float shaderSize;
	String shaderName;

	float minX, minY, maxX, maxY;

public:
	BoundaryPolygon() {
		ruleType = BOUNDARYPOLYGON;

		minX = 800000000;
		minY = 800000000;

		maxX = -80000000;
		minX = -80000000;
	}

	~BoundaryPolygon() {
		for (int i = 0; i < vertices.size(); ++i)
			delete vertices.get(i);
	}

	void executeRule(ProceduralTerrainAppearance* generator) {
		if (localWaterTableEnabled != 0)
			generator->insertWaterBoundary(this);
	}

	void initialize() {
		for(int i = 0; i < vertices.size(); ++i) {
			const Point2D* point = vertices.get(i);

			if (point->x < minX)
				minX = point->x;

			if (point->y < minY)
				minY = point->y;

			if (point->x > maxX)
				maxX = point->x;

			if (point->y > maxY)
				maxY = point->y;
		}
	}

	float process(float x, float y) {
		Point2D* lastPoint = NULL;

		float result = 0;

		if (x < minX)
			return 0.0;

		if (x > maxX || y < minY)
			return 0.0;

		if (y > maxY)
			return 0.0;

		if (vertices.size() <= 0)
			return 0.0;

		bool v50 = 0;

		lastPoint = vertices.get(vertices.size() - 1);

		for (int i = 0; i < vertices.size(); ++i) {
			Point2D* point = vertices.get(i);

			if ((point->y <= y && y < lastPoint->y) || (lastPoint->y <= y && y < point->y)) {
				if ( (y - point->y) * (lastPoint->x - point->x) / (lastPoint->y - point->y)
						+ point->x > (double)x ) {

					v50 = v50 == 0;

				}
			}

			lastPoint = point;
		}


		double v25, v43;

		if (v50) {
			if (featheringAmount == 0.0)
				return 1.0;

			v25 = featheringAmount * featheringAmount;
			v43 = v25;
			double v27, v26, v28;

			for (int i = 0; i < vertices.size(); ++i) {
				Point2D* point = vertices.get(i);

				v27 = y - point->y;
				v26 = v27 * v27 + (x - point->x) * (x - point->x);

				if ( v26 < v25 ) {
					v28 = v26;
					v25 = v28;
				}

			}

			double v35, v36, v44, v45, v37, v38, v39, v40, v41;

			lastPoint = vertices.get(vertices.size() - 1);

			for (int i = 0; i < vertices.size(); ++i) {
				Point2D* point = vertices.get(i);

				v35 = lastPoint->x - point->x;
				v36 = lastPoint->y - point->y;
				v44 = point->y - lastPoint->y;
				v45 = point->x - lastPoint->x;
				v37 = ((x - lastPoint->x) * v45 + (y - lastPoint->y) * v44) / (v36 * v36 + v35 * v35);
				if ( v37 >= 0.0 ) {
					if ( v37 <= 1.0 ) {
						v39 = x - (v45 * v37 + lastPoint->x);
						v40 = y - (v44 * v37 + lastPoint->y);
						v38 = v40 * v40 + v39 * v39;
						if ( v38 < v25 ) {
							v41 = v38;
							v25 = v41;
						}
					}
				}

				lastPoint = point;
			}

			if ( v25 >= v43 - 0.00009999999747378752 && v25 <= v43 + 0.00009999999747378752 )
				result = 1.0;
			else
				result = sqrt(v25) / featheringAmount;
		} else {
			result = 0.0;
		}

		return result;
	}

	bool containsPoint(float px, float py) {
		//System::out << "checking in polygon if contains point with vertices.size(): " << vertices.size() << endl;

		/*int nvert = vertices.size();

		int i, j;
		bool c = false;

		for (i = 0, j = nvert-1; i < nvert; j = i++) {
			if ( ((vertices.get(i)->getY() > y) != (vertices.get(j)->getY() > y)) &&
					(x < (vertices.get(i)->getX() - vertices.get(i)->getX()) * (y - vertices.get(i)->getY()) / (vertices.get(j)->getY() - vertices.get(i)->getY()) + vertices.get(i)->getX()) )
				c = !c;
		}

		return c;*/

		/* The points creating the polygon. */

		float x1,x2;

		/* The coordinates of the point */

		/* How many times the ray crosses a line-segment */
		int crossings = 0;

		/* Coordinates of the points */

		/* Iterate through each line */
		for ( int i = 0; i < vertices.size(); ++i ){

			/* This is done to ensure that we get the same result when
			   the line goes from left to right and right to left */
			if ( vertices.get(i)->getX() < vertices.get((i+1) % vertices.size())->getX()){
				x1 = vertices.get(i)->getX();
				x2 = vertices.get((i+1) % vertices.size())->getX();
			} else {
				x1 = vertices.get((i+1) % vertices.size())->getX();
				x2 = vertices.get(i)->getX();
			}

			/* First check if the ray is possible to cross the line */
			if ( px > x1 && px <= x2 && ( py < vertices.get(i)->getY() || py <= vertices.get((i+1) % vertices.size())->getY() ) ) {
				static const float eps = 0.000001;

				/* Calculate the equation of the line */
				float dx = vertices.get((i+1) % vertices.size())->getX() - vertices.get(i)->getX();
				float dy = vertices.get((i+1) % vertices.size())->getY() - vertices.get(i)->getY();
				float k;

				if ( fabs(dx) < eps ){
					k = INFINITY;	// math.h
				} else {
					k = dy/dx;
				}

				float m = vertices.get(i)->getY() - k * vertices.get(i)->getX();

				/* Find if the ray crosses the line */
				float y2 = k * px + m;
				if ( py <= y2 ){
					crossings++;
				}
			}
		}

		//printf("The point is crossing %d lines", crossings);
		if ( crossings % 2 == 1 )
			return true;

		return false;
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0005':
			parseFromIffStream(iffStream, Version<'0005'>());
			break;
		default:
			System::out << "unknown BoundaryPolygon version 0x" << hex << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0005'>) {
		informationHeader.readObject(iffStream);

		iffStream->openChunk('DATA');

		int var1 = iffStream->getInt();//count

		for (int i = 0; i < var1; i++) {
			Point2D* point = new Point2D();
			point->x = iffStream->getFloat();
			point->y = iffStream->getFloat();

			vertices.add(point);
		}

		featheringType = iffStream->getInt();
		featheringAmount = iffStream->getFloat();
		localWaterTableEnabled = iffStream->getInt(); // local water table enabled?
		localWaterTableHeight = iffStream->getFloat(); // water height
		shaderSize = iffStream->getFloat();
		iffStream->getString(shaderName);

		iffStream->closeChunk('DATA');

		initialize();
	}

	float getLocalWaterTableHeight() {
		return localWaterTableHeight;
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};



#endif /* BOUNDARYPOLYGON_H_ */
