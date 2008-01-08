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


nightsisterAttack20 = { 
	attackname = "nightsisterAttack20",
	animation = "lower_posture_2hmelee_2",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 1.50,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	actionAttackChance = 50,
	mindAttackChance = 0,
	
	dotChance = 15,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
	bleedingType = ACTION,

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

AddDotPoolAttackTargetSkill(nightsisterAttack20)

-----------------------------------------------------------------------

nightsisterAttack21 = { 
	attackname = "nightsisterAttack21",
	--animation = "combo_5a_medium",
	animation = "force_choke_1_arc_particle_level_1_light",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 2.85,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 1,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 1,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack21)

-----------------------------------------------------------------------

nightsisterAttack22 = { 
	attackname = "nightsisterAttack22",
	--animation = "combo_3a_medium",
	animation = "force_lightning_1_particle_level_5_medium",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 2.15,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 1,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack22)

-----------------------------------------------------------------------

nightsisterAttack23 = { 
	attackname = "nightsisterAttack23",
	--animation = "lower_posture_2hmelee_5",
	animation = "force_weaken_1_arc_particle_level_1_medium",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 2.0,
	speedRatio = 1.45,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 1,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack23)

-----------------------------------------------------------------------

nightsisterAttack24 = { 
	attackname = "nightsisterAttack24",
	--animation = "combo_2c_medium",
	animation = "force_drain_1",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 2.25,
	speedRatio = 1.45,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack24)

-----------------------------------------------------------------------

nightsisterAttack25 = { 
	attackname = "nightsisterAttack25",
	animation = "combo_3c_light",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 2.15,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 50,
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

AddDirectPoolAttackTargetSkill(nightsisterAttack25)

-----------------------------------------------------------------------

nightsisterAttack26 = { 
	attackname = "nightsisterAttack26",
	animation = "combo_2c_medium",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 2.5,
	speedRatio = 1.45,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack26)

-----------------------------------------------------------------------

nightsisterAttack27 = { 
	attackname = "nightsisterAttack27",
	animation = "combo_3b_medium",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 2.15,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 50,
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

AddDirectPoolAttackTargetSkill(nightsisterAttack27)

-----------------------------------------------------------------------

nightsisterAttack28 = { 
	attackname = "nightsisterAttack28",
	animation = "lower_posture_2hmelee_6",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 3.0,
	speedRatio = 2.45,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 1,
	blindChance = 0,
	stunChance = 1,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack28)

-----------------------------------------------------------------------

nightsisterAttack29 = { 
	attackname = "nightsisterAttack29",
	animation = "attack_low_right_medium_0",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 2.0,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 1,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack29)

-----------------------------------------------------------------------

nightsisterAttack30 = { 
	attackname = "nightsisterAttack30",
	animation = "combo_3d_medium",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 2.2,
	speedRatio = 1.45,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 1,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack30)

-----------------------------------------------------------------------

nightsisterAttack31 = { 
	attackname = "nightsisterAttack31",
	animation = "attack_low_right_medium_0",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 2.15,
	speedRatio = 1.05,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	actionAttackChance = 50,
	mindAttackChance = 0,
		
	dotChance = 5,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
	bleedingType = ACTION,

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

AddDotPoolAttackTargetSkill(nightsisterAttack31)

-----------------------------------------------------------------------
nightsisterAttack40 = { 
	attackname = "nightsisterAttack40",
	animation = "combo_4a_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.5,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack40)

-----------------------------------------------------------------------

nightsisterAttack41 = { 
	attackname = "nightsisterAttack41",
	animation = "combo_3b_light",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.5,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack41)

-----------------------------------------------------------------------

nightsisterAttack42 = { 
	attackname = "nightsisterAttack42",
	animation = "combo_2d_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.0,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack42)

-----------------------------------------------------------------------

nightsisterAttack43 = { 
	attackname = "nightsisterAttack43",
	animation = "combo_5b_light",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.2,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack43)

-----------------------------------------------------------------------


nightsisterAttack44 = { 
	attackname = "nightsisterAttack44",
	animation = "counter_low_left_light",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.15,
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

	bleedingStrength = 0,
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

AddDotPoolAttackTargetSkill(nightsisterAttack44)

-----------------------------------------------------------------------

nightsisterAttack45 = { 
	attackname = "nightsisterAttack45",
	animation = "lower_posture_2hmelee_6",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.15,
	speedRatio = 1.45,
	areaRange = 7,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack45)

-----------------------------------------------------------------------


nightsisterAttack46 = { 
	attackname = "nightsisterAttack46",
	animation = "combo_3c_light",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.15,
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

	bleedingStrength = 0,
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

AddDotPoolAttackTargetSkill(nightsisterAttack46)

-----------------------------------------------------------------------

nightsisterAttack47 = { 
	attackname = "nightsisterAttack47",
	animation = "combo_4b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.15,
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

AddDirectPoolAttackTargetSkill(nightsisterAttack47)

-----------------------------------------------------------------------

nightsisterAttack48 = { 
	attackname = "nightsisterAttack48",
	animation = "combo_3a_light",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.15,
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

AddDirectPoolAttackTargetSkill(nightsisterAttack48)

-----------------------------------------------------------------------

nightsisterAttack49 = { 
	attackname = "nightsisterAttack49",
	animation = "combo_4b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.15,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack49)

-----------------------------------------------------------------------

nightsisterAttack50 = { 
	attackname = "nightsisterAttack50",
	animation = "combo_2b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.55,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack50)

-----------------------------------------------------------------------

nightsisterAttack51 = { 
	attackname = "nightsisterAttack51",
	animation = "combo_5a_light",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 4.5,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack51)
