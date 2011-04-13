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

#ifndef HEALMINDCOMMAND_H_
#define HEALMINDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/collision/CollisionManager.h"

class HealMindCommand : public QueueCommand {
	float mindCost;
	float mindWoundCost;
	float range;
public:

	HealMindCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		mindCost = 250;
		mindWoundCost = 250;
		defaultTime = 6;
		range = 5;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		creatureTarget->playEffect("clienteffect/healing_healenhance.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	void sendHealMessage(CreatureObject* creature, CreatureObject* creatureTarget, int mindDamage) {
		if (!creature->isPlayerCreature() || !creatureTarget->isPlayerCreature())
			return;

		PlayerCreature* player = (PlayerCreature*) creature;
		PlayerCreature* playerTarget = (PlayerCreature*) creatureTarget;

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (mindDamage > 0) {
			msgBody << mindDamage << " mind";
		} else {
			return; //No damage to heal.
		}

		msgTail << " damage.";

		if (creatureTarget) {
			msgPlayer << "You heal " << playerTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString();
			msgTarget << player->getFirstName() << " heals you for " << msgBody.toString() << msgTail.toString();

			player->sendSystemMessage(msgPlayer.toString());
			playerTarget->sendSystemMessage(msgTarget.toString());
		}
	}

	int calculateWound(int wound, int poolWounds, int poolMax) {
		int maxWound = poolMax - poolWounds - 1;
		return (MAX(0,MIN(maxWound,wound)));
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL && !object->isCreatureObject()) {
			creature->sendSystemMessage("healing", "heal_mind_invalid_target");
			return INVALIDTARGET;
		} else if (object == NULL)
			object = creature;

		CreatureObject* creatureTarget = (CreatureObject*) object.get();

		Locker clocker(creatureTarget, creature);

		/*if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;*/

		PlayerCreature* player = (PlayerCreature*) creature;

		if (creatureTarget == creature) {
			creature->sendSystemMessage("healing", "no_heal_mind_self");
			return GENERALERROR;
		}

		if (creatureTarget->isDead())
			return GENERALERROR;

		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot Heal Mind while prone.");
			return GENERALERROR;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot Heal Mind while Meditating.");
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

		if (creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted()) {
			creature->sendSystemMessage("You cannot Heal the Mind of your Target in their current state.");
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

		if (creatureTarget->getHAM(CreatureAttribute::MIND) == 0) {
			if (creatureTarget) {
				StringIdChatParameter stringId("healing", "no_mind_to_heal_target");
				stringId.setTT(creatureTarget->getObjectID());
				creature->sendSystemMessage(stringId); //%NT has no mind to heal.
			}

			return GENERALERROR;
		}

		if (!creatureTarget->isInRange(creature, range))
			return TOOFAR;

		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			creature->sendSystemMessage("@container_error_message:container18");
			return GENERALERROR;
		}

		float modSkill = (float) creature->getSkillMod("combat_medic_effectiveness");
		int healPower = (int) round((100.0f + modSkill) / 100.0f * creatureTarget->getMaxHAM(CreatureAttribute::MIND) / 2);

		int healedMind = creatureTarget->healDamage(creature, CreatureAttribute::MIND, healPower);

		if (creature->isPlayerCreature() && creatureTarget->isPlayerCreature()) {
			playerManager->sendBattleFatigueMessage((PlayerCreature*)creature, (PlayerCreature*)creatureTarget);
		}

		sendHealMessage(creature, creatureTarget, healedMind);
		int mindWound = (int) round(500.0f * healedMind / healPower) ;

		creature->addWounds(CreatureAttribute::MIND, mindWound);
		creature->addWounds(CreatureAttribute::FOCUS, mindWound);
		creature->addWounds(CreatureAttribute::WILLPOWER, mindWound);
		/*creature->changeMindWoundsBar(calculateWound(mindWound,creature->getMindWounds(),creature->getBaseMind()));
		creature->changeFocusWoundsBar(calculateWound(mindWound,creature->getFocusWounds(),creature->getBaseFocus()));
		creature->changeWillpowerWoundsBar(calculateWound(mindWound,creature->getWillpowerWounds(),creature->getBaseWillpower()));*/

		creature->addShockWounds(25);

		doAnimations(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif //HEALMINDCOMMAND_H_
