/*
 * CustomizationDataMap.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef CUSTOMIZATIONDATAMAP_H_
#define CUSTOMIZATIONDATAMAP_H_

#include "engine/engine.h"

class CustomizationDataMap : public VectorMap<String, CustomizationData> {
public:
	CustomizationDataMap();

	void parseFromIffStream(IffStream* iffStream) {
		iffStream->openChunk("COLS");

		uint32 unknownInt1 = iffStream->getInt();
		uint32 unknownInt2 = iffStream->getInt();
	}
};


#endif /* CUSTOMIZATIONDATAMAP_H_ */
