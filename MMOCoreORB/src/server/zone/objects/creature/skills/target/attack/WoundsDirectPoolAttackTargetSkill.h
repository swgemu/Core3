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

#ifndef WOUNDSDIRECTPOOLATTACKTARGETSKILL_H_
#define WOUNDSDIRECTPOOLATTACKTARGETSKILL_H_

#include "DirectPoolAttackTargetSkill.h"

class WoundsDirectPoolAttackTargetSkill : public DirectPoolAttackTargetSkill {
public:
	WoundsDirectPoolAttackTargetSkill(const String& name, const String& anim, ZoneProcessServerImplementation* serv) : DirectPoolAttackTargetSkill(name, anim, serv) {
		skillType = WOUNDS;
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
		if (target->isPlayer() || target->isNonPlayerCreature()) {
			CreatureObject* targetCreature = (CreatureObject*) target;
			if (damage && targetCreature->hasAttackDelay())
				targetCreature->clearAttackDelay();
		}

		doAnimations(creature, target);

		return damage;
	}

	int calculateDamage(CreatureObject* creature, SceneObject* target) {
		Weapon* weapon = creature->getWeapon();

		CreatureObject* targetCreature = NULL;
		if (target->isPlayer() || target->isNonPlayerCreature())
			targetCreature = (CreatureObject*) target;

		float minDamage = 0;
		float maxDamage = 0;
		int woundsRatio = 5;
		int bodyPart = 0;
		int reduction = 0;

		if (weapon != NULL) {
			if (weapon->isCertified()) {
				minDamage = weapon->getMinDamage();
				maxDamage = weapon->getMaxDamage();
			}
			else {
				minDamage = weapon->getMinDamage() / 5;
				maxDamage = weapon->getMaxDamage() / 5;
			}
		} else {
			maxDamage = (float)creature->getSkillMod("unarmed_damage");
			if (maxDamage < 25)
				maxDamage = 25;
			minDamage = maxDamage / 2;
		}

		if (targetCreature != NULL)
			checkMitigation(creature, targetCreature, minDamage, maxDamage);

		int average = 0;

		int diff = (int)maxDamage - (int)minDamage;
		if (diff >= 0)
			average = System::random(diff) + (int)minDamage;

		float damage = damageRatio * average;

		if (targetCreature != NULL) {

			calculateDamageReduction(creature, targetCreature, damage);

			int pool = System::random(100);

			if (getHitChance(creature, targetCreature) > System::random(100)) {

				int secondaryDefense = checkSecondaryDefenses(creature, targetCreature);
				if (secondaryDefense < 2) {
					if (secondaryDefense == 1)
						damage = damage / 2;

					if (pool < healthPoolAttackChance)
						bodyPart = System::random(5)+1;
					else if (pool < healthPoolAttackChance + actionPoolAttackChance)
						bodyPart = System::random(1)+7;
					else if (pool < mindPoolAttackChance)
						bodyPart = 9;
					} else
						return 0;
			} else {
				doMiss(creature, targetCreature, (int32) damage);
				return 0;
			}

			if (hasCbtSpamHit())
				creature->sendCombatSpam(targetCreature, NULL, (int32)damage, getCbtSpamHit());

			if (bodyPart < 7) {
				reduction = applyHealthPoolDamage(creature, targetCreature, (int32) damage, bodyPart);
				applyHealthPoolWoundsDamage(targetCreature, (int32) damage / 25);
			} else if (bodyPart  < 9) {
				reduction = applyActionPoolDamage(creature, targetCreature, (int32) damage, bodyPart);
				applyActionPoolWoundsDamage(targetCreature, (int32) damage / 25);
			} else {
				reduction = applyMindPoolDamage(creature, targetCreature, (int32) damage);
				applyMindPoolWoundsDamage(targetCreature, (int32) damage / 25);
			}
		} else {
			return (int32)damage;
		}

		return (int32)damage - reduction;
	}

	void applyHealthPoolWoundsDamage(CreatureObject* targetCreature, int32 damage) {
		targetCreature->changeHealthWoundsBar(-damage);
	}

	void applyActionPoolWoundsDamage(CreatureObject* targetCreature, int32 damage) {
		targetCreature->changeActionWoundsBar(-damage);
	}

	void applyMindPoolWoundsDamage(CreatureObject* targetCreature, int32 damage) {
		targetCreature->changeMindWoundsBar(-damage);
	}

};

#endif /*WOUNDSDIRECTPOOLATTACKTARGETSKILL_H_*/
