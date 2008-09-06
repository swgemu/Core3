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

#ifndef CURETARGETSKILL_H_
#define CURETARGETSKILL_H_

#include "../TargetSkill.h"
#include "../../../tangible/pharmaceutical/PharmaceuticalImplementation.h"
#include "../../../tangible/pharmaceutical/CurePackImplementation.h"

#include "../../../../managers/player/PlayerManager.h"

class CureTargetSkill : public TargetSkill {
protected:
	string effectName;
	uint64 conditionCured;
	int mindCost;

public:
	CureTargetSkill(const string& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
		setEffectName(aname);
		setConditionCured(0);
		setMindCost(0);
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (effectName.size() != 0)
			creatureTarget->playEffect(effectName, "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	CurePack* findMedpack(CreatureObject* creature, const string& modifier) {
		CurePack* curePack = NULL;
		uint64 conditionCured = getConditionCured();
		int medicineUse = creature->getSkillMod("healing_ability");

		if (!modifier.empty()) {
			StringTokenizer tokenizer(modifier);
			uint64 objectid = 0;

			tokenizer.setDelimeter("|");

			if (tokenizer.hasMoreTokens())
				objectid = tokenizer.getLongToken();

			if (objectid > 0) {
				SceneObject* invObj = creature->getInventoryItem(objectid);

				if (invObj != NULL && invObj->isTangible()) {
					TangibleObject* tano = (TangibleObject*) invObj;

					if (tano->isPharmaceutical()) {
						Pharmaceutical* pharm = (Pharmaceutical*) tano;

						if (pharm->isCurePack()) {
							curePack = (CurePack*) pharm;

							if (curePack->getMedicineUseRequired() <= medicineUse && curePack->getConditionCured() == conditionCured)
								return curePack;
						}
					}
				}
			}
		}

		Inventory* inventory = creature->getInventory();

		for (int i=0; i<inventory->objectsSize(); i++) {
			TangibleObject* item = (TangibleObject*) inventory->getObject(i);

			if (item != NULL && item->isPharmaceutical()) {
				curePack = (CurePack*) item;

				if (curePack->isCurePack()
						&& curePack->getMedicineUseRequired() <= medicineUse
						&& curePack->getConditionCured() == conditionCured)
					return curePack;
			}
		}

		return NULL; //Never found a curepack
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const string& modifier, bool doAnimation = true) {
		CurePack* curePack = findMedpack(creature, modifier);
		uint64 conditionCured = getConditionCured();

		//Check that the condition cured is a valid condition
		if (conditionCured <= 0) {
			creature->sendSystemMessage("You must specify a valid condition."); //NOTE: This should never happen unless a LUA file is setup wrong.
			return 0;
		}

		//Validate our target is a Player or CreatureObject
		//TODO: Should check that is a Player or CreaturePet instead.
		if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			switch (getConditionCured()) {
				case CreatureObjectImplementation::POISONED_STATE:
					creature->sendSystemMessage("healing_response", "healing_response_83"); //Target must be a player or a creature pet in order to cure poison.
					break;

				case CreatureObjectImplementation::DISEASED_STATE:
					creature->sendSystemMessage("healing_response", "healing_response_91"); //Target must be a player or a creature pet in order cure disease.
					break;

				case CreatureObjectImplementation::ONFIRE_STATE:
				default:
					creature->sendSystemMessage("healing_response", "healing_response_87"); //Target must be a player or a creature pet in order to quench flames.
					break;
			}

			return 0;
		}

		CreatureObject* creatureTarget = (CreatureObject*) target;

		//If the target is in an unhealable state, then we set target to self.
		if (creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted())
			creatureTarget = creature;

		if (!creature->canTreatConditions()) {
			creature->sendSystemMessage("healing_response", "healing_must_wait"); //You must wait before you can do that.
			return 0;
		}

		if (curePack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
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

		if (creatureTarget->isOvert() && creatureTarget->getFaction() != creature->getFaction()) {
			creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
			return 0;
		}

		if (creature->getMind() < abs(mindCost)) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
			return 0;
		}

		if (!cureCondition(creature, creatureTarget)) {
			return 0;
		}

		creature->changeMindBar(mindCost);
		creature->deactivateConditionTreatment();

		if (curePack != NULL)
			curePack->useCharge((Player*) creature);

		if (creatureTarget != creature)
			awardXp(creature, "medical", 50); //No experience for healing yourself.

		doAnimations(creature, creatureTarget);

		return 0;
	}


