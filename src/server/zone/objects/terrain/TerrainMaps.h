/*
 * TerrainMaps.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef TERRAINMAPS_H_
#define TERRAINMAPS_H_

#include "TemplateVariable.h"
#include "TerrainMap.h"

class TerrainMaps : public TemplateVariable<'0001'> {
	float var1;
	float var2;
	int var3;
	int var4;

	TerrainMap<'WMAP'> waterMap;
	TerrainMap<'SMAP'> seedMap;
public:
	void parseFromIffStream(engine::util::IffStream* iffStream) {
		/*uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0001':
			parseFromIffStream(iffStream, Version<'0001'>());
			break;
		default:
			System::out << "unknown MAPS version 0x" << hex << version;
			break;
		}

		iffStream->closeForm(version);*/
		parseFromIffStream(iffStream, Version<'0001'>());
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
		iffStream->openChunk('DATA');

		var1 = iffStream->getFloat();
		var2 = iffStream->getFloat();
		var3 = iffStream->getInt();
		var4 = iffStream->getInt();

		iffStream->closeChunk('DATA');

		waterMap.readObject(iffStream);
		seedMap.readObject(iffStream);
	}
};


#endif /* TERRAINMAPS_H_ */
