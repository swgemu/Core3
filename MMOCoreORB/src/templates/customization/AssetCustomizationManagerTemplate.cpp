/*
 * AssetCustomizationManagerTemplate.cpp
 *
 *  Created on: 01/04/2011
 *      Author: victor
 */

#include "AssetCustomizationManagerTemplate.h"
#include "templates/params/PaletteColorCustomizationVariable.h"
#include "templates/customization/BasicRangedIntCustomizationVariable.h"

AssetCustomizationManagerTemplate::AssetCustomizationManagerTemplate() {
	ulstTable = NULL;
	ulstTableCount = 0;
	ucmpTable = NULL;
	ucmpTableCount = 0;
	vnofTable = NULL;
	vnofTableCount = 0;
	nameTable = NULL;
	nameTableCount = 0;
	pnofTable = NULL;
	pnofTableCount = 0;
	defvTable = NULL;
	defvTableCount = 0;
	irngTable = NULL;
	irngTableCount = 0;
	rtypTable = NULL;
	rtypTableCount = 0;
	uidxTable = NULL;
	uidxTableCount = 0;
	llstTable = NULL;
	llstTableCount = 0;
	lidxTable = NULL;
	lidxTableCount = 0;
	cidxTable = NULL;
	cidxTableCount = 0;
}

AssetCustomizationManagerTemplate::~AssetCustomizationManagerTemplate() {
	delete [] ulstTable;
	delete [] ucmpTable;
	delete [] vnofTable;
	delete [] nameTable;
	delete [] pnofTable;
	delete [] defvTable;
	delete [] irngTable;
	delete [] rtypTable;
	delete [] uidxTable;
	delete [] llstTable;
	delete [] lidxTable;
	delete [] cidxTable;
}

void* AssetCustomizationManagerTemplate::getCustomizationVariablesFromMap(uint16 key, uint64 a2, bool skipSharedOwner, VectorMap<String, Reference<CustomizationVariable*> >& result) {
	void* uidxResult = searchUidx(key);
	void* returnValue = NULL;

	if (uidxResult) {
		//Logger::console.info("UIDXRESULT NOT NULL", true);

		uint16 currentIndex = *((uint16*)uidxResult + 1);
		uint16 finalIndex = currentIndex + *((byte*)uidxResult + 4);

		while (currentIndex < finalIndex) {
			//Logger::console.info("CURERNTINDEX < FINALINDEX ", true);
			void* ucmpValue = getUCMPValue(*(uint16*)(ulstTable + 2 * currentIndex));


			String variableName = getCustomizationVariableName(*(byte*) ucmpValue);

			if (!result.contains(variableName) && !(skipSharedOwner && variableName.contains("/shared_owner/"))) {
				bool isPallette = false;
				uint16 rtypResult = 0;

				int defaultValue = getDEFVValue(*((byte*)ucmpValue + 2));

				//Logger::console.info("VARIABLENAME: " + variableName, true);
				//Logger::console.info("DEFAULT VALUE: " + String::valueOf(defaultValue), true);

				getRTYP(*((byte*)ucmpValue + 1), isPallette, rtypResult);

				if (!isPallette) {
					int min = *(uint32*)(irngTable + 8 * rtypResult - 8);
					int max = *(uint32*)(irngTable + 8 * rtypResult - 4);

					//Logger::console.info("MIN: " + String::valueOf(min), true);
					//Logger::console.info("MAX: " + String::valueOf(max), true);

					Reference<BasicRangedIntCustomizationVariable*> var = new BasicRangedIntCustomizationVariable(min, max, defaultValue);
					result.put(variableName, var.get());
				} else {
					String paletteFileName = getPaletteFileName(rtypResult);
					//Logger::console.info("PALETTE FILENAME: " + paletteFileName, true);

					//TODO: open palette file and parse min/max

					Reference<PaletteColorCustomizationVariable*> var = new PaletteColorCustomizationVariable(defaultValue, paletteFileName);
					result.put(variableName, var.get());
				}
			}

			currentIndex++;
		}
	}
		//Logger::console.info("UIDXRESULT NULL", true);
	returnValue = searchLidx(key);

	if (returnValue != NULL) {
		//Logger::console.info("RETURN VALUE NOT NULL", true);

		uint16 v23 = *((uint16*)returnValue + 1);

		for (int i = v23 + *((byte*)returnValue + 4); v23 < i; ++v23) {
			returnValue = getCustomizationVariablesFromMap(*(uint16*)(llstTable + 2 * v23), a2, skipSharedOwner, result);
		}
	}/* else
			Logger::console.info("RETURN VALUE NULL", true);*/


	return returnValue;
}

