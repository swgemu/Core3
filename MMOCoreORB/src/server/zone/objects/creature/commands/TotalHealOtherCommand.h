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

#ifndef TOTALHEALOTHERCOMMAND_H_
#define TOTALHEALOTHERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "QueueCommand.h"

class TotalHealOtherCommand : public QueueCommand {
protected:

	int forceCost;
	int heal;	

	int healthHealed;
	int actionHealed;
	int mindHealed;

	int healthWoundHealed;
	int strengthWoundHealed;
	int constitutionWoundHealed;
	
	int actionWoundHealed;
	int quicknessWoundHealed;
	int staminaWoundHealed;	
	
	int mindWoundHealed;
	int focusWoundHealed;
	int willpowerWoundHealed;	

	float speed;
	float range;
	String effectName;
	
public:
	TotalHealOtherCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	forceCost = 0;
	heal = 6000;
		
	healthHealed = 0;
	actionHealed = 0;
	mindHealed = 0;
		
	healthWoundHealed = 0;
	strengthWoundHealed = 0;
	constitutionWoundHealed = 0;		
		
	actionWoundHealed = 0;
	quicknessWoundHealed = 0;
	staminaWoundHealed = 0;	

	mindWoundHealed = 0;
	focusWoundHealed = 0;
	willpowerWoundHealed = 0;	

	speed = 3.0f;
	
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

		if (!creatureTarget->getWounds(CreatureAttribute::HEALTH)) {
			return false;
		}
		
		if (!creatureTarget->getWounds(CreatureAttribute::STRENGTH)) {
			return false;
		}

		if (!creatureTarget->getWounds(CreatureAttribute::CONSTITUTION)) {
			return false;
		}

		if (!creatureTarget->getWounds(CreatureAttribute::ACTION)) {
			return false;
		}

		if (!creatureTarget->getWounds(CreatureAttribute::QUICKNESS)) {
			return false;
		}

