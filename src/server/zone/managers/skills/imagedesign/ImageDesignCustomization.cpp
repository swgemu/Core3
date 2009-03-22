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

#include "engine/engine.h"
#include "../../../ZoneProcessServerImplementation.h"

#include "ImageDesignCustomization.h"
#include "../SkillManager.h"

//BankManager::BankManager(ZoneServer* server, ZoneProcessServerImplementation* processor) {
ImageDesignCustomization::ImageDesignCustomization(ZoneProcessServerImplementation* serv, CreatureObject* creo) {
	server = serv;
	speciesGender = creo->getStfName();
	speciesGender += "_";
	speciesGender += creo->getGender();

	customization = NULL;
	creatureObject = creo;

}

void ImageDesignCustomization::updateCustomization(String customizationName, float value) {
	if (value < 0 || value > 1 || creatureObject == NULL || server == NULL)
		return; // valid values are a scale of 0-1

	SkillManager* skillManager = server->getSkillManager();
	if (skillManager == NULL)
		return;

	customization = skillManager->getCustomizationData(speciesGender, customizationName);
	if (customization == NULL)
		return;

	String variables = customization->getVariables();
	String type = customization->getType();
	int choices = customization->getMaxChoices();

	if (type == "color") {
		// doh problem!
		creatureObject->sendSystemMessage("This isn't implemented - and frankly shouldn't have occured please report to McMahon repro steps - updateCustomization(String customizationName, uint32 value)");
	} else if (type == "hslider") {

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
			    //customizationName == "height" ||
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

			//StringBuffer msg;
			if (token_2 == "") {
				//msg << "one token: " << token_1 << " => " << hex << (uint8)(value * 255) << dec << " (" << value << ")";
				if (customization->getIsVarHairColor())
					creatureObject->setHairAppearanceAttribute(token_1, (uint8)(value * 255) );
				else
					creatureObject->setCustomizationVariable(token_1, (uint8)(value * 255) );
			} else {
				if (value == .5f) {
					creatureObject->setCustomizationVariable(token_1, (uint8) 0);
					creatureObject->setCustomizationVariable(token_2, (uint8) 0);
					//msg << "two tokens == .5, token 1: " << token_1 << " => " << hex << 0 << dec << " (" << value << ")";
					//msg << " token 2: " << token_2 << " => " << hex << 0 << dec << " (" << value << ")";

				} else if (value > .5) {
					// take (.75 - .5) / .5 (50% * 255 = 128)
					creatureObject->setCustomizationVariable(token_1, (uint8) 0);
					creatureObject->setCustomizationVariable(token_2, (uint8) (((value-.5f)/.5f) * 255) );
					//msg << "two tokens > .5, token 1: " << token_1 << " => " << hex << 0 << dec << " (" << value << ")";
					//msg << " token 2: " << token_2 << " => " << hex << (uint8) (((value-.5f)/.5f) * 255) << dec << " (" << value << ")";
				} else { // < .5
					// sometimes == 0
					// .25 / .5 => (50% * 255 = 128)
					creatureObject->setCustomizationVariable(token_1, (uint8) (((.5f-value)/.5f)* 255) );
					creatureObject->setCustomizationVariable(token_2, (uint8) 0);
					//msg << "two tokens else, token 1: " << token_1 << " => " << hex << (uint8) ((value)/.5f) * 255 << dec << " (" << value << ")";
					//msg << " token 2: " << token_2 << " => " << hex << 0 << dec << " (" << value << ")";
				}

			}
			//creatureObject->info(msg.toString());
		} else if (customizationName == "height") {

			float minScale = customization->getMinScale();
			float maxScale = customization->getMaxScale();

			creatureObject->setHeight(minScale + ((maxScale - minScale) * value));
			// special mojo
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

			StringBuffer msg;

			StringTokenizer tokenizer(variables.toCharArray());
			tokenizer.setDelimeter(",");

			while (tokenizer.hasMoreTokens()) {
				String attribute;
				tokenizer.getStringToken(attribute);
				msg << "customizationName: " << customizationName << "attribute: " << attribute << " => " << hex << (uint8) ((value/1.0f) * (choices-1)) << dec << " (" << value << ")" << dec << " choices (" << choices << ")";

				if (customization->getIsVarHairColor())
					creatureObject->setHairAppearanceAttribute(attribute, (uint8) ((value/1.0f) * (choices-1)) );
				else
					creatureObject->setCustomizationVariable(attribute, (uint8) ((value/1.0f) * (choices-1)) );
			}
			creatureObject->info(msg.toString());
		}
	} else {
		// danger will robinson!
		creatureObject->sendSystemMessage("This shouldn't have happend.  Please report repro steps to McMahon - updateCustomization(String customizationName, uint32 value)");
	}
}

void ImageDesignCustomization::updateCustomization(String customizationName, uint32 value) {
	// bad value, 0-255 = good
	if (value > 255 || creatureObject == NULL || server == NULL)
		return;

	SkillManager* skillManager = server->getSkillManager();
	if (skillManager == NULL)
		return;

	customization = skillManager->getCustomizationData(speciesGender, customizationName);
	if (customization == NULL)
		return;

	String variables = customization->getVariables();
	String type = customization->getType();
	int choices = customization->getMaxChoices();

	if (type == "color") {
		StringTokenizer tokenizer(variables.toCharArray());
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String attribute;
			tokenizer.getStringToken(attribute);

			if (customization->getIsVarHairColor())
				creatureObject->setHairAppearanceAttribute(attribute, (uint8)value);
			else
				creatureObject->setCustomizationVariable(attribute, (uint8)value);
		}
	} else if (type == "hslider")
	{
		// this happens for some index type variables
		updateCustomization(customizationName, (float)value);
		return;

	} else
	{
		creatureObject->sendSystemMessage("This shouldn't have happend.  Please report repro steps to McMahon - updateCustomization(String customizationName, uint32 value)");
	}
}