void AssetCustomizationManagerTemplate::getCustomizationVariables(uint32 appearanceFileCRC, VectorMap<String, Reference<CustomizationVariable*> >& variables, bool skipShared) {
	uint16 key = searchCidx(appearanceFileCRC);

	if (!key)
		return;

	getCustomizationVariablesFromMap(key, 0, skipShared, variables);
}

int AssetCustomizationManagerTemplate::cidxCompareFunction(const void* key, const void* value) {
	//return *(uint16*)key - *(uint16*)value;
	uint32 val = *(uint32*)value;
	uint32 k = *(uint32*)key;

	if (val <= k)
		return val < k;
	else
		return -1;
}

int AssetCustomizationManagerTemplate::lidxCompareFunction(const void* key, const void* value) {
	return *(uint16*)key - *(uint16*)value;
}

void AssetCustomizationManagerTemplate::getRTYP(byte a1, bool& pallete, uint16& resultIndex) {
	resultIndex = *(uint16*)(rtypTable + 2 * a1 - 2);
	pallete = resultIndex & 0x8000;

	resultIndex &= 0x7FFF;
}

String AssetCustomizationManagerTemplate::getPaletteFileName(uint16 pnofIndex) {
	return getStringFromNAME(*(uint16*)(pnofTable + 2 * pnofIndex - 2));
}

uint16 AssetCustomizationManagerTemplate::searchCidx(uint32 appearenceFileCRC) {
	uint16 returnValue;

	//Logger::console.info("CIDX TABLE COUNT " + String::hexvalueOf(cidxTableCount), true);

	void* result = bsearch(&appearenceFileCRC, cidxTable, cidxTableCount, 6, cidxCompareFunction);

	if (result) {
		//Logger::console.info("RESULT NOT NULL", true);
		returnValue = *((uint16*)result + 2);
	} else {
		//Logger::console.info("RESULT NULL", true);
		returnValue = 0;
	}

	return returnValue;
}

void* AssetCustomizationManagerTemplate::getUCMPValue(uint16 index) {
	return index + ucmpTable + 2 * index - 3;
}

String AssetCustomizationManagerTemplate::getCustomizationVariableName(byte index) {
	return getStringFromNAME(*(uint16*)(vnofTable + 2 * index - 2));
}

String AssetCustomizationManagerTemplate::getStringFromNAME(uint16 index) {
	return String((const char*)(nameTable + index));
}

int AssetCustomizationManagerTemplate::getDEFVValue(byte index) {
	return *(int*)(defvTable + 4 * index - 4);
}


void AssetCustomizationManagerTemplate::readObject(IffStream* iffStream) {
	iffStream->openForm('ACST');
	iffStream->openForm('0000');

	parseNameTable(iffStream);
	parsePnofTable(iffStream);
	parseVnofTable(iffStream);
	parseDefvTable(iffStream);
	parseIrngTable(iffStream);
	parseRtypTable(iffStream);
	parseUcmpTable(iffStream);
	parseUlstTable(iffStream);
	parseUidxTable(iffStream);
	parseLlstTable(iffStream);
	parseLidxTable(iffStream);
	parseCidxTable(iffStream);

	iffStream->closeForm('0000');
	iffStream->closeForm('ACST');
}

void AssetCustomizationManagerTemplate::parseCidxTable(IffStream* iffStream) {
	Chunk* chunk = iffStream->openChunk('CIDX');

	cidxTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)cidxTable, chunk->getChunkSize());
	cidxTableCount = chunk->getChunkSize() / 6;

	iffStream->closeChunk();
}

