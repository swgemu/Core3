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

#ifndef HEALALLOTHER1COMMAND_H_
#define HEALALLOTHER1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "QueueCommand.h"

class HealAllOther1Command : public QueueCommand {
protected:
	int forceCost;

	int healthHealed;
	int actionHealed;
	int mindHealed;
	
	int heal;

	float speed;
	float range;
	String effectName;
public:
	HealAllOther1Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		forceCost = 0;

		range = 32;

		healthHealed = 0;
		actionHealed = 0;
		mindHealed = 0;
		
		heal = 500;

		speed = 3.0;
	}
	
	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (creatureTarget == creature)
			creature->playEffect("clienteffect/pl_force_healing.cef", "");
		 else 
			creature->doCombatAnimation(creatureTarget,String("force_healing_1").hashCode(),0,0xFF);
	}

	bool checkTarget(CreatureObject* creature, CreatureObject* creatureTarget) {

		if (!creatureTarget->isPlayerCreature()) {
			return false;
		}

		if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH)) {
			return false;
		}

		if (!creatureTarget->hasDamage(CreatureAttribute::ACTION)) {
			return false;
		}

		if (!creatureTarget->hasDamage(CreatureAttribute::MIND)) {
			return false;
		}
		
		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			return false;
		}

		return true;
	}
	
	
	void sendHealMessage(CreatureObject* object, CreatureObject* target, int healthDamage, int actionDamage, int mindDamage) {
		if (!object->isPlayerCreature()) 
			return;
			
		if (!target->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>( target);

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (healthDamage > 0 && actionDamage > 0 && mindDamage > 0) {
			msgBody << healthDamage << " health, " << actionDamage << " action, and "  << mindDamage << " mind";
		} else if (healthDamage > 0) {
			msgBody << healthDamage << " health";
		} else if (actionDamage > 0) {
			msgBody << actionDamage << " action";
		} else if (mindDamage > 0) {
			msgBody << mindDamage << " mind";
		} else {
			StringIdChatParameter stringId("@healing_response:healing_response_63");
			stringId.setTT(creatureTarget->getObjectID());
			creature->sendSystemMessage(stringId); //%NT has no dmg of that type to heal.	
			return; //No damage to heal.
		}

		msgTail << " damage.";

			msgPlayer << "You heal " << creatureTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString();
			msgTarget << creature->getFirstName() << " heals you for " << msgBody.toString() << msgTail.toString();

			creature->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());

	}	
	
	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH) && !creatureTarget->hasDamage(CreatureAttribute::ACTION) && !creatureTarget->hasDamage(CreatureAttribute::MIND)) {
			StringIdChatParameter stringId("@healing_response:healing_response_63");
			stringId.setTT(creatureTarget->getObjectID());
			creature->sendSystemMessage(stringId); //%NT has no wounds of that type to heal.
			return false;
		}
		
		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			creature->sendSystemMessage("@container_error_message:container18");
			return false;
		}		

		return true;
	}	
	
	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}
		

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (!object->isCreatureObject()) {
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());

				if (tangibleObject != NULL && tangibleObject->isAttackableBy(creature)) {
					object = creature;
				} else
					return INVALIDTARGET;
			}
		} else
			object = creature;

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;


		PlayerObject* targetGhost = creatureTarget->getPlayerObject();
		
		if (creatureTarget == creature) {
			return GENERALERROR;
		}		

		if (!canPerformSkill(creature, creatureTarget))
			return GENERALERROR;
		
		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");
			return GENERALERROR;
		}


		uint32 healedHealth = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, heal, true);
		uint32 healedAction = creatureTarget->healDamage(creature, CreatureAttribute::ACTION, heal, true);
		uint32 healedMind = creatureTarget->healDamage(creature, CreatureAttribute::MIND, heal, true);

		
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();
		
		if (playerObject->getForcePower() <= 340) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //You do not have enough force to do that.
			return false;
		}
		
		forceCost = MIN(((healedHealth + healedAction + healedMind) / 4), 340);
		
		playerObject->setForcePower(playerObject->getForcePower() - forceCost); // Deduct force.	

		sendHealMessage(creature, creatureTarget, healedHealth, healedAction, healedMind);
		
		doAnimations(creature, creatureTarget);	
			
		return SUCCESS;
	}

};

#endif /* HEALALLOTHER1COMMAND_H_ */
