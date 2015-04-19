/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALDROIDDAMAGECOMMAND_H_
#define HEALDROIDDAMAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"

class HealDroidDamageCommand : public QueueCommand {
	float range;
	float mindCost;

public:

	HealDroidDamageCommand(const String& name, ZoneProcessServer* server)
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

	void doAnimations(CreatureObject* creature, CreatureObject* droid) const {
		droid->playEffect("clienteffect/healing_healdamage.cef", "");

		creature->doAnimation("heal_other");
	}

	StimPack* findStimPack(CreatureObject* creature) const {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
				SceneObject* item = inventory->getContainerObject(i);

				if (!item->isTangibleObject())
					continue;

				TangibleObject* tano = cast<TangibleObject*>( item);

				if (tano->isPharmaceuticalObject()) {
					PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>( tano);

					if (pharma->isDroidRepairKit()) {
						StimPack* stimPack = cast<StimPack*>( pharma);

						return stimPack;
					}

				}
			}
		}

		return NULL;
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* droid, StimPack* stimPack) const {
		if (!creature->canTreatInjuries()) {
			creature->sendSystemMessage("@healing_response:healing_must_wait"); //You must wait before you can do that.
			return false;
		}

		if (stimPack == NULL) {
			creature->sendSystemMessage("No valid droid repair kit found.");
			return false;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		if (!droid->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help"); //It would be unwise to help such a patient.
			return false;
		}

		if (!droid->hasDamage(CreatureAttribute::HEALTH) && !droid->hasDamage(CreatureAttribute::ACTION) && !droid->hasDamage(CreatureAttribute::MIND)) {
			StringBuffer message;
			message << droid->getDisplayedName() << " has no damage to heal.";
			creature->sendSystemMessage(message.toString());
			return false;
		}

		if (!CollisionManager::checkLineOfSight(creature, droid)) {
			creature->sendSystemMessage("@container_error_message:container18");
			return false;
		}

		return true;
	}

	void sendHealMessage(CreatureObject* creature, DroidObject* droid, int healthDamage, int actionDamage, int mindDamage)  const {
		if (!creature->isPlayerCreature())
			return;

		StringIdChatParameter stringId("healing", "droid_repair_damage_self"); // You have repaired %TO and healed a total of %DI point of damage.
		stringId.setTO(droid);
		stringId.setDI(healthDamage + actionDamage + mindDamage);
		creature->sendSystemMessage(stringId);

		ManagedReference<CreatureObject*> droidOwner = droid->getLinkedCreature().get();

		if (droidOwner != NULL && droidOwner != creature) {
			StringIdChatParameter stringId("healing", "droid_repair_damage_other"); // %TT has repaired %TO and healed a total of %DI point of damage.
			stringId.setTT(creature);
			stringId.setDI(healthDamage + actionDamage + mindDamage);
			droidOwner->sendSystemMessage(stringId);
		}
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isDroidObject()) {
			creature->sendSystemMessage("Invalid Target.");
			return GENERALERROR;
		}

		DroidObject* droid = cast<DroidObject*>( object.get());

		Locker clocker(droid, creature);

		if (!droid->isPet() || droid->isDead() || droid->isAttackableBy(creature)) {
			creature->sendSystemMessage("Invalid Target.");
			return GENERALERROR;
		}

		if (!creature->isInRange(droid, range + droid->getTemplateRadius() + creature->getTemplateRadius()))
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

		if (!canPerformSkill(creature, droid, stimPack))
			return GENERALERROR;

		uint32 stimPower = 0;
		stimPower = stimPack->calculatePower(creature, droid, false);

		int healthHealed = droid->healDamage(creature, CreatureAttribute::HEALTH, stimPower);
		int actionHealed = droid->healDamage(creature, CreatureAttribute::ACTION, stimPower, true, false);
		int mindHealed = droid->healDamage(creature, CreatureAttribute::MIND, stimPower, true, false);

		sendHealMessage(creature, droid, healthHealed, actionHealed, mindHealed);

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);

		Locker locker(stimPack);
		stimPack->decreaseUseCount();

		doAnimations(creature, droid);

		deactivateInjuryTreatment(creature);

		checkForTef(creature, droid);

		return SUCCESS;
	}

};

#endif //HEALDROIDDAMAGECOMMAND_H_
