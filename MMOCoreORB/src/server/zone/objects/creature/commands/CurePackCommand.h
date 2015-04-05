/*
 * CureStateCommand.h
 *
 *  Created on: 10/08/2010
 *      Author: victor
 */

#ifndef CUREPACKCOMMAND_H_
#define CUREPACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/CurePack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/InjuryTreatmentTask.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/BuffAttribute.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/packets/object/CombatAction.h"
#include "QueueCommand.h"

class CurePackCommand : public QueueCommand {
protected:
	int mindCost;
	float range;
	uint64 state;
public:
	CurePackCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		range = 7;
		mindCost = 100;
		state = 0;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) const {
		creatureTarget->playEffect("clienteffect/healing_healdamage.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	void parseModifier(const String& modifier, uint64& objectId) const {
		if (!modifier.isEmpty())
			objectId = Long::valueOf(modifier);
		else
			objectId = 0;
	}

	CurePack* findCurePack(CreatureObject* creature) const {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
				SceneObject* object = inventory->getContainerObject(i);

				if (!object->isTangibleObject())
					continue;

				TangibleObject* item = cast<TangibleObject*>( object);

				if (item->isPharmaceuticalObject()) {
					PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>( item);

					if (pharma->isCurePack()) {
						CurePack* curePack = cast<CurePack*>( pharma);

						if (curePack->getMedicineUseRequired() <= medicineUse && curePack->getState() == state)
							return curePack;
					}
				}
			}
		}

		return NULL;
	}

	void sendCureMessage(CreatureObject* object, CreatureObject* target) const {
		if (!object->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>( target);
		StringBuffer msgTarget, msgPlayer;
		String msgSelf, targetName;

		if (creatureTarget->isPlayerCreature())
			targetName = creatureTarget->getFirstName();
		else
			targetName = creatureTarget->getDisplayedName();

		switch (state) {
		case CreatureState::POISONED:
			msgPlayer << "You apply poison antidote to " << targetName << ".";
			msgTarget << creature->getFirstName() << " applies poison antidote to you.";
			msgSelf = "poison_antidote_self";
			break;
		case CreatureState::DISEASED:
			msgPlayer << "You apply disease antidote to " << targetName << ".";
			msgTarget << creature->getFirstName() << " applies disease antidote to you.";
			msgSelf = "disease_antidote_self";
			break;
		case CreatureState::ONFIRE:
			msgPlayer << "You attempt to suppress the flames on " << targetName << ".";
			msgTarget << creature->getFirstName() << " covers you in a suppressive blanket.";
			msgSelf = "blanket";
			break;
		default:
			return;
		}

		if (creature == creatureTarget) {
			creature->sendSystemMessage("@healing_response:" + msgSelf);
		} else {
			creature->sendSystemMessage(msgPlayer.toString());

			if (creatureTarget->isPlayerCreature())
				creatureTarget->sendSystemMessage(msgTarget.toString());
		}
	}

	void deactivateConditionTreatment(CreatureObject* creature) const {
		float modSkill = (float)creature->getSkillMod("healing_injury_speed");
		int delay = (int)round(20.0f - (modSkill / 5));

		if (creature->hasBuff(BuffCRC::FOOD_HEAL_RECOVERY)) {
			DelayedBuff* buff = cast<DelayedBuff*>( creature->getBuff(BuffCRC::FOOD_HEAL_RECOVERY));

			if (buff != NULL) {
				float percent = buff->getSkillModifierValue("heal_recovery");

				delay = round(delay * (100.0f - percent) / 100.0f);
			}
		}

		//Force the delay to be at least 4 seconds.
		delay = (delay < 4) ? 4 : delay;

		StringIdChatParameter message("healing_response", "healing_response_58"); //You are now ready to heal more damage.
		Reference<InjuryTreatmentTask*> task = new InjuryTreatmentTask(creature, message, "conditionTreatment");
		creature->addPendingTask("conditionTreatment", task, delay * 1000);
	}

	void awardXp(CreatureObject* creature, const String& type, int power) const {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		int amount = (int) round((float) power * 1.0f);

		if (amount <= 0)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(player, type, amount, true);
	}

	bool checkTarget(CreatureObject* creature, CreatureObject* creatureTarget) const {

		switch (state) {
		case CreatureState::POISONED:
			if (!creatureTarget->isPoisoned()) {
				return false;
			}
			break;
		case CreatureState::DISEASED:
			if (!creatureTarget->isDiseased()) {
				return false;
			}
			break;
		case CreatureState::ONFIRE:
			if (!creatureTarget->isOnFire()) {
				return false;
			}
			break;
		}

		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			return false;
		}

		if (!creatureTarget->isHealableBy(creature)) {
			return false;
		}

		return true;
	}

	void handleArea(CreatureObject* creature, CreatureObject* areaCenter, CurePack* pharma,
			float range) const {

		Zone* zone = creature->getZone();

		if (zone == NULL)
			return;

		try {
			SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
			CloseObjectsVector* vec = (CloseObjectsVector*) areaCenter->getCloseObjects();
			vec->safeCopyTo(closeObjects);

			for (int i = 0; i < closeObjects.size(); i++) {
				SceneObject* object = cast<SceneObject*>( closeObjects.get(i).get());

				if (!object->isPlayerCreature() && !object->isPet())
					continue;

				if (object == areaCenter || object->isDroidObject())
					continue;

				if (!areaCenter->isInRange(object, range))
					continue;

				CreatureObject* creatureTarget = cast<CreatureObject*>( object);

				try {
					Locker crossLocker(creatureTarget, creature);

					if (creatureTarget->isAttackableBy(creature))
						continue;

					if (checkTarget(creature, creatureTarget)) {
						doAreaMedicActionTarget(creature, creatureTarget, pharma);
					}

				} catch (Exception& e) {
					throw;
				}

			}

		} catch (Exception& e) {
			throw;
		}
	}

	void doAreaMedicActionTarget(CreatureObject* creature, CreatureObject* creatureTarget, PharmaceuticalObject* pharma) const {
		CurePack* curePack = NULL;

		if (pharma->isCurePack())
			curePack = cast<CurePack*>( pharma);
		else
			return;

		creatureTarget->healDot(state, curePack->calculatePower(creature));

		sendCureMessage(creature, creatureTarget);

		if (creatureTarget != creature && !creatureTarget->isPet())
			awardXp(creature, "medical", 50); //No experience for healing yourself or pets.

		checkForTef(creature, creatureTarget);
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, CurePack* curePack) const {
		switch (state) {
		case CreatureState::POISONED:
			if (!creatureTarget->isPoisoned()) {
				if (creature == creatureTarget)
					creature->sendSystemMessage("@healing_response:healing_response_82"); //You are not poisoned.
				else if (creatureTarget->isPlayerCreature()) {
					StringIdChatParameter stringId("healing_response", "healing_response_84");
					stringId.setTT(creatureTarget->getObjectID());
					creature->sendSystemMessage(stringId); //%NT is not poisoned.
				} else {
					StringBuffer message;
					message << creatureTarget->getDisplayedName() << " is not poisoned.";
					creature->sendSystemMessage(message.toString());
				}
				return false;
			}
			break;
		case CreatureState::DISEASED:
			if (!creatureTarget->isDiseased()) {
				if (creature == creatureTarget)
					creature->sendSystemMessage("@healing_response:healing_response_90"); //You are not diseased.
				else if (creatureTarget->isPlayerCreature()) {
					StringIdChatParameter stringId("healing_response", "healing_response_92");
					stringId.setTT(creatureTarget->getObjectID());
					creature->sendSystemMessage(stringId); //%NT is not diseased.
				} else {
					StringBuffer message;
					message << creatureTarget->getDisplayedName() << " is not diseased.";
					creature->sendSystemMessage(message.toString());
				}
				return false;
			}
			break;
		case CreatureState::ONFIRE:
			if (!creatureTarget->isOnFire()) {
				if (creature == creatureTarget)
					creature->sendSystemMessage("@healing_response:healing_response_86"); //You are not on fire.
				else if (creatureTarget->isPlayerCreature()) {
					StringIdChatParameter stringId("healing_response", "healing_response_88");
					stringId.setTT(creatureTarget->getObjectID());
					creature->sendSystemMessage(stringId); //%NT is not on fire.
				} else {
					StringBuffer message;
					message << creatureTarget->getDisplayedName() << " is not on fire.";
					creature->sendSystemMessage(message.toString());
				}
				return false;
			}
			break;
		}

		if (!creature->canTreatConditions()) {
			creature->sendSystemMessage("@healing_response:healing_must_wait"); //You must wait before you can do that.
			return false;
		}

		if (curePack == NULL) {
			creature->sendSystemMessage("@healing_response:healing_response_60"); //No valid medicine found.
			return false;
		}

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");
			return false;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			creature->sendSystemMessage("@container_error_message:container18");
			return false;
		}

		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL && !object->isCreatureObject()) {
			return INVALIDTARGET;
		} else if (object == NULL)
			object = creature;

		CreatureObject* targetCreature = cast<CreatureObject*>( object.get());

		Locker clocker(targetCreature, creature);

		if ((targetCreature->isAiAgent() && !targetCreature->isPet()) || targetCreature->isDroidObject() || targetCreature->isDead() || targetCreature->isRidingMount() || targetCreature->isAttackableBy(creature))
			targetCreature = creature;

		uint64 objectId = 0;

		parseModifier(arguments.toString(), objectId);

		ManagedReference<CurePack*> curePack;

		if (objectId == 0) {
			curePack = findCurePack(creature);
		} else {
			SceneObject* inventory = creature->getSlottedObject("inventory");

			if (inventory != NULL) {
				curePack = inventory->getContainerObject(objectId).castTo<CurePack*>();
			}
		}

		if (!creature->isInRange(targetCreature, range + creature->getTemplateRadius() + targetCreature->getTemplateRadius()))
			return TOOFAR;

		if (!canPerformSkill(creature, targetCreature, curePack))
			return GENERALERROR;

		sendCureMessage(creature, targetCreature);

		targetCreature->healDot(state, curePack->calculatePower(creature));

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);

		deactivateConditionTreatment(creature);

		if (curePack != NULL)
			curePack->decreaseUseCount();

		if (targetCreature != creature && !targetCreature->isPet())
			awardXp(creature, "medical", 50); //No experience for healing yourself or pets.

		if (curePack->isArea()) {
			if (creature != targetCreature)
				clocker.release();

			handleArea(creature, targetCreature, curePack, curePack->getArea());
		}

		doAnimations(creature, targetCreature);

		creature->notifyObservers(ObserverEventType::MEDPACKUSED);

		checkForTef(creature, targetCreature);

		return SUCCESS;
	}
};

#endif /* CURESTATECOMMAND_H_ */
