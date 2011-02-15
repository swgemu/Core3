/*
 * CustomizationData.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef CUSTOMIZATIONDATA_H_
#define CUSTOMIZATIONDATA_H_

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
		modificationType = 0;
	}

	CustomizationData(DataTableRow* row) {
		try {
			row->getCell(0);
		} catch (Exception& e) {
			System::out << "CustomizationData() exception: " << e.getMessage() << endl;
		}
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

		return *this;
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

	inline String& getImageDesignSkillMod() {
		return imageDesignSkillMod;
	}

	inline int getSkillModValue() {
		return skillModValue;
	}

	inline String& getModificationType() {
		return modificationType;
	}
};

#endif /* CUSTOMIZATIONDATA_H_ */
