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

#ifndef HEALWOUNDTARGETSKILL_H_
#define HEALWOUNDTARGETSKILL_H_

#include "../TargetSkill.h"
#include "../../../tangible/pharmaceutical/PharmaceuticalImplementation.h"
#include "../../../tangible/pharmaceutical/WoundPackImplementation.h"

#include "../../../../managers/player/PlayerManager.h"

class HealWoundTargetSkill : public TargetSkill {
protected:
	string effectName;
	int mindCost;

public:
	HealWoundTargetSkill(const string& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
		effectName = aname;
		mindCost = 0;

	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (effectName.size() != 0)
			creatureTarget->playEffect(effectName, "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	WoundPack* findMedpack(CreatureObject* creature, const string& modifier, int& poolAffected) {
		WoundPack* woundPack = NULL;
		int medicineUse = creature->getSkillMod("healing_ability");

		if (!modifier.empty()) {
			StringTokenizer tokenizer(modifier);
			string poolName;
			uint64 objectid = 0;

			tokenizer.setDelimeter("|");

			tokenizer.getStringToken(poolName);

			poolAffected = PharmaceuticalImplementation::getPoolFromName(poolName);

			if (tokenizer.hasMoreTokens())
				objectid = tokenizer.getLongToken();

			if (objectid > 0) {
				SceneObject* invObj = creature->getInventoryItem(objectid);

				if (invObj != NULL && invObj->isTangible()) {
					TangibleObject* tano = (TangibleObject*) invObj;

					if (tano->isPharmaceutical()) {
						Pharmaceutical* pharm = (Pharmaceutical*) tano;

						if (pharm->isWoundPack()) {
							woundPack = (WoundPack*) pharm;

							if (woundPack->getMedicineUseRequired() <= medicineUse)
								return woundPack;
						}
					}
				}
			}
		} else {
			poolAffected = PharmaceuticalImplementation::UNKNOWN;
			return NULL;
		}

		Inventory* inventory = creature->getInventory();

		for (int i=0; i<inventory->objectsSize(); i++) {
			TangibleObject* item = (TangibleObject*) inventory->getObject(i);

			if (item != NULL && item->isPharmaceutical()) {
				woundPack = (WoundPack*) item;

				if (woundPack->isWoundPack()
						&& woundPack->getMedicineUseRequired() <= medicineUse
						&& woundPack->getPoolAffected() == poolAffected)
					return woundPack;
			}
		}

		return NULL; //Never found a stimpack
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const string& modifier, bool doAnimation = true) {
		CreatureObject* creatureTarget;
		WoundPack* woundPack = NULL;

		int poolAffected = 0;
		int woundPower = 0;
		int woundsHealed = 0;
		int battleFatigue = 0;
		int modEnvironment = creature->getMedicalFacilityRating();

		woundPack = findMedpack(creature, modifier, poolAffected);

		if (target->isPlayer() || target->isNonPlayerCreature()) {
			creatureTarget = (CreatureObject*) target;
		} else {
			creature->sendSystemMessage("healing_response", "target_must_be_healable"); //Target must be a player or a creature pet in order to tend wounds.
			return 0;
		}

		if (creatureTarget != creature
				&& (creatureTarget->isDead()
						|| creatureTarget->isRidingCreature()
						|| creatureTarget->isMounted())) {
			//If the target is dead or mounted, then make self the target.
			creatureTarget = creature;
		}

		if (!creature->canTreatWounds()) {
			creature->sendSystemMessage("healing_response", "enhancement_must_wait"); //You must wait before you can heal wounds or apply enhancements again.
			return 0;
		}

		if (poolAffected == PharmaceuticalImplementation::UNKNOWN) {
			creature->sendSystemMessage("healing_response", "healing_response_75"); //You must specify a valid attribute.
			return 0;
		}

		if (woundPack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
			return 0;
		}

		if (modEnvironment <= 0) {
			creature->sendSystemMessage("healing_response", "must_be_near_droid"); //You must be in a hospital, at a campsite, or near a surgical droid to do that.
			return 0;
		}

		if (creature->isRidingCreature()) {
			creature->sendSystemMessage("You cannot do that while Riding a Creature.");
			return 0;
		}

		if (creature->isMounted()) {
			creature->sendSystemMessage("You cannot do that while Driving a Vehicle.");
			return 0;
		}

		if (creature->isInCombat()) {
			creature->sendSystemMessage("You cannot do that while in Combat.");
			return 0;
		}

		if (creatureTarget->isInCombat()) {
			creature->sendSystemMessage("You cannot do that while your target is in Combat.");
			return 0;
		}

		if (creatureTarget->isOvert() && creatureTarget->getFaction() != creature->getFaction()) {
			creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
			return 0;
		}

		if (creature->getMind() < abs(mindCost)) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
			return 0;
		}

		battleFatigue = creatureTarget->getShockWounds();

		woundPower = calculatePower(creature, creatureTarget, woundPack, modEnvironment, battleFatigue);

		if (woundPower <= 0) {
			if (battleFatigue >= 1000) {
				sendBFMessage(creature, creatureTarget, battleFatigue);
			}
			//The pack's effectiveness is 0 or has been nullified by battleFatigue.
			return 0;
		}

		woundsHealed = calculateHeal(creatureTarget, woundPower, poolAffected);

		if (woundsHealed <= 0) {
			if (creatureTarget == creature) {
				creature->sendSystemMessage("healing_response", "healing_response_67");
			} else {
				creature->sendSystemMessage(((Player*)creatureTarget)->getFirstNameProper() + " has no wounds of that type to heal.");
			}
			return 0;
		}

		applyWoundHeal(creatureTarget, woundsHealed, poolAffected);

		sendBFMessage(creature, creatureTarget, battleFatigue);
		sendWoundMessage(creature, creatureTarget, poolAffected, woundsHealed);

		creature->changeMindBar(mindCost);

		creature->deactivateWoundTreatment();

		if (woundPack != NULL)
			woundPack->useCharge((Player*) creature);

		if (creatureTarget != creature)
			awardXp(creature, "medical", woundsHealed); //No experience for healing yourself.

		doAnimations(creature, creatureTarget);

		return 0;
	}

