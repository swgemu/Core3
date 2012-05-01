/*
 * WeaponObjectImplementation.cpp
 *
 *  Created on: 30/07/2009
 *      Author: victor
 */

#include "WeaponObject.h"
#include "server/zone/packets/tangible/WeaponObjectMessage3.h"
#include "server/zone/packets/tangible/WeaponObjectMessage6.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/templates/tangible/SharedWeaponObjectTemplate.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/objects/tangible/powerup/PowerupObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"
#include "server/zone/Zone.h"



void WeaponObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	weaponTemplate = dynamic_cast<SharedWeaponObjectTemplate*>(TemplateManager::instance()->getTemplate(serverObjectCRC));

	setLoggingName("WeaponObject");

	if(damageSlice > 1.5 || damageSlice < 1) {
		damageSlice = 1;
	}

	if(speedSlice > 1.0 || speedSlice < .5) {
		speedSlice = 1;
	}
}

void WeaponObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	weaponTemplate = dynamic_cast<SharedWeaponObjectTemplate*>(templateData);

	certified = false;

	attackType = weaponTemplate->getAttackType();
	weaponEffect =  weaponTemplate->getWeaponEffect();
	weaponEffectIndex = weaponTemplate->getWeaponEffectIndex();

	damageType = weaponTemplate->getDamageType();

	armorPiercing = weaponTemplate->getArmorPiercing();

	healthAttackCost = weaponTemplate->getHealthAttackCost();
	actionAttackCost = weaponTemplate->getActionAttackCost();
	mindAttackCost = weaponTemplate->getMindAttackCost();
	forceCost = weaponTemplate->getForceCost();

	pointBlankAccuracy = weaponTemplate->getPointBlankAccuracy();
	pointBlankRange = weaponTemplate->getPointBlankRange();

	idealRange = weaponTemplate->getIdealRange();
	idealAccuracy = weaponTemplate->getIdealAccuracy();

	int templateMaxRange = weaponTemplate->getMaxRange();

	if (templateMaxRange > 5 )
		maxRange = templateMaxRange;

	maxRangeAccuracy = weaponTemplate->getMaxRangeAccuracy();

	minDamage = weaponTemplate->getMinDamage();
	maxDamage = weaponTemplate->getMaxDamage();

	woundsRatio = weaponTemplate->getWoundsRatio();

	damageRadius = weaponTemplate->getArea();

	float templateAttackSpeed = weaponTemplate->getAttackSpeed();

	if (templateAttackSpeed > 1)
		attackSpeed = templateAttackSpeed;

	setSliceable(true);
}

void WeaponObjectImplementation::sendContainerTo(CreatureObject* player) {

	if (isJediWeapon()) {

		ManagedReference<SceneObject*> saberInv = getSlottedObject("saber_inv");

		saberInv->sendDestroyTo(player);
		//saberInv->closeContainerTo(player, true);

		saberInv->sendWithoutContainerObjectsTo(player);
		saberInv->openContainerTo(player);

	}
}

void WeaponObjectImplementation::createChildObjects() {
	// Create any child objects in a weapon.

	ZoneServer* zoneServer = server->getZoneServer();

		for (int i = 0; i < templateObject->getChildObjectsSize(); ++i) {
			ChildObject* child = templateObject->getChildObject(i);

			if (child == NULL)
				continue;

			ManagedReference<SceneObject*> obj = zoneServer->createObject(
					child->getTemplateFile().hashCode(), 1);

			if (obj == NULL)
				continue;

			ContainerPermissions* permissions = obj->getContainerPermissions();
			permissions->setOwner(getObjectID());
			permissions->setInheritPermissionsFromParent(true);
			permissions->setDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
			permissions->setDenyPermission("owner", ContainerPermissions::MOVECONTAINER);

			childObjects.put(obj);

			obj->initializeChildObject(_this);

			transferObject(obj, child->getContainmentType());
		}

}

void WeaponObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending weapon object baselines");

	BaseMessage* weao3 = new WeaponObjectMessage3(_this);
	player->sendMessage(weao3);

	BaseMessage* weao6 = new WeaponObjectMessage6(_this);
	player->sendMessage(weao6);
}

void WeaponObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
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

	alm->insertAttribute("wpn_attack_speed", Math::getPrecision(getAttackSpeed(), 1));

	if (getDamageRadius() != 0.0f)
		alm->insertAttribute("area", Math::getPrecision(getDamageRadius(), 0));

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

	if (craftersName != "") {
		alm->insertAttribute("crafter", craftersName);
	}

	if (objectSerial != "") {
		alm->insertAttribute("serial_number", objectSerial);
	}

	if(hasPowerup())
		powerupObject->fillWeaponAttributeList(alm, _this);

	if (sliced == 1)
		alm->insertAttribute("wpn_attr", "@obj_attr_n:hacked1");

	if (isJediWeapon()){
	StringBuffer saberColor;

	int color = getBladeColor();


	saberColor << "@jedi_spam:saber_color_" << color;


	alm->insertAttribute("color", saberColor);
	}

}

