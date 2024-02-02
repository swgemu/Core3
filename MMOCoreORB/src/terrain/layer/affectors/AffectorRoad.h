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
#include "../boundaries/BoundaryRectangle.h"
#include "../../TerrainGenerator.h"
#include "AffectorRiver.h"

class TerrainGenerator;

#define DEBUG_AFFECTOR_ROAD

class AffectorRoad : public ProceduralRule<'AROA'>, public AffectorProceduralRule {
	Road road;
	Hdta hdta;

	uint32 type;
	int coordinateCount;

	Point2D startPoint;
	Point2D endPoint;
	Vector<Point2D*> midPositions;

	Vector<BoundaryRectangle*> rectangles;

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
