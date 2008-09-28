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
}

void CreatureImplementation::init() {
	zone = NULL;

	objectType = NONPLAYERCREATURE;

	creatureState = ACTIVE;

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

	actualSpeed = 0.f;

	movementCounter = 0;

	// stats
	aggroedCreature = NULL;
	willAggro = false;

	lootCreated = false;

	looted = false;

	creatureRemoveEvent = NULL;

	setObjectKeeping(true);

	stringstream logname;
	logname << "NPC = 0x" << hex << objectID;

	setLockName(logname.str());

	setLoggingName(logname.str());

	setLogging(false);
	setGlobalLogging(true);
}

void CreatureImplementation::sendRadialResponseTo(Player* player,
		ObjectMenuResponse* omr) {

	string skillBox = "outdoors_scout_novice";

	if (player->isInRange(getPositionX(), getPositionY(), 10.0f)
			&& !player->isInCombat() && player->hasSkillBox(skillBox)
			&& isDead() && canHarvest(player->getFirstName())) {

		omr->addRadialItem(0, 148, 3, "@sui:harvest_corpse");

		if (getMeatMax() != 0)
			omr->addRadialItem(4, 108, 3, "@sui:harvest_meat");

		if (getHideMax() != 0)
			omr->addRadialItem(4, 109, 3, "@sui:harvest_hide");

		if (getBoneMax() != 0)
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
		stringstream txt;
		txt << round(getKinetic()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic",
				txt.str());
	}

	if (energy > 0 && energy < 100) {
		stringstream txt;
		txt << round(getEnergy()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy",
				txt.str());
	}

	if (electricity > 0 && electricity < 100) {
		stringstream txt;
		txt << round(getElectricity()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_electrical",
				txt.str());
	}

	if (stun > 0 && stun < 100) {
		stringstream txt;
		txt << round(getStun()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun",
				txt.str());
	}

	if (blast > 0 && blast < 100) {
		stringstream txt;
		txt << round(getBlast()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast",
				txt.str());
	}

	if (heat > 0 && heat < 100) {
		stringstream txt;
		txt << round(getHeat()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_heat", txt.str());
	}

	if (cold > 0 && cold < 100) {
		stringstream txt;
		txt << round(getCold()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_cold", txt.str());
	}

	if (acid > 0 && acid < 100) {
		stringstream txt;
		txt << round(getAcid()) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_acid", txt.str());
	}

	if (lightSaber > 0 && lightSaber < 100) {
		stringstream txt;
		txt << round(getLightSaber()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint",
				txt.str());
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

	player->sendMessage(alm);
}

void CreatureImplementation::reload() {

	creatureManager->respawnCreature(_this);

	resetState();

	insertToZone(zone);

	info("creature respawned");
}

void CreatureImplementation::unload() {
	deagro();

	clearTarget();

	clearLootItems();

	resetPatrolPoints(false);

	playerCanHarvest.removeAll();

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
	if (creatureRemoveEvent == NULL)
		creatureRemoveEvent = new CreatureRemoveEvent(_this);

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

	string wpName = getCreatureWeaponName();
	if (wpName != "") {
		try {
			string wpObject = getCreatureWeapon();
			string wpName = getCreatureWeaponName();
			string wpTemp = getCreatureWeaponTemp();
			bool wpEq = (bool) getCreatureWeaponEquipped();
			int wpMinDamage = getCreatureWeaponMinDamage();
			int wpMaxDamage = getCreatureWeaponMaxDamage();
			float wpAttackSpeed = getCreatureWeaponAttackSpeed();
			string wpDamType = getCreatureWeaponDamageType();
			string wpArmorPiercing = getCreatureWeaponArmorPiercing();
			string wpClass = getCreatureWeaponClass();

			if (wpClass == "CarbineRangedWeapon")
				weapon = new CarbineRangedWeapon(_this, wpObject, unicode(
						wpName), wpTemp, wpEq);
			else if (wpClass == "RifleRangedWeapon")
				weapon
						= new RifleRangedWeapon(_this, wpObject, unicode(wpName), wpTemp, wpEq);
			else if (wpClass == "PistolRangedWeapon")
				weapon
						= new PistolRangedWeapon(_this, wpObject, unicode(
								wpName), wpTemp, wpEq);
			else if (wpClass == "UnarmedMeleeWeapon")
				weapon
						= new UnarmedMeleeWeapon(_this, wpObject, unicode(
								wpName), wpTemp, wpEq);
			else if (wpClass == "OneHandedMeleeWeapon")
				weapon = new OneHandedMeleeWeapon(_this, wpObject, unicode(
						wpName), wpTemp, wpEq);
			else if (wpClass == "TwoHandedMeleeWeapon")
				weapon = new TwoHandedMeleeWeapon(_this, wpObject, unicode(
						wpName), wpTemp, wpEq);
			else if (wpClass == "PolearmMeleeWeapon")
				weapon
						= new PolearmMeleeWeapon(_this, wpObject, unicode(
								wpName), wpTemp, wpEq);
			else if (wpClass == "OneHandedJediWeapon")
				weapon = new OneHandedJediWeapon(_this, wpObject, unicode(
						wpName), wpTemp, wpEq);
			else if (wpClass == "TwoHandedJediWeapon")
				weapon = new TwoHandedJediWeapon(_this, wpObject, unicode(
						wpName), wpTemp, wpEq);
			else if (wpClass == "PolearmJediWeapon")
				weapon
						= new PolearmJediWeapon(_this, wpObject, unicode(wpName), wpTemp, wpEq);
			else if (wpClass == "SpecialHeavyRangedWeapon")
				weapon = new SpecialHeavyRangedWeapon(_this, wpObject, unicode(
						wpName), wpTemp, wpEq);
			else if (wpClass == "HeavyRangedWeapon")
				weapon
						= new HeavyRangedWeapon(_this, wpObject, unicode(wpName), wpTemp, wpEq);

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

			addInventoryItem(weapon);
			setWeapon(weapon);
		} catch (...) {
			//ouch..something in the lua isnt right
			cout
					<< "exception CreatureImplementation::loadItems()  -  Weaponloading for creature "
					<< objectID << "\n";
			return;
		}
	} else
		return;
	/*
	 //old before new LUAs june 2008
	 if (objectCRC == 0x738E0B1F) { //Zealot of Lord Nyax + Diciple of Lord Nyax
	 weapon = new CarbineRangedWeapon(_this, "object/weapon/ranged/carbine/shared_carbine_laser.iff", unicode("a Laser Carbine"), "carbine_laser", true);
	 weapon->setMinDamage(350);
	 weapon->setMaxDamage(400);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
	 }
	 else if (objectCRC == 0xE275ECBB || objectCRC == 0xE275ECBB || objectCRC == 0xA1048F8A || objectCRC == 0xD084273F || objectCRC == 0x7477AB80) {
	 //Imperial GeneralMajor // Imperial General // Imperial High Colonel / Imperial Surface Marshall // Imperial Major
	 weapon = new PistolRangedWeapon(_this, "object/weapon/ranged/pistol/shared_pistol_dl44.iff", unicode("a DL-44 Pistol"), "pistol_dl44", true);
	 weapon->setMinDamage(350);
	 weapon->setMaxDamage(400);
	 weapon->setAttackSpeed(2.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);
	 setImperial();
	 }
	 else if (objectCRC == 0xBA7F23CD) { //storm trooper
	 weapon = new RifleRangedWeapon(_this, "object/weapon/ranged/rifle/shared_rifle_t21.iff", unicode("Teh Pwn"), "rifle_t21", true);
	 weapon->setMinDamage(350);
	 weapon->setMaxDamage(400);
	 weapon->setAttackSpeed(4);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);
	 setImperial();
	 }
	 else if (objectCRC == 0x4E38DA33) { //Dark trooper
	 //we assign but do not equip the weapon! We just need the line "setImperial" - but without an assigned weapon we will crash
	 weapon = new RifleRangedWeapon(_this, "object/weapon/ranged/rifle/shared_rifle_t21.iff", unicode("Teh Pwn"), "rifle_t21", false);
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
	 weapon = new PistolRangedWeapon(_this, "object/weapon/ranged/pistol/shared_pistol_cdef_corsec.iff", unicode("Corsec CDEF Pistol"), "pistol_cdef_corsec", true);
	 weapon->setMinDamage(150);
	 weapon->setMaxDamage(200);
	 weapon->setAttackSpeed(3);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);
	 }
	 else if (objectCRC == 0xFECDC4DE || objectCRC == 0x7EDC1419) { //  AT AT    / AT ST
	 weapon = new RifleRangedWeapon(_this,"object/weapon/ranged/vehicle/shared_vehicle_atst_ranged.iff", unicode("Imperial Cannon"), "vehicle_atst_ranged");
	 weapon->setAttackSpeed(1.5f);
	 setImperial();
	 }
	 else if (objectCRC == 0x8C70914) {
	 weapon = new OneHandedJediWeapon(_this,
	 "object/weapon/melee/sword/crafted_saber/shared_sword_lightsaber_one_handed_s4_gen4.iff",
	 unicode("Darth Saber"), "sword_lightsaber_one_handed_s4_gen4", true);
	 weapon->setDamageType(WeaponImplementation::LIGHTSABER);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 } else if (objectCRC == 0x2B0C220E || objectCRC == 0x476794EB || objectCRC == 0x4A889CCF ||
	 objectCRC == 0x6D029623 || objectCRC == 0x4A48B6CC || objectCRC == 0x1527DF01) {
	 // low level SMC, Rebel General
	 switch (System::random(1)) {
	 case 0 :
	 weapon = new OneHandedMeleeWeapon(_this, "object/weapon/melee/baton/shared_baton_gaderiffi.iff", unicode("a Gaderiffi"), "baton_gaderiffi", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(200 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 break;
	 case 1 :
	 weapon = new OneHandedMeleeWeapon(_this,
	 "object/weapon/melee/baton/shared_baton_stun.iff", unicode("a Stun Baton"), "baton_stun", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(250 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::STUN);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 break;
	 }
	 } else if (objectCRC == 0xE158FEC1) {
	 //ranged tusken raider
	 weapon = new RifleRangedWeapon(_this, "object/weapon/ranged/rifle/shared_rifle_tusken.iff", unicode("a Tusken Rifle"), "rifle_tusken", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(200 + level);
	 weapon->setAttackSpeed(4);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);

	 } else if (objectCRC ==0x148D60AA) {
	 //melee tusken raider
	 weapon = new OneHandedMeleeWeapon(_this, "object/weapon/melee/baton/shared_baton_gaderiffi.iff", unicode("a Gaderiffi"), "baton_gaderiffi", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(200 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);

	 } else if (objectCRC ==0xE21E6148) {
	 //SBD 0xE21E6148
	 weapon = new CarbineRangedWeapon(_this, "object/weapon/ranged/droid/shared_droid_droideka_ranged.iff", unicode("a SBD"), "droideka_ranged", true);
	 weapon->setMinDamage(600 + level);
	 weapon->setMaxDamage(1300 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);

	 } else if (objectCRC ==0xD3C915F9 || objectCRC ==0xB8270A11) {
	 //Death Watch Wraith // Ghosts
	 weapon = new RifleRangedWeapon(_this, "object/weapon/ranged/rifle/shared_rifle_tenloss_dxr6_disruptor_loot.iff", unicode("a Dxr6_Disrupter"), "rifle_dxr6", true);
	 weapon->setMinDamage(500 + level);
	 weapon->setMaxDamage(800 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);

	 } else if (objectCRC ==0xD83D2DEC || objectCRC ==0x730E66DF || objectCRC ==0xAD30C613) {
	 //Black Sun Henchmen Assassin Thug
	 weapon = new RifleRangedWeapon(_this, "object/weapon/ranged/rifle/shared_rifle_tenloss_dxr6_disruptor_loot.iff", unicode("a Dxr6_Disrupter"), "rifle_dxr6", true);
	 weapon->setMinDamage(400 + level);
	 weapon->setMaxDamage(600 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);

	 } else if (objectCRC ==0x79BC6EB3) {
	 //Battle Droid
	 weapon = new CarbineRangedWeapon(_this, "object/weapon/ranged/carbine/shared_carbine_elite.iff", unicode("a E5_Carbine"), "carbine_elite", true);
	 weapon->setMinDamage(400 + level);
	 weapon->setMaxDamage(600 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ENERGY);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);

	 } else if (objectCRC ==0xC3DE9EF6) {
	 //Death Watch Blood Guards
	 weapon = new OneHandedMeleeWeapon(_this, "object/weapon/melee/baton/shared_baton_stun.iff", unicode("a Stun_Baton"), "baton_stun", true);
	 weapon->setMinDamage(440 + level);
	 weapon->setMaxDamage(600 + level);
	 weapon->setAttackSpeed(2);
	 weapon->setDamageType(WeaponImplementation::STUN);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);

	 } else if (objectCRC ==0x320DD865) {
	 //Death Watch Overlord
	 weapon = new OneHandedMeleeWeapon(_this, "object/weapon/melee/baton/shared_baton_stun.iff", unicode("a Stun_Baton"), "baton_stun", true);
	 weapon->setMinDamage(1850 + level);
	 weapon->setMaxDamage(2250 + level);
	 weapon->setAttackSpeed(3);
	 weapon->setDamageType(WeaponImplementation::STUN);
	 weapon->setArmorPiercing(WeaponImplementation::HEAVY);

	 } else if (objectCRC ==0xEA0D8178 || objectCRC ==0x42DB151E || objectCRC ==0xD5A733A8) {
	 //DWB Miners
	 weapon = new PistolRangedWeapon(_this, "object/weapon/ranged/pistol/shared_pistol_cdef.iff", unicode("a CDEF_Pistol"), "pistol_cdef", true);
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
	 "object/weapon/melee/polearm/shared_lance_vibrolance.iff", unicode("a Vibrolance"), "lance_vibrolance", true);
	 weapon->setMinDamage(250 + level);
	 weapon->setMaxDamage(450 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ELECTRICITY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);
	 break;
	 case 1 :
	 weapon = new PolearmMeleeWeapon(_this,
	 "object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", unicode("a Long Vibro Axe"), "lance_vibro_axe", true);
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
	 "object/weapon/melee/baton/shared_baton_gaderiffi.iff", unicode("a Gaderiffi"), "baton_gaderiffi", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(200 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 break;
	 case 1 :
	 weapon = new OneHandedMeleeWeapon(_this,
	 "object/weapon/melee/baton/shared_baton_stun.iff", unicode("a Stun Baton"), "baton_stun", true);
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
	 "object/weapon/melee/polearm/shared_lance_vibrolance.iff", unicode("a Vibrolance"), "lance_vibrolance", true);
	 weapon->setMinDamage(250 + level);
	 weapon->setMaxDamage(450 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::ELECTRICITY);
	 weapon->setArmorPiercing(WeaponImplementation::LIGHT);
	 break;
	 case 1 :
	 weapon = new PolearmMeleeWeapon(_this,
	 "object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", unicode("a Long Vibro Axe"), "lance_vibro_axe", true);
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
	 "object/weapon/melee/baton/shared_baton_stun.iff", unicode("a Stun Baton"), "baton_stun", true);
	 weapon->setMinDamage(175 + level);
	 weapon->setMaxDamage(250 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::STUN);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 } else if (objectCRC == 0x3517D918) {
	 //Gamorrean Guard
	 weapon = new PolearmMeleeWeapon(_this,
	 "object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", unicode("a Long Vibro Axe"), "lance_vibro_axe", true);
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
	 "object/weapon/melee/baton/shared_baton_gaderiffi.iff", unicode("a Gaderiffi"), "baton_gaderiffi", true);
	 weapon->setMinDamage(800 + level);
	 weapon->setMaxDamage(1600 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::NONE);
	 break;
	 case 1 :
	 weapon = new OneHandedMeleeWeapon(_this,
	 "object/weapon/melee/baton/shared_baton_stun.iff", unicode("a Stun Baton"), "baton_stun", true);
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
	 "object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", unicode("a Long Vibro Axe"), "lance_vibro_axe", true);
	 weapon->setMinDamage(250 + level);
	 weapon->setMaxDamage(450 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
	 break;
	 case 1 :
	 weapon = new TwoHandedMeleeWeapon(_this,
	 "object/weapon/melee/axe/shared_axe_vibroaxe.iff", unicode("a Vibro Axe"), "axe_vibro", true);
	 weapon->setMinDamage(200 + level);
	 weapon->setMaxDamage(400 + level);
	 weapon->setAttackSpeed(1.5);
	 weapon->setDamageType(WeaponImplementation::KINETIC);
	 weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
	 break;
	 }
	 } else if (objectCRC == 0xFB872285) { // lord nyax
	 weapon = new CarbineRangedWeapon(_this,
	 "object/weapon/ranged/carbine/shared_carbine_e11.iff", unicode("a e11 Carbine"), "carbine_e11", true);
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
		cout << "exception CreatureImplementation::updateZone()\n";

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
				(SceneObject*) (((SceneObjectImplementation*) getInRangeObject(
						i))->_getStub());
		if (obj->isPlayer()) {
			Player* player = (Player*) obj;

			if (!lightUpdate) {
				if (parent != NULL) {
					UpdateTransformWithParentMessage* umsg =
							new UpdateTransformWithParentMessage(_this);
					player->sendMessage(umsg);
				} else {
					UpdateTransformMessage* umsg =
							new UpdateTransformMessage(_this);
					player->sendMessage(umsg);
				}
			} else {
				if (parent != NULL) {
					LightUpdateTransformWithParentMessage* umsg =
							new LightUpdateTransformWithParentMessage(_this);
					player->sendMessage(umsg);
				} else {
					LightUpdateTransformMessage* umsg =
							new LightUpdateTransformMessage(_this);
					player->sendMessage(umsg);
				}
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

		Player* player;

		switch (scno->getObjectType()) {
		case SceneObjectImplementation::PLAYER:
			player = (Player*) scno;

			if (isAgressive() && !isDead() && !player->isIncapacitated()
					&& !player->isDead() && !player->isImmune()) {

				if ((parent == NULL && isInRange(player, 24)) || ((parent
						!= NULL) && (getParentID() == player->getParentID())
						&& isInRange(player, 10))) {

					info("aggroing " + player->getFirstName());

					aggroedCreature = player;

					if (isQueued())
						creatureManager->dequeueActivity(this);

					creatureManager->queueActivity(this, 10);

				}
			} else if ((parent == NULL) && !doRandomMovement
					&& patrolPoints.isEmpty() && System::random(200) < 1) {
				doRandomMovement = true;

				positionZ = obj->getPositionZ();

				//cout << hex << player->getObjectID() << " initiating movement of " << objectID << "\n";

				if (!isQueued())
					creatureManager->queueActivity(this, System::random(30000)
							+ 1000);
			}

			break;
		}

	} catch (...) {
		error(
				"Unreported exception caught in void CreatureImplementation::notifyPositionUpdate(QuadTreeEntry* obj)\n");
	}
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
			zone->lock();

			doRandomMovement = false;

			zone->unlock();

			addRandomPatrolPoint(32 + System::random(64), false);
		}

		needMoreActivity |= doMovement();

		if (aggroedCreature != NULL) {
			if (!aggroedCreature->isAttackable())
				deagro();
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
			deagro();
		}

		unlock();
	} catch (Exception& e) {
		cout << "exception CreatureImplementation::activate()\n";
		e.printStackTrace();

		unlock();
	} catch (...) {
		cout << "exception CreatureImplementation::activate()\n";

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

		deagro();

		creatureState = DESPAWNING;

		creatureManager->queueActivity(this, 120000);

		return false;
	} else if (isDeSpawning()) {
		deagro();

		creatureState = RESPAWNING;

		unload();
		if (respawnTimer > 0) { // 0 is do not respawn
			stringstream msg;
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
	postureState = UPRIGHT_POSTURE;

	health = healthMax;
	action = actionMax;
	mind = mindMax;

	healthWounds = 0;
	actionWounds = 0;
	mindWounds = 0;

	//damageMap.removeAll(); // TODO:uncomment and remove below code when VectorMap can use ManagedReference
	while (damageMap.size() > 0) {
		CreatureObject* object = damageMap.elementAt(0)->getKey();
		damageMap.drop(object);

		object->release();
	}

	defenderList.removeAll();

	clearStates();

	try {

		zone->lock();

		aggroedCreature = NULL;

		zone->unlock();
	} catch (...) {
		zone->unlock();
	}

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
	try {
		zone->lock();

		setPosition(nextPosition->getPositionX(), nextPosition->getPositionZ(),
				nextPosition->getPositionY());

		zone->unlock();
	} catch (...) {
		zone->unlock();
	}
	uint64 newCell = nextPosition->getCellID();

	stringstream reachedPosition;
	reachedPosition << "(" << positionX << ", " << positionY << ")";
	info("reached " + reachedPosition.str());

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

	if (isKnockedDown())
		return true;

	if (isKneeled())
		doStandUp();

	float waypointX, waypointY, waypointZ;
	uint64 cellID = 0;

	float maxSpeed = speed + 0.75f;

	if (aggroedCreature != NULL) {
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

	/*stringstream angleMsg;
	 angleMsg << "angle = " << directionangle * 180 / M_PI << " (" << dx << "," << dy << ")\n";
	 info(angleMsg.str());*/

	setRadialDirection(M_PI / 2 - directionangle);

	stringstream position;
	position << "(" << newPositionX << ", " << newPositionY << ")";
	info("moving to " + position.str());

	broadcastNextPositionUpdate(nextPosition);

	return true;
}

void CreatureImplementation::doIncapacitate() {
	deagro();
	setPosture(DEAD_POSTURE);

	createHarvestList();

	scheduleDespawnCreature(180000);
}

void CreatureImplementation::createHarvestList() {

	Player* tempPlayer;
	GroupObject* group;
	Player* owner = (Player*) getLootOwner();

	string skillBox = "outdoors_scout_novice";

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
	setPosture(CreatureObjectImplementation::UPRIGHT_POSTURE, true);
}

void CreatureImplementation::doAttack(CreatureObject* target, int damage) {
	if (target != aggroedCreature && highestMadeDamage < damage) {
		highestMadeDamage = damage;

		info("new target locked");

		try {
			zone->lock();

			aggroedCreature = getLootOwner();

			zone->unlock();
		} catch (...) {
			zone->unlock();
		}

		updateTarget(target);

		info("new target locked");
	}

	if (aggroedCreature != NULL && !isActive())
		creatureManager->queueActivity(this, 10);
}

bool CreatureImplementation::attack(CreatureObject* target) {
	info("attacking target");

	if (target == NULL || target == _this || !target->isPlayer())
		return false;

	if (target->isIncapacitated() || target->isDead()) {
		deagro();

		return false;
	}

	if (!isInRange(target, 70)) {
		if (((parent != NULL) && (nextPosition->getCellID() == 0)) || (parent
				== NULL && nextPosition->getCellID() != 0))
			return true;
		else {
			deagro();

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

	string modifier = "";
	CommandQueueAction
			* action =
					new CommandQueueAction(_this, target->getObjectID(), 0, actionCRC, modifier);

	action->setSkill(skill);
	action->setTarget(target);

	combatManager->handleAction(action);
	delete action;

	if (target->isIncapacitated() || target->isDead()) {
		deagro();

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

void CreatureImplementation::deagro() {
	if (aggroedCreature != NULL) {
		stringstream msg;
		msg << "deaggroed (0x" << hex << aggroedCreature->getObjectID() << dec
				<< ")";
		info(msg);

		if (aggroedCreature->isDead() || aggroedCreature->isIncapacitated())
			doIncapAnimation();

		if (isKiller() && aggroedCreature->isIncapacitated()
				&& aggroedCreature->isPlayer()) {

			aggroedCreature->handleDeath();
		}

		removeFromDamageMap(aggroedCreature);
		removeDefender(aggroedCreature);

		try {
			zone->lock();

			aggroedCreature = NULL;

			zone->unlock();
		} catch (...) {
			zone->unlock();
		}
	}

	clearTarget();
	clearCombatState();
}

void CreatureImplementation::activateRecovery() {
	if (zone != NULL && !isActive())
		creatureManager->queueActivity(this);
}

bool CreatureImplementation::doRecovery() {
	if ((++activityCount) % 3 == 0) {
		//info("activating recovery");

		if (hasStates())
			doStatesRecovery();

		calculateHAMregen();

		if ((activityCount) % 6 == 0)
			highestMadeDamage = 0;
	}

	if (isOnFullHealth() && !hasStates()) {
		highestMadeDamage = 0;

		return false;
	}

	return true;
}

void CreatureImplementation::doIncapAnimation() {
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
		clearState(DIZZY_STATE);

	if (isBlinded() && blindRecoveryTime.isPast())
		clearState(BLINDED_STATE);

	if (isStunned() && stunRecoveryTime.isPast())
		clearState(STUNNED_STATE);

	if (isIntimidated() && intimidateRecoveryTime.isPast())
		clearState(INTIMIDATED_STATE);

	if (isPoisoned()) {
		if (poisonRecoveryTime.isPast())
			clearState(POISONED_STATE);
		else
			doPoisonTick();
	}

	if (isDiseased()) {
		if (diseasedRecoveryTime.isPast())
			clearState(DISEASED_STATE);
		else
			doDiseaseTick();
	}

	if (isOnFire()) {
		if (fireRecoveryTime.isPast())
			clearState(ONFIRE_STATE);
		else
			doFireTick();
	}

	if (isBleeding()) {
		if (bleedingRecoveryTime.isPast())
			clearState(BLEEDING_STATE);
		else
			doBleedingTick();
	}

	updateStates();
}

void CreatureImplementation::queueRespawn() {
	creatureState = RESPAWNING;

	stringstream msg;
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
		cout << "exception CreatureImplementation::addPatrolPoint()\n";
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
		cout << "exception CreatureImplementation::addPatrolPoint()\n";
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
		cout << "exception CreatureImplementation::addPatrolPoint()\n";
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
