/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALWOUNDCOMMAND_H_
#define HEALWOUNDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/WoundPack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/InjuryTreatmentTask.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/managers/collision/CollisionManager.h"

class HealWoundCommand : public QueueCommand {
	int mindCost;
	float range;
public:

	HealWoundCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

		mindCost = 50;
		range = 6;
	}

	void deactivateWoundTreatment(CreatureObject* creature) const {
		float modSkill = (float)creature->getSkillMod("healing_wound_speed");

		int delay = (int)round((modSkill * -(2.0f / 25.0f)) + 20.0f);

		if (creature->hasBuff(BuffCRC::FOOD_HEAL_RECOVERY)) {
			DelayedBuff* buff = cast<DelayedBuff*>( creature->getBuff(BuffCRC::FOOD_HEAL_RECOVERY));

			if (buff != NULL) {
				float percent = buff->getSkillModifierValue("heal_recovery");

				delay = round(delay * (100.0f - percent) / 100.0f);
			}
		}

		//Force the delay to be at least 3 seconds.
		delay = (delay < 3) ? 3 : delay;

		StringIdChatParameter message("healing_response", "healing_response_59");
		Reference<InjuryTreatmentTask*> task = new InjuryTreatmentTask(creature, message, "woundTreatment");
		creature->addPendingTask("woundTreatment", task, delay * 1000);
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) const {
		creatureTarget->playEffect("clienteffect/healing_healwound.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	void awardXp(CreatureObject* creature, const String& type, int power) const {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		int amount = (int)round((float)power * 2.5f);

		if (amount <= 0)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(player, type, amount, true);
	}

	void sendWoundMessage(CreatureObject* object, CreatureObject* target, uint8 attribute, uint32 woundsHealed) const {
		if (!object->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>(  target);

		String poolName = CreatureAttribute::getName(attribute);

		StringBuffer msgPlayer, msgTarget, msgTail;

		msgTail << woundsHealed << " " << poolName << " wound damage.";

		if (creature == creatureTarget) {
			msgTarget << "You heal yourself for " << msgTail.toString();
			creatureTarget->sendSystemMessage(msgTarget.toString());
		} else if (creatureTarget->isPlayerCreature()) {
			msgPlayer << "You heal " << creatureTarget->getFirstName() << " for " << msgTail.toString();
			msgTarget << creature->getFirstName() << " heals you for " << msgTail.toString();

			creature->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());
		} else {
			msgPlayer << "You heal " << creatureTarget->getDisplayedName() << " for " << msgTail.toString();
			creature->sendSystemMessage(msgPlayer.toString());
		}
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, WoundPack* woundPack, int mindCostNew) const {
		if (!creature->canTreatWounds()) {
			creature->sendSystemMessage("@healing_response:enhancement_must_wait"); //You must wait before you can heal wounds or apply enhancements again.
			return false;
		}

		if (woundPack == NULL) {
			creature->sendSystemMessage("@healing_response:healing_response_60"); //No valid medicine found.
			return false;
		}

		int medicalRatingNotIncludingCityBonus = creature->getSkillMod("private_medical_rating") - creature->getSkillModOfType("private_medical_rating", SkillModManager::CITY);
		if (medicalRatingNotIncludingCityBonus <= 0) {
			creature->sendSystemMessage("@healing_response:must_be_near_droid"); //You must be in a hospital, at a campsite, or near a surgical droid to do that.
			return false;
		} else {
			// are we in a cantina? we have a private medical rating so either thats form a droid or camp or hospital
			ManagedReference<SceneObject*> root = creature->getRootParent();
			if (root != NULL && root->isClientObject()) {
				uint32 gameObjectType = root->getGameObjectType();
				switch (gameObjectType) {
						case SceneObjectType::RECREATIONBUILDING:
						case SceneObjectType::HOTELBUILDING:
						case SceneObjectType::THEATERBUILDING:
							creature->sendSystemMessage("@healing_response:must_be_in_hospital"); // You must be in a hospital or at a campsite to do that.
							return false;
				}
			}
		}

		if (creature->isInCombat()) {
			creature->sendSystemMessage("You cannot heal your own wounds while still in Combat.");
			return false;
		}

		if (creatureTarget->isInCombat()) {
			creature->sendSystemMessage("You cannot heal your target's wounds while they are in Combat.");
			return false;
		}

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");  //It would be unwise to help such a patient.
			return false;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCostNew) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			creature->sendSystemMessage("@healing:no_line_of_sight"); // You cannot see your target.
			return false;
		}

		return true;
	}

	void parseModifier(const String& modifier, uint8& attribute, uint64& objectId) const {
		if (!modifier.isEmpty()) {
			StringTokenizer tokenizer(modifier);
			tokenizer.setDelimeter("|");

			String attributeName;

			tokenizer.getStringToken(attributeName);

			attribute = CreatureAttribute::getAttribute(attributeName);

			if (tokenizer.hasMoreTokens())
				objectId = tokenizer.getLongToken();
		} else {
			attribute = CreatureAttribute::UNKNOWN;
			objectId = 0;
		}
	}

	uint8 findAttribute(CreatureObject* creature, uint8 startAttribute = 0) const {
		for (int i = startAttribute; i < 9; ++i) {
			int wounds = creature->getWounds(i);

			if (wounds != 0)
				return i;
		}

		return CreatureAttribute::UNKNOWN;
	}


	WoundPack* findWoundPack(CreatureObject* creature, uint8 attribute) const {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				SceneObject* object = inventory->getContainerObject(i);

				if (!object->isPharmaceuticalObject())
					continue;

				PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>(object);

				if (pharma->isWoundPack()) {
					WoundPack* woundPack = cast<WoundPack*>(pharma);

					if (woundPack->getMedicineUseRequired() <= medicineUse && woundPack->getAttribute() == attribute)
						return woundPack;
				}
			}
		}

		return NULL;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (!object->isCreatureObject()) {
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());

				if (tangibleObject != NULL && tangibleObject->isAttackableBy(creature)) {
					object = creature;
				} else {
					creature->sendSystemMessage("Target must be a player or a creature pet in order to heal wound.");
					return GENERALERROR;
				}
			}
		} else {
			object = creature;
		}

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		if ((creatureTarget->isAiAgent() && !creatureTarget->isPet()) || creatureTarget->isDroidObject() || creatureTarget->isVehicleObject() || creatureTarget->isDead() || creatureTarget->isRidingMount() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;

		if(!checkDistance(creature, creatureTarget, range))
			return TOOFAR;

		uint8 attribute = CreatureAttribute::UNKNOWN;
		uint64 objectId = 0;

		parseModifier(arguments.toString(), attribute, objectId);

		ManagedReference<WoundPack*> woundPack = NULL;

		if (objectId != 0) {
			SceneObject* inventory = creature->getSlottedObject("inventory");

			if (inventory != NULL) {
				woundPack = inventory->getContainerObject(objectId).castTo<WoundPack*>();
			}

			if (woundPack == NULL) {
				creature->sendSystemMessage("@healing_response:healing_response_66"); // That item does not heal wounds.
				return false;
			}

			int medicineUse = creature->getSkillMod("healing_ability");

			if (woundPack->getMedicineUseRequired() > medicineUse) {
				creature->sendSystemMessage("@error_message:insufficient_skill"); // You lack the skill to use this item.
				return false;
			}

			if (woundPack->getAttribute() != attribute) {
				attribute = woundPack->getAttribute();
			}
		} else {
			int searchAttribute = -1;

			while (woundPack == NULL) {
				searchAttribute += 1;
				searchAttribute = findAttribute(creatureTarget, searchAttribute);

				if (searchAttribute == CreatureAttribute::UNKNOWN) {
					creature->sendSystemMessage("@healing_response:healing_response_60"); //No valid medicine found.
					return GENERALERROR;
				}

				woundPack = findWoundPack(creature, searchAttribute);
			}

			attribute = searchAttribute;
		}

		int mindCostNew = creature->calculateCostAdjustment(CreatureAttribute::FOCUS, mindCost);

		if (!canPerformSkill(creature, creatureTarget, woundPack, mindCostNew))
			return GENERALERROR;

		if (creatureTarget->getWounds(attribute) == 0) {
			if (creatureTarget == creature) {
				creature->sendSystemMessage("@healing_response:healing_response_67"); //You have no wounds of that type to heal.
			} else if (creatureTarget->isPlayerCreature()){
				//TODO: Patch the tre later to include a %NT.
				StringBuffer message;
				message << creatureTarget->getFirstName() << " has no wounds of that type to heal.";
				creature->sendSystemMessage(message.toString());
			} else {
				StringBuffer message;
				message << creatureTarget->getDisplayedName() << " has no wounds of that type to heal.";
				creature->sendSystemMessage(message.toString());
			}

			return 0;
		}

		uint32 woundPower = woundPack->calculatePower(creature, creatureTarget);

		int woundHealed = creatureTarget->healWound(creature, attribute, woundPower);

		woundHealed = abs(woundHealed);

		if (creature->isPlayerCreature()) {
			PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
			playerManager->sendBattleFatigueMessage(creature, creatureTarget);
		}

		sendWoundMessage(creature, creatureTarget, attribute, woundHealed);

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCostNew, false);

		deactivateWoundTreatment(creature);

		Locker locker(woundPack);
		woundPack->decreaseUseCount();

		if (creatureTarget != creature && !creatureTarget->isPet())
			awardXp(creature, "medical", woundHealed); //No experience for healing yourself or pets.

		doAnimations(creature, creatureTarget);

		creature->notifyObservers(ObserverEventType::MEDPACKUSED);

		checkForTef(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif //HEALWOUNDCOMMAND_H_
