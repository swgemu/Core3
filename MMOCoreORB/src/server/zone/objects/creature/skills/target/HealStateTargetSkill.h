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
	String effectName;
	int mindCost;

public:
	HealStateTargetSkill(const String& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
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

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, StatePack* statePack) {
		if (!creature->canTreatStates()) {
			creature->sendSystemMessage("healing_response", "healing_must_wait"); //You must wait before you can do that.
			return false;
		}

		if (statePack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
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

	void parseModifier(const String& modifier, uint64& state, uint64& objectId) {
		if (!modifier.isEmpty()) {
			StringTokenizer tokenizer(modifier);
			tokenizer.setDelimeter("|");

			String stateName;

			tokenizer.getStringToken(stateName);

			state = CreatureState::getState(stateName);

			if (tokenizer.hasMoreTokens())
				objectId = tokenizer.getLongToken();
		} else {
			state = CreatureState::INVALID;
			objectId = 0;
		}
	}

	StatePack* findStatePack(CreatureObject* creature, uint64 state) {
		Inventory* inventory = creature->getInventory();

		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->objectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				if (item->isPharmaceutical()) {
					Pharmaceutical* pharma = (Pharmaceutical*) item;

					if (pharma->isStatePack()) {
						StatePack* statePack = (StatePack*) pharma;

						if (statePack->getMedicineUseRequired() <= medicineUse && statePack->getState() == state)
							return statePack;
					}
				}
			}
		}

		return NULL;
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			creature->sendSystemMessage("healing_response", "healing_response_73"); //Target must be a player or a creature pet in order to heal a state.
			return 0;
		}

		uint64 state = CreatureState::INVALID;
		uint64 objectId = 0;

		parseModifier(modifier, state, objectId);

		if (state == CreatureState::INVALID) {
			creature->sendSystemMessage("healing_response", "healing_response_70"); //You must specify a valid state type.
			return 0;
		}

		StatePack* statePack = (StatePack*) creature->getInventoryItem(objectId);

		if (statePack == NULL)
			statePack = findStatePack(creature, state);

		CreatureObject* creatureTarget = (CreatureObject*) target;

		if (creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted())
			creatureTarget = creature;

		if (!canPerformSkill(creature, creatureTarget, statePack))
			return 0;

		if (!creature->healState(creatureTarget, state)) {
			if (creature == creatureTarget)
				creature->sendSystemMessage("healing_response", "healing_response_72"); //You have no state of that type to heal.
			else
				creature->sendSystemMessage("healing_response", "healing_response_74", creatureTarget->getObjectID()); //%NT has no state of that type to heal.

			return 0;
		}

		creature->changeMindBar(mindCost);

		sendStateMessage(creature, creatureTarget, state);

		creature->deactivateStateTreatment();

		if (statePack != NULL)
			statePack->useCharge((Player*) creature);

		if (creatureTarget != creature)
			awardXp(creature, "medical", 50); //No experience for healing yourself.

		doAnimations(creature, creatureTarget);

		return 0;
	}

	void awardXp(CreatureObject* creature, String type, int power) {
		Player* player = (Player*) creature;

		int amount = (int)round((float)power * 1.0f);

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

	void sendStateMessage(CreatureObject* creature, CreatureObject* creatureTarget, uint64 state) {
		StringBuffer msgPlayer, msgTarget;

		String stateName = CreatureState::getName(state, true);

		if (creature == creatureTarget) {
			msgTarget << "You remove the " << stateName << " state from yourself.";
		} else {
			String creatureName = creature->getCharacterName().toString();
			String creatureTargetName = creatureTarget->getCharacterName().toString();

			msgPlayer << "You remove the " << stateName << " state from " << creatureTargetName << ".";
			msgTarget << creatureName << " removes the " << stateName << " from you.";
		}


		creatureTarget->sendSystemMessage(msgTarget.toString());

		if (creature != creatureTarget)
			creature->sendSystemMessage(msgPlayer.toString());
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

#endif /*HEALSTATETARGETSKILL_H_*/
