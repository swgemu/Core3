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

#ifndef TENDHEALTARGETSKILL_H_
#define TENDHEALTARGETSKILL_H_

#include "../TargetSkill.h"

#include "../../../../managers/player/PlayerManager.h"

class TendHealTargetSkill : public TargetSkill {
protected:
	String effectName;
	int mindCost;
	int mindWoundCost;

	int healthHealed;
	int actionHealed;
	int mindHealed;

	uint8 woundPool;
	int woundsHealed;

	bool tendDamage;
	bool tendWound;

	float speed;

public:
	TendHealTargetSkill(const String& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
		effectName = aname;
		mindCost = 0;
		mindWoundCost = 0;

		healthHealed = 0;
		actionHealed = 0;
		mindHealed = 0;

		woundPool = 0;
		woundsHealed = 0;

		tendDamage = false;
		tendWound = false;

		speed = 0.0f;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!effectName.isEmpty())
			creatureTarget->playEffect(effectName, "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			creature->sendSystemMessage("healing_response", "healing_response_a1"); //Target must be a player or a creature pet in order to tend damage.
			return 0;
		}

		CreatureObject* creatureTarget = (CreatureObject*) target;

		uint8 attribute = creatureTarget->getNextWoundedAttribute();

		if (creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted())
			creatureTarget = creature;


		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot do that while Meditating.");
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



		if (tendDamage) {
			if (!creatureTarget->hasHealthDamage() && !creatureTarget->hasActionDamage()) {
				if (creatureTarget == creature)
					creature->sendSystemMessage("healing_response", "healing_response_61"); //You have no damage to heal.
				else
					creature->sendSystemMessage("healing_response", "healing_response_63", creatureTarget->getObjectID()); //%NT has no damage to heal.
				return 0;
			}

			float modSkill = (float) creature->getSkillMod("healing_injury_treatment");
			float effectiveness = 150.0f;

			int healPower = (int) round((100.0f + modSkill) / 100.0f * effectiveness);

			int healedHealth = creature->healDamage(creatureTarget, healPower, CreatureAttribute::HEALTH);
			int healedAction = creature->healDamage(creatureTarget, healPower, CreatureAttribute::ACTION);

			if (creature->isPlayer())
				((Player*)creature)->sendBattleFatigueMessage(creatureTarget);

			sendHealMessage(creature, creatureTarget, healedHealth, healedAction);
		}



		if (tendWound) {
			if (!creatureTarget->hasWound(attribute)) {
				if (creatureTarget == creature)
					creature->sendSystemMessage("healing_response", "healing_response_67");
				else
					creature->sendSystemMessage(creatureTarget->getCharacterName().toString()
							+ " has no wounds of that type to heal.");

				return 0;
			}

			//TODO: Add in medical city bonus
			float modEnvironment = (float) creature->getMedicalFacilityRating();
			float modSkill = (float) creature->getSkillMod("healing_wound_treatment");
			float modCityBonus = 1.0f;
			float effectiveness = 150.0f;

			//Since this skill can be used anywhere, we need to check that modEnvironment is not 0.
			modEnvironment = modEnvironment > 0.0f ? modEnvironment : 1.0f;

			int healPower = (int) round(effectiveness * modCityBonus * modEnvironment * (100.0f + modSkill) / 10000.0f);

			int healedWounds = creature->healWound(creatureTarget, healPower, attribute);

			if (creature->isPlayer())
				((Player*)creature)->sendBattleFatigueMessage(creatureTarget);

			sendWoundMessage(creature, creatureTarget, attribute, healedWounds);
		}

		creature->changeMindBar(-mindCost);

		creature->changeFocusWoundsBar(mindWoundCost);
		creature->changeWillpowerWoundsBar(mindWoundCost);

		if (creatureTarget != creature)
			awardXp(creature, "medical", 100);

		doAnimations(creature, creatureTarget);

		return 0;
	}

	void sendHealMessage(CreatureObject* creature, CreatureObject* creatureTarget, int healthDamage, int actionDamage) {
		Player* player = (Player*) creature;
		Player* playerTarget = (Player*) creatureTarget;

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

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
			msgPlayer << "You heal yourself for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
		} else {
			msgPlayer << "You heal " << playerTarget->getCharacterName().toString() << " for " << msgBody.toString() << msgTail.toString();
			msgTarget << player->getCharacterName().toString() << " heals you for " << msgBody.toString() << msgTail.toString();

			player->sendSystemMessage(msgPlayer.toString());
			playerTarget->sendSystemMessage(msgTarget.toString());
		}
	}

	void sendWoundMessage(CreatureObject* creature, CreatureObject* creatureTarget, int poolAffected, int woundsHealed) {
		String creatureName = creature->getCharacterName().toString();
		String creatureTargetName = creatureTarget->getCharacterName().toString();

		String poolName = CreatureAttribute::getName(poolAffected);

		StringBuffer msgPlayer, msgTarget, msgTail;

		if (creature == creatureTarget) {
			msgTarget << "You heal yourself for ";
		} else {
			msgPlayer << "You heal " << creatureTargetName << " for ";
			msgTarget << creatureName << " heals you for ";
		}

		msgTail << woundsHealed << " " << poolName << " wound damage.";

		msgTarget << msgTail.toString();
		creatureTarget->sendSystemMessage(msgTarget.toString());

		if (creature != creatureTarget) {
			msgPlayer << msgTail.toString();
			creature->sendSystemMessage(msgPlayer.toString());
		}
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

	float calculateSpeed(CreatureObject* creature) {
		return speed;
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

	void setMindWoundCost(int cost) {
		mindWoundCost = cost;
	}

	void setHealthHealed(int health) {
		healthHealed = health;
	}

	void setActionHealed(int action) {
		actionHealed = action;
	}

	void setMindHealed(int mind) {
		mindHealed = mind;
	}

	void setWoundPool(uint8 pool) {
		woundPool = pool;
	}

	void setWoundsHealed(int wounds) {
		woundsHealed = wounds;
	}


	void setTendDamage(bool tend) {
		tendDamage = tend;
	}

	void setTendWound(bool tend) {
		tendWound = tend;
	}

	void setSpeed(float spd) {
		speed = spd;
	}
};

#endif /*TENDHEALTARGETSKILL_H_*/
