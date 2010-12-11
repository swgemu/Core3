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
		range = 6;
		mindCost = 100;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		creatureTarget->playEffect("clienteffect/healing_healdamage.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	void parseModifier(const String& modifier, uint64& objectId) {
		if (!modifier.isEmpty())
			objectId = Long::valueOf(modifier);
		else
			objectId = 0;
	}

	CurePack* findCurePack(CreatureObject* creature) {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
				SceneObject* object = inventory->getContainerObject(i);

				if (!object->isTangibleObject())
					continue;

				TangibleObject* item = (TangibleObject*) object;

				if (item->isPharmaceuticalObject()) {
					PharmaceuticalObject* pharma = (PharmaceuticalObject*) item;

					if (pharma->isCurePack()) {
						CurePack* curePack = (CurePack*) pharma;

						if (curePack->getMedicineUseRequired() <= medicineUse && curePack->getState() == state)
							return curePack;
					}
				}
			}
		}

		return NULL;
	}

	void sendCureMessage(CreatureObject* object, CreatureObject* target) {
		if (!object->isPlayerCreature())
			return;

		if (!target->isPlayerCreature())
			return;

		PlayerCreature* creature = (PlayerCreature*) object;
		PlayerCreature* creatureTarget = (PlayerCreature*) target;
		StringBuffer msgTarget, msgPlayer;
		String msgSelf;
		switch (state) {
		case CreatureState::POISONED:
			msgPlayer << "You apply poison antidote to " << creatureTarget->getFirstName() << ".";
			msgTarget << creature->getFirstName() << " applies poison antidote to you.";
			msgSelf = "poison_antidote_self";
			break;
		case CreatureState::DISEASED:
			msgPlayer << "You apply disease antidote to " << creatureTarget->getFirstName() << ".";
			msgTarget << creature->getFirstName() << " applies disease antidote to you.";
			msgSelf = "disease_antidote_self";
			break;
		case CreatureState::ONFIRE:
			msgPlayer << "You attempt to suppress the flames on " << creatureTarget->getFirstName() << ".";
			msgTarget << creature->getFirstName() << " covers you in a suppressive blanket.";
			msgSelf = "blanket";
			break;
		default:
			return;
		}

		if (creature != creatureTarget) {
			creature->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());
		} else {
			creature->sendSystemMessage("healing_response", msgSelf);
		}
	}

	void deactivateConditionTreatment(CreatureObject* creature) {
		float modSkill = (float)creature->getSkillMod("healing_wound_speed");
		int delay = (int)round((modSkill * -(2.0f / 25.0f)) + 20.0f);

		//Force the delay to be at least 3 seconds.
		delay = (delay < 3) ? 3 : delay;

		StringIdChatParameter message("healing_response", "healing_response_59");
		Reference<InjuryTreatmentTask*> task = new InjuryTreatmentTask(creature, message, "conditionTreatment");
		creature->addPendingTask("conditionTreatment", task);
		task->schedule(delay * 1000);
	}

	void awardXp(CreatureObject* creature, const String& type, int power) {
		if (!creature->isPlayerCreature())
			return;

		PlayerCreature* player = (PlayerCreature*) creature;

		int amount = (int) round((float) power * 1.0f);

		if (amount <= 0)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(player, type, amount, true);
	}

	bool checkTarget(CreatureObject* creature, CreatureObject* creatureTarget) {
		// TODO: Pet Check
		if (!creatureTarget->isPlayerCreature()) {
			return false;
		}

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

		/*if (creatureTarget->isOvert() && creatureTarget->getFaction() != creature->getFaction()) {
			return false;
		}*/
		return true;
	}

	void handleArea(CreatureObject* creature, CreatureObject* areaCenter, CurePack* pharma,
			float range) {

		Zone* zone = creature->getZone();

		if (zone == NULL)
			return;

		try {
			zone->rlock();

			for (int i = 0; i < areaCenter->inRangeObjectCount(); i++) {
				SceneObject* object = (SceneObject*) areaCenter->getInRangeObject(i);

				if (!object->isPlayerCreature())
					continue;

				if (object == areaCenter || object == creature)
					continue;

				if (!areaCenter->isInRange(object, range))
					continue;

				CreatureObject* creatureTarget = (CreatureObject*) object;

				if (creatureTarget->isAttackableBy(creature))
					continue;

				zone->runlock();

				try {

					Locker crossLocker(creatureTarget, creature);

					if (checkTarget(creature, creatureTarget)) {
						doAreaMedicActionTarget(creature, creatureTarget, pharma);
					}

				} catch (...) {

				}

				zone->rlock();

			}

			zone->runlock();
		} catch (...) {
			zone->runlock();
		}


	}

	void doAreaMedicActionTarget(CreatureObject* creature, CreatureObject* creatureTarget, PharmaceuticalObject* pharma) {
		CurePack* curePack = NULL;

		if (pharma->isCurePack())
			curePack = (CurePack*) pharma;
		else
			return;

		creatureTarget->healDot(state, curePack->calculatePower(creature));

		sendCureMessage(creature, creatureTarget);

		if (creatureTarget != creature)
			awardXp(creature, "medical", 50); //No experience for healing yourself.
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, CurePack* curePack) {
		switch (state) {
		case CreatureState::POISONED:
			if (!creatureTarget->isPoisoned()) {
				if (creature == creatureTarget)
					creature->sendSystemMessage("healing_response", "healing_response_82"); //You are not poisoned.
				else {
					StringIdChatParameter stringId("healing_response", "healing_response_84");
					stringId.setTT(creatureTarget->getObjectID());
					creature->sendSystemMessage(stringId); //%NT is not poisoned.
				}
				return false;
			}
			break;
		case CreatureState::DISEASED:
			if (!creatureTarget->isDiseased()) {
				if (creature == creatureTarget)
					creature->sendSystemMessage("healing_response", "healing_response_90"); //You are not diseased.
				else {
					StringIdChatParameter stringId("healing_response", "healing_response_92");
					stringId.setTT(creatureTarget->getObjectID());
					creature->sendSystemMessage(stringId); //%NT is not poisoned.
					//creature->sendSystemMessage("healing_response", "healing_response_92", creatureTarget->getObjectID()); //%NT is not diseased.
				}
				return false;
			}
			break;
		case CreatureState::ONFIRE:
			if (!creatureTarget->isOnFire()) {
				if (creature == creatureTarget)
					creature->sendSystemMessage("healing_response", "healing_response_86"); //You are not on fire.
				else {
					StringIdChatParameter stringId("healing_response", "healing_response_88");
					stringId.setTT(creatureTarget->getObjectID());
					creature->sendSystemMessage(stringId); //%NT is not poisoned.
					//creature->sendSystemMessage("healing_response", "healing_response_88", creatureTarget->getObjectID()); //%NT is not on fire.
				}
				return false;
			}
			break;
		}

		if (!creature->canTreatConditions()) {
			creature->sendSystemMessage("healing_response", "healing_must_wait"); //You must wait before you can do that.
			return false;
		}

		if (curePack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
			return false;
		}


		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot Cure States while prone.");
			return false;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot Cure States while Meditating.");
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
			Player * pt = (Player *) creatureTarget;
			Player * p = (Player *) creature;

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

		CreatureObject* targetCreature = (CreatureObject*) object.get();

		Locker clocker(targetCreature, creature);

		if (targetCreature->isAiAgent() || targetCreature->isDead() || targetCreature->isRidingCreature() || targetCreature->isMounted() || targetCreature->isAttackableBy(creature))
			targetCreature = creature;

		uint64 objectId = 0;

		parseModifier(arguments.toString(), objectId);

		ManagedReference<CurePack*> curePack;

		if (objectId == 0) {
			curePack = findCurePack(creature);
		} else {
			SceneObject* inventory = creature->getSlottedObject("inventory");

			if (inventory != NULL) {
				curePack = dynamic_cast<CurePack*>(inventory->getContainerObject(objectId));
			}
		}

		if (!creature->isInRange(targetCreature, range))
			return TOOFAR;

		if (!canPerformSkill(creature, targetCreature, curePack))
			return GENERALERROR;

		sendCureMessage(creature, targetCreature);

		targetCreature->healDot(state, curePack->calculatePower(creature));

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);

		deactivateConditionTreatment(creature);

		if (curePack != NULL)
			curePack->decreaseUseCount();

		if (targetCreature != creature)
			awardXp(creature, "medical", 50); //No experience for healing yourself.

		if (curePack->isArea()) {
			if (creature != targetCreature)
				clocker.release();

			handleArea(creature, targetCreature, curePack, curePack->getArea());
		}

		doAnimations(creature, targetCreature);

		return SUCCESS;
	}
};


#endif /* CURESTATECOMMAND_H_ */
