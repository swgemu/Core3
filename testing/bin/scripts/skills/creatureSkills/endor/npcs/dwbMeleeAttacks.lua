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


dwbMeleeAttack40 = { 
	attackname = "dwbMeleeAttack40",
	animation = "combo_4a_medium",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(dwbMeleeAttack40)

-----------------------------------------------------------------------

dwbMeleeAttack41 = { 
	attackname = "dwbMeleeAttack41",
	animation = "combo_3b_light",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(dwbMeleeAttack41)

-----------------------------------------------------------------------

dwbMeleeAttack42 = { 
	attackname = "dwbMeleeAttack42",
	animation = "combo_2d_medium",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.8,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 1,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(dwbMeleeAttack42)

-----------------------------------------------------------------------

dwbMeleeAttack43 = { 
	attackname = "dwbMeleeAttack43",
	animation = "combo_5b_light",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(dwbMeleeAttack43)

-----------------------------------------------------------------------


dwbMeleeAttack44 = { 
	attackname = "dwbMeleeAttack44",
	animation = "counter_low_left_light",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 50,
	actionAttackChance = 0,
	mindAttackChance = 0,

	dotChance = 5,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 1,
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

AddDotPoolAttackTargetSkill(dwbMeleeAttack44)

-----------------------------------------------------------------------

dwbMeleeAttack45 = { 
	attackname = "dwbMeleeAttack45",
	animation = "lower_posture_2hmelee_6",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.45,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 1,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(dwbMeleeAttack45)

-----------------------------------------------------------------------


dwbMeleeAttack46 = { 
	attackname = "dwbMeleeAttack46",
	animation = "combo_3c_light",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 50,
	actionAttackChance = 0,
	mindAttackChance = 0,

	dotChance = 5,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 1,
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

AddDotPoolAttackTargetSkill(dwbMeleeAttack46)

-----------------------------------------------------------------------

dwbMeleeAttack47 = { 
	attackname = "dwbMeleeAttack47",
	animation = "combo_4b_medium",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 50,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 0,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddDirectPoolAttackTargetSkill(dwbMeleeAttack47)

-----------------------------------------------------------------------

dwbMeleeAttack48 = { 
	attackname = "dwbMeleeAttack48",
	animation = "combo_3a_light",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 50,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 0,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddDirectPoolAttackTargetSkill(dwbMeleeAttack48)

-----------------------------------------------------------------------

dwbMeleeAttack49 = { 
	attackname = "dwbMeleeAttack49",
	animation = "combo_4b_medium",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.45,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 1,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(dwbMeleeAttack49)

-----------------------------------------------------------------------

dwbMeleeAttack50 = { 
	attackname = "dwbMeleeAttack50",
	animation = "combo_2b_medium",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.45,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 1,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(dwbMeleeAttack50)

-----------------------------------------------------------------------

dwbMeleeAttack51 = { 
	attackname = "dwbMeleeAttack51",
	animation = "combo_5a_light",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 1,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(dwbMeleeAttack51)

-----------------------------------------------------------------------

-----------------------------------------------------------------------

dwbMeleeAttack52 = { 
	attackname = "dwbMeleeAttack52",
	animation = "combo_3c_light",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 75,
	actionAttackChance = 0,
	mindAttackChance = 0,

	dotChance = 25,
	tickStrengthOfHit = 2,

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

AddDotPoolAttackTargetSkill(dwbMeleeAttack52)

-----------------------------------------------------------------------
dwbMeleeAttack53 = { 
	attackname = "dwbMeleeAttack53",
	animation = "combo_3c_light",

	requiredWeaponType = NONE,
	
	range = 11,
	damageRatio = 1.2,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 75,
	actionAttackChance = 0,
	mindAttackChance = 0,

	dotChance = 25,
	tickStrengthOfHit = 2,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
	bleedingType = 0,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 1,
	diseaseType = HEALTH,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddDotPoolAttackTargetSkill(dwbMeleeAttack53)

-----------------------------------------------------------------------

dwbMeleeRangedAttack1 = {
	attackname = "dwbMeleeRangedAttack1",
	animation = "creature_attack_ranged_light",
	
	requiredWeaponType = RANGED,

	range = 64,

	damageRatio = 1.2,

	speedRatio = 4,
	coneAngle = 0,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 5,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(dwbMeleeRangedAttack1)
dwbMeleeRangedAttack2 = {
	attackname = "dwbMeleeRangedAttack2",
	animation = "creature_attack_ranged_light",
	
	requiredWeaponType = RANGED,

	range = 64,

	damageRatio = 1.2,

	speedRatio = 4,
	coneAngle = 0,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 5,
	stunChance = 5,
	intimidateChance = 3,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(dwbMeleeRangedAttack2)
dwbMeleeRangedAttack3 = {
	attackname = "dwbMeleeRangedAttack3",
	animation = "creature_attack_ranged_light",
	
	requiredWeaponType = RANGED,

	range = 64,

	damageRatio = 1.2,

	speedRatio = 4,
	coneAngle = 60,

	areaRange = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 5,
	stunChance = 5,
	intimidateChance = 3,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(dwbMeleeRangedAttack3)
dwbMeleeRangedAttack4 = { 
	attackname = "dwbMeleeRangedAttack4",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 64,
	damageRatio = 1.2,
	speedRatio = 7,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 75,
	actionAttackChance = 0,
	mindAttackChance = 0,

	dotChance = 25,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 1,
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

AddDotPoolAttackTargetSkill(dwbMeleeRangedAttack4)
