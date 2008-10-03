--Copyright (C) 2007 <SWGEmu>
 
--This File is part of Core3.
 
--This program is free software; you can redistribute 
--it and/or modify it under the terms of the GNU Lesser 
--General Public License as published by the Free Software
--Foundation; either version 2 of the License, 
--or (at your option) any later version.
 
--This program is distributed in the hope that it will be useful, 
--but WITHOUT ANY WARRANTY; without even the implied warranty of 
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
--See the GNU Lesser General Public License for
--more details.
 
--You should have received a copy of the GNU Lesser General 
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
--Linking Engine3 statically or dynamically with other modules 
--is making a combined work based on Engine3. 
--Thus, the terms and conditions of the GNU Lesser General Public License 
--cover the whole combination.
 
--In addition, as a special exception, the copyright holders of Engine3 
--give you permission to combine Engine3 program with free software 
--programs or libraries that are released under the GNU LGPL and with 
--code included in the standard release of Core3 under the GNU LGPL 
--license (or modified versions of such code, with unchanged license). 
--You may copy and distribute such a system following the terms of the 
--GNU LGPL for Engine3 and the licenses of the other code concerned, 
--provided that you include the source code of that other code when 
--and as the GNU LGPL requires distribution of source code.
 
--Note that people who make modified versions of Engine3 are not obligated 
--to grant this special exception for their modified versions; 
--it is their choice whether to do so. The GNU Lesser General Public License 
--gives permission to release a modified version without this exception; 
--this exception also makes it possible to release a modified version 
--which carries forward this exception.

palpatineAttack1 = {
	attackname = "palpatineAttack1",
	animation = "force_lightning_1_particle_level_1_light",
	
	requiredWeaponType = RANGED,

	range = 64,

	damageRatio = 50,

	speedRatio = 1,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 100,
		
	knockdownChance = 50,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 50,
	blindChance = 50,
	stunChance = 50,
	intimidateChance = 50,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(palpatineAttack1)

-----------------------------------------------

palpatineAttack2 = {
	attackname = "palpatineAttack2",
	animation = "force_intimidate_chain",
	
	requiredWeaponType = RANGED,

	range = 64,

	damageRatio = 50,

	speedRatio = 1,
	coneAngle = 0,

	areaRange = 32,
	accuracyBonus = 100,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 80,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss"
}

AddRandomPoolAttackTargetSkill(palpatineAttack2)

-----------------------------------------------
palpatineAttack3 = {
attackname = "palpatineAttack3",
animation = "force_lightning_1_particle_level_2_light",

	requiredWeaponType = RANGED,
	
	range = 64,
	damageRatio = 50,
	speedRatio = 1,
	areaRange = 32,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 50,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss"
}

AddRandomPoolAttackTargetSkill(palpatineAttack3)

-----------------------------------------------

palpatineAttack4 = {
	attackname = "palpatineAttack4",
	animation = "force_weaken_1_particle_level_1_medium",
	
	requiredWeaponType = RANGED,

	range = 64,

	damageRatio = 50,

	speedRatio = 1,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 100,
		
	knockdownChance = 50,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 50,
	blindChance = 50,
	stunChance = 50,
	intimidateChance = 50,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss"
}

AddRandomPoolAttackTargetSkill(palpatineAttack4)

-----------------------------------------------------------------------

palpatineAttack5 = {
	attackname = "palpatineAttack5",
	animation = "force_lightning_1_particle_level_3_medium",
	
	requiredWeaponType = RANGED,

	range = 64,

	damageRatio = 50,

	speedRatio = 1,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 100,
		
	knockdownChance = 50,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 50,
	blindChance = 50,
	stunChance = 50,
	intimidateChance = 50,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss"
}

AddRandomPoolAttackTargetSkill(palpatineAttack5)

-----------------------------------------------------------------------

palpatineAttack6 = { 
	attackname = "palpatineAttack6",
	animation = "force_weaken_1_particle_level_1_medium",

	requiredWeaponType = RANGED,
	
	range = 64,
	damageRatio = 40,
	speedRatio = 2.0,
	areaRange = 32,
	accuracyBonus = 50,
	
	postureDownChance = 20,
		
	healthAttackChance = 90,
	actionAttackChance = 70,
	mindAttackChance = 50,

	dotChance = 50,
	tickStrengthOfHit = 10,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
	bleedingType = HEALTH,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss"
}

AddDotPoolAttackTargetSkill(palpatineAttack6)

-----------------------------------------------------------------------

palpatineAttack7 = { 
	attackname = "palpatineAttack7",
	animation = "force_lightning_1_arc_particle_level_5_medium",

	requiredWeaponType = RANGED,
	
	range = 64,
	damageRatio = 50,
	speedRatio = 1.0,
	coneAngle = 80,
	areaRange = 32,
	accuracyBonus = 100,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 95,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "forcelightningcone2_block",
	CbtSpamCounter = "forcelightningcone2_counter",
    CbtSpamEvade = "forcelightningcone2_evade",
    CbtSpamHit = "forcelightningcone2_hit",
    CbtSpamMiss = "forcelightningcone2_miss"
}

AddDotPoolAttackTargetSkill(palpatineAttack7)

-----------------------------------------------------------------------

palpatineAttack8 = { 
	attackname = "palpatineAttack8",
	animation = "force_knockdown_1_arc_particle_level_1",

	requiredWeaponType = RANGED,
	
	range = 64,
	damageRatio = 50,
	speedRatio = 1.0,
	coneAngle = 50,
	areaRange = 32,
	accuracyBonus = 100,
	
	knockdownChance = 95,
	postureDownChance = 70,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "forceknockdown3_block",
	CbtSpamCounter = "forceknockdown3_counter",
	CbtSpamEvade = "forceknockdown3_evade",
	CbtSpamHit = "forceknockdown3_hit",
	CbtSpamMiss = "forceknockdown3_miss"
}

AddDotPoolAttackTargetSkill(palpatineAttack8)

-----------------------------------------------------------------------
