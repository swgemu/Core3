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
	
	generateAttributes(player);
	
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
	
	float speed = round(10*attackSpeed)/10;
	
	alm->insertAttribute("wpn_attack_speed", speed);
	
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
			maxDamage = 1;
			minDamage = 1;
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
	
	if (templateName == "rifle_flame_thrower") {
		minDamage = minDamage * 2;
		maxDamage = maxDamage * 3;
		woundsRatio = woundsRatio * 2;
		
		pointBlankAccuracy = 10;
		idealAccuracy = -65;
		maxRangeAccuracy = -120;

		idealRange = 50;
	}
	
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
	
	if (luck * System::random(100) > 1600) {
		minDamage = (minDamage * modifier / 100) + (0.7 * luck);
		maxDamage = (maxDamage * modifier / 100) + (0.8 * luck);
	}
	
	if (luck * System::random(100) > 1750) {	
		attackSpeed = attackSpeed - (attackSpeed * modifier / 500) - (luck / 150);
	}
	
	if (luck * System::random(100) > 1000) {
		healthAttackCost = healthAttackCost - (modifier / 25) - (luck / 50);
		actionAttackCost = actionAttackCost - (modifier / 25) - (luck / 50);
		mindAttackCost = mindAttackCost - (modifier / 25) - (luck / 50);
	}

	if (luck * System::random(100) > 1750)
		woundsRatio = woundsRatio + (modifier / 15) + (luck / 10);
	
	if (playerRoll > 13500)	{
		switch (System::random(4)) {
		case 1:
			dot1Type = BLEED;
			dot1Attribute = (System::random(2) * 3) + 1;
			dot1Strength = (modifier / 10) + luck;
			dot1Duration = (luck * 5) + modifier;
			dot1Potency = luck;
			dot1Uses = (modifier + luck) * 11;
			break;
		case 2:
			dot1Type = DISEASE;
			dot1Attribute = (System::random(2) * 3) + 1;
			dot1Strength = (modifier / 10) + luck;
			dot1Duration = (luck * 7) + modifier;
			dot1Potency = luck;
			dot1Uses = (modifier + luck) * 13;
			break;	
		case 3:
			dot1Type = FIRE;
			dot1Attribute = (System::random(2) * 3) + 1;
			dot1Strength = (modifier / 10)+ luck;
			dot1Duration = (luck * 4) + modifier;
			dot1Potency = luck;
			dot1Uses = (modifier + luck) * 11;
			break;
		case 4:
			dot1Type = POISON;
			dot1Attribute = (System::random(2) * 3) + 1;
			dot1Strength = (modifier / 10) + luck;
			dot1Duration = (luck * 5) + modifier;
			dot1Potency = luck;
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
	
	equipped = false;
	
	persistent = false;
	updated = true;
	
	unlock();
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
		
			sendTo(player);
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
		
	int modifier = System::random(11) + 25;
	
	minDamage = (minDamage * modifier / 100) + minDamage;
	maxDamage = (maxDamage * modifier / 100) + maxDamage;
	
	sliced = true;
	updated = true;
	
	return modifier;
}

int WeaponImplementation::sliceWeaponSpeed(){
	if (sliced) 
		return 0;
		
	int modifier = System::random(11) + 25;
	
	attackSpeed = attackSpeed - (attackSpeed * modifier / 100);

	if (attackSpeed < 1) 
		attackSpeed = 1.0f;
	
	sliced = true;
	updated = true;
	
	return modifier;
}
