/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "ImageDesignManager.h"
#include "templates/customization/CustomizationIdManager.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/ZoneServer.h"
#include "templates/manager/TemplateManager.h"
#include "templates/creature/PlayerCreatureTemplate.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"
#include "templates/customization/BasicRangedIntCustomizationVariable.h"

ImageDesignManager::ImageDesignManager() {
	setLoggingName("ImageDesignManager");

	loadCustomizationData();
}

void ImageDesignManager::updateCustomization(CreatureObject* imageDesigner, CustomizationData* customData, float value, CreatureObject* creo) {
	if (creo == NULL || value < 0 || value > 1)
		return;

	ManagedReference<CreatureObject*> creatureObject = creo;

	String variables = customData->getVariables();
	String type = customData->getType();

	String skillMod = customData->getImageDesignSkillMod();

	if (imageDesigner->getSkillMod(skillMod) < customData->getSkillModValue())
		return;

	if (customData->getIsScale()) {
		float minScale = customData->getMinScale();
		float maxScale = customData->getMaxScale();

		float height = minScale + value * (maxScale - minScale);

		creatureObject->setHeight(Math::max(Math::min(height, maxScale), minScale));

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

					// pre: i � [0, 1] && value � [0, 1]
					// post f � [0, 1]
					currentValue = Math::max(0.f, ((value - 0.5f) * 2.f) * (-1.f + (i * 2.f)));
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

void ImageDesignManager::updateCustomization(CreatureObject* imageDesigner, const String& customizationName, float value, CreatureObject* creo) {
	if (creo == NULL || value < 0 || value > 1)
		return;

	String speciesGender = getSpeciesGenderString(creo);

	Vector<CustomizationData>* data = getCustomizationData(speciesGender, customizationName);

	if (data == NULL) {
		error("Unable to get CustomizationData for " + speciesGender + "_" + customizationName);
		return;
	}

	for (int i = 0; i < data->size(); ++i) {
		CustomizationData* customData = &data->get(i);

		updateCustomization(imageDesigner, customData, value, creo);
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

				Locker locker(tano);
				tano->setCustomizationVariable(fullVariableNameLimit, currentVal, true);

				//info("setting " + fullVariableNameLimit + " to " + String::valueOf(currentVal), true);
			}
		}
	}
}

void ImageDesignManager::updateColorCustomization(CreatureObject* imageDesigner, CustomizationData* customData, uint32 value, TangibleObject* hairObject, CreatureObject* creo) {
	if (value > 255 || creo == NULL)
		return;

	ManagedReference<CreatureObject*> creatureObject = creo;

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

void ImageDesignManager::updateColorCustomization(CreatureObject* imageDesigner, const String& customizationName, uint32 value, TangibleObject* hairObject, CreatureObject* creo) {
	if (value > 255 || creo == NULL)
		return;

	String speciesGender = getSpeciesGenderString(creo);

	Vector<CustomizationData>* data = getCustomizationData(speciesGender, customizationName);

	if (data == NULL) {
		error("Unable to get CustomizationData for " + speciesGender + "_" + customizationName);
		return;
	}

	for (int i = 0; i < data->size(); ++i) {
		CustomizationData* customData = &data->get(i);
		updateColorCustomization(imageDesigner, customData, value, hairObject, creo);
	}
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
		uint32 templateCRC = String::hashCode("object/creature/player/" + speciesGender + ".iff");
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

		if (!dataMap->contains(customizationData.getCustomizationName()))
			dataMap->put(customizationData.getCustomizationName(), Vector<CustomizationData>());

		Vector<CustomizationData> &records = dataMap->get(customizationData.getCustomizationName());

		records.add(customizationData);
	}

	//Done with the stream, so delete it.
	if (iffStream != NULL) {
		delete iffStream;
		iffStream = NULL;
	}

}

Vector<CustomizationData>* ImageDesignManager::getCustomizationData(const String& speciesGender, const String& customizationName) {
	TemplateManager* templateManager = TemplateManager::instance();

	uint32 templateCRC = String::hashCode("object/creature/player/" + speciesGender + ".iff");

	PlayerCreatureTemplate* tmpl = dynamic_cast<PlayerCreatureTemplate*>(templateManager->getTemplate(templateCRC));

	if (tmpl == NULL)
		return NULL;

	return tmpl->getCustomizationData(customizationName);
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
	Reference<TangibleObject*> oldHair = targetObject->getSlottedObject("hair").castTo<TangibleObject*>();

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
	if (hair == NULL || !hair->isTangibleObject()) {
		if (hair != NULL) {
			Locker locker(hair);
			hair->destroyObjectFromDatabase(true);
		}

		return oldHair;
	}

	TangibleObject* tanoHair = cast<TangibleObject*>( hair.get());

	Locker locker(tanoHair);

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

	ManagedReference<TangibleObject*> hair = creo->getSlottedObject("hair").castTo<TangibleObject*>();

	if (hair == hairObject) {
		return hairObject;
	}

	if (hair != NULL) {
		Locker locker(hair);
		hair->destroyObjectFromWorld(true);
		hair->destroyObjectFromDatabase(true);
	}

	if (hairObject == NULL)
		return NULL;

	// Some race condition in the client prevents both the destroy and transfer from happening too close together
	// Without it placing a hair object in the inventory.
	ManagedReference<CreatureObject*> strongCreo = creo;
	ManagedReference<TangibleObject*> strongHair = hairObject;
	Core::getTaskManager()->scheduleTask([strongCreo, strongHair]{
		Locker locker(strongCreo);
		Locker cLocker(strongCreo, strongHair);
		strongCreo->transferObject(strongHair, 4);
		strongCreo->broadcastObject(strongHair, true);
	}, "TransferHairTask", 100);

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
