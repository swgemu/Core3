/*
 * SpaceTerrainAppearance.cpp
 *
 *  Created on: 17/10/2013
 *      Author: victor
 */

#include "SpaceTerrainAppearance.h"

SpaceTerrainAppearance::SpaceTerrainAppearance() : Logger("SpaceTerrainAppearance") {

}

bool SpaceTerrainAppearance::load(IffStream* iffStream) {
	readObject(iffStream);

	return true;
}

void SpaceTerrainAppearance::parseFromIffStream(engine::util::IffStream* iffStream) {
	uint32 version = iffStream->getNextFormType();

	iffStream->openForm(version);

	switch (version) {
	case '0000':
		parseFromIffStream(iffStream, Version<'0000'>());
		break;
	default:
		error("unknown version in SpaceTerrainAppearance::parseFromIffStream " + String::valueOf(version));
		break;
	}

	iffStream->closeForm(version);
}

void SpaceTerrainAppearance::parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
	while (iffStream->getRemainingSubChunksNumber() > 0) {
		uint32 nextForm = iffStream->getNextFormType();

		switch (nextForm) {
		case 'SKYB':
			parseSKYB(iffStream);
			break;
		case 'STAR':
			parseSTAR(iffStream);
			break;
		case 'PLAN':
			parsePLAN(iffStream);
			break;
		case 'PARA':
			parsePARA(iffStream);
			break;
		case 'FOG ':
			parseFOG(iffStream);
			break;
		case 'ENVI':
			parseENVI(iffStream);
			break;
		case 'DIST':
			parseDIST(iffStream);
			break;
		case 'DUST':
			parseDUST(iffStream);
			break;
		case 'CLEA':
			parseCLEA(iffStream);
			break;
		case 'CELE':
			parseCELE(iffStream);
			break;
		case 'AMBI':
			parseAMBI(iffStream);
			break;
		default:
			error("unexpected FORM " + String::hexvalueOf((int)nextForm));
			iffStream->skipChunks(1);
			break;
		}
	}
}

void SpaceTerrainAppearance::parseSKYB(engine::util::IffStream* iffStream) {
	iffStream->openForm('SKYB');
	iffStream->openChunk('0000');

	bool var1 = iffStream->getByte();
	String var2;
	iffStream->getString(var2);

	iffStream->closeChunk('0000');
	iffStream->closeForm('SKYB');
}

void SpaceTerrainAppearance::parseSTAR(engine::util::IffStream* iffStream) {
	iffStream->openForm('STAR');
	iffStream->openChunk('0000');

	String var1;
	iffStream->getString(var1);

	int var2 = iffStream->getInt();

	iffStream->closeChunk('0000');
	iffStream->closeForm('STAR');
}

void SpaceTerrainAppearance::parsePLAN(engine::util::IffStream* iffStream) {
	iffStream->openForm('PLAN');
	iffStream->openChunk('0000');

	String var1;
	iffStream->getString(var1);

	//these are their own struct posible 3d point
	float x = iffStream->getFloat();
	float z = iffStream->getFloat();
	float y = iffStream->getFloat();

	float var5 = iffStream->getFloat() * Math::DEG2RAD;
	float var6 = iffStream->getFloat() * Math::DEG2RAD;
	float var7 = iffStream->getFloat() * Math::DEG2RAD;
	float var8 = iffStream->getFloat();

	iffStream->closeChunk('0000');
	iffStream->closeForm('PLAN');
}

void SpaceTerrainAppearance::parsePARA(engine::util::IffStream* iffStream) {
	iffStream->openForm('PARA');
	iffStream->openChunk('0000');

	bool var1 = iffStream->getByte();

	float dw = iffStream->getFloat();
	float dx = iffStream->getFloat();
	float dy = iffStream->getFloat();
	float dz = iffStream->getFloat();

	float dw2 = iffStream->getFloat();
	float dx2 = iffStream->getFloat();
	float dy2 = iffStream->getFloat();
	float dz2 = iffStream->getFloat();

	float x = iffStream->getFloat();
	float z = iffStream->getFloat();
	float y = iffStream->getFloat();


	iffStream->closeChunk('0000');
	iffStream->closeForm('PARA');
}

void SpaceTerrainAppearance::parseFOG(engine::util::IffStream* iffStream) {
	iffStream->openForm('FOG ');
	iffStream->openChunk('0000');

	float dw = iffStream->getFloat();
	float dx = iffStream->getFloat();
	float dy = iffStream->getFloat();
	float dz = iffStream->getFloat();

	iffStream->closeChunk('0000');
	iffStream->closeForm('FOG ');
}

void SpaceTerrainAppearance::parseENVI(engine::util::IffStream* iffStream) {
	iffStream->openForm('ENVI');
	iffStream->openChunk('0000');

	String var1;
	iffStream->getString(var1);

	iffStream->closeChunk('0000');
	iffStream->closeForm('ENVI');
}

void SpaceTerrainAppearance::parseDIST(engine::util::IffStream* iffStream) {
	iffStream->openForm('DIST');
	iffStream->openChunk('0000');

	String var1;
	iffStream->getString(var1);

	float x = iffStream->getFloat();
	float z = iffStream->getFloat();
	float y = iffStream->getFloat();

	float var5 = iffStream->getFloat() * Math::DEG2RAD;
	float var6 = iffStream->getFloat() * Math::DEG2RAD;
	float var7 = iffStream->getFloat() * Math::DEG2RAD;

	iffStream->closeChunk('0000');
	iffStream->closeForm('DIST');
}

void SpaceTerrainAppearance::parseDUST(engine::util::IffStream* iffStream) {
	iffStream->openForm('DUST');
	iffStream->openChunk('0000');

	uint32 var1 = iffStream->getUnsignedInt();
	float var2 = iffStream->getFloat();

	iffStream->closeChunk('0000');
	iffStream->closeForm('DUST');
}

void SpaceTerrainAppearance::parseCLEA(engine::util::IffStream* iffStream) {
	iffStream->openForm('CLEA');
	iffStream->openChunk('0000');

	float var1 = iffStream->getFloat();
	var1 = MAX(MIN(var1, 1.0), 0);

	float var2 = iffStream->getFloat();
	var2 = MAX(MIN(var1, 1.0), 0);

	float var3 = iffStream->getFloat();
	var3 = MAX(MIN(var1, 1.0), 0);

	uint8 thisVar1 = (uint8) (var1 * 255.f);
	uint8 thisVar2 = (uint8) (var2 * 255.f);
	uint8 thisVar3 = (uint8) (var3 * 255.f);

	iffStream->closeChunk('0000');
	iffStream->closeForm('CLEA');
}

void SpaceTerrainAppearance::parseCELE(engine::util::IffStream* iffStream) {
	iffStream->openForm('CELE');
	iffStream->openChunk('0000');

	String var1, var3;

	iffStream->getString(var1);
	float var2 = iffStream->getFloat();
	iffStream->getString(var3);
	float var4 = iffStream->getFloat(); //might be int

	float x = iffStream->getFloat();
	float z = iffStream->getFloat();
	float y = iffStream->getFloat();

	iffStream->closeChunk('0000');
	iffStream->closeForm('CELE');
}

void SpaceTerrainAppearance::parseAMBI(engine::util::IffStream* iffStream) {
	iffStream->openForm('AMBI');
	iffStream->openChunk('0000');

	float dw = iffStream->getFloat();
	float dx = iffStream->getFloat();
	float dy = iffStream->getFloat();
	float dz = iffStream->getFloat();

	iffStream->closeChunk('0000');
	iffStream->closeForm('AMBI');
}
