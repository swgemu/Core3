/*
 Copyright (C) 2007 <SWGEmu>

 This File is part of Core3.
 This program is free software; you can redistribute
 it and/or modify it under the terms of the GNU Lesser
 General Public License as published by the Free Software
 Foundation; either version 2 of the License,
 or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for
 more details.

 You should have received a copy of the GNU Lesser General
 Public License along with this program; if not, write to
 the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

 Linking Engine3 statically or dynamically with other modules
 is making a combined work based on Engine3.
 Thus, the terms and conditions of the GNU Lesser General Public License
 cover the whole combination.

 In addition, as a special exception, the copyright holders of Engine3
 give you permission to combine Engine3 program with free software
 programs or libraries that are released under the GNU LGPL and with
 code included in the standard release of Core3 under the GNU LGPL
 license (or modified versions of such code, with unchanged license).
 You may copy and distribute such a system following the terms of the
 GNU LGPL for Engine3 and the licenses of the other code concerned,
 provided that you include the source code of that other code when
 and as the GNU LGPL requires distribution of source code.

 Note that people who make modified versions of Engine3 are not obligated
 to grant this special exception for their modified versions;
 it is their choice whether to do so. The GNU Lesser General Public License
 gives permission to release a modified version without this exception;
 this exception also makes it possible to release a modified version
 which carries forward this exception.
 */

#include "../../ZoneServer.h"

#include "../../objects.h"
#include "../../packets.h"

#include "../tangible/Inventory.h"
#include "../tangible/Container.h"

#include "../terrain/Terrain.h"

#include "../../managers/creature/CreatureManagerImplementation.h"

#include "../../managers/combat/CombatManager.h"

#include "skills/Skill.h"
#include "skills/target/AttackTargetSkill.h"
#include "skills/CamoSkill.h"

#include "CreatureGroup.h"

#include "Creature.h"
#include "CreatureImplementation.h"

#include "../scene/SceneObjectImplementation.h"

#include "../../ZoneProcessServerImplementation.h"

#include "../../managers/combat/CommandQueueAction.h"
#include "../../managers/loot/LootManager.h"

CreatureImplementation::CreatureImplementation(uint64 oid, CreatureGroup* group) :
	CreatureServant(oid), Event() {
	objectID = oid;
	type = CREATURE;

	baseID = oid;

	stfName = "mob/creature_names";

	creatureGroup = group;

	setKeeping(true);

	init();

	camoCount = 0;
	camoSet = false;
}

CreatureImplementation::~CreatureImplementation() {
	if (nextPosition != NULL) {
		delete nextPosition;

		nextPosition = NULL;
	}

	if (spawnPosition != NULL) {
		delete spawnPosition;

		spawnPosition = NULL;
	}

	playerCanHarvest.removeAll();

	while (damageMap.size() > 0) {
		CreatureObject* object = damageMap.elementAt(0)->getKey();
		damageMap.drop(object);

		object->release();
	}
}

void CreatureImplementation::init() {
	zone = NULL;

	creatureManager = NULL;

	objectType = NONPLAYERCREATURE;

	creatureState = ACTIVE;

	armor = 0;

	kinetic = 0;
	energy = 0;
	electricity = 0;
	stun = 0;
	blast = 0;
	heat = 0;
	cold = 0;
	acid = 0;
	lightSaber = 0;

	doRandomMovement = false;

	directionAngle = 0;

	//visibilityRange = 32;

	// constants
	itemShift = 100;

	activityCount = 0;
	highestMadeDamage = 0;

	respawnTimer = 60;

	lair = NULL;

	level = 250;

	nextPosition = new PatrolPoint();

	spawnPosition = new PatrolPoint();

	randomizeRespawn = false;

	hasRandomMovement = true;

	actualSpeed = 0.f;

	movementCounter = 0;

	// stats
	aggroedCreature = NULL;
	willAggro = false;

	lootCreated = false;

	looted = false;

	creatureRemoveEvent = NULL;

	//Reducing in combat regen for non players to 25% of normal.
	combatRegenModifier = 0.25f;
	peacedRegenModifier = 1.0f;

	setObjectKeeping(true);

	StringBuffer logname;
	logname << "NPC = 0x" << hex << objectID;

	setLockName(logname.toString());

	setLoggingName(logname.toString());

	setLogging(false);
	setGlobalLogging(true);
}

void CreatureImplementation::sendRadialResponseTo(Player* player,
		ObjectMenuResponse* omr) {

	String skillBox = "outdoors_scout_novice";

	if (player->isInRange(getPositionX(), getPositionY(), 10.0f)
			&& !player->isInCombat() && player->hasSkillBox(skillBox)
			&& isDead() && canHarvest(player->getFirstName())) {

		omr->addRadialItem(0, 148, 3, "@sui:harvest_corpse");

		if (getMeatType() != "")
			omr->addRadialItem(4, 108, 3, "@sui:harvest_meat");

		if (getHideType() != "")
			omr->addRadialItem(4, 109, 3, "@sui:harvest_hide");

		if (getBoneType() != "")
			omr->addRadialItem(4, 110, 3, "@sui:harvest_bone");

	}

	omr->finish();

	player->sendMessage(omr);
}

void CreatureImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage(_this);

	int creaKnowledge = player->getSkillMod("creature_knowledge");

	if (isDead()) {
		player->sendMessage(alm);
		return;
	}

	if (armor == 0)
		alm->insertAttribute("armorrating", "None");
	else if (armor == 1)
		alm->insertAttribute("armorrating", "Light");
	else if (armor == 2)
		alm->insertAttribute("armorrating", "Medium");
	else if (armor == 3)
		alm->insertAttribute("armorrating", "Heavy");

	if (kinetic == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic",
				"100%");

	if (energy == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy",
				"100%");

	if (electricity == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_electrical",
				"100%");

	if (stun == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun",
				"100%");

	if (blast == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast",
				"100%");

	if (heat == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_heat", "100%");

	if (cold == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_cold", "100%");

	if (acid == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_acid", "100%");

	if (lightSaber == 100)
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_restraint", "100%");

	if (kinetic > 0 && kinetic < 100) {
		StringBuffer txt;
		txt << round(getKinetic()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic",
				txt.toString());
	}

	if (energy > 0 && energy < 100) {
		StringBuffer txt;
		txt << round(getEnergy()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy",
				txt.toString());
	}

	if (electricity > 0 && electricity < 100) {
		StringBuffer txt;
		txt << round(getElectricity()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_electrical",
				txt.toString());
	}

	if (stun > 0 && stun < 100) {
		StringBuffer txt;
		txt << round(getStun()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun",
				txt.toString());
	}

	if (blast > 0 && blast < 100) {
		StringBuffer txt;
		txt << round(getBlast()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast",
				txt.toString());
	}

	if (heat > 0 && heat < 100) {
		StringBuffer txt;
		txt << round(getHeat()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_heat",
				txt.toString());
	}

	if (cold > 0 && cold < 100) {
		StringBuffer txt;
		txt << round(getCold()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_cold",
				txt.toString());
	}

	if (acid > 0 && acid < 100) {
		StringBuffer txt;
		txt << round(getAcid()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_acid",
				txt.toString());
	}

	if (lightSaber > 0 && lightSaber < 100) {
		StringBuffer txt;
		txt << round(getLightSaber()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint",
				txt.toString());
	}

	if (kinetic == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (energy == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (electricity == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (stun == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (blast == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (heat == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (cold == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (acid == 0)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_acid", "-");

	if (lightSaber == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");

	if (getHideType().isEmpty() && getBoneType().isEmpty()
			&& getMeatType().isEmpty()) {
		player->sendMessage(alm);
		return;
	}

	if (creaKnowledge >= 5) {
		if (isAggressive())
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
			alm->insertAttribute("res_hide", getHideType());
		else
			alm->insertAttribute("res_hide", "---");
		if (!getBoneType().isEmpty())
			alm->insertAttribute("res_bone", getBoneType());
		else
			alm->insertAttribute("res_bone", "---");
		if (!getMeatType().isEmpty())
			alm->insertAttribute("res_meat", getMeatType());
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

	int skillNum = creatureSkills.size();

	if (creaKnowledge >= 70) {
		if (skillNum >= 1)
			alm->insertAttribute("pet_command_18", getSkill(0));
		else
			alm->insertAttribute("pet_command_18", "---");
	}

	if (creaKnowledge >= 80) {
		if (skillNum >= 2)
			alm->insertAttribute("pet_command_19", getSkill(1));
		else
			alm->insertAttribute("pet_command_19", "---");
	}

	if (creaKnowledge >= 90)
		alm->insertAttribute("basetohit", 0.89f);

	if (creaKnowledge >= 100) {
		float minDamage = 0;
		float maxDamage = 0;

		Weapon* wpn = getWeapon();

		if (wpn != NULL) {
			minDamage = wpn->getMinDamage();
			maxDamage = wpn->getMaxDamage();
		} else {
			maxDamage = getSkillMod("unarmed_damage");
			if (maxDamage < 25.0f)
				maxDamage = 25.0f;

			if (isBaby())
				maxDamage / 2;

			minDamage = maxDamage / 2;
		}

		minDamage *= getInternalNPCDamageModifier();
		maxDamage *= getInternalNPCDamageModifier();

		if (skillNum > 0) {
			Skill* skill = getSkill(getSkill(0));
			if (skill->isAttackSkill()) {
				AttackTargetSkill* askill = (AttackTargetSkill*) skill;
				maxDamage *= askill->getDamageRatio();
				minDamage *= askill->getDamageRatio();
			}

		}

		StringBuffer damageMsg;
		damageMsg << (int) minDamage << "-" << (int) maxDamage;
		alm->insertAttribute("cat_wpn_damage", damageMsg.toString());
	}

	player->sendMessage(alm);
}

void CreatureImplementation::reload() {

	creatureManager->respawnCreature(_this);

	resetState();

	insertToZone(zone);

	info("creature respawned");
}

void CreatureImplementation::unload() {
	deaggro();

	clearTarget();

	clearLootItems();

	resetPatrolPoints(false);

	playerCanHarvest.removeAll();

	while (damageMap.size() > 0) {
		CreatureObject* object = damageMap.elementAt(0)->getKey();
		damageMap.drop(object);

		object->release();
	}

	if (zone != NULL && isInQuadTree())
		removeFromZone(true);

	creatureManager->despawnCreature(_this);

	setPosition(spawnPosition->getPositionX(), spawnPosition->getPositionZ(),
			spawnPosition->getPositionY());

	uint64 respawnCellID = spawnPosition->getCellID();

	if (respawnCellID != 0)
		parent = zone->lookupObject(respawnCellID);

	info("creature despawned");

}

void CreatureImplementation::scheduleDespawnCreature(int time) {
	if (isMount())
		return;

	if (creatureRemoveEvent == NULL)
		creatureRemoveEvent = new CreatureRemoveEvent(_this);

	if (server == NULL)
		return;

	if (creatureRemoveEvent->isQueued())
		server->removeEvent(creatureRemoveEvent);

	server->addEvent(creatureRemoveEvent, time);
}

void CreatureImplementation::clearLootItems() {
	setCashCredits(0);

	lootCreated = false;

	if (lootContainer == NULL)
		return;

	while (!lootContainer->isEmpty()) {
		SceneObject* object = lootContainer->getObject((int) 0);

		lootContainer->removeObject((int) 0);

		object->finalize();
	}
}

void CreatureImplementation::loadItems() {
	inventory = new Inventory(_this);

	lootContainer = new CreatureInventory(_this);

	Weapon* weapon = NULL;

	String wpName = getCreatureWeaponName();
	if (wpName != "") {
		try {
			String wpObject = getCreatureWeapon();
			String wpName = getCreatureWeaponName();
			String wpTemp = getCreatureWeaponTemp();
			bool wpEq = (bool) getCreatureWeaponEquipped();
			int wpMinDamage = getCreatureWeaponMinDamage();
			int wpMaxDamage = getCreatureWeaponMaxDamage();
			float wpAttackSpeed = getCreatureWeaponAttackSpeed();
			String wpDamType = getCreatureWeaponDamageType();
			String wpArmorPiercing = getCreatureWeaponArmorPiercing();
			String wpClass = getCreatureWeaponClass();

			if (wpClass == "CarbineRangedWeapon")
				weapon = new CarbineRangedWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "RifleRangedWeapon")
				weapon
						= new RifleRangedWeapon(_this, wpObject, UnicodeString(wpName), wpTemp, wpEq);
			else if (wpClass == "PistolRangedWeapon")
				weapon
						= new PistolRangedWeapon(_this, wpObject, UnicodeString(
								wpName), wpTemp, wpEq);
			else if (wpClass == "UnarmedMeleeWeapon")
				weapon
						= new UnarmedMeleeWeapon(_this, wpObject, UnicodeString(
								wpName), wpTemp, wpEq);
			else if (wpClass == "OneHandedMeleeWeapon")
				weapon = new OneHandedMeleeWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "TwoHandedMeleeWeapon")
				weapon = new TwoHandedMeleeWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "PolearmMeleeWeapon")
				weapon
						= new PolearmMeleeWeapon(_this, wpObject, UnicodeString(
								wpName), wpTemp, wpEq);
			else if (wpClass == "OneHandedJediWeapon")
				weapon = new OneHandedJediWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "TwoHandedJediWeapon")
				weapon = new TwoHandedJediWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "PolearmJediWeapon")
				weapon
						= new PolearmJediWeapon(_this, wpObject, UnicodeString(wpName), wpTemp, wpEq);
			else if (wpClass == "SpecialHeavyRangedWeapon")
				weapon = new SpecialHeavyRangedWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "HeavyRangedWeapon")
				weapon
						= new HeavyRangedWeapon(_this, wpObject, UnicodeString(wpName), wpTemp, wpEq);

			//DAMAGE TYPE
			if (wpDamType == "ENERGY")
				weapon->setDamageType(WeaponImplementation::ENERGY);
			else if (wpDamType == "KINECTIC")
				weapon->setDamageType(WeaponImplementation::KINETIC);
			else if (wpDamType == "ELECTRICITY")
				weapon->setDamageType(WeaponImplementation::ELECTRICITY);
			else if (wpDamType == "STUN")
				weapon->setDamageType(WeaponImplementation::STUN);
			else if (wpDamType == "BLAST")
				weapon->setDamageType(WeaponImplementation::BLAST);
			else if (wpDamType == "HEAT")
				weapon->setDamageType(WeaponImplementation::HEAT);
			else if (wpDamType == "COLD")
				weapon->setDamageType(WeaponImplementation::COLD);
			else if (wpDamType == "ACID")
				weapon->setDamageType(WeaponImplementation::ACID);
			else if (wpDamType == "LIGHTSABER")
				weapon->setDamageType(WeaponImplementation::LIGHTSABER);

			//ARMOR PIERCING
			if (wpArmorPiercing == "NONE")
				weapon->setArmorPiercing(WeaponImplementation::NONE);
			else if (wpArmorPiercing == "LIGHT")
				weapon->setArmorPiercing(WeaponImplementation::LIGHT);
			else if (wpArmorPiercing == "MEDIUM")
				weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
			else if (wpArmorPiercing == "HEAVY")
				weapon->setArmorPiercing(WeaponImplementation::HEAVY);

			//MODFIERS
			weapon->setMinDamage(wpMinDamage);
			weapon->setMaxDamage(wpMaxDamage);
			weapon->setAttackSpeed(wpAttackSpeed);
			weapon->setEquipped(true);

			addInventoryItem(weapon);
			setWeapon(weapon);
		} catch (...) {
			//ouch..something in the lua isnt right
			System::out
					<< "exception CreatureImplementation::loadItems()  -  Weaponloading for creature "
					<< objectID << "\n";
			return;
		}
	} else
		return;
	/*
	 //old before new LUAs june 2008
	 if (objectCRC == 0x738E0B1F) { //Zealot of Lord Nyax + Diciple of Lord Nyax
	 weapon = new CarbineRangedWeapon(_this, "object/weapon/ranged/carbine/shared_carbine_laser.iff", UnicodeString("a Laser Carbine"), "carbine_laser", true);
	 weapon->setMinDamage(350);
	 weapon->setMaxDamage(400);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
	 }
	 else if (objectCRC == 0xE275ECBB || objectCRC == 0xE275ECBB || objectCRC == 0xA1048F8A || objectCRC == 0xD084273F || objectCRC == 0x7477AB80) {
	 //Imperial GeneralMajor // Imperial General // Imperial High Colonel / Imperial Surface Marshall // Imperial Major
	 weapon = new PistolRangedWeapon(_this, "object/weapon/ranged/pistol/shared_pistol_dl44.iff", UnicodeString("a DL-44 Pistol"), "pistol_dl44", true);
	 weapon->setMinDamage(350);
	 weapon->setMaxDamage(400);
	 weapon->setAttackSpeed(2.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);
	 setImperial();
	 }
	 else if (objectCRC == 0xBA7F23CD) { //storm trooper
	 weapon = new RifleRangedWeapon(_this, "object/weapon/ranged/rifle/shared_rifle_t21.iff", UnicodeString("Teh Pwn"), "rifle_t21", true);
	 weapon->setMinDamage(350);
	 weapon->setMaxDamage(400);
	 weapon->setAttackSpeed(4);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);
	 setImperial();
	 }
	 else if (objectCRC == 0x4E38DA33) { //Dark trooper
	 //we assign but do not equip the weapon! We just need the line "setImperial" - but without an assigned weapon we will crash
	 weapon = new RifleRangedWeapon(_this, "object/weapon/ranged/rifle/shared_rifle_t21.iff", UnicodeString("Teh Pwn"), "rifle_t21", false);
	 weapon->setMinDamage(350);
	 weapon->setMaxDamage(400);
	 weapon->setAttackSpeed(4);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);
	 setImperial();
	 }
	 else if (objectCRC == 0xFCA399 || objectCRC == 0x1BCAE981 ||
	 objectCRC == 0x75A7387A || objectCRC == 0xEF5997EB ||
	 objectCRC == 0xFCA399 || objectCRC == 0xE0B389E5 ||
	 objectCRC == 0xFECB7C04 || objectCRC == 0xD96A33B7) { //Corsecs (also used for Rogue Corsecs!)
	 weapon = new PistolRangedWeapon(_this, "object/weapon/ranged/pistol/shared_pistol_cdef_corsec.iff", UnicodeString("Corsec CDEF Pistol"), "pistol_cdef_corsec", true);
	 weapon->setMinDamage(150);
	 weapon->setMaxDamage(200);
	 weapon->setAttackSpeed(3);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);
	 }
	 else if (objectCRC == 0xFECDC4DE || objectCRC == 0x7EDC1419) { //  AT AT    / AT ST
	 weapon = new RifleRangedWeapon(_this,"object/weapon/ranged/vehicle/shared_vehicle_atst_ranged.iff", UnicodeString("Imperial Cannon"), "vehicle_atst_ranged");
	 weapon->setAttackSpeed(1.5f);
	 setImperial();
	 }
	 else if (objectCRC == 0x8C70914) {
	 weapon = new OneHandedJediWeapon(_this,
	 "object/weapon/melee/sword/crafted_saber/shared_sword_lightsaber_one_handed_s4_gen4.iff",
	 UnicodeString("Darth Saber"), "sword_lightsaber_one_handed_s4_gen4", true);
	 weapon->setDamageType(WeaponImplementation::LIGHTSABER);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 } else if (objectCRC == 0x2B0C220E || objectCRC == 0x476794EB || objectCRC == 0x4A889CCF ||
	 objectCRC == 0x6D029623 || objectCRC == 0x4A48B6CC || objectCRC == 0x1527DF01) {
	 // low level SMC, Rebel General
	 switch (System::random(1)) {
	 case 0 :
	 weapon = new OneHandedMeleeWeapon(_this, "object/weapon/melee/baton/shared_baton_gaderiffi.iff", UnicodeString("a Gaderiffi"), "baton_gaderiffi", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(200 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 break;
	 case 1 :
	 weapon = new OneHandedMeleeWeapon(_this,
	 "object/weapon/melee/baton/shared_baton_stun.iff", UnicodeString("a Stun Baton"), "baton_stun", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(250 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::STUN);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 break;
	 }
	 } else if (objectCRC == 0xE158FEC1) {
	 //ranged tusken raider
	 weapon = new RifleRangedWeapon(_this, "object/weapon/ranged/rifle/shared_rifle_tusken.iff", UnicodeString("a Tusken Rifle"), "rifle_tusken", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(200 + level);
	 weapon->setAttackSpeed(4);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);

	 } else if (objectCRC ==0x148D60AA) {
	 //melee tusken raider
	 weapon = new OneHandedMeleeWeapon(_this, "object/weapon/melee/baton/shared_baton_gaderiffi.iff", UnicodeString("a Gaderiffi"), "baton_gaderiffi", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(200 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);

	 } else if (objectCRC ==0xE21E6148) {
	 //SBD 0xE21E6148
	 weapon = new CarbineRangedWeapon(_this, "object/weapon/ranged/droid/shared_droid_droideka_ranged.iff", UnicodeString("a SBD"), "droideka_ranged", true);
	 weapon->setMinDamage(600 + level);
	 weapon->setMaxDamage(1300 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);

	 } else if (objectCRC ==0xD3C915F9 || objectCRC ==0xB8270A11) {
	 //Death Watch Wraith // Ghosts
	 weapon = new RifleRangedWeapon(_this, "object/weapon/ranged/rifle/shared_rifle_tenloss_dxr6_disruptor_loot.iff", UnicodeString("a Dxr6_Disrupter"), "rifle_dxr6", true);
	 weapon->setMinDamage(500 + level);
	 weapon->setMaxDamage(800 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);

	 } else if (objectCRC ==0xD83D2DEC || objectCRC ==0x730E66DF || objectCRC ==0xAD30C613) {
	 //Black Sun Henchmen Assassin Thug
	 weapon = new RifleRangedWeapon(_this, "object/weapon/ranged/rifle/shared_rifle_tenloss_dxr6_disruptor_loot.iff", UnicodeString("a Dxr6_Disrupter"), "rifle_dxr6", true);
	 weapon->setMinDamage(400 + level);
	 weapon->setMaxDamage(600 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);

	 } else if (objectCRC ==0x79BC6EB3) {
	 //Battle Droid
	 weapon = new CarbineRangedWeapon(_this, "object/weapon/ranged/carbine/shared_carbine_elite.iff", UnicodeString("a E5_Carbine"), "carbine_elite", true);
	 weapon->setMinDamage(400 + level);
	 weapon->setMaxDamage(600 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);

	 } else if (objectCRC ==0xC3DE9EF6) {
	 //Death Watch Blood Guards
	 weapon = new OneHandedMeleeWeapon(_this, "object/weapon/melee/baton/shared_baton_stun.iff", UnicodeString("a Stun_Baton"), "baton_stun", true);
	 weapon->setMinDamage(440 + level);
	 weapon->setMaxDamage(600 + level);
	 weapon->setAttackSpeed(2);
	 weapon->setDamageType(WeaponImplementation::STUN);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);

	 } else if (objectCRC ==0x320DD865) {
	 //Death Watch Overlord
	 weapon = new OneHandedMeleeWeapon(_this, "object/weapon/melee/baton/shared_baton_stun.iff", UnicodeString("a Stun_Baton"), "baton_stun", true);
	 weapon->setMinDamage(1850 + level);
	 weapon->setMaxDamage(2250 + level);
	 weapon->setAttackSpeed(3);
	 weapon->setDamageType(WeaponImplementation::STUN);
	 weapon->setArmorPiercing(WeaponImplementation::HEAVY);

	 } else if (objectCRC ==0xEA0D8178 || objectCRC ==0x42DB151E || objectCRC ==0xD5A733A8) {
	 //DWB Miners
	 weapon = new PistolRangedWeapon(_this, "object/weapon/ranged/pistol/shared_pistol_cdef.iff", UnicodeString("a CDEF_Pistol"), "pistol_cdef", true);
	 weapon->setMinDamage(100 + level);
	 weapon->setMaxDamage(175 + level);
	 weapon->setAttackSpeed(2.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);

	 } else if (objectCRC == 0x6BABDCC0 || objectCRC == 0x35F5AD39 || objectCRC == 0x113E9DB3 ||
	 objectCRC == 0x6050E92E || objectCRC == 0x46ABF8A1 || objectCRC == 0x71F874) {
	 // High level SMC, Rebel Surface Marshal
	 switch (System::random(1)) {
	 case 0 :
	 weapon = new PolearmMeleeWeapon(_this,
	 "object/weapon/melee/polearm/shared_lance_vibrolance.iff", UnicodeString("a Vibrolance"), "lance_vibrolance", true);
	 weapon->setMinDamage(250 + level);
	 weapon->setMaxDamage(450 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ELECTRICITY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);
	 break;
	 case 1 :
	 weapon = new PolearmMeleeWeapon(_this,
	 "object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", UnicodeString("a Long Vibro Axe"), "lance_vibro_axe", true);
	 weapon->setMinDamage(250 + level);
	 weapon->setMaxDamage(450 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
	 break;
	 }

	 } else if (objectCRC == 0xD84925C2 || objectCRC == 0x90D8EBF8 || objectCRC == 0x1FA893FD || objectCRC == 0x2E831404 ||
	 objectCRC == 0x2D98A9B3) {
	 // low level NS
	 switch (System::random(1)) {
	 case 0 :
	 weapon = new OneHandedMeleeWeapon(_this,
	 "object/weapon/melee/baton/shared_baton_gaderiffi.iff", UnicodeString("a Gaderiffi"), "baton_gaderiffi", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(200 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 break;
	 case 1 :
	 weapon = new OneHandedMeleeWeapon(_this,
	 "object/weapon/melee/baton/shared_baton_stun.iff", UnicodeString("a Stun Baton"), "baton_stun", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(250 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::STUN);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 break;
	 }

	 } else if (objectCRC == 0xF0663601 || objectCRC == 0xAC722907 || objectCRC == 0x889ADF8D || objectCRC == 0xC4E5A41E ||
	 objectCRC == 0x44F934A9) {
	 // High Level NS
	 switch (System::random(1)) {
	 case 0 :
	 weapon = new PolearmMeleeWeapon(_this,
	 "object/weapon/melee/polearm/shared_lance_vibrolance.iff", UnicodeString("a Vibrolance"), "lance_vibrolance", true);
	 weapon->setMinDamage(250 + level);
	 weapon->setMaxDamage(450 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ELECTRICITY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);
	 break;
	 case 1 :
	 weapon = new PolearmMeleeWeapon(_this,
	 "object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", UnicodeString("a Long Vibro Axe"), "lance_vibro_axe", true);
	 weapon->setMinDamage(250 + level);
	 weapon->setMaxDamage(450 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
	 break;
	 }
	 } else if (objectCRC == 0xC5A39C12 || objectCRC == 0x5CECC950) {
	 //Hutt Hideout
	 weapon = new OneHandedMeleeWeapon(_this,
	 "object/weapon/melee/baton/shared_baton_stun.iff", UnicodeString("a Stun Baton"), "baton_stun", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(250 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::STUN);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 } else if (objectCRC == 0x3517D918) {
	 //Gamorrean Guard
	 weapon = new PolearmMeleeWeapon(_this,
	 "object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", UnicodeString("a Long Vibro Axe"), "lance_vibro_axe", true);
	 weapon->setMinDamage(250 + level);
	 weapon->setMaxDamage(450 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
	 } else if (objectCRC == 0xAA197516) {
	 // NS Queen
	 switch (System::random(1)) {
	 case 0 :
	 weapon = new OneHandedMeleeWeapon(_this,
	 "object/weapon/melee/baton/shared_baton_gaderiffi.iff", UnicodeString("a Gaderiffi"), "baton_gaderiffi", true);
	 weapon->setMinDamage(800 + level);
	 weapon->setMaxDamage(1600 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 break;
	 case 1 :
	 weapon = new OneHandedMeleeWeapon(_this,
	 "object/weapon/melee/baton/shared_baton_stun.iff", UnicodeString("a Stun Baton"), "baton_stun", true);
	 weapon->setMinDamage(900 + level);
	 weapon->setMaxDamage(1700 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::STUN);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 break;
	 }
	 } else if (objectCRC == 0x9242B53A || objectCRC == 0x49551DAD || objectCRC == 0x587A20 ||
	 objectCRC == 0xFBBB5134 || objectCRC == 0xB2B636B9 || objectCRC == 0x69A19E2E) {
	 // Sennex Cave
	 switch (System::random(1)) {
	 case 0 :
	 weapon = new PolearmMeleeWeapon(_this,
	 "object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", UnicodeString("a Long Vibro Axe"), "lance_vibro_axe", true);
	 weapon->setMinDamage(250 + level);
	 weapon->setMaxDamage(450 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
	 break;
	 case 1 :
	 weapon = new TwoHandedMeleeWeapon(_this,
	 "object/weapon/melee/axe/shared_axe_vibroaxe.iff", UnicodeString("a Vibro Axe"), "axe_vibro", true);
	 weapon->setMinDamage(200 + level);
	 weapon->setMaxDamage(400 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
	 break;
	 }
	 } else if (objectCRC == 0xFB872285) { // lord nyax
	 weapon = new CarbineRangedWeapon(_this,
	 "object/weapon/ranged/carbine/shared_carbine_e11.iff", UnicodeString("a e11 Carbine"), "carbine_e11", true);
	 weapon->setMinDamage(550);
	 weapon->setMaxDamage(880);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
	 } else
	 return;

	 addInventoryItem(weapon);
	 setWeapon(weapon);
	 */
}

void CreatureImplementation::updateZone(bool lightUpdate, bool sendPackets) {
	bool insert = false;

	try {
		zone->lock();

		if (parent != NULL && parent->isCell()) {
			CellObject* cell = (CellObject*) parent;

			removeFromBuilding((BuildingObject*) cell->getParent());

			parent = NULL;
			insert = true;
		}

		if (insert)
			zone->insert(this);
		else
			zone->update(this);

		zone->inRange(this, 128);

		if (sendPackets)
			updateCreaturePosition(lightUpdate);

		zone->unlock();
	} catch (...) {
		System::out << "exception CreatureImplementation::updateZone()\n";

		zone->unlock();
	}
}

void CreatureImplementation::updateZoneWithParent(uint64 par, bool lightUpdate,
		bool sendPackets) {
	if (zone == NULL)
		return;

	SceneObject* newParent = parent;

	if (parent == NULL || (parent != NULL && parent->getObjectID() != par))
		newParent = zone->lookupObject(par);

	if (newParent == NULL)
		return;

	bool insert = false;

	try {
		zone->lock();

		if (newParent != parent) {
			if (parent == NULL) {
				zone->remove(this);
				insert = true;
			} else {
				BuildingObject* building =
						(BuildingObject*) parent->getParent();
				SceneObject* newObj = newParent->getParent();

				if (newObj->isBuilding()) {
					BuildingObject* newBuilding = (BuildingObject*) newObj;

					if (building != newBuilding) {
						removeFromBuilding(building);

						insert = true;
					}
				}

				((CellObject*) parent)->removeChild(_this);
			}
			parent = newParent;
			((CellObject*) parent)->addChild(_this);
		}

		BuildingObject* building = (BuildingObject*) parent->getParent();

		if (insert) {
			insertToBuilding(building);
		} else {
			building->update(this);
			building->inRange(this, 128);
		}

		if (sendPackets)
			updateCreaturePosition(lightUpdate);

		zone->unlock();
	} catch (...) {
		zone->unlock();
		error("Exception in CreatureImplementation::updateZoneWithParent");
	}
}

void CreatureImplementation::updateCreaturePosition(bool lightUpdate) {
	++movementCounter;

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		SceneObject* obj =
				(SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

		if (obj->isPlayer()) {
			Player* player = (Player*) obj;

			if (!lightUpdate) {
				if (parent != NULL)
					player->sendMessage(new UpdateTransformWithParentMessage(_this));
				else
					player->sendMessage(new UpdateTransformMessage(_this));
			} else {
				if (parent != NULL)
					player->sendMessage(new LightUpdateTransformWithParentMessage(_this));
				else
					player->sendMessage(new LightUpdateTransformMessage(_this));
			}
		}
	}
}

void CreatureImplementation::notifyPositionUpdate(QuadTreeEntry* obj) {
	try {
		if (obj == this)
			return;

		if (!isCreature() || aggroedCreature != NULL || isInCombat()) {
			return;
		}

		SceneObject* scno =
				(SceneObject*) (((SceneObjectImplementation*) obj)->_getStub());

		if (scno == targetObject) {
			return;
		}

		if (this->shouldAgro(scno)) {

			int worldAggroRange = 25;

			if(isKiller() && getLevel() > 35)
				worldAggroRange = 35;

			if(isKiller() && getLevel() > 70)
				worldAggroRange = 45;

			if(isKiller() && getLevel() > 100)
				worldAggroRange = 55;

			if ((parent == NULL && isInRange(scno, worldAggroRange)) || ((parent != NULL)
					&& (getParentID() == scno->getParentID()) && isInRange(
					scno, 10))) {

				info("aggroing " + scno->_getName());

				aggroedCreature = (CreatureObject *) scno;

				//((CreatureObject*)_this)->showFlyText("npc_reaction/flytext", "alert", 0xFF, 0, 0);

				if (isQueued())
					creatureManager->dequeueActivity(this);

				creatureManager->queueActivity(this, 10);
			}
		} else if ((parent == NULL) && scno->isPlayer() && !doRandomMovement && hasRandomMovement
				&& patrolPoints.isEmpty() && System::random(200) < 1) {
			doRandomMovement = true;

			positionZ = obj->getPositionZ();

			//System::out << hex << player->getObjectID() << " initiating movement of " << objectID << "\n";

			if (!isQueued())
				creatureManager->queueActivity(this, System::random(30000)
						+ 1000);
		}
	} catch (...) {
		error(
				"Unreported exception caught in void CreatureImplementation::notifyPositionUpdate(QuadTreeEntry* obj)\n");
	}
}

bool CreatureImplementation::shouldAgro(SceneObject * target) {

	if (this->isDead() || this->isIncapacitated())
		return false;

	if (!target->isPlayer() && !target->isNonPlayerCreature())
		return false;

	CreatureObject * creature = (CreatureObject *) target;

	if (creature->isDead() || creature->isIncapacitated())
		return false;

	if (target->isPlayer()) {
		Player * player = (Player *) target;
		if (player->isImmune())
			return false;

		if (this->isAgressive())
			return true;
	}

	if (target->isNonPlayerCreature()) {
		Creature * npc = (Creature *) target;

		if (npc->isMount() && this->isAgressive()) {

			if(System::random(10) == 7)
				return true;
			else
				return false;
		}
	}

	if (this->hatesFaction(creature->getFaction())) {
		if (creature->isPlayer() && ((Player *) creature)->isOnLeave())
			return false;
		else
			return true;
	}

	return false;
}

bool CreatureImplementation::activate() {
	try {
		wlock();

		if (!checkState() || zone == NULL) {
			unlock();
			return false;
		}

		bool needMoreActivity = false;

		if (aggroedCreature != NULL && targetObject != aggroedCreature) {
			updateTarget(aggroedCreature);
		} else if (doRandomMovement) {
			doRandomMovement = false;

			addRandomPatrolPoint(32 + System::random(64), false);
		}

		needMoreActivity |= doMovement();

		if (aggroedCreature != NULL) {
			if (!aggroedCreature->isAttackable())
				deaggro();
			else
				needMoreActivity |= attack(aggroedCreature);
		} else if (isInCombat())
			clearCombatState();

		needMoreActivity |= doRecovery();

		if (needMoreActivity && zone != NULL) {
			info("queuing more activities");

			creatureManager->queueActivity(this);
		} else {
			info("no more activities needed");
			deaggro();
		}

		unlock();
	} catch (Exception& e) {
		System::out << "exception CreatureImplementation::activate()\n";
		e.printStackTrace();

		unlock();
	} catch (...) {
		System::out << "exception CreatureImplementation::activate()\n";

		unlock();
	}

	return true;
}

void CreatureImplementation::removeFromQueue() {
	if (isQueued())
		creatureManager->dequeueActivity(this);
}

bool CreatureImplementation::checkState() {
	if (isDead() && isInActiveState()) {
		info("queing despawn");

		deaggro();

		creatureState = DESPAWNING;

		creatureManager->queueActivity(this, 120000);

		return false;
	} else if (isDeSpawning()) {
		deaggro();

		creatureState = RESPAWNING;

		unload();
		if (respawnTimer > 0) { // 0 is do not respawn
			StringBuffer msg;
			msg << "respawning creature with " << respawnTimer << "s timer";
			info(msg);

			creatureManager->queueActivity(this, respawnTimer * 1000);
		}
		return false;
	} else if (isReSpawning()) {
		reload();

		return false;
	}

	return true;

}

void CreatureImplementation::resetState() {
	zone = creatureManager->getZone();

	creatureState = ACTIVE;
	postureState = CreaturePosture::UPRIGHT;

	setHealth(getHealthMax());
	setAction(getActionMax());
	setMind(getMindMax());

	setHealthWounds(0);
	setActionWounds(0);
	setMindWounds(0);

	//damageMap.removeAll(); // TODO:uncomment and remove below code when VectorMap can use ManagedReference
	while (damageMap.size() > 0) {
		CreatureObject* object = damageMap.elementAt(0)->getKey();
		damageMap.drop(object);

		object->release();
	}

	defenderList.removeAll();

	clearStates();

	aggroedCreature = NULL;

	resetPatrolPoints(false);

	looted = false;

	if (randomizeRespawn) {
		float distance = System::random(64) + 16;
		randomizePosition(distance);
	}
}

void CreatureImplementation::broadcastNextPositionUpdate(PatrolPoint* point) {
	BaseMessage* msg;

	++movementCounter;

	if (point == NULL) {
		if (parent != NULL)
			msg = new UpdateTransformWithParentMessage(_this);
		else
			msg = new UpdateTransformMessage(_this);
	} else {
		if (point->getCellID() != 0)
			msg
					= new UpdateTransformWithParentMessage(_this, point->getPositionX(), point->getPositionZ(), point->getPositionY(), point->getCellID());
		else
			msg
					= new UpdateTransformMessage(_this, point->getPositionX(), point->getPositionZ(), point->getPositionY());
	}

	broadcastMessage(msg);
}

void CreatureImplementation::setNextPosition() {
	setPosition(nextPosition->getPositionX(), nextPosition->getPositionZ(),
		nextPosition->getPositionY());

	uint64 newCell = nextPosition->getCellID();

	StringBuffer reachedPosition;
	reachedPosition << "(" << positionX << ", " << positionY << ")";
	info("reached " + reachedPosition.toString());

	if (newCell != 0)
		updateZoneWithParent(newCell, false, false);
	else
		updateZone(false, false);
}

void CreatureImplementation::checkNewAngle(float directionangle) {
	float radians = M_PI / 2 - directionangle;
	uint8 newDirectionAngle = (uint8) ((radians / 6.283f) * 100);

	if (newDirectionAngle != directionAngle) {
		setRadialDirection(radians);

		broadcastNextPositionUpdate();
	}
}

bool CreatureImplementation::doMovement() {
	if (actualSpeed != 0)
		setNextPosition();

	if (isKnockedDown() || isRooted())
		return true;

	if (isKneeling())
		doStandUp();

	float waypointX, waypointY, waypointZ;
	uint64 cellID = 0;

	float maxSpeed = speed + 0.75f;

	if (isSnared())
		maxSpeed *= 0.20f;

	if (aggroedCreature != NULL && !camoSet) {
		waypointX = aggroedCreature->getPositionX();
		waypointZ = aggroedCreature->getPositionZ();
		waypointY = aggroedCreature->getPositionY();
		cellID = aggroedCreature->getParentID();

	} else if (!patrolPoints.isEmpty()) {
		PatrolPoint* waypoint = patrolPoints.get(0);

		waypointX = waypoint->getPositionX();
		waypointZ = waypoint->getPositionZ();
		waypointY = waypoint->getPositionY();

		cellID = waypoint->getCellID();
	} else
		return false;

	if (cellID != 0) {
		SceneObject* obj = zone->lookupObject(cellID);

		if (obj == NULL || !obj->isCell())
			cellID = 0;
	}

	float dx = waypointX - positionX;
	float dy = waypointY - positionY;

	float dist = sqrt(dx * dx + dy * dy);

	try {
		if (aggroedCreature != NULL && (dist > 100 || getZoneID()
				!= aggroedCreature->getZoneID())) {
			deaggro();
			return false;
		}
	} catch (...) {

	}

	float directionangle = atan2(dy, dx);

	float maxDistance = 5;

	if (weaponObject != NULL)
		maxDistance = weaponObject->getMaxRange();

	if (dist < maxDistance) {
		info("reached destintaion");

		if (aggroedCreature == NULL) {
			resetPatrolPoints(false);
			actualSpeed = 0;
		}

		//actualSpeed = 0;

		if (aggroedCreature != NULL && !aggroedCreature->isMoving()) {
			actualSpeed == 0;
		}

		checkNewAngle(directionangle);

		return false;
	}

	float newPositionX, newPositionZ, newPositionY;

	newPositionZ = waypointZ;

	if (actualSpeed < maxSpeed)
		actualSpeed += acceleration;
	else
		actualSpeed = maxSpeed;

	if (((parent != NULL) && (cellID == 0)) || (parent == NULL && cellID != 0)) {
		newPositionX = waypointX;
		newPositionY = waypointY;
	} else {
		newPositionX = positionX + (actualSpeed * (dx / dist));
		newPositionY = positionY + (actualSpeed * (dy / dist));
	}

	newPositionZ = zone->getHeight(newPositionX, newPositionY);

	nextPosition->setPosition(newPositionX, newPositionZ, newPositionY);
	nextPosition->setCellID(cellID);

	/*StringBuffer angleMsg;
	 angleMsg << "angle = " << directionangle * 180 / M_PI << " (" << dx << "," << dy << ")\n";
	 info(angleMsg.toString());*/

	setRadialDirection(M_PI / 2 - directionangle);

	StringBuffer position;
	position << "(" << newPositionX << ", " << newPositionY << ")";
	info("moving to " + position.toString());

	broadcastNextPositionUpdate(nextPosition);

	return true;
}

void CreatureImplementation::doIncapacitate() {
	if (isMount())
		return;

	disseminateXp(getLevel());
	deaggro();
	setPosture(CreaturePosture::DEAD);

	CreatureObject* lootOwner = getLootOwner();

	if ((isImperial() || isRebel()) && lootOwner != NULL && lootOwner->isPlayer()) {
		Player* lootOwnerPlayer = (Player *) lootOwner;

		String pfaction = (lootOwnerPlayer->isImperial())
			? "imperial" : "rebel";

		String myfaction = (isImperial())
			? "imperial" : "rebel";

		lootOwnerPlayer->addFactionPoints(pfaction, fpValue);
		lootOwnerPlayer->subtractFactionPoints(myfaction, fpValue);
	}

	creatureHealth = System::random(3) + 1;

	createHarvestList();

	scheduleDespawnCreature(180000);
}

void CreatureImplementation::createHarvestList() {
	Player* tempPlayer;
	GroupObject* group;
	Player* owner = (Player*) getLootOwner();

	String skillBox = "outdoors_scout_novice";

	if (owner == NULL || !hasOrganics())
		return;

	if (owner->isInAGroup()) {

		group = owner->getGroupObject();

		for (int i = 0; i < group->getGroupSize(); ++i) {

			tempPlayer = group->getGroupMember(i);

			if (tempPlayer != NULL && tempPlayer->hasSkillBox(skillBox))
				playerCanHarvest.add(tempPlayer->getFirstName());
		}

	} else {

		if (owner->hasSkillBox(skillBox))
			playerCanHarvest.add(owner->getFirstName());

	}
}

void CreatureImplementation::doStandUp() {
	setPosture(CreaturePosture::UPRIGHT, true);
}

void CreatureImplementation::doAttack(CreatureObject* target, int damage) {

	if (target != aggroedCreature && highestMadeDamage < damage) {
		highestMadeDamage = damage;

		info("new target locked");

		aggroedCreature = getLootOwner();

		updateTarget(target);

		info("new target locked");
	}

	if (aggroedCreature != NULL && !isActive() && creatureManager != NULL)
		creatureManager->queueActivity(this, 10);
}

bool CreatureImplementation::attack(CreatureObject* target) {
	info("attacking target");

	doCamoCheck(target);
	if (camoSet) {
		return false;
	}

	if (target == NULL || target == _this || (!target->isPlayer() && !target->isNonPlayerCreature()))
		return false;

	if (target->isIncapacitated() || target->isDead()) {
		deaggro();

		return false;
	}

	if (!isInRange(target, 70)) {
		if (((parent != NULL) && (nextPosition->getCellID() == 0)) || (parent
				== NULL && nextPosition->getCellID() != 0))
			return true;
		else {
			deaggro();

			return false;
		}
	}

	if (!nextAttackDelay.isPast()) {
		lastCombatAction.update();
		return true;
	}

	CombatManager* combatManager = server->getCombatManager();

	int skills = creatureSkills.size();

	Skill* skill = NULL;

	if (skills == 0)
		return false;
	else {
		int rand = System::random(skills - 1);
		skill = creatureSkills.get(rand);
	}

	if (skill == NULL)
		return false;

	uint32 actionCRC = skill->getNameCRC();

	//updateTarget(target->getObjectID());

	if (isDead() || isKnockedDown())
		return false;

	if (weaponObject != NULL
			&& (!isInRange(target, weaponObject->getMaxRange()))) {
		return true;
	} else if (!isInRange(target, skill->getRange()))
		return true;

	info("queuing attacking");

	String modifier = "";
	CommandQueueAction* action =
					new CommandQueueAction(_this, target->getObjectID(), 0, actionCRC, modifier);

	action->setSkill(skill);
	action->setTarget(target);

	combatManager->handleAction(action);
	delete action;

	if (target->isIncapacitated() || target->isDead()) {
		deaggro();

		return false;
	}

	if (target->isNonPlayerCreature() && ((Creature *)target)->isMount() && ((MountCreature *) target)->isDisabled()) {
		deaggro();

		return false;
	}

	lastCombatAction.update();

	float delay = skill->getSpeedRatio();

	if (weaponObject != NULL)
		delay = delay * weaponObject->getAttackSpeed();

	nextAttackDelay.update();
	nextAttackDelay.addMiliTime((uint64) (delay * 1000));

	return true;
}

float CreatureImplementation::getArmorResist(int resistType) {
	switch (resistType) {
	case 1:
		return kinetic - (kinetic * calculateBFRatio());

	case 2:
		return energy - (energy * calculateBFRatio());

	case 3:
		return electricity - (electricity * calculateBFRatio());

	case 4:
		return stun - (stun * calculateBFRatio());

	case 5:
		return blast - (blast * calculateBFRatio());

	case 6:
		return heat - (heat * calculateBFRatio());

	case 7:
		return cold - (cold * calculateBFRatio());

	case 8:
		return acid - (acid * calculateBFRatio());

	case 9:
		return lightSaber - (lightSaber * calculateBFRatio());

	default:
		return 0;
	}
}

void CreatureImplementation::doCamoCheck(CreatureObject* target) {
	unsigned int targetHash = target->getCharacterName().toString().hashCode();

	int targetCamoType = target->getCamoType();

	if (targetCamoType != CamoSkill::NONE) {

		if (targetCamoType == CamoSkill::MASKSCENT && !isCreature()) {
			camoSet = false;
			camoCount = 0;
			return;
		}

		// if more player are in the range and maskscent they should be checked
		// more often. i wasn't able to test this situation
		// in case of strange creature behavior it could store the last n players
		// instead of the last one. in this case a map or list and events are needed.

		if (lastCamoUser == targetHash && camoCount > 0 && !target->isInCombat()) {
			camoCount--;
			camoSet = true;
			return;
		}

		float rndNumber = (float) rand()/RAND_MAX;
		float score = target->getMaskScent();



		if (targetCamoType == CamoSkill::MASKSCENT)
			score -= 1.0f * (float) getLevel();
		else
			score -= 0.5f * (float) getLevel();

		score = score / 100.0f;


		if (target->isInCombat())
			score *= 0.75f;
		if (target->isProne())
			score *= 1.25f;
		if (target->isRidingCreature())
			score *= 0.5f;

		if(!isCreature())
			score *= 0.75f;

		if (score > 0.9f)
			score = 0.9f;
		else if (score < 0.1f)
			score = 0.1f;


		if (rndNumber < score) {
			if (!target->isInCombat()) {
				if (target->isPlayer()) {
					Player* player = (Player*) target;
					String type = "scout";
					player->addXp(type,getLevel()*3, true);

					StfParameter* params = new StfParameter();
					StringBuffer creatureName;
					creatureName << "@" << getStfName() << ":" << getSpeciesName();
					params->addTT(creatureName.toString());

					player->sendSystemMessage("skl_use", "sys_scentmask_success", params);
					delete params;
				}
			}
			lastCamoUser = targetHash;
			camoCount = 60;
			camoSet = true;

			return;
		} else {
			if (targetCamoType == CamoSkill::MASKSCENT)
				target->deactivateCamo(true);

			lastCamoUser = 0;
			camoCount = 0;
			camoSet = false;

			return;
		}

	} else {
		camoSet = false;
	}
}

/**
 * The actions that are performed when the creature loses interest in combat and returns to their business.
 */
void CreatureImplementation::deaggro() {
	if (aggroedCreature != NULL) {
		StringBuffer msg;
		msg << "deaggroed (0x" << hex << aggroedCreature->getObjectID() << dec
				<< ")";
		info(msg);

		if (aggroedCreature->isDead()) {
			removeFromDamageMap(aggroedCreature);
			dropDamageDone(aggroedCreature);
		}

		removeDefender(aggroedCreature);

		aggroedCreature = NULL;
	}

	clearTarget();
	clearCombatState();
}

void CreatureImplementation::activateRecovery() {
	if (zone != NULL && !isActive() && creatureManager != NULL)
		creatureManager->queueActivity(this);
}

bool CreatureImplementation::doRecovery() {
	if ((++activityCount) % 3 == 0) {
		//info("activating recovery");

		if (hasStates())
			doStatesRecovery();

		onRegenerateHAM();

		if ((activityCount) % 6 == 0)
			highestMadeDamage = 0;
	}

	if (isOnFullHealth() && !hasStates()) {
		highestMadeDamage = 0;

		return false;
	}

	return true;
}

void CreatureImplementation::performRandomIncapAnimation() {
	switch (System::random(20)) {
	case 0:
		doAnimation("laugh");
		break;
	case 1:
		doAnimation("rofl");
		break;
	case 2:
		doAnimation("chicken");
		break;
	case 3:
		doAnimation("airguitar");
		break;
	case 4:
		doAnimation("curtsey");
		break;
	case 5:
		doAnimation("bang");
		break;
	case 6:
		doAnimation("kiss");
		break;
	case 7:
		doAnimation("mock");
		break;
	case 8:
		doAnimation("strut");
		break;
	case 9:
		doAnimation("waft");
		break;
	default:
		doAnimation("rude");
		break;
	}
}

void CreatureImplementation::doStatesRecovery() {
	if (isKnockedDown() && knockdownRecoveryTime.isPast())
		doStandUp();

	if (isDizzied() && dizzyRecoveryTime.isPast())
		clearState(CreatureState::DIZZY);

	if (isBlinded() && blindRecoveryTime.isPast())
		clearState(CreatureState::BLINDED);

	if (isStunned() && stunRecoveryTime.isPast())
		clearState(CreatureState::STUNNED);

	if (isIntimidated() && intimidateRecoveryTime.isPast())
		clearState(CreatureState::INTIMIDATED);

	if (isRooted() && rootRecoveryTime.isPast())
		clearState(CreatureState::ROOTED);

	if (isSnared() && snareRecoveryTime.isPast())
		clearState(CreatureState::SNARED);

	if (isPoisoned()) {
		if (poisonRecoveryTime.isPast())
			clearState(CreatureState::POISONED);
		else
			doPoisonTick();
	}

	if (isDiseased()) {
		if (diseasedRecoveryTime.isPast())
			clearState(CreatureState::DISEASED);
		else
			doDiseaseTick();
	}

	if (isOnFire()) {
		if (fireRecoveryTime.isPast())
			clearState(CreatureState::ONFIRE);
		else
			doFireTick();
	}

	if (isBleeding()) {
		if (bleedingRecoveryTime.isPast())
			clearState(CreatureState::BLEEDING);
		else
			doBleedingTick();
	}

	updateStates();
}

void CreatureImplementation::queueRespawn() {
	creatureState = RESPAWNING;

	StringBuffer msg;
	info(msg);

	removeFromQueue();

	if (respawnTimer > 0)
		creatureManager->queueActivity(this, respawnTimer * 1000);
}

void CreatureImplementation::setPatrolPoint(PatrolPoint* cord, bool doLock) {
	try {
		wlock(doLock);

		patrolPoints.add(0, cord);

		if (!isActive())
			creatureManager->queueActivity(this);

		unlock(doLock);
	} catch (...) {
		System::out << "exception CreatureImplementation::addPatrolPoint()\n";
		unlock(doLock);
	}
}

void CreatureImplementation::resetPatrolPoints(bool doLock) {
	try {
		wlock(doLock);

		while (!patrolPoints.isEmpty()) {
			PatrolPoint* point = patrolPoints.remove(0);

			delete point;
		}

		//patrolPoints.removeAll();

		unlock(doLock);
	} catch (...) {
		System::out << "exception CreatureImplementation::addPatrolPoint()\n";
		unlock(doLock);
	}
}

void CreatureImplementation::addPatrolPoint(float x, float y, bool doLock) {
	float z = zone->getHeight(x, y);

	addPatrolPoint(new PatrolPoint(x, z, y, getParentID()), doLock);
}

void CreatureImplementation::addPatrolPoint(SceneObject* obj, bool doLock) {
	addPatrolPoint(
			new PatrolPoint(obj->getPositionX(), obj->getPositionZ(), obj->getPositionY(), obj->getParentID()),
			doLock);
}

void CreatureImplementation::addPatrolPoint(PatrolPoint* cord, bool doLock) {
	try {
		wlock(doLock);

		patrolPoints.add(cord);

		if (!isActive())
			creatureManager->queueActivity(this);

		unlock(doLock);
	} catch (...) {
		System::out << "exception CreatureImplementation::addPatrolPoint()\n";
		unlock(doLock);
	}
}

void CreatureImplementation::addRandomPatrolPoint(float radius, bool doLock) {
	float angle = (45 + System::random(200)) / 3.14;
	float distance = radius + System::random((int) radius);

	float newPositionX = positionX + cos(angle) * distance;
	float newPositionY = positionY + sin(angle) * distance;

	float newPositionZ = zone->getHeight(newPositionX, newPositionY);

	PatrolPoint
			* cord =
					new PatrolPoint(newPositionX, newPositionZ, newPositionY, getParentID());

	addPatrolPoint(cord, doLock);
}



//Event Handlers
void CreatureImplementation::onIncapacitateTarget(CreatureObject* victim) {
	performRandomIncapAnimation();

	if (isKiller() && victim->isPlayer() && !victim->isDead() && victim->isIncapacitated())
		deathblow((Player*) victim);

	deaggro();
}
