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

CreatureImplementation::CreatureImplementation(uint64 oid, CreatureGroup* group) : CreatureServant(oid), Event() {
	objectID = oid;
	type = CREATURE;
	
	baseID = oid;
	
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
	setGlobalLogging(true);
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
	InventoryImplementation* invImpl = new InventoryImplementation(_this);
	inventory = (Inventory*) invImpl->deploy();
	
	ContainerImplementation* containerImpl = new ContainerImplementation(getNewItemID());
	lootContainer = (Container*) containerImpl->deploy();
	
	Weapon* weapon = NULL;
	
	if (objectCRC == 0xBA7F23CD) { //storm trooper
		RifleRangedWeaponImplementation* rifleImpl = new RifleRangedWeaponImplementation(_this, 
				"object/weapon/ranged/rifle/shared_rifle_t21.iff", unicode("Teh Pwn"), "rifle_t21", true);
		
		weapon = (Weapon*) rifleImpl->deploy();
	} else if (objectCRC == 0x8C70914) {
		OneHandedJediWeaponImplementation* saberImpl = new OneHandedJediWeaponImplementation(_this, 
				"object/weapon/melee/sword/crafted_saber/shared_sword_lightsaber_one_handed_s4_gen4.iff", 
				unicode("Darth Saber"), "sword_lightsaber_one_handed_s4_gen4", true);
		
		weapon = (Weapon*) saberImpl->deploy();
	} else if (objectCRC == 0xD84925C2 || objectCRC == 0x90D8EBF8 || objectCRC == 0x1FA893FD || objectCRC == 0x2E831404 || 
			   objectCRC == 0x2D98A9B3 || objectCRC == 0x2B0C220E || objectCRC == 0x476794EB || objectCRC == 0x4A889CCF ||
			   objectCRC == 0x6D029623 || objectCRC == 0x4A48B6CC || objectCRC == 0x1527DF01 || objectCRC == 0xE158FEC1) { 
		// low level NS, SMC, Rebel General, Tusken Raider		
		switch (System::random(1)) {
		case 0 :
			OneHandedMeleeWeaponImplementation* gaffi2Impl = new OneHandedMeleeWeaponImplementation(_this, "object/weapon/melee/baton/shared_baton_gaderiffi.iff", unicode("a Gaderiffi"), "baton_gaderiffi", true);
			gaffi2Impl->setMinDamage(75 + level);
			gaffi2Impl->setMaxDamage(100 + level);
			gaffi2Impl->setAttackSpeed(1.5);
			gaffi2Impl->setDamageType(WeaponImplementation::KINETIC);
			gaffi2Impl->setArmorPiercing(WeaponImplementation::NONE);

			weapon = (Weapon*) gaffi2Impl->deploy();
			break;
		case 1 :
			OneHandedMeleeWeaponImplementation* baton1Impl = new OneHandedMeleeWeaponImplementation(_this, 
					"object/weapon/melee/baton/shared_baton_stun.iff", unicode("a Stun Baton"), "baton_stun", true);
			baton1Impl->setMinDamage(75 + level);
			baton1Impl->setMaxDamage(100 + level);
			baton1Impl->setAttackSpeed(1.5);
			baton1Impl->setDamageType(WeaponImplementation::STUN);
			baton1Impl->setArmorPiercing(WeaponImplementation::NONE);

			weapon = (Weapon*) baton1Impl->deploy();
			break;
		}
	} else if (objectCRC == 0xF0663601 || objectCRC == 0xAC722907 || objectCRC == 0x889ADF8D || objectCRC == 0xC4E5A41E || 
			   objectCRC == 0x44F934A9 || objectCRC == 0x6BABDCC0 || objectCRC == 0x35F5AD39 || objectCRC == 0x113E9DB3 ||
			   objectCRC == 0x6050E92E || objectCRC == 0x46ABF8A1 || objectCRC == 0x71F874   || objectCRC == 0x148D60AA) {
		// High level NS, SMC, Rebel Surface Marshal, Elite Tusken
		switch (System::random(1)) {
		case 0 :
			PolearmMeleeWeaponImplementation* vibrolance1Impl = new PolearmMeleeWeaponImplementation(_this, 
					"object/weapon/melee/polearm/shared_lance_vibrolance.iff", unicode("a Vibrolance"), "lance_vibrolance", true);
			vibrolance1Impl->setMinDamage(150 + level);
			vibrolance1Impl->setMaxDamage(300 + level);
			vibrolance1Impl->setAttackSpeed(1.5);
			vibrolance1Impl->setDamageType(WeaponImplementation::ELECTRICITY);
			vibrolance1Impl->setArmorPiercing(WeaponImplementation::LIGHT);

			weapon = (Weapon*) vibrolance1Impl->deploy();
			break;
		case 1 :
			PolearmMeleeWeaponImplementation* lva1Impl = new PolearmMeleeWeaponImplementation(_this, 
					"object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", unicode("a Long Vibro Axe"), "lance_vibro_axe", true);
			lva1Impl->setMinDamage(150 + level);
			lva1Impl->setMaxDamage(300 + level);
			lva1Impl->setAttackSpeed(1.5);
			lva1Impl->setDamageType(WeaponImplementation::KINETIC);
			lva1Impl->setArmorPiercing(WeaponImplementation::MEDIUM);

			weapon = (Weapon*) lva1Impl->deploy();
			break;
		}
	} else if (objectCRC == 0xFB872285) { // lord nyax
		CarbineRangedWeaponImplementation* nyaxCarbImpl = new CarbineRangedWeaponImplementation(_this, 
				"object/weapon/ranged/carbine/shared_carbine_laser.iff", unicode("a Laser Carbine"), "carbine_laser", true);
		nyaxCarbImpl->setMinDamage(250);
		nyaxCarbImpl->setMaxDamage(450);
		nyaxCarbImpl->setAttackSpeed(1.5);
		nyaxCarbImpl->setDamageType(WeaponImplementation::ENERGY);
		nyaxCarbImpl->setArmorPiercing(WeaponImplementation::MEDIUM);

		weapon = (Weapon*) nyaxCarbImpl->deploy();
	} else
		return;
	
	addInventoryItem(weapon);
	setWeapon(weapon);
}

