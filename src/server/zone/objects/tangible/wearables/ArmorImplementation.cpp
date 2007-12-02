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

#include "../../../ZoneClient.h"
#include "../../player/Player.h"

#include "../../../packets.h"

#include "Armor.h"
#include "ArmorImplementation.h"

void ArmorImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;
 
	SceneObjectImplementation::create(client);
	
	if (container != NULL)
		link(client, container);
		
	Message* tano3 = new TangibleObjectMessage3((TangibleObject*) _this);
	client->sendMessage(tano3);
	
	generateAttributes(player);
	
	if (doClose)
		SceneObjectImplementation::close(client);
		
}

void ArmorImplementation::generateAttributes(SceneObject* obj) {
		
	if (obj->getObjectType() != SceneObjectImplementation::PLAYER)
		return;
		
	Player* play = (Player*) obj;
	
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);
	
	stringstream conditionStr;
	conditionStr << getCondition() << '/' << maxCondition;
	alm->insertAttribute("Condition", conditionStr);
	
	alm->insertAttribute("Volume", "1");
	
	//Armor Rating
	if(rating == LIGHT)
		alm->insertAttribute("armorrating", "Light");
	else if(rating == MEDIUM)
		alm->insertAttribute("armorrating", "Medium");
	else if(rating == HEAVY)
		alm->insertAttribute("armorrating", "Heavy");
	
	alm->insertAttribute("cat_armor_special_protection", "");
	
	//Check for special protections
	if(kineticIsSpecial)
		alm->insertAttribute("armor_eff_kinetic", kinetic);
	if(energyIsSpecial)
		alm->insertAttribute("armor_eff_energy", energy);
	if(electricityIsSpecial)
		alm->insertAttribute("armor_eff_elemental_electrical", electricity);
	if(stunIsSpecial)
		alm->insertAttribute("armor_eff_stun", stun);
	if(blastIsSpecial)
		alm->insertAttribute("armor_eff_blast", blast);
	if(heatIsSpecial)
		alm->insertAttribute("armor_eff_elemental_heat", heat);
	if(coldIsSpecial)
		alm->insertAttribute("armor_eff_elemental_cold", cold);
	if(acidIsSpecial)
		alm->insertAttribute("armor_eff_elemental_acid", acid);
	if(lightSaberIsSpecial)
		alm->insertAttribute("armor_eff_restraint", lightSaber);
		
	alm->insertAttribute("cat_armor_effectiveness", "");
	//Check for Effectiveness protections(Normal)
	if(!kineticIsSpecial)
		alm->insertAttribute("armor_eff_kinetic", kinetic);
	if(!energyIsSpecial)
		alm->insertAttribute("armor_eff_energy", energy);
	if(!electricityIsSpecial)
		alm->insertAttribute("armor_eff_elemental_electrical", electricity);
	if(!stunIsSpecial)
		alm->insertAttribute("armor_eff_stun", stun);
	if(!blastIsSpecial)
		alm->insertAttribute("armor_eff_blast", blast);
	if(!heatIsSpecial)
		alm->insertAttribute("armor_eff_elemental_heat", heat);
	if(!coldIsSpecial)
		alm->insertAttribute("armor_eff_elemental_cold", cold);
	if(!acidIsSpecial)
		alm->insertAttribute("armor_eff_elemental_acid", acid);
	if(!lightSaberIsSpecial)
		alm->insertAttribute("armor_eff_restraint", lightSaber);
	
	//Encumbrances
	alm->insertAttribute("cat_armor_encumbrance", "");
	
	alm->insertAttribute("healthencumbrance", healthEncumbrance);
	
	alm->insertAttribute("actionencumbrance", actionEncumbrance);
	
	alm->insertAttribute("mindencumbrance", mindEncumbrance);
	
	play->sendMessage(alm);
	
}
