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

#include "ImageDesignManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/customization/CustomizationIdManager.h"
#include "server/db/ServerDatabase.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage3.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/templates/tangible/PlayerCreatureTemplate.h"
#include "server/zone/templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/templates/customization/BasicRangedIntCustomizationVariable.h"


ImageDesignManager::ImageDesignManager() {
	setLoggingName("ImageDesignManager");

	loadCustomizationData();
}

void ImageDesignManager::updateCustomization(CreatureObject* imageDesigner, const String& customizationName, float value, CreatureObject* creo) {
	if (creo == NULL)
		return;

	if (value < 0 || value > 1)
		return;

	String speciesGender = getSpeciesGenderString(creo);

	ManagedReference<CreatureObject*> creatureObject = creo;

	CustomizationData* customData = getCustomizationData(speciesGender, customizationName);

	if (customData == NULL) {
		//System::out << "Unable to get CustomizationData for " + speciesGender + "_" + customizationName << endl;
		return;
	}

	String variables = customData->getVariables();
	String type = customData->getType();

	String skillMod = customData->getImageDesignSkillMod();

	if (imageDesigner->getSkillMod(skillMod) < customData->getSkillModValue())
		return;

	if (customData->getIsScale()) {
		float minScale = customData->getMinScale();
		float maxScale = customData->getMaxScale();

		float height = minScale + value * (maxScale - minScale);

		creatureObject->setHeight(MAX(MIN(height, maxScale), minScale));

		return;
	}

	Vector<String> fullVariables;
	StringTokenizer tokenizer(variables);
	tokenizer.setDelimeter(",");

	while (tokenizer.hasMoreTokens()) {
		String var;
		tokenizer.getStringToken(var);

		fullVariables.add(var);
	}

	String appearanceFilename = creo->getObjectTemplate()->getAppearanceFilename();

	VectorMap<String, Reference<CustomizationVariable*> > variableLimits;

	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variableLimits, false);

	for (int i = 0; i < fullVariables.size(); ++i) {
		String var = fullVariables.get(i);

		for (int j = 0; j < variableLimits.size(); ++j) {
			String fullVariableNameLimit = variableLimits.elementAt(j).getKey();

			if (fullVariableNameLimit.contains(var)) {
				BasicRangedIntCustomizationVariable* ranged = dynamic_cast<BasicRangedIntCustomizationVariable*>(variableLimits.elementAt(j).getValue().get());

				if (ranged == NULL) {
					error("variable " + fullVariableNameLimit + " is not ranged");

					continue;
				}

				int min = ranged->getMinValueInclusive();
				int max = ranged->getMaxValueExclusive();

				int count = max - min;

				int setVal;

				float currentValue = value;

				if (fullVariables.size() > 1) {
					// examples for var count = 2
					// ex: received value 0 is for i == 0 -> 1.0, i == 1 -> 0.0
					// ex: received value 0.5 is for i == 0 -> 0.0, i == 1 -> 0.0
					// ex: received value 1 is for i == 0 -> 0.0, i == 1 -> 1.0

					// pre: i Û [0, 1] && value Û [0, 1]
					// post f Û [0, 1]
					currentValue = MAX(0, ((value - 0.5) * 2) * (-1 + (i * 2)));
				}

				if (customData->getReverse()) {
					setVal = float(max - 1) - currentValue * (float(count) - 1);
				} else {
					setVal = float(min) + currentValue * (float(count) - 1);
				}

				creatureObject->setCustomizationVariable(fullVariableNameLimit, setVal, true);

				//info("setting " + fullVariableNameLimit + " to " + String::valueOf(setVal), true);
			}
		}
	}

}

