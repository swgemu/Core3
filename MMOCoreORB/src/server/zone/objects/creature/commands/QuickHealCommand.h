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

#ifndef QUICKHEALCOMMAND_H_
#define QUICKHEALCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "server/zone/objects/tangible/pharmaceutical/RangedStimPack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/InjuryTreatmentTask.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/packets/object/CombatAction.h"

class QuickHealCommand : public QueueCommand {
	int mindCost;
	int mindWoundCost;

	int healthHealed;
	int actionHealed;
	int mindHealed;

	float speed;
	float range;
public:

	QuickHealCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

		healthHealed = 0;
		actionHealed = 0;
		mindHealed = 0;

		mindCost = 800;
		mindWoundCost = 10;

		defaultTime = 3.5;
		range = 6;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		creatureTarget->playEffect("clienteffect/healing_healdamage.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	void sendHealMessage(CreatureObject* creature, CreatureObject* creatureTarget, int healthDamage, int actionDamage) {
		if (!creature->isPlayerCreature() || !creatureTarget->isPlayerCreature())
			return;

		CreatureObject* player = (CreatureObject*) creature;
		CreatureObject* playerTarget = (CreatureObject*) creatureTarget;

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (healthDamage > 0 && actionDamage > 0) {
			msgBody << healthDamage << " health and " << actionDamage << " action";
		} else if (healthDamage > 0) {
			msgBody << healthDamage << " health";
		} else if (actionDamage > 0) {
			msgBody << actionDamage << " action";
		} else {
			return; //No damage to heal.
		}

		msgTail << " damage.";

		if (creature == creatureTarget) {
			msgPlayer << "You heal yourself for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
		} else {
			msgPlayer << "You heal " << playerTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString();
			msgTarget << player->getFirstName() << " heals you for " << msgBody.toString() << msgTail.toString();

			player->sendSystemMessage(msgPlayer.toString());
			playerTarget->sendSystemMessage(msgTarget.toString());
		}
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL && !object->isCreatureObject()) {
			return INVALIDTARGET;
		} else if (object == NULL)
			object = creature;

		CreatureObject* creatureTarget = (CreatureObject*) object.get();

		Locker clocker(creatureTarget, creature);

		if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;

		/*if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			creature->sendSystemMessage("healing_response", "healing_response_99"); //Target must be a player or a creature pet in order to quickheal .
			return GENERALERROR;
		}

		CreatureObject* creatureTarget = (CreatureObject*) target;

		if (creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted())
			creatureTarget = creature;	//If our target is dead, riding a creature, or mounted, then we make ourself target.
		*/

		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot Quick Heal while prone.");
			return GENERALERROR;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot Quick Heal while meditating.");
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

		if (creature->getHAM(CreatureAttribute::MIND) < abs(mindCost)) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
			return GENERALERROR;
		}


		if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH) && !creatureTarget->hasDamage(CreatureAttribute::ACTION)) {
			if (creatureTarget == creature)
				creature->sendSystemMessage("healing_response", "healing_response_61"); //You have no damage to heal.
			else {
				StringIdChatParameter stringId("healing_response", "healing_response_63");
				stringId.setTT(creatureTarget->getObjectID());
				//creature->sendSystemMessage("healing_response", "healing_response_63", creatureTarget->getObjectID()); //%NT has no damage to heal.
			}

			return GENERALERROR;
		}

		int healPower = (int) round(150 + System::random(600));

		int healedHealth = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, healPower);
		int healedAction = creatureTarget->healDamage(creature, CreatureAttribute::ACTION, healPower);

		if (creature->isPlayerCreature() && creatureTarget->isPlayerCreature()) {
			PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
			playerManager->sendBattleFatigueMessage((CreatureObject*)creature, (CreatureObject*)creatureTarget);
		}

		sendHealMessage(creature, creatureTarget, healedHealth, healedAction);

		/*creature->changeMindBar(-mindCost);
		creature->changeFocusWoundsBar(mindWoundCost);
		creature->changeWillpowerWoundsBar(mindWoundCost);
		creature->changeShockWounds(2);*/

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);
		creature->addWounds(CreatureAttribute::FOCUS, mindWoundCost, true);
		creature->addWounds(CreatureAttribute::WILLPOWER, mindWoundCost, true);
		//creature->changeWillpowerWoundsBar(mindWoundCost);
		creature->addShockWounds(2);

		doAnimations(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif //QUICKHEALCOMMAND_H_