void AssetCustomizationManagerTemplate::parseLidxTable(IffStream* iffStream) {
	Chunk* chunk = iffStream->openChunk('LIDX');

	lidxTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)lidxTable, chunk->getChunkSize());
	lidxTableCount = chunk->getChunkSize() / 5;

	iffStream->closeChunk();
}

void AssetCustomizationManagerTemplate::parseLlstTable(IffStream* iffStream) {
	Chunk* chunk = iffStream->openChunk('LLST');

	llstTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)llstTable, chunk->getChunkSize());
	llstTableCount = chunk->getChunkSize() / 2;

	iffStream->closeChunk();
}

void AssetCustomizationManagerTemplate::parseUidxTable(IffStream* iffStream) {
	Chunk* chunk = iffStream->openChunk('UIDX');

	uidxTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)uidxTable, chunk->getChunkSize());
	uidxTableCount = chunk->getChunkSize() / 5;

	iffStream->closeChunk();
}

void AssetCustomizationManagerTemplate::parseUlstTable(IffStream* iffStream) {
	Chunk* chunk = iffStream->openChunk('ULST');

	ulstTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)ulstTable, chunk->getChunkSize());
	ulstTableCount = chunk->getChunkSize() / 2;

	iffStream->closeChunk();
}

void AssetCustomizationManagerTemplate::parseUcmpTable(IffStream* iffStream) {
	Chunk* chunk = iffStream->openChunk('UCMP');

	ucmpTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)ucmpTable, chunk->getChunkSize());
	ucmpTableCount = chunk->getChunkSize() / 3;

	iffStream->closeChunk();
}

void AssetCustomizationManagerTemplate::parseRtypTable(IffStream* iffStream) {
	//NAME
	Chunk* chunk = iffStream->openChunk('RTYP');

	rtypTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)rtypTable, chunk->getChunkSize());
	rtypTableCount = chunk->getChunkSize() / 2;

	iffStream->closeChunk();
}

void AssetCustomizationManagerTemplate::parseIrngTable(IffStream* iffStream) {
	//NAME
	Chunk* chunk = iffStream->openChunk('IRNG');

	irngTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)irngTable, chunk->getChunkSize());
	irngTableCount = chunk->getChunkSize() / 8;

	iffStream->closeChunk();
}

void AssetCustomizationManagerTemplate::parseNameTable(IffStream* iffStream) {
	//NAME
	Chunk* chunk = iffStream->openChunk('NAME');

	nameTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)nameTable, chunk->getChunkSize());
	nameTableCount = chunk->getChunkSize();

	iffStream->closeChunk();
}

void AssetCustomizationManagerTemplate::parsePnofTable(IffStream* iffStream) {
	//PNOF
	Chunk* chunk = iffStream->openChunk('PNOF');

	pnofTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)pnofTable, chunk->getChunkSize());
	pnofTableCount = chunk->getChunkSize() / 2;

	iffStream->closeChunk();
}

void AssetCustomizationManagerTemplate::parseVnofTable(IffStream* iffStream) {
	//vnof
	Chunk* chunk = iffStream->openChunk('VNOF');

	vnofTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)vnofTable, chunk->getChunkSize());
	vnofTableCount = chunk->getChunkSize() / 2;

	iffStream->closeChunk();
}

void AssetCustomizationManagerTemplate::parseDefvTable(IffStream* iffStream) {
	Chunk* chunk = iffStream->openChunk('DEFV');

	defvTable = new byte[chunk->getChunkSize()];
	chunk->readStream((char*)defvTable, chunk->getChunkSize());
	defvTableCount = chunk->getChunkSize() / 2;

	iffStream->closeChunk();
}

void* AssetCustomizationManagerTemplate::searchLidx(uint16 cidxKey) {
	return bsearch(&cidxKey, lidxTable, lidxTableCount, 5, lidxCompareFunction);
}

void* AssetCustomizationManagerTemplate::searchUidx(uint16 cidxKey) {
	return bsearch(&cidxKey, uidxTable, uidxTableCount, 5, lidxCompareFunction);
}