void ImageDesignManager::updateColorVariable(const Vector<String>& fullVariables, uint32 value, TangibleObject* tano, int skillLevel) {
	String appearanceFilename = tano->getObjectTemplate()->getAppearanceFilename();

	VectorMap<String, Reference<CustomizationVariable*> > variableLimits;

	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variableLimits, false);

	for (int i = 0; i < fullVariables.size(); ++i) {
		String var = fullVariables.get(i);

		for (int j = 0; j < variableLimits.size(); ++j) {
			String fullVariableNameLimit = variableLimits.elementAt(j).getKey();

			//info("checking customization variable " + fullVariableNameLimit + " for " + var, true);

			if (fullVariableNameLimit.contains(var)) {
				BasicRangedIntCustomizationVariable* ranged = dynamic_cast<BasicRangedIntCustomizationVariable*>(variableLimits.elementAt(j).getValue().get());
				PaletteColorCustomizationVariable* palette = NULL;
				uint32 currentVal = value;

				if (ranged != NULL) {
					int min = ranged->getMinValueInclusive();
					int max = ranged->getMaxValueExclusive();

					if (value < min)
						currentVal = min;

					if (value >= max)
						currentVal = max - 1;
				} else {
					palette = dynamic_cast<PaletteColorCustomizationVariable*>(variableLimits.elementAt(j).getValue().get());

					if (palette != NULL) {
						if (!validatePalette(palette, currentVal, skillLevel))
							currentVal = palette->getDefaultValue();
					}
				}

				tano->setCustomizationVariable(fullVariableNameLimit, currentVal, true);

				//info("setting " + fullVariableNameLimit + " to " + String::valueOf(currentVal), true);
			}
		}
	}
}

void ImageDesignManager::updateColorCustomization(CreatureObject* imageDesigner, const String& customizationName, uint32 value, TangibleObject* hairObject, CreatureObject* creo) {
	if (value > 255 || creo == NULL)
		return;

	String speciesGender = getSpeciesGenderString(creo);

	ManagedReference<CreatureObject*> creatureObject = creo;

	CustomizationData* customData = getCustomizationData(speciesGender, customizationName);

	if (customData == NULL) {
		//System::out << "Unable to get CustomizationData for " + speciesGender + "_" + customizationName << endl;
		return;
	}

	String skillMod = customData->getImageDesignSkillMod();

	if (imageDesigner->getSkillMod(skillMod) < customData->getSkillModValue())
		return;

	String variables = customData->getVariables();
	String type = customData->getType();

	TangibleObject* objectToUpdate = creo;

	if (customData->getIsVarHairColor()) {
		objectToUpdate = hairObject;
	}

	if (objectToUpdate == NULL)
		return;

	Vector<String> fullVariables;
	StringTokenizer tokenizer(variables);
	tokenizer.setDelimeter(",");

	while (tokenizer.hasMoreTokens()) {
		String var;
		tokenizer.getStringToken(var);

		fullVariables.add(var);
	}

	int skillLevel = getSkillLevel(imageDesigner, skillMod);

	updateColorVariable(fullVariables, value, objectToUpdate, skillLevel);
}

int ImageDesignManager::getSkillLevel(CreatureObject* imageDesigner, const String& skillMod) {
	if (imageDesigner->hasSkill("social_imagedesigner_master")) {
		return 5;
	}

	String skillName = "social_imagedesigner_";

	if (skillMod == "body")
		skillName += "bodyform_0";
	else if (skillMod == "face")
		skillName += "exotic_0";
	else if (skillMod == "hair")
		skillName += "hairstyle_0";
	else {
		skillName += skillMod;
		skillName += "_0";
	}

	//info("testing for " + skillName, true);

	for (int i = 4; i >= 1; --i) {
		String testName = skillName + String::valueOf(i);

		//info("testing for " + testName, true);

		if (imageDesigner->hasSkill(testName)) {
			return i;
		}
	}

	if (imageDesigner->hasSkill("social_imagedesigner_novice")) {
		return 0;
	}

	return -1;
}

