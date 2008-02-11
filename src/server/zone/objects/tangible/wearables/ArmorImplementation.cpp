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

void ArmorImplementation::parseItemAttributes() {
	string name = "armorType";
	type = itemAttributes->getIntAttribute(name);

	maxCondition = itemAttributes->getMaxCondition();
	conditionDamage = maxCondition - itemAttributes->getCurrentCondition();
	
	name = "rating";
	rating = itemAttributes->getIntAttribute(name);
	
	name = "sockets";
	sockets = itemAttributes->getIntAttribute(name);
	
	name = "skillMod0Type";
	skillMod0Type = itemAttributes->getIntAttribute(name);
	name = "skillMod0Value";
	skillMod0Value = itemAttributes->getIntAttribute(name);

	name = "skillMod1Type";
	skillMod1Type = itemAttributes->getIntAttribute(name);
	name = "skillMod1Value";
	skillMod1Value = itemAttributes->getIntAttribute(name);
	
	name = "skillMod2Type";
	skillMod2Type = itemAttributes->getIntAttribute(name);
	name = "skillMod2Value";
	skillMod2Value = itemAttributes->getIntAttribute(name);
	
	name = "socket0Type";
	socket0Type = itemAttributes->getIntAttribute(name);
	name = "socket0Value";
	socket0Value = itemAttributes->getIntAttribute(name);
	
	name = "socket1Type";
	socket1Type = itemAttributes->getIntAttribute(name);
	name = "socket1Value";
	socket1Value = itemAttributes->getIntAttribute(name);

	name = "socket2Type";
	socket2Type = itemAttributes->getIntAttribute(name);
	name = "socket2Value";
	socket2Value = itemAttributes->getIntAttribute(name);

	name = "socket3Type";
	socket3Type = itemAttributes->getIntAttribute(name);
	name = "socket3Value";
	socket3Value = itemAttributes->getIntAttribute(name);

	name = "healthEncumberence";
	healthEncumbrance = itemAttributes->getIntAttribute(name);
	name = "actionEncumberence";
	actionEncumbrance = itemAttributes->getIntAttribute(name);
	name = "mindEncumberence";
	mindEncumbrance = itemAttributes->getIntAttribute(name);
	
	name = "kinetic";
	kinetic = itemAttributes->getFloatAttribute(name);
	name = "energy";
	energy = itemAttributes->getFloatAttribute(name);
	name = "electricity";
	electricity = itemAttributes->getFloatAttribute(name);
	name = "stun";
	stun = itemAttributes->getFloatAttribute(name);
	name = "blast";
	blast = itemAttributes->getFloatAttribute(name);
	name = "heat";
	heat = itemAttributes->getFloatAttribute(name);
	name = "cold";
	cold = itemAttributes->getFloatAttribute(name);
	name = "acid";
	acid = itemAttributes->getFloatAttribute(name);
	name = "lightSaber";
	lightSaber = itemAttributes->getFloatAttribute(name);

	name = "kineticIsSpecial";
	kineticIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "energyIsSpecial";
	energyIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "electricityIsSpecial";
	electricityIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "stunIsSpecial";
	stunIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "blastIsSpecial";
	blastIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "heatIsSpecial";
	heatIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "coldIsSpecial";
	coldIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "acidIsSpecial";
	acidIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "lightSaberIsSpecial";
	lightSaberIsSpecial = itemAttributes->getBooleanAttribute(name);
	
	name = "sliced";
	sliced = itemAttributes->getBooleanAttribute(name);
	
}

