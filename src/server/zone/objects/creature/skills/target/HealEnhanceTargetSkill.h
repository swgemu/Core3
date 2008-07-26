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

class HealEnhanceTargetSkill : public TargetSkill {
protected:
	string effectName;
	int poolAffected;

	int buffPower;

	int mindCost;

	EnhancePack* enhancePack;

public:
	HealEnhanceTargetSkill(const string& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
		effectName = aname;
		poolAffected = 0;

		buffPower = 0;

		mindCost = 0;

		enhancePack = NULL;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (effectName.size() != 0)
			creatureTarget->playEffect(effectName, "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const string& modifier, bool doAnimation = true) {
		CreatureObject* creatureTarget;

		if (target == creature) {
			creatureTarget = creature;
		} else {
			creatureTarget = (CreatureObject*) target;
		}

		findEnhancePack(creature, modifier);

		if (poolAffected == PharmaceuticalImplementation::UNKNOWN) {
			creature->sendSystemMessage("healing_response", "healing_response_75"); //You must specify a valid attribute.
			return 0;
		}

		if (enhancePack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
			return 0;
		}

		if (!creature->canTreatWounds()) {
			creature->sendSystemMessage("healing_response", "enhancement_must_wait"); //You must wait before you can heal wounds or apply enhancements again.
			return 0;
		}

		if (!calculateEnhance(creature, creatureTarget))
			return 0;

		if (enhancePack != NULL)
			enhancePack->useCharge((Player*) creature);

		creature->deactivateWoundTreatment();

		awardXp(creature);

		doAnimations(creature, creatureTarget);

		return 0;
	}

	bool calculateEnhance(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (creature->getMedicalFacilityRating() <= 0) {
			creature->sendSystemMessage("healing_response", "must_be_near_droid"); //You must be in a hospital, at a campsite, or near a surgical droid to do that.
			return false;
		}

		if (creature->getMind() < abs(mindCost)) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		calculateBuffPower(creature, creatureTarget);

		if (buffPower <= 0)
			return false;

		int existingBuffPower = 0;

		uint32 buffCRC = enhancePack->getBuffCRC();

		if (creatureTarget->hasBuff(buffCRC)) {
			BuffObject* bo = creatureTarget->getBuffObject(buffCRC);
			Buff* b = bo->getBuff();

			bo->finalize();
			existingBuffPower = getBuffPower(b, buffCRC);

			if (existingBuffPower > buffPower) {
				if (creatureTarget == creature) {
					creature->sendSystemMessage("Your current enhancements are of greater power.");
				} else {
					creature->sendSystemMessage("The patient's current enhancements are of greater power.");
					creatureTarget->sendSystemMessage("Your current enhancements are of greater power.");
				}
				return false;
			}
		}

		Buff* buff = getBuff(buffPower, enhancePack->getDuration());
		BuffObject* bo = new BuffObject(buff);
		creatureTarget->applyBuff(bo);

		int buffDifference = buffPower - existingBuffPower;

		string creatureName = ((Player*)creature)->getFirstName();
		string creatureTargetName = ((Player*)creatureTarget)->getFirstName();
		string poolName = PharmaceuticalImplementation::getPoolName(poolAffected);

		//Initial Capitalize the Proper names.
		creatureName[0] = toupper(creatureName[0]);
		creatureTargetName[0] = toupper(creatureTargetName[0]);
		poolName[0] = toupper(poolName[0]);

		stringstream msgPlayer, msgTarget, msgBuff;

		if (existingBuffPower == buffPower) {
			if (creature == creatureTarget) {
				msgPlayer << "You re-apply your ";
			} else {
				msgPlayer << "You re-apply " << creatureTargetName << "'s ";
				msgTarget << creatureName << " re-applies your ";
			}
			msgBuff << poolName << " enhancement.";
		} else {
			if (creature == creatureTarget) {
				msgPlayer << "You enhance your ";
			} else {
				msgPlayer << "You enhance " << creatureTargetName << "'s ";
				msgTarget << creatureName << " enhances your ";
			}
			msgBuff << poolName << " by " << buffDifference << ".";
		}

		msgPlayer << msgBuff.str();
		creature->sendSystemMessage(msgPlayer.str());

		if (creature != creatureTarget) {
			msgTarget << msgBuff.str();
			creatureTarget->sendSystemMessage(msgTarget.str());
		}

		return true;
	}

	bool calculateBuffPower(CreatureObject* creature, CreatureObject* creatureTarget) {
		float modEnvironment = creature->getMedicalFacilityRating();
		float modSkill = creature->getSkillMod("healing_wound_treatment");
		float modCityBonus = 1.0f; //TODO: If in Medical City, then 1.1f bonus

		buffPower = (int)round(enhancePack->getEffectiveness() * modCityBonus * modEnvironment * (100.0f + modSkill) / 10000.0f); //TODO: Add in medical city bonus

		int battleFatigue = creatureTarget->getShockWounds();
		string file = "healing";
		string msg = "shock_effect_low";

		if (battleFatigue >= 1000) {
			buffPower = 0;
			file = "error_message";
			msg = "too_much_shock";
		} else if (battleFatigue >= 750) {
			msg = "shock_effect_hight";
		} else if (battleFatigue >= 500) {
			msg = "shock_effect_medium";
		} else if (battleFatigue >= 250) {
			msg = "shock_effect_low";
		}

		if (battleFatigue >= 250) {
			creature->sendSystemMessage(file, msg);
			if (creature != creatureTarget) {
				if (battleFatigue < 1000)
					msg += "_target";
				creatureTarget->sendSystemMessage(file, msg);
			}

			buffPower -= buffPower * ((battleFatigue - 250) / 1000);
		}

		return true;
	}

	void awardXp(CreatureObject* creature) {
		Player* player = (Player*) creature;

		string type = "medical";
		int amount = (int)round((float)buffPower * 0.5f);

		player->addXp(type, amount, true);

		stringstream msgExperience;
		msgExperience << "You receive " << amount << " points of Medical experience.";
		player->sendSystemMessage(msgExperience.str());
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

	Buff* getBuff(int buffPower, float duration) {
		Buff* buff;
		switch (getPoolAffected()) {
		case PharmaceuticalImplementation::ACTION:
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_ACTION, BuffType::MEDICAL, duration);
			buff->setActionBuff(buffPower);
			break;
		case PharmaceuticalImplementation::CONSTITUTION:
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_CONSTITUTION, BuffType::MEDICAL, duration);
			buff->setConstitutionBuff(buffPower);
			break;
		case PharmaceuticalImplementation::STRENGTH:
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_STRENGTH, BuffType::MEDICAL, duration);
			buff->setStrengthBuff(buffPower);
			break;
		case PharmaceuticalImplementation::QUICKNESS:
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_QUICKNESS, BuffType::MEDICAL, duration);
			buff->setQuicknessBuff(buffPower);
			break;
		case PharmaceuticalImplementation::STAMINA:
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_STAMINA, BuffType::MEDICAL, duration);
			buff->setStaminaBuff(buffPower);
			break;
		case PharmaceuticalImplementation::HEALTH:
		default:
			buff = new Buff(BuffCRC::MEDICAL_ENHANCE_HEALTH, BuffType::MEDICAL, duration);
			buff->setHealthBuff(buffPower);
			break;
		}
		return buff;
	}

	float calculateSpeed(CreatureObject* creature) {
		return 0.0f;
	}

	virtual bool calculateCost(CreatureObject* creature) {
		return true;
	}

	void findEnhancePack(CreatureObject* creature, const string& modifier) {
		if (!modifier.empty()) {

			uint64 objectid = 0;
			string pool;
			StringTokenizer tokenizer(modifier);
			tokenizer.setDelimeter("|");

			tokenizer.getStringToken(pool);
			if (tokenizer.hasMoreTokens())
				objectid = tokenizer.getLongToken();

			if (!validatePool(pool))
				return;
			else
				setPoolAffected(pool);

			if (objectid > 0) {
				enhancePack = (EnhancePack*) creature->getInventoryItem(objectid);
				if (enhancePack != NULL && enhancePack->isEnhancePack())
					return;
			}
		}

		setEnhancePack(NULL);
		int playerMedUse = creature->getSkillMod("healing_ability");

		Inventory* inventory = creature->getInventory();
		EnhancePack* pack;

		for (int i=0; i<inventory->objectsSize(); i++) {

			TangibleObject* item = (TangibleObject*) inventory->getObject(i);

			if (item != NULL && item->isPharmaceutical()) {
				pack = (EnhancePack*) item;

				if (pack->isEnhancePack()
						&& pack->getMedicineUseRequired() <= playerMedUse
						&& pack->getPoolAffected() == poolAffected)
					break;
			}
		}

		setEnhancePack(pack);
	}

	bool validatePool(const string& pool) {
		int p = PharmaceuticalImplementation::getPoolFromName(pool);
		if (p == PharmaceuticalImplementation::UNKNOWN)
			return false;

		return true;
	}

	void setEnhancePack(EnhancePack* pack) {
		enhancePack = pack;
	}

	EnhancePack* getEnhancePack() {
		return enhancePack;
	}

	inline int getPoolAffected() {
		return poolAffected;
	}

	inline void setMindCost(int value) {
		mindCost = value;
	}

	inline int getMindCost() {
		return mindCost;
	}

	void setPoolAffected(int pool) {
		poolAffected = pool;
	}

	void setPoolAffected(const string& pool) {
		poolAffected = PharmaceuticalImplementation::getPoolFromName(pool);
	}
};

#endif /*HEALENHANCETARGETSKILL_H_*/
