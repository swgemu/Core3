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

#ifndef HEALSTATETARGETSKILL_H_
#define HEALSTATETARGETSKILL_H_

#include "../TargetSkill.h"
#include "../../../tangible/pharmaceutical/PharmaceuticalImplementation.h"
#include "../../../tangible/pharmaceutical/StatePackImplementation.h"

#include "../../../../managers/player/PlayerManager.h"

class HealStateTargetSkill : public TargetSkill {
protected:
	string effectName;
	int mindCost;

public:
	HealStateTargetSkill(const string& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
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

	int doSkill(CreatureObject* creature, SceneObject* target, const string& modifier, bool doAnimation = true) {
		uint64 stateAffected = 0;
		StatePack* statePack = getStatePack(creature, modifier, stateAffected);

		//If a statepack isnt passed with objectid, then we have to search for one in the creature's inventory.
		//If no stateAffected was passed with modifier, then we have to check if the creature has the corresponding state before assigning that statepack.
		//Problem: hasState(state) takes a CreatureObjectImplementation::DIZZY_STATE, but they do not correlate with the states from statepacks.
		//Solution: change the states on statepacks to correlate with CreatureObjectImplementation so I can use hasState(state);

		if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			creature->sendSystemMessage("healing_response", "healing_response_73"); //Target must be a player or a creature pet in order to heal a state.
			return 0;
		}

		CreatureObject* creatureTarget = (CreatureObject*) target;

		if (creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted())
			creatureTarget = creature;	//If our target is dead, riding a creature, or mounted, then we make ourself target.


		if (!creature->canTreatStates()) {
			creature->sendSystemMessage("healing_response", "healing_must_wait"); //You must wait before you can do that.
			return 0;
		}

		if (stateAffected == PharmaceuticalImplementation::UNKNOWN) {
			creature->sendSystemMessage("healing_response", "healing_response_70"); //You must specify a valid state type.
			return 0;
		}

		if (statePack == NULL) {
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

		if (!healState(creatureTarget, stateAffected)) {
			if (creature == creatureTarget)
				creature->sendSystemMessage("healing_response", "healing_response_72"); //You have no state of that type to heal.
			else
				creature->sendSystemMessage("healing_response", "healing_response_74", creatureTarget->getObjectID()); //%NT has no state of that type to heal.

			return 0;
		}

		creature->changeMindBar(mindCost);
		sendStateMessage(creature, creatureTarget, stateAffected);
		creature->deactivateStateTreatment();

		if (statePack != NULL)
			statePack->useCharge((Player*) creature);

		if (creatureTarget != creature)
			awardXp(creature, "medical", 50); //No experience for healing yourself.

		doAnimations(creature, creatureTarget);

		return 0;
	}

	StatePack* getStatePack(CreatureObject* creature, const string& modifier, uint64& stateAffected) {
		StatePack* statePack = NULL;

		int medicineUse = creature->getSkillMod("healing_ability");

		if (modifier.empty()) {
			return searchInventory(creature, stateAffected, medicineUse);
		} else {
			uint64 objectID = 0;

			parseModifier(modifier, stateAffected, objectID);

			if (objectID <= 0) {
				return searchInventory(creature, stateAffected, medicineUse);
			} else {
				SceneObject* object = creature->getInventoryItem(objectID);
				return (StatePack*) object;
			}
		}
	}

	void parseModifier(const string& modifier, uint64& stateAffected, uint64& objectID) {
		StringTokenizer tokenizer(modifier);
		tokenizer.setDelimeter("|");
		string stateName;

		tokenizer.getStringToken(stateName);

		stateAffected = PharmaceuticalImplementation::getStateFromName(stateName);

		if (tokenizer.hasMoreTokens())
			objectID = tokenizer.getLongToken();
	}

	StatePack* searchInventory(CreatureObject* creature, uint64 stateAffected, int medicineUse) {
		Inventory* inventory = creature->getInventory();
		StatePack* statePack = NULL;

		if (inventory != NULL) {
			for (int i=0; i<inventory->objectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				if (item != NULL && item->isPharmaceutical()) {
					statePack = (StatePack*) item;

					if (statePack->isStatePack() && statePack->getMedicineUseRequired() <= medicineUse) {
						if (stateAffected > 0) {
							if (stateAffected == statePack->getStateAffected())
								return statePack;
						} else {
							if (creature->hasState(statePack->getStateAffected()))
								return statePack;
						}
					}
				}

			}
		}

		return NULL;
	}

	bool healState(CreatureObject* creature, uint64 stateAffected) {
		if (creature->hasState(stateAffected)) {
			if (creature->clearState(stateAffected)) {
				creature->updateStates();
				return true;
			}
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

	void sendStateMessage(CreatureObject* creature, CreatureObject* creatureTarget, uint64 stateAffected) {
		stringstream msgPlayer, msgTarget;

		string stateName = PharmaceuticalImplementation::getStateName(stateAffected);
		stateName[0] = toupper(stateName[0]); //initial cap statename

		if (creature == creatureTarget) {
			msgTarget << "You remove the " << stateName << " state from yourself.";
		} else {
			string creatureName = creature->getCharacterName().c_str().c_str();
			string creatureTargetName = creatureTarget->getCharacterName().c_str().c_str();

			msgPlayer << "You remove the " << stateName << " state from " << creatureTargetName << ".";
			msgTarget << creatureName << " removes the " << stateName << " from you.";
		}


		creatureTarget->sendSystemMessage(msgTarget.str());

		if (creature != creatureTarget)
			creatureTarget->sendSystemMessage(msgPlayer.str());
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

#endif /*HEALSTATETARGETSKILL_H_*/
