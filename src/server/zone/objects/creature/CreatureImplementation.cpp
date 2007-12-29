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

CreatureImplementation::CreatureImplementation(uint64 oid, CreatureGroup* group) : CreatureServant(oid), Event() {
	objectID = oid;
	type = CREATURE;
	
	stfName = "mob/creature_names";

	creatureGroup = group;
	
	setKeeping(true);

	init();
}

CreatureImplementation::~CreatureImplementation() {
}

void CreatureImplementation::init() {
	zone = NULL;

	objectType = NONPLAYERCREATURE;

	creatureState = ACTIVE;

	doRandomMovement = false;

	//visibilityRange = 32;

	// constants
	itemShift = 100;
	
	activityCount = 0;
	highestMadeDamage = 0;
	
	respawnTimer = 60;
	
	lair = NULL;
	
	level = 250;

	// stats
	aggroedCreature = NULL;
	willAggro = false;
	
	setObjectKeeping(true);
	
	stringstream logname;
	logname << "NPC = 0x" << hex << objectID;

	setLockName(logname.str());
	
	setLoggingName(logname.str());
	setLogging(false);
	setGlobalLogging(false);	
}

void CreatureImplementation::reload() {
	creatureManager->respawnCreature(_this);
	
	resetState();

	insertToZone(zone);
	
	info("creature respawned");
}

void CreatureImplementation::unload() {
	clearCombatState();

	clearTarget();

	if (zone != NULL && isInQuadTree()) {
		removeFromZone(true);
	}
	
	creatureManager->despawnCreature(_this);
	
	info("creature despawned");
}

void CreatureImplementation::loadItems() {
	InventoryImplementation* invImpl = new InventoryImplementation((CreatureObject*) _this);
	inventory = (Inventory*) invImpl->deploy();
	
	Weapon* weapon = NULL;
	
	if (objectCRC == 0xBA7F23CD) { //storm trooper
		RifleRangedWeaponImplementation* rifleImpl = new RifleRangedWeaponImplementation((Creature*) _this, "object/weapon/ranged/rifle/shared_rifle_t21.iff", 
				unicode("Teh Pwn"), "rifle_t21", true);
		
		weapon = (Weapon*) rifleImpl->deploy();
	} else if (objectCRC == 0xE158FEC1) { //tusken raider
		OneHandedMeleeWeaponImplementation* gardiffImpl = new OneHandedMeleeWeaponImplementation((Creature*) _this, "object/weapon/melee/baton/shared_baton_gaderiffi.iff", 
				unicode("Teh Pwn"), "baton_gaderiffi", true);
		
		weapon = (Weapon*) gardiffImpl->deploy();
	} else if (objectCRC == 0x148D60AA) { //elite tusken
		PolearmMeleeWeaponImplementation* lanceImpl = new PolearmMeleeWeaponImplementation((Creature*) _this, "object/weapon/melee/polearm/shared_lance_vibrolance.iff", 
				unicode("Teh Pwn Lance"), "lance_vibrolance", true);
		
		weapon = (Weapon*) lanceImpl->deploy();
	} else if (objectCRC == 0x8C70914) {
		OneHandedJediWeaponImplementation* saberImpl = new OneHandedJediWeaponImplementation((Creature*) _this, "object/weapon/melee/sword/crafted_saber/shared_sword_lightsaber_one_handed_s4_gen4.iff", 
				unicode("Darth Saber"), "sword_lightsaber_one_handed_s4_gen4", true);
		
		weapon = (Weapon*) saberImpl->deploy();
	} else
		return;
	
	addInventoryItem(weapon);
	setWeapon(weapon);
}

void CreatureImplementation::insertToZone(Zone* zone) {
	CreatureImplementation::zone = zone;
	zoneID = zone->getZoneID();

	try {
		zone->lock();
		
		zone->registerObject(_this);

		zone->insert(this);
		zone->inRange(this, 128);
		
		zone->unlock();
	} catch (...) {
		cout << "exception CreatureImplementation::insertToZone(Zone* zone)\n";

		zone->unlock();
	}
}

void CreatureImplementation::updateZone() {
	try {
		zone->lock();

		zone->update(this);
		zone->inRange(this, 128);

    	for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());
			if (obj->isPlayer()) {
				Player* player = (Player*) obj;

				UpdateTransformMessage* umsg = new UpdateTransformMessage(_this);
				player->sendMessage(umsg);
			}
		}

		/*UpdateTransformMessage* umsg = new UpdateTransformMessage(this);
		broadcastMessage(umsg, 128, false);*/

		++movementCounter;

		zone->unlock();
	} catch (...) {
		cout << "exception CreatureImplementation::updateZone()\n";

		zone->unlock();
	}
}

