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

#ifndef HEALMINDWOUNDOTHER1COMMAND_H_
#define HEALMINDWOUNDOTHER1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "QueueCommand.h"

class HealMindWoundOther1Command : public QueueCommand {
protected:
	int forceCost;

	int mindWoundHealed;
	int focusWoundHealed;
	int willpowerWoundHealed;
	int heal;

	float speed;
	float range;
	String effectName;
public:
	HealMindWoundOther1Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		forceCost = 0;

		range = 32;

		mindWoundHealed = 0;
		focusWoundHealed = 0;
		willpowerWoundHealed = 0;
		
		heal = 150;

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

		if (!creatureTarget->getWounds(CreatureAttribute::MIND)) {
			return false;
		}

		if (!creatureTarget->getWounds(CreatureAttribute::FOCUS)) {
			return false;
		}

		if (!creatureTarget->getWounds(CreatureAttribute::WILLPOWER)) {
			return false;
		}
		
		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			return false;
		}

		return true;
	}
	
	
	void sendWoundMessage(CreatureObject* object, CreatureObject* target, int mindWound, int focusWound, int willpowerWound) {
		if (!object->isPlayerCreature()) 
			return;
			
		if (!target->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>( target);

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (mindWound > 0 && focusWound > 0 && willpowerWound > 0) {
			msgBody << mindWound << " mind, " << focusWound << " focus, and "  << willpowerWound << " willpower";
		} else if (mindWound > 0) {
			msgBody << mindWound << " mind";
		} else if (focusWound > 0) {
			msgBody << focusWound << " focus";
		} else if (willpowerWound > 0) {
			msgBody << willpowerWound << " willpower";
		} else {
			creature->sendSystemMessage("Your target has no wounds of that type to heal."); //%NT has no wounds of that type to heal.
			return;
		}

		msgTail << " wounds.";

			msgPlayer << "You heal " << creatureTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString();
			msgTarget << creature->getFirstName() << " heals you for " << msgBody.toString() << msgTail.toString();

			creature->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());

	}	
	
	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!creatureTarget->getWounds(CreatureAttribute::MIND) && !creatureTarget->getWounds(CreatureAttribute::FOCUS) && !creatureTarget->getWounds(CreatureAttribute::WILLPOWER)) {
			creature->sendSystemMessage("Your target has no wounds of that type to heal."); //%NT has no wounds of that type to heal.
			return false;
		}
		
		if (creature->isProne()) {
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
					creature->sendSystemMessage("@jedi_spam:not_this_target"); //This command cannot be used on this target.
					
					return GENERALERROR;
			}
		} else
			object = creature;

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;


		PlayerObject* targetGhost = creatureTarget->getPlayerObject();

		if (targetGhost != NULL && creatureTarget->getFaction() != creature->getFaction() && !(targetGhost->getFactionStatus() & FactionStatus::ONLEAVE)) {
			return GENERALERROR;
		}
		
		if (creatureTarget == creature) {
			return GENERALERROR;
		}		

		if (!canPerformSkill(creature, creatureTarget))
			return GENERALERROR;
		
		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");
			return GENERALERROR;
		}


		
		uint32 healedMindWound = creatureTarget->healWound(creature, CreatureAttribute::MIND, heal, true);
		uint32 healedFocusWound = creatureTarget->healWound(creature, CreatureAttribute::FOCUS, heal, true);
		uint32 healedWillpowerWound = creatureTarget->healWound(creature, CreatureAttribute::WILLPOWER, heal, true);

		
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();
		
		if (playerObject->getForcePower() <= 85) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //You do not have enough force to do that.
			return GENERALERROR;
		}
		
		forceCost = MIN(((healedMindWound + healedFocusWound + healedWillpowerWound) / 15), 85);
		
		playerObject->setForcePower(playerObject->getForcePower() - forceCost); // Deduct force.	

		sendWoundMessage(creature, creatureTarget, healedMindWound, healedFocusWound, healedWillpowerWound);
		
		doAnimations(creature, creatureTarget);	
			
		return SUCCESS;
	}

};

#endif /* HEALMINDWOUNDOTHER1COMMAND_H_ */
