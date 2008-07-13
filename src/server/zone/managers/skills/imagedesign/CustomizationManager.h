/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/

#ifndef CUSTOMIZATIONMANAGER_H_
#define CUSTOMIZATIONMANAGER_H_

#include "engine/engine.h"

#include "../../../ZoneServer.h"
#include "../../../ZoneProcessServerImplementation.h"


class CustomizationData {
	string speciesGender;
	string customizationGroup;
	string type;
	string customizationName;
	string variables;
	bool isScale;
	bool reverse;
	string colorLinked;
	string colorLinkedtoSelf0;
	string colorLinkedtoSelf1;
	int cameraYaw;
	bool discrete;
	bool randomizable;
	bool randomizableGroup;
	bool isVarHairColor;
	string imageDesignSkillMod;
	int skillModValue;
	string modificationType;
	int maxChoices;
	float minScale;
	float maxScale;
public:
	// setters
	inline void setSpeciesGender(string value) {
		speciesGender = value;
	}
	inline void setCustomizationGroup(string value) {
		customizationGroup = value;
	}
	inline void setType(string value) {
		type = value;
	}
	inline void setCustomizationName(string value) {
		customizationName = value;
	}
	inline void setVariables(string value) {
		variables = value;
	}
	inline void setIsScale(bool value) {
		isScale = value;
	}
	inline void setReverse(bool value) {
		reverse = value;
	}
	inline void setColorLinked(string value) {
		colorLinked = value;
	}
	inline void setColorLinkedtoSelf0(string value) {
		colorLinkedtoSelf0 = value;
	}
	inline void setColorLinkedtoSelf1(string value) {
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
	inline void setImageDesignSkillMod(string value) {
		imageDesignSkillMod = value;
	}
	inline void setSkillModValue(int value) {
		skillModValue = value;
	}
	inline void setModificationType(string value) {
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

	// getters
	inline string getSpeciesGender() {
		return speciesGender;
	}
	inline string getCustomizationGroup() {
		return customizationGroup;
	}
	inline string getType() {
		return type;
	}
	inline string getCustomizationName() {
		return customizationName;
	}
	inline string getVariables() {
		return variables;
	}
	inline bool getIsScale() {
		return isScale;
	}
	inline bool getReverse() {
		return reverse;
	}
	inline string getColorLinked() {
		return colorLinked;
	}
	inline string getColorLinkedtoSelf0() {
		return colorLinkedtoSelf0;
	}
	inline string getColorLinkedtoSelf1() {
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
	inline string getImageDesignSkillMod() {
		return imageDesignSkillMod;
	}
	inline int getSkillModValue() {
		return skillModValue;
	}
	inline string getModificationType() {
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


class CustomizationManager {
	
	VectorMap<string, CustomizationData*> customizations;
	int loadedCount;
	void loadCustomizationData();

public:
	CustomizationManager();
	
	~CustomizationManager();
	
	CustomizationData* getCustomizationData(string speciesGender, string customizationName);
	
};
#endif /*CUSTOMIZATIONMANAGER_H_*/
