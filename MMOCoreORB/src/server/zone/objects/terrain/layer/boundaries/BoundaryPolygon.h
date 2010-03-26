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
	int featheringType;
	float featheringAmount;
	int localWaterTableEnabled;
	float localWaterTableHeight;
	float shaderSize;
	String shaderName;
public:
	BoundaryPolygon() {
		ruleType = BOUNDARYPOLYGON;
	}

	~BoundaryPolygon() {
		for (int i = 0; i < vertices.size(); ++i)
			delete vertices.get(i);
	}

	void executeRule(ProceduralTerrainAppearance* generator) {
		if (localWaterTableEnabled != 0)
			generator->insertWaterBoundary(this);
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
	}

	float getLocalWaterTableHeight() {
		return localWaterTableHeight;
	}
};



#endif /* BOUNDARYPOLYGON_H_ */
