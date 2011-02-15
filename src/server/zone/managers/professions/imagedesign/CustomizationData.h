/*
 * CustomizationData.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef CUSTOMIZATIONDATA_H_
#define CUSTOMIZATIONDATA_H_

class CustomizationData : public Serializable {
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

public:

	CustomizationData() {
		/*speciesGender = 0;
		customizationGroup = 0;
		type = 0;
		customizationName = 0;
		variables = 0;
		isScale = 0;
		reverse = 0;
		colorLinked = 0;
		colorLinkedtoSelf0 = 0;
		colorLinkedtoSelf1 = 0;
		cameraYaw = 0;
		discrete = 0;
		randomizable = 0;
		randomizableGroup = 0;
		isVarHairColor = 0;
		imageDesignSkillMod = 0;
		skillModValue = 0;
		modificationType = 0;*/

		addSerializableVariables();
	}

	CustomizationData(const CustomizationData& c) :	Object(), Serializable() {
		speciesGender = c.speciesGender;
		customizationGroup = c.customizationGroup;
		type = c.type;
		customizationName = c.customizationName;
		variables = c.variables;
		isScale = c.isScale;
		reverse = c.reverse;
		colorLinked = c.colorLinked;
		colorLinkedtoSelf0 = c.colorLinkedtoSelf0;
		colorLinkedtoSelf1 = c.colorLinkedtoSelf1;
		cameraYaw = c.cameraYaw;
		discrete = c.discrete;
		randomizable = c.randomizable;
		randomizableGroup = c.randomizableGroup;
		isVarHairColor = c.isVarHairColor;
		imageDesignSkillMod = c.imageDesignSkillMod;
		skillModValue = c.skillModValue;
		modificationType = c.modificationType;

		addSerializableVariables();
	}

	CustomizationData& operator=(const CustomizationData& c) {
		if (this == &c)
			return *this;

		speciesGender = c.speciesGender;
		customizationGroup = c.customizationGroup;
		type = c.type;
		customizationName = c.customizationName;
		variables = c.variables;
		isScale = c.isScale;
		reverse = c.reverse;
		colorLinked = c.colorLinked;
		colorLinkedtoSelf0 = c.colorLinkedtoSelf0;
		colorLinkedtoSelf1 = c.colorLinkedtoSelf1;
		cameraYaw = c.cameraYaw;
		discrete = c.discrete;
		randomizable = c.randomizable;
		randomizableGroup = c.randomizableGroup;
		isVarHairColor = c.isVarHairColor;
		imageDesignSkillMod = c.imageDesignSkillMod;
		skillModValue = c.skillModValue;
		modificationType = c.modificationType;

		return *this;
	}

	inline void addSerializableVariables() {
		addSerializableVariable("speciesGender", &speciesGender);
		addSerializableVariable("customizationGroup", &customizationGroup);
		addSerializableVariable("type", &type);
		addSerializableVariable("customizationName", &customizationName);
		addSerializableVariable("isScale", &isScale);
		addSerializableVariable("reverse", &reverse);
		addSerializableVariable("colorLinked", &colorLinked);
		addSerializableVariable("colorLinkedtoSelf0", &colorLinkedtoSelf0);
		addSerializableVariable("colorLinkedtoSelf1", &colorLinkedtoSelf1);
		addSerializableVariable("cameraYaw", &cameraYaw);
		addSerializableVariable("discrete", &discrete);
		addSerializableVariable("randomizable", &randomizable);
		addSerializableVariable("randomizableGroup", &randomizableGroup);
		addSerializableVariable("isVarHairColor", &isVarHairColor);
		addSerializableVariable("imageDesignSkillMod", &imageDesignSkillMod);
		addSerializableVariable("skillModValue", &skillModValue);
		addSerializableVariable("modificationType", &modificationType);
	}

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
};

#endif /* CUSTOMIZATIONDATA_H_ */
