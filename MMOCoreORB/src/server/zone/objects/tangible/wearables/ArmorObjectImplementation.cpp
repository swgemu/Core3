/*
 * ArmorObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "ArmorObject.h"
#include "server/zone/templates/tangible/ArmorObjectTemplate.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"

void ArmorObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("ArmorObject");
}

void ArmorObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	WearableObjectImplementation::loadTemplateData(templateData);

	if (!templateData->isArmorObjectTemplate())
		return;

	ArmorObjectTemplate* armorTemplate = cast<ArmorObjectTemplate*>( templateData);

	vulnerabilites = armorTemplate->getVulnerabilites();

	healthEncumbrance = armorTemplate->getHealthEncumbrance();
	actionEncumbrance = armorTemplate->getActionEncumbrance();
	mindEncumbrance = armorTemplate->getMindEncumbrance();

	rating = armorTemplate->getRating();

	kinetic = armorTemplate->getKinetic();
	energy = armorTemplate->getEnergy();
	electricity = armorTemplate->getElectricity();
	stun = armorTemplate->getStun();
	blast = armorTemplate->getBlast();
	heat = armorTemplate->getHeat();
	cold = armorTemplate->getCold();
	acid = armorTemplate->getAcid();
	lightSaber = armorTemplate->getLightSaber();

	hitLocation = armorTemplate->getHitLocation();
	if (hitLocation == CombatManager::NOLOCATION) {
		if (hasArrangementDescriptor("chest2"))
			hitLocation |= CombatManager::CHEST;
		if (hasArrangementDescriptor("bicep_r") || hasArrangementDescriptor("bicep_l") || hasArrangementDescriptor("bracer_upper_r") || hasArrangementDescriptor("bracer_upper_l") || hasArrangementDescriptor("gloves"))
			hitLocation |= CombatManager::ARMS;
		if (hasArrangementDescriptor("shoes") || hasArrangementDescriptor("pants1"))
			hitLocation |= CombatManager::LEGS;
		if (hasArrangementDescriptor("hat"))
			hitLocation |= CombatManager::HEAD;
	}

	setSliceable(true);
}

void ArmorObjectImplementation::notifyLoadFromDatabase() {
	WearableObjectImplementation::notifyLoadFromDatabase();

	if (templateObject == NULL)
		return;

	if (rating != LIGHT && templateObject->getClientTemplateFileName().contains("armor_bounty_hunter_"))
		rating = LIGHT;
}

void ArmorObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	WearableObjectImplementation::fillAttributeList(alm, object);

	//Armor Rating
	if (rating == LIGHT)
		alm->insertAttribute("armorrating", "@obj_attr_n:armor_pierce_light"); //Light
	else if (rating == MEDIUM)
		alm->insertAttribute("armorrating", "@obj_attr_n:armor_pierce_medium"); //Medium
	else if (rating == HEAVY)
		alm->insertAttribute("armorrating", "@obj_attr_n:armor_pierce_heavy"); //Heavy
	else
		alm->insertAttribute("armorrating", "@obj_attr_n:armor_pierce_none"); //None

	//Check for special protections
	if (isSpecial(WeaponObject::KINETIC) && getKinetic() >= 0.5) {
		StringBuffer txt;
		txt << round(getKinetic()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic",
				txt.toString());
	}
	if (isSpecial(WeaponObject::ENERGY) && getEnergy() >= 0.5) {
		StringBuffer txt;
		txt << round(getEnergy()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy",
				txt.toString());
	}
	if (isSpecial(WeaponObject::ELECTRICITY) && getElectricity() >= 0.5) {
		StringBuffer txt;
		txt << round(getElectricity()) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_electrical",
				txt.toString());
	}
	if (isSpecial(WeaponObject::STUN) &&  getStun() >= 0.5) {
		StringBuffer txt;
		txt << round(getStun()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun",
				txt.toString());
	}
	if (isSpecial(WeaponObject::BLAST) && getBlast() >= 0.5) {
		StringBuffer txt;
		txt << round(getBlast()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast",
				txt.toString());
	}
	if (isSpecial(WeaponObject::HEAT) && getHeat() >= 0.5) {
		StringBuffer txt;
		txt << round(getHeat()) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_heat",
				txt.toString());
	}
	if (isSpecial(WeaponObject::COLD) && getCold() >= 0.5) {
		StringBuffer txt;
		txt << round(getCold()) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_cold",
				txt.toString());
	}
	if (isSpecial(WeaponObject::ACID) && getAcid() >= 0.5) {
		StringBuffer txt;
		txt << round(getAcid()) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_acid",
				txt.toString());
	}
	if (isSpecial(WeaponObject::LIGHTSABER) && getLightSaber() >= 0.5) {
		StringBuffer txt;
		txt << round(getLightSaber()) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_restraint",
				txt.toString());
	}
	//Check for Effectiveness protections(Normal)
	if (!isSpecial(WeaponObject::KINETIC) && getKinetic() >= 0.5) {
		StringBuffer txt;
		txt << round(getKinetic()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic",
				txt.toString());
	}
	if (!isSpecial(WeaponObject::ENERGY) && getEnergy() >= 0.5) {
		StringBuffer txt;
		txt << round(getEnergy()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy",
				txt.toString());
	}
	if (!isSpecial(WeaponObject::ELECTRICITY) && getElectricity() >= 0.5) {
		StringBuffer txt;
		txt << round(getElectricity()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_electrical",
				txt.toString());
	}
	if (!isSpecial(WeaponObject::STUN) && getStun() >= 0.5) {
		StringBuffer txt;
		txt << round(getStun()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun",
				txt.toString());
	}
	if (!isSpecial(WeaponObject::BLAST) && getBlast() >= 0.5) {
		StringBuffer txt;
		txt << round(getBlast()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast",
				txt.toString());
	}
	if (!isSpecial(WeaponObject::HEAT) && getHeat() >= 0.5) {
		StringBuffer txt;
		txt << round(getHeat()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_heat",
				txt.toString());
	}
	if (!isSpecial(WeaponObject::COLD) && getCold() >= 0.5) {
		StringBuffer txt;
		txt << round(getCold()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_cold",
				txt.toString());
	}
	if (!isSpecial(WeaponObject::ACID) && getAcid() >= 0.5) {
		StringBuffer txt;
		txt << round(getAcid()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_acid",
				txt.toString());
	}
	if (!isSpecial(WeaponObject::LIGHTSABER) && getLightSaber() >= 0.5) {
		StringBuffer txt;
		txt << round(getLightSaber()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint",
				txt.toString());
	}

	//Vulnerabilities
	if (getKinetic() < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (getEnergy() < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (getElectricity() < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (getStun() < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (getBlast() < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (getHeat() < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (getCold() < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (getAcid() < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_acid", "-");

	if (getLightSaber() < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");

	//Encumbrances
	alm->insertAttribute("cat_armor_encumbrance.health", getHealthEncumbrance());

	alm->insertAttribute("cat_armor_encumbrance.action", getActionEncumbrance());

	alm->insertAttribute("cat_armor_encumbrance.mind", getMindEncumbrance());

	if (sliced)
		alm->insertAttribute("arm_attr", "@obj_attr_n:hacked");

}

bool ArmorObjectImplementation::isVulnerable(int type) {
	return (!isSpecial(type) && (vulnerabilites & type));
}

float ArmorObjectImplementation::getTypeValue(int type, float value) {

	int newValue = 0;

	if(vulnerabilites & type)
		newValue = value;

	else if(isSpecial(type)) {
		newValue = specialProtection + value;
		if(newValue > 80)
			newValue = 80;
	} else {
		newValue = baseProtection + value;
		newValue *= effectivenessSlice;

		if(sliced) {
			if(newValue > 90)
				newValue = 90;
		} else {
			if(newValue > 80)
				newValue = 80;
		}
	}

	return newValue;
}

int ArmorObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
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
		session->initalizeSlicingMenu(player, _this.get());

		return 0;

	} else
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void ArmorObjectImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {

	WearableObjectImplementation::updateCraftingValues(values, firstUpdate);

	/*
	 * Incoming Values:					Ranges:
	 * sockets							All depend on type of armor
	 * hit_points
	 * armor_effectiveness
	 * armor_integrity
	 * armor_health_encumbrance
	 * armor_action_encumbrance
	 * armor_mind_encumbrance
	 * armor_rating
	 * armor_special_type
	 * armor_special_effectiveness
	 * armor_special_integrity
	 */
	//craftingValues->toString();

	if(firstUpdate) {

		kinetic = 0;
		energy = 0;
		electricity = 0;
		stun = 0;
		blast = 0;
		heat = 0;
		cold = 0;
		acid = 0;
		lightSaber = 0;
		baseProtection = 0;
		specialProtection = 0;
		effectivenessSlice = 1;
		encumbranceSlice = 1;

		calculateSpecialProtection(values);

		setRating((int) values->getCurrentValue("armor_rating"));

		setConditionDamage(0);
	}

	setHealthEncumbrance((int) values->getCurrentValue(
			"armor_health_encumbrance"));
	setActionEncumbrance((int) values->getCurrentValue(
			"armor_action_encumbrance"));
	setMindEncumbrance((int) values->getCurrentValue(
			"armor_mind_encumbrance"));

	setMaxCondition((int) values->getCurrentValue("armor_integrity"));

	baseProtection = values->getCurrentValue("armor_effectiveness");

	/// Because SOE had to be stupid and not make the rules consistant
	if(values->getMaxValue("armor_special_effectiveness") == values->getMinValue("armor_special_effectiveness"))
		specialProtection = values->getCurrentValue("armor_effectiveness");
	else
		specialProtection = values->getCurrentValue("armor_special_effectiveness");

}

