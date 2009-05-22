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
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02300-1301 USA
 
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


dwbSBDAttack40 = { 
	attackname = "dwbSBDAttack40",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.25,
	coneAngle = 7,
	areaRange = 0,
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(dwbSBDAttack40)

-----------------------------------------------------------------------

dwbSBDAttack41 = { 
	attackname = "dwbSBDAttack41",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.25,
	coneAngle = 7,
	areaRange = 0,
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(dwbSBDAttack41)

-----------------------------------------------------------------------

dwbSBDAttack42 = { 
	attackname = "dwbSBDAttack42",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.8,
	coneAngle = 7,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 1,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(dwbSBDAttack42)

-----------------------------------------------------------------------

dwbSBDAttack43 = { 
	attackname = "dwbSBDAttack43",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.25,
	coneAngle = 7,
	areaRange = 0,
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(dwbSBDAttack43)

-----------------------------------------------------------------------


dwbSBDAttack44 = { 
	attackname = "dwbSBDAttack44",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.45,
	coneAngle = 7,
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
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDotPoolAttackTargetSkill(dwbSBDAttack44)

-----------------------------------------------------------------------

dwbSBDAttack45 = { 
	attackname = "dwbSBDAttack45",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.45,
	coneAngle = 7,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 1,
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(dwbSBDAttack45)

-----------------------------------------------------------------------


dwbSBDAttack46 = { 
	attackname = "dwbSBDAttack46",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.45,
	coneAngle = 7,
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
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDotPoolAttackTargetSkill(dwbSBDAttack46)

-----------------------------------------------------------------------

dwbSBDAttack47 = { 
	attackname = "dwbSBDAttack47",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.45,
	coneAngle = 7,
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
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDirectPoolAttackTargetSkill(dwbSBDAttack47)

-----------------------------------------------------------------------

dwbSBDAttack48 = { 
	attackname = "dwbSBDAttack48",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.45,
	coneAngle = 7,
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
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDirectPoolAttackTargetSkill(dwbSBDAttack48)

-----------------------------------------------------------------------

dwbSBDAttack49 = { 
	attackname = "dwbSBDAttack49",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.45,
	coneAngle = 7,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 1,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(dwbSBDAttack49)

-----------------------------------------------------------------------

dwbSBDAttack50 = { 
	attackname = "dwbSBDAttack50",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.45,
	coneAngle = 7,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 1,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(dwbSBDAttack50)

-----------------------------------------------------------------------

dwbSBDAttack51 = { 
	attackname = "dwbSBDAttack51",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.25,
	coneAngle = 7,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 1,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(dwbSBDAttack51)

-----------------------------------------------------------------------

-----------------------------------------------------------------------

dwbSBDAttack52 = { 
	attackname = "dwbSBDAttack52",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.45,
	coneAngle = 7,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 75,
	actionAttackChance = 0,
	mindAttackChance = 0,

	dotChance = 25,
	tickStrengthOfHit = 2,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 1,
	bleedingType = HEALTH,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDotPoolAttackTargetSkill(dwbSBDAttack52)

-----------------------------------------------------------------------
dwbSBDAttack53 = { 
	attackname = "dwbSBDAttack53",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 30,
	damageRatio = 1.2,
	speedRatio = 1.45,
	coneAngle = 7,
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
	bleedingType = 0,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 1,
	diseaseType = HEALTH,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDotPoolAttackTargetSkill(dwbSBDAttack53)

-----------------------------------------------------------------------

dwbSBDRangedAttack1 = {
	attackname = "dwbSBDRangedAttack1",
	animation = "creature_attack_ranged_light",
	
	requiredWeaponType = RANGED,

	range = 64,

	damageRatio = 1.2,

	speedRatio = 4,
	coneAngle = 7,

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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(dwbSBDRangedAttack1)
dwbSBDRangedAttack2 = {
	attackname = "dwbSBDRangedAttack2",
	animation = "creature_attack_ranged_light",
	
	requiredWeaponType = RANGED,

	range = 64,

	damageRatio = 1.2,

	speedRatio = 4,
	coneAngle = 7,

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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(dwbSBDRangedAttack2)
dwbSBDRangedAttack3 = {
	attackname = "dwbSBDRangedAttack3",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(dwbSBDRangedAttack3)
dwbSBDRangedAttack4 = { 
	attackname = "dwbSBDRangedAttack4",
	animation = "creature_attack_ranged_light",

	requiredWeaponType = RANGED,
	
	range = 64,
	damageRatio = 1.2,
	speedRatio = 7,
	coneAngle = 7,
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
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDotPoolAttackTargetSkill(dwbSBDRangedAttack4)
