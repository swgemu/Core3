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
#include "server/zone/templates/datatables/DataTableIff.h"

ImageDesignManager::ImageDesignManager() {
	loadCustomizationData();
}

void ImageDesignManager::updateCustomization(String customizationName, float value, CreatureObject* creo) {
	if(creo == NULL)
		return;

	if (value < 0 || value > 1)
		return;

	speciesGender = getSpeciesGenderString(creo);

	creatureObject = creo;

	hairCustomization.removeAll();

	CustomizationData* customData = getCustomizationData(speciesGender, customizationName);

	if (customData == NULL) {
		System::out << "Unable to get CustomizationData for " + speciesGender + "_" + customizationName << endl;
		return;
	}

	String variables = customData->getVariables();
	String type = customData->getType();
	int choices = customData->getMaxChoices();

	if (type == "hslider") {

		if (
				customizationName == "brow" ||
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
				customizationName == "trunk_height" ||
				customizationName == "trunk_length" ||
				customizationName == "trunk_size" ||
				customizationName == "trunk_slope" ||
				customizationName == "weight"
		) {
			String token_1 = "";
			String token_2 = "";

			StringTokenizer tokenizer(variables.toCharArray());
			tokenizer.setDelimeter(",");

			tokenizer.getStringToken(token_1);
			if (tokenizer.hasMoreTokens())
				tokenizer.getStringToken(token_2);

			if (token_2 == "") {
				if (customData->getIsVarHairColor())
					setHairAttribute(token_1, (value * 255) );
				else
					creatureObject->setCustomizationVariable(token_1, (value * 255) );
			} else {
				if (value == .5f) {
					creatureObject->setCustomizationVariable(token_1, 0);
					creatureObject->setCustomizationVariable(token_2, 0);

				} else if (value > .5) {
					creatureObject->setCustomizationVariable(token_1, 0);
					creatureObject->setCustomizationVariable(token_2, (((value-.5f)/.5f) * 255) );

				} else { // < .5
					creatureObject->setCustomizationVariable(token_1, (((.5f-value)/.5f)* 255) );
					creatureObject->setCustomizationVariable(token_2, 0);

				}

			}

		} else if (customizationName == "height") {

			float minScale = customData->getMinScale();
			float maxScale = customData->getMaxScale();

			creatureObject->setHeight(minScale + ((maxScale - minScale) * value));

		} else if (

				customizationName == "age" ||
				customizationName == "beard" ||
				customizationName == "center_beard" ||
				customizationName == "eyebrows" ||
				customizationName == "eyeshadow" ||
				customizationName == "freckles" ||
				customizationName == "hair_style" ||
				customizationName == "pattern" ||
				customizationName == "side_beard" ||
				customizationName == "tattoo_style"
		){

			StringTokenizer tokenizer(variables.toCharArray());
			tokenizer.setDelimeter(",");

			while (tokenizer.hasMoreTokens()) {
				String attribute;
				tokenizer.getStringToken(attribute);

				creatureObject->setCustomizationVariable(attribute, ((value/1.0f) * (choices-1)) );
			}

		}
		updateCharacterAppearance(creatureObject);

	} else
		creatureObject->sendSystemMessage("This shouldn't have happend.  Please report repro steps to Polonel - updateCustomization(String customizationName, uint32 value)");

}

void ImageDesignManager::updateCustomization(String customizationName, uint32 value, CreatureObject* creo) {
	if (value > 255 || creo == NULL)
		return;

	speciesGender = getSpeciesGenderString(creo);

	creatureObject = creo;

	CustomizationData* customData = getCustomizationData(speciesGender, customizationName);

	if (customData == NULL) {
		System::out << "Unable to get CustomizationData for " + speciesGender + "_" + customizationName << endl;
		return;
	}

	String variables = customData->getVariables();
	String type = customData->getType();

	if (type == "color") {
		StringTokenizer tokenizer(variables.toCharArray());
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String attribute;
			tokenizer.getStringToken(attribute);

			if (customData->getIsVarHairColor())
				setHairAttribute(attribute, value);
			else
				creatureObject->setCustomizationVariable(attribute, value);
		}

		updateCharacterAppearance(creatureObject);

	} else if (type == "hslider")
	{
		updateCustomization(customizationName, (float)value, creo);
		return;

	} else
	{
		creatureObject->sendSystemMessage("This shouldn't have happend.  Please report repro steps to Polonel - updateCustomization(String customizationName, uint32 value)");
	}
}

void ImageDesignManager::loadCustomizationData() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("datatables/customization/customization_data.iff");

	if (iffStream == NULL)
		return;

	DataTableIff dataTable;
	dataTable.readObject(iffStream);

	delete iffStream;
	iffStream = NULL;
}

CustomizationData* ImageDesignManager::getCustomizationData(String speciesGender, String customizationName) {
	StringBuffer speciesGenderCustomization;
	speciesGenderCustomization << speciesGender << "_" << customizationName;

	CustomizationData* customization = customizationData.get(speciesGenderCustomization.toString());

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

void ImageDesignManager::updateHairObject(CreatureObject* creo, String& hairObject) {
	if (creo == NULL)
		return;

	TangibleObject* hair = (TangibleObject*) creo->getSlottedObject("hair");

	if (hair != NULL) {
		creo->removeObject(hair);
		creo->broadcastDestroy(hair, true);

	}

	if(!hairObject.isEmpty()) {
		String h;
		hairCustomization.getData(h);

		ManagedReference<PlayerManager*> playerMgr = creo->getZoneServer()->getPlayerManager();
		hair = playerMgr->createHairObject(hairObject,h);
		creo->addObject(hair, 4);
		creo->broadcastObject(hair,true);

	}

	hairCustomization.removeAll();
}

void ImageDesignManager::setHairAttribute(String& type, uint8 value) {
	hairCustomization.setVariable(type,value);
}

void ImageDesignManager::setHairAttribute(uint8 type, uint8 value) {
	hairCustomization.setVariable(type,value);
}

ImageDesignManager::~ImageDesignManager() {
	customizationData.removeAll();
	hairCustomization.removeAll();
}
