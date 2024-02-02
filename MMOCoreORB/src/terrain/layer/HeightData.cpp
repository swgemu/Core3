/*
 * HeightData.cpp
*/

#include "HeightData.h"

void HeightData::parseFromIffStream(engine::util::IffStream* iffStream) {
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

void HeightData::parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
	int number = iffStream->getSubChunksNumber();

	for (int i = 0; i < number; i++) {
		Segment* sgmt = new Segment();

#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "HeightData - Adding segment #" << i;
#endif

		sgmt->readObject(iffStream);

		segments.add(sgmt);
	}

#ifdef DEBUG_AFFECTOR_ROAD
	Logger::console.info(true) << "HeightData finished loading segments - Total Segments: " << segments.size();
#endif
}

void HeightData::findNearestHeight(float& baseValue, float positionX, float positionY, float roadX, float roadY) {
	float zCoord = 0.f;

#ifdef DEBUG_AFFECTOR_ROAD
	Logger::console.info(true) << "HeightData::findNearestHeight called - roadX: " << roadX << " roadY: " << roadY << " Total Segments to check: " << segments.size();
#endif

	for (int i = 0; i < segments.size(); ++i) {
		Segment* segment = segments.get(i);

		if (segment == nullptr || !segment->hasInitialCoordinate(roadX, roadY))
			continue;

		segment->findNearestHeight(baseValue, positionX, positionY);

		break;
	}
}
