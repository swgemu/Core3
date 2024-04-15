/*
 * ThrowTrapTask.h
 *
 *	Created on: Nov 20, 2010
 *	Author: da
 *
 *	Refactored on: 2024-04-14
 *	By: Hakry
 */

#ifndef THROWTRAPTASK_H_
#define THROWTRAPTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "templates/tangible/TrapTemplate.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class ThrowTrapTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> weakAttacker;
	ManagedWeakReference<CreatureObject*> weakTarget;
	ManagedWeakReference<TangibleObject*> weakTrap;

public:
	ThrowTrapTask(CreatureObject* attacker, CreatureObject* target, TangibleObject* trap) : Task(2500) {
		weakAttacker = attacker;
		weakTarget = target;
		weakTrap = trap;

		setLoggingName("ThrowTrapTask");
	}

	virtual ~ThrowTrapTask() {
	}

	void run() {
		auto attacker = weakAttacker.get();
		auto target = weakTarget.get();

		if (attacker == nullptr || target == nullptr) {
			return;
		}

		auto trap = weakTrap.get();

		if (trap == nullptr) {
			return;
		}

		// Lock the attacker
		Locker lock(attacker);

		// Remove any trap tasks from attacker
		attacker->removePendingTask("throwtrap");

		auto zoneServer = attacker->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		auto trapData = cast<TrapTemplate*>(TemplateManager::instance()->getTemplate(trap->getServerObjectCRC()));

		if (trapData == nullptr) {
			error() << "Trap Template has a nullptr";
			return;
		}

		auto objectController = zoneServer->getObjectController();

		if (objectController == nullptr) {
			return;
		}

		const auto trapCommand = cast<const CombatQueueCommand*>(objectController->getQueueCommand(STRING_HASHCODE("throwtrap")));

		if (trapCommand == nullptr) {
			return;
		}

		// Cross lock the target to the attacker
		Locker targetLock(target, attacker);

		// Use combat manager to handle the combat action
		int combatResult = CombatManager::instance()->doCombatAction(attacker, attacker->getWeapon(), target, trapCommand);

		if (combatResult == CombatManager::MISS) {
			info(true) << "ThrowTrapCommand - trap missed with doCombatAction";
		}

		SortedVector<ManagedReference<TreeEntry*> > closeObjects;

		// Find nearby objects to our target using the targets COV
		CloseObjectsVector* closeObjectsVector = (CloseObjectsVector*) target->getCloseObjects();

		if (closeObjectsVector != nullptr) {
			closeObjectsVector->safeCopyReceiversTo(closeObjects, CloseObjectsVector::CREOTYPE);
		}

		// Release the lock on the target
		targetLock.release();

		// Trap Data from template
		uint64 state = trapData->getState();
		const auto defenseString = trapData->getDefenseMod();
		const auto animationString = trapData->getAnimation();
		uint32 crc = animationString.hashCode();
		bool isAoeTrap = trapData->isAoeTrap();

		int debuffDuration = trapData->getDuration();
		short hamPool = trapData->getPoolToDamage();
		const auto skillMods = trapData->getSkillMods();
		float maxDamage = trapData->getMaxDamage();
		float minDamage = trapData->getMinDamage();

		// Trap Messages
		const auto successMsg = trapData->getSuccessMessage();
		const auto failMsg = trapData->getFailMessage();
		const auto startSpam = trapData->getStartSpam();
		const auto stopSpam = trapData->getStopSpam();

		// Trapping skill mod
		int trappingSkill = attacker->getSkillMod("trapping");
		uint64 targetID = target->getObjectID();

		StringIdChatParameter message;
		int totalXP = 0;

		// Iterate the nearby elligible targets
		for (int i = 0; i < closeObjects.size(); ++i) {
			auto objectCreature = closeObjects.get(i).castTo<CreatureObject*>();

			if (objectCreature == nullptr || !objectCreature->isCreature() || objectCreature->isPet()) {
				continue;
			}

			if (!isAoeTrap && objectCreature->getObjectID() != targetID) {
				continue;
			}

			auto targetAgent = objectCreature->asAiAgent();

			if (targetAgent == nullptr) {
				continue;
			}

			Locker tarLock(targetAgent, attacker);

			if (!targetAgent->isInRange(target, 5.f)) {
				continue;
			}

			if (!CombatManager::instance()->startCombat(attacker, targetAgent, false, false)) {
				continue;
			}

			int targetDefense = targetAgent->getSkillMod(trapData->getDefenseMod());

			int attackRoll = System::random(199) + 1;
			int defendRoll = System::random(199) + 1;

			float hitChance = CombatManager::instance()->hitChanceEquation(trappingSkill + attackRoll, targetDefense + defendRoll);

			if (hitChance > 100) {
				hitChance = 100.0;
			} else if (hitChance < 0) {
				hitChance = 0;
			}

			int roll = System::random(100);
			bool hit = roll < hitChance && (state == 0 || (state != 0 && !targetAgent->hasState(state)));

			auto action = new CombatAction(attacker, targetAgent, crc, hit, 0L);

			if (action != nullptr) {
				attacker->broadcastMessage(action, true);
			}

			if (hit) {
				message.setStringId("trap/trap", trapData->getSuccessMessage());

				ManagedReference<Buff*> buff = new Buff(targetAgent, crc, trapData->getDuration(), BuffType::STATE);

				if (buff != nullptr) {
					Locker locker(buff, attacker);

					if (state != 0) {
						buff->addState(state);
					}

					// Add skill mods to the buff
					for (int i = 0; i < skillMods->size(); ++i) {
						buff->setSkillModifier(skillMods->elementAt(i).getKey(), skillMods->get(i));
					}

					if (!startSpam.isEmpty()) {
						buff->setStartFlyText("trap/trap", startSpam, 0, 0xFF, 0);
					}

					if (!stopSpam.isEmpty()) {
						buff->setEndFlyText("trap/trap", stopSpam, 0xFF, 0, 0);
					}

					// Add buff to the target
					targetAgent->addBuff(buff);
				}

				float damage = System::random(maxDamage - minDamage) + minDamage;

				targetAgent->inflictDamage(attacker, hamPool, damage, true);

				if (!targetAgent->isEventMob()) {
					totalXP += targetAgent->getLevel() * 15;
				}
			} else if (!trapData->getFailMessage().isEmpty()) {
				message.setStringId("trap/trap", trapData->getFailMessage());
			}

			auto playerManager = zoneServer->getPlayerManager();

			if (playerManager != nullptr) {
				playerManager->awardExperience(attacker, "trapping", totalXP, true);
			}

			message.setTT(targetAgent->getDisplayedName());

			attacker->sendSystemMessage(message);

			message.clear();
		}

		// Reduce cost based upon player's strength, quickness, and focus if any are over 300
		int healthCost = attacker->calculateCostAdjustment(CreatureAttribute::STRENGTH, trapData->getHealthCost());
		int actionCost = attacker->calculateCostAdjustment(CreatureAttribute::QUICKNESS, trapData->getActionCost());
		int mindCost = attacker->calculateCostAdjustment(CreatureAttribute::FOCUS, trapData->getMindCost());

		attacker->inflictDamage(attacker, CreatureAttribute::HEALTH, healthCost, false);
		attacker->inflictDamage(attacker, CreatureAttribute::ACTION, actionCost, false);
		attacker->inflictDamage(attacker, CreatureAttribute::MIND, mindCost, false);
	}
};

} // namespace events
} // namespace creature
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::creature::events;

#endif /* THROWTRAPTASK_H_ */
