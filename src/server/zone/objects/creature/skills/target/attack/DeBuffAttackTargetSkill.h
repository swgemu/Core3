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

#ifndef DEBUFFATTACKTARGETSKILL_H_
#define DEBUFFATTACKTARGETSKILL_H_

#include "../AttackTargetSkill.h"

class DeBuffAttackTargetSkill : public AttackTargetSkill {
protected:

	float speed;

	float duration;

	int meleeDamagePenalty;
	int meleeAccuracyPenalty;

	int rangedDamagePenalty;
	int rangedAccuracyPenalty;

	int defensePenalty;
	int speedPenalty;

	float nextAttackDelay;

	String selfEffect;

	String flyText;


public:
	DeBuffAttackTargetSkill(const String& Name, const String& anim, ZoneProcessServerImplementation* serv) : AttackTargetSkill(Name, anim, DEBUFF, serv) {

		duration = 0;

		meleeDamagePenalty = 0;
		meleeAccuracyPenalty = 0;

		rangedDamagePenalty = 0;
		rangedAccuracyPenalty = 0;

		defensePenalty = 0;
		speedPenalty = 0;

		nextAttackDelay = 0;

		speed = 0;

	}

	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		int damage = calculateDamage(creature, target);

		/*if (doAnimation) {
			if (animCRC == 0 && creature->isPlayer()) {
				Player* player = (Player*) creature;
				String anim = Animations::getRandomAnimation();
				uint32 animationCRC = String::hashCode(anim);
				player->doCombatAnimation(targetCreature, animationCRC, 1);
				creature->sendSystemMessage(anim);
			} else
				creature->doCombatAnimation(targetCreature, animCRC, (damage > 0));
		}*/

		if (damage == 0)
			return 0;

		doAnimations(creature, target);

		return damage;
	}

	void doAnimations(CreatureObject* creature, SceneObject* target) {
		CreatureObject* targetCreature = (CreatureObject*) target;

		if (!flyText.isEmpty())
			targetCreature->showFlyText("combat_effects", flyText , 0, 255, 0);

		if (!selfEffect.isEmpty())
			creature->playEffect(selfEffect, "");
	}

	float getSpeed() {
		return speed;
	}

	int calculateDamage(CreatureObject* creature, SceneObject* target) {
		/*
		player->AddMeleeAccuracy(MeleeAccuracyPenalty, time);
		player->AddMeleeDamage(MeleeDamagePenalty, time);

		player->AddRangedAccuracy(RangedAccuracyPenalty, time);
		player->AddRangedDamage(RangedDamagePenalty, time);

		player->AddDefense(DefensePenalty, time);
	 	player->AddSpeed(SpeedPenalty, time);

		*/
		CreatureObject* targetCreature = NULL;
		if (target->isPlayer() || target->isNonPlayerCreature())
			targetCreature = (CreatureObject*) target;
		else
			return 0;

		if (nextAttackDelay > 0) {
			if (targetCreature->setNextAttackDelay((int)nextAttackDelay*1000)) {
				StringBuffer msg;
				msg << targetCreature->getCharacterName().toString() << " has been delayed for " << (int)nextAttackDelay << " seconds";
				creature->sendSystemMessage(msg.toString());
			} else {
				StringBuffer msg;
				msg << "You failed to delay " << targetCreature->getCharacterName().toString();
				creature->sendSystemMessage(msg.toString());
			}
		}

		return 1;
	}

	void setMeleeDamagePenalty(int dmg) {
		meleeDamagePenalty = dmg;
	}

	void setRangedDamagePenalty(int dmg) {
		meleeDamagePenalty = dmg;
	}

	void setMeleeAccuracyPenalty(int acc) {
		meleeAccuracyPenalty = acc;
	}

	void setRangedAccuracyPenalty(int acc) {
		rangedAccuracyPenalty = acc;
	}

	void setDefensePenalty(int def) {
		defensePenalty = def;
	}

	void setSpeedPenalty(int speed) {
		speedPenalty = speed;
	}

	void setNextAttackDelay(float tm) {
		nextAttackDelay = tm;
	}

	void setFlyText(const String& name) {
		flyText = name;
	}

	void setSpeed(float sp) {
		speed = sp;
	}

	void setForceCost(int forcecost) {
		forceCost = forcecost;
	}

	bool calculateCost(CreatureObject* creature) {
		if (!creature->isPlayer())
			return true;

		Player* player = (Player*)creature;

		if (forceCost > 0) {
			if (forceCost > player->getForcePower())
				return false;
			else
				player->changeForcePowerBar(-forceCost);
		}

		return true;
	}


	void setDuration(float dur) {
		duration = dur;
	}

	void setSelfEffect(const String& name) {
		selfEffect = name;
	}

	inline int getMeleeDamagePenalty() {
		return meleeDamagePenalty;
	}

	inline int getRangedDamagePenalty() {
		return rangedDamagePenalty;
	}

	inline int getMeleeAccuracyPenalty() {
		return meleeAccuracyPenalty;
	}

	inline int getRangedAccuracyPenalty() {
		return rangedAccuracyPenalty;
	}

	inline int getdDefensePenalty() {
		return defensePenalty;
	}

	inline int getSpeedPenalty() {
		return speedPenalty;
	}

};

#endif /*DEBUFFATTACKTARGETSKILL_H_*/