	//TODO: This needs restructuring bad!
	bool cureCondition(CreatureObject* creature, CreatureObject* creatureTarget) {
		int conditionCured = getConditionCured();

		switch (conditionCured) {
			case CreatureObjectImplementation::POISONED_STATE:
			{
				if (creatureTarget->isPoisoned()) {
					creatureTarget->clearState(CreatureObjectImplementation::POISONED_STATE);
					if (creature == creatureTarget) {
						creature->sendSystemMessage("healing_response", "poison_antidote_self"); //You apply poison antidote to yourself.
					} else {
						stringstream msgTarget, msgPlayer;
						msgTarget << "You apply poison antidote to " << creatureTarget->getCharacterName().c_str() << ".";
						creature->sendSystemMessage(msgTarget.str());
						msgPlayer << creature->getCharacterName().c_str() << " applies poison antidote to you.";
						creatureTarget->sendSystemMessage(msgPlayer.str());
					}
					creatureTarget->updateStates();
					return true;
				} else {
					if (creature == creatureTarget)
						creature->sendSystemMessage("healing_response", "healing_response_82"); //You are not poisoned.
					else
						creature->sendSystemMessage("healing_response", "healing_response_84", creatureTarget->getObjectID()); //%NT is not poisoned.
				}
				break;
			}
			case CreatureObjectImplementation::DISEASED_STATE:
			{
				if (creatureTarget->isDiseased()) {
					creatureTarget->clearState(CreatureObjectImplementation::DISEASED_STATE);
					if (creature == creatureTarget) {
						creature->sendSystemMessage("healing_response", "disease_antidote_self"); //You apply disease antidote to yourself.
					} else {
						stringstream msgTarget, msgPlayer;
						msgTarget << "You apply disease antidote to " << creatureTarget->getCharacterName().c_str() << ".";
						creature->sendSystemMessage(msgTarget.str());
						msgPlayer << creature->getCharacterName().c_str() << " applies disease antidote to you.";
						creatureTarget->sendSystemMessage(msgPlayer.str());
					}
					creatureTarget->updateStates();
					return true;
				} else {
					if (creature == creatureTarget)
						creature->sendSystemMessage("healing_response", "healing_response_90"); //You are not diseased.
					else
						creature->sendSystemMessage("healing_response", "healing_response_92", creatureTarget->getObjectID()); //%NT is not diseased.
				}
				break;
			}
			case CreatureObjectImplementation::ONFIRE_STATE:
			{
				if (creatureTarget->isOnFire()) {
					creatureTarget->clearState(CreatureObjectImplementation::ONFIRE_STATE);
					if (creature == creatureTarget) {
						creature->sendSystemMessage("healing_response", "blanket"); //You cover yourself in a suppressive blanket.
					} else {
						stringstream msgTarget, msgPlayer;
						msgTarget << "You attempt to suppress the flames on " << creatureTarget->getCharacterName().c_str() << ".";
						creature->sendSystemMessage(msgTarget.str());
						msgPlayer << creature->getCharacterName().c_str() << " covers you in a suppressive blanket.";
						creatureTarget->sendSystemMessage(msgPlayer.str());
					}
					creatureTarget->updateStates();
					return true;
				} else {
					if (creature == creatureTarget)
						creature->sendSystemMessage("healing_response", "healing_response_86"); //You are not on fire.
					else
						creature->sendSystemMessage("healing_response", "healing_response_88", creatureTarget->getObjectID()); //%NT is not on fire.
				}
				break;
			}
			case PharmaceuticalImplementation::UNKNOWN:
			default:
				return false;
			}

		return false;
	}

	void awardXp(CreatureObject* creature, string type, int power) {
		Player* player = (Player*) creature;

		int amount = (int)round((float)power * 1.0f);

		if (amount <= 0)
			return;

		player->addXp(type, amount, true);

		String::toLower(type);
		type[0] = toupper(type[0]); //Capitalize first letter.

		stringstream msgExperience;
		msgExperience << "You receive " << amount << " points of " << type << " experience.";
		player->sendSystemMessage(msgExperience.str());
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

	void setConditionCured(uint64 condition) {
		conditionCured = condition;
	}

	void setMindCost(int cost) {
		mindCost = cost;
	}

	uint64 getConditionCured() {
		return conditionCured;
	}
};

#endif /*CURETARGETSKILL_H_*/
