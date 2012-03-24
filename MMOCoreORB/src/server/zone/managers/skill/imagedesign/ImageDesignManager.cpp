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
#include "server/db/ServerDatabase.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage3.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/templates/tangible/PlayerCreatureTemplate.h"

ImageDesignManager::ImageDesignManager() {
	loadCustomizationData();
}

void ImageDesignManager::updateCustomization(const String& customizationName, float value, String& hairTemplate, CreatureObject* creo) {
	if (creo == NULL)
		return;

	if (value < 0 || value > 1)
		return;

	String speciesGender = getSpeciesGenderString(creo);

	ManagedReference<CreatureObject*> creatureObject = creo;

	CustomizationData* customData = getCustomizationData(speciesGender, customizationName);

	CustomizationVariables hairCustomization;

	String hairCustomizationString;

	if (customData == NULL) {
		//System::out << "Unable to get CustomizationData for " + speciesGender + "_" + customizationName << endl;
		return;
	}

	String variables = customData->getVariables();
	String type = customData->getType();
	//int choices = customData->getMaxChoices();

	if (type == "hslider") {

		if (customizationName == "brow" ||
			customizationName == "cheeks" ||
			customizationName == "chest" ||
			customizationName == "chin" ||
			customizationName == "chin_length" ||
			customizationName == "ear_shape" ||
			customizationName == "ears" ||
			customizationName == "eye_direction" ||
			customizationName == "eye_shape" ||
			customizationName == "eye_size" ||
			customizationName == "gullet" ||
			customizationName == "head" ||
			customizationName == "head_shape" ||
			customizationName == "head_size" ||
			customizationName == "hump_size" ||
			customizationName == "jaw" ||
			customizationName == "jowl" ||
			customizationName == "lip_fullness" ||
			customizationName == "lip_width" ||
			customizationName == "muscle" ||
			customizationName == "nose_length" ||
			customizationName == "nose_protrusion" ||
			customizationName == "nose_width" ||
			customizationName == "sensors" ||
			customizationName == "trunk_height"	||
			customizationName == "trunk_length" ||
			customizationName == "trunk_size" ||
			customizationName == "trunk_slope" ||
			customizationName == "weight") {

			String token_1 = "";
			String token_2 = "";

			StringTokenizer tokenizer(variables.toCharArray());
			tokenizer.setDelimeter(",");

			tokenizer.getStringToken(token_1);
			if (tokenizer.hasMoreTokens())
				tokenizer.getStringToken(token_2);
			//System::out << token_1 << "   " << token_2 << endl;
			if (token_2 == "") {
				if (customData->getIsVarHairColor())
					hairCustomization.setVariable(token_1, (value * 255));
				else
					creatureObject->setCustomizationVariable(token_1, (value * 255));
			} else {
				  if (value >= .5) {
					creatureObject->setCustomizationVariable(token_1, (((value - .5f) / .5f) * 255));
					creatureObject->setCustomizationVariable(token_2, 0);
				} else { // value < .5
					creatureObject->setCustomizationVariable(token_1, 0);
					creatureObject->setCustomizationVariable(token_2, (((value - .5f) / .5f) * 255));

				}

			}

		} else if (customizationName == "height") {

			float minScale = customData->getMinScale();
			float maxScale = customData->getMaxScale();


			creatureObject->setHeight(MAX(MIN(value, maxScale), minScale));

		} else if (

		customizationName == "age" ||
		customizationName == "beard" ||
		customizationName == "center_beard" ||
		customizationName == "eyebrows"	||
		customizationName == "eyeshadow" ||
		customizationName == "freckles" ||
		customizationName == "fur_pattern" ||
		customizationName == "side_beard" ||
		customizationName == "tattoo_style") {

			StringTokenizer tokenizer(variables.toCharArray());
			tokenizer.setDelimeter(",");

			while (tokenizer.hasMoreTokens()) {
				String attribute;
				tokenizer.getStringToken(attribute);
				creatureObject->setCustomizationVariable(attribute, value);
			}

		}
		hairCustomization.getData(hairCustomizationString);
		updateHairObject(creatureObject, hairTemplate, hairCustomizationString);

		updateCharacterAppearance(creatureObject);

	} else

		hairCustomization.getData(hairCustomizationString);
		updateHairObject(creatureObject, hairTemplate, hairCustomizationString);

		updateCharacterAppearance(creatureObject);
}

void ImageDesignManager::updateCustomization(const String& customizationName, uint32 value, String& hairTemplate, CreatureObject* creo) {
	if (value > 255 || creo == NULL)
		return;

	String speciesGender = getSpeciesGenderString(creo);

	ManagedReference<CreatureObject*> creatureObject = creo;

	CustomizationData* customData = getCustomizationData(speciesGender, customizationName);

	CustomizationVariables hairCustomization;

	if (customData == NULL) {
		//System::out << "Unable to get CustomizationData for " + speciesGender + "_" + customizationName << endl;
		return;
	}

	String variables = customData->getVariables();
	String type = customData->getType();
		if (type == "color"){
		if (
			customizationName == "hair_color" ||
			customizationName == "lekku_color" ||
			customizationName == "horns_color" ||
			customizationName == "hair_trim_color"){
		StringTokenizer tokenizer(variables.toCharArray());
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String attribute;
			tokenizer.getStringToken(attribute);
			hairCustomization.setVariable(attribute,value);
		}

		String hairCustomizationString;
		hairCustomization.getData(hairCustomizationString);
		updateHairObject(creatureObject, hairTemplate, hairCustomizationString);

		updateCharacterAppearance(creatureObject);
		}

		else if(
				customizationName == "eye_color" ||
				customizationName == "eyebrows_color" ||
				customizationName == "facial_hair_color" ||
				customizationName == "fur_color_bothan" ||
				customizationName == "skin_color" ||
				customizationName == "fur_color_wookiee" ||
				customizationName == "nose_color"){

			StringTokenizer tokenizer(variables.toCharArray());
			tokenizer.setDelimeter(",");

			while (tokenizer.hasMoreTokens()) {
				String attribute;
				tokenizer.getStringToken(attribute);
				creatureObject->setCustomizationVariable(attribute, value);
			}

		updateCharacterAppearance(creatureObject);
		}

	} else if (type == "hslider") {
		updateCustomization(customizationName, (float) value, hairTemplate, creo);
		return;

	} else {
		String hairCustomizationString;
		hairCustomization.getData(hairCustomizationString);
		updateHairObject(creatureObject, hairTemplate, hairCustomizationString);

		updateCharacterAppearance(creatureObject);
	}
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

void ImageDesignManager::updateCharacterAppearance(CreatureObject* creo) {
	if (creo == NULL)
		return;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(creo);
	dcreo3->updateCharacterAppearance();
	dcreo3->updateHeight();
	dcreo3->close();
	creo->broadcastMessage(dcreo3, true);
}

void ImageDesignManager::updateHairObject(CreatureObject* creo, String& hairObject, String& hairCustomization) {
	if (creo == NULL)
		return;

	ManagedReference<TangibleObject*> hair = cast<TangibleObject*>( creo->getSlottedObject("hair"));

	if (hair != NULL) {
		hair->destroyObjectFromWorld(true);
	}

	if (!hairObject.isEmpty()) {
		ManagedReference<PlayerManager*> playerMgr = creo->getZoneServer()->getPlayerManager();
		hair = playerMgr->createHairObject(hairObject, hairCustomization);
		creo->transferObject(hair, 4);
		creo->broadcastObject(hair, true);

	}
}

ImageDesignManager::~ImageDesignManager() {
}