void CreatureImplementation::lightUpdateZone() {
	try {
		zone->lock();

		zone->update(this);
		zone->inRange(this, 128);

    	for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_this);
			if (obj->isPlayer()) {
				Player* player = (Player*) obj;

				LightUpdateTransformMessage* umsg = new LightUpdateTransformMessage((Creature*) _this);
				player->sendMessage(umsg);
			}
		}

		/*UpdateTransformMessage* umsg = new UpdateTransformMessage(this);
		broadcastMessage(umsg, 128, false);*/

		++movementCounter;

		zone->unlock();
	} catch (...) {
		cout << "exception CreatureImplementation::updateZone()\n";

		zone->unlock();
	}
}

void CreatureImplementation::removeFromZone(bool doLock) {
	clearCombatState();
	
	try {
		if (zone == NULL)
			return;
		
		zone->lock(doLock);

    	for (int i = 0; i < inRangeObjectCount(); ++i) {
			QuadTreeEntry* obj = getInRangeObject(i);
			
			if (obj != this)
				obj->removeInRangeObject(this);
		}

		removeInRangeObjects();
		
		zone->remove(this);
		
		zone->deleteObject(objectID);

		zone->unlock(doLock);
	} catch (...) {
		cout << "exception CreatureImplementation::removeFromZone(bool doLock)\n";

		zone->unlock(doLock);
	}
}

void CreatureImplementation::notifyPositionUpdate(QuadTreeEntry* obj) {
	if (obj == this || !isCreature() || aggroedCreature != NULL || isInCombat())
		return;
	
	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) obj)->_getStub());
	if (scno == targetObject)
		return;
		
	Player* player;

	switch (scno->getObjectType()) {
	case SceneObjectImplementation::PLAYER:
		player = (Player*) scno;

		if (isAgressive() && !player->isIncapacitated() && !player->isDead() && isInRange(player, 32)) {
			info("aggroing " + player->getFirstName());

			aggroedCreature = player;

			if (isQueued())
				creatureManager->dequeueActivity(this);
			
			creatureManager->queueActivity(this, 10);
		} else if (!doRandomMovement && patrolPoints.isEmpty() && System::random(200) < 1) {
			doRandomMovement = true;

			//cout << hex << player->getObjectID() << " initiating movement of " << objectID << "\n";
			
			if (!isQueued())
				creatureManager->queueActivity(this, System::random(30000) + 1000);
		}
		
		
		break;
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
			doRandomMovement = false;
			
			addRandomPatrolPoint(32 + System::random(64), false);
		}
		
		needMoreActivity |= doMovement();
	
		if (aggroedCreature != NULL)
			needMoreActivity |= attack(aggroedCreature);
		else if (isInCombat())
			clearCombatState();
		
		needMoreActivity |= doRecovery();
		
		if (needMoreActivity && zone != NULL) {
			info("queuing more activities");
			
			creatureManager->queueActivity(this);
		} else
			info("no more activities needed");
			
		unlock();
	} catch (...) {
		cout << "exception CreatureImplementation::activate()\n";

		unlock();
	}
			
}