void ImageDesignManager::loadCustomizationData() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("datatables/customization/customization_data.iff");

	if (iffStream == NULL)
		return;

	//Get the datatable, and parse it into a datatable object.
	DataTableIff dataTable;
	dataTable.readObject(iffStream);

	for (int i = 0; i < dataTable.getTotalRows(); i++) {
		DataTableRow* dataRow = dataTable.getRow(i);

		if (dataRow == NULL)
			continue;

		//Get the species gender
		String speciesGender = dataRow->getCell(0)->toString();
		uint32 templateCRC = String("object/creature/player/" + speciesGender + ".iff").hashCode();
		PlayerCreatureTemplate* tmpl = dynamic_cast<PlayerCreatureTemplate*>(templateManager->getTemplate(templateCRC));

		if (tmpl == NULL)
			continue;

		CustomizationDataMap* dataMap = tmpl->getCustomizationDataMap();

		if (dataMap == NULL)
			continue;

		CustomizationData customizationData;
		customizationData.parseRow(dataRow);

		customizationData.setMinScale(tmpl->getMinScale());
		customizationData.setMaxScale(tmpl->getMaxScale());

		dataMap->put(customizationData.getCustomizationName(), customizationData);

	}

	//Done with the stream, so delete it.
	if (iffStream != NULL) {
		delete iffStream;
		iffStream = NULL;
	}

}

CustomizationData* ImageDesignManager::getCustomizationData(const String& speciesGender, const String& customizationName) {
	TemplateManager* templateManager = TemplateManager::instance();

	uint32 templateCRC = String("object/creature/player/" + speciesGender + ".iff").hashCode();

	PlayerCreatureTemplate* tmpl = dynamic_cast<PlayerCreatureTemplate*>(templateManager->getTemplate(templateCRC));
	CustomizationData* customization = tmpl->getCustomizationData(customizationName);

	if (customization == NULL)
		return NULL;

	return customization;
}

String ImageDesignManager::getSpeciesGenderString(CreatureObject* creo) {
	if (creo == NULL)
		return "unknown";

	int gender = creo->getGender();
	String genderString;
	if (gender == 0)
		genderString = "male";
	else if (gender == 1)
		genderString = "female";
	else
		return "unknown";

	return creo->getSpeciesName() + "_" + genderString;
}

TangibleObject* ImageDesignManager::createHairObject(CreatureObject* imageDesigner, CreatureObject* targetObject, const String& hairTemplate, const String& hairCustomization) {
	TangibleObject* oldHair = dynamic_cast<TangibleObject*>(targetObject->getSlottedObject("hair"));

	HairAssetData* hairAssetData = CustomizationIdManager::instance()->getHairAssetData(hairTemplate);

	if (hairTemplate.isEmpty()) {
		if (!CustomizationIdManager::instance()->canBeBald(getSpeciesGenderString(targetObject)))
			return oldHair;
		else
			return NULL;
	}

	if (hairAssetData == NULL)
		return oldHair;

	int skillMod = hairAssetData->getSkillModValue();

	if (imageDesigner->getSkillMod("hair") < skillMod)
		return oldHair;

	if (hairAssetData->getServerPlayerTemplate() != targetObject->getObjectTemplate()->getFullTemplateString()) {
		error("hair " + hairTemplate + " is not compatible with this creature player " + targetObject->getObjectTemplate()->getFullTemplateString());
		return oldHair;
	}

	ManagedReference<SceneObject*> hair = imageDesigner->getZoneServer()->createObject(hairTemplate.hashCode(), 1);

	//TODO: Validate hairCustomization
	if (hair == NULL || !hair->isTangibleObject())
		return oldHair;

	TangibleObject* tanoHair = cast<TangibleObject*>( hair.get());
	tanoHair->setContainerDenyPermission("owner", ContainerPermissions::MOVECONTAINER);
	tanoHair->setContainerDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);

	String appearanceFilename = tanoHair->getObjectTemplate()->getAppearanceFilename();

	CustomizationVariables data;

	data.parseFromClientString(hairCustomization);

	if (validateCustomizationString(&data, appearanceFilename, getSkillLevel(imageDesigner, "hair")))
		tanoHair->setCustomizationString(hairCustomization);

	return tanoHair;
}

