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

nymAttack1 = {
	attackname = "nymAttack1",
	animation = "combo_2d_medium",
	
	requiredWeaponType = CARBINE,

	range = 25,

	damageRatio = 1.2,

	speedRatio = 1.2,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 2,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 2,
	stunChance = 2,
	intimidateChance = 1,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack1)

-----------------------------------------------------------------------

nymAttack2 = {
	attackname = "nymAttack2",
	animation = "combo_4b_medium",
	
	requiredWeaponType = CARBINE,

	range = 15,

	damageRatio = 1.2,

	speedRatio = 3,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 2,
	blindChance = 2,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack2)

-----------------------------------------------------------------------

nymAttack3 = {
	attackname = "nymAttack3",
	animation = "droid_attack_medium",

	requiredWeaponType = RANGED,
	
	range = 64,
	damageRatio = 1.2,
	speedRatio = 1,
	coneAngle = 0,
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

AddRandomPoolAttackTargetSkill(nymAttack3)
-----------------------------------------------------------------------

nymAttack10 = { 
	attackname = "nymAttack10",
	animation = "fire_area_medium",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	actionAttackChance = 60,
	mindAttackChance = 0,

	dotChance = 50,
	tickStrengthOfHit = 3,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 3,
	bleedingType = ACTION,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "legshot_block",
	CbtSpamCounter = "legshot_counter",
	CbtSpamEvade = "legshot_evade",
	CbtSpamHit = "legshot_hit",
	CbtSpamMiss = "legshot_miss",
}

AddDotPoolAttackTargetSkill(nymAttack10)

-----------------------------------------------------------------------

nymAttack11 = { 
	attackname = "nymAttack11",
	animation = "fire_7_single_medium_face",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.15,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "fullautoattack_block",
	CbtSpamCounter = "fullautoattack_counter",
	CbtSpamEvade = "fullautoattack_evade",
	CbtSpamHit = "fullautoattack_hit",
	CbtSpamMiss = "fullautoattack_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack11)

-----------------------------------------------------------------------

nymAttack12 = { 
	attackname = "nymAttack12",
	animation = "fire_5_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.15,
	areaRange = 0,
	accuracyBonus = 0,
		
	healthAttackChance = 50,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,
	
	actionAttackChance = 50,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 50,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "scattershot_block",
	CbtSpamCounter = "scattershot_counter",
	CbtSpamEvade = "scattershot_evade",
	CbtSpamHit = "scattershot_hit",
	CbtSpamMiss = "scattershot_miss",
}

AddDirectPoolAttackTargetSkill(nymAttack12)

-----------------------------------------------------------------------

nymAttack13 = { 
	attackname = "nymAttack13",
	animation = "fire_7_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.15,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 20,
	intimidateChance = 0,
	
	CbtSpamBlock = "wildshot_block",
	CbtSpamCounter = "wildshot_counter",
	CbtSpamEvade = "wildshot_evade",
	CbtSpamHit = "wildshot_hit",
	CbtSpamMiss = "wildshot_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack13)

-----------------------------------------------------------------------

nymAttack14 = { 
	attackname = "nymAttack14",
	animation = "fire_5_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.15,
	areaRange = 0,
	accuracyBonus = 0,
		
	healthAttackChance = 50,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,
	
	actionAttackChance = 50,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 50,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "scattershot_block",
	CbtSpamCounter = "scattershot_counter",
	CbtSpamEvade = "scattershot_evade",
	CbtSpamHit = "scattershot_hit",
	CbtSpamMiss = "scattershot_miss",
}

AddDirectPoolAttackTargetSkill(nymAttack14)

-----------------------------------------------------------------------

nymAttack15 = { 
	attackname = "nymAttack15",
	animation = "fire_7_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.15,
	coneAngle = 60,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 20,
	intimidateChance = 0,
	
	CbtSpamBlock = "wildshot_block",
	CbtSpamCounter = "wildshot_counter",
	CbtSpamEvade = "wildshot_evade",
	CbtSpamHit = "wildshot_hit",
	CbtSpamMiss = "wildshot_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack15)

-----------------------------------------------------------------------

nymAttack16 = { 
	attackname = "nymAttack16",
	animation = "test_homing",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 60,
	quicknessAttackChance = 0,
	staminaAttakcChance = 0,

	mindAttackChance = 0,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	
	CbtSpamBlock = "legshot_block",
	CbtSpamCounter = "legshot_counter",
	CbtSpamEvade = "legshot_evade",
	CbtSpamHit = "legshot_hit",
	CbtSpamMiss = "legshot_miss",
}

AddDirectPoolAttackTargetSkill(nymAttack16)

-----------------------------------------------------------------------

nymAttack17 = { 
	attackname = "nymAttack17",
	animation = "fire_3_single_medium_face",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.15,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "cripplingshot_block",
	CbtSpamCounter = "cripplingshot_counter",
	CbtSpamEvade = "cripplingshot_evade",
	CbtSpamHit = "cripplingshot_hit",
	CbtSpamMiss = "cripplingshot_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack17)

-----------------------------------------------------------------------

nymAttack18 = { 
	attackname = "nymAttack18",
	animation = "fire_7_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.15,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "burstshot_block",
	CbtSpamCounter = "burstshot_counter",
	CbtSpamEvade = "burstshot_evade",
	CbtSpamHit = "burstshot_hit",
	CbtSpamMiss = "burstshot_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack18)

-----------------------------------------------------------------------

nymAttack19 = { 
	attackname = "nymAttack19",
	animation = "fire_7_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.15,
	coneAngle = 60,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "burstshot_block",
	CbtSpamCounter = "burstshot_counter",
	CbtSpamEvade = "burstshot_evade",
	CbtSpamHit = "burstshot_hit",
	CbtSpamMiss = "burstshot_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack19)

-----------------------------------------------------------------------

nymAttack20 = { 
	attackname = "nymAttack20",
	animation = "fire_area_medium",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.15,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 40,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 20,
	intimidateChance = 0,
	
	CbtSpamBlock = "sup_fire_block",
	CbtSpamCounter = "sup_fire_counter",
	CbtSpamEvade = "sup_fire_evade",
	CbtSpamHit = "sup_fire_hit",
	CbtSpamMiss = "sup_fire_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack20)

-----------------------------------------------------------------------

nymAttack21 = { 
	attackname = "nymAttack21",
	animation = "fire_defender_posture_change_down",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.05,
	coneAngle = 60,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "fullautoattack_block",
	CbtSpamCounter = "fullautoattack_counter",
	CbtSpamEvade = "fullautoattack_evade",
	CbtSpamHit = "fullautoattack_hit",
	CbtSpamMiss = "fullautoattack_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack21)

-----------------------------------------------------------------------

nymAttack22 = { 
	attackname = "nymAttack22",
	animation = "charge",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.05,
	coneAngle = 60,
	accuracyBonus = 0,
		
	knockdownChance = 20,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "chargeshot_block",
	CbtSpamCounter = "chargeshot_counter",
	CbtSpamEvade = "chargeshot_evade",
	CbtSpamHit = "chargeshot_hit",
	CbtSpamMiss = "chargeshot_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack22)

-----------------------------------------------------------------------

nymAttack23 = { 
	attackname = "nymAttack23",
	animation = "fire_defender_posture_change_down",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.05,
	coneAngle = 60,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "fullautoattack_block",
	CbtSpamCounter = "fullautoattack_counter",
	CbtSpamEvade = "fullautoattack_evade",
	CbtSpamHit = "fullautoattack_hit",
	CbtSpamMiss = "fullautoattack_miss",
}

AddRandomPoolAttackTargetSkill(nymAttack23)

-----------------------------------------------------------------------

nymAttack24 = { 
	attackname = "nymAttack24",
	animation = "charge",

	requiredWeaponType = CARBINE,
	
	range = 65,
	damageRatio = 1.2,
	speedRatio = 1.05,
	coneAngle = 60,
	accuracyBonus = 0,
		
	knockdownChance = 40,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "chargeshot_block",
	CbtSpamCounter = "chargeshot_counter",
	CbtSpamEvade = "chargeshot_evade",
	CbtSpamHit = "chargeshot_hit",
	CbtSpamMiss = "chargeshot_miss",
}
AddRandomPoolAttackTargetSkill(nymAttack24)
