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
	String effectName;
	uint64 state;
	int mindCost;

public:
	CureTargetSkill(const String& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
		setEffectName(aname);
		setState(CreatureState::INVALID);
		setMindCost(0);
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!effectName.isEmpty())
			creatureTarget->playEffect(effectName, "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, CurePack* curePack) {
		switch (state) {
		case CreatureState::POISONED:
			if (!creatureTarget->isPoisoned()) {
				if (creature == creatureTarget)
					creature->sendSystemMessage("healing_response", "healing_response_82"); //You are not poisoned.
				else
					creature->sendSystemMessage("healing_response", "healing_response_84", creatureTarget->getObjectID()); //%NT is not poisoned.
				return false;
			}
			break;
		case CreatureState::DISEASED:
			if (!creatureTarget->isDiseased()) {
				if (creature == creatureTarget)
					creature->sendSystemMessage("healing_response", "healing_response_90"); //You are not diseased.
				else
					creature->sendSystemMessage("healing_response", "healing_response_92", creatureTarget->getObjectID()); //%NT is not diseased.
				return false;
			}
			break;
		case CreatureState::ONFIRE:
			if (!creatureTarget->isOnFire()) {
				if (creature == creatureTarget)
					creature->sendSystemMessage("healing_response", "healing_response_86"); //You are not on fire.
				else
					creature->sendSystemMessage("healing_response", "healing_response_88", creatureTarget->getObjectID()); //%NT is not on fire.
				return false;
			}
			break;
		}

		if (!creature->canTreatConditions()) {
			creature->sendSystemMessage("healing_response", "healing_must_wait"); //You must wait before you can do that.
			return false;
		}

		if (curePack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
			return false;
		}


		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot Cure States while prone.");
			return false;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot Cure States while Meditating.");
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

	void parseModifier(const String& modifier, uint64& objectId) {
		if (!modifier.isEmpty())
			objectId = Long::valueOf(modifier);
		else
			objectId = 0;
	}

	CurePack* findCurePack(CreatureObject* creature) {
		Inventory* inventory = creature->getInventory();
		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				if (item->isPharmaceutical()) {
					Pharmaceutical* pharma = (Pharmaceutical*) item;

					if (pharma->isCurePack()) {
						CurePack* curePack = (CurePack*) pharma;

						if (curePack->getMedicineUseRequired() <= medicineUse && curePack->getState() == state)
							return curePack;
					}
				}
			}
		}

		return NULL;
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		//Validate our target is a Player or CreatureObject
		//TODO: Should check that is a Player or CreaturePet instead.
		if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			switch (state) {
				case CreatureState::POISONED:
					creature->sendSystemMessage("healing_response", "healing_response_83"); //Target must be a player or a creature pet in order to cure poison.
					break;

				case CreatureState::DISEASED:
					creature->sendSystemMessage("healing_response", "healing_response_91"); //Target must be a player or a creature pet in order cure disease.
					break;

				case CreatureState::ONFIRE:
				default:
					creature->sendSystemMessage("healing_response", "healing_response_87"); //Target must be a player or a creature pet in order to quench flames.
					break;
			}

			return 0;
		}

		uint64 objectId = 0;

		parseModifier(modifier, objectId);

		CurePack* curePack = (CurePack*) creature->getInventoryItem(objectId);

		if (curePack == NULL)
			curePack = findCurePack(creature);

		CreatureObject* creatureTarget = (CreatureObject*) target;

		if (creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted())
			creatureTarget = creature;

		if (!canPerformSkill(creature, creatureTarget, curePack))
			return 0;

		sendCureMessage(creature, creatureTarget);

		switch (state) {
		case CreatureState::DISEASED:
			/*if (!creature->cureDisease(creatureTarget, curePack->getEffectiveness()))
				return 0;*/
			creatureTarget->healDot(CreatureState::DISEASED,(int)curePack->getEffectiveness());
			break;
		case CreatureState::POISONED:
			/*if (!creature->curePoison(creatureTarget, curePack->getEffectiveness()))
				return 0;*/
			creatureTarget->healDot(CreatureState::POISONED,(int)curePack->getEffectiveness());
			break;
		case CreatureState::ONFIRE:
			/*if (!creature->extinguishFire(creatureTarget, curePack->getEffectiveness()))
				return 0;*/
			creatureTarget->healDot(CreatureState::ONFIRE, (int)curePack->getEffectiveness());
			break;
		default:
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

	void sendCureMessage(CreatureObject* creature, CreatureObject* creatureTarget) {
		StringBuffer msgTarget, msgPlayer;
		String msgSelf;
		switch (state) {
		case CreatureState::POISONED:
			msgPlayer << "You apply poison antidote to " << creatureTarget->getCharacterName().toString() << ".";
			msgTarget << creature->getCharacterName().toString() << " applies poison antidote to you.";
			msgSelf = "poison_antidote_self";
			break;
		case CreatureState::DISEASED:
			msgPlayer << "You apply disease antidote to " << creatureTarget->getCharacterName().toString() << ".";
			msgTarget << creature->getCharacterName().toString() << " applies disease antidote to you.";
			msgSelf = "disease_antidote_self";
			break;
		case CreatureState::ONFIRE:
			msgPlayer << "You attempt to suppress the flames on " << creatureTarget->getCharacterName().toString() << ".";
			msgTarget << creature->getCharacterName().toString() << " covers you in a suppressive blanket.";
			msgSelf = "blanket";
			break;
		default:
			return;
		}

		if (creature != creatureTarget) {
			creature->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());
		} else {
			creature->sendSystemMessage("healing_response", msgSelf);
		}
	}

	void awardXp(CreatureObject* creature, String type, int power) {
		Player* player = (Player*) creature;

		int amount = (int) round((float) power * 1.0f);

		if (amount <= 0)
			return;

		player->addXp(type, amount, true);
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

	void setState(uint64 value) {
		state = value;
	}

	void setMindCost(int cost) {
		mindCost = cost;
	}
};

#endif /*CURETARGETSKILL_H_*/
