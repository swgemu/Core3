/*
 * TurretDataComponent.cpp
 *
 *  Created on: Dec 10, 2012
 *      Author: root
 */

#include "TurretDataComponent.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/installation/components/TurretFireTask.h"
#include "server/zone/Zone.h"

void TurretDataComponent::initializeTransientMembers() {
	ManagedReference<SceneObject*> turret = getParent();

	if (turret == nullptr) {
		return;
	}

	templateData = dynamic_cast<SharedInstallationObjectTemplate*>(turret->getObjectTemplate());

	SceneObject* sceneObject = turret->getSlottedObject("hold_r");

	if (sceneObject == nullptr) {
		return;
	}

	WeaponObject* weapon = cast<WeaponObject*>(sceneObject);

	setWeapon(weapon);
}

void TurretDataComponent::setWeapon(WeaponObject* weapon) {
	if (weapon != nullptr) {
		attackSpeed = weapon->getAttackSpeed();
		maxRange = weapon->getMaxRange();
	}
}

Vector<CreatureObject*> TurretDataComponent::getAvailableTargets(bool aggroOnly) {
	Vector<CreatureObject*> targets;

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(getParent());

	if (turret == nullptr)
		return targets;

	CloseObjectsVector* vec = (CloseObjectsVector*)turret->getCloseObjects();

	SortedVector<QuadTreeEntry*> closeObjects;

	vec->safeCopyReceiversTo(closeObjects, CloseObjectsVector::CREOTYPE);

	int targetTotal = 0;

	for (int i = 0; i < closeObjects.size(); ++i) {
		CreatureObject* creo = cast<CreatureObject*>(closeObjects.get(i));

		if (creo != nullptr && checkTarget(creo, turret, aggroOnly)) {
			targets.add(creo);
		}
	}

	return targets;
}

CreatureObject* TurretDataComponent::selectTarget() {
	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(getParent());

	if (turret == nullptr)
		return nullptr;

	ManagedReference<CreatureObject*> lastTarget = lastAutoTarget.get();

	bool isVillageTurret = turret->getObjectTemplate()->getFullTemplateString().contains("turret_fs_village");

	if (!isVillageTurret || (lastTarget == nullptr || !checkTarget(lastTarget, turret, true))) {
		lastAutoTarget = nullptr;

		Vector<CreatureObject*> targets = getAvailableTargets(true);

		if (targets.size() == 0)
			return nullptr;

		lastTarget = targets.get(System::random(targets.size() - 1));
		lastAutoTarget = lastTarget;
	}

	return lastTarget;
}

bool TurretDataComponent::checkTarget(CreatureObject* creature, TangibleObject* turret, bool aggroOnly) {
	if (creature == nullptr || turret == nullptr)
		return false;

	if (!creature->isAttackableBy(turret) || !turret->isInRange(creature, maxRange))
		return false;

	if (aggroOnly && !turret->hasDefender(creature) && !turret->isAggressiveTo(creature))
		return false;

	if (!CollisionManager::checkLineOfSight(creature, turret))
		return false;

	return true;
}

void TurretDataComponent::updateAutoCooldown(float secondsToAdd) {
	int milisecondsToAdd = secondsToAdd*1000;
	nextAutoFireTime = Time();
	nextAutoFireTime.addMiliTime(milisecondsToAdd);
}

void TurretDataComponent::scheduleFireTask(CreatureObject* target, TangibleObject* terminal, int delay) {
	//PRE: turret is locked

	if (numberOfPlayersInRange.get() < 1)
		return;

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(getParent());

	if (turret->getZone() == nullptr)
		return;

	if (turretFireTask == nullptr) {
		turretFireTask = new TurretFireTask(turret, terminal, target != nullptr);
	}

	TurretFireTask* task = turretFireTask.castTo<TurretFireTask*>();

	if (task == nullptr)
		return;

	if (task->isManualFireTask()) {
		if (target != nullptr && target != getManualTarget())
			setManualTarget(target);
	} else {
		if (target != nullptr) {
			if (target != getManualTarget())
				setManualTarget(target);

			task->setManualFireTask(true);
			task->setTerminal(terminal);
		}
	}

	if (target == nullptr && !task->isManualFireTask()) {
		delay += getRescheduleDelay();
	}

	if (!task->isScheduled()) {
		if (delay == 0)
			task->execute();
		else
			task->schedule(delay);

	} else if (task->isManualFireTask()) {
		task->reschedule(attackSpeed * 1000);
	}
}

void TurretDataComponent::rescheduleFireTask(bool wasManual, bool isManual) {
	if (numberOfPlayersInRange.get() < 1)
		return;

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(getParent());

	if (turret == nullptr || turret->getZone() == nullptr)
		return;

	TurretFireTask* task = turretFireTask.castTo<TurretFireTask*>();

	if (task == nullptr)
		return;

	if (wasManual) {
		updateAutoCooldown(getAutoFireTimeout());
	} else {
		updateAutoCooldown(attackSpeed);
	}

	if (isManual) {
		task->reschedule(attackSpeed * 1000);
	} else {
		setManualTarget(nullptr);
		task->setManualFireTask(false);
		task->setTerminal(nullptr);
		task->reschedule(getRescheduleDelay());
	}
}

int TurretDataComponent::getAutoFireTimeout() {
	int cooldown = 20;

	ManagedReference<InstallationObject*> turret = cast<InstallationObject*>(getParent());

	if (turret != nullptr) {
		Zone* zone = turret->getZone();

		if (zone != nullptr) {
			GCWManager* gcwMan = zone->getGCWManager();

			if (gcwMan != nullptr)
				cooldown = gcwMan->getTurretAutoFireTimeout();
		}
	}

	return cooldown;
}

