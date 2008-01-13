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

ArmorImplementation::ArmorImplementation(uint64 objid, uint32 tempCRC, const unicode& n, const string& tempn, bool eqp)
		: ArmorServant(objid, tempCRC, n, tempn, eqp) {
	initialize();
}

ArmorImplementation::ArmorImplementation(CreatureObject* creature, uint32 tempCRC, const unicode& n, const string& tempn, bool eqp)
		: ArmorServant(creature, tempCRC, n, tempn, eqp) {
	initialize();
}

void ArmorImplementation::initialize() {
	objectSubType = ARMOR;
	
	rating = LIGHT;
	conditionDamage = 10000;
	maxCondition = 50000;
	 	
	healthEncumbrance = 300;
	actionEncumbrance = 124;
	mindEncumbrance = 87; 	
	 	
	kinetic = 50.0f;
	kineticIsSpecial = true;

	energy = 50.0f;
	energyIsSpecial = true;

	electricity = 30.0f;
	electricityIsSpecial = false;

	stun = 0.0f;
	stunIsSpecial = false;

	blast = 30.0f;
	blastIsSpecial = false;

	heat = 30.0f;
	heatIsSpecial = false;

	cold = 30.0f;
	coldIsSpecial = false;

	acid = 30.0f;
	acidIsSpecial = false;

	lightSaber = 0.0f;
	lightSaberIsSpecial = false;
	
	type = 0;

	stringstream loggingname;
	loggingname << "Armor = 0x" << objectID;
	setLoggingName(loggingname.str());
	
	setLogging(false);
	setGlobalLogging(true);
}

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
	if (!obj->isPlayer())
		return;
		
	Player* player = (Player*) obj;
	
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);
	
	stringstream conditionStr;
	conditionStr << getCondition() << '/' << maxCondition;
	alm->insertAttribute("Condition", conditionStr);
	
	alm->insertAttribute("Volume", "1");
	
	//Armor Rating
	if (rating == LIGHT)
		alm->insertAttribute("armorrating", "Light");
	else if (rating == MEDIUM)
		alm->insertAttribute("armorrating", "Medium");
	else if (rating == HEAVY)
		alm->insertAttribute("armorrating", "Heavy");
	
	alm->insertAttribute("cat_armor_special_protection", "");
	
	//Check for special protections
	if (kineticIsSpecial)
		alm->insertAttribute("armor_eff_kinetic", kinetic);
	
	if (energyIsSpecial)
		alm->insertAttribute("armor_eff_energy", energy);
	
	if (electricityIsSpecial)
		alm->insertAttribute("armor_eff_elemental_electrical", electricity);
	
	if (stunIsSpecial)
		alm->insertAttribute("armor_eff_stun", stun);
	
	if (blastIsSpecial)
		alm->insertAttribute("armor_eff_blast", blast);
	
	if (heatIsSpecial)
		alm->insertAttribute("armor_eff_elemental_heat", heat);
	
	if (coldIsSpecial)
		alm->insertAttribute("armor_eff_elemental_cold", cold);
	
	if (acidIsSpecial)
		alm->insertAttribute("armor_eff_elemental_acid", acid);
	
	if (lightSaberIsSpecial)
		alm->insertAttribute("armor_eff_restraint", lightSaber);
		
	alm->insertAttribute("cat_armor_effectiveness", "");

	//Check for Effectiveness protections(Normal)
	if (!kineticIsSpecial)
		alm->insertAttribute("armor_eff_kinetic", kinetic);
	
	if (!energyIsSpecial)
		alm->insertAttribute("armor_eff_energy", energy);
	
	if (!electricityIsSpecial)
		alm->insertAttribute("armor_eff_elemental_electrical", electricity);
	
	if (!stunIsSpecial)
		alm->insertAttribute("armor_eff_stun", stun);
	
	if (!blastIsSpecial)
		alm->insertAttribute("armor_eff_blast", blast);
	
	if (!heatIsSpecial)
		alm->insertAttribute("armor_eff_elemental_heat", heat);
	
	if (!coldIsSpecial)
		alm->insertAttribute("armor_eff_elemental_cold", cold);
	
	if (!acidIsSpecial)
		alm->insertAttribute("armor_eff_elemental_acid", acid);
	
	if (!lightSaberIsSpecial)
		alm->insertAttribute("armor_eff_restraint", lightSaber);
	
	//Encumbrances
	alm->insertAttribute("cat_armor_encumbrance", "");
	
	alm->insertAttribute("healthencumbrance", healthEncumbrance);
	
	alm->insertAttribute("actionencumbrance", actionEncumbrance);
	
	alm->insertAttribute("mindencumbrance", mindEncumbrance);
	
	player->sendMessage(alm);
	
}

