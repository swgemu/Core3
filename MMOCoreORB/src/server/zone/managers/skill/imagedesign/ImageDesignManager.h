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
#include "server/zone/templates/params/PaletteColorCustomizationVariable.h"

class ImageDesignManager : public Singleton<ImageDesignManager>, public Object, public Logger {
	void loadCustomizationData();
	void updateColorVariable(const Vector<String>& fullVariables, uint32 value, TangibleObject* tano, int skillLevel);
	int getSkillLevel(CreatureObject* imageDesigner);

public:
	ImageDesignManager();
	~ImageDesignManager();

	void updateCustomization(CreatureObject* imageDesigner, const String& customizationName, float value, CreatureObject* creo = NULL);
	void updateColorCustomization(CreatureObject* imageDesigner, const String& customizationName, uint32 value, TangibleObject* hairObject, CreatureObject* creo = NULL);


	CustomizationData* getCustomizationData(const String& speciesGender, const String& customizationName);

	String getSpeciesGenderString(CreatureObject* creo = NULL);

	TangibleObject* updateHairObject(CreatureObject* creo, TangibleObject* hairObject);

	TangibleObject* createHairObject(CreatureObject* imageDesigner, CreatureObject* targetObject, const String& hairTemplate, const String& hairCustomization);

	//skillLevel: -1 creation, 0 novice... 5 master
	static bool validateCustomizationString(CustomizationVariables* data, const String& appearanceFilename, int skillLevel);
	static bool validatePalette(PaletteColorCustomizationVariable* variable, int value, int skillLevel);
};

#endif /* IMAGEDESIGNMANAGER_H_ */
