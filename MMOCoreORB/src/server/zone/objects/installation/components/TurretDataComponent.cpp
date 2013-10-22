/*
 * TurretDataComponent.cpp
 *
 *  Created on: Dec 10, 2012
 *      Author: root
 */

#include "TurretDataComponent.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/installation/components/TurretFireTask.h"

void TurretDataComponent::initializeTransientMembers() {
	if(getParent() != NULL){
		templateData = dynamic_cast<SharedInstallationObjectTemplate*>(getParent()->getObjectTemplate());

		SceneObject* sceneObject = getParent()->getSlottedObject("hold_r");

		if(sceneObject == NULL){
			return;
		}

		WeaponObject* weapon = cast<WeaponObject*>(sceneObject);

		if(weapon != NULL){
			attackSpeed = weapon->getAttackSpeed();
			maxrange = weapon->getMaxRange();
		}
	}
}

void TurretDataComponent::rescheduleFireTask(float secondsToWait, bool manual){
	if(getParent() == NULL)
		return;

	CreatureObject* attacker = getController();
	CreatureObject* target = getTarget();

	//Logger::Logger tlog("reschedule");
	if(target != NULL){

		Reference<TurretFireTask*> fireTask = new TurretFireTask(cast<TangibleObject*>(getParent()), getTarget(),manual);
		this->setFireTask(fireTask);
		getFireTask()->schedule(secondsToWait * 1000);

	} else {
		//tlog.info("target is null",true);
		setController(NULL);
		setFireTask(NULL);
		setTarget(NULL);
	}

}

void TurretDataComponent::setWeapon(WeaponObject* weapon){
	if(weapon != NULL){
		attackSpeed = weapon->getAttackSpeed();
		maxrange = weapon->getMaxRange();
	}
}

void TurretDataComponent::fillAttributeList(AttributeListMessage* alm){

	if(getParent() == NULL)
		return;

	ManagedReference<InstallationObject*> turret = cast<InstallationObject*>(getParent());

	alm->insertAttribute("condition",String::valueOf(turret->getMaxCondition() - turret->getConditionDamage()) + "/" + String::valueOf(turret->getMaxCondition()));

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
		txt << round(getKinetic()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic", txt.toString());
	}

	if (getEnergy() > 90) {
		StringBuffer txt;
		txt << round(getEnergy()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy", txt.toString());
	}

	if (getElectricity() > 90) {
		StringBuffer txt;
		txt << round(getElectricity()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_electrical", txt.toString());
	}

	if (getStun() > 90) {
		StringBuffer txt;
		txt << round(getStun()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun", txt.toString());
	}

	if (getBlast() > 90) {
		StringBuffer txt;
		txt << round(getBlast()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast", txt.toString());
	}

	if (getHeat() > 90) {
		StringBuffer txt;
		txt << round(getHeat()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_heat", txt.toString());
	}

	if (getCold() > 90) {
		StringBuffer txt;
		txt << round(getCold()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_cold", txt.toString());
	}

	if (getAcid() > 90) {
		StringBuffer txt;
		txt << round(getAcid()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_acid", txt.toString());
	}

	if (getLightSaber() > 90) {
		StringBuffer txt;
		txt << round(getLightSaber()) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_restraint", txt.toString());
	}

	if (getKinetic() > 0 && getKinetic() <= 90) {
		StringBuffer txt;
		txt << round(getKinetic()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic", txt.toString());
	}

	if (getEnergy() > 0 && getEnergy() <= 90) {
		StringBuffer txt;
		txt << round(getEnergy()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy", txt.toString());
	}

	if (getElectricity() > 0 && getElectricity() <= 90) {
		StringBuffer txt;
		txt << round(getElectricity()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_electrical", txt.toString());
	}

	if (getStun() > 0 && getStun() <= 90) {
		StringBuffer txt;
		txt << round(getStun()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun", txt.toString());
	}

	if (getBlast() > 0 && getBlast() <= 90) {
		StringBuffer txt;
		txt << round(getBlast()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast", txt.toString());
	}

	if (getHeat() > 0 && getHeat() <= 90) {
		StringBuffer txt;
		txt << round(getHeat()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_heat", txt.toString());
	}

	if (getCold() > 0 && getCold() <= 90) {
		StringBuffer txt;
		txt << round(getCold()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_cold", txt.toString());
	}

	if (getAcid() > 0 && getAcid() <= 90) {
		StringBuffer txt;
		txt << round(getAcid()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_acid", txt.toString());
	}

	if (getLightSaber() > 0 && getLightSaber() <= 90) {
		StringBuffer txt;
		txt << round(getLightSaber()) << "%";
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
void TurretDataComponent::updateAutoCooldown(float secondsToAdd){
	int milisecondsToAdd = secondsToAdd*1000;
	nextFireTime = Time();
	nextFireTime.addMiliTime(milisecondsToAdd);
}

void TurretDataComponent::updateManualCooldown(float secondsToAdd){
	int milisecondsToAdd = secondsToAdd*1000;
	nextManualFireTime = Time();
	nextManualFireTime.addMiliTime(milisecondsToAdd);
}

unsigned int TurretDataComponent::getArmorRating(){
	if(templateData != NULL)
		return templateData->getArmorRating();

	return 0;
}

float TurretDataComponent::getKinetic(){
	if(templateData != NULL)
		return templateData->getKinetic();

	return 0;
}

float TurretDataComponent::getEnergy(){
	if(templateData != NULL)
		return templateData->getEnergy();

	return 0;
}

float TurretDataComponent::getElectricity(){
	if(templateData != NULL)
		return templateData->getElectricity();

	return 0;
}

float TurretDataComponent::getStun(){
	if(templateData != NULL)
		return templateData->getStun();

	return 0;
}

float TurretDataComponent::getBlast(){
	if(templateData != NULL)
		return templateData->getBlast();

	return 0;
}

float TurretDataComponent::getHeat(){
	if(templateData != NULL)
		return templateData->getHeat();

	return 0;
}

float TurretDataComponent::getCold(){
	if(templateData != NULL)
		return templateData->getCold();

	return 0;
}

float TurretDataComponent::getAcid(){
	if(templateData != NULL)
		return templateData->getAcid();

	return 0;
}

float TurretDataComponent::getLightSaber(){
	if(templateData != NULL)
		return templateData->getLightSaber();

	return 0;
}

float TurretDataComponent::getChanceHit(){
	if(templateData != NULL)
		return templateData->getChanceHit();

	return 0;
}

String TurretDataComponent::getWeaponString(){
	if(templateData != NULL)
		return templateData->getWeapon();

	return "";
}
