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
			//Skip cell 0. We don't need to store it.
			row->getCell(1)->getValue(customizationGroup);
			row->getCell(2)->getValue(type);
			row->getCell(3)->getValue(customizationName);
			row->getCell(4)->getValue(variables);
			row->getCell(5)->getValue(isScale);
			row->getCell(6)->getValue(reverse);
			row->getCell(7)->getValue(colorLinked);
			row->getCell(8)->getValue(colorLinkedtoSelf0);
			row->getCell(9)->getValue(colorLinkedtoSelf1);
			row->getCell(10)->getValue(cameraYaw);
			row->getCell(11)->getValue(discrete);
			row->getCell(12)->getValue(randomizable);
			row->getCell(13)->getValue(randomizableGroup);
			row->getCell(14)->getValue(isVarHairColor);
			row->getCell(15)->getValue(imageDesignSkillMod);
			row->getCell(16)->getValue(skillModValue);
			row->getCell(17)->getValue(modificationType);
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
