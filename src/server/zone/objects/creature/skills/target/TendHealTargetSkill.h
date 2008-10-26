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
	string effectName;
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
	TendHealTargetSkill(const string& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
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
		if (effectName.size() != 0)
			creatureTarget->playEffect(effectName, "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const string& modifier, bool doAnimation = true) {
		if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			creature->sendSystemMessage("healing_response", "healing_response_a1"); //Target must be a player or a creature pet in order to tend damage.
			return 0;
		}

		CreatureObject* creatureTarget = (CreatureObject*) target;

		if (creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted())
			creatureTarget = creature;


		if (creature->isMeditating()) {
			creature->sendSystemMessage("You can not Heal Enhance while meditating.");
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
			int healthDamage = 0, actionDamage = 0;

			calculateHeal(creatureTarget, healthDamage, actionDamage, healthHealed, actionHealed);

			if (healthDamage <= 0 && actionDamage <= 0) {
				if (creatureTarget == creature) {
					creature->sendSystemMessage("healing_response", "healing_response_61"); //You have no damage to heal.
				} else {
					creature->sendSystemMessage("healing_response", "healing_response_63", creatureTarget->getObjectID()); //%NT has no damage to heal.
				}
				return 0;
			}

			if (healthDamage > 0)
				creatureTarget->changeHealthBar(healthDamage);
			if (actionDamage > 0)
				creatureTarget->changeActionBar(actionDamage);

			if (creatureTarget->isIncapacitated()) {
				//Bring incapped players back from incap.
				if (creatureTarget->getHealth() > 0 && creatureTarget->getAction() > 0 && creatureTarget->getMind() > 0)
					((Player*)creatureTarget)->changePosture(CreatureObjectImplementation::UPRIGHT_POSTURE);
			}

			sendHealMessage(creature, creatureTarget, healthDamage, actionDamage);

			creature->changeMindBar(-mindCost);
			creature->changeFocusWoundsBar(mindWoundCost);
			creature->changeWillpowerWoundsBar(mindWoundCost);

			if (creatureTarget != creature)
				awardXp(creature, "medical", 100); //No experience for healing yourself.

			doAnimations(creature, creatureTarget);
		}

		if (tendWound) {
			int woundsHealed = calculateWoundHeal(creatureTarget, 25, woundPool);

			if (woundsHealed <= 0) {
				if (creatureTarget == creature) {
					creature->sendSystemMessage("healing_response", "healing_response_67");
				} else {
					creature->sendSystemMessage(((Player*)creatureTarget)->getFirstNameProper() + " has no wounds of that type to heal.");
				}
				return 0;
			}

			applyWoundHeal(creatureTarget, woundsHealed, woundPool);
			sendWoundMessage(creature, creatureTarget, woundPool, woundsHealed);

			creature->changeMindBar(-mindCost);
			creature->changeFocusWoundsBar(mindWoundCost);
			creature->changeWillpowerWoundsBar(mindWoundCost);

			if (creatureTarget != creature)
				awardXp(creature, "medical", 100); //No experience for healing yourself.

			doAnimations(creature, creatureTarget);

		}

		return 0;
	}

	void calculateHeal(CreatureObject* creatureTarget, int& healthDamage, int& actionDamage, int healthPower, int actionPower) {
		healthDamage = creatureTarget->getHealthMax() - creatureTarget->getHealth() - creatureTarget->getHealthWounds();
		actionDamage = creatureTarget->getActionMax() - creatureTarget->getAction() - creatureTarget->getActionWounds();

		healthDamage = (healthDamage > healthPower) ? healthPower : healthDamage;
		actionDamage = (actionDamage > actionPower) ? actionPower : actionDamage;
	}

	int calculateWoundHeal(CreatureObject* creature, int woundPower, int poolAffected) {
		int woundsHealed = 0;
		switch (poolAffected) {
			case CreatureAttribute::ACTION:
				woundsHealed = creature->getActionWounds();
				break;
			case CreatureAttribute::STRENGTH:
				woundsHealed = creature->getStrengthWounds();
				break;
			case CreatureAttribute::CONSTITUTION:
				woundsHealed = creature->getConstitutionWounds();
				break;
			case CreatureAttribute::QUICKNESS:
				woundsHealed = creature->getQuicknessWounds();
				break;
			case CreatureAttribute::STAMINA:
				woundsHealed = creature->getStaminaWounds();
				break;
			case CreatureAttribute::HEALTH:
			default:
				woundsHealed = creature->getHealthWounds();
				break;
		}

		return (woundsHealed > woundPower) ? woundPower : woundsHealed;
	}

	void applyWoundHeal(CreatureObject* creature, int woundsHealed, int poolAffected) {
		switch (poolAffected) {
			case CreatureAttribute::ACTION:
				creature->changeActionWoundsBar(-woundsHealed);
				break;
			case CreatureAttribute::STRENGTH:
				creature->changeStrengthWoundsBar(-woundsHealed);
				break;
			case CreatureAttribute::CONSTITUTION:
				creature->changeConstitutionWoundsBar(-woundsHealed);
				break;
			case CreatureAttribute::QUICKNESS:
				creature->changeQuicknessWoundsBar(-woundsHealed);
				break;
			case CreatureAttribute::STAMINA:
				creature->changeStaminaWoundsBar(-woundsHealed);
				break;
			case CreatureAttribute::HEALTH:
			default:
				creature->changeHealthWoundsBar(-woundsHealed);
				break;
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

	void sendWoundMessage(CreatureObject* creature, CreatureObject* creatureTarget, int poolAffected, int woundsHealed) {
		string creatureName = creature->getCharacterName().c_str();
		string creatureTargetName = creatureTarget->getCharacterName().c_str();
		string poolName = CreatureAttribute::getName(poolAffected);

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
			creature->sendSystemMessage(msgPlayer.str());
		}
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
		return speed;
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
