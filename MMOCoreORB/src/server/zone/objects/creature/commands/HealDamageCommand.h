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

#ifndef HEALDAMAGECOMMAND_H_
#define HEALDAMAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "server/zone/objects/tangible/pharmaceutical/RangedStimPack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/InjuryTreatmentTask.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/managers/collision/CollisionManager.h"

class HealDamageCommand : public QueueCommand {
	float range;
	float mindCost;

public:
	HealDamageCommand(const String& name, ZoneProcessServer* server)
	: QueueCommand(name, server) {

		range = 5;
		mindCost = 50;
		//defaultTime = 0;
	}

	void deactivateInjuryTreatment(CreatureObject* creature, bool isRangedStim) {
		float modSkill = 0.0f;

		if (isRangedStim)
			modSkill = (float)creature->getSkillMod("healing_range_speed");
		else
			modSkill = (float)creature->getSkillMod("healing_injury_speed");

		int delay = (int)round((modSkill * -(1.0f / 8.0f)) + 21.0f);

		if (creature->hasBuff(BuffCRC::FOOD_HEAL_RECOVERY)) {
			DelayedBuff* buff = cast<DelayedBuff*>( creature->getBuff(BuffCRC::FOOD_HEAL_RECOVERY));

			if (buff != NULL) {
				float percent = buff->getSkillModifierValue("heal_recovery");

				delay = round(delay * (100.0f - percent) / 100.0f);
			}
		}

		//Force the delay to be at least 3 seconds.
		delay = (delay < 3) ? 3 : delay;

		StringIdChatParameter message("healing_response", "healing_response_58");
		Reference<InjuryTreatmentTask*> task = new InjuryTreatmentTask(creature, message, "injuryTreatment");
		creature->addPendingTask("injuryTreatment", task, delay * 1000);
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		creatureTarget->playEffect("clienteffect/healing_healdamage.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	void doAnimationsRange(CreatureObject* creature, CreatureObject* creatureTarget, int oid, float range) {
		String crc;

		if (range < 10.0f) {
			crc = "throw_grenade_near_healing";
		}
		else if (10.0f <= range && range < 20.f) {
			crc = "throw_grenade_medium_healing";
		}
		else {
			crc = "throw_grenade_far_healing";
		}

		CombatAction* action = new CombatAction(creature, creatureTarget,  crc.hashCode(), 1, 0L);
		creature->broadcastMessage(action, true);
	}

	StimPack* findStimPack(CreatureObject* creature) {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		if (inventory == NULL)
			return NULL;

		int medicineUse = creature->getSkillMod("healing_ability");
		int combatMedicineUse = creature->getSkillMod("combat_healing_ability");

		bool melee = range <= 5.0f;

		for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
			SceneObject* item = inventory->getContainerObject(i);

			if (!item->isTangibleObject())
				continue;

			TangibleObject* tano = cast<TangibleObject*>( item);

			if (tano->isPharmaceuticalObject()) {
				PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>( tano);

				if (melee && pharma->isStimPack()) {
					StimPack* stimPack = cast<StimPack*>(pharma);

					if (stimPack->getMedicineUseRequired() <= medicineUse)
						return stimPack;
				}

				if (pharma->isRangedStimPack()) {
					RangedStimPack* stimPack = cast<RangedStimPack*>(pharma);

					if (stimPack->getMedicineUseRequired() <= combatMedicineUse && stimPack->getRange(creature))
						return stimPack;
				}
			}
		}

		return NULL;
	}