bool CreatureImplementation::checkState() {
	if (isDead() && isInActiveState()) {
		info("queing despawn");
		
		clearCombatState();
		
		creatureState = DESPAWNING;
		
		creatureManager->queueActivity(this, 30000);
		
		return false;
	} else if (isDeSpawning()) {
		clearCombatState();
		
		creatureState = RESPAWNING;
		
		unload();

		stringstream msg;
		msg << "respawning creature with " << respawnTimer << "s timer";
		info(msg);
		
		creatureManager->queueActivity(this, respawnTimer * 1000);
		
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
	
	float distance = System::random(64) + 16;
	randomizePosition(distance);
}

bool CreatureImplementation::doMovement() {
	if (isKnockeddowned())
		return true;
		
	if (isKneeled())
		doStandUp();

	float waypointX, waypointY;
	float actualspeed = speed;

	if (aggroedCreature != NULL) {
		waypointX = aggroedCreature->getPositionX();
		waypointY = aggroedCreature->getPositionY();
		
		actualspeed *= 1.4f;
	} else if (!patrolPoints.isEmpty()) {
		Coordinate* waypoint = patrolPoints.get(0);
	
		waypointX = waypoint->getPositionX();
		waypointY = waypoint->getPositionY();

		actualspeed *= 0.5f;
	} else
		return false;
	
	float dx = waypointX - positionX; 
	float dy = waypointY - positionY;
	
	float dist = sqrt(dx * dx + dy * dy);
	
	if (dist < 5) {
		info("reached destintaion");
		
		if (aggroedCreature == NULL)
			patrolPoints.remove(0);

		return false;
	}
	
	positionX += actualspeed * (dx / dist);
	positionY += actualspeed * (dy / dist);
	
	float directionangle = atan2(dy, dx);
	//cout << "angle = " << directionangle * 180 / M_PI << " (" << dx << "," << dy << ")\n";
	
	setRadialDirection(M_PI / 2 - directionangle);
	
	stringstream position;
	position << "(" << positionX << ", " << positionY << ")"; 
	info("moving to " + position.str());

	updateZone();
	
	return true;
}

void CreatureImplementation::doIncapacitate() {
	clearCombatState();
	setPosture(DEAD_POSTURE);
}

void CreatureImplementation::doStandUp() {
	setPosture(CreatureObjectImplementation::UPRIGHT_POSTURE, true);
}

void CreatureImplementation::doAttack(CreatureObject* target, int damage) {
	if (target != aggroedCreature && highestMadeDamage < damage) {
		highestMadeDamage = damage;

		aggroedCreature = target;
		
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

	if (target->isIncapacitated() || target->isDead() || !isInRange(target, 64)) {
		aggroedCreature = NULL;
		
		clearTarget();
		clearCombatState();
		
		return false;
	}

	if (!nextAttackDelay.isPast())
		return true;
	
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

	if (isDead() || isKnockeddowned())
		return false;

	if (!isInRange(target, skill->getRange()))
		return true;

	info("queuing attacking");

	CommandQueueAction* action = new CommandQueueAction(_this, target->getObjectID(), actionCRC, 0);

	action->setSkill(skill);
	action->setTarget(target);
	
	combatManager->handleAction(action);
	delete action;
	
	if (target->isIncapacitated() || target->isDead()) {
		aggroedCreature = NULL;

		clearTarget();
		clearCombatState();
		
		return false;
	}
	
	lastCombatAction.update();

	return true;
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

void CreatureImplementation::doStatesRecovery() {
	if (isKnockeddowned() && knockdownRecoveryTime.isPast())
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
		else doPoisonTick();
	}
	
	if (isDiseased()) {
		if (diseasedRecoveryTime.isPast())
			clearState(DISEASED_STATE);
		else doDiseaseTick();
	}
	
	if (isOnFire()) {
		if (fireRecoveryTime.isPast())
			clearState(ONFIRE_STATE);
		else doFireTick();
	}
	
	if (isBleeding()) {
		if (bleedingRecoveryTime.isPast())
			clearState(BLEEDING_STATE);
		else doBleedingTick();
	}

	updateStates();
}

void CreatureImplementation::createLoot() {
	int creatureLevel = getLevel();

	if (creatureLevel == 0) 
		creatureLevel = 1;

	int weaponDropRate = 1750;
	int armorDropRate = 1750;
	int junkDropRate = 1050;
	int creditDropRate = 1500;
	
	setCashCredits(0);

	int itemcount = System::random(3) + 1;

	for (int i = 0; i < itemcount; ++i) {
		if (System::random(armorDropRate) + creatureLevel > 1000) 
			createArmorLoot(creatureLevel);
		
		if (System::random(weaponDropRate) + creatureLevel > 1000)
			createWeaponLoot(creatureLevel);
		
		if (System::random(junkDropRate) > 1000)
			createJunkLoot();
		
		if (System::random(creditDropRate) + creatureLevel > 1000)
			setCashCredits(creatureLevel * System::random(1234) / 25);
	}
}

void CreatureImplementation::createWeaponLoot(int creatureLevel) {
	Weapon* item = NULL;
	
	switch (System::random(12)) {
	case 0 :	// UNARMED
		UnarmedMeleeWeaponImplementation* unarmedImpl = new UnarmedMeleeWeaponImplementation((Creature*) _this, 
				"object/weapon/melee/special/shared_vibroknuckler.iff",	unicode("a Vibroknuckler"), "vibroknuckler", false);
		item = (Weapon*) unarmedImpl->deploy();
		break;
	case 1 :	// ONEHANDED
		OneHandedMeleeWeaponImplementation* onehandImpl = new OneHandedMeleeWeaponImplementation((Creature*) _this, 
				"object/weapon/melee/baton/shared_baton_gaderiffi.iff", unicode("a Gaderiffi"), "baton_gaderiffi", true);
		item = (Weapon*) onehandImpl->deploy();
		break;
	case 2 :	// TWOHANDED
		TwoHandedMeleeWeaponImplementation* twohandImpl = new TwoHandedMeleeWeaponImplementation((Creature*) _this, 
				"object/weapon/melee/2h_sword/shared_2h_sword_maul.iff", unicode("a Power Hammer"), "2h_sword_battleaxe", false);
		item = (Weapon*) twohandImpl->deploy();
		break;
	case 3 :	// POLEARM
		PolearmMeleeWeaponImplementation* polearmImpl = new PolearmMeleeWeaponImplementation((Creature*) _this, 
				"object/weapon/melee/polearm/shared_lance_vibrolance.iff", unicode("a Vibrolance"), "lance_vibrolance", true);
		item = (Weapon*) polearmImpl->deploy();
		break;
	case 4 :	// PISTOL
		PistolRangedWeaponImplementation* pistolImpl = new PistolRangedWeaponImplementation((Creature*) _this, 
				"object/weapon/ranged/pistol/shared_pistol_cdef.iff", unicode("a CDEF Pistol"), "pistol_cdef", false);
		item = (Weapon*) pistolImpl->deploy();
		break;
	case 5 :	// CARBINE
		CarbineRangedWeaponImplementation* carbImpl = new CarbineRangedWeaponImplementation((Creature*) _this,
				"object/weapon/ranged/carbine/shared_carbine_cdef.iff", unicode("a CDEF Carbine"), "carbine_cdef", false);
		item = (Weapon*) carbImpl->deploy();
		break;
	case 6 :	// RIFLE
		RifleRangedWeaponImplementation* rifleImpl = new RifleRangedWeaponImplementation((Creature*) _this, 
				"object/weapon/ranged/rifle/shared_rifle_t21.iff", unicode("a T21 Rifle"), "rifle_t21", true);
		item = (Weapon*) rifleImpl->deploy();
		break;
	case 7 :	// ONEHANDED
		OneHandedMeleeWeaponImplementation* onehand2Impl = new OneHandedMeleeWeaponImplementation((Creature*) _this, 
				"object/weapon/melee/baton/shared_baton_stun.iff", unicode("a Stun Baton"), "baton_stun", true);
		item = (Weapon*) onehand2Impl->deploy();
		break;
	case 8 :	// TWOHANDED
		TwoHandedMeleeWeaponImplementation* twohand2Impl = new TwoHandedMeleeWeaponImplementation((Creature*) _this, 
				"object/weapon/melee/2h_sword/shared_2h_sword_scythe.iff", unicode("a Scythe"), "2h_sword_scythe", false);
		item = (Weapon*) twohand2Impl->deploy();
		break;
	case 9 :	// POLEARM
		PolearmMeleeWeaponImplementation* polearm2Impl = new PolearmMeleeWeaponImplementation((Creature*) _this, 
				"object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", unicode("a Long Vibro Axe"), "lance_vibro_axe", true);
		item = (Weapon*) polearm2Impl->deploy();
		break;
	case 10 :	// PISTOL
		PistolRangedWeaponImplementation* pistol2Impl = new PistolRangedWeaponImplementation((Creature*) _this, 
				"object/weapon/ranged/pistol/shared_pistol_dx2.iff", unicode("a DX2 Pistol"), "pistol_dx2", false);
		item = (Weapon*) pistol2Impl->deploy();
		break;
	case 11 :	// CARBINE
		CarbineRangedWeaponImplementation* carb2Impl = new CarbineRangedWeaponImplementation((Creature*) _this, 
				"object/weapon/ranged/carbine/shared_carbine_dxr6.iff", unicode("a DX6R Carbine"), "carbine_dx6r", false);
		item = (Weapon*) carb2Impl->deploy();
		break;
	case 12 :	// RIFLE
		RifleRangedWeaponImplementation* rifle2Impl = new RifleRangedWeaponImplementation((Creature*) _this, 
				"object/weapon/ranged/rifle/shared_rifle_tenloss_dxr6_disruptor_loot.iff", unicode("a DX6R Rifle"), "rifle_tenloss_dxr6", true);
		item = (Weapon*) rifle2Impl->deploy();
		break;			
	}
	
	if (item != NULL) {
		item->setWeaponStats(creatureLevel);
		addInventoryItem(item);
	}
}

void CreatureImplementation::createArmorLoot(int creatureLevel) {
	Armor* item = NULL;
	
	switch (System::random(5)){
	case 0:
		switch (System::random(8)) {
		case 0 :
			ArmorImplementation* chest1Impl = new ArmorImplementation(_this, 0x7B476F26, 
					unicode("Composite Chestplate"), "armor_composite_chestplate", false);
			item = (Armor*) chest1Impl->deploy();
			break;
		case 1 :
			ArmorImplementation* helmet1Impl = new ArmorImplementation(_this, 0x9AF51EAA, 
					unicode("Composite Helmet"), "armor_composite_helmet", false);
			item = (Armor*) helmet1Impl->deploy();
			break;
		case 2 :
			ArmorImplementation* boots1Impl = new ArmorImplementation(_this, 0xDB91E9DB, 
					unicode("Composite Boots"), "armor_composite_boots", false);
			item = (Armor*) boots1Impl->deploy();
			break;
		case 3 :
			ArmorImplementation* gloves1Impl = new ArmorImplementation(_this, 0x2C35FFA2, 
					unicode("Composite Gloves"), "armor_composite_gloves", false);
			item = (Armor*) gloves1Impl->deploy();
			break;
		case 4 :
			ArmorImplementation* pants1Impl = new ArmorImplementation(_this, 0xC294C432, 
					unicode("Composite Leggings"), "armor_composite_pants", false);
			item = (Armor*) pants1Impl->deploy();
			break;
		case 5 :
			ArmorImplementation* bicepl1Impl = new ArmorImplementation(_this, 0x13A4DA11, 
					unicode("Composite Bicep"), "armor_composite_bicep_l", false);
			item = (Armor*) bicepl1Impl->deploy();
			break;
		case 6 :
			ArmorImplementation* bicepr1Impl = new ArmorImplementation(_this, 0x63719F82, 
					unicode("Composite Bicep"), "armor_composite_bicep_r", false);
			item = (Armor*) bicepr1Impl->deploy();
			break;
		case 7 :
			ArmorImplementation* bracerl1Impl = new ArmorImplementation(_this, 0x4DB0192D, 
					unicode("Composite Bracer"), "armor_composite_bracer_l", false);
			item = (Armor*) bracerl1Impl->deploy();
			break;
		case 8 :
			ArmorImplementation* bracerr1Impl = new ArmorImplementation(_this, 0x3D655CBE, 
					unicode("Composite Bracer"), "armor_composite_bracer_r", false);
			item = (Armor*) bracerr1Impl->deploy();
			break;
		}
		break;
	case 1:
		if (creatureLevel > 99) {
			switch (System::random(8)) {	// BH Armor
			case 0 :
				ArmorImplementation* chest2Impl = new ArmorImplementation(_this, 0x4FD29AA3, 
						unicode("Bounty Hunter Chestplate"), "armor_bounty_hunter_chestplate", false);
				item = (Armor*) chest2Impl->deploy();
				break;
			case 1 :
				ArmorImplementation* helmet2Impl = new ArmorImplementation(_this, 0x30DB6875, 
						unicode("Bounty Hunter Helmet"), "armor_bounty_hunter_helmet", false);
				item = (Armor*) helmet2Impl->deploy();
				break;
			case 2 :
				ArmorImplementation* boots2Impl = new ArmorImplementation(_this, 0x219DF586, 
						unicode("Bounty Hunter Boots"), "armor_bounty_hunter_boots", false);
				item = (Armor*) boots2Impl->deploy();
				break;
			case 3 :
				ArmorImplementation* gloves2Impl = new ArmorImplementation(_this, 0x861B897D, 
						unicode("Bounty Hunter Gloves"), "armor_bounty_hunter_gloves", false);
				item = (Armor*) gloves2Impl->deploy();
				break;
			case 4 :
				ArmorImplementation* pants2Impl = new ArmorImplementation(_this, 0x9873E13B, 
						unicode("Bounty Hunter Leggings"), "armor_bounty_hunter_pants", false);
				item = (Armor*) pants2Impl->deploy();
				break;
			case 5 :
				ArmorImplementation* bicepl2Impl = new ArmorImplementation(_this, 0xE37785C9, 
						unicode("Bounty Hunter Bicep"), "armor_bounty_hunter_bicep_l", false);
				item = (Armor*) bicepl2Impl->deploy();
				break;
			case 6 :
				ArmorImplementation* bicepr2Impl = new ArmorImplementation(_this, 0x93A2C05A, 
						unicode("Bounty Hunter Bicep"), "armor_bounty_hunter_bicep_r", false);
				item = (Armor*) bicepr2Impl->deploy();
				break;
			case 7 :
				ArmorImplementation* bracerl2Impl = new ArmorImplementation(_this, 0x17573C24, 
						unicode("Bounty Hunter Bracer"), "armor_bounty_hunter_bracer_l", false);
				item = (Armor*) bracerl2Impl->deploy();
				break;
			case 8 :
				ArmorImplementation* bracerr2Impl = new ArmorImplementation(_this, 0x678279B7, 
						unicode("Bounty Hunter Bracer"), "armor_bounty_hunter_bracer_r", false);	
				item = (Armor*) bracerr2Impl->deploy();
				break;
			}
			
			creatureLevel = creatureLevel + 25;	
		}
		
		break;
	case 2:
		if (creatureLevel > 124) {
			switch (System::random(8)) {	// Mando Armor
			case 0 :
				ArmorImplementation* chest3Impl = new ArmorImplementation(_this, 0x24525C1C, 
						unicode("Mandalorian Chestplate"), "armor_mandalorian_chest", false);
				item = (Armor*) chest3Impl->deploy();
				break;
			case 1 :
				ArmorImplementation* helmet3Impl = new ArmorImplementation(_this, 0x37A4683E, 
						unicode("Mandalorian Helmet"), "armor_mandalorian_helmet", false);
				item = (Armor*) helmet3Impl->deploy();
				break;
			case 2 :
				ArmorImplementation* boots3Impl = new ArmorImplementation(_this, 0x84AD5603, 
						unicode("Mandalorian Boots"), "armor_mandalorian_shoes", false);
				item = (Armor*) boots3Impl->deploy();
				break;
			case 3 :
				ArmorImplementation* gloves3Impl = new ArmorImplementation(_this, 0x81648936, 
						unicode("Mandalorian Gloves"), "armor_mandalorian_gloves", false);
				item = (Armor*) gloves3Impl->deploy();
				break;
			case 4 :
				ArmorImplementation* pants3Impl = new ArmorImplementation(_this, 0x770C3F1B, 
						unicode("Mandalorian Leggings"), "armor_mandalorian_pants", false);
				item = (Armor*) pants3Impl->deploy();
				break;
			case 5 :
				ArmorImplementation* bicepl3Impl = new ArmorImplementation(_this, 0x82309ECC, 
						unicode("Mandalorian Bicep"), "armor_mandalorian_bicep_l", false);
				item = (Armor*) bicepl3Impl->deploy();
				break;
			case 6 :
				ArmorImplementation* bicepr3Impl = new ArmorImplementation(_this, 0xF2E5DB5F, 
						unicode("Mandalorian Bicep"), "armor_mandalorian_bicep_r", false);
				item = (Armor*) bicepr3Impl->deploy();
				break;
			case 7 :
				ArmorImplementation* bracerl3Impl = new ArmorImplementation(_this, 0xF828E204, 
						unicode("Mandalorian Bracer"), "armor_mandalorian_bracer_l", false);
				item = (Armor*) bracerl3Impl->deploy();
				break;
			case 8 :
				ArmorImplementation* bracerr3Impl = new ArmorImplementation(_this, 0x88FDA797, 
						unicode("Mandalorian Bracer"), "armor_mandalorian_bracer_r", false);
				item = (Armor*) bracerr3Impl->deploy();
				break;
			}
			
			creatureLevel = creatureLevel + 50;
		}
		
		break;
	case 3:
		if (objectCRC == 0xBA7F23CD) { 
			switch (System::random(8)) {
			case 0 :
				ArmorImplementation* chest4Impl = new ArmorImplementation(_this, 0xF22790E, 
						unicode("Stormtrooper Chestplate"), "armor_stormtrooper_chest", false);
				item = (Armor*) chest4Impl->deploy();
				break;
			case 1 :
				ArmorImplementation* helmet4Impl = new ArmorImplementation(_this, 0xC499637D, 
						unicode("Stormtrooper Helmet"), "armor_stormtrooper_helmet", false);
				item = (Armor*) helmet4Impl->deploy();
				break;
			case 2 :
				ArmorImplementation* boots4Impl = new ArmorImplementation(_this, 0x7833E9D6, 
						unicode("Stormtrooper Boots"), "armor_stormtrooper_boots", false);
				item = (Armor*) boots4Impl->deploy();
				break;
			case 3 :
				ArmorImplementation* gloves4Impl = new ArmorImplementation(_this, 0x72598275, 
						unicode("Stormtrooper Gloves"), "armor_stormtrooper_gloves", false);
				item = (Armor*) gloves4Impl->deploy();
				break;
			case 4 :
				ArmorImplementation* pants4Impl = new ArmorImplementation(_this, 0x1863926A, 
						unicode("Stormtrooper Leggings"), "armor_stormtrooper_pants", false);
				item = (Armor*) pants4Impl->deploy();
				break;
			case 5 :
				ArmorImplementation* bicepl4Impl = new ArmorImplementation(_this, 0x3BC0061C, 
						unicode("Stormtrooper Bicep"), "armor_stormtrooper_bicep_l", false);
				item = (Armor*) bicepl4Impl->deploy();
				break;
			case 6 :
				ArmorImplementation* bicepr4Impl = new ArmorImplementation(_this, 0x4B15438F, 
						unicode("Stormtrooper Bicep"), "armor_stormtrooper_bicep_r", false);
				item = (Armor*) bicepr4Impl->deploy();
				break;
			case 7 :
				ArmorImplementation* bracerl4Impl = new ArmorImplementation(_this, 0x97474F75, 
						unicode("Stormtrooper Bracer"), "armor_stormtrooper_bracer_l", false);
				item = (Armor*) bracerl4Impl->deploy();
				break;
			case 8 :
				ArmorImplementation* bracerr4Impl = new ArmorImplementation(_this, 0xE7920AE6, 
						unicode("Stormtrooper Bracer"), "armor_stormtrooper_bracer_r", false);
				item = (Armor*) bracerr4Impl->deploy();
				break;
			}
		}
		
		break;
	case 4:
		if ((objectCRC == 0x1527DF01)||(objectCRC == 0x71F874)) {
			switch (System::random(5)) {
			case 0 :
				ArmorImplementation* chest5Impl = new ArmorImplementation(_this, 0x98A41A65, 
						unicode("Marine Chestplate"), "armor_marine_chest", false);
				item = (Armor*) chest5Impl->deploy();
				break;
			case 1 :
				ArmorImplementation* helmet5Impl = new ArmorImplementation(_this, 0x1890B6F4, 
						unicode("Marine Helmet"), "armor_marine_helmet", false);
				item = (Armor*) helmet5Impl->deploy();
				break;
			case 2 :
				ArmorImplementation* boots5Impl = new ArmorImplementation(_this, 0xA06D625, 
						unicode("Marine Boots"), "armor_marine_boots", false);
				item = (Armor*) helmet5Impl->deploy();
				break;
			case 3 :
				ArmorImplementation* pants5Impl = new ArmorImplementation(_this, 0xF3D42F59, 
						unicode("Marine Leggings"), "armor_marine_pants", false);
				item = (Armor*) pants5Impl->deploy();
				break;
			case 4 :
				ArmorImplementation* bicepl5Impl = new ArmorImplementation(_this, 0x16825F91, 
						unicode("Marine Bicep"), "armor_marine_bicep_l", false);
				item = (Armor*) bicepl5Impl->deploy();
				break;
			case 5 :
				ArmorImplementation* bicepr5Impl = new ArmorImplementation(_this, 0x66571A02, 
						unicode("Marine Bicep"), "armor_marine_bicep_r", false);
				item = (Armor*) bicepr5Impl->deploy();
				break;
			}
		}
		break;
	/*case 5:
		if (((objectCRC == 0xF0663601)||(objectCRC == 0xAA197516))&&(System::random(10)==7)) {
			ArmorImplementation* nsImpl = new ArmorImplementation(_this, 0x2E943BD2, unicode("Nightsister Bicep"), "nightsister_bicep_r", false);
			item = (Armor*) nsImpl->deploy();
			creatureLevel = creatureLevel + 200;
		break;
		}*/
	}
		
	if (item != NULL) {
		item->setArmorStats(creatureLevel);
		addInventoryItem(item);
	}
}

void CreatureImplementation::createJunkLoot() {
	TangibleObject* item = NULL;
	
	switch (System::random(10)) {
	case 0 :
		TangibleObjectImplementation* item0Impl = new TangibleObjectImplementation(_this, unicode("a Viewscreen (broken)"), 
				"object/tangible/loot/tool/shared_viewscreen_broken_s2.iff", 0xBC03F94);
		item = item0Impl->deploy();
		break;
	case 1 :
		TangibleObjectImplementation* item1Impl = new TangibleObjectImplementation(_this, unicode("Binoculars (broken)"), 
				"object/tangible/loot/tool/shared_binoculars_broken_s1.iff", 0x1E84585F);
		item = item1Impl->deploy();
		break;
	case 2 :
		TangibleObjectImplementation* item2Impl = new TangibleObjectImplementation(_this, unicode("a Human Skull"), 
				"object/tangible/loot/misc/shared_loot_skull_human.iff", 0x25B24532);
		item = item2Impl->deploy();
		break;
	case 3 :
		TangibleObjectImplementation* item3Impl = new TangibleObjectImplementation(_this, unicode("an Impulse Detector (broken)"), 
				"/tangible/loot/tool/shared_impulse_detector_broken_s3.iff", 0x2D13F714);
		item = item3Impl->deploy();
		break;
	case 4 :
		TangibleObjectImplementation* item4Impl = new TangibleObjectImplementation(_this, unicode("a Cage"), 
				"object/tangible/loot/misc/shared_cage_s01.iff", 0x3238DD4A);
		item = item4Impl->deploy();
		break;
	case 5 :
		TangibleObjectImplementation* item5Impl = new TangibleObjectImplementation(_this, unicode("a Rare Artifact"), 
				"object/tangible/loot/misc/shared_artifact_rare_s01.iff", 0x3393694D);
		item = item5Impl->deploy();
		break;
	case 6 :
		TangibleObjectImplementation* item6Impl = new TangibleObjectImplementation(_this, unicode("Holocron Splinters"), 
				"object/tangible/loot/misc/shared_holocron_splinters_sith_s01.iff", 0x3CEA7897);
		item = item6Impl->deploy();
		break;
	case 7 :
		TangibleObjectImplementation* item7Impl = new TangibleObjectImplementation(_this, unicode("a Calibrator (broken)"), 
				"object/tangible/loot/tool/shared_calibrator_broken.iff", 0x5289E0D9);
		item = item7Impl->deploy();
		break;
	case 8 :
		TangibleObjectImplementation* item8Impl = new TangibleObjectImplementation(_this, unicode("a Corrupt Datadisk"), 
				"object/tangible/loot/misc/shared_datadisk_corrupt.iff", 0x5F4B8D76);
		item = item8Impl->deploy();
		break;
	case 9 :
		TangibleObjectImplementation* item9Impl = new TangibleObjectImplementation(_this, unicode("Jawa Beads"), 
				"object/tangible/loot/misc/shared_jawa_beads.iff", 0x619F4DFD);
		item = item9Impl->deploy();
		break;
	case 10 :
		TangibleObjectImplementation* item10Impl = new TangibleObjectImplementation(_this, unicode("a Briefcase"), 
				"object/tangible/loot/misc/shared_briefcase_s01.iff", 0x6C34F325);
		item = item10Impl->deploy();
		break;	
	}
	
	if (item != NULL)
		addInventoryItem(item);
}

void CreatureImplementation::lootCorpse(Player* player) {
	if (!isDead())
		return;

	int credits = getCashCredits();
	
	if (credits > 0) {	
		setCashCredits(0);
		
		player->addCashCredits(credits);
		
		stringstream creditText;
		creditText << "You loot " << credits << " credits from corpse of " << characterName.c_str() << ".";

		player->sendSystemMessage(creditText.str());
	}
	
	if (inventory != NULL) {
		for (int i = inventory->objectsSize() - 1; i >= 0; --i) {
			TangibleObject* lootItem = (TangibleObject*) inventory->getObject(i);
			
			if (!lootItem->isEquipped()) {
				inventory->removeObject(i);
				
				player->addInventoryItem(lootItem);
				
				lootItem->sendTo(player);
				
				lootItem->setPersistent(false);
			}
		}

		player->sendSystemMessage("You have completely looted the corpse of all items.");
	} else 
		player->sendSystemMessage("You find nothing else of value on the selected corpse.");
	
	if (isQueued())
		server->removeEvent(this);
	
	unload();
}

void CreatureImplementation::setPatrolPoint(Coordinate* cord, bool doLock) {
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
			Coordinate* point = patrolPoints.remove(0);
			
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
	addPatrolPoint(new Coordinate(x , positionZ, y), doLock);
}

void CreatureImplementation::addPatrolPoint(SceneObject* obj, bool doLock) {
	addPatrolPoint(new Coordinate(obj->getPositionX() , positionZ, obj->getPositionY()), doLock);
}

void CreatureImplementation::addPatrolPoint(Coordinate* cord, bool doLock) {
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

void CreatureImplementation::addRandomPatrolPoint(float distance, bool doLock) {
	Coordinate* cord = new Coordinate(positionX, positionZ, positionY);
	cord->randomizePosition(distance);
	
	addPatrolPoint(cord, doLock);
}