	void applyWoundHeal(CreatureObject* creature, int woundsHealed, int poolAffected) {
		switch (poolAffected) {
			case PharmaceuticalImplementation::ACTION:
				creature->changeActionWoundsBar(-woundsHealed);
				break;
			case PharmaceuticalImplementation::STRENGTH:
				creature->changeStrengthWoundsBar(-woundsHealed);
				break;
			case PharmaceuticalImplementation::CONSTITUTION:
				creature->changeConstitutionWoundsBar(-woundsHealed);
				break;
			case PharmaceuticalImplementation::QUICKNESS:
				creature->changeQuicknessWoundsBar(-woundsHealed);
				break;
			case PharmaceuticalImplementation::STAMINA:
				creature->changeStaminaWoundsBar(-woundsHealed);
				break;
			case PharmaceuticalImplementation::HEALTH:
			default:
				creature->changeHealthWoundsBar(-woundsHealed);
				break;
			}
	}

	int calculateHeal(CreatureObject* creature, int woundPower, int poolAffected) {
		int woundsHealed = 0;
		switch (poolAffected) {
		case PharmaceuticalImplementation::ACTION:
			woundsHealed = creature->getActionWounds();
			break;
		case PharmaceuticalImplementation::STRENGTH:
			woundsHealed = creature->getStrengthWounds();
			break;
		case PharmaceuticalImplementation::CONSTITUTION:
			woundsHealed = creature->getConstitutionWounds();
			break;
		case PharmaceuticalImplementation::QUICKNESS:
			woundsHealed = creature->getQuicknessWounds();
			break;
		case PharmaceuticalImplementation::STAMINA:
			woundsHealed = creature->getStaminaWounds();
			break;
		case PharmaceuticalImplementation::HEALTH:
		default:
			woundsHealed = creature->getHealthWounds();
			break;
		}

		return (woundsHealed > woundPower) ? woundPower : woundsHealed;
	}