		if (!creatureTarget->getWounds(CreatureAttribute::STAMINA)) {
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

		if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH)) {
			return false;
		}

		if (!creatureTarget->hasDamage(CreatureAttribute::ACTION)) {
			return false;
		}

		if (!creatureTarget->hasDamage(CreatureAttribute::MIND)) {
			return false;
		}

		if (!creatureTarget->hasState(CreatureState::STUNNED)) {
			return false;
		}		

		if (!creatureTarget->hasState(CreatureState::DIZZY)) {
			return false;
		}

		if (!creatureTarget->hasState(CreatureState::INTIMIDATED)) {
			return false;
		}
		
		if (!creatureTarget->hasState(CreatureState::BLINDED)) {
			return false;
		}

		if (!creatureTarget->isPoisoned()) {
			return false;
		}

		if (!creatureTarget->isDiseased()) {
			return false;
		}

		if (!creatureTarget->isBleeding()) {
			return false;
		}			
		
		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			return false;
		}

		return true;
	}
	
	
	void sendWoundMessage(CreatureObject* object, CreatureObject* target, int healthWound, int actionWound, int mindWound, int strengthWound, int constitutionWound, int quicknessWound, int staminaWound, int focusWound, int willpowerWound) {
		if (!object->isPlayerCreature()) 
			return;
			
		if (!target->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>( target);

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (healthWound > 0 && strengthWound > 0 && constitutionWound > 0 && actionWound > 0 && quicknessWound > 0 && staminaWound > 0 && mindWound > 0 && focusWound > 0 && willpowerWound > 0) {
			msgBody << healthWound << " health, " << strengthWound << " strength, " << constitutionWound << " constitution " << actionWound << " action, " << quicknessWound << " quickness, " << staminaWound << " stamina " << mindWound << " mind, " << focusWound << " focus, and "  << willpowerWound << " willpower";;
		} else if (healthWound > 0) {
			msgBody << healthWound << " health";
		} else if (strengthWound > 0) {
			msgBody << strengthWound << " strength";
		} else if (constitutionWound > 0) {
			msgBody << constitutionWound << " constitution";
		} else if (actionWound > 0) {
			msgBody << actionWound << " action";
		} else if (quicknessWound > 0) {
			msgBody << quicknessWound << " quickness";
		} else if (staminaWound > 0) {
			msgBody << staminaWound << " stamina";
		} else if (mindWound > 0) {
			msgBody << mindWound << " mind";
		} else if (focusWound > 0) {
			msgBody << focusWound << " focus";
		} else if (willpowerWound > 0) {
			msgBody << willpowerWound << " willpower";			
		} else {
			creature->sendSystemMessage("Your target has nothing of that type to heal."); //Your target has nothing of that type to heal.
			return;
		}

		msgTail << " wounds.";

			msgPlayer << "You heal " << creatureTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString();
			msgTarget << creature->getFirstName() << " heals you for " << msgBody.toString() << msgTail.toString();

			creature->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());

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

			msgPlayer << "You heal " << creatureTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString(); // You heal %TT for %DI points of %TO.
			msgTarget << "You are healed for " << msgBody.toString() << " points of damage by " << creature->getFirstName(); // You are healed for %DI points of %TO by %TT.

			creature->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());

	}	
	
	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!creatureTarget->getWounds(CreatureAttribute::HEALTH) && !creatureTarget->getWounds(CreatureAttribute::STRENGTH) && !creatureTarget->getWounds(CreatureAttribute::CONSTITUTION) && !creatureTarget->getWounds(CreatureAttribute::ACTION) && !creatureTarget->getWounds(CreatureAttribute::QUICKNESS) && !creatureTarget->getWounds(CreatureAttribute::STAMINA) && !creatureTarget->getWounds(CreatureAttribute::MIND) && !creatureTarget->getWounds(CreatureAttribute::FOCUS) && !creatureTarget->getWounds(CreatureAttribute::WILLPOWER) && !creatureTarget->hasDamage(CreatureAttribute::HEALTH) && !creatureTarget->hasDamage(CreatureAttribute::ACTION) && !creatureTarget->hasDamage(CreatureAttribute::MIND) && !creatureTarget->hasState(CreatureState::STUNNED) && !creatureTarget->hasState(CreatureState::DIZZY) && !creatureTarget->hasState(CreatureState::INTIMIDATED) && !creatureTarget->hasState(CreatureState::BLINDED) && !creatureTarget->isPoisoned() && !creatureTarget->isDiseased() && !creatureTarget->isBleeding()) {
			creature->sendSystemMessage("Your target has nothing of that type to heal."); //Your target has nothing of that type to heal.
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
		
		if (!creatureTarget->isHealableBy(creature)) {
		creature->sendSystemMessage("@healing:pvp_no_help");
			return GENERALERROR;
			}		
			
		if (!canPerformSkill(creature, creatureTarget))
			return GENERALERROR;
	
		int healDisease = creatureTarget->healDot(CreatureState::DISEASED, 300);
		int healPoison = creatureTarget->healDot(CreatureState::POISONED, 300);
		int healBleeding = creatureTarget->healDot(CreatureState::BLEEDING, 300);
		
		int healedHealthWound = creatureTarget->healWound(creature, CreatureAttribute::HEALTH, heal);
		int healedStrengthWound = creatureTarget->healWound(creature, CreatureAttribute::STRENGTH, heal);
		int healedConstitutionWound = creatureTarget->healWound(creature, CreatureAttribute::CONSTITUTION, heal);
		
		int healedActionWound = creatureTarget->healWound(creature, CreatureAttribute::ACTION, heal);
		int healedQuicknessWound = creatureTarget->healWound(creature, CreatureAttribute::QUICKNESS, heal);
		int healedStaminaWound = creatureTarget->healWound(creature, CreatureAttribute::STAMINA, heal);
		
		int healedMindWound = creatureTarget->healWound(creature, CreatureAttribute::MIND, heal);
		int healedFocusWound = creatureTarget->healWound(creature, CreatureAttribute::FOCUS, heal);
		int healedWillpowerWound = creatureTarget->healWound(creature, CreatureAttribute::WILLPOWER, heal);
		
		int healedHealth = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, heal);
		int healedAction = creatureTarget->healDamage(creature, CreatureAttribute::ACTION, heal);
		int healedMind = creatureTarget->healDamage(creature, CreatureAttribute::MIND, heal, true, false);		

		creatureTarget->addShockWounds(-1000);
		
		creatureTarget->removeStateBuff(CreatureState::STUNNED);

		creatureTarget->removeStateBuff(CreatureState::DIZZY);

		creatureTarget->removeStateBuff(CreatureState::BLINDED);

		creatureTarget->removeStateBuff(CreatureState::INTIMIDATED);
		
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();
		
		if (playerObject->getForcePower() <= 1000) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //You do not have enough force to do that.
			return GENERALERROR;
		}
		
		forceCost = MIN(((healedHealth + healedAction + healedMind + healedHealthWound + healedStrengthWound + healedConstitutionWound + healedActionWound + healedQuicknessWound + healedStaminaWound + healedMindWound + healedFocusWound + healedWillpowerWound + healDisease + healPoison + healBleeding) / 20), 1000);
		
		playerObject->setForcePower(playerObject->getForcePower() - forceCost); // Deduct force.	

		sendHealMessage(creature, creatureTarget, healedHealth, healedAction, healedMind);
		
		sendWoundMessage(creature, creatureTarget, healedHealthWound, healedActionWound,  healedMindWound, healedStrengthWound, healedConstitutionWound, healedQuicknessWound, healedStaminaWound, healedFocusWound, healedWillpowerWound);
		
		doAnimations(creature, creatureTarget);	
			
		return SUCCESS;
	}

};

#endif //TOTALHEALOTHERCOMMAND_H_
