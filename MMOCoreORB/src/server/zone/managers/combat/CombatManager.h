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

#ifndef COMBATMANAGER_H_
#define COMBATMANAGER_H_

#include "engine/engine.h"

#define MELEEWEAPON(weapontype) ((weapontype < 4 || (weapontype > 6 && weapontype < 10)) ? true : false)
#define RANGEDWEAPON(weapontype) (((weapontype > 3 && weapontype < 7) || (weapontype > 6 && weapontype < 20)) ? true : false)
#define THROWNWEAPON(weapontype) ((weapontype > 19 && weapontype < 21) ? true : false)

class SceneObject;
class ZoneServer;
class Player;
class CreatureObject;
class AttackableObject;
class MountCreature;
class Weapon;

class TargetSkill;
class AttackTargetSkill;
class ThrowAttackTargetSkill;
class ZoneProcessServerImplementation;
class CombatAction;

class CommandQueueAction;

static uint32 defaultAttacks[] = {
			0x99476628, 0xF5547B91, 0x3CE273EC, 0x734C00C,
			0x43C4FFD0, 0x56D7CC78, 0x4B41CAFB, 0x2257D06B,
			0x306887EB
};

class CombatManager {
	ZoneProcessServerImplementation* server;

private:
	bool doAttackAction(CreatureObject* attacker, SceneObject* target, AttackTargetSkill* skill, String& modifier, CombatAction* actionMessage);
	uint32 getDefaultAttackAnimation(CreatureObject* creature);

public:
	static const float GLOBAL_MULTIPLIER = 1.5;
	static const float PVE_MULTIPLIER = 1.0;
	static const float PVP_MULTIPLIER = 0.25;

	CombatManager(ZoneProcessServerImplementation* srv);

	float handleAction(CommandQueueAction* action);
	void handleAreaAction(CreatureObject* creature, SceneObject* target, CommandQueueAction* action, CombatAction* actionMessage);

	float doTargetSkill(CommandQueueAction* action);
	float doSelfSkill(CommandQueueAction* action);
	float doCamoSkill(CommandQueueAction* action);
	float doGroupSkill(CommandQueueAction* action);

	bool handleMountDamage(CreatureObject* targetCreature, MountCreature* mount);

	// misc methods
	bool canAttack(Player* player, Player* targetPlayer);
	float getConeAngle(SceneObject* targetCreature, float CreatureVectorX, float CreatureVectorY, float DirectionVectorX, float DirectionVectorY);
	bool checkSkill(CreatureObject* creature, SceneObject* target, TargetSkill* skill);

	void requestDuel(Player* player, uint64 targetID);
	void requestDuel(Player* player, Player* targetPlayer);

	void requestEndDuel(Player* player, Player* targetPlayer);
	void requestEndDuel(Player* player, uint64 targetID);

	void freeDuelList(Player* player);

	void declineDuel(Player* player, uint64 targetID);
	void declineDuel(Player* player, Player* targetPlayer);

	//bool areInDuel(Player* player, Player* targetPlayer);

	void doDodge(CreatureObject* creature, CreatureObject* defender);
	void doCounterAttack(CreatureObject* creature, CreatureObject* defender);
	void doBlock(CreatureObject* creature, CreatureObject* defender);

	// calc methods
	void calculateDamageReduction(CreatureObject* creature, CreatureObject* targetCreature, float& damage);
	int calculatePostureMods(CreatureObject* creature, CreatureObject* targetCreature);
	void checkMitigation(CreatureObject* creature, CreatureObject* targetCreature, float& minDamage, float& maxDamage);
	int checkSecondaryDefenses(CreatureObject* creature, CreatureObject* targetCreature);
	int getHitChance(CreatureObject* creature, CreatureObject* targetCreature, int accuracyBonus);
	float getWeaponRangeMod(float currentRange, Weapon* weapon);
	uint32 getTargetDefense(CreatureObject* creature, CreatureObject* targetCreature, Weapon* weapon, bool forceAttack = false);
	int applyDamage(CreatureObject* attacker, CreatureObject* target, int32 damage, int part, AttackTargetSkill* askill);
	int applyTrapDamage(CreatureObject* attacker, CreatureObject* target, int32 damage, int part, AttackTargetSkill* askill,Weapon* weapon);
	int getArmorReduction(Weapon* weapon, CreatureObject* target, int damage, int location);
	bool calculateCost(CreatureObject* creature, float healthMultiplier, float actionMultiplier, float mindMultiplier, float forceMultiplier);
	float calculateWeaponAttackSpeed(CreatureObject* creature, TargetSkill* tskill);
	float calculateHealSpeed(CreatureObject* creature, TargetSkill* tskill);
	void calculateStates(CreatureObject* creature, CreatureObject* targetCreature, AttackTargetSkill* tskill);
	void calculateTrapStates(CreatureObject* creature, CreatureObject* targetCreature, ThrowAttackTargetSkill* tskill);
	void checkKnockDown(CreatureObject* creature, CreatureObject* targetCreature, int chance);
	void checkPostureDown(CreatureObject* creature, CreatureObject* targetCreature, int chance);
	void checkPostureUp(CreatureObject* creature, CreatureObject* targetCreature, int chance);
	int calculateDamage(CreatureObject* creature, SceneObject* target, AttackTargetSkill* skill, bool randompoolhit);
	int calculateTrapDamage(CreatureObject* creature, SceneObject* target, ThrowAttackTargetSkill* skill, bool randompoolhit, Weapon* weapon);
	void doDotWeaponAttack(CreatureObject* creature, CreatureObject* targetCreature, bool areaHit);
};

#endif /*COMBATMANAGER_H_*/
