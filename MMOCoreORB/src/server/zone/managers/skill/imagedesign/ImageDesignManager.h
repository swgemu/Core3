/*
 * ImageDesignManager.h
 *
 *  Created on: Feb 3, 2011
 *      Author: Polonel
 */

#ifndef IMAGEDESIGNMANAGER_H_
#define IMAGEDESIGNMANAGER_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "templates/customization/CustomizationData.h"
#include "templates/params/PaletteColorCustomizationVariable.h"

class ImageDesignManager : public Singleton<ImageDesignManager>, public Object, public Logger {
	void loadCustomizationData();
	void updateColorVariable(const Vector<String>& fullVariables, uint32 value, TangibleObject* tano);
	//int getSkillLevel(CreatureObject* imageDesigner, const String& skillMod);

	void updateCustomization(CreatureObject* imageDesigner, CustomizationData* customData, float value, CreatureObject* creo = nullptr);
	void updateColorCustomization(CreatureObject* imageDesigner, CustomizationData* customData, uint32 value, TangibleObject* hairObject, CreatureObject* creo = nullptr);

public:
	enum {
		NONE,
		PHYSICAL,
		COSMETIC,
	};

	ImageDesignManager();
	~ImageDesignManager();

	void updateCustomization(CreatureObject* imageDesigner, const String& customizationName, float value, int& modificationType, CreatureObject* creo = nullptr);
	void updateColorCustomization(CreatureObject* imageDesigner, const String& customizationName, uint32 value, TangibleObject* hairObject, int& modificationType, CreatureObject* creo = nullptr);

	const Vector<CustomizationData>* getCustomizationData(const String& speciesGender, const String& customizationName);

	String getSpeciesGenderString(CreatureObject* creo = nullptr);

	TangibleObject* updateHairObject(CreatureObject* creo, TangibleObject* hairObject);

	TangibleObject* createHairObject(CreatureObject* imageDesigner, CreatureObject* targetObject, const String& hairTemplate, const String& hairCustomization);

	//skillLevel: -1 creation, 0 novice... 5 master
	static bool validateCustomizationString(CustomizationVariables* data, const String& appearanceFilename);
	static bool validatePalette(PaletteColorCustomizationVariable* variable, int value);
};

#endif /* IMAGEDESIGNMANAGER_H_ */
