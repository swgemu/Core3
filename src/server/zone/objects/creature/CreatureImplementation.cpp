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
