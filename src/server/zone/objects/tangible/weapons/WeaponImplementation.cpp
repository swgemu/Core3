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

#include "WeaponImplementation.h"

WeaponImplementation::WeaponImplementation(uint64 objid, uint32 tempCRC, const unicode& n, const string& tempn, bool eqp, int tp, int cat) 
		: WeaponServant(objid, n, tempn, tempCRC, WEAPON) {
	type = tp;
	category = cat;
		
	equipped = eqp;

	initialize();
}

WeaponImplementation::WeaponImplementation(CreatureObject* creature, const string& temp, const unicode& n, const string& tempn, bool eqp, int tp, int cat) 
		: WeaponServant(creature->getNewItemID(), WEAPON) {
	objectCRC = String::hashCode(temp);

	name = n;
		
	type = tp;
	category = cat;
		
	templateName = tempn;

	if (equipped = eqp)
		setContainer(creature, 0x04);
	else
		setContainer(creature->getInventory(), 0xFFFFFFFF);
		
	initialize();
}

void WeaponImplementation::initialize() {
	templateTypeName = "weapon_name";

	conditionDamage = 0;
	maxCondition = 750;
	
	skillMod0Type = 0;
	skillMod0Value = 0;
	
	skillMod1Type = 0;
	skillMod1Value = 0;
	
	skillMod2Type = 0;
	skillMod2Value = 0;
	
	damageType = KINETIC;
	minDamage = 50;
	maxDamage = 100;
	
	attackSpeed = 1.0f;
	
	healthAttackCost = 15;
	actionAttackCost = 10;
	mindAttackCost = 5;
	
	pointBlankRange = 0;
	pointBlankAccuracy = 0;
	
	idealRange = 2;
	idealAccuracy = 15;
			
	maxRange = 5;
	maxRangeAccuracy = 0;
	
	woundsRatio = 10;
	
	armorPiercing = NONE;
	
	dot0Type = 0;
	dot0Attribute = 0;
	dot0Strength = 0;
	dot0Duration = 0;
	dot0Potency = 0;
	dot0Uses = 0;
	
	dot1Type = 0;
	dot1Attribute = 0;
	dot1Strength = 0;
	dot1Duration = 0;
	dot1Potency = 0;
	dot1Uses = 0;

	dot2Type = 0;
	dot2Attribute = 0;
	dot2Strength = 0;
	dot2Duration = 0;
	dot2Potency = 0;
	dot2Uses = 0;
	
	sliced = false;

	stringstream loggingname;
	loggingname << "Weapon = 0x" << objectID;
	setLoggingName(loggingname.str());
	
	setLogging(false);
	setGlobalLogging(true);
}

void WeaponImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);
	
	if (container != NULL)
		link(client, container);
	
	BaseMessage* weao3 = new WeaponObjectMessage3((Weapon*) _this);
	client->sendMessage(weao3);

	/*Message* weao6 = new WeaponObjectMessage6(this);
	client->sendMessage(weao6);*/
	
	if (doClose)
		SceneObjectImplementation::close(client);
}

void WeaponImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;
		
	Player* player = (Player*) obj;
	
	AttributeListMessage* alm = new AttributeListMessage((Weapon*) _this);
	
	alm->insertAttribute("weapon_cert_status", "Yes");
	
	stringstream cond;
	cond << (maxCondition-conditionDamage) << "/" << maxCondition;
	
	alm->insertAttribute("condition", cond);
	
	alm->insertAttribute("volume", "1");
	
	if (skillMod0Type > 0)
		generateSkillMods(alm, skillMod0Type, skillMod0Value);
	
	if (skillMod1Type > 0)
		generateSkillMods(alm, skillMod1Type, skillMod1Value);
	
	if (skillMod2Type > 0)
		generateSkillMods(alm, skillMod2Type, skillMod2Value);

	string ap;
	
	switch (armorPiercing) {
	case NONE:
		ap = "None";
		break;
	case LIGHT:
		ap = "Light";
		break;
	case MEDIUM:
		ap = "Medium";
		break;
	case HEAVY:
		ap = "Heavy";
		break;
	default:
		ap = "Unknown";
		break;
	}
	
	alm->insertAttribute("wpn_armor_pierce_rating", ap);
	
	float speed = round(10 * attackSpeed) / 10;
	
	stringstream spdtxt;
	
	spdtxt << speed;
	
	if ((int(round(speed * 10)) % 10) == 0)
		spdtxt << ".0";
	
	alm->insertAttribute("wpn_attack_speed", spdtxt.str());
	
	//Damage Information
	stringstream dmgtxt;

	switch (damageType) {
	case KINETIC:
		dmgtxt << "Kinetic";
		break;
	case ENERGY:
		dmgtxt << "Energy";
		break;
	case ELECTRICITY:
		dmgtxt << "Electricity";
		break;
	case STUN:
		dmgtxt << "Stun";
		break;
	case BLAST:
		dmgtxt << "Blast";
		break;
	case HEAT:
		dmgtxt << "Heat";
		break;
	case COLD:
		dmgtxt << "Cold";
		break;
	case ACID:
		dmgtxt << "Acid";
		break;
	case LIGHTSABER:
		dmgtxt << "Lightsaber";
		break;
	}
	
	alm->insertAttribute("damage.wpn_damage_type", dmgtxt);

	float minDmg = round(minDamage);
	float maxDmg = round(maxDamage);
	
	alm->insertAttribute("damage.wpn_damage_min", minDmg);

	alm->insertAttribute("damage.wpn_damage_max", maxDmg);
	
	stringstream woundsratio;
	woundsratio << woundsRatio << "%";
	
	alm->insertAttribute("damage.wpn_wound_chance", woundsratio);
	
	//Accuracy Modifiers
	stringstream pblank;
	if (pointBlankAccuracy >= 0)
		pblank << "+";
		
	pblank << pointBlankAccuracy << " @ " << pointBlankRange << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_zero", pblank);
	
	stringstream ideal;
	if (idealAccuracy >= 0)
		ideal << "+";
		
	ideal << idealAccuracy << " @ " << idealRange << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_mid", ideal);
	
	stringstream maxrange;
	if (maxRangeAccuracy >= 0)
		maxrange << "+";
		
	maxrange << maxRangeAccuracy << " @ " << maxRange << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_max", maxrange);
	
	//Special Attack Costs
	alm->insertAttribute("cat_wpn_attack_cost.health", healthAttackCost);
	
	alm->insertAttribute("cat_wpn_attack_cost.action", actionAttackCost);
	
	alm->insertAttribute("cat_wpn_attack_cost.mind", mindAttackCost);
	
	generateDotAttributes(alm);
	
	if (sliced == 1) 
		alm->insertAttribute("hacked1", "");
		
	player->sendMessage(alm);
}

