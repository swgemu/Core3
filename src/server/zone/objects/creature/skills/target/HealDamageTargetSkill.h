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

#include "../../Attribute.h"

#include "../../../../managers/player/PlayerManager.h"

class HealDamageTargetSkill : public TargetSkill {
protected:
	string effectName;
	int mindCost;

public:
	HealDamageTargetSkill(const string& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
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

	//TODO: Needs refactoring
	StimPack* findMedpack(CreatureObject* creature, const string& modifier) {
		StimPack* stimPack = NULL;
		int medicineUse = creature->getSkillMod("healing_ability");

		if (!modifier.empty()) {
			StringTokenizer tokenizer(modifier);
			uint64 objectid = 0;

			if (tokenizer.hasMoreTokens())
				objectid = tokenizer.getLongToken();

			if (objectid > 0) {
				SceneObject* invObj = creature->getInventoryItem(objectid);

				if (invObj != NULL && invObj->isTangible()) {
					TangibleObject* tano = (TangibleObject*) invObj;

					if (tano->isPharmaceutical()) {
						Pharmaceutical* pharm = (Pharmaceutical*) tano;

						if (pharm->isStimPack()) {
							stimPack = (StimPack*) pharm;

							if (stimPack->getMedicineUseRequired() <= medicineUse)
								return stimPack;
						}
					}
				}
			}
		}

		Inventory* inventory = creature->getInventory();

		for (int i=0; i<inventory->objectsSize(); i++) {
			TangibleObject* item = (TangibleObject*) inventory->getObject(i);

			if (item != NULL && item->isPharmaceutical()) {
				stimPack = (StimPack*) item;

				if (stimPack->isStimPack() && stimPack->getMedicineUseRequired() <= medicineUse)
					return stimPack;
			}
		}

		return NULL; //Never found a stimPack
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, StimPack* stimPack) {
		if (!creature->canTreatInjuries()) {
			creature->sendSystemMessage("healing_response", "healing_must_wait"); //You must wait before you can do that.
			return false;
		}

		if (stimPack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
			return false;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot do that while meditating.");
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

		if (creatureTarget->isOvert() && creatureTarget->getFaction() != creature->getFaction()) {
			creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
			return false;
		}

		if (!creatureTarget->hasHealthDamage() && !creatureTarget->hasActionDamage()) {
			if (creatureTarget == creature) {
				creature->sendSystemMessage("healing_response", "healing_response_61"); //You have no damage to heal.
			} else {
				creature->sendSystemMessage("healing_response", "healing_response_63", creatureTarget->getObjectID()); //%NT has no damage to heal.
			}
			return false;
		}

		if (creature->getMind() < abs(mindCost)) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		return true;
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const string& modifier, bool doAnimation = true) {
		if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			creature->sendSystemMessage("healing_response", "healing_response_62"); //Target must be a player or a creature pet in order to heal damage.
			return 0;
		}

		StimPack* stimPack = findMedpack(creature, modifier);
		CreatureObject* creatureTarget = (CreatureObject*) target;

		if (creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted()) {
			cout << "Target is dead, ridingcreature, or mounted." << endl;
			creatureTarget = creature;
		}

		if (!canPerformSkill(creature, creatureTarget, stimPack))
			return 0;

		//Checks completed

		int stimPower = stimPack->calculatePower(creature);

		int healthHealed = creature->healDamage(creatureTarget, stimPower, Attribute::HEALTH);
		int actionHealed = creature->healDamage(creatureTarget, stimPower, Attribute::ACTION);

		if (creature->isPlayer())
			((Player*)creature)->sendBFMessage(creatureTarget);

		//sendBFMessage(creature, creatureTarget);
		sendHealMessage(creature, creatureTarget, healthHealed, actionHealed);

		creature->changeMindBar(mindCost);

		creature->deactivateInjuryTreatment();

		if (stimPack != NULL)
			stimPack->useCharge((Player*) creature);

		if (creatureTarget != creature)
			awardXp(creature, "medical", (healthHealed + healthHealed)); //No experience for healing yourself.

		doAnimations(creature, creatureTarget);

		return 0;
	}

	void awardXp(CreatureObject* creature, string type, int power) {
		Player* player = (Player*) creature;

		int amount = (int)round((float)power * 0.25f);

		if (amount <= 0)
			return;

		player->addXp(type, amount, true);

		String::toLower(type);
		type[0] = toupper(type[0]); //Capitalize first letter.

		stringstream msgExperience;
		msgExperience << "You receive " << amount << " points of " << type << " experience.";
		player->sendSystemMessage(msgExperience.str());
	}

	void sendBFMessage(CreatureObject* creature, CreatureObject* creatureTarget) {
		string targetName = ((Player*)creatureTarget)->getFirstNameProper();
		stringstream msgPlayer, msgTarget;

		int battleFatigue = creatureTarget->getShockWounds();

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

	void sendHealMessage(CreatureObject* creature, CreatureObject* creatureTarget, int healthDamage, int actionDamage) {
		Player* player = (Player*) creature;
		Player* playerTarget = (Player*) creatureTarget;

		stringstream msgPlayer, msgTarget, msgBody, msgTail;

		if (healthDamage > 0 && actionDamage > 0) {
			msgBody << healthDamage << " health and " << actionDamage << " action";
		} else if (healthDamage > 0) {
			msgBody << healthDamage << " health";
		} else if (actionDamage > 0) {
			msgBody << actionDamage << " action";
		} else {
			return; //No damage to heal.
		}

		msgTail << " damage.";

		if (creature == creatureTarget) {
			msgPlayer << "You heal yourself for " << msgBody.str() << msgTail.str();
			player->sendSystemMessage(msgPlayer.str());
		} else {
			msgPlayer << "You heal " << playerTarget->getFirstNameProper() << " for " << msgBody.str() << msgTail.str();
			player->sendSystemMessage(msgPlayer.str());
			msgTarget << player->getFirstNameProper() << " heals you for " << msgBody.str() << msgTail.str();
			playerTarget->sendSystemMessage(msgTarget.str());
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

#endif /*HEALDAMAGETARGETSKILL_H_*/
