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

#ifndef DIRECTPOOLATTACKTARGETSKILL_H_
#define DIRECTPOOLATTACKTARGETSKILL_H_

#include "../AttackTargetSkill.h"

class DirectPoolAttackTargetSkill : public AttackTargetSkill {
public:
	DirectPoolAttackTargetSkill(const string& name, const string& anim, ZoneProcessServerImplementation* serv) : AttackTargetSkill(name, anim, DIRECT, serv) {
		healthPoolAttackChance = 0;
		actionPoolAttackChance = 0;
		mindPoolAttackChance = 0;
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const string& modifier, bool doAnimation = true) {
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
		Weapon* weapon = creature->getWeapon();

		CreatureObject* targetCreature = NULL;
		if (target->isPlayer() || target->isNonPlayerCreature())
			targetCreature = (CreatureObject*) target;

		float minDamage = 0;
		float maxDamage = 0;
		float healthDamage = 0;
		float actionDamage = 0;
		float mindDamage = 0;
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

		float damage = 0;
		int average = 0;

		int diff = (int)maxDamage - (int)minDamage;
		if (diff >= 0)
			average = System::random(diff) + (int)minDamage;

		float globalMultiplier = CombatManager::GLOBAL_MULTIPLIER;
		if (creature->isPlayer() && !target->isPlayer())
			globalMultiplier *= CombatManager::PVE_MULTIPLIER;
		else if (creature->isPlayer() && target->isPlayer())
			globalMultiplier *= CombatManager::PVP_MULTIPLIER;

		if (targetCreature != NULL) {

			int rand = System::random(100);

			if (getHitChance(creature, targetCreature) > rand) {
				int secondaryDefense = checkSecondaryDefenses(creature, targetCreature);

				if (secondaryDefense < 2) {
					if (secondaryDefense == 1)
						damage = damage / 2;

					//Work out the number of pools that may be affected
					int poolsAffected = 0;
					int totalPercentage = 0;  // Temporary fix until percentages in lua are corrected

					if (healthPoolAttackChance > 0) {
						poolsAffected++;
						totalPercentage += healthPoolAttackChance;
					}
					if (actionPoolAttackChance > 0) {
						poolsAffected++;
						totalPercentage += actionPoolAttackChance;
					}
					if (mindPoolAttackChance > 0) {
						poolsAffected++;
						totalPercentage += mindPoolAttackChance;
					}

					float damage = damageRatio * average * globalMultiplier;
					float individualDamage = damage / poolsAffected;

					for (int i = 0; i < poolsAffected; i++) {
						int pool = System::random(totalPercentage);

						int bodyPart = 0;
						if (pool < healthPoolAttackChance) {
							healthDamage = individualDamage;
							bodyPart = System::random(5)+1;
							calculateDamageReduction(creature, targetCreature, healthDamage);
						}
						else if (pool < healthPoolAttackChance + actionPoolAttackChance) {
							actionDamage = individualDamage;
							bodyPart = System::random(1)+7;
							calculateDamageReduction(creature, targetCreature, actionDamage);
						}
						else {
							mindDamage = individualDamage;
							bodyPart = 9;
							calculateDamageReduction(creature, targetCreature, mindDamage);
						}

						reduction += applyDamage(creature, targetCreature, (int32) individualDamage, bodyPart);

						if (hasCbtSpamHit())
							creature->sendCombatSpam(targetCreature, NULL, (int32)individualDamage, getCbtSpamHit());

					}
				}


				if (weapon != NULL) {
					doDotWeaponAttack(creature, targetCreature, 0);

					if (weapon->decreasePowerupUses())
						weapon->setUpdated(true);
					else if (weapon->hasPowerup())
						weapon->removePowerup((Player*)creature, true);
				}

			} else {
				doMiss(creature, targetCreature, (int32) damage);
				return 0;
			}
		} else {
			return (int32)damageRatio * average;
		}

		return (int32)damage - reduction;
	}
};

#endif /*DIRECTPOOLATTACKSKILL_H_*/