	bool checkTarget(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH) && !creatureTarget->hasDamage(CreatureAttribute::ACTION)) {
			/*if (creatureTarget == creature) {
				creature->sendSystemMessage("@healing_response:healing_response_61"); //You have no damage to heal.
			} else {
				StringIdChatParameter stringId("healing_response", "healing_response_63");
				stringId.setTO(creatureTarget->getObjectID());
				//creature->sendSystemMessage("healing_response", "healing_response_63", creatureTarget->getObjectID()); //%NT has no damage to heal.
				creature->sendSystemMessage(stringId);
			}*/
			return false;
		}

		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			return false;
		}

		if (creatureTarget->isDead())
			return false;

		return true;
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, StimPack* stimPack) {
		if (!creature->canTreatInjuries()) {
			creature->sendSystemMessage("@healing_response:healing_must_wait"); //You must wait before you can do that.
			return false;
		}

		if (stimPack == NULL) {
			creature->sendSystemMessage("@healing_response:healing_response_60"); //No valid medicine found.
			return false;
		}

		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot do that while prone.");
			return false;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot do that while meditating.");
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

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");
			return GENERALERROR;
		}

		if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH) && !creatureTarget->hasDamage(CreatureAttribute::ACTION)) {
			if (creatureTarget == creature) {
				creature->sendSystemMessage("@healing_response:healing_response_61"); //You have no damage to heal.
			} else {
				StringIdChatParameter stringId("healing_response", "healing_response_63");
				stringId.setTT(creatureTarget->getObjectID());
				//creature->sendSystemMessage("healing_response", "healing_response_63", creatureTarget->getObjectID()); //%NT has no damage to heal.
				creature->sendSystemMessage(stringId);
			}

			return false;
		}

		if (stimPack->isRangedStimPack()) {
			RangedStimPack* rangedStimPack = cast<RangedStimPack*>(stimPack);
			int combatMedicineUse = creature->getSkillMod("combat_healing_ability");

			if (rangedStimPack->getMedicineUseRequired() > combatMedicineUse || !rangedStimPack->getRange(creature)) {
				creature->sendSystemMessage("@error_message:insufficient_skill"); //You lack the skill to use this item.
				return false;

			}
		}

		return true;
	}

	void sendHealMessage(CreatureObject* creature, CreatureObject* creatureTarget, uint32 healthDamage, uint32 actionDamage) {
		if (!creature->isPlayerCreature() || !creatureTarget->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);
		CreatureObject* playerTarget = cast<CreatureObject*>(  creatureTarget);

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
			creature->sendSystemMessage(msgPlayer.toString());
		} else if (creatureTarget->isPlayerCreature()) {
			msgPlayer << "You heal " << playerTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());

			msgTarget << player->getFirstName() << " heals you for " << msgBody.toString() << msgTail.toString();
			playerTarget->sendSystemMessage(msgTarget.toString());
		} else {
			//TODO: Pet Message
		}
	}

	void awardXp(CreatureObject* creature, const String& type, int power) {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		int amount = (int)round((float)power * 0.25f);

		if (amount <= 0)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(player, type, amount, true);
	}

	void doAreaMedicActionTarget(CreatureObject* creature, CreatureObject* targetCreature, PharmaceuticalObject* pharma) {
		if (pharma->isRangedStimPack()) {
			RangedStimPack* rangeStim = cast<RangedStimPack*>( pharma);

			if (pharma == NULL)
				return;

			uint32 stimPower = rangeStim->calculatePower(creature, targetCreature);

			uint32 healthHealed = targetCreature->healDamage(creature, CreatureAttribute::HEALTH, stimPower);
			uint32 actionHealed = targetCreature->healDamage(creature, CreatureAttribute::ACTION, stimPower);

			if (creature->isPlayerCreature() && targetCreature->isPlayerCreature()) {
				PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
				playerManager->sendBattleFatigueMessage(creature, targetCreature);
			}

			sendHealMessage(creature, targetCreature, healthHealed, actionHealed);

			if (targetCreature != creature)
				awardXp(creature, "medical", (healthHealed + actionHealed)); //No experience for healing yourself.
		}
	}

	void handleArea(CreatureObject* creature, CreatureObject* areaCenter, StimPack* pharma,
			float range) {

		Zone* zone = creature->getZone();

		if (zone == NULL)
			return;

		try {
			zone->rlock();

			SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = areaCenter->getCloseObjects();

			for (int i = 0; i < closeObjects->size(); i++) {
				SceneObject* object = cast<SceneObject*>( closeObjects->get(i).get());

				if (!object->isPlayerCreature())
					continue;

				if (object == areaCenter || object == creature)
					continue;

				if (!areaCenter->isInRange(object, range))
					continue;

				CreatureObject* creatureTarget = cast<CreatureObject*>( object);

				if (creatureTarget->isAttackableBy(creature))
					continue;

				/*if (creatureTarget->isDead() || creatureTarget->isIncapacitated())
					continue;*/

				zone->runlock();

				try {

					Locker crossLocker(creatureTarget, creature);

					if (checkTarget(creature, creatureTarget)) {
						doAreaMedicActionTarget(creature, creatureTarget, pharma);
					}

				} catch (Exception& e) {

				}

				zone->rlock();

			}

			zone->runlock();
		} catch (Exception& e) {
			zone->runlock();
		}
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

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

		CreatureObject* targetCreature = cast<CreatureObject*>( object.get());

		Locker clocker(targetCreature, creature);

		if (targetCreature->isAiAgent() || targetCreature->isDead() || targetCreature->isRidingCreature() || targetCreature->isMounted() || targetCreature->isAttackableBy(creature))
			targetCreature = creature;

		uint64 pharmaceuticalObjectID = 0;

		try {
			if (!arguments.isEmpty())
				pharmaceuticalObjectID = UnsignedLong::valueOf(arguments.toString());
		} catch (Exception& e) {

		}

		ManagedReference<StimPack*> stimPack;

		if (pharmaceuticalObjectID == 0) {
			stimPack = findStimPack(creature);
		} else {
			SceneObject* inventory = creature->getSlottedObject("inventory");

			if (inventory != NULL) {
				stimPack = dynamic_cast<StimPack*>(inventory->getContainerObject(pharmaceuticalObjectID));
			}
		}

		if (!canPerformSkill(creature, targetCreature, stimPack))
			return GENERALERROR;

		float rangeToCheck = 7;

		if (stimPack->isRangedStimPack())
			rangeToCheck = (cast<RangedStimPack*>(stimPack.get()))->getRange();
		/*} else {

		}*/

		if (!creature->isInRange(targetCreature, rangeToCheck))
			return TOOFAR;

		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != targetCreature && !CollisionManager::checkLineOfSight(creature, targetCreature)) {
			creature->sendSystemMessage("@container_error_message:container18");
			return GENERALERROR;
		}

		uint32 stimPower = stimPack->calculatePower(creature, targetCreature);

		uint32 healthHealed = targetCreature->healDamage(creature, CreatureAttribute::HEALTH, stimPower);
		uint32 actionHealed = targetCreature->healDamage(creature, CreatureAttribute::ACTION, stimPower, true, false);

		if (creature->isPlayerCreature() && targetCreature->isPlayerCreature()) {
			playerManager->sendBattleFatigueMessage(creature, targetCreature);
		}

		sendHealMessage(creature, targetCreature, healthHealed, actionHealed);

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);
		stimPack->decreaseUseCount();

		if (targetCreature != creature)
			awardXp(creature, "medical", (healthHealed + actionHealed)); //No experience for healing yourself.

		if (targetCreature != creature)
			clocker.release();

		if (stimPack->isArea()) {
			handleArea(creature, targetCreature, stimPack, stimPack->getArea());
		}

		if (stimPack->isRangedStimPack()) {
			doAnimationsRange(creature, targetCreature, stimPack->getObjectID(), creature->getDistanceTo(targetCreature));
		} else
			doAnimations(creature, targetCreature);

		deactivateInjuryTreatment(creature, stimPack->isRangedStimPack());

		return SUCCESS;
	}

};

#endif //HEALDAMAGECOMMAND_H_
