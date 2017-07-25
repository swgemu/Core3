/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REVIVEPLAYERCOMMAND_H_
#define REVIVEPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/RevivePack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"

class RevivePlayerCommand : public QueueCommand {
	float mindCost;
	float range;
public:

	RevivePlayerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

		mindCost = 200;
		range = 7;
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, RevivePack* revivePack, int mindCostNew) const {
		if (!creatureTarget->isDead()) {
			creature->sendSystemMessage("@healing_response:healing_response_a4"); //Your target does not require resuscitation!
			return 0;
		}

		if (revivePack == NULL) {
			creature->sendSystemMessage("@healing_response:cannot_resuscitate_kit"); //You cannot resuscitate someone without a resuscitation kit!
			return false;
		}

		if (!creatureTarget->isResuscitable()) {
			creature->sendSystemMessage("@healing_response:too_dead_to_resuscitate"); //Your target has been dead too long. There is no hope of resuscitation.
			return false;
		}

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");  //It would be unwise to help such a patient.
			return false;
		}

		ManagedReference<GroupObject*> group = creature->getGroup();

		if (group == NULL || !group->hasMember(creatureTarget)) {
			if (creature->isPlayerCreature()) {
				CreatureObject* player = cast<CreatureObject*>(creature);
				CreatureObject* consentOwner = cast<CreatureObject*>( creatureTarget);

				PlayerObject* ghost = consentOwner->getPlayerObject();

				if (!ghost->hasInConsentList(player->getFirstName().toLowerCase())) {
					if ((consentOwner->getWeapon() != NULL && consentOwner->getWeapon()->isJediWeapon()) || consentOwner->hasSkill("force_title_jedi_rank_02")) {
						creature->sendSystemMessage("@healing_response:jedi_must_consent"); // You must have consent from a jedi resuscitation target!
						return false;
					} else {
						creature->sendSystemMessage("@healing_response:must_be_grouped"); //You must be grouped with or have consent from your resuscitation target!
						return false;
					}
				}

			} else {
				return false;
			}
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCostNew) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		return true;
	}

	void parseModifier(const String& modifier, uint64& objectId) const {
		if (!modifier.isEmpty())
			objectId = Long::valueOf(modifier);
		else
			objectId = 0;
	}

	void awardXp(CreatureObject* creature, const String& type, int power) const {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		int amount = (int)round((float)power * 0.5f);

		if (amount <= 0)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(player, type, amount, true);
	}

	void applyDebuff(CreatureObject* creature) const {
		// Apply grogginess debuff
		ManagedReference<PrivateBuff *> debuff = new PrivateBuff(creature, STRING_HASHCODE("private_groggy_debuff"), 60, BuffType::JEDI);
		Locker locker(debuff);

		for(int i=0; i<CreatureAttribute::ARRAYSIZE; i++)
			debuff->setAttributeModifier(i, -100);

		creature->sendSystemMessage("Your grogginess will expire in 60.0 seconds.");
		// TODO: Find potential end message for groggy debuff

		creature->addBuff(debuff);
	}

	RevivePack* findRevivePack(CreatureObject* creature) const {
		SceneObject* inventory = creature->getSlottedObject("inventory");
		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
				SceneObject* object = inventory->getContainerObject(i);

				if (!object->isPharmaceuticalObject())
					continue;

				PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>(object);

				if (pharma->isRevivePack()) {
					RevivePack* revivePack = cast<RevivePack*>(pharma);

					if (revivePack->getMedicineUseRequired() <= medicineUse)
						return revivePack;
				}
			}
		}

		return NULL;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) const {
		creatureTarget->playEffect("clienteffect/healing_healwound.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
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
					creature->sendSystemMessage("@healing_response:healing_response_a2"); //You cannot apply resuscitation medication without a valid target!
					return GENERALERROR;
				}
			}
		} else {
			object = creature;
		}

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		if (!creatureTarget->isPlayerCreature()) {
			creature->sendSystemMessage("@healing_response:healing_response_a3"); // You cannot apply resuscitation medication to a non-player entity!
			return GENERALERROR;
		}

		if (creatureTarget == creature) {
			creature->sendSystemMessage("@error_message:target_self_disallowed"); //You cannot target yourself with this command.
			return GENERALERROR;
		}

		if(!checkDistance(creature, creatureTarget, range))
			return TOOFAR;

		uint64 objectId = 0;

		parseModifier(arguments.toString(), objectId);

		ManagedReference<RevivePack*> revivePack = NULL;

		SceneObject* inventory = creature->getSlottedObject("inventory");

		if (inventory != NULL) {
			revivePack = inventory->getContainerObject(objectId).castTo<RevivePack*>();
		}

		if (revivePack == NULL)
			revivePack = findRevivePack(creature);

		int mindCostNew = creature->calculateCostAdjustment(CreatureAttribute::FOCUS, mindCost);

		if (!canPerformSkill(creature, creatureTarget, revivePack, mindCostNew))
			return 0;

		int healthToHeal = Math::max(1, (int) round(revivePack->getHealthHealed()));
		int actionToHeal = Math::max(1, (int) round(revivePack->getActionHealed()));
		int mindToHeal = Math::max(1, (int) round(revivePack->getMindHealed()));

		int healedHealth = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, healthToHeal);
		int healedAction = creatureTarget->healDamage(creature, CreatureAttribute::ACTION, actionToHeal);
		int healedMind = creatureTarget->healDamage(creature, CreatureAttribute::MIND, mindToHeal);

		creatureTarget->setPosture(CreaturePosture::UPRIGHT);
		
		creatureTarget->removeFeignedDeath();

		int healedHealthWounds = creatureTarget->healWound(creature, CreatureAttribute::HEALTH, (int) (round(revivePack->getHealthWoundHealed())));
		int healedActionWounds = creatureTarget->healWound(creature, CreatureAttribute::ACTION, (int) (round(revivePack->getActionWoundHealed())));
		int healedMindWounds = creatureTarget->healWound(creature, CreatureAttribute::MIND, (int) (round(revivePack->getMindWoundHealed())));

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCostNew, false);

		if (revivePack != NULL) {
			Locker locker(revivePack);

			revivePack->decreaseUseCount();
		}

		int xpAmount = healedHealth + healedAction + healedMind + healedHealthWounds + healedActionWounds + healedMindWounds + 250;

		awardXp(creature, "medical", xpAmount);

		doAnimations(creature, creatureTarget);

		checkForTef(creature, creatureTarget);

		applyDebuff(creatureTarget);

		creatureTarget->notifyObservers(ObserverEventType::CREATUREREVIVED, creature, 0);

		return SUCCESS;
	}

};

#endif //REVIVEPLAYERCOMMAND_H_
