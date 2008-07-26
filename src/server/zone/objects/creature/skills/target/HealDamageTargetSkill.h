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

#ifndef HEALDAMAGETARGETSKILL_H_
#define HEALDAMAGETARGETSKILL_H_

#include "../TargetSkill.h"
#include "../../../tangible/pharmaceutical/PharmaceuticalImplementation.h"
#include "../../../tangible/pharmaceutical/StimPackImplementation.h"

#include "../../../../managers/player/PlayerManager.h"

class HealDamageTargetSkill : public TargetSkill {
protected:
	string effectName;
	int mindCost;

	int healthDamage;
	int actionDamage;
	int stimPower;

	StimPack* stimPack;

public:
	HealDamageTargetSkill(const string& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
		effectName = aname;
		mindCost = 0;

		healthDamage = 0;
		actionDamage = 0;
		stimPower = 0;

		stimPack = NULL;
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

		if (!creatureTarget->isPlayer()) { //TODO: Allow healing of pets.
			creature->sendSystemMessage("healing_response", "healing_response_62"); //Target must be a player or a creature pet in order to heal damage.
			return 0;
		}

		if (!creature->canTreatInjuries()) {
			creature->sendSystemMessage("healing_response", "healing_must_wait"); //You must wait before you can do that.
			return 0;
		}

		findStimPack(creature, modifier);

		if (stimPack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
			return 0;
		}

		setStimPower(creature, creatureTarget);

		if (creature->getMind() < abs(mindCost)) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		if (!calculateHeal(creature, creatureTarget)) {
			if (creatureTarget == creature) {
				creature->sendSystemMessage("healing_response", "healing_response_61"); //You have no damage to heal.
			} else {
				Player* player = (Player*) creature;
				player->sendSystemMessage("healing_response", "healing_response_63", creatureTarget->getObjectID()); //%NT has no damage to heal.
			}

			return 0;
		}

		if (stimPack != NULL)
			stimPack->useCharge((Player*) creature);

		creature->deactivateInjuryTreatment();

		awardXp(creature);

		doAnimations(creature, creatureTarget);

		return 0;
	}

	bool calculateHeal(CreatureObject* creature, CreatureObject* creatureTarget) {
		Player* player = (Player*) creature;
		Player* playerTarget = (Player*) creatureTarget;

		healthDamage = creatureTarget->getHealthMax() - creatureTarget->getHealth();
		actionDamage = creatureTarget->getActionMax() - creatureTarget->getAction();

		healthDamage = (healthDamage > stimPower) ? stimPower : healthDamage;
		actionDamage = (actionDamage > stimPower) ? stimPower : actionDamage;

		stringstream msgPlayer, msgTarget, msgBody, msgTail;

		if (healthDamage > 0 && actionDamage > 0) {
			msgBody << healthDamage << " health and " << actionDamage << " action";
		} else if (healthDamage > 0) {
			msgBody << healthDamage << " health";
		} else if (actionDamage > 0) {
			msgBody << actionDamage << " action";
		} else {
			return false; //No damage to heal.
		}

		msgTail << " damage.";

		if (creature == creatureTarget) {
			msgPlayer << "You heal yourself for " << msgBody.str() << msgTail.str();
			player->sendSystemMessage(msgPlayer.str());
		} else {
			msgPlayer << "You heal " << playerTarget->getFirstName() << " for " << msgBody.str() << msgTail.str();
			player->sendSystemMessage(msgPlayer.str());
			msgTarget << player->getFirstName() << " heals you for " << msgBody.str() << msgTail.str();
			playerTarget->sendSystemMessage(msgTarget.str());
		}

		creatureTarget->changeHealthBar(healthDamage);
		creatureTarget->changeActionBar(actionDamage);

		creature->changeMindBar(mindCost);

		return true;
	}

	void findStimPack(CreatureObject* creature, const string& modifier) {
		if (!modifier.empty()) {

			uint64 objectid = 0;
			StringTokenizer tokenizer(modifier);

			objectid = tokenizer.getLongToken();

			if (objectid > 0) {
				stimPack = (StimPack*) creature->getInventoryItem(objectid);
				if (stimPack != NULL && stimPack->isStimPack())
					return;
			}
		}

		setStimPack(NULL);
		int playerMedUse = creature->getSkillMod("healing_ability");

		Inventory* inventory = creature->getInventory();
		StimPack* pack;

		for (int i=0; i<inventory->objectsSize(); i++) {

			TangibleObject* item = (TangibleObject*) inventory->getObject(i);

			if (item != NULL && item->isPharmaceutical()) {
				pack = (StimPack*) item;

				if (pack->isStimPack() && pack->getMedicineUseRequired() <= playerMedUse)
					break;
			}
		}

		setStimPack(pack);
	}

	void setStimPower(CreatureObject* creature, CreatureObject* creatureTarget) {
		float modSkill = (float)creature->getSkillMod("healing_injury_treatment");
		stimPower = (int)round((100.0f + modSkill) / 100.0f * stimPack->getEffectiveness());

		//TODO: Add in BattleFatigue.
		//Calculate Battle Fatigue
		//TODO: Can this be re-factored?
		int battleFatigue = creatureTarget->getShockWounds();
		string file = "healing", msg;

		if (battleFatigue >= 1000) {
			file = "error_message";
			msg = "too_much_shock";
			stimPower = 0; //This will cancel the buff
		} else if (battleFatigue >= 750) {
			msg = "shock_effect_high";
		} else if (battleFatigue >= 500) {
			msg = "shock_effect_medium";
		} else if (battleFatigue >= 250) {
			msg = "shock_effect_low";
		}

		if (battleFatigue >= 250) {
			stimPower -= stimPower * ((battleFatigue - 250) / 1000);
			creature->sendSystemMessage(file, msg);
			if (creature != creatureTarget)
				creatureTarget->sendSystemMessage(file, ((battleFatigue >= 1000) ? msg : msg + "_target"));
		}
	}

	void awardXp(CreatureObject* creature) {
		Player* player = (Player*) creature;

		string type = "medical";
		int amount = (int)round((float)stimPower * 0.25f);

		player->addXp(type, amount, true);

		stringstream msgExperience;
		msgExperience << "You receive " << amount << " points of Medical experience.";
		player->sendSystemMessage(msgExperience.str());
	}

	float calculateSpeed(CreatureObject* creature) {
		return 0.0f; //Handled by event
	}

	virtual bool calculateCost(CreatureObject* creature) {
		return true;
	}

	void setHealthDamage(int i) {
		healthDamage = 0;
	}

	void setActionDamage(int i) {
		actionDamage = 0;
	}

	void setStimPower(int power) {
		stimPower = power;
	}

	void setEffectName(const string& name) {
		effectName = name;
	}

	void setMindCost(int cost) {
		mindCost = cost;
	}

	void setStimPack(StimPack* pack) {
		stimPack = pack;
	}
};

#endif /*HEALDAMAGETARGETSKILL_H_*/
