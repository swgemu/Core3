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
		defaultTime = 3;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		creatureTarget->playEffect("clienteffect/healing_healdamage.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL && !object->isCreatureObject()) {
			return INVALIDTARGET;
		} else if (object == NULL)
			object = creature;

		CreatureObject* creatureTarget = (CreatureObject*) object.get();

		Locker clocker(creatureTarget, creature);

		if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;

		if (!creatureTarget->isInRange(creature, range))
			return TOOFAR;

		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot apply First Aid while prone.");
			return GENERALERROR;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot apply First Aid while Meditating.");
			return GENERALERROR;
		}

		if (creature->isRidingCreature()) {
			creature->sendSystemMessage("You cannot do that while Riding a Creature.");
			return GENERALERROR;
		}

		if (creature->isMounted()) {
			creature->sendSystemMessage("You cannot do that while Driving a Vehicle.");
			return GENERALERROR;
		}

		/*if (creatureTarget->isPlayer() && creature->isPlayer()) {
			Player * pt = (Player *) creatureTarget;
			Player * p = (Player *) creature;

			if (pt->getFaction() != p->getFaction() && !pt->isOnLeave()) {
				creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
				return GENERALERROR;
			}

			if ((pt->isOvert() && !p->isOvert()) || (pt->isCovert() && p->isOnLeave())) {
				creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
				return GENERALERROR;
			}
		}*/

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
			return GENERALERROR;
		}


		if (creatureTarget->isBleeding()) {

			if (creatureTarget != creature) {
				if (creatureTarget->isPlayerCreature()) {
					StringBuffer message;
					message << "You apply first aid to " << ((PlayerCreature*)creatureTarget)->getFirstName() << ".";
					creature->sendSystemMessage(message.toString());
				}
			} else {
				creature->sendSystemMessage("healing_response","first_aid_self"); //You apply first aid to yourself.
			}

			creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);

			doAnimations(creature, creatureTarget);

			uint32 skillMod = creature->getSkillMod("healing_injury_treatment");
			creatureTarget->healDot(CreatureState::BLEEDING, skillMod);
			/*if (creatureTarget->healDot(CreatureState::BLEEDING,skillMod))
							creatureTarget->sendSystemMessage("Bleed stop");
						else
							creatureTarget->sendSystemMessage("Bleed reduced");
			 */
		} else {
			creature->error("Failed clearing bleeding state on player for unknown reason.");
		}

		if (creatureTarget != creature) {
			StringIdChatParameter stringId("healing_response", "healing_response_80");
			stringId.setTT(creatureTarget->getObjectID());
		} else {
			creature->sendSystemMessage("healing_response", "healing_response_78"); //You are not bleeding.
		}


		return SUCCESS;
	}

};

#endif //FIRSTAIDCOMMAND_H_
