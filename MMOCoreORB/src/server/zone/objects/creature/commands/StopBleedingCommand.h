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

#ifndef STOPBLEEDINGCOMMAND_H_
#define STOPBLEEDINGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "QueueCommand.h"

class StopBleedingCommand : public QueueCommand {
public:

	StopBleedingCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}
	
	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (creatureTarget == creature)
			creature->playEffect("clienteffect/pl_force_healing.cef", "");
		 else 
			creature->doAnimation("force_healing_1");
	}		
	
	void sendCureMessage(CreatureObject* object, CreatureObject* target) {
		if (!object->isPlayerCreature())
			return;

		if (!target->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>( target);
		StringBuffer msgTarget, msgPlayer;
			msgPlayer << creatureTarget->getFirstName() << " bleeding has slightly decreased.";
			msgTarget << creature->getFirstName() << " uses the Force to heal your bleeding.";

		if (creature != creatureTarget) 
			creature->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());
	}	
	
	bool checkTarget(CreatureObject* creature, CreatureObject* creatureTarget) {
		// TODO: Pet Check
		if (!creatureTarget->isPlayerCreature()) {
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
	
	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!creatureTarget->isBleeding()) {
			if (creature == creatureTarget)
				creature->sendSystemMessage("@healing_response:healing_response_78"); //You are not bleeding.
			else {
				StringIdChatParameter stringId("healing_response", "healing_response_80");
				stringId.setTT(creatureTarget->getObjectID());
				creature->sendSystemMessage(stringId); //%NT is not bleeding.
			}
			return false;
		}

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();
		
		if (playerObject->getForcePower() <= 75) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //You do not have enough force to do that.
			return false;
		}
		
		playerObject->setForcePower(playerObject->getForcePower() - 75); // Static amount.

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

		int range = 32;

		if (!creature->isInRange(creatureTarget, range))
			return TOOFAR;

		PlayerObject* targetGhost = creatureTarget->getPlayerObject();

		if (!canPerformSkill(creature, creatureTarget))
			return GENERALERROR;

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");
			return GENERALERROR;
		}


		creatureTarget->healDot(CreatureState::BLEEDING, 30);

		sendCureMessage(creature, creatureTarget);
		
		doAnimations(creature, creatureTarget);	
			
		return SUCCESS;
	}

};

#endif //STOPBLEEDINGCOMMAND_H_