void CreatureImplementation::insertToZone(Zone* zone) {
	CreatureImplementation::zone = zone;
	zoneID = zone->getZoneID();

	stringstream msg;
	msg << "spawned on " << zoneID;
	info(msg);

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
		if (zone == NULL || !isInQuadTree())
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
			aggroedCreature->acquire();

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
	
		if (aggroedCreature != NULL) {
			if (aggroedCreature->isPlayer() && !((Player*) aggroedCreature)->isOnline())
				deagro();
			else
				needMoreActivity |= attack(aggroedCreature);
		} else if (isInCombat())
			clearCombatState();
		
		needMoreActivity |= doRecovery();
		
		if (needMoreActivity && zone != NULL) {
			info("queuing more activities");
			
			creatureManager->queueActivity(this);
		} else
			info("no more activities needed");
			
		unlock();
	} catch (Exception& e) {
		cout << "exception CreatureImplementation::activate()\n";
		e.printStackTrace();

		unlock();
	} catch (...) {
		cout << "exception CreatureImplementation::activate()\n";

		unlock();
	}
			
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
	
	healthWounds = 0;
	actionWounds = 0;
	mindWounds = 0;
	
	clearStates();
	
	float distance = System::random(64) + 16;
	randomizePosition(distance);
}

bool CreatureImplementation::doMovement() {
	if (isKnockedDown())
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

		info("new target locked");

		aggroedCreature = target;
		aggroedCreature->acquire();
		
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
		deagro();

		doIncapAnimation();
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

	if (isDead() || isKnockedDown())
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
		deagro();
		return false;
	}
	
	lastCombatAction.update();

	return true;
}

void CreatureImplementation::deagro() {
	if (aggroedCreature != NULL) {
		stringstream msg;
		msg << "deaggroed (0x" << hex << aggroedCreature->getObjectID() << dec << ")";
		info(msg);
	
		aggroedCreature->release();
		aggroedCreature = NULL;
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

void CreatureImplementation::queueRespawn() {
	creatureState = RESPAWNING;
			
	stringstream msg;
	msg << "respawning creature with " << respawnTimer << "s timer";
	info(msg);
			
	removeFromQueue();
	
	creatureManager->queueActivity(this, respawnTimer * 1000);
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
