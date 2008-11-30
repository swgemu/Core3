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

#ifndef HEALENHANCETARGETSKILL_H_
#define HEALENHANCETARGETSKILL_H_

#include "../TargetSkill.h"

#include "../../../tangible/pharmaceutical/PharmaceuticalImplementation.h"
#include "../../../tangible/pharmaceutical/EnhancePackImplementation.h"

#include "../../../../managers/player/PlayerManager.h"

class HealEnhanceTargetSkill : public TargetSkill {
protected:
	String effectName;
	int mindCost;

public:
	HealEnhanceTargetSkill(const String& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
		effectName = aname;
		mindCost = 0;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!effectName.isEmpty())
			creatureTarget->playEffect(effectName, "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, EnhancePack* enhancePack) {
		if (!creature->canTreatWounds()) {
			creature->sendSystemMessage("healing_response", "enhancement_must_wait"); //You must wait before you can heal wounds or apply enhancements again.
			return false;
		}

		if (enhancePack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
			return false;
		}

		if (creature->getMedicalFacilityRating() <= 0) {
			creature->sendSystemMessage("healing_response", "must_be_near_droid"); //You must be in a hospital, at a campsite, or near a surgical droid to do that.
			return false;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot do that while Meditating.");
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

		if (creature->isInCombat()) {
			creature->sendSystemMessage("You cannot do that while in Combat.");
			return false;
		}

		if (creatureTarget->isInCombat()) {
			creature->sendSystemMessage("You cannot do that while your target is in Combat.");
			return false;
		}

		if (creatureTarget->isOvert() && creatureTarget->getFaction() != creature->getFaction()) {
			creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
			return false;
		}

		if (creature->getMind() < abs(mindCost)) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
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
			attribute = CreatureAttribute::getAttribute(attributeName);

			if (tokenizer.hasMoreTokens())
				objectId = tokenizer.getLongToken();
		} else {
			attribute = CreatureAttribute::UNKNOWN;
			objectId = 0;
		}
	}