void WeaponImplementation::generateDotAttributes(AttributeListMessage* alm) {
	if (dot0Uses != 0) {
		//Sends the information along for the first DOT, if it exists
		
		switch (dot0Type) {
		case BLEED:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_type", "Bleed");
			break;
		case DISEASE:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_type", "Disease");
			break;
		case FIRE:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_type", "Fire");
			break;
		case POISON:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_type", "Poison");
			break;
		}
		
		switch (dot0Attribute) {
		case HEALTH:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Health");
			break;
		case STRENGTH:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Strength");
			break;
		case CONSTITUTION:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Constitution");
			break;
		case ACTION:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Action");
			break;
		case QUICKNESS:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Quickness");
			break;
		case STAMINA:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Stamina");
			break;
		case MIND:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Mind");
			break;
		case FOCUS:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Focus");
			break;
		case WILLPOWER:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Willpower");
			break;
		}
		alm->insertAttribute("cat_wpn_dot_00.wpn_dot_strength", dot0Strength);
		
		stringstream dur;
		dur << dot0Duration << "s";
		alm->insertAttribute("cat_wpn_dot_00.wpn_dot_duration", dur);
		
		stringstream pot;
		pot << dot0Potency << "%";
		alm->insertAttribute("cat_wpn_dot_00.wpn_dot_potency", pot);
		
		alm->insertAttribute("cat_wpn_dot_00.wpn_dot_uses", dot0Uses);
	}

	if (dot1Uses != 0) {
		//Sends the information for the second DOT, if it exists
		
		switch (dot1Type) {
		case BLEED:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_type", "Bleed");
			break;
		case DISEASE:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_type", "Disease");
			break;
		case FIRE:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_type", "Fire");
			break;
		case POISON:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_type", "Poison");
			break;
		}
		
		switch (dot1Attribute) {
		case HEALTH:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Health");
			break;
		case STRENGTH:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Strength");
			break;
		case CONSTITUTION:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Constitution");
			break;
		case ACTION:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Action");
			break;
		case QUICKNESS:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Quickness");
			break;
		case STAMINA:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Stamina");
			break;
		case MIND:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Mind");
			break;
		case FOCUS:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Focus");
			break;
		case WILLPOWER:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Willpower");
			break;
		}
		
		alm->insertAttribute("cat_wpn_dot_01.wpn_dot_strength", dot1Strength);

		stringstream dur;
		dur << dot1Duration << "s";
		alm->insertAttribute("cat_wpn_dot_01.wpn_dot_duration", dur);
		
		stringstream pot;
		pot << dot1Potency << "%";
		alm->insertAttribute("cat_wpn_dot_01.wpn_dot_potency", pot);
		
		alm->insertAttribute("cat_wpn_dot_01.wpn_dot_uses", dot1Uses);
	}
	
	if (dot2Uses != 0) {
		//The third DOT, if it exists
		
		switch (dot2Type) {
		case BLEED:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_type", "Bleed");
			break;
		case DISEASE:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_type", "Disease");
			break;
		case FIRE:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_type", "Fire");
			break;
		case POISON:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_type", "Poison");
			break;
		}
		
		switch (dot2Attribute) {
		case HEALTH:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Health");
			break;
		case STRENGTH:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Strength");
			break;
		case CONSTITUTION:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Constitution");
			break;
		case ACTION:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Action");
			break;
		case QUICKNESS:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Quickness");
			break;
		case STAMINA:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Stamina");
			break;
		case MIND:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Mind");
			break;
		case FOCUS:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Focus");
			break;
		case WILLPOWER:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Willpower");
			break;
		}
		
		alm->insertAttribute("cat_wpn_dot_02.wpn_dot_strength", dot2Strength);
		
		stringstream dur;
		dur << dot2Duration << "s";
		alm->insertAttribute("cat_wpn_dot_02.wpn_dot_duration", dur);
		
		stringstream pot;
		pot << dot2Potency << "%";
		alm->insertAttribute("cat_wpn_dot_02.wpn_dot_potency", pot);
		
		alm->insertAttribute("cat_wpn_dot_02.wpn_dot_uses", dot2Uses);
	}
}

void WeaponImplementation::decayWeapon(int decayRate) {
	conditionDamage = conditionDamage + (maxCondition / 100 * decayRate);

	if (conditionDamage > maxCondition)
		conditionDamage = maxCondition;
	
	if (maxCondition > 0) {
		float ratio = ((float) conditionDamage) / ((float) maxCondition);

		if (ratio > 0.99) {
			maxCondition = 1;
			conditionDamage = 0;
			maxDamage = 0;
			minDamage = 0;
		} else if (ratio > 0.75) {
			maxDamage = maxDamage - (maxDamage * decayRate / 100);
			minDamage = minDamage - (minDamage * decayRate / 100);

			attackSpeed = attackSpeed + (attackSpeed * decayRate / 100);
		}
	}
	
	updated = true;
}

