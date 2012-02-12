/*
 * WeaponObjectImplementation.cpp
 *
 *  Created on: 30/07/2009
 *      Author: victor
 */

#include "WeaponObject.h"
#include "server/zone/packets/tangible/WeaponObjectMessage3.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/templates/tangible/SharedWeaponObjectTemplate.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

#include "server/zone/objects/player/sessions/SlicingSession.h"


void WeaponObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	weaponTemplate = dynamic_cast<SharedWeaponObjectTemplate*>(TemplateManager::instance()->getTemplate(serverObjectCRC));

	setLoggingName("WeaponObject");

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

	area = weaponTemplate->getArea();

	float templateAttackSpeed = weaponTemplate->getAttackSpeed();

	if (templateAttackSpeed > 1)
		attackSpeed = templateAttackSpeed;

	setSliceable(true);
}

void WeaponObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending weapon object baselines");

	BaseMessage* weao3 = new WeaponObjectMessage3(_this);
	player->sendMessage(weao3);
}

int WeaponObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 69) {
		if (isSliced()) {
			player->sendSystemMessage("@slicing/slicing:already_sliced");
			return 0;
		}

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::SLICING);
		ManagedReference<SlicingSession*> session = dynamic_cast<SlicingSession*>(facade.get());

		if (session != NULL) {
			player->sendSystemMessage("@slicing/slicing:already_slicing");
			return 0;
		}

		//Create Session
		session = new SlicingSession(player);
		session->initalizeSlicingMenu(player, _this);

		return 0;

	} else
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
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

	float speed = round(10 * attackSpeed) / 10;

	StringBuffer spdtxt;

	spdtxt << speed;

	if ((int(round(speed * 10)) % 10) == 0)
		spdtxt << ".0";

	alm->insertAttribute("wpn_attack_speed", spdtxt.toString());

	/*if (area != 0.0f)
		alm->insertAttribute("area", Math::getPrecision(area, 0));*/

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

	if (sliced == 1)
		alm->insertAttribute("wpn_attr", "@obj_attr_n:hacked1");

	//generatePowerup(alm);
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
