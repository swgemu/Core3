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

#ifndef FIRSTAIDCOMMAND_H_
#define FIRSTAIDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class FirstAidCommand : public QueueCommand {
	float mindCost;
	float range;
public:

	FirstAidCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		
		mindCost = 0;
		range = 6;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		creatureTarget->playEffect("clienteffect/healing_healdamage.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}
	
	void sendCureMessage(CreatureObject* object, CreatureObject* target) {
		if (!object->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>( target);
		
		if (creatureTarget != creature) {
			StringBuffer msgPlayer;
			if (creatureTarget->isPlayerCreature()) {
				StringBuffer msgTarget;
				msgTarget << creature->getFirstName() << " applies first aid to you.";
				creatureTarget->sendSystemMessage(msgTarget.toString());

				msgPlayer << "You apply first aid to " << creatureTarget->getFirstName() << ".";
				creature->sendSystemMessage(msgPlayer.toString());
			} else {
				msgPlayer << "You apply first aid to " << creatureTarget->getDisplayedName() << ".";
				creature->sendSystemMessage(msgPlayer.toString());
			}
		} else {
			creature->sendSystemMessage("@healing_response:first_aid_self"); //You apply first aid to yourself.
		}		
	}				
		
	
	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!creatureTarget->isBleeding()) {
			if (creature == creatureTarget)
				creature->sendSystemMessage("@healing_response:healing_response_78"); //You are not bleeding.
			else if (creatureTarget->isPlayerCreature()) {
				StringIdChatParameter stringId("healing_response", "healing_response_80"); //%NT is not bleeding.
				stringId.setTT(creatureTarget->getObjectID());
				creature->sendSystemMessage(stringId);
			} else {
				StringBuffer message;
				message << creatureTarget->getDisplayedName() << " is not bleeding.";
				creature->sendSystemMessage(message.toString());
			}
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

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (!object->isCreatureObject()) {
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());

				if (tangibleObject != NULL && tangibleObject->isAttackableBy(creature)) {
					object = creature;
				} else
					creature->sendSystemMessage("@healing_response:healing_response_79"); //Target must be a player or a creature pet in order to apply first aid.					
					return GENERALERROR;
			}
		} else
			object = creature;

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		if ((creatureTarget->isAiAgent() && !creatureTarget->isPet()) || creatureTarget->isDroidObject() || creatureTarget->isDead() || creatureTarget->isRidingMount() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;

		if (!creatureTarget->isInRange(creature, range + creatureTarget->getTemplateRadius() + creature->getTemplateRadius()))
			return TOOFAR;

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help"); //It would be unwise to help such a patient.
			return GENERALERROR;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return GENERALERROR;
		}

		if (!canPerformSkill(creature, creatureTarget))
			return GENERALERROR;		
					
			
		uint32 skillMod = creature->getSkillMod("healing_injury_treatment");
			
		creatureTarget->healDot(CreatureState::BLEEDING, skillMod*3);
			
		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);
		
		sendCureMessage(creature, creatureTarget);
 
		doAnimations(creature, creatureTarget);		

		return SUCCESS;
	}

};

#endif //FIRSTAIDCOMMAND_H_
