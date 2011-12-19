/*
 * AssetCustomizationManager.h
 *
 *  Created on: 01/04/2011
 *      Author: victor
 */

#ifndef ASSETCUSTOMIZATIONMANAGERTEMPLATE_H_
#define ASSETCUSTOMIZATIONMANAGERTEMPLATE_H_

#include "engine/engine.h"
#include "../IffTemplate.h"

#include "CustomizationVariable.h"

class AssetCustomizationManagerTemplate : public IffTemplate, public Singleton<AssetCustomizationManagerTemplate> {
	byte* ulstTable;
	int ulstTableCount;

	byte* ucmpTable;
	int ucmpTableCount;

	byte* vnofTable;
	int vnofTableCount;

	byte* pnofTable;
	int pnofTableCount;

	byte* defvTable;
	int defvTableCount;

	byte* irngTable;
	int irngTableCount;

	byte* nameTable;
	int nameTableCount;

	byte* rtypTable;
	int rtypTableCount;

	byte* uidxTable;
	int uidxTableCount;

	byte* llstTable;
	int llstTableCount;

	byte* lidxTable;
	int lidxTableCount;

	byte* cidxTable;
	int cidxTableCount;

public:
	AssetCustomizationManagerTemplate();
	~AssetCustomizationManagerTemplate();

	void readObject(IffStream* iffStream);
	void getCustomizationVariables(uint32 appearanceFileCRC, VectorMap<String, Reference<CustomizationVariable*> >& variables);

private:
	void parseCidxTable(IffStream* iffStream);
	void parseLidxTable(IffStream* iffStream);
	void parseLlstTable(IffStream* iffStream);
	void parseUidxTable(IffStream* iffStream);
	void parseUlstTable(IffStream* iffStream);
	void parseUcmpTable(IffStream* iffStream);
	void parseRtypTable(IffStream* iffStream);
	void parseIrngTable(IffStream* iffStream);
	void parseNameTable(IffStream* iffStream);
	void parsePnofTable(IffStream* iffStream);
	void parseVnofTable(IffStream* iffStream);
	void parseDefvTable(IffStream* iffStream);


	static int cidxCompareFunction(const void* key, const void* value);
	static int lidxCompareFunction(const void* key, const void* value);

	uint16 searchCidx(uint32 appearenceFileCRC);

	void* searchLidx(uint16 cidxKey);
	void* searchUidx(uint16 cidxKey);

	void* getUCMPValue(uint16 index);
	int getDEFVValue(byte index);
	String getCustomizationVariableName(byte index);
	String getStringFromNAME(uint16 index);
	String getPaletteFileName(uint16 pnofIndex);

	void getRTYP(byte a1, bool& pallete, uint16& resultIndex);

	void* getCustomizationVariablesFromMap(uint16 key, uint64 a2, bool skipSharedOwner, VectorMap<String, Reference<CustomizationVariable*> >& result);

};



#endif /* ASSETCUSTOMIZATIONMANAGER_H_ */