int WeaponObjectImplementation::getPointBlankAccuracy(bool withPup) {

	if(powerupObject != NULL && withPup)
		return pointBlankAccuracy + (abs(pointBlankAccuracy) * powerupObject->getPowerupStat("pointBlankAccuracy"));

	return pointBlankAccuracy;
}

int WeaponObjectImplementation::getPointBlankRange(bool withPup) {

	if(powerupObject != NULL && withPup)
		return pointBlankRange + (abs(pointBlankRange) * powerupObject->getPowerupStat("pointBlankRange"));

	return pointBlankRange;
}

int WeaponObjectImplementation::getIdealRange(bool withPup) {

	if(powerupObject != NULL && withPup)
		return idealRange + (abs(idealRange) * powerupObject->getPowerupStat("idealRange"));

	return idealRange;
}

int WeaponObjectImplementation::getMaxRange(bool withPup) {

	if(powerupObject != NULL && withPup)
		return maxRange + (abs(maxRange) * powerupObject->getPowerupStat("maxRange"));

	return maxRange;
}

int WeaponObjectImplementation::getIdealAccuracy(bool withPup) {

	if(powerupObject != NULL && withPup)
		return idealAccuracy + (abs(idealAccuracy) * powerupObject->getPowerupStat("idealAccuracy"));

	return idealAccuracy;
}


int WeaponObjectImplementation::getMaxRangeAccuracy(bool withPup) {

	if(powerupObject != NULL && withPup)
		return maxRangeAccuracy + (abs(maxRangeAccuracy) * powerupObject->getPowerupStat("maxRangeAccuracy"));

	return maxRangeAccuracy;
}

float WeaponObjectImplementation::getAttackSpeed(bool withPup) {

	float speed = attackSpeed;

	if(sliced)
		speed *= speedSlice;

	if(powerupObject != NULL && withPup)
		return speed -
				(abs(attackSpeed) *
				powerupObject->getPowerupStat("attackSpeed")) +
				getConditionReduction(speed);

	return speed + getConditionReduction(speed);
}


float WeaponObjectImplementation::getMaxDamage(bool withPup) {

	float damage = maxDamage;

	if(sliced)
		damage *= damageSlice;

	if(powerupObject != NULL && withPup)
		return damage +
				(abs(maxDamage) *
				powerupObject->getPowerupStat("maxDamage")) -
				getConditionReduction(damage);

	return damage - getConditionReduction(damage);
}

float WeaponObjectImplementation::getMinDamage(bool withPup) {

	float damage = minDamage;

	if(sliced)
		damage *= damageSlice;

	if(powerupObject != NULL && withPup)
		return damage +
				(abs(minDamage) *
				powerupObject->getPowerupStat("minDamage")) -
				getConditionReduction(damage);

	return damage - getConditionReduction(damage);
}

float WeaponObjectImplementation::getWoundsRatio(bool withPup) {

	if(powerupObject != NULL && withPup)
		return woundsRatio + (abs(woundsRatio) * powerupObject->getPowerupStat("woundsRatio"));

	return woundsRatio;
}

float WeaponObjectImplementation::getDamageRadius(bool withPup) {

	if(powerupObject != NULL && withPup)
		return damageRadius + (abs(damageRadius) * powerupObject->getPowerupStat("damageRadius"));

	return damageRadius;
}


int WeaponObjectImplementation::getHealthAttackCost(bool withPup) {

	if(powerupObject != NULL && withPup)
		return healthAttackCost - (abs(healthAttackCost) * powerupObject->getPowerupStat("healthAttackCost"));

	return healthAttackCost;
}

int WeaponObjectImplementation::getActionAttackCost(bool withPup) {

	if(powerupObject != NULL && withPup)
		return actionAttackCost - (abs(actionAttackCost) * powerupObject->getPowerupStat("actionAttackCost"));

	return actionAttackCost;
}

int WeaponObjectImplementation::getMindAttackCost(bool withPup) {

	if(powerupObject != NULL && withPup)
		return mindAttackCost - (abs(mindAttackCost) * powerupObject->getPowerupStat("mindAttackCost"));

	return mindAttackCost;
}

void WeaponObjectImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/*
	 * Incoming Values:					Ranges:
	 * mindamage						Differs between weapons
	 * maxdamage
	 * attackspeed
	 * woundchance
	 * roundsused
	 * hitpoints
	 * zerorangemod
	 * maxrange
	 * maxrangemod
	 * midrange
	 * midrangemod
	 * charges
	 * attackhealthcost
	 * attackactioncost
	 * attackmindcost
	 */
	float value = 0.f;
	setMinDamage(MAX(values->getCurrentValue("mindamage"), 0));
	setMaxDamage(MAX(values->getCurrentValue("maxdamage"), 0));

	setAttackSpeed(values->getCurrentValue("attackspeed"));
	setHealthAttackCost((int)values->getCurrentValue("attackhealthcost"));
	setActionAttackCost((int)values->getCurrentValue("attackactioncost"));
	setMindAttackCost((int)values->getCurrentValue("attackmindcost"));

	if (isJediWeapon())
		setForceCost((int)values->getCurrentValue("forcecost"));

	value = values->getCurrentValue("woundchance");
	if(value != CraftingValues::VALUENOTFOUND)
		setWoundsRatio(value);

	//value = craftingValues->getCurrentValue("roundsused");
	//if(value != DraftSchematicValuesImplementation::VALUENOTFOUND)
		//_this->set_______(value);

	value = values->getCurrentValue("zerorangemod");
	if(value != CraftingValues::VALUENOTFOUND)
		setPointBlankAccuracy((int)value);

	value = values->getCurrentValue("maxrange");
	if(value != CraftingValues::VALUENOTFOUND)
		setMaxRange((int)value);

	value = values->getCurrentValue("maxrangemod");
	if(value != CraftingValues::VALUENOTFOUND)
		setMaxRangeAccuracy((int)value);

	value = values->getCurrentValue("midrange");
	if(value != CraftingValues::VALUENOTFOUND)
		setIdealRange((int)value);

	value = values->getCurrentValue("midrangemod");
	if(value != CraftingValues::VALUENOTFOUND)
		setIdealAccuracy((int)value);

	//value = craftingValues->getCurrentValue("charges");
	//if(value != CraftingValues::VALUENOTFOUND)
	//	setUsesRemaining((int)value);

	value = values->getCurrentValue("hitpoints");
	if(value != CraftingValues::VALUENOTFOUND)
		setMaxCondition((int)value);

	setConditionDamage(0);
}

bool WeaponObjectImplementation::isCertifiedFor(CreatureObject* object) {
	ManagedReference<PlayerObject*> ghost = object->getPlayerObject();

	if (ghost == NULL)
		return false;

	Vector<String>* certificationsRequired = weaponTemplate->getCertificationsRequired();

	for (int i = 0; i < certificationsRequired->size(); ++i) {
		String cert = certificationsRequired->get(i);

		if (!ghost->hasAbility(cert)) {
			return false;
		}
	}

	return true;
}

void WeaponObjectImplementation::decreasePowerupUses(CreatureObject* player) {
	if (hasPowerup()) {
		powerupObject->decreaseUses();
		if (powerupObject->getUses() < 1) {
			Locker locker(_this);
			StringIdChatParameter message("powerup", "prose_pup_expire"); //The powerup on your %TT has expired.
			message.setTT(getDisplayedName());

			player->sendSystemMessage(message);

			powerupObject = NULL;
		}
		sendAttributeListTo(player);
	}
}

String WeaponObjectImplementation::repairAttempt(int repairChance) {

	String message = "@error_message:";

	if(repairChance < 25) {
		message += "sys_repair_failed";
		setMaxCondition(1, true);
		setConditionDamage(0, true);
	} else if(repairChance < 50) {
		message += "sys_repair_imperfect";
		setMaxCondition(getMaxCondition() * .65f, true);
		setConditionDamage(0, true);
	} else if(repairChance < 75) {
		setMaxCondition(getMaxCondition() * .80f, true);
		setConditionDamage(0, true);
		message += "sys_repair_slight";
	} else {
		setMaxCondition(getMaxCondition() * .95f, true);
		setConditionDamage(0, true);
		message += "sys_repair_perfect";
	}

	return message;
}

void WeaponObjectImplementation::decay(CreatureObject* user, float damage) {
	if (_this != user->getSlottedObject("default_weapon")) {
		damage = damage / 10000.f;
		if (isSliced()) damage *= 1.1;
		if (hasPowerup()) damage *= 1.1;
		inflictDamage(_this, 0, damage, false, true);

		if ((conditionDamage - damage / maxCondition < 0.75) && (conditionDamage / maxCondition > 0.75))
			user->sendSystemMessage("@combat_effects:weapon_quarter");
		if ((conditionDamage - damage / maxCondition < 0.50) && (conditionDamage / maxCondition > 0.50))
			user->sendSystemMessage("@combat_effects:weapon_half");
	}
}
