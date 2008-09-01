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

class SceneObject;
class ZoneServer;
class Player;
class CreatureObject;
class AttackableObject;
class MountCreature;
class Weapon;

class TargetSkill;
class ZoneProcessServerImplementation;
class CombatAction;

class CommandQueueAction;

class CombatManager {
	ZoneProcessServerImplementation* server;
	
private:
	bool doAction(CreatureObject* attacker, SceneObject* target, TargetSkill* skill, string& modifier, CombatAction* actionMessage);
	uint32 getDefaultAttackAnimation(CreatureObject* creature);
	
public:
	CombatManager(ZoneProcessServerImplementation* srv);

	float handleAction(CommandQueueAction* action);
	void handleAreaAction(CreatureObject* creature, SceneObject* target, CommandQueueAction* action, CombatAction* actionMessage);
	
	float doTargetSkill(CommandQueueAction* action);
	float doSelfSkill(CommandQueueAction* action);
	
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
	float getWeaponAccuracy(float currentRange, Weapon* weapon);
	uint32 getTargetDefense(CreatureObject* creature, CreatureObject* targetCreature, Weapon* weapon);
	
};

#endif /*COMBATMANAGER_H_*/
