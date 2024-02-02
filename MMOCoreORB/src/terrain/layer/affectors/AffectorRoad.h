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
#include "../../TerrainGenerator.h"

class AffectorRoad : public ProceduralRule<'AROA'>, public AffectorProceduralRule {
	Road road;
	Hdta hdta;

	int coordinateCount;

	Vector<Point2D*> positions;

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

		coordinateCount = iffStream->getInt();

		for (int i = 0; i < coordinateCount; i++) {
			Point2D* pos = new Point2D();
			pos->x = iffStream->getFloat();
			pos->y = iffStream->getFloat();

			Logger::console.info(true) << "Loading Road Position - X: " << pos->x << " Y: " << pos->y;

			positions.add(pos);
		}

		width = iffStream->getFloat();
		familyID = iffStream->getInt();
		featheringType = iffStream->getInt();
		featheringAmount = Math::clamp(0.f, iffStream->getFloat(), 1.f);
		featheringShader = iffStream->getInt();
		featheringShaderDistance = Math::clamp(0.f, iffStream->getFloat(), 1.f);

		Logger::console.info(true) << "AffectorRoad -- coordinateCount: " << coordinateCount << " width: " << width << " familyID: " << familyID << " featheringType: " << featheringType << " featheringAmount: " << featheringAmount << " featheringShader: " << featheringShader << " featheringShaderDistance: " << featheringShaderDistance;

		iffStream->closeChunk('DATA');

		iffStream->closeForm('DATA');
	}

	void process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator) {
		Logger::console.info(true) << "AffectorRoad -- process function called for location X: " << x << " Y: " << y << " transformValue: " << transformValue << " baseValue: " << baseValue;
		Logger::console.info(true) << "Road Info -- coordinateCount: " << positions.size() << " width: " << width << " familyID: " << familyID << " featheringType: " << featheringType << " featheringAmount: " << featheringAmount << " featheringShader: " << featheringShader << " featheringShaderDistance: " << featheringShaderDistance;


		if (transformValue == 0 || positions.size() == 0)
			return;

		//float currentHeight = terrainGenerator->get

		Logger::console.info(true) << "Processing baseValue for new height";

		/*	Process the RoadData
			Result we will be returning should be the height for the road using the x, y and the base values passed into the function
		*/

		//Math::linearInterpolate(1.f, maxFactor, (speedRatio - optimalFactor) / (1.f - optimalFactor))

		float distSquared = 0.f;
		float nearestX = 0.f;
		float nearestY = 0.f;

		for (int i = 0; i < positions.size(); ++i) {
			Point2D* pos = positions.get(i);

			if (pos == nullptr)
				continue;

			float deltaX = pos->getX() - x;
			float deltaY = pos->getY() - y;
			float pointDistSq = (deltaX * deltaX + deltaY * deltaY);

			if (distSquared == 0.f || pointDistSq < distSquared) {
				distSquared = pointDistSq;

				nearestX = pos->getX();
				nearestY = pos->getY();
			}
		}

		Logger::console.info(true) << "Nearest Point Distance Squared: " << distSquared << "   Location  X: " << nearestX << " Y: " << nearestY;


	}

	bool isEnabled() {
		return informationHeader.isEnabled();
	}
};

#endif /* AFFECTORROAD_H_ */
