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

class ImageDesignManager : public Object {
	void loadCustomizationData();

public:
	ImageDesignManager();
	~ImageDesignManager();

	void updateCustomization(const String& customizationName, float value, String& hairTemplate, CreatureObject* creo = NULL);
	void updateCustomization(const String& customizationName, uint32 value, String& hairTemplate, CreatureObject* creo = NULL);

	CustomizationData* getCustomizationData(const String& speciesGender, const String& customizationName);

	String getSpeciesGenderString(CreatureObject* creo = NULL);

	void updateCharacterAppearance(CreatureObject* creo = NULL);

	void updateHairObject(CreatureObject* creo, String& hairObject, String& hairCustomization);

	void setHairAttribute(String& type, uint8 value);
	void setHairAttribute(uint8 type, uint8 value);

};

#endif /* IMAGEDESIGNMANAGER_H_ */