void TurretDataComponent::fillAttributeList(AttributeListMessage* alm) {
	if (getParent() == nullptr)
		return;

	ManagedReference<InstallationObject*> turret = cast<InstallationObject*>(getParent());

	if (turret == nullptr)
		return;

	alm->insertAttribute("condition",String::valueOf(turret->getMaxCondition() - turret->getConditionDamage()) + "/" + String::valueOf(turret->getMaxCondition()));

	int objectCount = turret->getSlottedObjectsSize();
	int volumeLimit = turret->getContainerVolumeLimit();

	StringBuffer contentsString;
	contentsString << objectCount << "/" << volumeLimit;

	alm->insertAttribute("contents", contentsString);

	if (getArmorRating() == 0)
		alm->insertAttribute("armorrating", "None");
	else if (getArmorRating() == 1)
		alm->insertAttribute("armorrating", "Light");
	else if (getArmorRating() == 2)
		alm->insertAttribute("armorrating", "Medium");
	else if (getArmorRating() == 3)
		alm->insertAttribute("armorrating", "Heavy");


	if (getKinetic() > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getKinetic(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic", txt.toString());
	}

	if (getEnergy() > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getEnergy(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy", txt.toString());
	}

	if (getElectricity() > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getElectricity(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_electrical", txt.toString());
	}

	if (getStun() > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getStun(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun", txt.toString());
	}

	if (getBlast() > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getBlast(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast", txt.toString());
	}

	if (getHeat() > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getHeat(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_heat", txt.toString());
	}

	if (getCold() > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getCold(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_cold", txt.toString());
	}

	if (getAcid() > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getAcid(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_acid", txt.toString());
	}

	if (getLightSaber() > 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getLightSaber(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_restraint", txt.toString());
	}

	if (getKinetic() > 0 && getKinetic() <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getKinetic(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic", txt.toString());
	}

	if (getEnergy() > 0 && getEnergy() <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getEnergy(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy", txt.toString());
	}

	if (getElectricity() > 0 && getElectricity() <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getElectricity(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_electrical", txt.toString());
	}

	if (getStun() > 0 && getStun() <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getStun(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun", txt.toString());
	}

	if (getBlast() > 0 && getBlast() <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getBlast(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast", txt.toString());
	}

	if (getHeat() > 0 && getHeat() <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getHeat(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_heat", txt.toString());
	}

	if (getCold() > 0 && getCold() <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getCold(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_cold", txt.toString());
	}

	if (getAcid() > 0 && getAcid() <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getAcid(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_acid", txt.toString());
	}

	if (getLightSaber() > 0 && getLightSaber() <= 90) {
		StringBuffer txt;
		txt << Math::getPrecision(getLightSaber(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint", txt.toString());
	}

	if (getKinetic() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (getEnergy() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (getElectricity() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (getStun() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (getBlast() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (getHeat() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (getCold() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (getAcid() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_acid", "-");

	if (getLightSaber() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");

}

unsigned int TurretDataComponent::getArmorRating() {
	if (templateData != nullptr)
		return templateData->getArmorRating();

	return 0;
}

float TurretDataComponent::getArmorResistReduction(float value) {
	if (value == -1) {
		return value;
	}

	ManagedReference<TangibleObject*> turret = cast<TangibleObject*>(getParent());

	if (turret == nullptr || turret->getZone() == nullptr)
		return 0;

	int maxCondition = turret->getMaxCondition();

	// Damage not prevented by armor resists
	int unmitigatedDamage = turret->getUnmitigatedDamage();

	// Percent of damage not prevented by armor resists compared to maxCondition
	// Only accounts if the turret has that resistance type.
	float mitigatedAmount = unmitigatedDamage / (float)maxCondition;

#ifdef DEBUG_RESIST_DECAY
	turret->info (true) << " Value of damage mitigated by armor = " << mitigatedAmount;
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
		turret->info(true) << " max condition = " << maxCondition << " Total Damage Mitigated = " << unmitigatedDamage << " Start Armor value: " << value << " New Armor Value = " << newValue << " Reduction percent = " << reduction;
#endif
	}

	return newValue;
}

float TurretDataComponent::getKinetic() {
	if (templateData != nullptr)
		return getArmorResistReduction(templateData->getKinetic());

	return 0;
}

float TurretDataComponent::getEnergy() {
	if (templateData != nullptr)
		return getArmorResistReduction(templateData->getEnergy());

	return 0;
}

float TurretDataComponent::getElectricity() {
	if (templateData != nullptr)
		return getArmorResistReduction(templateData->getElectricity());

	return 0;
}

float TurretDataComponent::getStun() {
	if (templateData != nullptr)
		return getArmorResistReduction(templateData->getStun());

	return 0;
}

float TurretDataComponent::getBlast() {
	if (templateData != nullptr)
		return getArmorResistReduction(templateData->getBlast());

	return 0;
}

float TurretDataComponent::getHeat() {
	if (templateData != nullptr)
		return getArmorResistReduction(templateData->getHeat());

	return 0;
}

float TurretDataComponent::getCold() {
	if (templateData != nullptr)
		return getArmorResistReduction(templateData->getCold());

	return 0;
}

float TurretDataComponent::getAcid() {
	if (templateData != nullptr)
		return getArmorResistReduction(templateData->getAcid());

	return 0;
}

float TurretDataComponent::getLightSaber() {
	if (templateData != nullptr)
		return getArmorResistReduction(templateData->getLightSaber());

	return 0;
}

float TurretDataComponent::getChanceHit() {
	if (templateData != nullptr)
		return templateData->getChanceHit();

	return 0;
}
