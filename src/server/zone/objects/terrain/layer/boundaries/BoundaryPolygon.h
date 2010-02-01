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
	int var2;
	float var3;
	int localWaterTableEnabled;
	float localWaterTableHeight;
	float var6;
	String name;
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

	bool containsPoint(float x, float y) {
		int nvert = vertices.size();

		int i, j;
		bool c = false;

		for (i = 0, j = nvert-1; i < nvert; j = i++) {
			if ( ((vertices.get(i)->getY() > y) != (vertices.get(j)->getY() > y)) &&
					(x < (vertices.get(i)->getX() - vertices.get(i)->getX()) * (y - vertices.get(i)->getY()) / (vertices.get(j)->getY() - vertices.get(i)->getY()) + vertices.get(i)->getX()) )
				c = !c;
		}

		return c;
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

		var2 = iffStream->getInt();
		var3 = iffStream->getFloat();
		localWaterTableEnabled = iffStream->getInt(); // local water table enabled?
		localWaterTableHeight = iffStream->getFloat(); // water height
		var6 = iffStream->getFloat();
		iffStream->getString(name);

		iffStream->closeChunk('DATA');
	}

	float getLocalWaterTableHeight() {
		return localWaterTableHeight;
	}
};



#endif /* BOUNDARYPOLYGON_H_ */
