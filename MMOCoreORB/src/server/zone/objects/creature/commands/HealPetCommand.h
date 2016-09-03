/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALPETCOMMAND_H_
#define HEALPETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"

class HealPetCommand : public QueueCommand {
	float range;
	float mindCost;

public:

	HealPetCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

		range = 5;
		mindCost = 50;
	}

	void deactivateInjuryTreatment(CreatureObject* creature) const {
		int delay = 20;

		StringIdChatParameter message("healing_response", "healing_response_58"); //You are now ready to heal more damage.
		Reference<InjuryTreatmentTask*> task = new InjuryTreatmentTask(creature, message, "injuryTreatment");
		creature->addPendingTask("injuryTreatment", task, delay * 1000);
	}

	void doAnimations(CreatureObject* creature, CreatureObject* pet) const {
		pet->playEffect("clienteffect/healing_healdamage.cef", "");

		creature->doAnimation("heal_other");
	}

	StimPack* findStimPack(CreatureObject* creature) const {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
				SceneObject* item = inventory->getContainerObject(i);

				if (!item->isPharmaceuticalObject())
					continue;

				PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>(item);

				if (pharma->isPetStimPack()) {
					StimPack* stimPack = cast<StimPack*>(pharma);

					return stimPack;
				}
			}
		}

		return NULL;
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* pet, StimPack* stimPack, int mindCostNew) const {
		if (!creature->canTreatInjuries()) {
			creature->sendSystemMessage("@healing_response:healing_must_wait"); //You must wait before you can do that.
			return false;
		}

		if (stimPack == NULL) {
			creature->sendSystemMessage("@healing_response:healing_response_60"); //No valid medicine found.
			return false;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCostNew) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		if (!pet->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help"); //It would be unwise to help such a patient.
			return false;
		}

		Vector<byte> atts = stimPack->getAttributes();
		bool needsHeals = false;

		for (int i = 0; i < atts.size(); i++) {
			if (pet->hasDamage(atts.get(i)))
				needsHeals = true;
		}

		if (!needsHeals) {
			StringBuffer message;
			message << pet->getDisplayedName() << " has no damage to heal.";
			creature->sendSystemMessage(message.toString());
			return false;
		}

		return true;
	}

	void sendHealMessage(CreatureObject* creature, CreatureObject* pet, int healthDamage, int actionDamage, int mindDamage) const {
		if (!creature->isPlayerCreature())
			return;

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (healthDamage > 0 && actionDamage > 0 && mindDamage > 0) {
			msgBody << healthDamage << " health, " << actionDamage << " action, and " << mindDamage << " mind";
		} else if (healthDamage > 0 && actionDamage > 0) {
			msgBody << healthDamage << " health and " << actionDamage << " action";
		} else if (healthDamage > 0 && mindDamage > 0) {
			msgBody << healthDamage << " health and " << mindDamage << " mind";
		} else if (actionDamage > 0 && mindDamage > 0) {
			msgBody << actionDamage << " action and " << mindDamage << " mind";
		} else if (healthDamage > 0) {
			msgBody << healthDamage << " health";
		} else if (actionDamage > 0) {
			msgBody << actionDamage << " action";
		} else if (mindDamage > 0) {
			msgBody << mindDamage << " mind";
		} else {
			return; //No damage to heal.
		}

		msgTail << " damage.";

		msgPlayer << "You heal " << pet->getDisplayedName() << " for " << msgBody.toString() << msgTail.toString();
		creature->sendSystemMessage(msgPlayer.toString());
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isCreature()) {
			creature->sendSystemMessage("Invalid Target.");
			return GENERALERROR;
		}

		Creature* pet = cast<Creature*>( object.get());

		Locker clocker(pet, creature);

		if (!pet->isPet() || pet->isDead() || pet->isAttackableBy(creature)) {
			creature->sendSystemMessage("Invalid Target.");
			return GENERALERROR;
		}

		PetControlDevice* pcd = pet->getControlDevice().get().castTo<PetControlDevice*>();
		if (pcd == NULL || pcd->getPetType() != PetManager::CREATUREPET) {
			creature->sendSystemMessage("Invalid Target.");
			return GENERALERROR;
		}

		if(!checkDistance(creature, pet, range))
			return TOOFAR;

		uint64 objectID = 0;

		try {
			if (!arguments.isEmpty())
				objectID = UnsignedLong::valueOf(arguments.toString());
		} catch (Exception& e) {

		}

		ManagedReference<StimPack*> stimPack = NULL;

		if (objectID == 0) {
			stimPack = findStimPack(creature);
		} else {
			SceneObject* inventory = creature->getSlottedObject("inventory");

			if (inventory != NULL) {
				stimPack = inventory->getContainerObject(objectID).castTo<StimPack*>();
			}
		}

		int mindCostNew = creature->calculateCostAdjustment(CreatureAttribute::FOCUS, mindCost);

		if (!canPerformSkill(creature, pet, stimPack, mindCostNew))
			return GENERALERROR;

		uint32 stimPower = stimPack->calculatePower(creature, pet);

		Vector<byte> atts = stimPack->getAttributes();
		int healthHealed = 0, actionHealed = 0, mindHealed = 0;
		bool notifyObservers = true;


		if (atts.contains(CreatureAttribute::HEALTH)) {
			healthHealed = pet->healDamage(creature, CreatureAttribute::HEALTH, stimPower);
			notifyObservers = false;
		}

		if (atts.contains(CreatureAttribute::ACTION)) {
			if (notifyObservers) {
				actionHealed = pet->healDamage(creature, CreatureAttribute::ACTION, stimPower);
				notifyObservers = false;
			} else {
				actionHealed = pet->healDamage(creature, CreatureAttribute::ACTION, stimPower, true, false);
			}
		}

		if (atts.contains(CreatureAttribute::MIND)) {
			if (notifyObservers) {
				mindHealed = pet->healDamage(creature, CreatureAttribute::MIND, stimPower);
			} else {
				mindHealed = pet->healDamage(creature, CreatureAttribute::MIND, stimPower, true, false);
			}
		}

		if (creature->isPlayerCreature()) {
			PlayerManager* playerManager = server->getPlayerManager();
			playerManager->sendBattleFatigueMessage(creature, pet);
		}

		sendHealMessage(creature, pet, healthHealed, actionHealed, mindHealed);

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCostNew, false);

		Locker locker(stimPack);
		stimPack->decreaseUseCount();

		doAnimations(creature, pet);

		deactivateInjuryTreatment(creature);

		checkForTef(creature, pet);

		return SUCCESS;
	}

};

#endif //HEALPETCOMMAND_H_
