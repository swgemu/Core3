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

tuskenRangedAttack1 = {
	attackname = "tuskenRangedAttack1",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 10,

	speedRatio = 1.5,
	coneAngle = 0,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 5,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(tuskenRangedAttack1)

-----------------------------------------------------------------------

tuskenRangedAttack2 = {
	attackname = "tuskenRangedAttack2",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 15,

	speedRatio = 1.5,
	coneAngle = 0,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 5,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(tuskenRangedAttack2)

-----------------------------------------------------------------------

tuskenRangedAttack3 = {
	attackname = "tuskenRangedAttack3",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 10,

	speedRatio = 4,
	coneAngle = 60,

	areaRange = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(tuskenRangedAttack3)

-----------------------------------------------------------------------

tuskenRangedAttack4 = { 
	attackname = "tuskenRangedAttack4",
	animation = "fire_3_special_single_medium",

	requiredWeaponType = RIFLE,
	
	range = 64,
	damageRatio = 4.5,
	speedRatio = 3,
	areaRange = 0,
	accuracyBonus = 0,

	dotChance = 50,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 2,
	bleedingType = HEALTH,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddDotPoolAttackTargetSkill(tuskenRangedAttack4)

-----------------------------------------------------------------------

tuskenRangedAttack5 = {
	attackname = "tuskenRangedAttack5",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 10,

	speedRatio = 2,
	coneAngle = 60,

	areaRange = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(tuskenRangedAttack5)

-----------------------------------------------------------------------

tuskenRangedAttack6 = {
	attackname = "tuskenRangedAttack6",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 10,

	speedRatio = 2,
	coneAngle = 60,

	areaRange = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 20,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 20,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(tuskenRangedAttack6)

-----------------------------------------------------------------------

tuskenRangedAttack7 = {
	attackname = "tuskenRangedAttack7",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 5,

	speedRatio = 2,
	coneAngle = 60,

	areaRange = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(tuskenRangedAttack7)

-----------------------------------------------------------------------

tuskenRangedAttack8 = {
	attackname = "tuskenRangedAttack8",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 5,

	speedRatio = 2,
	coneAngle = 60,

	areaRange = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 10,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(tuskenRangedAttack8)

-----------------------------------------------------------------------

tuskenRangedAttack9 = {
	attackname = "tuskenRangedAttack9",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 5,

	speedRatio = 2,
	coneAngle = 60,

	areaRange = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 50,
	postureUpChance = 0,
	dizzyChance = 40,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(tuskenRangedAttack9)

-----------------------------------------------------------------------

tuskenRangedAttack10 = {
	attackname = "tuskenRangedAttack10",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 5,

	speedRatio = 2,
	coneAngle = 60,

	areaRange = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(tuskenRangedAttack10)

-----------------------------------------------------------------------

tuskenRangedAttack11 = {
	attackname = "tuskenRangedAttack11",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 5,

	speedRatio = 2,
	coneAngle = 60,

	areaRange = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 10,
	blindChance = 1,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(tuskenRangedAttack11)

-----------------------------------------------------------------------

tuskenRangedAttack12 = {
	attackname = "tuskenRangedAttack12",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 5,

	speedRatio = 2,
	coneAngle = 60,

	areaRange = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 1,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(tuskenRangedAttack12)

-----------------------------------------------------------------------

tuskenRangedAttack13 = {
	attackname = "tuskenRangedAttack13",
	animation = "fire_1_special_single_medium",
	
	requiredWeaponType = RIFLE,

	range = 64,

	damageRatio = 5,

	speedRatio = 2,
	coneAngle = 0,

	areaRange = 0,
	accuracyBonus = 10,
	
	dotChance = 80,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
	bleedingType = 0,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 2,
	diseaseType = HEALTH,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddDotPoolAttackTargetSkill(tuskenRangedAttack13)

-----------------------------------------------------------------------