void ArmorObjectImplementation::calculateSpecialProtection(CraftingValues* craftingValues) {

	specialResists = ((int)(craftingValues->getCurrentValue("armor_special_type")));

	for (int i = 0; i <= 8; ++i) {

		int type = pow((float)2,i);

		String subtitle = getStringType(type);
		float value = craftingValues->getCurrentValue(subtitle);

		if(value != CraftingValues::VALUENOTFOUND) {

			specialResists |= type;
			setProtectionValue(type, value);

		}
	}
}

String ArmorObjectImplementation::getStringType(int type) {

	switch(type) {
	case WeaponObject::KINETIC:
		return "kineticeffectiveness";
		break;
	case WeaponObject::ENERGY:
		return "energyeffectiveness";
	break;
	case WeaponObject::ELECTRICITY:
		return "electricaleffectiveness";
		break;
	case WeaponObject::STUN:
		return "stuneffectiveness";
		break;
	case WeaponObject::BLAST:
		return "blasteffectiveness";
		break;
	case WeaponObject::HEAT:
		return "heateffectiveness";
		break;
	case WeaponObject::COLD:
		return "coldeffectiveness";
		break;
	case WeaponObject::ACID:
		return "acideffectiveness";
		break;
	case WeaponObject::LIGHTSABER:
		return "restraineffectiveness";
		break;
	default:
		return "";
	}
}

void ArmorObjectImplementation::setProtectionValue(int type, float value) {

	if (type & WeaponObject::KINETIC)
		setKinetic(value);
	if (type & WeaponObject::ENERGY)
		setEnergy(value);
	if (type & WeaponObject::BLAST)
		setBlast(value);
	if (type & WeaponObject::STUN)
		setStun(value);
	if (type & WeaponObject::LIGHTSABER)
		setLightSaber(value);
	if (type & WeaponObject::HEAT)
		setHeat(value);
	if (type & WeaponObject::COLD)
		setCold(value);
	if (type & WeaponObject::ACID)
		setAcid(value);
	if (type & WeaponObject::ELECTRICITY)
		setElectricity(value);
}
