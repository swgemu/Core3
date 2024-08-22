/*
 * TurretObjectImplementation.cpp
 *
 * Created: 2024-08-10
 * Author: Hakry
 *
 */

#include "server/zone/objects/installation/TurretObject.h"
#include "templates/installation/SharedInstallationObjectTemplate.h"
#include "server/zone/objects/installation/components/TurretDataComponent.h"

void TurretObjectImplementation::initializeTransientMembers() {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	SharedInstallationObjectTemplate* inso = dynamic_cast<SharedInstallationObjectTemplate*>(getObjectTemplate());

	if (inso == nullptr) {
		return;
	}

	uint32 defaultWeaponCRC = inso->getWeapon().hashCode();

	ManagedReference<WeaponObject*> weapon = (zoneServer->createObject(defaultWeaponCRC, 0)).castTo<WeaponObject*>();

	if (weapon == nullptr) {
		return;
	}

	// Assign the turret weapon
	setTurretWeapon(weapon);

	InstallationObjectImplementation::initializeTransientMembers();
}

void TurretObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	if (!templateData->isSharedInstallationObjectTemplate()) {
		return;
	}

	SharedInstallationObjectTemplate* inso = dynamic_cast<SharedInstallationObjectTemplate*>(templateData);

	if (inso == nullptr) {
		return;
	}

	setArmorRating(inso->getArmorRating());

	setKinetic(inso->getKinetic());
	setEnergy(inso->getEnergy());
	setElectricity(inso->getElectricity());
	setStun(inso->getStun());
	setBlast(inso->getBlast());
	setHeat(inso->getHeat());
	setCold(inso->getCold());
	setAcid(inso->getAcid());
	setLightSaber(inso->getLightSaber());

	setChanceHit(inso->getChanceHit());

	InstallationObjectImplementation::loadTemplateData(templateData);
}

void TurretObjectImplementation::createChildObjects() {
	if (!isTurret()) {
		InstallationObjectImplementation::createChildObjects();
		return;
	}
}

void TurretObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	if (alm == nullptr || player == nullptr) {
		return;
	}

	InstallationObjectImplementation::fillAttributeList(alm, player);

	alm->insertAttribute("condition", String::valueOf(getMaxCondition() - getConditionDamage()) + "/" + String::valueOf(getMaxCondition()));

	int objectCount = getContainerObjectsSize();
	int volumeLimit = getContainerVolumeLimit();

	StringBuffer contentsString;
	contentsString << objectCount << "/" << volumeLimit;

	alm->insertAttribute("contents", contentsString);

	unsigned int rating = getArmorRating();

	if (rating == 0) {
		alm->insertAttribute("armorrating", "None");
	} else if (rating == 1) {
		alm->insertAttribute("armorrating", "Light");
	} else if (rating == 2) {
		alm->insertAttribute("armorrating", "Medium");
	} else if (rating == 3) {
		alm->insertAttribute("armorrating", "Heavy");
	}

	float kineticResist = getKinetic();
	float energyResist = getEnergy();
	float electricityResist = getElectricity();
	float stunResist = getStun();
	float blastResist = getBlast();
	float heatResist = getHeat();
	float coldResist = getCold();
	float acidResist = getAcid();
	float lightsaberResist = getLightSaber();

	if (kineticResist > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(kineticResist, 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic", txt.toString());
	}

	if (energyResist > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(energyResist, 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy", txt.toString());
	}

	if (electricityResist > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(electricityResist, 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_electrical", txt.toString());
	}

	if (stunResist > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(stunResist, 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun", txt.toString());
	}

	if (blastResist > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(blastResist, 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast", txt.toString());
	}

	if (heatResist > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(heatResist, 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_heat", txt.toString());
	}

	if (coldResist > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(coldResist, 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_cold", txt.toString());
	}

	if (acidResist > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(acidResist, 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_acid", txt.toString());
	}

	if (lightsaberResist > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(lightsaberResist, 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_restraint", txt.toString());
	}

	if (kineticResist > 0 && kineticResist <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(kineticResist, 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic", txt.toString());
	}

	if (energyResist > 0 && energyResist <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(energyResist, 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy", txt.toString());
	}

	if (electricityResist > 0 && electricityResist <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(electricityResist, 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_electrical", txt.toString());
	}

	if (stunResist > 0 && stunResist <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(stunResist, 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun", txt.toString());
	}

	if (blastResist > 0 && blastResist <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(blastResist, 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast", txt.toString());
	}

	if (heatResist > 0 && heatResist <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(heatResist, 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_heat", txt.toString());
	}

	if (coldResist > 0 && coldResist <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(coldResist, 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_cold", txt.toString());
	}

	if (acidResist > 0 && acidResist <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(acidResist, 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_acid", txt.toString());
	}

	if (lightsaberResist > 0 && lightsaberResist <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getLightSaber(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint", txt.toString());
	}

	if (kineticResist < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (energyResist < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (electricityResist < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (stunResist < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (blastResist < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (heatResist < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (coldResist < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (acidResist < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_acid", "-");

	if (lightsaberResist < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");
}

/*
*
*	Turret Armor
*
*/

float TurretObjectImplementation::getArmorResistReduction(float value) {
	if (value == -1) {
		return value;
	}

	// if (getZone )

	int maxCondition = getMaxCondition();

	// Damage not prevented by armor resists
	int unmitigatedDamage = getUnmitigatedDamage();

	// Percent of damage not prevented by armor resists compared to maxCondition
	// Only accounts if the turret has that resistance type.
	float mitigatedAmount = unmitigatedDamage / (float)maxCondition;

#ifdef DEBUG_RESIST_DECAY
	info (true) << " Value of damage mitigated by armor = " << mitigatedAmount;
#endif

	float newValue = value;

	// Decay resists when unmitigated damage is greater than 25% of maxConiditon
	if (mitigatedAmount > 0.25f) {
		// Reduce resists 2% for every 1% of damage passed armor resists greater than 25% of max condition
		// Range to reduce armor is 75% to 50% totaling a max of 50% reduction of resists
		float reduction = (mitigatedAmount - 0.25f) * 2.f;

		// Resists never drop below 50%
		reduction = 1.f - (reduction > 0.50f ? 0.50f : reduction);

		newValue = (value * reduction);

#ifdef DEBUG_RESIST_DECAY
		info(true) << " max condition = " << maxCondition << " Total Damage Mitigated = " << unmitigatedDamage << " Start Armor value: " << value << " New Armor Value = " << newValue << " Reduction percent = " << reduction;
#endif
	}

	return newValue;
}

float TurretObjectImplementation::getKinetic() {
	return getArmorResistReduction(kinetic);
}

float TurretObjectImplementation::getEnergy() {
	return getArmorResistReduction(energy);
}

float TurretObjectImplementation::getElectricity() {
	return getArmorResistReduction(electricity);
}

float TurretObjectImplementation::getStun() {
	return getArmorResistReduction(stun);
}

float TurretObjectImplementation::getBlast() {
	return getArmorResistReduction(blast);
}

float TurretObjectImplementation::getHeat() {
	return getArmorResistReduction(heat);
}

float TurretObjectImplementation::getCold() {
	return getArmorResistReduction(cold);
}

float TurretObjectImplementation::getAcid() {
	return getArmorResistReduction(acid);
}

float TurretObjectImplementation::getLightSaber() {
	return getArmorResistReduction(lightsaber);
}
