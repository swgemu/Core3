/*
 * DotPackCommand.h
 *
 *  Created on: 11/08/2010
 *      Author: victor
 */

#ifndef DOTPACKCOMMAND_H_
#define DOTPACKCOMMAND_H_

#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/DotPack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/packets/object/CombatAction.h"
#include "QueueCommand.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"

class DotPackCommand : public QueueCommand {
protected:
	String effectName;
	String skillName;
public:
	DotPackCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
		effectName = "clienteffect/healing_healenhance.cef";
	}

	void doAnimationsRange(CreatureObject* creature, CreatureObject* targetCreature, uint64 oid, float range, bool area) const {
		String crc;

		if (range < 10.0f) {
			if (area)
				crc = "throw_grenade_near_area_poison";
			else
				crc = "throw_grenade_near_poison";
		} else if (10.0f <= range && range < 20.f) {
			if (area)
				crc = "throw_grenade_medium_area_poison";
			else
				crc = "throw_grenade_medium_poison";
		} else {
			if (area)
				crc = "throw_grenade_far_area_poison";
			else
				crc = "throw_grenade_far_poison";
		}

		CombatAction* action = new CombatAction(creature, targetCreature,  crc.hashCode(), 0x01, 0L);
		creature->broadcastMessage(action, true);
	}

	DotPack* findDotPack(CreatureObject* creature, uint8 pool, bool poolGiven) const {
		if (creature == nullptr)
			return nullptr;

		SceneObject* inventory = creature->getSlottedObject("inventory");

		if (inventory == nullptr) {
			return nullptr;
		}

		int combatMedUse = creature->getSkillMod("combat_healing_ability");

		for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
			SceneObject* item = inventory->getContainerObject(i);

			if (!item->isDotPackObject()) {
				continue;
			}

			DotPack* pack = cast<DotPack*>(item);

			if (pack == nullptr)
				continue;

			if (combatMedUse < pack->getMedicineUseRequired())
				continue;

			if ((skillName == "applypoison") && pack->isPoisonDeliveryUnit()) {
				if (!poolGiven) {
					return pack;
				} else if (pack->getPool() == pool) {
					return pack;
				}
			}

			if ((skillName == "applydisease") && pack->isDiseaseDeliveryUnit()) {
				if (!poolGiven) {
					return pack;
				} else if (pack->getPool() == pool) {
					return pack;
				}
			}
		}

		return nullptr;
	}

	void parseModifier(const String& modifier, uint8& pool, uint64& objectId) const {
		if (!modifier.isEmpty()) {
			StringTokenizer tokenizer(modifier);
			tokenizer.setDelimeter("|");

			String poolName;

			tokenizer.getStringToken(poolName);
			pool = BuffAttribute::getAttribute(poolName);

			if (tokenizer.hasMoreTokens()) {
				objectId = tokenizer.getLongToken();
			}
		} else {
			pool = BuffAttribute::UNKNOWN;
			objectId = 0;
		}
	}

	bool checkTarget(CreatureObject* creature, CreatureObject* targetCreature, uint32 dotType) const {
		if (!targetCreature->isAttackableBy(creature))
			return false;

		if (targetCreature->hasDotImmunity(dotType))
			return false;

		if (!CollisionManager::checkLineOfSight(creature, targetCreature))
			return false;

		if (!playerEntryCheck(creature, targetCreature)) {
			return false;
		}

		return true;
	}

	void awardXp(CreatureObject* creature, const String& type, int power) const {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		int amount = (int)round((float)power);

		if (amount <= 0)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(player, type, amount, true);
	}

	void handleArea(CreatureObject* attackerCreo, CreatureObject* targetCreature, DotPack* pharma, float range) const {
		Zone* zone = attackerCreo->getZone();

		if (zone == nullptr)
			return;

		try {
			CloseObjectsVector* vec = (CloseObjectsVector*)attackerCreo->getCloseObjects();

			SortedVector<QuadTreeEntry*> closeObjects;

			if (vec != nullptr) {
				closeObjects.removeAll(vec->size(), 10);
				vec->safeCopyTo(closeObjects);
			} else {
	#ifdef COV_DEBUG
				attacker->info("Null closeobjects vector in DotPackCommand::handleArea", true);
	#endif
				zone->getInRangeObjects(attackerCreo->getPositionX(), attackerCreo->getPositionY(), 128, &closeObjects, true);
			}


			for (int i = 0; i < closeObjects.size(); i++) {
				SceneObject* object = static_cast<SceneObject*>(closeObjects.get(i));

				if (object == nullptr || !object->isCreatureObject())
					continue;

				CreatureObject* areaCreo = object->asCreatureObject();

				if (areaCreo == nullptr || areaCreo == targetCreature || areaCreo == attackerCreo)
					continue;

				if (targetCreature->getWorldPosition().distanceTo(areaCreo->getWorldPosition()) - areaCreo->getTemplateRadius() > range)
					continue;

				try {
					Locker crossLocker(areaCreo, attackerCreo);

					if (checkTarget(attackerCreo, areaCreo, pharma->getDotType()))
						doAreaMedicActionTarget(attackerCreo, areaCreo, pharma);

				} catch (Exception& e) {
				}
			}
		} catch (Exception& e) {
		}
	}

	void doAreaMedicActionTarget(CreatureObject* creature, CreatureObject* targetCreature, DotPack* dotPack) const {
		int dotPower = dotPack->calculatePower(creature);
		int dotDMG = 0;

		if (dotPack->isPoisonDeliveryUnit()) {
			StringIdChatParameter stringId("healing", "apply_poison_self");
			stringId.setTT(targetCreature->getObjectID());

			creature->sendSystemMessage(stringId);

			StringIdChatParameter stringId2("healing", "apply_poison_other");
			stringId2.setTU(creature->getObjectID());

			targetCreature->sendSystemMessage(stringId2);

			dotDMG = targetCreature->addDotState(creature, CreatureState::POISONED, dotPack->getServerObjectCRC(), dotPower, dotPack->getPool(), dotPack->getDuration(), dotPack->getPotency(), targetCreature->getSkillMod("resistance_poison") + targetCreature->getSkillMod("poison_disease_resist"));
		} else {
			StringIdChatParameter stringId("healing", "apply_disease_self");
			stringId.setTT(targetCreature->getObjectID());

			creature->sendSystemMessage(stringId);

			StringIdChatParameter stringId2("healing", "apply_disease_other");
			stringId2.setTU(creature->getObjectID());

			targetCreature->sendSystemMessage(stringId2);

			dotDMG = targetCreature->addDotState(creature, CreatureState::DISEASED, dotPack->getServerObjectCRC(), dotPower, dotPack->getPool(), dotPack->getDuration(), dotPack->getPotency(), targetCreature->getSkillMod("resistance_disease") + targetCreature->getSkillMod("poison_disease_resist"));
		}

		if (dotDMG) {
			awardXp(creature, "medical", dotDMG); // No experience for healing yourself.

			targetCreature->getThreatMap()->addDamage(creature, dotDMG, "dotDMG");
			creature->addDefender(targetCreature);
		} else {
			StringIdChatParameter stringId("dot_message", "dot_resisted");
			stringId.setTT(targetCreature->getObjectID());

			creature->sendSystemMessage(stringId);
		}

		checkForTef(creature, targetCreature);
	}

	int hasCost(CreatureObject* creature) const {
		if (!creature->isPlayerCreature())
			return 0;

		CreatureObject* player = cast<CreatureObject*>(creature);

		int wpnMind = 150;

		int mindAttackCost = wpnMind - (wpnMind * creature->getHAM(CreatureAttribute::FOCUS) / 1500);

		if (mindAttackCost < 0)
			mindAttackCost = 0;

		if (player->getHAM(CreatureAttribute::MIND) < mindAttackCost)
			return -1;

		return mindAttackCost;
	}

	void applyCost(CreatureObject* creature, int mindDamage) const {
		if (mindDamage == 0)
			return;

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindDamage, false);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		int cost = hasCost(creature);

		if (cost < 0)
			return INSUFFICIENTHAM;

		// Check cooldown timer
		if (!creature->checkCooldownRecovery(skillName)) {
			creature->sendSystemMessage("@healing_response:healing_must_wait"); //You must wait before you can do that.
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == nullptr || !object->isCreatureObject() || creature == object)
			return INVALIDTARGET;

		uint8 pool = BuffAttribute::UNKNOWN;
		bool poolGiven = false;
		uint64 objectId = 0;

		ManagedReference<DotPack*> dotPack;

		parseModifier(arguments.toString(), pool, objectId);

		if (objectId == 0) {
			if (pool != BuffAttribute::UNKNOWN) {
				poolGiven = true;
			}

			dotPack = findDotPack(creature, pool, poolGiven);
		} else {
			SceneObject* inventory = creature->getSlottedObject("inventory");

			if (inventory != nullptr) {
				dotPack = inventory->getContainerObject(objectId).castTo<DotPack*>();
			}
		}

		if (dotPack == nullptr) {
			return GENERALERROR;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>(object.get());

		if (targetCreature == nullptr)
			return GENERALERROR;

		int	range = int(dotPack->getRange() + creature->getSkillMod("healing_range") / 100 * 14);

		// Distance Check
		if (!checkDistance(creature, targetCreature, range))
			return TOOFAR;

		// Line of sight check
		if (creature != targetCreature && !CollisionManager::checkLineOfSight(creature, targetCreature)) {
			creature->sendSystemMessage("@healing:no_line_of_sight"); // You cannot see your target.
			return GENERALERROR;
		}

		// player Entry check
		if (!playerEntryCheck(creature, targetCreature)) {
			return GENERALERROR;
		}

		// Checks Successful
		Locker clocker(targetCreature, creature);

		checkForTef(creature, targetCreature);
		doAnimationsRange(creature, targetCreature, dotPack->getObjectID(), creature->getWorldPosition().distanceTo(targetCreature->getWorldPosition()), dotPack->isArea());

		float modSkill = (float)creature->getSkillMod("healing_range_speed");
		int delay = (int)round(12.0f - (6.0f * modSkill / 100 ));

		if (creature->hasBuff(BuffCRC::FOOD_HEAL_RECOVERY)) {
			DelayedBuff* buff = cast<DelayedBuff*>( creature->getBuff(BuffCRC::FOOD_HEAL_RECOVERY));

			if (buff != nullptr) {
				float percent = buff->getSkillModifierValue("heal_recovery");

				delay = round(delay * (100.0f - percent) / 100.0f);
			}
		}

		// If the delay is less that 4 seconds, use the default time
		delay = (delay < 4) ? defaultTime : delay;

		creature->addCooldown(skillName, delay * 1000);

		applyCost(creature, cost);

		int dotPower = dotPack->calculatePower(creature);
		int dotDMG = 0;

		if (dotPack->isPoisonDeliveryUnit()) {
			if (!targetCreature->hasDotImmunity(dotPack->getDotType())) {
				StringIdChatParameter stringId("healing", "apply_poison_self");
				stringId.setTT(targetCreature->getObjectID());

				creature->sendSystemMessage(stringId);

				StringIdChatParameter stringId2("healing", "apply_poison_other");
				stringId2.setTU(creature->getObjectID());

				targetCreature->sendSystemMessage(stringId2);

				dotDMG = targetCreature->addDotState(creature, CreatureState::POISONED, dotPack->getServerObjectCRC(), dotPower, dotPack->getPool(), dotPack->getDuration(), dotPack->getPotency(), targetCreature->getSkillMod("resistance_poison") + targetCreature->getSkillMod("poison_disease_resist"));
			}
		} else {
			if (!targetCreature->hasDotImmunity(dotPack->getDotType())) {
				StringIdChatParameter stringId("healing", "apply_disease_self");
				stringId.setTT(targetCreature->getObjectID());

				creature->sendSystemMessage(stringId);

				StringIdChatParameter stringId2("healing", "apply_disease_other");
				stringId2.setTU(creature->getObjectID());

				targetCreature->sendSystemMessage(stringId2);

				dotDMG = targetCreature->addDotState(creature, CreatureState::DISEASED, dotPack->getServerObjectCRC(), dotPower, dotPack->getPool(), dotPack->getDuration(), dotPack->getPotency(), targetCreature->getSkillMod("resistance_disease") + targetCreature->getSkillMod("poison_disease_resist"));
			}
		}

		if (dotDMG) {
			awardXp(creature, "medical", dotDMG);
			targetCreature->getThreatMap()->addDamage(creature, dotDMG, "dotDMG");
		} else {
			StringIdChatParameter stringId("dot_message", "dot_resisted");
			stringId.setTT(targetCreature->getObjectID());

			creature->sendSystemMessage(stringId);

			StringIdChatParameter stringId2("healing", "dot_resist_other");

			targetCreature->sendSystemMessage(stringId2);
		}

		if (dotPack->isArea()) {
			if (targetCreature != creature)
				clocker.release();

			handleArea(creature, targetCreature, dotPack, dotPack->getArea());
		}

		if (targetCreature != creature)
			clocker.release();

		Locker dlocker(dotPack, creature);

		dotPack->decreaseUseCount();
		creature->notifyObservers(ObserverEventType::MEDPACKUSED);

		return SUCCESS;
	}

};

#endif /* DOTPACKCOMMAND_H_ */