void ArmorImplementation::setArmorStats(int modifier) {	
	int luck = (System::random(100)) + (modifier / 4);
	
	if (System::random(1000) == 7) 
		luck = luck * 10;
	
	if (System::random(10000) == 777) 
		luck = luck * 25;
	
	if (System::random(100) == 6) 
		luck = 0;
	
	int playerRoll = System::random(1000) * modifier * luck / 1000;
	if (playerRoll > 100000) {
		modifier = modifier + 100;
		luck = luck + 100;
		
		stringstream itemText;
		itemText << "\\#ffff00" << name.c_str() << " (Legendary)";
		name = unicode(itemText.str());	
	} else if (playerRoll > 22500) {
		modifier = modifier + 50;
		luck = luck + 50;
		
		stringstream itemText;
		itemText << "\\#ffff00" << name.c_str() << " (Exceptional)";	
		name = unicode(itemText.str());
	} else if (playerRoll > 7500) {
		modifier = modifier + 25;
		luck = luck + 25;
		
		stringstream itemText;
		itemText << "\\#ffff00" << name.c_str();
		name = unicode(itemText.str());	
	}
	
	maxCondition = 25000 + (modifier * 10) + (luck * 10);
	
	if ((luck * System::random(100)) > 2000) {
		healthEncumbrance = healthEncumbrance - (modifier / 4) - (luck / 10);
		actionEncumbrance = actionEncumbrance - (modifier / 4) - (luck / 10);
		mindEncumbrance = mindEncumbrance - (modifier / 4) - (luck / 10);
	}
	
	if ((luck * System::random(100)) > 2000) {
		kinetic = kinetic + (modifier / 10) + (luck / 10);
		energy = energy + (modifier / 10) + (luck / 10);
		electricity = electricity + (modifier / 10) + (luck / 10);
		blast = blast + (modifier / 10) + (luck / 10);
		heat = heat + (modifier / 10) + (luck / 10);
		cold = cold + (modifier / 10) + (luck / 10);
		acid = acid + (modifier / 10) + (luck / 10);
	}
	
	kineticIsSpecial = System::random(1);
	energyIsSpecial = System::random(1);
	electricityIsSpecial = System::random(1);
	blastIsSpecial = System::random(1);
	heatIsSpecial = System::random(1);
	coldIsSpecial = System::random(1);
	acidIsSpecial = System::random(1);
	
	if (kinetic > 90.0f) 
		kinetic = 90.0f;
	
	if (energy > 90.0f) 
		energy = 90.0f;
	
	if (electricity > 90.0f) 
		electricity = 90.0f;
	
	if (blast > 90.0f) 
		blast = 90.0f;
	
	if (heat > 90.0f) 
		heat = 90.0f;
	
	if (cold > 90.0f) 
		cold = 90.0f;
	
	if (acid > 90.0f) 
		acid = 90.0f;
	
	if (healthEncumbrance < 0) 
		healthEncumbrance = 0;
	
	if (actionEncumbrance < 0) 
		actionEncumbrance = 0;
	
	if (mindEncumbrance < 0) 
		mindEncumbrance = 0;
	
}
