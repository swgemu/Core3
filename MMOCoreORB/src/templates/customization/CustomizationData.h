/*
 * CustomizationData.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef CUSTOMIZATIONDATA_H_
#define CUSTOMIZATIONDATA_H_

#include "templates/datatables/DataTableRow.h"

class CustomizationData : public Object {
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
	float cameraYaw;
	bool discrete;
	bool randomizable;
	bool randomizableGroup;
	bool isVarHairColor;
	String imageDesignSkillMod;
	int skillModValue;
	String modificationType;
	float minScale;
	float maxScale;

public:
	CustomizationData() {
		isScale = false;
		reverse = false;
		cameraYaw = 0.f;
		discrete = false;
		randomizable = false;
		randomizableGroup = false;
		isVarHairColor = false;
		skillModValue = 0;
		minScale = 0.f;
		maxScale = 0.f;
	}

	CustomizationData(const CustomizationData& c) :	Object() {
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
		minScale = c.minScale;
		maxScale = c.maxScale;
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
		minScale = c.minScale;
		maxScale = c.maxScale;

		return *this;
	}

	void parseRow(DataTableRow* row) {
		try {
			row->getValue(0, speciesGender);
			row->getValue(1, customizationGroup);
			row->getValue(2, type);
			row->getValue(3, customizationName);
			row->getValue(4, variables);
			row->getValue(5, isScale);
			row->getValue(6, reverse);
			row->getValue(7, colorLinked);
			row->getValue(8, colorLinkedtoSelf0);
			row->getValue(9, colorLinkedtoSelf1);
			row->getValue(10, cameraYaw);
			row->getValue(11, discrete);
			row->getValue(12, randomizable);
			row->getValue(13, randomizableGroup);
			row->getValue(14, isVarHairColor);
			row->getValue(15, imageDesignSkillMod);
			row->getValue(16, skillModValue);
			row->getValue(17, modificationType);
		} catch (const Exception& e) {
			System::err << "CustomizationData::parse() exception: " << e.getMessage() << endl;
		}
	}

	inline const String& getCustomizationGroup() const {
		return customizationGroup;
	}

	inline const String& getType() const {
		return type;
	}

	inline const String& getCustomizationName() const {
		return customizationName;
	}

	inline const String& getVariables() const {
		return variables;
	}

	inline bool getIsScale() const {
		return isScale;
	}

	inline bool getReverse() const {
		return reverse;
	}

	inline const String& getColorLinked() const {
		return colorLinked;
	}

	inline const String& getColorLinkedtoSelf0() const {
		return colorLinkedtoSelf0;
	}

	inline const String& getColorLinkedtoSelf1() const {
		return colorLinkedtoSelf1;
	}

	inline float getCameraYaw() const {
		return cameraYaw;
	}

	inline bool getDiscrete() const {
		return discrete;
	}

	inline bool getRandomizable() const {
		return randomizable;
	}

	inline bool getRandomizableGroup() const {
		return randomizableGroup;
	}

	inline bool getIsVarHairColor() const {
		return isVarHairColor;
	}

	inline const String& getImageDesignSkillMod() const {
		return imageDesignSkillMod;
	}

	inline int getSkillModValue() const {
		return skillModValue;
	}

	inline const String& getModificationType() const {
		return modificationType;
	}

	inline bool isPhysicalModificationType() const {
		return (modificationType == "physical");
	}

	inline bool isCosmeticModificationType() const {
		return (modificationType == "cosmetic");
	}

	inline bool isHorizontalSlider() const {
		return (type == "hslider");
	}

	inline bool isColorPicker() const {
		return (type == "color");
	}

	inline float getMinScale() const {
		return minScale;
	}

	inline float getMaxScale() const {
		return maxScale;
	}

	inline void setMinScale(float min) {
		minScale = min;
	}

	inline void setMaxScale(float max) {
		maxScale = max;
	}

};

#endif /* CUSTOMIZATIONDATA_H_ */
