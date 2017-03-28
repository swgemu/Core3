/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALDROIDWOUNDCOMMAND_H_
#define HEALDROIDWOUNDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/tangible/pharmaceutical/WoundPack.h"

class HealDroidWoundCommand : public QueueCommand {
	int mindCost;
	float range;
public:

	HealDroidWoundCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

		mindCost = 50;
		range = 6;
	}

	void deactivateWoundTreatment(CreatureObject* creature) const {
		int delay = 20;

		StringIdChatParameter message("healing_response", "healing_response_59");
		Reference<InjuryTreatmentTask*> task = new InjuryTreatmentTask(creature, message, "woundTreatment");
		creature->addPendingTask("woundTreatment", task, delay * 1000);
	}

	void doAnimations(CreatureObject* creature, CreatureObject* droid) const {
		droid->playEffect("clienteffect/healing_healwound.cef", "");

		creature->doAnimation("heal_other");
	}

	void sendWoundMessage(CreatureObject* creature, DroidObject* droid, uint32 woundsHealed) const {
		if (!creature->isPlayerCreature())
			return;

		StringIdChatParameter stringId("healing", "droid_repair_wound_self"); // You have repaired %TO and healed a total of %DI wounds.
		stringId.setTO(droid->getObjectID());
		stringId.setDI(woundsHealed);
		creature->sendSystemMessage(stringId);

		ManagedReference<CreatureObject*> droidOwner = droid->getLinkedCreature().get();

		if (droidOwner != NULL && droidOwner != creature) {
			StringIdChatParameter stringId("healing", "droid_repair_wound_other"); // %TT has repaired %TO and healed a total of %DI wounds.
			stringId.setTT(creature->getObjectID());
			stringId.setTO(droid->getObjectID());
			stringId.setDI(woundsHealed);
			droidOwner->sendSystemMessage(stringId);
		}
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* droid, WoundPack* woundPack, int mindCostNew) const {
		if (!creature->canTreatWounds()) {
			creature->sendSystemMessage("@healing_response:enhancement_must_wait"); //You must wait before you can heal wounds or apply enhancements again.
			return false;
		}

		if (woundPack == NULL) {
			creature->sendSystemMessage("@error_message:droid_repair_no_wound_kit"); //No valid droid wound repair kit was found in your inventory.
			return false;
		}

		int medicalRatingNotIncludingCityBonus = creature->getSkillMod("private_medical_rating") - creature->getSkillModOfType("private_medical_rating", SkillModManager::CITY);
		if (medicalRatingNotIncludingCityBonus <= 0) {
			creature->sendSystemMessage("@healing_response:must_be_near_droid"); //You must be in a hospital, at a campsite, or near a surgical droid to do that.
			return false;
		} else {
			// are we in a cantina? we have a private medical rating so either thats from a droid or camp or hospital
			ManagedReference<SceneObject*> root = creature->getRootParent();
			if (root != NULL && root->isClientObject()) {
				uint32 gameObjectType = root->getGameObjectType();
				switch (gameObjectType) {
						case SceneObjectType::RECREATIONBUILDING:
						case SceneObjectType::HOTELBUILDING:
						case SceneObjectType::THEATERBUILDING:
							creature->sendSystemMessage("@error_message:droid_repair_not_valid_location"); // You must be in a city, at a camp site, or near your residence in order to use these tools.
							return false;
				}
			}
		}

		if (creature->isInCombat()) {
			creature->sendSystemMessage("@error_message:droid_repair_you_in_combat"); //You cannot repair this droid while you are in combat!
			return false;
		}

		if (droid->isInCombat()) {
			creature->sendSystemMessage("@error_message:droid_repair_droid_in_combat"); //You cannot repair this droid while it is in combat!
			return false;
		}

		if (!droid->isHealableBy(creature)) {
			creature->sendSystemMessage("@error_message:droid_repair_opposite_faction");  //It would be unwise to repair a droid such as this.
			return false;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCostNew) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		if (!CollisionManager::checkLineOfSight(creature, droid)) {
			creature->sendSystemMessage("@container_error_message:container18");
			return false;
		}

		return true;
	}

	void parseModifier(const String& modifier, uint64& objectId) const {
		if (!modifier.isEmpty()) {
			StringTokenizer tokenizer(modifier);

			objectId = tokenizer.getLongToken();
		} else {
			objectId = 0;
		}
	}

	uint8 findAttribute(CreatureObject* creature) const {
		for (int i = 0; i < 9; ++i) {
			int wounds = creature->getWounds(i);

			if (wounds != 0)
				return i;
		}

		return CreatureAttribute::UNKNOWN;
	}

	WoundPack* findWoundPack(CreatureObject* creature) const {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				SceneObject* object = inventory->getContainerObject(i);

				if (!object->isPharmaceuticalObject())
					continue;

				PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>(object);

				if (pharma->isDroidReconstructionKit()) {
					WoundPack* woundPack = cast<WoundPack*>(pharma);

					return woundPack;
				}
			}
		}

		return NULL;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!creature->hasSkill("crafting_droidengineer_novice")) {
			creature->sendSystemMessage("@error_message:droid_repair_not_droid_engineer"); //You must be a droid engineer to use this tool kit.
			return GENERALERROR;
		}

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL) {
			creature->sendSystemMessage("@error_message:droid_repair_no_target"); //You must target a droid pet to use these tools.
			return GENERALERROR;
		} else if (!object->isDroidObject()) {
			creature->sendSystemMessage("@error_message:droid_repair_target_not_droid"); //Your target is not able to be repaired with these tools.
			return GENERALERROR;
		}

		DroidObject* droid = cast<DroidObject*>( object.get());

		Locker clocker(droid, creature);

		if (!droid->isPet() || droid->isDead() || droid->isAttackableBy(creature))
			return INVALIDTARGET;

		if(!checkDistance(creature, droid, range))
			return TOOFAR;

		uint8 attribute = findAttribute(droid);

		if (attribute == CreatureAttribute::UNKNOWN) {
			StringIdChatParameter stringId("error_message", "droid_repair_no_wounds"); // It appears %TO has no wounds to repair.
			stringId.setTO(droid->getObjectID());
			creature->sendSystemMessage(stringId);
			return 0;
		}

		uint64 objectId = 0;

		parseModifier(arguments.toString(), objectId);

		ManagedReference<WoundPack*> woundPack = NULL;

		if (objectId != 0) {
			SceneObject* inventory = creature->getSlottedObject("inventory");

			if (inventory != NULL) {
				woundPack = inventory->getContainerObject(objectId).castTo<WoundPack*>();
			}
		} else {
			woundPack = findWoundPack(creature);
		}

		int mindCostNew = creature->calculateCostAdjustment(CreatureAttribute::FOCUS, mindCost);

		if (!canPerformSkill(creature, droid, woundPack, mindCostNew))
			return GENERALERROR;

		uint32 woundPower = woundPack->calculatePower(creature, droid, false);

		int woundHealed = droid->healWound(creature, attribute, woundPower);

		woundHealed = abs(woundHealed);

		sendWoundMessage(creature, droid, woundHealed);

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCostNew, false);

		deactivateWoundTreatment(creature);

		Locker locker(woundPack);
		woundPack->decreaseUseCount();

		doAnimations(creature, droid);

		checkForTef(creature, droid);

		return SUCCESS;
	}

};

#endif //HEALDROIDWOUNDCOMMAND_H_
