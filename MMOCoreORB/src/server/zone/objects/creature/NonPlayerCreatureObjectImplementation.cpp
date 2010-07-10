/*
 * NonPlayerCreatureObjectImplementation.cpp
 *
 *  Created on: 23/06/2010
 *      Author: victor
 */

#include "NonPlayerCreatureObject.h"
#include "events/CreatureThinkEvent.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/managers/templates/TemplateManager.h"

void NonPlayerCreatureObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	CreatureObjectImplementation::loadTemplateData(templateData);

	if (templateData->isNonPlayerCreatureObjectTemplate())
		npcTemplate = (NonPlayerCreatureObjectTemplate*) templateData;
	/*else {
		StringBuffer msg;
		msg << "creating " << TemplateManager::instance()->getTemplateFile(serverObjectCRC);
		msg << " with wrong template type object";
		error(msg.toString());
	}*/
}

void NonPlayerCreatureObjectImplementation::initializeTransientMembers() {
	SharedObjectTemplate* templ = TemplateManager::instance()->getTemplate(serverObjectCRC);

	if (templ != NULL && templ->isNonPlayerCreatureObjectTemplate()) {
		npcTemplate = (NonPlayerCreatureObjectTemplate*) templ;
	}
}

void NonPlayerCreatureObjectImplementation::doRecovery() {
	activateHAMRegeneration();
	activateStateRecovery();

	if (damageOverTimeList.hasDot() && damageOverTimeList.isNextTickPast()) {
		damageOverTimeList.activateDots(_this);
	}

	if (isInCombat() && defenderList.size() > 0) {
		SceneObject* targetToAttack = defenderList.get(0);

		if (targetToAttack->isCreatureObject()) {
			CreatureObject* creo = (CreatureObject*) targetToAttack;

			if (creo->isPeaced()) {
				CombatManager::instance()->attemptPeace(_this);
			} else {
				setTargetID(creo->getObjectID(), true);

				if (commandQueue.size() == 0)
					enqueueCommand(0xA8FEF90A, 0, creo->getObjectID(), ""); // Do default attack
			}
		}
	}

	activateRecovery();
}

void NonPlayerCreatureObjectImplementation::activateRecovery() {
	if (thinkEvent == NULL) {
		thinkEvent = new CreatureThinkEvent(_this);

		thinkEvent->schedule(2000);
	}

	if (!thinkEvent->isScheduled())
		thinkEvent->schedule(2000);
}

void NonPlayerCreatureObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* player) {
	int creaKnowledge = player->getSkillMod("creature_knowledge");

	if (isDead()) {
		return;
	}

	if (getArmor() == 0)
		alm->insertAttribute("armorrating", "None");
	else if (getArmor() == 1)
		alm->insertAttribute("armorrating", "Light");
	else if (getArmor() == 2)
		alm->insertAttribute("armorrating", "Medium");
	else if (getArmor() == 3)
		alm->insertAttribute("armorrating", "Heavy");

	if (getKinetic() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic",
				"100%");

	if (getEnergy() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy",
				"100%");

	if (getElectricity() == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_electrical",
				"100%");

	if (getStun() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun",
				"100%");

	if (getBlast() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast",
				"100%");

	if (getHeat() == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_heat", "100%");

	if (getCold() == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_cold", "100%");

	if (getAcid() == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_acid", "100%");

	if (getLightSaber() == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_restraint", "100%");

	if (getKinetic() > 0 && getKinetic() < 100) {
		StringBuffer txt;
		txt << round(getKinetic()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic",
				txt.toString());
	}

	if (getEnergy() > 0 && getEnergy() < 100) {
		StringBuffer txt;
		txt << round(getEnergy()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy",
				txt.toString());
	}

	if (getElectricity() > 0 && getElectricity() < 100) {
		StringBuffer txt;
		txt << round(getElectricity()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_electrical",
				txt.toString());
	}

	if (getStun() > 0 && getStun() < 100) {
		StringBuffer txt;
		txt << round(getStun()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun",
				txt.toString());
	}

	if (getBlast() > 0 && getBlast() < 100) {
		StringBuffer txt;
		txt << round(getBlast()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast",
				txt.toString());
	}

	if (getHeat() > 0 && getHeat() < 100) {
		StringBuffer txt;
		txt << round(getHeat()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_heat",
				txt.toString());
	}

	if (getCold() > 0 && getCold() < 100) {
		StringBuffer txt;
		txt << round(getCold()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_cold",
				txt.toString());
	}

	if (getAcid() > 0 && getAcid() < 100) {
		StringBuffer txt;
		txt << round(getAcid()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_acid",
				txt.toString());
	}

	if (getLightSaber() > 0 && getLightSaber() < 100) {
		StringBuffer txt;
		txt << round(getLightSaber()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint",
				txt.toString());
	}

	if (getKinetic() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (getEnergy() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (getElectricity() == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (getStun() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (getBlast() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (getHeat() == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (getCold() == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (getAcid() == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_acid", "-");

	if (getLightSaber() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");

	if (getHideType().isEmpty() && getBoneType().isEmpty()
			&& getMeatType().isEmpty()) {
		return;
	}

	if (creaKnowledge >= 5) {
		if (isAggressiveTo(player))
			alm->insertAttribute("aggro", "yes");
		else
			alm->insertAttribute("aggro", "no");
		if (isStalker())
			alm->insertAttribute("stalking", "yes");
		else
			alm->insertAttribute("stalking", "no");
	}

	if (creaKnowledge >= 10) {
		if (getTame() >= 0.0f && isBaby())
			alm->insertAttribute("tamable", "yes");
		else
			alm->insertAttribute("tamable", "no");
	}

	if (creaKnowledge >= 20) {
		if (!getHideType().isEmpty())
			alm->insertAttribute("res_hide", getHideType());//.subString(4).replaceAll("_"," "));
		else
			alm->insertAttribute("res_hide", "---");
		if (!getBoneType().isEmpty())
			alm->insertAttribute("res_bone", getBoneType());//.subString(5).replaceAll("_"," "));
		else
			alm->insertAttribute("res_bone", "---");
		if (!getMeatType().isEmpty())
			alm->insertAttribute("res_meat", getMeatType());//.subString(4).replaceAll("_"," "));
		else
			alm->insertAttribute("res_meat", "---");
	}

	if (creaKnowledge >= 30) {
		if (isKiller())
			alm->insertAttribute("killer", "yes");
		else
			alm->insertAttribute("killer", "no");
	}

	if (creaKnowledge >= 40) {
		alm->insertAttribute("ferocity", (int) getFerocity());
	}

	if (creaKnowledge >= 50)
		alm->insertAttribute("challenge_level", (int) getLevel());

	int skillNum = skillCommands.size();

	if (creaKnowledge >= 70) {
		if (skillNum >= 1)
			alm->insertAttribute("pet_command_18", skillCommands.get(0));
		else
			alm->insertAttribute("pet_command_18", "---");
	}

	if (creaKnowledge >= 80) {
		if (skillNum >= 2)
			alm->insertAttribute("pet_command_19", skillCommands.get(1));
		else
			alm->insertAttribute("pet_command_19", "---");
	}

	if (creaKnowledge >= 90)
		alm->insertAttribute("basetohit", 0.89f);

	if (creaKnowledge >= 100) {
		StringBuffer damageMsg;
		//damageMsg << creatureWeaponMinDamage << "-" << creatureWeaponMaxDamage;
		alm->insertAttribute("cat_wpn_damage", damageMsg.toString());
	}

}


void NonPlayerCreatureObjectImplementation::doMovement() {

}

bool NonPlayerCreatureObjectImplementation::hasOrganics() {
	return ((getHideMax() + getBoneMax() + getMeatMax()) > 0);
}

int NonPlayerCreatureObjectImplementation::inflictDamage(TangibleObject* attacker, int damageType, int damage, bool destroy, bool notifyClient) {
	activateRecovery();

	return CreatureObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient);
}
