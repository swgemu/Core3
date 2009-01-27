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

#ifndef THROWATTACKTARGETSKILL_H_
#define THROWATTACKTARGETSKILL_H_

#include "../AttackTargetSkill.h"
#include "../../../../tangible/weapons/ThrowableWeapon.h"
#include "../../../../tangible/weapons/throwable/TrapThrowableWeapon.h"

class ThrowAttackTargetSkill: public AttackTargetSkill {
protected:
	bool missed;
	bool isDebuff;

	int dotType;

	int snareStateChance;
	int rootStateChance;

	int meleeDefDebuff;
	int rangedDefDebuff;
	int stunDefDebuff;
	int intimidateDefDebuff;

	String debuffHitMessage;
	String debuffStrFile;
	String debuffMissMessage;
public:
	/*
	 * The constructor.
	 * \param name The skill name.
	 * \param anim The animation.
	 * \param serv The ZoneProcessServerImplementation.
	 */
	ThrowAttackTargetSkill(const String& name, const String& anim, int type,
			ZoneProcessServerImplementation* serv) :
		AttackTargetSkill(name, anim, type, serv) {
		healthPoolAttackChance = 0;
		strengthPoolAttackChance = 0;
		constitutionPoolAttackChance = 0;

		actionPoolAttackChance = 0;
		quicknessPoolAttackChance = 0;
		staminaPoolAttackChance = 0;

		mindPoolAttackChance = 0;
		focusPoolAttackChance = 0;
		willpowerPoolAttackChance = 0;

		type = THROW;
		damageRatio = 1.0;

		requiredWeaponType = 0xFF;

		range = 32.0f;

		missed = false;
		isDebuff = false;

		dotType = 0;

		snareStateChance = 0;
		rootStateChance = 0;

		meleeDefDebuff = 0;
		rangedDefDebuff = 0;
		stunDefDebuff = 0;
		intimidateDefDebuff = 0;

		debuffHitMessage = "";
		debuffStrFile = "";
		debuffMissMessage = "";

	}

	/*
	 * Activates the target skill (throw).
	 * \param creature The creature, that activates the skill.
	 * \param target The target.
	 * \param modifier The modifiers, contains the traps object id.
	 */
	virtual int doSkill(CreatureObject* creature, SceneObject* target,
			const String& modifier, bool doAnimation) {
		return 0;
	}

	void doMiss(CreatureObject* creature, CreatureObject* target, int32 damage) {

		target->showFlyText("trap/trap", "sys_miss", 0xFF, 0xFF, 0xFF);
	}

	/*
	 * Calculates the damage of the trap. Calls getCombatManager::calculateTrapDamage.
	 * \param creature The creature, that throws the trap.
	 * \param target The target.
	 * \param weapon The trap.
	 * \return Returns Returns the damage.
	 */
	virtual int calculateTrapDamage(CreatureObject* creature,
				SceneObject* target, Weapon* weapon) {
		return 0;
	}

	/**
	 * Applies the dot.
	 * \param targetCreature The target.
	 * \param damage The damage. Dot strength = damage / 3;
	 */
	void applyDot(CreatureObject* creature,CreatureObject* targetCreature, float damage) {
		if (dotType > 0) {
			int bleedingDotStrength = (int)(damage / 3);
			targetCreature->addDotState(creature,nameCRC,CreatureState::BLEEDING, bleedingDotStrength, CreatureAttribute::MIND, 60,50,targetCreature->getSkillMod("resistance_bleeding"));
		}
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

	/*
	 * Applies the states to the target.
	 * \param creature The skill user.
	 * \param targetCreature The target.
	 */
	void calculateStates(CreatureObject* creature,
			CreatureObject* targetCreature) {
		if (hasStateChance)
			return server->getCombatManager()->calculateTrapStates(creature, targetCreature, this);
	}

	/*
	 * Find the trap in the inventory.
	 * \param creature The skill user.
	 * \param modifier The modifier contains the traps object id.
	 * \return The trap.
	 */
	ThrowableWeapon* getThrowableWeapon(CreatureObject* creature, const String& modifier) {
		if (!modifier.isEmpty()) {
			StringTokenizer tokenizer(modifier);
			String poolName;
			uint64 objectid = 0;

			tokenizer.setDelimeter("|");

			if (tokenizer.hasMoreTokens())
				objectid = tokenizer.getLongToken();

			if (objectid > 0) {
				SceneObject* invObj = creature->getInventoryItem(objectid);

				if (invObj != NULL && invObj->isTangible()) {
					TangibleObject* tano = (TangibleObject*) invObj;

					if (tano->isThrowable()) {
						ThrowableWeapon* twp = (ThrowableWeapon*) tano;

						return twp;
					}
				}
			}
		}

		return NULL;
	}

	inline void setDotType(int type) {
		dotType = type;
	}

	inline int getDotType() {
		return dotType;
	}

	inline void setSnareChance(int chance) {
		snareStateChance = chance;
		hasStateChance = true;
	}

	inline void setRootChance(int chance) {
		rootStateChance = chance;
		hasStateChance = true;
	}

	inline void setMeleeDefDebuff(int dBuff) {
		meleeDefDebuff = dBuff;
		isDebuff = true;
	}

	inline void setRangedDefDebuff(int dBuff) {
		rangedDefDebuff = dBuff;
		isDebuff = true;
	}

	inline void setStunDefDebuff(int dBuff) {
		stunDefDebuff = dBuff;
		isDebuff = true;
	}

	inline void setIntimidateDefDebuff(int dBuff) {
		intimidateDefDebuff = dBuff;
		isDebuff = true;
	}

	inline int getMeleeDefDebuff() {
		return meleeDefDebuff;
	}

	inline int getRangedDefDebuff() {
		return rangedDefDebuff;
	}

	inline int getStunDefDebuff() {
		return stunDefDebuff;
	}

	inline int getIntimidateDefDebuff() {
		return intimidateDefDebuff;
	}

	inline void setDeBuffHitMessage(const String& ename) {
		debuffHitMessage = ename;
	}

	inline String getDeBuffHitMessage() {
		return debuffHitMessage;
	}

	inline void setDeBuffStrFile(const String& ename) {
		debuffStrFile = ename;
	}

	inline String getDeBuffStrFile() {
		return debuffStrFile;
	}

	inline void setDeBuffMissMessage(const String& ename) {
		debuffMissMessage = ename;
	}

	inline String getDeBuffMissMessage() {
		return debuffMissMessage;
	}

	inline bool isMissed() {
		return missed;
	}

	inline bool isStateTap() {
		return hasStateChance;
	}

	inline bool isDebuffTrap() {
		return isDebuff;
	}
	inline int getSnareChance() {
		return snareStateChance;
	}

	inline int getRootChance() {
		return rootStateChance;
	}
};

#endif /* THROWDIRECTPOOLATTACKTARGETSKILL_H_ */
