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
hanAttack1 = {
	attackname = "hanAttack1",
	animation = "fire_1_special_single_light",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 70,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 100,
	actionAttackChance = 0,
	mindAttackChance = 0,

	dotChance = 60,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
	bleedingType = HEALTH,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "sapblast_block",
	CbtSpamCounter = "sapblast_counter",
	CbtSpamEvade = "sapblast_evade",
	CbtSpamHit = "sapblast_hit",
	CbtSpamMiss = "sapblast_miss",
}

AddRandomPoolAttackTargetSkill(hanAttack1)

-----------------------------------------------
hanAttack2 = {
	attackname = "hanAttack2",
	animation = "fire_5_single_light",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 70,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "pointblankblast_block",
	CbtSpamCounter = "pointblankblast_counter",
	CbtSpamEvade = "pointblankblast_evade",
	CbtSpamHit = "pointblankblast_hit",
	CbtSpamMiss = "pointblankblast_miss",
}

AddRandomPoolAttackTargetSkill(hanAttack2)


-----------------------------------------------------------------------

hanAttack3 = {
	attackname = "hanAttack3",
	animation = "fire_1_special_single_light",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 70,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 100,
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
	
	CbtSpamBlock = "bodyshot_block",
	CbtSpamCounter = "bodyshot_counter",
	CbtSpamEvade = "bodyshot_evade",
	CbtSpamHit = "bodyshot_hit",
	CbtSpamMiss = "bodyshot_miss",
}

AddRandomPoolAttackTargetSkill(hanAttack3)

-----------------------------------------------------------------------

hanAttack4 = {
	attackname = "hanAttack4",
	animation = "fire_area_no_trails_light",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 70,
	speedRatio = 1,
	coneAngle = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "areashot_block",
	CbtSpamCounter = "areashot_counter",
	CbtSpamEvade = "areashot_evade",
	CbtSpamHit = "areashot_hit",
	CbtSpamMiss = "areashot_miss",
}

AddRandomPoolAttackTargetSkill(hanAttack4)

-----------------------------------------------------------------------

hanAttack5 = {
	attackname = "hanAttack5",
	animation = "fire_3_single_light_face",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 70,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "disarmshot_block",
	CbtSpamCounter = "disarmshot_counter",
	CbtSpamEvade = "disarmshot_evade",
	CbtSpamHit = "disarmshot_hit",
	CbtSpamMiss = "disarmshot_miss",
}

AddRandomPoolAttackTargetSkill(hanAttack5)

-----------------------------------------------------------------------

hanAttack6 = {
	attackname = "hanAttack6",
	animation = "fire_7_single_light_face",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 70,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,
	
	healthAttackChance = 75,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,
	
	actionAttackChance = 75,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 10,
	focusAttackChance = 0,
	willpowerAttackChance = 0,	
	
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "doubletap_block",
	CbtSpamCounter = "doubletap_counter",
	CbtSpamEvade = "doubletap_evade",
	CbtSpamHit = "doubletap_hit",
	CbtSpamMiss = "doubletap_miss",
}

AddRandomPoolAttackTargetSkill(hanAttack6)

-----------------------------------------------------------------------

hanAttack7 = {
	attackname = "hanAttack7",
	animation = "fire_1_special_single_light",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 70,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "stoppingshot_block",
	CbtSpamCounter = "stoppingshot_counter",
	CbtSpamEvade = "stoppingshot_evade",
	CbtSpamHit = "stoppingshot_hit",
	CbtSpamMiss = "stoppingshot_miss",
}

AddRandomPoolAttackTargetSkill(hanAttack7)

-----------------------------------------------------------------------

hanAttack8 = {
	attackname = "hanAttack8",
	animation = "fire_area_light",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 70,
	speedRatio = 1,
	areaRange = 0,
	coneAngle = 60,	
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 20,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "fanshot_block",
	CbtSpamCounter = "fanshot_counter",
	CbtSpamEvade = "fanshot_evade",
	CbtSpamHit = "fanshot_hit",
	CbtSpamMiss = "fanshot_miss",
}

AddRandomPoolAttackTargetSkill(hanAttack8)

-----------------------------------------------------------------------

hanAttack9 = {
	attackname = "hanAttack9",
	animation = "ranged_melee_light",

	requiredWeaponType = PISTOL,
	
	range = 5,
	damageRatio = 70,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 10,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "pistolwhip_block",
	CbtSpamCounter = "pistolwhip_counter",
	CbtSpamEvade = "pistolwhip_evade",
	CbtSpamHit = "pistolwhip_hit",
	CbtSpamMiss = "pistolwhip_miss",

}

AddRandomPoolAttackTargetSkill(hanAttack9)

-----------------------------------------------------------------------

hanAttack10 = {
	attackname = "hanAttack10",
	animation = "ranged_melee_light",

	requiredWeaponType = PISTOL,
	
	range = 5,
	damageRatio = 70,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 30,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "pistolsmash_block",
	CbtSpamCounter = "pistolsmash_counter",
	CbtSpamEvade = "pistolsmash_evade",
	CbtSpamHit = "pistolsmash_hit",
	CbtSpamMiss = "pistolsmash_miss",

}

AddRandomPoolAttackTargetSkill(hanAttack10)

-----------------------------------------------------------------------

hanAttack11 = {
	attackname = "hanAttack11",
	animation = "fire_5_special_single_light",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 70,
	speedRatio = 1,
	coneAngle = 30,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "pistolmultishot_block",
	CbtSpamCounter = "pistolmultishot_counter",
	CbtSpamEvade = "pistolmultishot_evade",
	CbtSpamHit = "pistolmultishot_hit",
	CbtSpamMiss = "pistolmultishot_miss",
}

AddRandomPoolAttackTargetSkill(hanAttack11)

-----------------------------------------------------------------------

hanAttack12= {
	attackname = "hanAttack12",
	animation = "fire_3_single_light_face",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 70,
	speedRatio = 2.5,
	areaRange = 0,
	accuracyBonus = 0,
	
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "disarmblast_block",
	CbtSpamCounter = "disarmblast_counter",
	CbtSpamEvade = "disarmblast_evade",
	CbtSpamHit = "disarmblast_hit",
	CbtSpamMiss = "disarmblast_miss",
}

AddRandomPoolAttackTargetSkill(hanAttack12)