void WeaponImplementation::setWeaponStats(int modifier){
	wlock();
	
	int luck = (System::random(100)) + (modifier/4);
	
	if (System::random(1000) == 7) 
		luck = luck * 2; 
	
	if (System::random(50000) == 77) 
		luck = luck * 5; 
		
	if (System::random(1000000) == 777) 
		luck = luck * 10; 
	
	if (System::random(100) == 6) 
		luck = 0;
		
	modifier = modifier + System::random(10);
	
	int playerRoll = System::random(1000) * modifier * luck / 1000;
	if (playerRoll > 200000) {
		modifier = modifier + 100;
		luck = luck + 100;
		maxDamage = maxDamage * 1.5;
		
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
		luck = luck + 25;

		stringstream itemText;
		itemText << "\\#ffff00" << name.c_str();
		name = unicode(itemText.str());	
	}
	
	if (luck * System::random(100) > 1700) {
		minDamage = (minDamage * modifier / 100) + (0.45 * luck);
		maxDamage = (maxDamage * modifier / 100) + (0.55 * luck);
	}
	
	if (luck * System::random(100) > 1700) {	
		attackSpeed = attackSpeed - (attackSpeed * modifier / 500) - (luck / 500);
	}
	
	if (luck * System::random(100) > 1700) {
		healthAttackCost = healthAttackCost - (modifier / 25) - (luck / 75);
		actionAttackCost = actionAttackCost - (modifier / 25) - (luck / 75);
		mindAttackCost = mindAttackCost - (modifier / 25) - (luck / 75);
	}

	if (luck * System::random(100) > 1700)
		woundsRatio = woundsRatio + (modifier / 15) + (luck / 10);
	
	if (playerRoll > 12500 && System::random(3) == 1) {
		skillMod0Type = System::random(27) + 1;
		skillMod0Value = luck / (System::random(3) + 9);
	}
	if (playerRoll > 15000 && System::random(2) == 1) {
		skillMod1Type = System::random(27) + 1;
		skillMod1Value = luck / (System::random(3) + 9);
	}
	if (playerRoll > 45000) {
		skillMod2Type = System::random(27) + 1;
		skillMod2Value = luck / (System::random(3) + 9);
	}
	
	if (playerRoll > 13500 && System::random(1) == 1)	{
		switch (System::random(4)) {
		case 1:
			dot1Type = BLEED;
			dot1Attribute = (System::random(2) * 3) + 1;
			dot1Strength = (modifier / 11) + luck;
			dot1Duration = ((luck * 4) + modifier) / 7;
			dot1Potency = luck/4;
			dot1Uses = (modifier + luck) * 11;
			break;
		case 2:
			dot1Type = DISEASE;
			dot1Attribute = (System::random(2) * 3) + 1;
			dot1Strength = (modifier / 11) + luck;
			dot1Duration = ((luck * 5) + modifier) / 7;
			dot1Potency = luck/4;
			dot1Uses = (modifier + luck) * 13;
			break;	
		case 3:
			dot1Type = FIRE;
			dot1Attribute = (System::random(2) * 3) + 1;
			dot1Strength = (modifier / 11) + luck;
			dot1Duration = ((luck * 3) + modifier) / 7;
			dot1Potency = luck/4;
			dot1Uses = (modifier + luck) * 11;
			break;
		case 4:
			dot1Type = POISON;
			dot1Attribute = (System::random(2) * 3) + 1;
			dot1Strength = (modifier / 11) + luck;
			dot1Duration = ((luck * 4) + modifier) / 7;
			dot1Potency = luck/4;
			dot1Uses = (modifier + luck) * 11;
			break;
		}
	}
	
	if (attackSpeed < 1) 
		attackSpeed = 1.0f;
	
	if (healthAttackCost < 0) 
		healthAttackCost = 0;
	
	if (actionAttackCost < 0) 
		actionAttackCost = 0;
	
	if (mindAttackCost < 0) 
		mindAttackCost = 0;
	
	if (maxDamage > 900)
		maxDamage = 850 + System::random(50);
	
	if (type == UNARMED && maxDamage > 500)
		maxDamage = 450 + System::random(50);
	
	if (dot1Strength > 300)
		dot1Strength = 250 + System::random(50);
	
	if (minDamage > maxDamage) 
		minDamage = round(0.8 * maxDamage);
	
	if (skillMod0Value > 25)
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
	}
	
	equipped = false;
	
	persistent = false;
	updated = true;
	
	unlock();
}

void WeaponImplementation::generateSkillMods(AttributeListMessage* alm, int skillModType, int skillModValue) {
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
	}
}


void WeaponImplementation::sliceWeapon(Player* player){
	bool sliceType = System::random(1);
	int slicePercent;
	
	stringstream msg;

	try {
		wlock();

		if (!isSliced()) {
			switch (sliceType) {
			case 0:
				slicePercent = sliceWeaponDamage();
				msg << "Weapon damage increased by " << slicePercent << "%";
				break;
			case 1:
				slicePercent = sliceWeaponSpeed();
				msg << "Weapon speed decreased by " << slicePercent << "%";
				break;
			}
		
		} else
			msg << "Weapon is already sliced.";

		unlock();
	} catch (...) {
		unlock();
	}

	player->sendSystemMessage(msg.str());
}

int WeaponImplementation::sliceWeaponDamage(){
	if (sliced) 
		return 0;
		
	int modifier = System::random(10) + 25;
	
	minDamage = (minDamage * modifier / 100) + minDamage;
	maxDamage = (maxDamage * modifier / 100) + maxDamage;
	
	sliced = true;
	updated = true;
	
	return modifier;
}

int WeaponImplementation::sliceWeaponSpeed(){
	if (sliced) 
		return 0;
		
	int modifier = System::random(10) + 25;
	
	attackSpeed = attackSpeed - (attackSpeed * modifier / 100);

	if (attackSpeed < 1) 
		attackSpeed = 1.0f;
	
	sliced = true;
	updated = true;
	
	return modifier;
}
