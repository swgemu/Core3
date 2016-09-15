/*
 * ArmorObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "templates/tangible/ArmorObjectTemplate.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"
#include "templates/tangible/SharedWeaponObjectTemplate.h"

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

	specialResists = armorTemplate->getSpecialResists();

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
	if (hitLocation == ArmorObjectTemplate::NOLOCATION) {
		if (hasArrangementDescriptor("chest2"))
			hitLocation |= ArmorObjectTemplate::CHEST;
		if (hasArrangementDescriptor("bicep_r") || hasArrangementDescriptor("bicep_l") || hasArrangementDescriptor("bracer_upper_r") || hasArrangementDescriptor("bracer_upper_l") || hasArrangementDescriptor("gloves"))
			hitLocation |= ArmorObjectTemplate::ARMS;
		if (hasArrangementDescriptor("shoes") || hasArrangementDescriptor("pants1"))
			hitLocation |= ArmorObjectTemplate::LEGS;
		if (hasArrangementDescriptor("hat"))
			hitLocation |= ArmorObjectTemplate::HEAD;
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
	if ((isSpecial(SharedWeaponObjectTemplate::KINETIC) || isVulnerable(SharedWeaponObjectTemplate::KINETIC)) && getKinetic() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getKinetic(),1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic",
				txt.toString());
	}
	if ((isSpecial(SharedWeaponObjectTemplate::ENERGY) || isVulnerable(SharedWeaponObjectTemplate::ENERGY)) && getEnergy() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getEnergy(),1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy",
				txt.toString());
	}
	if ((isSpecial(SharedWeaponObjectTemplate::ELECTRICITY) || isVulnerable(SharedWeaponObjectTemplate::ELECTRICITY)) && getElectricity() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getElectricity(),1) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_electrical",
				txt.toString());
	}
	if ((isSpecial(SharedWeaponObjectTemplate::STUN) || isVulnerable(SharedWeaponObjectTemplate::STUN)) &&  getStun() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getStun(),1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun",
				txt.toString());
	}
	if ((isSpecial(SharedWeaponObjectTemplate::BLAST) || isVulnerable(SharedWeaponObjectTemplate::BLAST)) && getBlast() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getBlast(),1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast",
				txt.toString());
	}
	if ((isSpecial(SharedWeaponObjectTemplate::HEAT) || isVulnerable(SharedWeaponObjectTemplate::HEAT)) && getHeat() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getHeat(),1) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_heat",
				txt.toString());
	}
	if ((isSpecial(SharedWeaponObjectTemplate::COLD) || isVulnerable(SharedWeaponObjectTemplate::COLD)) && getCold() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getCold(),1) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_cold",
				txt.toString());
	}
	if ((isSpecial(SharedWeaponObjectTemplate::ACID) || isVulnerable(SharedWeaponObjectTemplate::ACID)) && getAcid() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getAcid(),1) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_acid",
				txt.toString());
	}
	if ((isSpecial(SharedWeaponObjectTemplate::LIGHTSABER) || isVulnerable(SharedWeaponObjectTemplate::LIGHTSABER)) && getLightSaber() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getLightSaber(),1) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_restraint",
				txt.toString());
	}
	//Check for Effectiveness protections(Normal)
	if (!isSpecial(SharedWeaponObjectTemplate::KINETIC) && !isVulnerable(SharedWeaponObjectTemplate::KINETIC) && getKinetic() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getKinetic(),1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic",
				txt.toString());
	}
	if (!isSpecial(SharedWeaponObjectTemplate::ENERGY) && !isVulnerable(SharedWeaponObjectTemplate::ENERGY) && getEnergy() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getEnergy(),1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy",
				txt.toString());
	}
	if (!isSpecial(SharedWeaponObjectTemplate::ELECTRICITY) && !isVulnerable(SharedWeaponObjectTemplate::ELECTRICITY) && getElectricity() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getElectricity(),1) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_electrical",
				txt.toString());
	}
	if (!isSpecial(SharedWeaponObjectTemplate::STUN) && !isVulnerable(SharedWeaponObjectTemplate::STUN) && getStun() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getStun(),1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun",
				txt.toString());
	}
	if (!isSpecial(SharedWeaponObjectTemplate::BLAST) && !isVulnerable(SharedWeaponObjectTemplate::BLAST) && getBlast() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getBlast(),1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast",
				txt.toString());
	}
	if (!isSpecial(SharedWeaponObjectTemplate::HEAT) && !isVulnerable(SharedWeaponObjectTemplate::HEAT) && getHeat() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getHeat(),1) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_heat",
				txt.toString());
	}
	if (!isSpecial(SharedWeaponObjectTemplate::COLD) && !isVulnerable(SharedWeaponObjectTemplate::COLD) && getCold() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getCold(),1) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_cold",
				txt.toString());
	}
	if (!isSpecial(SharedWeaponObjectTemplate::ACID) && !isVulnerable(SharedWeaponObjectTemplate::ACID) && getAcid() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getAcid(),1) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_acid",
				txt.toString());
	}
	if (!isSpecial(SharedWeaponObjectTemplate::LIGHTSABER) && !isVulnerable(SharedWeaponObjectTemplate::LIGHTSABER) && getLightSaber() >= 0.5) {
		StringBuffer txt;
		txt << Math::getPrecision(getLightSaber(),1) << "%";
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

	//Anti Decay Kit
	if(hasAntiDecayKit()){
		alm->insertAttribute("@veteran_new:antidecay_examine_title", "@veteran_new:antidecay_examine_text");
	}

	if (sliced)
		alm->insertAttribute("arm_attr", "@obj_attr_n:hacked");

}

bool ArmorObjectImplementation::isVulnerable(int type) {
	return isBroken() || (!isSpecial(type) && (vulnerabilites & type));
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

		if(sliced && effectivenessSlice > 1) {
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
	if (selectedID == 69 && player->hasSkill("combat_smuggler_slicing_03")) {
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
		session->initalizeSlicingMenu(player, _this.getReferenceUnsafeStaticCast());

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

		if (value != ValuesMap::VALUENOTFOUND) {
			specialResists |= type;
			setProtectionValue(type, value);
		}
	}
}

String ArmorObjectImplementation::getStringType(int type) {

	switch(type) {
	case SharedWeaponObjectTemplate::KINETIC:
		return "kineticeffectiveness";
		break;
	case SharedWeaponObjectTemplate::ENERGY:
		return "energyeffectiveness";
	break;
	case SharedWeaponObjectTemplate::ELECTRICITY:
		return "electricaleffectiveness";
		break;
	case SharedWeaponObjectTemplate::STUN:
		return "stuneffectiveness";
		break;
	case SharedWeaponObjectTemplate::BLAST:
		return "blasteffectiveness";
		break;
	case SharedWeaponObjectTemplate::HEAT:
		return "heateffectiveness";
		break;
	case SharedWeaponObjectTemplate::COLD:
		return "coldeffectiveness";
		break;
	case SharedWeaponObjectTemplate::ACID:
		return "acideffectiveness";
		break;
	case SharedWeaponObjectTemplate::LIGHTSABER:
		return "restraineffectiveness";
		break;
	default:
		return "";
	}
}

float ArmorObjectImplementation::getKinetic() {
	float value = getTypeValue(SharedWeaponObjectTemplate::KINETIC, kinetic);
	return value - getConditionReduction(value);
}

float ArmorObjectImplementation::getEnergy() {
	float value = getTypeValue(SharedWeaponObjectTemplate::ENERGY, energy);
	return value - getConditionReduction(value);
}
float ArmorObjectImplementation::getElectricity() {
	float value = getTypeValue(SharedWeaponObjectTemplate::ELECTRICITY, electricity);
	return value - getConditionReduction(value);
}
float ArmorObjectImplementation::getStun() {
	float value = getTypeValue(SharedWeaponObjectTemplate::STUN, stun);
	return value - getConditionReduction(value);
}

float ArmorObjectImplementation::getBlast() {
	float value = getTypeValue(SharedWeaponObjectTemplate::BLAST, blast);
	return value - getConditionReduction(value);
}
float ArmorObjectImplementation::getHeat() {
	float value = getTypeValue(SharedWeaponObjectTemplate::HEAT, heat);
	return value - getConditionReduction(value);
}

float ArmorObjectImplementation::getCold() {
	float value = getTypeValue(SharedWeaponObjectTemplate::COLD, cold);
	return value - getConditionReduction(value);
}

float ArmorObjectImplementation::getAcid() {
	float value = getTypeValue(SharedWeaponObjectTemplate::ACID, acid);
	return value - getConditionReduction(value);
}

float ArmorObjectImplementation::getLightSaber() {
	float value = getTypeValue(SharedWeaponObjectTemplate::LIGHTSABER, lightSaber);
	return value - getConditionReduction(value);
}


void ArmorObjectImplementation::setProtectionValue(int type, float value) {

	if (type & SharedWeaponObjectTemplate::KINETIC)
		setKinetic(value);
	if (type & SharedWeaponObjectTemplate::ENERGY)
		setEnergy(value);
	if (type & SharedWeaponObjectTemplate::BLAST)
		setBlast(value);
	if (type & SharedWeaponObjectTemplate::STUN)
		setStun(value);
	if (type & SharedWeaponObjectTemplate::LIGHTSABER)
		setLightSaber(value);
	if (type & SharedWeaponObjectTemplate::HEAT)
		setHeat(value);
	if (type & SharedWeaponObjectTemplate::COLD)
		setCold(value);
	if (type & SharedWeaponObjectTemplate::ACID)
		setAcid(value);
	if (type & SharedWeaponObjectTemplate::ELECTRICITY)
		setElectricity(value);
}
