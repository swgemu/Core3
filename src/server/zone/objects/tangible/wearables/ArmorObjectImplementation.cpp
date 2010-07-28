/*
 * ArmorObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "ArmorObject.h"
#include "server/zone/templates/tangible/ArmorObjectTemplate.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"

void ArmorObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("ArmorObject");
}

void ArmorObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	WearableObjectImplementation::loadTemplateData(templateData);

	if (!templateData->isArmorObjectTemplate())
		return;

	ArmorObjectTemplate* armorTemplate = (ArmorObjectTemplate*) templateData;

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

	specialBase = armorTemplate->getSpecialBase();

}

void ArmorObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	WearableObjectImplementation::fillAttributeList(alm, object);

	if (socketsLeft() > 0)
		alm->insertAttribute("sockets", socketsLeft());

	wearableSkillModMap.insertStatMods(alm);

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
	if (isSpecial("kineticeffectiveness") && kinetic >= 0.5) {
		StringBuffer txt;
		txt << round(kinetic) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic",
				txt.toString());
	}
	if (isSpecial("energyeffectiveness") && energy >= 0.5) {
		StringBuffer txt;
		txt << round(energy) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy",
				txt.toString());
	}
	if (isSpecial("electricaleffectiveness") && electricity >= 0.5) {
		StringBuffer txt;
		txt << round(electricity) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_electrical",
				txt.toString());
	}
	if (isSpecial("stuneffectiveness") && stun >= 0.5) {
		StringBuffer txt;
		txt << round(stun) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun",
				txt.toString());
	}
	if (isSpecial("blasteffectiveness") && blast >= 0.5) {
		StringBuffer txt;
		txt << round(blast) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast",
				txt.toString());
	}
	if (isSpecial("heateffectiveness") && heat >= 0.5) {
		StringBuffer txt;
		txt << round(heat) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_heat",
				txt.toString());
	}
	if (isSpecial("coldeffectiveness") && cold >= 0.5) {
		StringBuffer txt;
		txt << round(cold) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_cold",
				txt.toString());
	}
	if (isSpecial("acideffectiveness") && acid >= 0.5) {
		StringBuffer txt;
		txt << round(acid) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_acid",
				txt.toString());
	}
	if (isSpecial("restraineffectiveness") && lightSaber >= 0.5) {
		StringBuffer txt;
		txt << round(lightSaber) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_restraint",
				txt.toString());
	}
	//Check for Effectiveness protections(Normal)
	if (!isSpecial("kineticeffectiveness") && kinetic >= 0.5) {
		StringBuffer txt;
		txt << round(kinetic) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic",
				txt.toString());
	}
	if (!isSpecial("energyeffectiveness") && energy >= 0.5) {
		StringBuffer txt;
		txt << round(energy) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy",
				txt.toString());
	}
	if (!isSpecial("electricaleffectiveness") && electricity >= 0.5) {
		StringBuffer txt;
		txt << round(electricity) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_electrical",
				txt.toString());
	}
	if (!isSpecial("stuneffectiveness") && stun >= 0.5) {
		StringBuffer txt;
		txt << round(stun) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun",
				txt.toString());
	}
	if (!isSpecial("blasteffectiveness") && blast >= 0.5) {
		StringBuffer txt;
		txt << round(blast) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast",
				txt.toString());
	}
	if (!isSpecial("heateffectiveness") && heat >= 0.5) {
		StringBuffer txt;
		txt << round(heat) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_heat",
				txt.toString());
	}
	if (!isSpecial("coldeffectiveness") && cold >= 0.5) {
		StringBuffer txt;
		txt << round(cold) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_cold",
				txt.toString());
	}
	if (!isSpecial("acideffectiveness") && acid >= 0.5) {
		StringBuffer txt;
		txt << round(acid) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_acid",
				txt.toString());
	}
	if (!isSpecial("restraineffectiveness") && lightSaber >= 0.5) {
		StringBuffer txt;
		txt << round(lightSaber) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint",
				txt.toString());
	}

	//Vulnerabilities
	if (kinetic < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (energy < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (electricity < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (stun < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (blast < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (heat < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (cold < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (acid < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_acid", "-");

	if (lightSaber < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");

	//Encumbrances
	alm->insertAttribute("cat_armor_encumbrance.health", healthEncumbrance);

	alm->insertAttribute("cat_armor_encumbrance.action", actionEncumbrance);

	alm->insertAttribute("cat_armor_encumbrance.mind", mindEncumbrance);

	if (craftersName != "") {
		alm->insertAttribute("crafter", craftersName);
	}

	/*if (craftedSerial != "") {
		alm->insertAttribute("serial_number", craftedSerial);
	}*/

	if (sliced)
		alm->insertAttribute("arm_attr", "@obj_attr_n:hacked");

}

void ArmorObjectImplementation::updateCraftingValues(ManufactureSchematic* schematic) {

	WearableObjectImplementation::updateCraftingValues(schematic);

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
	CraftingValues* craftingValues = schematic->getCraftingValues();
	//craftingValues->toString();

	setRating((int) craftingValues->getCurrentValue("armor_rating"));

	setHealthEncumbrance((int) craftingValues->getCurrentValue(
			"armor_health_encumbrance"));
	setActionEncumbrance((int) craftingValues->getCurrentValue(
			"armor_action_encumbrance"));
	setMindEncumbrance((int) craftingValues->getCurrentValue(
			"armor_mind_encumbrance"));

	float base = craftingValues->getCurrentValue("armor_effectiveness");

	setProtection(schematic, "kineticeffectiveness", base);
	setProtection(schematic, "energyeffectiveness", base);
	setProtection(schematic, "electricaleffectiveness", base);
	setProtection(schematic, "stuneffectiveness", base);
	setProtection(schematic, "blasteffectiveness", base);
	setProtection(schematic, "heateffectiveness", base);
	setProtection(schematic, "coldeffectiveness", base);
	setProtection(schematic, "acideffectiveness", base);
	setProtection(schematic, "restraineffectiveness", base);

	setMaxCondition((int) craftingValues->getCurrentValue("armor_integrity"));
	setConditionDamage(0);

	schematic->setFirstCraftingUpdate();
}

void ArmorObjectImplementation::setProtection(ManufactureSchematic* schematic,
		const String& type, float base) {

	CraftingValues* craftingValues = schematic->getCraftingValues();

	float value = craftingValues->getCurrentValue(type);

	if (value == CraftingValues::VALUENOTFOUND
			&& schematic->getFirstCraftingUpdate()) {
		craftingValues->lockValue(type);
	}

	if (value == CraftingValues::VALUENOTFOUND) {
		if (isVulnerable(type))
			setProtectionValue(type, 0.0f);
		else
			setProtectionValue(type, base);
	} else {
		if (value + base > 80.0f)
			setProtectionValue(type, 80.0f);
		else
			setProtectionValue(type, value + base);
	}
}

void ArmorObjectImplementation::setProtectionValue(const String& type, float value) {

	if (type == "kineticeffectiveness") {
		setKinetic(value);
	} else if (type == "energyeffectiveness") {
		setEnergy(value);
	} else if (type == "electricaleffectiveness") {
		setElectricity(value);
	} else if (type == "stuneffectiveness") {
		setStun(value);
	} else if (type == "blasteffectiveness") {
		setBlast(value);
	} else if (type == "heateffectiveness") {
		setHeat(value);
	} else if (type == "coldeffectiveness") {
		setCold(value);
	} else if (type == "acideffectiveness") {
		setAcid(value);
	} else if (type == "restraineffectiveness") {
		setLightSaber(value);
	}

}
