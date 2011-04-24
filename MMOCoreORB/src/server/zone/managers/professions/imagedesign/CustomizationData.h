/*
 * CustomizationData.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef CUSTOMIZATIONDATA_H_
#define CUSTOMIZATIONDATA_H_

#include "engine/engine.h"
#include "server/zone/templates/datatables/DataTableRow.h"

class CustomizationData : public Object {
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
		} catch (Exception& e) {
			System::out << "CustomizationData::parse() exception: " << e.getMessage() << endl;
		}
	}

	inline String& getCustomizationGroup() {
		return customizationGroup;
	}

	inline String& getType() {
		return type;
	}

	inline String& getCustomizationName() {
		return customizationName;
	}

	inline String& getVariables() {
		return variables;
	}

	inline bool getIsScale() {
		return isScale;
	}

	inline bool getReverse() {
		return reverse;
	}

	inline String& getColorLinked() {
		return colorLinked;
	}

	inline String& getColorLinkedtoSelf0() {
		return colorLinkedtoSelf0;
	}

	inline String& getColorLinkedtoSelf1() {
		return colorLinkedtoSelf1;
	}

	inline float getCameraYaw() {
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

	inline String& getImageDesignSkillMod() {
		return imageDesignSkillMod;
	}

	inline int getSkillModValue() {
		return skillModValue;
	}

	inline String& getModificationType() {
		return modificationType;
	}

	inline bool isPhysicalModificationType() {
		return (modificationType == "physical");
	}

	inline bool isCosmeticModificationType() {
		return (modificationType == "cosmetic");
	}

	inline bool isHorizontalSlider() {
		return (type == "hslider");
	}

	inline bool isColorPicker() {
		return (type == "color");
	}

	inline float getMinScale() {
		return minScale;
	}

	inline float getMaxScale() {
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
