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

	int MeleeDamagePenalty;
	int MeleeAccuracyPenalty;

	int RangedDamagePenalty;
	int RangedAccuracyPenalty;

	int DefensePenalty;
	int SpeedPenalty;

	float nextAttackDelay;

	string selfEffect;

	string FlyText;


public:
	DeBuffAttackTargetSkill(const string& Name, const string& anim, ZoneProcessServerImplementation* serv) : AttackTargetSkill(Name, anim, serv) {

		duration = 0;

		MeleeDamagePenalty = 0;
		MeleeAccuracyPenalty = 0;

		RangedDamagePenalty = 0;
		RangedAccuracyPenalty = 0;

		DefensePenalty = 0;
		SpeedPenalty = 0;

		nextAttackDelay = 0;

		speed = 0;

	}

	int doSkill(CreatureObject* creature, SceneObject* target, const string& modifier, bool doAnimation = true) {
		int damage = calculateDamage(creature, target);

		/*if (doAnimation) {
			if (animCRC == 0 && creature->isPlayer()) {
				Player* player = (Player*) creature;
				string anim = Animations::getRandomAnimation();
				uint32 animationCRC = String::hashCode(anim);
				player->doCombatAnimation(targetCreature, animationCRC, 1);
				creature->sendSystemMessage(anim);
			} else
				creature->doCombatAnimation(targetCreature, animCRC, (damage > 0));
		}*/

		if(damage == 0)
			return 0;

		doAnimations(creature, target);

		return damage;
	}

	void doAnimations(CreatureObject* creature, SceneObject* target) {
		CreatureObject* targetCreature = (CreatureObject*) target;
		if (FlyText.size() != 0)
			targetCreature->showFlyText("combat_effects", FlyText , 0, 255, 0);

		if (selfEffect.size() != 0)
			creature->playEffect(selfEffect, "");
	}

	float calculateSpeed(CreatureObject* creature) {
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
				stringstream msg;
				msg << targetCreature->getCharacterName().c_str() << " has been delayed for " << (int)nextAttackDelay << " seconds";
				creature->sendSystemMessage(msg.str());
			} else {
				stringstream msg;
				msg << "You failed to delay " << targetCreature->getCharacterName().c_str();
				creature->sendSystemMessage(msg.str());
			}
		}

		return 1;
	}

	void setMeleeDamagePenalty(int dmg) {
		MeleeDamagePenalty = dmg;
	}

	void setRangedDamagePenalty(int dmg) {
		MeleeDamagePenalty = dmg;
	}

	void setMeleeAccuracyPenalty(int acc) {
		MeleeAccuracyPenalty = acc;
	}

	void setRangedAccuracyPenalty(int acc) {
		RangedAccuracyPenalty = acc;
	}

	void setDefensePenalty(int def) {
		DefensePenalty = def;
	}

	void setSpeedPenalty(int speed) {
		SpeedPenalty = speed;
	}

	void setNextAttackDelay(float tm) {
		nextAttackDelay = tm;
	}

	void setFlyText(const string& name) {
		FlyText = name;
	}

	void setSpeed(float sp) {
		speed = sp;
	}

	void setDuration(float dur) {
		duration = dur;
	}

	void setSelfEffect(const string& name) {
		selfEffect = name;
	}

	inline int getMeleeDamagePenalty() {
		return MeleeDamagePenalty;
	}

	inline int getRangedDamagePenalty() {
		return RangedDamagePenalty;
	}

	inline int getMeleeAccuracyPenalty() {
		return MeleeAccuracyPenalty;
	}

	inline int getRangedAccuracyPenalty() {
		return RangedAccuracyPenalty;
	}

	inline int getdDefensePenalty() {
		return DefensePenalty;
	}

	inline int getSpeedPenalty() {
		return SpeedPenalty;
	}

};

#endif /*DEBUFFATTACKTARGETSKILL_H_*/