TangibleObject* ImageDesignManager::updateHairObject(CreatureObject* creo, TangibleObject* hairObject) {
	if (creo == NULL)
		return NULL;

	ManagedReference<TangibleObject*> hair = cast<TangibleObject*>( creo->getSlottedObject("hair"));

	if (hair != NULL) {
		hair->destroyObjectFromWorld(true);
	}

	if (hairObject == NULL)
		return NULL;

	creo->transferObject(hairObject, 4);
	creo->broadcastObject(hairObject, true);

	return hair;
}

bool ImageDesignManager::validatePalette(PaletteColorCustomizationVariable* palette, int value, int skillLevel) {
	String paletteFileName = palette->getPaletteFileName();
	int idx = paletteFileName.lastIndexOf("/");

	if (idx != -1) {
		String paletteName = paletteFileName.subString(idx + 1);
		paletteName = paletteName.subString(0, paletteName.indexOf("."));

		//info("palette name = " + paletteName, true);

		PaletteData* data = CustomizationIdManager::instance()->getPaletteData(paletteName);

		if (data == NULL) {
			//error("could not find palette data for " + paletteName);
		} else {
			int maxIndex;

			switch (skillLevel) {
			case -1:
				maxIndex = data->getCreationIndexes();
				break;
			case 0:
				maxIndex = data->getIdNoviceIndexes();
				break;
			case 1:
				maxIndex = data->getIdLevel1Indexes();
				break;
			case 2:
				maxIndex = data->getIdLevel2Indexes();
				break;
			case 3:
				maxIndex = data->getIdLevel3Indexes();
				break;
			case 4:
				maxIndex = data->getIdLevel4Indexes();
				break;
			case 5:
				maxIndex = data->getIdMasterIndexes();
				break;
			default:
				maxIndex = -1;
				break;
			}

			if (value >= maxIndex || value < 0) {
				instance()->error("value for " + paletteFileName + " value " + value + " outside bound " + String::valueOf(maxIndex));

				return false;
			} else {
				//info(name + " value " + String::valueOf(val) + " inside bound " + String::valueOf(maxIndex) + " for " + name , true);
			}
		}
	}

	return true;
}

bool ImageDesignManager::validateCustomizationString(CustomizationVariables* data, const String& appearanceFilename, int skillLevel) {
	VectorMap<String, Reference<CustomizationVariable*> > variables;
	variables.setNullValue(NULL);
	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, false);

	if (variables.size() == 0) {
		instance()->error("no customization data found for " + appearanceFilename);
		return false;
	}

	for (int i = 0; i < data->size(); ++i) {
		uint8 id = data->elementAt(i).getKey();
		int16 val = data->elementAt(i).getValue();

		String name = CustomizationIdManager::instance()->getCustomizationVariable(id);

		//instance()->info("validating " + name + " with value " + String::valueOf(val), true);

		CustomizationVariable* customizationVariable = variables.get(name).get();

		if (customizationVariable == NULL) {
			instance()->error("customization variable id " + String::valueOf(id) + " not found in the appearance file " + appearanceFilename + " with value " + String::valueOf(val));

			continue;
		}

		PaletteColorCustomizationVariable* palette = dynamic_cast<PaletteColorCustomizationVariable*>(customizationVariable);

		if (palette != NULL) {
			if (!validatePalette(palette, val, skillLevel))
				return false;
		} else {
			BasicRangedIntCustomizationVariable* range = dynamic_cast<BasicRangedIntCustomizationVariable*>(customizationVariable);

			if (range == NULL) {
				instance()->error("unkown customization variable type " + name);
				return false;
			} else {
				int maxExcl = range->getMaxValueExclusive();
				int minIncl = range->getMinValueInclusive();

				if (val >= maxExcl || val < minIncl) {
					instance()->error("variable outside bounds " + name + " value " + val + " outside bounds [" + String::valueOf(minIncl) + "," + String::valueOf(maxExcl) + ")");

					return false;
				} else {
					//instance()->info("variable " + name + " value " + String::valueOf(val) + " inside bounds [" + String::valueOf(minIncl) + "," + String::valueOf(maxExcl) + ")", true);
				}

			}
		}


		//info("setting variable:" + name + " to " + String::valueOf(val), true);
	}

	return true;
}

ImageDesignManager::~ImageDesignManager() {
}
