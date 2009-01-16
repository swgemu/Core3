--Copyright (C) 2009 <SWGEmu>
 
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

nightsisterAttack1 = {
        attackname = "nightsisterAttack1",
        animation = "creature_attack_light",
        
        requiredWeaponType = MELEE,

        range = 5,
        damageRatio = 1,
        speedRatio = 2,
        areaRange = 5,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack1)

--------------------------------------------------------------------------------------

nightsisterAttack20 = { 
	attackname = "nightsisterAttack20",
	animation = "combo_3a_medium",

	requiredWeaponType = POLEARM,
	
	range = 7,
	damageRatio = 3.3,
	speedRatio = 3,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack20)

-----------------------------------------------------------------------

nightsisterAttack21 = { 
	attackname = "nightsisterAttack21",
	animation = "lower_posture_polearm_2",

	requiredWeaponType = POLEARM,
	
	range = 7,
	damageRatio = 2.45,
	speedRatio = 2.3,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 50,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack21)

-----------------------------------------------------------------------

nightsisterAttack22 = { 
	attackname = "nightsisterAttack22",
	animation = "force_lightning_1_particle_level_5_medium",

	requiredWeaponType = POLEARM,
	
	range = 7,
	damageRatio = 2.8,
	speedRatio = 2.1,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack22)

-----------------------------------------------------------------------

nightsisterAttack23 = { 
	attackname = "nightsisterAttack23",
	--animation = "lower_posture_2hmelee_5",
	animation = "force_weaken_1_arc_particle_level_1_medium",

	requiredWeaponType = POLEARM,
	
	range = 7,
	damageRatio = 2.6,
	speedRatio = 2.25,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 60,
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
	animation = "combo_2c_medium",

	requiredWeaponType = POLEARM,
	
	range = 7,
	damageRatio = 3.2,
	speedRatio = 2.3,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 60,
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
	
	range = 7,
	damageRatio = 2,
	speedRatio = 2,
	areaRange = 7,
	accuracyBonus = 0,
		
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

AddRandomPoolAttackTargetSkill(nightsisterAttack25)

-----------------------------------------------------------------------

nightsisterAttack26 = { 
	attackname = "nightsisterAttack26",
	animation = "combo_2c_medium",

	requiredWeaponType = POLEARM,
	
	range = 7,
	damageRatio = 3.1,
	speedRatio = 2.8,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 20,
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
	
	range = 7,
	damageRatio = 2.36,
	speedRatio = 2.74,
	areaRange = 7,
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
	animation = "combo_3a_medium",

	requiredWeaponType = POLEARM,
	
	range = 7,
	damageRatio = 2.9,
	speedRatio = 2.3,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack28)

-----------------------------------------------------------------------

nightsisterAttack29 = { 
	attackname = "nightsisterAttack29",
	animation = "attack_low_right_medium_0",

	requiredWeaponType = POLEARM,
	
	range = 7,
	damageRatio = 3.4,
	speedRatio = 2.52,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 67,
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
	
	range = 7,
	damageRatio = 3.1,
	speedRatio = 3,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack30)

-----------------------------------------------------------------------

nightsisterAttack31 = { 
	attackname = "nightsisterAttack31",
	animation = "attack_low_right_medium_0",

	requiredWeaponType = POLEARM,
	
	range = 7,
	damageRatio = 1,
	speedRatio = 2,
	areaRange = 7,
	accuracyBonus = 0,

	healthAttackChance = 0,
	actionAttackChance = 90,
	mindAttackChance = 0,
		
	dotChance = 60,
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
	
	range = 5,
	damageRatio = 2.26,
	speedRatio = 2.62,
	areaRange = 5,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 50,
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
	
	range = 5,
	damageRatio = 3.5,
	speedRatio = 2,
	areaRange = 5,
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
	
	range = 5,
	damageRatio = 2.1,
	speedRatio = 2.23,
	areaRange = 5,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 70,
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
	
	range = 5,
	damageRatio = 2,
	speedRatio = 1.7,
	areaRange = 5,
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
	
	range = 5,
	damageRatio = 1,
	speedRatio = 2.7,
	areaRange = 5,
	accuracyBonus = 0,

	healthAttackChance = 90,
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
	animation = "lower_posture_1hmelee_1",

	requiredWeaponType = ONEHANDED,
	
	range = 5,
	damageRatio = 2.6,
	speedRatio = 3,
	areaRange = 5,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 85,
	postureUpChance = 0,
	dizzyChance = 50,
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
	
	range = 5,
	damageRatio = 3.42,
	speedRatio = 2,
	areaRange = 5,
	accuracyBonus = 0,
		
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

AddRandomPoolAttackTargetSkill(nightsisterAttack46)

-----------------------------------------------------------------------

nightsisterAttack47 = { 
	attackname = "nightsisterAttack47",
	animation = "combo_4b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 5,
	damageRatio = 2.87,
	speedRatio = 2,
	areaRange = 5,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 50,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack47)

-----------------------------------------------------------------------

nightsisterAttack48 = { 
	attackname = "nightsisterAttack48",
	animation = "combo_3a_light",

	requiredWeaponType = ONEHANDED,
	
	range = 5,
	damageRatio = 2,
	speedRatio = 3.25,
	areaRange = 5,
	accuracyBonus = 0,

	healthAttackChance = 25,
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
	animation = "force_lightning_1_particle_level_5_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 5,
	damageRatio = 3.3,
	speedRatio = 1.7,
	areaRange = 5,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 25,
	blindChance = 0,
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
	
	range = 5,
	damageRatio = 3.7,
	speedRatio = 2.15,
	areaRange = 5,
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

AddRandomPoolAttackTargetSkill(nightsisterAttack50)

-----------------------------------------------------------------------

nightsisterAttack51 = { 
	attackname = "nightsisterAttack51",
	animation = "combo_5a_light",

	requiredWeaponType = ONEHANDED,
	
	range = 5,
	damageRatio = 2.54,
	speedRatio = 2,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 25,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack51)
