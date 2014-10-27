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

#ifndef HEALALLOTHER2COMMAND_H_
#define HEALALLOTHER2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "ForceHealQueueCommand.h"

class HealAllOther2Command : public ForceHealQueueCommand {
protected:

	int healthHealed;
	int actionHealed;
	int mindHealed;
	
	int heal;	

	float speed;
	float range;
	String effectName;
public:
	HealAllOther2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {

		range = 32;

		healthHealed = 0;
		actionHealed = 0;
		mindHealed = 0;
		
		heal = 1500;		

		speed = 3.0;
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
	
	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH) && !creatureTarget->hasDamage(CreatureAttribute::ACTION) && !creatureTarget->hasDamage(CreatureAttribute::MIND)) {
			creature->sendSystemMessage("@jedi_spam:no_damage_heal_other"); //Your target has no damage of that type to heal.
			return false;
		}

		if (creature->isProne()) {
			return false;
		}

		if (creature->isKnockedDown()) {
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
		
		if (isWarcried(creature)) {
			return GENERALERROR;
		}

		if (!checkForceCost(creature)) {
			creature->sendSystemMessage("@jedi_spam:no_force_power");
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (!object->isCreatureObject()) {
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());

				if (tangibleObject != NULL && tangibleObject->isAttackableBy(creature)) {
					object = creature;
				} else {
					creature->sendSystemMessage("@jedi_spam:not_this_target"); //This command cannot be used on this target.
					return GENERALERROR;
				}
			}
		} else
			object = creature;

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingMount() || creatureTarget->isAttackableBy(creature))
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
		

		int healedHealth = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, heal, true);
		int healedAction = creatureTarget->healDamage(creature, CreatureAttribute::ACTION, heal, true);
		int healedMind = creatureTarget->healDamage(creature, CreatureAttribute::MIND, heal, true);

		
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();
		
		int forceCostDeducted = forceCost;

		forceCostDeducted = MIN(((healedHealth + healedAction + healedMind) / 9.5), forceCost);
		
		playerObject->setForcePower(playerObject->getForcePower() - forceCostDeducted); // Deduct force.

		sendHealMessage(creature, creatureTarget, healedHealth, healedAction, healedMind);
		
		doAnimations(creature, creatureTarget);	
			
		return SUCCESS;
	}

};

#endif /* HEALALLOTHER2COMMAND_H_ */