void ArmorImplementation::initialize() {
	objectSubType = ARMOR;
	
	setRating(LIGHT);
	setConditionDamage(0);
	setCondition(35000, 35000);
	
	skillMod0Type = 0;
	skillMod0Value = 0;
	
	skillMod1Type = 0;
	skillMod1Value = 0;
	
	skillMod2Type = 0;
	skillMod2Value = 0;

	setSockets(4);
	
	socket0Type = 0;
	socket0Value = 0;

	socket1Type = 0;
	socket1Value = 0;

	socket2Type = 0;
	socket2Value = 0;

	socket3Type = 0;
	socket3Value = 0;
	
	setHealthEncumbrance(100);
	setActionEncumbrance(100);
	setMindEncumbrance(100); 	
	 	
	setKinetic(50.0f);
	kineticIsSpecial = false;

	setEnergy(50.0f);
	energyIsSpecial = false;

	setElectricity(50.0f);
	electricityIsSpecial = false;

	setStun(0.0f);
	stunIsSpecial = false;

	setBlast(50.0f);
	blastIsSpecial = false;

	setHeat(50.0f);
	heatIsSpecial = false;

	setCold(50.0f);
	coldIsSpecial = false;

	setAcid(50.0f);
	acidIsSpecial = false;

	setLightSaber(0.0f);
	lightSaberIsSpecial = false;
	
	type = 0;
	
	setSliced(false);
	
	customizationVars.setVariable(2, System::random(150));

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
		
	BaseMessage* tano3 = new TangibleObjectMessage3((TangibleObject*) _this);
	client->sendMessage(tano3);
	
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
	
	alm->insertAttribute("Sockets", sockets);
	
	if (skillMod0Type > 0)
		generateSkillMods(alm, skillMod0Type, skillMod0Value);
	
	if (skillMod1Type > 0)
		generateSkillMods(alm, skillMod1Type, skillMod1Value);
	
	if (skillMod2Type > 0)
		generateSkillMods(alm, skillMod2Type, skillMod2Value);
	
	if (socket0Type > 0)
		generateSkillMods(alm, socket0Type, socket0Value);
	
	if (socket1Type > 0)
		generateSkillMods(alm, socket1Type, socket1Value);
	
	if (socket2Type > 0)
		generateSkillMods(alm, socket2Type, socket2Value);
	
	if (socket3Type > 0)
		generateSkillMods(alm, socket3Type, socket3Value);
	
	//Armor Rating
	if (rating == LIGHT)
		alm->insertAttribute("armorrating", "Light");
	else if (rating == MEDIUM)
		alm->insertAttribute("armorrating", "Medium");
	else if (rating == HEAVY)
		alm->insertAttribute("armorrating", "Heavy");
	
	//Check for special protections
	if (kineticIsSpecial && kinetic >= 0.5) {
		stringstream txt;
		txt << round(kinetic) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic", txt.str());
	}
	if (energyIsSpecial && energy >= 0.5) {
		stringstream txt;
		txt << round(energy) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy", txt.str());
	}
	if (electricityIsSpecial && electricity >= 0.5) {
		stringstream txt;
		txt << round(electricity) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_electrical", txt.str());
	}
	if (stunIsSpecial && stun >= 0.5) {
		stringstream txt;
		txt << round(stun) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun", txt.str());
	}
	if (blastIsSpecial && blast >= 0.5) {
		stringstream txt;
		txt << round(blast) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast", txt.str());
	}
	if (heatIsSpecial && heat >= 0.5) {
		stringstream txt;
		txt << round(heat) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_heat", txt.str());
	}
	if (coldIsSpecial && cold >= 0.5) {
		stringstream txt;
		txt << round(cold) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_cold", txt.str());
	}
	if (acidIsSpecial && acid >= 0.5) {
		stringstream txt;
		txt << round(acid) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_acid", txt.str());
	}
	if (lightSaberIsSpecial && lightSaberIsSpecial >= 0.5) {
		stringstream txt;
		txt << round(lightSaber) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_restraint", txt.str());
	}
	//Check for Effectiveness protections(Normal)
	if (!kineticIsSpecial && kinetic >= 0.5) {
		stringstream txt;
		txt << round(kinetic) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic", txt.str());
	}
	if (!energyIsSpecial && energy >= 0.5) {
		stringstream txt;
		txt << round(energy) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy", txt.str());
	}
	if (!electricityIsSpecial && electricity >= 0.5) {
		stringstream txt;
		txt << round(electricity) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_electrical", txt.str());
	}
	if (!stunIsSpecial && stun >= 0.5) {
		stringstream txt;
		txt << round(stun) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun", txt.str());
	}
	if (!blastIsSpecial && blast >= 0.5) {
		stringstream txt;
		txt << round(blast) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast", txt.str());
	}
	if (!heatIsSpecial && heat >= 0.5) {
		stringstream txt;
		txt << round(heat) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_heat", txt.str());
	}
	if (!coldIsSpecial && cold >= 0.5) {
		stringstream txt;
		txt << round(cold) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_cold", txt.str());
	}
	if (!acidIsSpecial && acid >= 0.5) {
		stringstream txt;
		txt << round(acid) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_acid", txt.str());
	}
	if (!lightSaberIsSpecial && lightSaber >= 0.5) {
		stringstream txt;
		txt << round(lightSaber) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint", txt.str());
	}
	
	//Vulnerabilities
	if (kinetic < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");
	
	if (energy < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");
	
	if (electricity < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_electrical", "-");
	
	if (stun < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");
	
	if (blast < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");
	
	if (heat < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_heat", "-");
	
	if (cold < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_cold", "-");
	
	if (acid < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_acid", "-");
	
	if (lightSaber < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");
	
	//Encumbrances
	alm->insertAttribute("cat_armor_encumbrance.health", healthEncumbrance);
	
	alm->insertAttribute("cat_armor_encumbrance.action", actionEncumbrance);
	
	alm->insertAttribute("cat_armor_encumbrance.mind", mindEncumbrance);
	
	if (sliced == 1) 
		alm->insertAttribute("hacked", "");
	
	player->sendMessage(alm);
	
}

void ArmorImplementation::generateSkillMods(AttributeListMessage* alm, int skillModType, int skillModValue) {
	switch (skillModType) {
	case 1:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:melee_defense", skillModValue);
		break;
	case 2:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:ranged_defense", skillModValue);
		break;
	case 3:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:stun_defense", skillModValue);
		break;
	case 4:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:dizzy_defense", skillModValue);
		break;
	case 5:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:blind_defense", skillModValue);
		break;
	case 6:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:knockdown_defense", skillModValue);
		break;
	case 7:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:intimidate_defense", skillModValue);
		break;
	case 8:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:pistol_speed", skillModValue);
		break;
	case 9:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:carbine_speed", skillModValue);
		break;
	case 10:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:rifle_speed", skillModValue);
		break;
	case 11:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:unarmed_speed", skillModValue);
		break;
	case 12:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:onehandmelee_speed", skillModValue);
		break;
	case 13:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:twohandmelee_speed", skillModValue);
		break;
	case 14:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:polearm_speed", skillModValue);
		break;
	case 15:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:pistol_accuracy", skillModValue);
		break;
	case 16:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:carbine_accuracy", skillModValue);
		break;
	case 17:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:rifle_accuracy", skillModValue);
		break;
	case 18:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:unarmed_accuracy", skillModValue);
		break;
	case 19:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:onehandmelee_accuracy", skillModValue);
		break;
	case 20:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:twohandmelee_accuracy", skillModValue);
		break;
	case 21:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:polearm_accuracy", skillModValue);
		break;
	case 22:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:dodge", skillModValue);
		break;
	case 23:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:block", skillModValue);
		break;
	case 24:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:counterattack", skillModValue);
		break;
	case 25:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_bleeding", skillModValue);
		break;
	case 26:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_disease", skillModValue);
		break;
	case 27:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_fire", skillModValue);
		break;
	case 28:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_poison", skillModValue);
		break;
	case 29:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:slope_move", skillModValue);
		break;
	}
}

void ArmorImplementation::decayArmor(int decayRate) {
	setConditionDamage(conditionDamage + (maxCondition * decayRate / 100));

	if (conditionDamage > maxCondition)
		conditionDamage = maxCondition;
	
	if (maxCondition > 0) {
		float ratio = ((float) conditionDamage) / ((float) maxCondition);

		if (ratio > 0.99) {
			setRating(0);
			maxCondition = 1;
			conditionDamage = 1;
			itemAttributes->setCondition(0, 1);
			
			setKinetic(0.0f);
			setKineticIsSpecial(false);
			setEnergy(0.0f);
			setEnergyIsSpecial(false);
			setElectricity(0.0f);
			setElectricityIsSpecial(false);
			setStun(0.0f);
			setStunIsSpecial(false);
			setBlast(0.0f);
			setBlastIsSpecial(false);
			setHeat(0.0f);
			setHeatIsSpecial(false);
			setCold(0.0f);
			setColdIsSpecial(false);
			setAcid(0.0f);
			setAcidIsSpecial(false);
			setLightSaber(0.0f);
			setLightSaberIsSpecial(false);
			
		} else if (ratio > 0.75) {
			setKinetic(kinetic - (kinetic * decayRate / 100));
			setEnergy(energy - (energy * decayRate / 100));
			setElectricity(electricity - (electricity * decayRate / 100));
			setStun(stun - (stun * decayRate / 100));
			setBlast(blast - (blast * decayRate / 100));
			setHeat(heat - (heat * decayRate / 100));
			setCold(cold - (cold * decayRate / 100));
			setAcid(acid - (acid * decayRate / 100));
			setLightSaber(lightSaber - (lightSaber* decayRate / 100));
		}
	}
	
	updated = true;
	
}

void ArmorImplementation::repairArmor(Player* player) {
	int roll = System::random(100);
	
	int decayRate = 0;
	
	stringstream txt;
	
	if (roll < 10) {
		player->sendSystemMessage("You have completely failed to repair the item. The item falls apart.");
		decayArmor(100);
		
		updated = true;
		
		BaseMessage* tano3 = new TangibleObjectMessage3(_this);
		player->sendMessage(tano3);
		
		return;
	} else if (roll < 75) {
		txt << "You have repaired the item, however the items maximum condition has been reduced.";
		decayRate = 20;
	} else {
		txt << "You have completely repaired the item.";				
	}
	
	player->sendSystemMessage(txt.str());

	maxCondition = (maxCondition - (maxCondition / 100 * decayRate));
	conditionDamage = 0;
	setCondition(maxCondition, maxCondition);
	
	updated = true;
	
	BaseMessage* tano3 = new TangibleObjectMessage3(_this);
	player->sendMessage(tano3);
	
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
	if (playerRoll > 200000) {
		modifier = modifier + 100;
		luck = luck + 100;
		
		stringstream itemText;
		itemText << "\\#ffff00" << name.c_str() << " (Legendary)";
		name = unicode(itemText.str());	
	} else if (playerRoll > 45000) {
		modifier = modifier + 50;
		luck = luck + 50;
		
		stringstream itemText;
		itemText << "\\#ffff00" << name.c_str() << " (Exceptional)";	
		name = unicode(itemText.str());
	} else if (playerRoll > 12500) {
		modifier = modifier + 10;
		luck = luck + 20;
		
		stringstream itemText;
		itemText << "\\#ffff00" << name.c_str();
		name = unicode(itemText.str());	
	}
	
	maxCondition = 25000 + (modifier * 10) + (luck * 50);
	setCondition(maxCondition, maxCondition);
	
	if ((luck * System::random(100)) > 2000) {
		setHealthEncumbrance(healthEncumbrance - (healthEncumbrance * luck / 300));
		setActionEncumbrance(actionEncumbrance - (actionEncumbrance * luck / 300));
		setMindEncumbrance(mindEncumbrance - (mindEncumbrance * luck / 300));
	}
	
	if ((luck * System::random(100)) > 2000) {
		setKinetic(kinetic + (modifier / 10) + (luck / 10));
		setEnergy(energy + (modifier / 10) + (luck / 10));
		setElectricity(electricity + (modifier / 10) + (luck / 10));
		setBlast(blast + (modifier / 10) + (luck / 10));
		setHeat(heat + (modifier / 10) + (luck / 10));
		setCold(cold + (modifier / 10) + (luck / 10));
		setAcid(acid + (modifier / 10) + (luck / 10));
	}
	
	/*if (playerRoll > 45000 && System::random(3) == 1) {
		skillMod0Type = System::random(28) + 1;
		skillMod0Value = luck / (System::random(3) + 9);
	}
	if (playerRoll > 75000 && System::random(2) == 1) {
		skillMod1Type = System::random(28) + 1;
		skillMod1Value = luck / (System::random(3) + 9);
	}
	if (playerRoll > 125000) {
		skillMod2Type = System::random(28) + 1;
		skillMod2Value = luck / (System::random(3) + 9);
	}*/
	
	if (playerRoll > 15000 && System::random(3) == 1) {
		setStun(stun + System::random(9) + 1);
		setStunIsSpecial(true);
	}
	
	if (System::random(1))
		setKineticIsSpecial(true);
	if (System::random(1))
		setEnergyIsSpecial(true);
	if (System::random(1))
		setElectricityIsSpecial(true);
	if (System::random(1))
		setBlastIsSpecial(true);
	if (System::random(1))
		setHeatIsSpecial(true);
	if (System::random(1))
		setColdIsSpecial(true);
	if (System::random(1))
		setAcidIsSpecial(true);
	
	if (kinetic > 90.0f) 
		setKinetic(90.0f);
	
	if (energy > 90.0f) 
		setEnergy(90.0f);
	
	if (electricity > 90.0f) 
		setElectricity(90.0f);
	
	if (blast > 90.0f) 
		setBlast(90.0f);
	
	if (heat > 90.0f) 
		setHeat(90.0f);
	
	if (cold > 90.0f) 
		setCold(90.0f);
	
	if (acid > 90.0f) 
		setAcid(90.0f);
	
	if (healthEncumbrance < 0) 
		setHealthEncumbrance(0);
	
	if (actionEncumbrance < 0) 
		setActionEncumbrance(0);
	
	if (mindEncumbrance < 0) 
		setMindEncumbrance(0);
	
	/*if (skillMod0Value > 25)
		skillMod0Value = 25;

	if (skillMod1Value > 25)
		skillMod1Value = 25;

	if (skillMod2Value > 25)
		skillMod2Value = 25;
	
	if (skillMod2Type == skillMod1Type || skillMod2Type == skillMod0Type) {
		skillMod2Type = 0;
		skillMod2Value = 0;
	}
	
	if (skillMod1Type == skillMod0Type || skillMod1Type == skillMod2Type) {
		skillMod1Type = 0;
		skillMod1Value = 0;
	}*/
}

void ArmorImplementation::sliceArmor(Player* player){
	bool sliceType = System::random(1);
	int slicePercent;
	
	stringstream msg;

	try {
		wlock();
		
		if (isEquipped())
			msg << "You must unequip this item first.";
		else if (!isSliced()) {
			switch (sliceType) {
			case 0:
				slicePercent = sliceArmorEffectiveness();
				msg << "Armor effectiveness increased by " << slicePercent << "%";
				break;
			case 1:
				slicePercent = sliceArmorEncumbrance();
				msg << "Armor encumbrance reduced by " << slicePercent << "%";
				break;
			}
		
		} else
			msg << "Armor is already sliced.";

		unlock();
	} catch (...) {
		unlock();
	}

	player->sendSystemMessage(msg.str());
}

int ArmorImplementation::sliceArmorEffectiveness(){
	if (sliced) 
		return 0;
		
	int modifier = System::random(10) + 25;

	if (!kineticIsSpecial) {
		setKinetic(kinetic + (kinetic * modifier / 100));
		if (kinetic > 90.0f) 
			setKinetic(90.0f);
	}
		
	if (!energyIsSpecial) {
		setEnergy(energy + (energy * modifier / 100));
		if (energy > 90.0f) 
			setEnergy(90.0f);		
	}
	if (!electricityIsSpecial) {
		setElectricity(electricity + (electricity * modifier / 100));
		if (electricity > 90.0f) 
			setElectricity(90.0f);
	}
	if (!stunIsSpecial) {
		setStun(stun + (stun * modifier / 100));
		if (stun > 90.0f)
			setStun(90.0f);
	}
	if (!blastIsSpecial) {
		setBlast(blast + (blast * modifier / 100));
		if (blast > 90.0f) 
			setBlast(90.0f);
	}
	if (!heatIsSpecial) {
		setHeat(heat + (heat * modifier / 100));
		if (heat > 90.0f) 
			setHeat(90.0f);
	}
	if (!coldIsSpecial) {
		setCold(cold + (cold * modifier / 100));
		if (cold > 90.0f) 
			setCold(90.0f);
	}
	if (!acidIsSpecial) {
		setAcid(acid + (acid * modifier / 100));
		if (acid > 90.0f) 
			setAcid(90.0f);
	}
	if (!lightSaberIsSpecial) {
		setLightSaber(lightSaber + (lightSaber * modifier / 100));
		if (lightSaber > 90.0f)
			setLightSaber(90.0f);
	}

	setSliced(true);
	updated = true;
	
	return modifier;
}

int ArmorImplementation::sliceArmorEncumbrance(){
	if (sliced) 
		return 0;
		
	int modifier = System::random(30) + 15;
	
	setHealthEncumbrance(healthEncumbrance - (healthEncumbrance * modifier / 100));
	setActionEncumbrance(actionEncumbrance - (actionEncumbrance * modifier / 100));
	setMindEncumbrance(mindEncumbrance - (mindEncumbrance * modifier / 100));
	
	setSliced(true);
	updated = true;
	
	return modifier;
}

void ArmorImplementation::setSocket(int index, int type, int value) {
	switch (index) {
	case 0:
		setSocket0Value(value);
		setSocket0Type(type);
		break;
	case 1:
		setSocket1Value(value);
		setSocket1Type(type);
		break;
	case 2:
		setSocket2Value(value);
		setSocket2Type(type);
		break;
	case 3:
		setSocket3Value(value);
		setSocket3Type(type);
		break;
	}
}

void ArmorImplementation::setSocketValue(int index, int value) {
	switch (index) {
	case 0:
		setSocket0Value(value);
		break;
	case 1:
		setSocket1Value(value);
		break;
	case 2:
		setSocket2Value(value);
		break;
	case 3:
		setSocket3Value(value);
		break;
	}
}

void ArmorImplementation::setSocketType(int index, int type) {
	switch (index) {
	case 0:
		setSocket0Type(type);
		break;
	case 1:
		setSocket1Type(type);
		break;
	case 2:
		setSocket2Type(type);
		break;
	case 3:
		setSocket3Type(type);
		break;
	}
}

int ArmorImplementation::getSocketType(int index) {
	switch (index) {
	case 0:
		return socket0Type;
		break;
	case 1:
		return socket1Type;
		break;
	case 2:
		return socket2Type;
		break;
	case 3:
		return socket3Type;
		break;
	}
	return -1;
}

int ArmorImplementation::getSocketValue(int index) {
	switch (index) {
	case 0:
		return socket0Value;
		break;
	case 1:
		return socket1Value;
		break;
	case 2:
		return socket2Value;
		break;
	case 3:
		return socket3Value;
		break;
	}
	return 0;
}

int ArmorImplementation::addSkillMod(int skillModType, int skillModValue) {

	if (skillModType == 0 || skillModValue == 0) {
		return -1;
	}
	
	int i = 0;
	
	for (; i < 4; i++) {
		if (getSocketType(i) == skillModType) {
			int modValue = getSocketValue(i);
			
			if (skillModValue <= modValue)
				return -2;
			else if (skillModValue > modValue){
				setSocketValue(i, skillModValue);
				updated = true;
				return -3;
			}
		}
	}
		
	if (sockets > 0)
		for (i = 0; i < 4; i++)
			if (getSocketValue(i) == 0) {
				setSocket(i, skillModType, skillModValue);
				updated = true;
				setSockets(sockets - 1);
				return i;
			}
	
	return -1;
}
