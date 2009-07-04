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

#ifndef FORCEPOWERSPOOLATTACKTARGETSKILL_H_
#define FORCEPOWERSPOOLATTACKTARGETSKILL_H_

class ForcePowersPoolAttackTargetSkill : public AttackTargetSkill {
private:
	int attackType;
	int damageType;
	float minDamage;
	float maxDamage;
	float speed;

public:
	ForcePowersPoolAttackTargetSkill(const String& name, const String& anim, ZoneProcessServerImplementation* serv) : AttackTargetSkill(name, anim, FORCE, serv) {
		healthPoolAttackChance = 50;
		strengthPoolAttackChance = 0;
		constitutionPoolAttackChance = 0;

		actionPoolAttackChance = 35;
		quicknessPoolAttackChance = 0;
		staminaPoolAttackChance = 0;

		mindPoolAttackChance = 15;
		focusPoolAttackChance = 0;
		willpowerPoolAttackChance = 0;

		minDamage = 0;
		maxDamage = 0;
	}

	/*
	 * doSkill:
	 *     returns damage (-1 for miss)
	 */
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

	/*
	 * calculateDamage:
	 *     returns damage
	 */
	virtual int calculateDamage(CreatureObject* creature, SceneObject* target) {
		return server->getCombatManager()->calculateForceDamage(creature, (TangibleObject*)target, this, attackType, damageType, minDamage, maxDamage);
	}

	inline int getHitChance(CreatureObject* creature, CreatureObject* targetCreature) {
		int accuracy = 0;
		int hitChance = 0;

		if (creature->isPlayer()) {
			Player* player = (Player*)creature;
			switch (attackType) {
			case 1: // Force throw
				accuracy = player->getSkillMod("forcethrow_accuracy");
				break;
			case 2: // Force Lightning
				accuracy = player->getSkillMod("forcelightning_accuracy");
				break;
			case 3: // Mindblast
				accuracy = player->getSkillMod("mindblast_accuracy");
				break;
			case 4: // Force knockdown
				accuracy = player->getSkillMod("forcethrow_accuracy");
				break;
			case 5:  // Force choke
				accuracy = 0;
				break;
			default:
				System::out << "Unknown force power type " << attackType << endl;
				break;
			}
		}
		else {
			accuracy = creature->getAccuracy();
		}

		int targetDefense = server->getCombatManager()->getTargetDefense(creature,
				targetCreature, FORCEATTACK);

		// Calculation based on the DPS calculation spreadsheet
		float accTotal = 66.0; // Base chance

		float blindState = 0;
		if (creature->isBlinded())
			blindState = 50;
		float stunBonus =0;
		if (targetCreature->isStunned())
			stunBonus = 50;

		float ability = 50.0; // Don't know what this is taken from spreadsheet

		accTotal += (accuracy + ability + stunBonus - targetDefense - blindState) / 2.0;

		if (accTotal > 100)
			accTotal = 100.0;
		else if (accTotal < 0)
			accTotal = 0;

		hitChance = (int)(accTotal + 0.5);

		System::out << "hitChance:[" << hitChance << "]" << endl;

		return hitChance;
	}

	inline void setDamageType(int dmg) {
		damageType = dmg;
	}

	inline int getDamageType() {
		return damageType;
	}

	inline void setMinDamage(float mindamage) {
		minDamage = mindamage;
	}

	inline void setMaxDamage(float maxdamage) {
		maxDamage = maxdamage;
	}

	inline void setAttackType(int attack) {
		attackType = attack;
	}

	inline int getAttackType() {
		return attackType;
	}

	inline int getForceCost() {
		return forceCost;
	}

	inline void setForceCost(int forcecost) {
		forceCost = forcecost;
	}

	bool calculateCost(CreatureObject* creature) {
		if (!creature->isPlayer())
			return true;

		Player* player = (Player*)creature;

		if (forceCost < 0)
			forceCost = 0;

		if (forceCost > 0) {
			if (forceCost > player->getForcePower())
				return false;
			else
				player->changeForcePowerBar(-forceCost);
		}

		return true;
	}

	void setSpeed(float spd) {
		speed = spd;
	}

	float calculateSpeed(CreatureObject* creature) {
		// TODO: Add in speed changes for enhancer skill
		return speed;
	}
};

#endif /* FORCEPOWERSPOOLATTACKTARGETSKILL_H_ */
