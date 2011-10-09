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

#ifndef HEALSTATECOMMAND_H_
#define HEALSTATECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/StatePack.h"
#include "server/zone/objects/tangible/pharmaceutical/RangedStimPack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/InjuryTreatmentTask.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/managers/collision/CollisionManager.h"

class HealStateCommand : public QueueCommand {
	float mindCost;
	float range;
public:

	HealStateCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		mindCost = 20;
		range = 6;
	}

	void deactivateStateTreatment(CreatureObject* creature) {
		float modSkill = (float)creature->getSkillMod("healing_injury_speed");
		int delay = (int)round((modSkill * -(1.0f / 8.0f)) + 21.0f);

		//Force the delay to be at least 3 seconds.
		delay = (delay < 3) ? 3 : delay;

		StringIdChatParameter message("healing_response", "healing_response_59");
		Reference<InjuryTreatmentTask*> task = new InjuryTreatmentTask(creature, message, "stateTreatment");
		creature->addPendingTask("stateTreatment", task, delay * 1000);
	}

	void awardXp(CreatureObject* creature, String type, int power) {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		int amount = (int)round((float)power * 1.f);

		if (amount <= 0)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(player, type, amount, true);
	}

	void sendStateMessage(CreatureObject* creature, CreatureObject* creatureTarget, uint64 state) {
		if (!creature->isPlayerCreature())
			return;

		if (!creatureTarget->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);
		CreatureObject* playerTarget = cast<CreatureObject*>( creatureTarget);
		StringBuffer msgPlayer, msgTarget;

		String stateName = CreatureState::instance()->getName(state, true);

		if (player == playerTarget) {
			msgTarget << "You remove the " << stateName << " state from yourself.";
		} else {
			String creatureName = player->getFirstName();
			String creatureTargetName = playerTarget->getFirstName();

			msgPlayer << "You remove the " << stateName << " state from " << creatureTargetName << ".";
			msgTarget << creatureName << " removes the " << stateName << " from you.";
		}


		playerTarget->sendSystemMessage(msgTarget.toString());

		if (player != playerTarget)
			player->sendSystemMessage(msgPlayer.toString());
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		creatureTarget->playEffect("clienteffect/healing_healdamage.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, StatePack* statePack) {
		if (!creature->canTreatStates()) {
			creature->sendSystemMessage("healing_response", "healing_must_wait"); //You must wait before you can do that.
			return false;
		}

		if (statePack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
			return false;
		}

		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot Heal States while prone.");
			return false;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot Heal States while Meditating.");
			return false;
		}

		if (creature->isRidingCreature()) {
			creature->sendSystemMessage("You cannot do that while Riding a Creature.");
			return false;
		}

		if (creature->isMounted()) {
			creature->sendSystemMessage("You cannot do that while Driving a Vehicle.");
			return false;
		}

		/*if (creatureTarget->isPlayer() && creature->isPlayer()) {
			Player * pt = cast<Player *>( creatureTarget);
			Player * p = cast<Player *>( creature);

			if (pt->getFaction() != p->getFaction() && !pt->isOnLeave()) {
				creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
				return false;
			}

			if ((pt->isOvert() && !p->isOvert()) || (pt->isCovert() && p->isOnLeave())) {
				creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
				return false;
			}
		}*/

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		return true;
	}

	StatePack* findStatePack(CreatureObject* creature, uint64 state) {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				SceneObject* object = inventory->getContainerObject(i);

				if (!object->isTangibleObject())
					continue;

				TangibleObject* item = cast<TangibleObject*>( object);

				if (item->isPharmaceuticalObject()) {
					PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>( item);

					if (pharma->isStatePack()) {
						StatePack* statePack = cast<StatePack*>( pharma);

						if (statePack->getMedicineUseRequired() <= medicineUse && statePack->getState() == state)
							return statePack;
					}
				}
			}
		}

		return NULL;
	}

	void parseModifier(const String& modifier, uint64& state, uint64& objectId) {
		if (!modifier.isEmpty()) {
			StringTokenizer tokenizer(modifier);
			tokenizer.setDelimeter("|");

			String stateName;

			tokenizer.getStringToken(stateName);

			state = CreatureState::instance()->getState(stateName);

			if (tokenizer.hasMoreTokens())
				objectId = tokenizer.getLongToken();
		} else {
			state = CreatureState::INVALID;
			objectId = 0;
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

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;

		uint64 state = CreatureState::INVALID;
		uint64 objectId = 0;

		parseModifier(arguments.toString(), state, objectId);

		if (state == CreatureState::INVALID) {
			creature->sendSystemMessage("healing_response", "healing_response_70"); //You must specify a valid state type.
			return GENERALERROR;
		}

		SceneObject* inventory = creature->getSlottedObject("inventory");

		ManagedReference<StatePack*> statePack = NULL;

		if (inventory != NULL) {
			statePack = dynamic_cast<StatePack*>(inventory->getContainerObject(objectId));
		}

		if (statePack == NULL)
			statePack = findStatePack(creature, state);

		if (!canPerformSkill(creature, creatureTarget, statePack))
			return GENERALERROR;

		if (!creatureTarget->isInRange(creature, range))
			return TOOFAR;

		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			creature->sendSystemMessage("@container_error_message:container18");
			return GENERALERROR;
		}


		if (!creatureTarget->clearState(state)) {
			if (creature == creatureTarget)
				creature->sendSystemMessage("healing_response", "healing_response_72"); //You have no state of that type to heal.
			else {
				StringIdChatParameter msg("healing_response", "healing_response_74");
				msg.setTT(creatureTarget->getObjectID());
				creature->sendSystemMessage(msg); //%NT has no state of that type to heal.
			}

			return GENERALERROR;
		}

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);

		sendStateMessage(creature, creatureTarget, state);

		deactivateStateTreatment(creature);

		if (statePack != NULL)
			statePack->decreaseUseCount();

		if (creatureTarget != creature)
			awardXp(creature, "medical", 50); //No experience for healing yourself.

		doAnimations(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif //HEALSTATECOMMAND_H_
