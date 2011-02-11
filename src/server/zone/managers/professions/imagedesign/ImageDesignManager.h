/*
 * ImageDesignManager.h
 *
 *  Created on: Feb 3, 2011
 *      Author: Polonel
 */

#ifndef IMAGEDESIGNMANAGER_H_
#define IMAGEDESIGNMANAGER_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"

class CustomizationData {
	String speciesGender;
	String customizationGroup;
	String type;
	String customizationName;
	String variables;
	bool isScale;
	bool reverse;
	String colorLinked;
	String colorLinkedtoSelf0;
	String colorLinkedtoSelf1;
	int cameraYaw;
	bool discrete;
	bool randomizable;
	bool randomizableGroup;
	bool isVarHairColor;
	String imageDesignSkillMod;
	int skillModValue;
	String modificationType;
	int maxChoices;
	float minScale;
	float maxScale;

public:

	inline void setSpeciesGender(String value) {
		speciesGender = value;
	}
	inline void setCustomizationGroup(String value) {
		customizationGroup = value;
	}
	inline void setType(String value) {
		type = value;
	}
	inline void setCustomizationName(String value) {
		customizationName = value;
	}
	inline void setVariables(String value) {
		variables = value;
	}
	inline void setIsScale(bool value) {
		isScale = value;
	}
	inline void setReverse(bool value) {
		reverse = value;
	}
	inline void setColorLinked(String value) {
		colorLinked = value;
	}
	inline void setColorLinkedtoSelf0(String value) {
		colorLinkedtoSelf0 = value;
	}
	inline void setColorLinkedtoSelf1(String value) {
		colorLinkedtoSelf1 = value;
	}
	inline void setCameraYaw(int value) {
		cameraYaw = value;
	}
	inline void setDiscrete(bool value) {
		discrete = value;
	}
	inline void setRandomizable(bool value) {
		randomizable = value;
	}
	inline void setRandomizableGroup(bool value) {
		randomizableGroup = value;
	}
	inline void setIsVarHairColor(bool value) {
		isVarHairColor = value;
	}
	inline void setImageDesignSkillMod(String value) {
		imageDesignSkillMod = value;
	}
	inline void setSkillModValue(int value) {
		skillModValue = value;
	}
	inline void setModificationType(String value) {
		modificationType = value;
	}
	inline void setMaxChoices(int value) {
		maxChoices = value;
	}
	inline void setMinScale(float value) {
		minScale = value;
	}
	inline void setMaxScale(float value) {
		maxScale = value;
	}


	inline String getSpeciesGender() {
		return speciesGender;
	}
	inline String getCustomizationGroup() {
		return customizationGroup;
	}
	inline String getType() {
		return type;
	}
	inline String getCustomizationName() {
		return customizationName;
	}
	inline String getVariables() {
		return variables;
	}
	inline bool getIsScale() {
		return isScale;
	}
	inline bool getReverse() {
		return reverse;
	}
	inline String getColorLinked() {
		return colorLinked;
	}
	inline String getColorLinkedtoSelf0() {
		return colorLinkedtoSelf0;
	}
	inline String getColorLinkedtoSelf1() {
		return colorLinkedtoSelf1;
	}
	inline int getCameraYaw() {
		return cameraYaw;
	}
	inline bool getDiscrete() {
		return discrete;
	}
	inline bool getRandomizable() {
		return randomizable;
	}
	inline bool getRandomizableGroup() {
		return randomizableGroup;
	}
	inline bool getIsVarHairColor() {
		return isVarHairColor;
	}
	inline String getImageDesignSkillMod() {
		return imageDesignSkillMod;
	}
	inline int getSkillModValue() {
		return skillModValue;
	}
	inline String getModificationType() {
		return modificationType;
	}
	inline int getMaxChoices() {
		return maxChoices;
	}
	inline float getMinScale() {
		return minScale;
	}
	inline float getMaxScale() {
		return maxScale;
	}
};

class ImageDesignManager {
	String speciesGender;
	String customizationName;
	CreatureObject* creatureObject;

	VectorMap<String, CustomizationData*> customizationData;

	CustomizationVariables hairCustomization;

	void loadCustomizationData();

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
