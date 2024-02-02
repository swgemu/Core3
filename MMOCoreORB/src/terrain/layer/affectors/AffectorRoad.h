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

// #define DEBUG_AFFECTOR_ROAD

class RoadRectangle {
	float lowerLeftX, lowerLeftY, upperRightX, upperRightY;
	float roadStartX, roadStartY, centerX, centerY;
	float width, height, direction;

public:
	RoadRectangle(float x0, float y0, float x1, float y1, float startX, float startY, float roadWidth, float dir) {
		lowerLeftX = x0;
		lowerLeftY = y0;
		upperRightX = x1;
		upperRightY = y1;
		roadStartX = startX;
		roadStartY = startY;
		direction = dir;

		centerX = ((lowerLeftX + upperRightX) / 2.f);
		centerY = ((lowerLeftY + upperRightY) / 2.f);

		width = roadWidth;
		height = Math::sqrt(Math::sqr(upperRightX - lowerLeftX) + Math::sqr(upperRightY - lowerLeftY));
	}

	~RoadRectangle() {
	}

	bool containsPoint(float x, float y) const {
#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "RoadRectangle::containsPoint - centerX: " << centerX << " centerY: " << centerY << " width: " << width << " height: " << height;
#endif

		float deltaX = centerX - x;
		float deltaY = centerY - y;

		float rotatedX = deltaX * Math::cos(-direction) + deltaY * Math::sin(-direction);
		float rotatedY = deltaX * Math::sin(-direction) - deltaY * Math::cos(-direction);

		bool result = (fabs(rotatedX) <= width / 2.f) && (fabs(rotatedY) <= height / 2.f);

#ifdef DEBUG_AFFECTOR_ROAD
		if (result)
			Logger::console.info(true) << "Rectangle Contains Point - Center X: " << centerX << " Center Y: " << centerY <<  " X: " << x << " Y: " << y << " rotatedX: " << rotatedX << " rotatedY: " << rotatedY;
#endif

		// Check if the point is inside the bounding box
		return result;
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

	float getRoadCenterX() {
		return centerX;
	}

	float getRoadCenterY() {
		return centerY;
	}

	float getDirection() {
		return direction;
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

	static const int OUT_OF_RANGE = 500;

public:
	AffectorRoad() : coordinateCount(0), width(0.f), familyID(0), featheringType(0), featheringAmount(0), featheringShader(0), featheringShaderDistance(0.5f) {
		affectorType = HEIGHTROAD;
	}

	~AffectorRoad() {
		for (int i = 0; i < midPositions.size(); ++i)
			delete midPositions.get(i);

		midPositions.removeAll();

		for (int i = 0; i < rectangles.size(); ++i)
			delete rectangles.get(i);

		rectangles.removeAll();
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
