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
	speciesGender = creo->getSpeciesName();
	speciesGender += "_";
	speciesGender += creo->getGender();
		
	customization = NULL;
	creatureObject = creo; 

}

void ImageDesignCustomization::updateCustomization(string customizationName, float value) {
	if(value < 0 || value > 1 || creatureObject == NULL || server == NULL)
		return; // valid values are a scale of 0-1
		
	SkillManager* skillManager = server->getSkillManager();
	if(skillManager == NULL)
		return;
		
	customization = skillManager->getCustomizationData(speciesGender, customizationName);
	if(customization == NULL)
		return;
		
	string variables = customization->getVariables();
	string type = customization->getType();
	int choices = customization->getMaxChoices();
	
	if(type == "color") {
			
			
	} else if(type == "hslider") {
			
	}  else {
		// danger will robinson!
		creatureObject->sendSystemMessage("This shouldn't have happend.  Please report repro steps to McMahon - updateCustomization(string customizationName, uint32 value)");
	}
		
		//string variables = customization->getVariables();
		
		/*
		if(customizationName == "age") {
			switch(value / 1.0) {
			case 0.0:
				//creatureObject->setAppearanceAttribute(CustomizationVariableTypes::PRIVATE_INDEX_AGE, 0);
				break;
			case 1.0/3.0:
				//creatureObject->setAppearanceAttribute(CustomizationVariableTypes::PRIVATE_INDEX_AGE, 1);
				break;
			case 2.0/3.0:
				//creatureObject->setAppearanceAttribute(CustomizationVariableTypes::PRIVATE_INDEX_AGE, 2);
				break;
			case: 1.0:
				//creatureObject->setAppearanceAttribute(CustomizationVariableTypes::PRIVATE_INDEX_AGE, 3);
				break;
			}
		} else if(customizationName == "beard") {
			
		} else if(customizationName == "brow") {
			
		} else if(customizationName == "center_beard") {
						
		} else if(customizationName == "cheeks") {
			
		} else if(customizationName == "chest") {
								
		} else if(customizationName == "chin") {
			
		} else if(customizationName == "chin_length") {
			
		} else if(customizationName == "ear_shape") {
			
		} else if(customizationName == "ears") {
			
		} else if(customizationName == "eye_direction") {
			
		} else if(customizationName == "eye_shape") {
			
		} else if(customizationName == "eye_size") {
			
		} else if(customizationName == "eyebrows") {
			
		} else if(customizationName == "eyeshadow") {
			
		} else if(customizationName == "freckles") {
			
		} else if(customizationName == "gullet") {
			
		} else if(customizationName == "hair_style") {
			
		} else if(customizationName == "head") {
			
		} else if(customizationName == "head_shape") {
			
		} else if(customizationName == "head_size") {
			
		} else if(customizationName == "height") {
			
		} else if(customizationName == "hump_size") {
			
		} else if(customizationName == "jaw") {
			
		} else if(customizationName == "jowl") {
			
		} else if(customizationName == "lip_fullness") {
			
		} else if(customizationName == "lip_width") {
			
		} else if(customizationName == "muscle") {
			
		} else if(customizationName == "nose_length") {
			
		} else if(customizationName == "nose_protrusion") {
			
		} else if(customizationName == "nose_width") {
			
		} else if(customizationName == "pattern") {
			
		} else if(customizationName == "sensors") {
			
		} else if(customizationName == "side_beard") {
			
		} else if(customizationName == "tattoo_style") {
			
		} else if(customizationName == "trunk_height") {
			
		} else if(customizationName == "trunk_length") {
			
		} else if(customizationName == "trunk_size") {
			
		} else if(customizationName == "trunk_slope") {
			
		} else if(customizationName == "weight") {
			
		}
		*/

}

void ImageDesignCustomization::updateCustomization(string customizationName, uint32 value) {
	// bad value, 0-255 = good
	if(value > 255 || creatureObject == NULL || server == NULL)
		return;
	
	SkillManager* skillManager = server->getSkillManager();
	if(skillManager == NULL)
		return;
		
	customization = skillManager->getCustomizationData(speciesGender, customizationName);
	if(customization == NULL)
		return;
	
	string variables = customization->getVariables();
	string type = customization->getType();
	int choices = customization->getMaxChoices();
		
	if(type == "color") {
		StringTokenizer tokenizer(variables.c_str());
		tokenizer.setDelimeter(",");
			
		while (tokenizer.hasMoreTokens()) {
			string attribute;
			tokenizer.getStringToken(attribute);

			creatureObject->setAppearanceAttribute(attribute, (uint8)value);
		}
	} else if(type == "hslider")
	{
		// this happens for some index type variables
			
	} else
	{
		creatureObject->sendSystemMessage("This shouldn't have happend.  Please report repro steps to McMahon - updateCustomization(string customizationName, uint32 value)");
	}
}

