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

#ifndef QUICKHEALTARGETSKILL_H_
#define QUICKHEALTARGETSKILL_H_

#include "../TargetSkill.h"

#include "../../../../managers/player/PlayerManager.h"

class QuickHealTargetSkill : public TargetSkill {
protected:
	String effectName;
	int mindCost;
	int mindWoundCost;

	int healthHealed;
	int actionHealed;
	int mindHealed;

	float speed;

public:
	QuickHealTargetSkill(const String& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
		effectName = aname;
		mindCost = 0;
		mindWoundCost = 0;

		healthHealed = 0;
		actionHealed = 0;
		mindHealed = 0;

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
			creature->sendSystemMessage("healing_response", "healing_response_99"); //Target must be a player or a creature pet in order to quickheal .
			return 0;
		}

		CreatureObject* creatureTarget = (CreatureObject*) target;

		if (creatureTarget->isDead() || creatureTarget->isMountedCreature() || creatureTarget->isRidingMount())
			creatureTarget = creature;	//If our target is dead, riding a creature, or mounted, then we make ourself target.

		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot Quick Heal while prone.");
			return 0;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot Quick Heal while meditating.");
			return 0;
		}

		if (creature->isMountedCreature()) {
			creature->sendSystemMessage("You cannot do that while Riding a Creature.");
			return 0;
		}

		if (creature->isRidingMount()) {
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


		if (!creatureTarget->hasHealthDamage() && !creatureTarget->hasActionDamage()) {
				if (creatureTarget == creature)
					creature->sendSystemMessage("healing_response", "healing_response_61"); //You have no damage to heal.
				else
					creature->sendSystemMessage("healing_response", "healing_response_63", creatureTarget->getObjectID()); //%NT has no damage to heal.
				return 0;
			}

			int healPower = (int) round(150 + System::random(600));

			int healedHealth = creature->healDamage(creatureTarget, CreatureAttribute::HEALTH, healPower);
			int healedAction = creature->healDamage(creatureTarget, CreatureAttribute::ACTION, healPower);

			if (creature->isPlayer())
				((Player*)creature)->sendBattleFatigueMessage(creatureTarget);

			sendHealMessage(creature, creatureTarget, healedHealth, healedAction);

		creature->changeMindBar(-mindCost);
		creature->changeFocusWoundsBar(mindWoundCost);
		creature->changeWillpowerWoundsBar(mindWoundCost);
		creature->changeShockWounds(2);

		doAnimations(creature, creatureTarget);

		return 0;
	}

	void sendHealMessage(CreatureObject* creature, CreatureObject* creatureTarget, int healthDamage, int actionDamage) {
		if (!creature->isPlayer() || !creatureTarget->isPlayer())
			return;

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

	void setSpeed(float spd) {
		speed = spd;
	}
};

#endif /*QUICKHEALTARGETSKILL_H_*/
