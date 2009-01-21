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

#ifndef DOTPOOLATTACKTARGETSKILL_H_
#define DOTPOOLATTACKTARGETSKILL_H_

#include "../AttackTargetSkill.h"

class DotPoolAttackTargetSkill : public AttackTargetSkill {
protected:

	int dotChanceState;
	bool tickStrengthOfHit;

	int fireDotType;
	int fireDotStrength;

	int bleedingDotType;
	int bleedingDotStrength;

	int poisonDotType;
	int poisonDotStrength;

	int diseaseDotType;
	int diseaseDotStrength;

public:
	DotPoolAttackTargetSkill(const String& name, const String& anim, ZoneProcessServerImplementation* serv) : AttackTargetSkill(name, anim, DOT, serv) {

		dotChanceState = 0;

		fireDotType = 0;
		fireDotStrength = 0;

		bleedingDotType = 0;
		bleedingDotStrength = 0;

		poisonDotType = 0;
		poisonDotStrength = 0;

		diseaseDotType = 0;
		diseaseDotStrength = 0;

		tickStrengthOfHit= false;

	}

	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		int damage = calculateDamage(creature, target);


		if (target->isPlayer() || target->isNonPlayerCreature()) {
			CreatureObject* targetCreature = (CreatureObject*) target;
			if (damage && targetCreature->hasAttackDelay())
				targetCreature->clearAttackDelay();
		}

		doAnimations(creature, target);

		return damage;
	}

	int calculateDamage(CreatureObject* creature, SceneObject* target) {
		int damage = server->getCombatManager()->calculateWeaponDamage(creature, (TangibleObject*)target, this, true);
		if (damage > 0 && (target->isPlayer() || target->isNonPlayerCreature())) {
			CreatureObject* targetCreature = (CreatureObject*)target;
			checkDots(targetCreature, damage);
		}

		return damage;
	}

	void checkDots(CreatureObject* targetCreature, float damage) {
		int bleedResist = 0;
		int diseaseResist = 0;
		int fireResist = 0;
		int poisonResist = 0;

		if (fireDotType > 0)
			fireResist += targetCreature->getSkillMod("resistance_fire");
		if (bleedingDotType > 0)
			bleedResist += targetCreature->getSkillMod("resistance_bleeding");
		if (poisonDotType > 0)
			poisonResist += targetCreature->getSkillMod("resistance_poison");
		if (diseaseDotType > 0)
			diseaseResist += targetCreature->getSkillMod("resistance_disease");

		if (dotChanceState > 0 && System::random(100) < dotChanceState) {

		if (fireDotType > 0 && dotChanceState > 0 && System::random(100) < (dotChanceState-fireResist)) {
				if (tickStrengthOfHit)
					fireDotStrength = (int)(damage / 5);
				targetCreature->setOnFireState(fireDotStrength, fireDotType, 60);
		}

		if (bleedingDotType > 0 && dotChanceState > 0 && System::random(100) < (dotChanceState-bleedResist)) {
			if (tickStrengthOfHit)
				bleedingDotStrength = (int)(damage / 5);
			targetCreature->setBleedingState(bleedingDotStrength, bleedingDotType, 60);
		}

		if (poisonDotType > 0 && dotChanceState > 0 && System::random(100) < (dotChanceState-poisonResist)) {
			if (tickStrengthOfHit)
			poisonDotStrength = (int)(damage / 5);
			targetCreature->setPoisonedState(poisonDotStrength, poisonDotType, 60);
		}

		if (diseaseDotType > 0 && dotChanceState > 0 && System::random(100) < (dotChanceState-diseaseResist)) {
			if (tickStrengthOfHit)
				diseaseDotStrength = (int)(damage / 5);
			targetCreature->setDiseasedState(diseaseDotStrength, diseaseDotType, 60);
		}

		targetCreature->updateStates();
		}
	}

	void setDotChance(int dotchance) {
		dotChanceState = dotchance;
	}

	void setFireDotStrength(int str) {
		fireDotStrength = str;
	}

	void setFireDotType(int tp) {
		fireDotType = tp;
	}

	void setBleedingDotStrength(int str) {
		bleedingDotStrength = str;
	}

	void setBleedingDotType(int tp) {
		bleedingDotType = tp;
	}

	void setPoisonDotStrength(int str) {
		poisonDotStrength = str;
	}

	void setPoisonDotType(int tp) {
		poisonDotType = tp;
	}

	void setDiseaseDotStrength(int str) {
		diseaseDotStrength = str;
	}

	void setDiseaseDotType(int tp) {
		diseaseDotType = tp;
	}

	void setTickStrengthOfHit(bool t) {
		tickStrengthOfHit = t;
	}

};

#endif /*DOTPOOLATTACKTARGETSKILL_H_*/
