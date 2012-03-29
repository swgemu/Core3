/*
 * CustomizationIdManager.h
 *
 *  Created on: 28/03/2012
 *      Author: victor
 */

#ifndef CUSTOMIZATIONIDMANAGER_H_
#define CUSTOMIZATIONIDMANAGER_H_

#include "engine/engine.h"
#include "PaletteData.h"
#include "HairAssetData.h"

class CustomizationIdManager : public Object, public Logger, public Singleton<CustomizationIdManager> {
	HashTable<String, int> customizationIds;
	HashTable<int, String> reverseIds;
	HashTable<String, Reference<PaletteData*> > paletteColumns;
	HashTable<String, Reference<HairAssetData*> > hairAssetSkillMods;

public:
	CustomizationIdManager();

	void loadPaletteColumns(IffStream* iffStream);
	void loadHairAssetsSkillMods(IffStream* iffStream);
	void readObject(IffStream* iffStream);

	int getCustomizationId(const String& var) {
		return customizationIds.get(var);
	}

	String getCustomizationVariable(int id) {
		return reverseIds.get(id);
	}

	PaletteData* getPaletteData(const String& palette) {
		return paletteColumns.get(palette);
	}

	HairAssetData* getHairAssetData(const String& hairServerTemplate) {
		return hairAssetSkillMods.get(hairServerTemplate);
	}
};


#endif /* CUSTOMIZATIONIDMANAGER_H_ */
