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

	Logger::Logger tlog("reschedule");
	if(target != NULL){

		Reference<TurretFireTask*> fireTask = new TurretFireTask(cast<TangibleObject*>(getParent()), getTarget(),manual);
		this->setFireTask(fireTask);
		getFireTask()->schedule(secondsToWait * 1000);

	} else {
		tlog.info("target is null",true);
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
	alm->insertAttribute("armorrating","Heavy");

	alm->insertAttribute("cat_armor_special_protection.armor_eff_energy",String::valueOf(getEnergy()) + "%");
	alm->insertAttribute("cat_armor_special_protection.armor_eff_stun",String::valueOf(getStun()) + "%");

	alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic",String::valueOf(getKinetic()) + "%");
	alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_heat",String::valueOf(getHeat()) + "%");
	alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_cold",String::valueOf(getCold()) + "%");
	alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_acid",String::valueOf(getAcid()) + "%");

	alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_electrical",String::valueOf(getElectricity()) + "%");
	alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast",String::valueOf(getBlast()) + "%");

	alm->insertAttribute("cat_armor_encumbrance.health","0");
	alm->insertAttribute("cat_armor_encumbrance.action","0");
	alm->insertAttribute("cat_armor_encumbrance.mind","0");

	alm->insertAttribute("description",turret->getDetailedDescription());
	alm->insertAttribute("owner",String::valueOf(turret->getOwnerObjectID()));

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


float TurretDataComponent::getKinetic(){
	if(templateData != NULL)
		return templateData->getKinetic();

	return 0;
}

float TurretDataComponent::getEnergy(){
	if(templateData != NULL)
		return templateData->getKinetic();

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
