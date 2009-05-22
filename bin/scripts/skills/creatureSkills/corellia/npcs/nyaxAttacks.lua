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
nyaxAttack1 = {
	attackname = "nyaxAttack1",
	animation = "combo_2d_medium",
	
	requiredWeaponType = CARBINE,

	range = 25,

	damageRatio = 1.2,

	speedRatio = 2,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 2,
	postureUpChance = 0,
	dizzyChance = 2,
	blindChance = 2,
	stunChance = 2,
	intimidateChance = 2,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack1)
nyaxAttack2 = {
	attackname = "nyaxAttack2",
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
	stunChance = 2,
	intimidateChance = 2,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack2)

nyaxAttack10 = { 
	attackname = "nyaxAttack10",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDotPoolAttackTargetSkill(nyaxAttack10)

-----------------------------------------------------------------------

nyaxAttack11 = { 
	attackname = "nyaxAttack11",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack11)

-----------------------------------------------------------------------


nyaxAttack12 = { 
	attackname = "nyaxAttack12",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDirectPoolAttackTargetSkill(nyaxAttack12)

-----------------------------------------------------------------------

nyaxAttack13 = { 
	attackname = "nyaxAttack13",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack13)

-----------------------------------------------------------------------

nyaxAttack14 = { 
	attackname = "nyaxAttack14",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDirectPoolAttackTargetSkill(nyaxAttack14)

-----------------------------------------------------------------------

nyaxAttack15 = { 
	attackname = "nyaxAttack15",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack15)

-----------------------------------------------------------------------

nyaxAttack16 = { 
	attackname = "nyaxAttack16",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDirectPoolAttackTargetSkill(nyaxAttack16)

-----------------------------------------------------------------------

nyaxAttack17 = { 
	attackname = "nyaxAttack17",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack17)

-----------------------------------------------------------------------

nyaxAttack18 = { 
	attackname = "nyaxAttack18",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack18)

-----------------------------------------------------------------------

nyaxAttack19 = { 
	attackname = "nyaxAttack19",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack19)

-----------------------------------------------------------------------

nyaxAttack20 = { 
	attackname = "nyaxAttack20",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack20)

-----------------------------------------------------------------------

nyaxAttack21 = { 
	attackname = "nyaxAttack21",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack21)

-----------------------------------------------------------------------

nyaxAttack22 = { 
	attackname = "nyaxAttack22",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack22)

-----------------------------------------------------------------------

nyaxAttack23 = { 
	attackname = "nyaxAttack23",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack23)

-----------------------------------------------------------------------

nyaxAttack24 = { 
	attackname = "nyaxAttack24",
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

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(nyaxAttack24)
