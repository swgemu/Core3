/*
 * ImageDesignManager.h
 *
 *  Created on: Feb 3, 2011
 *      Author: Polonel
 */

#ifndef IMAGEDESIGNMANAGER_H_
#define IMAGEDESIGNMANAGER_H_

#include "engine/engine.h"
#include "system/lang/ref/Reference.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "CustomizationData.h"
#include "CustomizationDataMap.h"

class ImageDesignManager {
	// THESE CANNOT BE HERE!!!!!!!!!!!!
	String speciesGender;
	String customizationName;
	CreatureObject* creatureObject;
	CustomizationVariables hairCustomization;

	// ------------------------------------------

	VectorMap<String, CustomizationData*> customizationData;

	void loadCustomizationData();

protected:
	CustomizationDataMap customizationMap;
	VectorMap<String, CustomizationDataMap*> testVectorMap;

public:
	ImageDesignManager();
	~ImageDesignManager();

	void updateCustomization(String customizationName, float value, CreatureObject* creo = NULL);

	void updateCustomization(String customizationName, uint32 value, CreatureObject* creo = NULL);

	CustomizationData* getCustomizationData(String speciesGender, String customizationName);

	String getSpeciesGenderString(CreatureObject* creo = NULL);

	void updateCharacterAppearance(CreatureObject* creo = NULL);

	void updateHairObject(CreatureObject* creo, String& hairObject);

	inline void setHairCustomizationString(String& cus) {
		hairCustomization.parseFromClientString(cus);
	}
	void setHairAttribute(String& type, uint8 value);
	void setHairAttribute(uint8 type, uint8 value);

};

#endif /* IMAGEDESIGNMANAGER_H_ */
