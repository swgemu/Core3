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

	void doAnimations(CreatureObject* enhancer, CreatureObject* patient) {
		if (!effectName.isEmpty())
			patient->playEffect(effectName, "");

		if (enhancer == patient)
			enhancer->doAnimation("heal_self");
		else
			enhancer->doAnimation("heal_other");
	}

	bool canPerformSkill(CreatureObject* enhancer, CreatureObject* patient, EnhancePack* enhancePack) {
		if (!enhancer->canTreatWounds()) {
			enhancer->sendSystemMessage("healing_response", "enhancement_must_wait"); //You must wait before you can heal wounds or apply enhancements again.
			return false;
		}

		if (enhancePack == NULL) {
			enhancer->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
			return false;
		}

		if (enhancer->getMedicalFacilityRating() <= 0) {
			enhancer->sendSystemMessage("healing_response", "must_be_near_droid"); //You must be in a hospital, at a campsite, or near a surgical droid to do that.
			return false;
		}

		if (enhancer->isProne()) {
			enhancer->sendSystemMessage("You cannot Heal Enhance while prone.");
			return false;
		}

		if (enhancer->isMeditating()) {
			enhancer->sendSystemMessage("You cannot Heal Enhance while Meditating.");
			return false;
		}

		if (enhancer->isRidingCreature()) {
			enhancer->sendSystemMessage("You cannot do that while Riding a Creature.");
			return false;
		}

		if (enhancer->isMounted()) {
			enhancer->sendSystemMessage("You cannot do that while Driving a Vehicle.");
			return false;
		}

		if (enhancer->isInCombat()) {
			enhancer->sendSystemMessage("You cannot do that while in Combat.");
			return false;
		}

		if (patient->isInCombat()) {
			enhancer->sendSystemMessage("You cannot do that while your target is in Combat.");
			return false;
		}

		if (patient->isOvert() && patient->getFaction() != enhancer->getFaction()) {
			enhancer->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
			return false;
		}

		if (enhancer->getMind() < abs(mindCost)) {
			enhancer->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
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

			if (tokenizer.hasMoreTokens())
				objectId = tokenizer.getLongToken();
		} else {
			attribute = BuffAttribute::UNKNOWN;
			objectId = 0;
		}
	}

	EnhancePack* findEnhancePack(CreatureObject* enhancer, uint8 attribute) {
		Inventory* inventory = enhancer->getInventory();

		int medicineUse = enhancer->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
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

	int doSkill(CreatureObject* enhancer, SceneObject* target, const String& modifier, bool doAnimation = true) {
		if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			enhancer->sendSystemMessage("healing_response", "healing_response_77"); //Target must be a player or a creature pet in order to apply enhancements.
			return 0;
		}

		uint8 attribute = BuffAttribute::UNKNOWN;
		uint64 objectId = 0;

		parseModifier(modifier, attribute, objectId);

		if (attribute == BuffAttribute::UNKNOWN) {
			enhancer->sendSystemMessage("healing_response", "healing_response_75"); //You must specify a valid attribute.
			return 0;
		}

		ManagedReference<EnhancePack> enhancePack = (EnhancePack*) enhancer->getInventoryItem(objectId);

		if (enhancePack == NULL)
			enhancePack = findEnhancePack(enhancer, attribute);

		CreatureObject* patient = (CreatureObject*) target;

		if (patient->isDead() || patient->isRidingCreature() || patient->isMounted())
			patient = enhancer;

		if (!canPerformSkill(enhancer, patient, enhancePack))
			return 0;

		uint32 currentBuff = 0;
		uint32 buffCRC = BuffCRC::getMedicalBuff(attribute);

		if (patient->hasBuff(buffCRC)) {
			BuffObject* bo = patient->getBuffObject(buffCRC);
			currentBuff = bo->getBuff()->getAttributeBuff(attribute);
			bo->finalize();
		}

		//Applies battle fatigue
		uint32 buffPower = enhancePack->calculatePower(enhancer, patient);

		if (buffPower < currentBuff) {
			if (patient == enhancer)
				enhancer->sendSystemMessage("Your current enhancements are of greater power and cannot be re-applied.");
			else
				enhancer->sendSystemMessage("Your target's current enhancements are of greater power and cannot be re-applied.");

			return 0;
		}

		uint32 amountEnhanced = enhancer->healEnhance(patient, attribute, buffPower, enhancePack->getDuration());

		if (enhancer->isPlayer())
			((Player*)enhancer)->sendBattleFatigueMessage(patient);

		sendEnhanceMessage(enhancer, patient, attribute, amountEnhanced);

		enhancer->changeMindBar(mindCost);

		enhancer->deactivateWoundTreatment();

		if (enhancePack != NULL)
			enhancePack->useCharge((Player*) enhancer);

		if (patient != enhancer)
			awardXp(enhancer, "medical", amountEnhanced); //No experience for healing yourself.

		doAnimations(enhancer, patient);

		return 0;
	}

	void awardXp(CreatureObject* enhancer, String type, int power) {
		Player* player = (Player*) enhancer;

		int amount = (int)round((float)power * 0.5f);

		if (amount <= 0)
			return;

		player->addXp(type, amount, true);
	}

	void sendEnhanceMessage(CreatureObject* enhancer, CreatureObject* patient, uint8 attribute, uint32 buffApplied) {
		String enhancerName = enhancer->getCharacterName().toString();
		String patientName = patient->getCharacterName().toString();
		String attributeName = BuffAttribute::getName(attribute, true);

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

	float getSpeed() {
		return 1.0f; //Handled by event
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
