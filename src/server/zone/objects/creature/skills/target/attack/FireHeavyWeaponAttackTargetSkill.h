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

#ifndef FIREHEAVYWEAPONATTACKTARGETSKILL_H_
#define FIREHEAVYWEAPONATTACKTARGETSKILL_H_

#include "../AttackTargetSkill.h"
#include "../../../../tangible/weapons/ranged/HeavyRangedWeapon.h"

class FireHeavyWeaponAttackTarget: public AttackTargetSkill {
protected:

public:
	/*
	 * The constructor.
	 * \param name The skill name.
	 * \param anim The animation.
	 * \param serv The ZoneProcessServerImplementation.
	 */
	FireHeavyWeaponAttackTarget(const String& name, const String& anim, ZoneProcessServerImplementation* serv) : AttackTargetSkill(name, anim, HEAVYWEAPON, serv) {
		healthPoolAttackChance = 50;
		actionPoolAttackChance = 35;
		mindPoolAttackChance = 15;

		type = HEAVYWEAPON;
	}


	/*
	 * Activates the target skill (throw).
	 * \param creature The creature, that activates the skill.
	 * \param target The target.
	 * \param modifier The modifiers, contains the traps object id.
	 */
	virtual int doSkill(CreatureObject* creature, SceneObject* target,
			const String& modifier, bool doAnimation) {

		HeavyRangedWeapon* wpn = getHeavyRangedWeapon(creature, modifier);

		if (wpn == NULL)
			return 0;

		int damage = calculateHeavyWeaponDamage(creature,target,wpn);

		if (target->isPlayer() || target->isNonPlayerCreature()) {
			CreatureObject* targetCreature = (CreatureObject*) target;
			if (damage && targetCreature->hasAttackDelay())
				targetCreature->clearAttackDelay();
		}

		return damage;
	}

	/*
	 * Calculates the damage of the trap. Is not used.
	 * \param creature The creature, that throws the trap.
	 * \param target The target.
	 * \return Returns Returns always 0.
	 */
	virtual int calculateDamage(CreatureObject* creature, SceneObject* target) {
		return 0;
	}

	int calculateHeavyWeaponDamage(CreatureObject* creature, SceneObject* target,Weapon* weapon) {
		return server->getCombatManager()->calculateHeavyWeaponDamage(creature, (TangibleObject*)target, this, weapon);
	}

	/*
	 * Calculates the costs of the skill.
	 * \param creature The creature, that is checked.
	 * \return Returns if costs are applied.
	 */
	virtual bool calculateCost(CreatureObject* creature) {
		if (!creature->isPlayer())
			return true;

		Player* player = (Player*) creature;

		int wpnHealth = 20;
		int wpnAction = 80;
		int wpnMind = 10;

		int healthAttackCost = wpnHealth - (wpnHealth * creature->getStrength()
				/ 1500);
		int actionAttackCost = wpnAction - (wpnAction
				* creature->getQuickness() / 1500);
		int mindAttackCost = wpnMind - (wpnMind * creature->getFocus() / 1500);

		if (healthAttackCost < 0)
			healthAttackCost = 0;

		if (actionAttackCost < 0)
			actionAttackCost = 0;

		if (mindAttackCost < 0)
			mindAttackCost = 0;

		if (!player->changeHAMBars(-healthAttackCost, -actionAttackCost,
				-mindAttackCost))
			return false;

		return true;
	}

	float calculateSpeed(CreatureObject* creature, CommandQueueAction* action) {
		Weapon* weapon;
		float weaponSpeed;
		int speedMod = 0;

		if (creature == NULL)
			return 1.0f;

		if (action != NULL) {
			String actionModifier = action->getActionModifier();
			weapon = getHeavyRangedWeapon(creature,actionModifier);
			if (weapon != NULL)
				speedMod = creature->getSkillMod(weapon->getSpeedSkillMod());
			else //default to lightning heavy weapon
				speedMod = creature->getSkillMod("heavy_rifle_lightning_speed");
		}

		// Classic speed equation
		if (weapon != NULL)
			weaponSpeed = (1.0f - ((float)speedMod / 100.0f)) * getSpeedRatio() * weapon->getAttackSpeed();
		else
			weaponSpeed = (1.0f - ((float)speedMod / 100.0f)) * getSpeedRatio() * 2.0f;

		return MAX(weaponSpeed, 1.0f);
	}

	virtual uint64 useWeaponCharge(CreatureObject* creature, CommandQueueAction* action) {
		if (creature == NULL || action == NULL)
			return 0;

		if (creature->isPlayer()) {
			String actionModifier = action->getActionModifier();
			HeavyRangedWeapon* heavyWeapon= getHeavyRangedWeapon(creature,actionModifier);

			heavyWeapon->useCharge((Player*) creature);
			return heavyWeapon->getObjectID();
		}
		return 0;
	}

	virtual int getWeaponArea(CreatureObject* creature, CommandQueueAction* action) {
		if (creature == NULL || action == NULL)
			return 5; //default area range

		String actionModifier = action->getActionModifier();
		HeavyRangedWeapon* heavyWeapon = getHeavyRangedWeapon(creature,actionModifier);
		if (heavyWeapon != NULL)
			return heavyWeapon->getArea();
		return 5; //default area range
	}

	/*
	 * Find the trap in the inventory.
	 * \param creature The skill user.
	 * \param modifier The modifier contains the traps object id.
	 * \return The trap.
	 */
	HeavyRangedWeapon* getHeavyRangedWeapon(CreatureObject* creature, const String& modifier) {
		uint64 objectid = 0;

		if (!modifier.isEmpty()) {
			StringTokenizer tokenizer(modifier);

			tokenizer.setDelimeter("|");

			if (tokenizer.hasMoreTokens())
				objectid = tokenizer.getLongToken();
		} else {
			if (creature->isPlayer()) {
				Player* player = (Player*) creature;

				objectid = player->getHeavyRangedWeapon();
			}
		}

		if (objectid > 0) {
			SceneObject* invObj = creature->getInventoryItem(objectid);
			if (invObj != NULL)
				return (HeavyRangedWeapon* ) invObj;
		}

		return NULL;
	}
};

#endif /* FIREHEAVYWEAPONDIRECTPOOLATTACKTARGETSKILL_H_ */