	EnhancePack* findEnhancePack(CreatureObject* creature, uint8 attribute) {
		Inventory* inventory = creature->getInventory();

		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->objectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				if (item->isPharmaceutical()) {
					Pharmaceutical* pharma = (Pharmaceutical*) item;

					if (pharma->isEnhancePack()) {
						EnhancePack* enhancePack = (EnhancePack*) pharma;

						if (enhancePack->getMedicineUseRequired() <= medicineUse && enhancePack->getAttribute() == attribute)
							return enhancePack;
					}
				}
			}
		}

		return NULL;
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			creature->sendSystemMessage("healing_response", "healing_response_77"); //Target must be a player or a creature pet in order to apply enhancements.
			return 0;
		}

		uint8 attribute = CreatureAttribute::UNKNOWN;
		uint64 objectId = 0;

		parseModifier(modifier, attribute, objectId);

		if (attribute == CreatureAttribute::UNKNOWN) {
			creature->sendSystemMessage("healing_response", "healing_response_75"); //You must specify a valid attribute.
			return 0;
		}

		EnhancePack* enhancePack = (EnhancePack*) creature->getInventoryItem(objectId);

		if (enhancePack == NULL)
			enhancePack = findEnhancePack(creature, attribute);

		CreatureObject* creatureTarget = (CreatureObject*) target;

		if (creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted())
			creatureTarget = creature;

		if (!canPerformSkill(creature, creatureTarget, enhancePack))
			return 0;


		//Calculate current buff
		int currentPower = 0;
		uint32 currentBuffCRC = enhancePack->getBuffCRC();

		if (creature->hasBuff(currentBuffCRC)) {
			BuffObject* currentBuffObj = creature->getBuffObject(currentBuffCRC);
			Buff* currentBuff = currentBuffObj->getBuff();

			currentPower = getBuffPower(currentBuff, currentBuffCRC);

			currentBuffObj->finalize();
		}

		int buffPower = enhancePack->calculatePower(creature);
		int predictedPower = buffPower - (int)round(((float)buffPower * creatureTarget->calculateBFRatio()));

		if (currentPower > predictedPower) {
			if (creatureTarget == creature) {
				creature->sendSystemMessage("Your current enhancements are of greater power and cannot be replaced.");
			} else {
				creature->sendSystemMessage("Your target's current enhancements are of greater power and cannot be replaced.");
			}
			return 0;
		}

		int buffApplied = creature->healEnhance(creatureTarget, buffPower, enhancePack->getDuration(), attribute);

		if (creature->isPlayer())
			((Player*)creature)->sendBattleFatigueMessage(creatureTarget);

		sendEnhanceMessage(creature, creatureTarget, attribute, buffApplied, currentPower);

		creature->changeMindBar(mindCost);

		creature->deactivateWoundTreatment();

		if (enhancePack != NULL)
			enhancePack->useCharge((Player*) creature);

		if (creatureTarget != creature)
			awardXp(creature, "medical", buffApplied); //No experience for healing yourself.

		doAnimations(creature, creatureTarget);

		return 0;
	}

	void awardXp(CreatureObject* creature, String type, int power) {
		Player* player = (Player*) creature;

		int amount = (int)round((float)power * 0.5f);

		if (amount <= 0)
			return;

		player->addXp(type, amount, true);

		// Capitalize first letter.
		type = Character::toUpperCase(type.charAt(0)) +
			type.subString(1, type.length()).toLowerCase();

		StringBuffer msgExperience;
		msgExperience << "You receive " << amount << " points of " << type << " experience.";
		player->sendSystemMessage(msgExperience.toString());
	}

	void sendEnhanceMessage(CreatureObject* creature, CreatureObject* creatureTarget, uint8 attribute, int buffApplied, int currentPower) {
		String creatureName = creature->getCharacterName().toString();
		String creatureTargetName = creatureTarget->getCharacterName().toString();
		String attributeName = CreatureAttribute::getName(attribute, true);

		StringBuffer msgPlayer, msgTarget, msgBuff;

		if (buffApplied == currentPower) {
			if (creature == creatureTarget) {
				msgPlayer << "You re-apply your ";
			} else {
				msgPlayer << "You re-apply " << creatureTargetName << "'s ";
				msgTarget << creatureName << " re-applies your ";
			}
			msgBuff << attributeName << " enhancement.";
		} else {
			if (creature == creatureTarget) {
				msgPlayer << "You enhance your ";
			} else {
				msgPlayer << "You enhance " << creatureTargetName << "'s ";
				msgTarget << creatureName << " enhances your ";
			}
			msgBuff << attributeName << " by " << buffApplied << ".";
		}

		msgPlayer << msgBuff.toString();
		creature->sendSystemMessage(msgPlayer.toString());

		if (creature != creatureTarget) {
			msgTarget << msgBuff.toString();
			creatureTarget->sendSystemMessage(msgTarget.toString());
		}
	}

	int getBuffPower(Buff* buff, uint32 buffCRC) {
		switch (buffCRC) {
		case BuffCRC::MEDICAL_ENHANCE_ACTION:
			return buff->getActionBuff();
			break;
		case BuffCRC::MEDICAL_ENHANCE_CONSTITUTION:
			return buff->getConstitutionBuff();
			break;
		case BuffCRC::MEDICAL_ENHANCE_STRENGTH:
			return buff->getStrengthBuff();
			break;
		case BuffCRC::MEDICAL_ENHANCE_QUICKNESS:
			return buff->getQuicknessBuff();
			break;
		case BuffCRC::MEDICAL_ENHANCE_STAMINA:
			return buff->getStaminaBuff();
			break;
		case BuffCRC::MEDICAL_ENHANCE_HEALTH:
		default:
			return buff->getHealthBuff();
			break;
		}
	}

	float calculateSpeed(CreatureObject* creature) {
		return 0.0f; //Handled by event
	}

	virtual bool calculateCost(CreatureObject* creature) {
		return true;
	}

	void setEffectName(const String& name) {
		effectName = name;
	}

	void setMindCost(int cost) {
		mindCost = cost;
	}

};

#endif /*HEALENHANCETARGETSKILL_H_*/