	int calculatePower(CreatureObject* creature, CreatureObject* creatureTarget, WoundPack* woundPack, int modEnvironment, int battleFatigue) {
		float modSkill = (float)creature->getSkillMod("healing_wound_treatment");
		float modCityBonus = 1.0f; //TODO: If in Medical City, then 1.1f bonus

		int power = (int)round(woundPack->getEffectiveness() * modCityBonus * modEnvironment * (100.0f + modSkill) / 10000.0f); //TODO: Add in medical city bonus

		if (battleFatigue >= 1000) {
			power = 0; //Will cancel the action.
		} else if (battleFatigue >= 250) {
			power -= (int)round((float)power * (((float)battleFatigue - 250.0f) / 1000.0f));
		}

		return power;
	}

	void awardXp(CreatureObject* creature, string type, int power) {
		Player* player = (Player*) creature;

		int amount = (int)round((float)power * 0.5f);

		if (amount <= 0)
			return;

		player->addXp(type, amount, true);

		String::toLower(type);
		type[0] = toupper(type[0]); //Capitalize first letter.

		stringstream msgExperience;
		msgExperience << "You receive " << amount << " points of " << type << " experience.";
		player->sendSystemMessage(msgExperience.str());
	}

	void sendBFMessage(CreatureObject* creature, CreatureObject* creatureTarget, int battleFatigue) {
		string targetName = ((Player*)creatureTarget)->getFirstNameProper();
		stringstream msgPlayer, msgTarget;

		if (battleFatigue >= 1000) {
			msgPlayer << targetName << "'s battle fatigue is too high for the medicine to do any good.";
			msgTarget << "Your battle fatigue is too high for the medicine to do any good. You should seek an entertainer.";
		} else if (battleFatigue >= 750) {
			msgPlayer << targetName << "'s battle fatgiue is greatly reducing the effectiveness of the medicine.";
			msgTarget << "Your battle fatigue is greatly reducing the effectiveness of the medicine. You should seek an entertainer.";
		} else if (battleFatigue >= 500) {
			msgPlayer << targetName << "'s battle fatigue is significantly reducing the effectiveness of the medicine.";
			msgTarget << "Your battle fatigue is significantly reducing the effectiveness of the medicine.";
		} else if (battleFatigue >= 250) {
			msgPlayer << targetName << "'s battle fatigue is reducing the effectiveness of the medicine.";
			msgTarget << "Your battle fatigue is greatly reducing the effectiveness of the medicine.";
		}

		creatureTarget->sendSystemMessage(msgTarget.str());
		if (creatureTarget != creature) {
			creature->sendSystemMessage(msgPlayer.str());
		}
	}

	void sendWoundMessage(CreatureObject* creature, CreatureObject* creatureTarget, int poolAffected, int woundsHealed) {
		string creatureName = ((Player*)creature)->getFirstNameProper();
		string creatureTargetName = ((Player*)creatureTarget)->getFirstNameProper();
		string poolName = PharmaceuticalImplementation::getPoolName(poolAffected);

		stringstream msgPlayer, msgTarget, msgTail;

		if (creature == creatureTarget) {
			msgTarget << "You heal yourself for ";
		} else {
			msgPlayer << "You heal " << creatureTargetName << " for ";
			msgTarget << creatureName << " heals you for ";
		}

		msgTail << woundsHealed << " " << poolName << " wound damage.";

		msgTarget << msgTail.str();
		creatureTarget->sendSystemMessage(msgTarget.str());

		if (creature != creatureTarget) {
			msgPlayer << msgTail.str();
			creatureTarget->sendSystemMessage(msgPlayer.str());
		}
	}

	float calculateSpeed(CreatureObject* creature) {
		return 0.0f; //Handled by event
	}

	virtual bool calculateCost(CreatureObject* creature) {
		return true;
	}

	void setEffectName(const string& name) {
		effectName = name;
	}

	void setMindCost(int cost) {
		mindCost = cost;
	}

};

#endif /*HEALWOUNDTARGETSKILL_H_*/
