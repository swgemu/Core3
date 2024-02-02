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
#include "../HeightData.h"
#include "../boundaries/BoundaryRectangle.h"
#include "../../TerrainGenerator.h"
#include "AffectorRiver.h"

class TerrainGenerator;

#define DEBUG_AFFECTOR_ROAD

class RoadRectangle {
	float lowerLeftX, lowerLeftY, upperRightX, upperRightY;
	float roadStartX, roadStartY;

public:
	RoadRectangle(float x0, float y0, float x1, float y1, float startX, float startY) {
		lowerLeftX = x0;
		lowerLeftY = y0;
		upperRightX = x1;
		upperRightY = y1;
		roadStartX = startX;
		roadStartY = startY;
	}

	~RoadRectangle() {
	}

	bool containsPoint(float x, float y) const {
		// Some roads are turned, so the lower left corner and upper right are not always higher or lower then one another by given location
		float leastX = (lowerLeftX < upperRightX) ? lowerLeftX : upperRightX;
		float greatestX = (lowerLeftX > upperRightX) ? lowerLeftX : upperRightX;
		float leastY = (lowerLeftY < upperRightY) ? lowerLeftY : upperRightY;
		float greatestY = (lowerLeftY > upperRightY) ? lowerLeftY : upperRightY;

		return (x > leastX) && (x < greatestX) && (y > leastY) && (y < greatestY);
	}

	float getLowerLeftX() const {
		return lowerLeftX;
	}

	float getLowerLeftY() const {
		return lowerLeftY;
	}

	float getUpperRightX() const {
		return upperRightX;
	}

	float getUpperRightY() const {
		return upperRightY;
	}

	float getRoadStartX(){
		return roadStartX;
	}

	float getRoadStartY() {
		return roadStartY;
	}
};

class AffectorRoad : public ProceduralRule<'AROA'>, public AffectorProceduralRule {
	Road road;
	HeightData hdta;

	uint32 type;
	int coordinateCount;

	Point2D startPoint;
	Point2D endPoint;
	Vector<Point2D*> midPositions;

	Vector<RoadRectangle*> rectangles;

	float width;
	int familyID;

	int featheringType;
	float featheringAmount;
	int featheringShader;
	float featheringShaderDistance;

public:
	AffectorRoad() : coordinateCount(0), width(0.f), familyID(0), featheringType(0), featheringAmount(0), featheringShader(0), featheringShaderDistance(0.5f) {
		affectorType = HEIGHTROAD;
	}

	~AffectorRoad() {
		for (int i = 0; i < midPositions.size(); ++i)
			delete midPositions.get(i);

		midPositions.removeAll();
	}

	void process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator);

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0005'>);
	void addNewRectangle(float x1, float y1, float x2, float y2);
	void generateRectangles();
	void sendDebugMessage(String message);

	inline int getFamilyID() {
		return familyID;
	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};

#endif /* AFFECTORROAD_H_ */
