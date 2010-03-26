/*
 * WeaponObjectImplementation.cpp
 *
 *  Created on: 30/07/2009
 *      Author: victor
 */

#include "WeaponObject.h"
#include "server/zone/packets/tangible/WeaponObjectMessage3.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/PlayerObject.h"

void WeaponObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("WeaponObject");
}

void WeaponObjectImplementation::loadTemplateData(LuaObject* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	certified = false;

	attackType = templateData->getIntField("attackType");
	weaponEffect =  templateData->getStringField("weaponEffect");
	weaponEffectIndex = templateData->getIntField("weaponEffectIndex");

	damageType = templateData->getIntField("damageType");

	LuaObject certifications = templateData->getObjectField("certificationsRequired");

	for (int i = 1; i <= certifications.getTableSize(); ++i) {
		certificationsRequired.add(certifications.getStringAt(i));
	}

	certifications.pop();

	LuaObject accMods = templateData->getObjectField("creatureAccuracyModifiers");

	for (int i = 1; i <= accMods.getTableSize(); ++i) {
		creatureAccuracyModifiers.add(accMods.getStringAt(i));
	}

	accMods.pop();

	LuaObject defMods = templateData->getObjectField("defenderDefenseModifiers");

	for (int i = 1; i <= defMods.getTableSize(); ++i) {
		defenderDefenseModifiers.add(defMods.getStringAt(i));
	}

	defMods.pop();

	LuaObject dmgMods = templateData->getObjectField("damageModifiers");

	for (int i = 1; i <= dmgMods.getTableSize(); ++i) {
		damageModifiers.add(dmgMods.getStringAt(i));
	}

	dmgMods.pop();

	LuaObject speedMods = templateData->getObjectField("speedModifiers");

	for (int i = 1; i <= speedMods.getTableSize(); ++i) {
		speedModifiers.add(speedMods.getStringAt(i));
	}

	speedMods.pop();

}

void WeaponObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending weapon object baselines");

	BaseMessage* weao3 = new WeaponObjectMessage3(_this);
	player->sendMessage(weao3);
}

void WeaponObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	bool res = isCertifiedFor(object);

	if (res) {
		alm->insertAttribute("weapon_cert_status", "Yes");
	} else {
		alm->insertAttribute("weapon_cert_status", "No");
	}

	/*if (usesRemaining > 0)
		alm->insertAttribute("count", usesRemaining);*/

	/*int key = 0;
	int value = 0;
	for (int i = 0; i < innateSkillModMap.size(); ++i) {
		key = innateSkillModMap.elementAt(i).getKey();
		value = innateSkillModMap.elementAt(i).getValue();

		if (value > 0)
			generateSkillMods(alm, key, value);
	}*/

	String ap;

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

	StringBuffer spdtxt;

	spdtxt << speed;

	if ((int(round(speed * 10)) % 10) == 0)
		spdtxt << ".0";

	alm->insertAttribute("wpn_attack_speed", spdtxt.toString());

	if (area != 0.0f)
		alm->insertAttribute("area", Math::getPrecision(area, 0));

	//Damage Information
	StringBuffer dmgtxt;

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
	default:
		dmgtxt << "Unknown";
		break;
	}

	alm->insertAttribute("damage.wpn_damage_type", dmgtxt);

	float minDmg = round(getMinDamage());
	float maxDmg = round(getMaxDamage());

	alm->insertAttribute("damage.wpn_damage_min", minDmg);

	alm->insertAttribute("damage.wpn_damage_max", maxDmg);

	StringBuffer woundsratio;

	float wnd = round(10 * getWoundsRatio()) / 10.0f;

	woundsratio << wnd << "%";

	alm->insertAttribute("damage.wpn_wound_chance", woundsratio);

	//Accuracy Modifiers
	StringBuffer pblank;
	if (getPointBlankAccuracy() >= 0)
		pblank << "+";

	pblank << getPointBlankAccuracy() << " @ " << getPointBlankRange() << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_zero", pblank);

	StringBuffer ideal;
	if (getIdealAccuracy() >= 0)
		ideal << "+";

	ideal << getIdealAccuracy() << " @ " << getIdealRange() << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_mid", ideal);

	StringBuffer maxrange;
	if (getMaxRangeAccuracy() >= 0)
		maxrange << "+";

	maxrange << getMaxRangeAccuracy() << " @ " << getMaxRange() << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_max", maxrange);

	//Special Attack Costs
	alm->insertAttribute("cat_wpn_attack_cost.health", getHealthAttackCost());

	alm->insertAttribute("cat_wpn_attack_cost.action", getActionAttackCost());

	alm->insertAttribute("cat_wpn_attack_cost.mind", getMindAttackCost());

	// Force Cost
	if (getForceCost() > 0)
		alm->insertAttribute("forcecost", getForceCost());

	/*if (getDotCount() > 0)
		generateDotAttributes(alm);*/

	if (sliced == 1)
		alm->insertAttribute("wpn_attr", "@obj_attr_n:hacked1");

	//generatePowerup(alm);
}

bool WeaponObjectImplementation::isCertifiedFor(PlayerCreature* object) {
	PlayerObject* ghost = object->getPlayerObject();

	for (int i = 0; i < certificationsRequired.size(); ++i) {
		String cert = certificationsRequired.get(i);

		if (!ghost->hasSkill(cert)) {
			return false;
		}
	}

	return true;
}
