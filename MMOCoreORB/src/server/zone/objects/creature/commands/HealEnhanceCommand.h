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

#ifndef HEALENHANCECOMMAND_H_
#define HEALENHANCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/EnhancePack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/InjuryTreatmentTask.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/BuffAttribute.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/managers/collision/CollisionManager.h"

class HealEnhanceCommand : public QueueCommand {
	float mindCost;
	float range;
public:

	HealEnhanceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		
		mindCost = 150;
		range = 7;
	}

	void deactivateWoundTreatment(CreatureObject* creature) {
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

		StringIdChatParameter message("healing_response", "healing_response_59"); //You are now ready to heal more wounds or apply more enhancements.
		Reference<InjuryTreatmentTask*> task = new InjuryTreatmentTask(creature, message, "woundTreatment");
		creature->addPendingTask("woundTreatment", task, delay * 1000);
	}

	EnhancePack* findEnhancePack(CreatureObject* enhancer, uint8 attribute) {
		SceneObject* inventory = enhancer->getSlottedObject("inventory");

		int medicineUse = enhancer->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
				SceneObject* object = inventory->getContainerObject(i);

				if (!object->isTangibleObject())
					continue;

				TangibleObject* item = cast<TangibleObject*>( object);

				if (item->isPharmaceuticalObject()) {
					PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>( item);

					if (pharma->isEnhancePack()) {
						EnhancePack* enhancePack = cast<EnhancePack*>( pharma);

						if (enhancePack->getMedicineUseRequired() <= medicineUse && enhancePack->getAttribute() == attribute)
							return enhancePack;
					}
				}
			}
		}

		return NULL;
	}

	bool canPerformSkill(CreatureObject* enhancer, CreatureObject* patient, EnhancePack* enhancePack) {
		if (patient->isDead())
			return false;

		if (!enhancer->canTreatWounds()) {
			enhancer->sendSystemMessage("@healing_response:enhancement_must_wait"); //You must wait before you can heal wounds or apply enhancements again.
			return false;
		}

		if (enhancePack == NULL) {
			enhancer->sendSystemMessage("@healing_response:healing_response_60"); //No valid medicine found.
			return false;
		}

		int medicalRatingNotIncludingCityBonus = enhancer->getSkillMod("private_medical_rating") - enhancer->getSkillModOfType("private_medical_rating", SkillModManager::CITY);
		if (medicalRatingNotIncludingCityBonus <= 0) {
			enhancer->sendSystemMessage("@healing_response:must_be_near_droid"); //You must be in a hospital, at a campsite, or near a surgical droid to do that.
			return false;
		}else {
			// are we in a cantina? we have a private medical rating so either thats form a droid or camp or hospital
			ManagedReference<SceneObject*> root = enhancer->getRootParent();
			if (root != NULL && root->isStaticObject()) {
				uint32 gameObjectType = root->getGameObjectType();
				switch (gameObjectType) {
						case SceneObjectType::RECREATIONBUILDING:
						case SceneObjectType::HOTELBUILDING:
						case SceneObjectType::THEATERBUILDING:
							enhancer->sendSystemMessage("@healing_response:must_be_in_hospital"); // You must be in a hospital or at a campsite to do that.
							return false;
				}
			}
		}

		if (enhancer->isInCombat()) {
			enhancer->sendSystemMessage("You cannot do that while in Combat.");
			return false;
		}

		if (!patient->isPlayerCreature() && !(patient->isCreature() && patient->isPet())) {
			enhancer->sendSystemMessage("@healing_response:healing_response_77"); //Target must be a player or a creature pet in order to apply enhancements.
			return false;
		}

		if (patient->isInCombat()) {
			enhancer->sendSystemMessage("You cannot do that while your target is in Combat.");
			return false;
		}

		if (!patient->isHealableBy(enhancer)) {
			enhancer->sendSystemMessage("@healing:pvp_no_help"); //It would be unwise to help such a patient.
			return false;
		}

		if (enhancer->getHAM(CreatureAttribute::MIND) < mindCost) {
			enhancer->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		if (enhancer != patient && !CollisionManager::checkLineOfSight(enhancer, patient)) {
			enhancer->sendSystemMessage("@container_error_message:container18");
			return false;
		}

		return true;
	}

	void parseModifier(const String& modifier, uint8& attribute, uint64& objectId) {
		if (!modifier.isEmpty()) {
			StringTokenizer tokenizer(modifier);
			tokenizer.setDelimeter("|");

			String attributeName;

			tokenizer.getStringToken(attributeName);
			attribute = BuffAttribute::getAttribute(attributeName);

			if (tokenizer.hasMoreTokens()) {
				objectId = tokenizer.getLongToken();
			}
		} else {
			attribute = BuffAttribute::UNKNOWN;
			objectId = 0;
		}
	}

	void sendEnhanceMessage(CreatureObject* creature, CreatureObject* target, uint8 attribute, uint32 buffApplied) {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* enhancer = cast<CreatureObject*>( creature);
		CreatureObject* patient = cast<CreatureObject*>( target);

		String enhancerName = enhancer->getFirstName();
		String patientName;
		String attributeName = BuffAttribute::getName(attribute, true);

		if (target->isPlayerCreature())
			patientName = patient->getFirstName();
		else
			patientName = patient->getDisplayedName();

		if (BuffAttribute::isProtection(attribute))
			attributeName += " Resistance";

		StringBuffer msgPlayer, msgTarget, msgBuff;

		if (buffApplied == 0) {
			if (enhancer == patient) {
				msgPlayer << "You re-apply your ";
			} else {
				msgPlayer << "You re-apply " << patientName << "'s ";
				msgTarget << enhancerName << " re-applies your ";
			}
			msgBuff << attributeName << " enhancement.";
		} else {
			if (enhancer == patient) {
				msgPlayer << "You enhance your ";
			} else {
				msgPlayer << "You enhance " << patientName << "'s ";
				msgTarget << enhancerName << " enhances your ";
			}
			msgBuff << attributeName << " by " << buffApplied << ".";
		}

		msgPlayer << msgBuff.toString();
		enhancer->sendSystemMessage(msgPlayer.toString());

		if (enhancer != patient) {
			msgTarget << msgBuff.toString();
			patient->sendSystemMessage(msgTarget.toString());
		}
	}

	void awardXp(CreatureObject* creature, const String& type, int power) {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		int amount = (int)round((float)power * 2.5f);

		if (amount <= 0)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(player, type, amount, true);
	}

	void doAnimations(CreatureObject* enhancer, CreatureObject* patient) {
		patient->playEffect("clienteffect/healing_healenhance.cef", "");

		if (enhancer == patient)
			enhancer->doAnimation("heal_self");
		else
			enhancer->doAnimation("heal_other");
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		CreatureObject* enhancer = creature;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (!object->isCreatureObject()) {
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());
 
				if (tangibleObject != NULL && tangibleObject->isAttackableBy(creature)) {
					object = creature;
				} else {
					creature->sendSystemMessage("@healing_response:healing_response_77"); //Target must be a player or a creature pet in order to apply enhancements.
					return GENERALERROR;
				}
			}
		} else {
			object = creature;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>( object.get());

		uint8 attribute = BuffAttribute::UNKNOWN;
		uint64 objectId = 0;

		if (!targetCreature->isInRange(creature, range + targetCreature->getTemplateRadius() + creature->getTemplateRadius()))
			return TOOFAR;

		parseModifier(arguments.toString(), attribute, objectId);

		if (attribute == BuffAttribute::UNKNOWN) {
			enhancer->sendSystemMessage("@healing_response:healing_response_75"); //You must specify a valid attribute.
			return GENERALERROR;
		}

		ManagedReference<EnhancePack*> enhancePack = NULL;

		if (objectId != 0) {
			SceneObject* inventory = creature->getSlottedObject("inventory");

			if (inventory != NULL) {
				enhancePack = inventory->getContainerObject(objectId).castTo<EnhancePack*>();
			}

			if (enhancePack == NULL) {
				enhancer->sendSystemMessage("@healing_response:healing_response_76"); // That item does not provide attribute enhancement.
				return false;
			}

			int medicineUse = enhancer->getSkillMod("healing_ability");

			if (enhancePack->getMedicineUseRequired() > medicineUse) {
				enhancer->sendSystemMessage("@error_message:insufficient_skill"); // You lack the skill to use this item.
				return false;
			}

			if (enhancePack->getAttribute() != attribute) {
				attribute = enhancePack->getAttribute();
			}
		} else {
			enhancePack = findEnhancePack(creature, attribute);
		}

		CreatureObject* patient = cast<CreatureObject*>( targetCreature);

		Locker clocker(patient, creature);

		if (patient->isDead() || patient->isRidingMount())
			patient = enhancer;

		if (!canPerformSkill(enhancer, patient, enhancePack))
			return GENERALERROR;

		uint32 currentBuff = 0;
		uint32 buffcrc = BuffCRC::getMedicalBuff(attribute);

		if (patient->hasBuff(buffcrc)) {
			Buff* existingbuff = patient->getBuff(buffcrc);

			if (existingbuff != NULL){

				if (BuffAttribute::isProtection(attribute))
					currentBuff = existingbuff->getSkillModifierValue(BuffAttribute::getProtectionString(attribute));
				else
					currentBuff = existingbuff->getAttributeModifierValue(attribute);
			}
		}

		//Applies battle fatigue
		uint32 buffPower = 0;
		if (BuffAttribute::isProtection(attribute)) {  // If it's a protection enhancement, wound treatment has no effect
			buffPower = enhancePack->getEffectiveness();
			buffPower = buffPower * (1 - patient->calculateBFRatio()) * (1 - enhancer->calculateBFRatio());
		} else
			buffPower = enhancePack->calculatePower(enhancer, patient);

		if (buffPower < currentBuff) {
			if (patient == enhancer)
				enhancer->sendSystemMessage("Your current enhancements are of greater power and cannot be re-applied.");
			else
				enhancer->sendSystemMessage("Your target's current enhancements are of greater power and cannot be re-applied.");

			return 0;
		}

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();

		uint32 amountEnhanced = playerManager->healEnhance(enhancer, patient, attribute, buffPower, enhancePack->getDuration());

		if (creature->isPlayerCreature() && targetCreature->isPlayerCreature()) {
			playerManager->sendBattleFatigueMessage(creature, targetCreature);
		}

		sendEnhanceMessage(enhancer, patient, attribute, amountEnhanced);

		enhancer->inflictDamage(enhancer, CreatureAttribute::MIND, mindCost, false);

		deactivateWoundTreatment(enhancer);

		if (enhancePack != NULL)
			enhancePack->decreaseUseCount();

		if (patient != enhancer)
			awardXp(enhancer, "medical", amountEnhanced); //No experience for healing yourself.

		doAnimations(enhancer, patient);

		creature->notifyObservers(ObserverEventType::MEDPACKUSED);

		return SUCCESS;
	}

};

#endif //HEALENHANCECOMMAND_H_
