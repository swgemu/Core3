/*
 * Hdta.cpp
 *
 * Created on: 2/2/2024
 * Author: Hakry
 */

#include "Hdta.h"

void Hdta::parseFromIffStream(engine::util::IffStream* iffStream) {
	uint32 version = iffStream->getNextFormType();

	iffStream->openForm(version);

	switch (version) {
		case '0001':
			parseFromIffStream(iffStream, Version<'0001'>());
			break;
		default:
			System::out << "unknown Road version " << version << endl;
			break;
	}

	iffStream->closeForm(version);
}

void Hdta::parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
	int number = iffStream->getSubChunksNumber();

	for (int i = 0; i < number; i++) {
		Segment* sgmt = new Segment();

		Logger::console.info(true) << "Hdta - Adding segment #" << i;

		sgmt->readObject(iffStream);

		segments.add(sgmt);
	}

	Logger::console.info(true) << "Hdta finished loading segments - Total Segments: " << segments.size();
}

void Hdta::findNearestHeight(float& baseValue, float positionX, float positionY, float roadX, float roadY) {
	float zCoord = 0.f;

	Logger::console.info(true) << "Hdta::findNearestHeight called - roadX: " << roadX << " roadY: " << roadY << " Total Segments to check: " << segments.size();

	for (int i = 0; i < segments.size(); ++i) {
		Segment* segment = segments.get(i);

		if (segment == nullptr || !segment->hasInitialCoordinate(roadX, roadY))
			continue;

		segment->findNearestHeight(baseValue, positionX, positionY);

		break;
	}
}
