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

#ifndef FORCECUREDISEASECOMMAND_H_
#define FORCECUREDISEASECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceCureDiseaseCommand : public QueueCommand {
public:

	ForceCureDiseaseCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!creatureTarget->isPoisoned()) {
			if (creature == creatureTarget)
				creature->sendSystemMessage("@healing_response:healing_response_82"); //You are not poisoned.
			else {
				StringIdChatParameter stringId("healing_response", "healing_response_84");
				stringId.setTT(creatureTarget->getObjectID());
				creature->sendSystemMessage(stringId); //%NT is not poisoned.
			}
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

		if (object != NULL && !object->isCreatureObject()) {
			return INVALIDTARGET;
		} else if (object == NULL)
			object = creature;

		CreatureObject* targetCreature = cast<CreatureObject*>( object.get());

		Locker clocker(targetCreature, creature);

		if (targetCreature->isAiAgent() || targetCreature->isDead() || targetCreature->isRidingCreature() || targetCreature->isMounted() || targetCreature->isAttackableBy(creature))
			targetCreature = creature;

		int range = 32;

		if (!creature->isInRange(targetCreature, range))
			return TOOFAR;

		PlayerObject* targetGhost = targetCreature->getPlayerObject();

		if (targetGhost != NULL && targetCreature->getFaction() != creature->getFaction() && !(targetGhost->getFactionStatus() & FactionStatus::ONLEAVE)) {
			return GENERALERROR;
		}

		if (!canPerformSkill(creature, targetCreature))
			return GENERALERROR;

			targetCreature->healDot(CreatureState::DISEASED, 30);


			ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

			playerObject->setForcePower(playerObject->getForcePower() - 65);

		if (targetCreature == creature){
			creature->playEffect("clienteffect/pl_force_heal_self.cef", "");
		} else {
			creature->doAnimation("force_healing_1");
		}

		return SUCCESS;
	}

	float getCommandDuration(CreatureObject* object) {
		return defaultTime * 3.0;
	}

};

#endif //FORCECUREDISEASECOMMAND_H_
