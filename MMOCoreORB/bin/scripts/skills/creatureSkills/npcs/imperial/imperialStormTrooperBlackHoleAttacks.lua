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

imperialStormTrooperBlackHoleAttack1 = {
	attackname = "imperialStormTrooperBlackHoleAttack1",	
	animation = "fire_area_medium",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1.5,
	speedRatio = 1,
	areaRange = 0,
	coneAngle = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	actionAttackChance = 100,
	mindAttackChance = 0,
	
	knockdownChance = 0,
	postureDownChance = 25,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

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
	
	CbtSpamBlock = "legshot_block",
	CbtSpamCounter = "legshot_counter",
	CbtSpamEvade = "legshot_evade",
	CbtSpamHit = "legshot_hit",
	CbtSpamMiss = "legshot_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack1)

-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack2 = {
	attackname = "imperialStormTrooperBlackHoleAttack2",
	animation = "fire_7_single_medium_face",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1.7,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 25,
	blindChance = 25,
	stunChance = 15,
	intimidateChance = 0,
	
	CbtSpamBlock = "s_auto_block",
	CbtSpamCounter = "s_auto_counter",
	CbtSpamEvade = "s_auto_evade",
	CbtSpamHit = "s_auto_hit",
	CbtSpamMiss = "s_auto_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack2)

-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack3 = {
	attackname = "imperialStormTrooperBlackHoleAttack3",
	animation = "fire_5_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1.1,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,
		
	healthAttackChance = 80,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,
	
	actionAttackChance = 90,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 12,
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

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack3)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack4 = {
	attackname = "imperialStormTrooperBlackHoleAttack4",
	animation = "fire_7_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 2.1,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 25,
	intimidateChance = 0,
	
	CbtSpamBlock = "wildshot_block",
	CbtSpamCounter = "wildshot_counter",
	CbtSpamEvade = "wildshot_evade",
	CbtSpamHit = "wildshot_hit",
	CbtSpamMiss = "wildshot_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack4)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack5 = {
	attackname = "imperialStormTrooperBlackHoleAttack5",
	animation = "fire_5_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1.6,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,
		
	healthAttackChance = 85,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,
	
	actionAttackChance = 95,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 20,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "scatterblast_block",
	CbtSpamCounter = "scatterblast_counter",
	CbtSpamEvade = "scatterblast_evade",
	CbtSpamHit = "scatterblast_hit",
	CbtSpamMiss = "scatterblast_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack5)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack6 = {
	attackname = "imperialStormTrooperBlackHoleAttack6",
	animation = "fire_7_single_medium",

	requiredWeaponType = CARBINE,
	
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
	stunChance = 50,
	intimidateChance = 0,
	
	CbtSpamBlock = "widewildshot_block",
	CbtSpamCounter = "widewildshot_counter",
	CbtSpamEvade = "widewildshot_evade",
	CbtSpamHit = "widewildshot_hit",
	CbtSpamMiss = "widewildshot_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack6)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack7 = {
	attackname = "imperialStormTrooperBlackHoleAttack7",
	animation = "test_homing",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1.9,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 100,
	quicknessAttackChance = 0,
	staminaAttakcChance = 0,

	mindAttackChance = 0,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 25,
	
	CbtSpamBlock = "kneecapshot_block",
	CbtSpamCounter = "kneecapshot_counter",
	CbtSpamEvade = "kneecapshot_evade",
	CbtSpamHit = "kneecapshot_hit",
	CbtSpamMiss = "kneecapshot_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack7)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack8 = {
	attackname = "imperialStormTrooperBlackHoleAttack8",
	animation = "fire_5_single_light_face",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1.6,
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
	
	CbtSpamBlock = "cripplingshot_block",
	CbtSpamCounter = "cripplingshot_counter",
	CbtSpamEvade = "cripplingshot_evade",
	CbtSpamHit = "cripplingshot_hit",
	CbtSpamMiss = "cripplingshot_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack8)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack9 = {
	attackname = "imperialStormTrooperBlackHoleAttack9",
	animation = "fire_7_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 2.0,
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
	
	CbtSpamBlock = "burstshot_block",
	CbtSpamCounter = "burstshot_counter",
	CbtSpamEvade = "burstshot_evade",
	CbtSpamHit = "burstshot_hit",
	CbtSpamMiss = "burstshot_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack9)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack10 = {
	attackname = "imperialStormTrooperBlackHoleAttack10",
	animation = "fire_7_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1.1,
	speedRatio = 1,
	coneAngle = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "burstblast_block",
	CbtSpamCounter = "burstblast_counter",
	CbtSpamEvade = "burstblast_evade",
	CbtSpamHit = "burstblast_hit",
	CbtSpamMiss = "burstblast_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack10)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack11 = {
	attackname = "imperialStormTrooperBlackHoleAttack11",
	animation = "fire_area_medium",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1.3,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 50,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "sup_fire_block",
	CbtSpamCounter = "sup_fire_counter",
	CbtSpamEvade = "sup_fire_evade",
	CbtSpamHit = "sup_fire_hit",
	CbtSpamMiss = "sup_fire_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack11)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack12 = {
	attackname = "imperialStormTrooperBlackHoleAttack12",
	animation = "fire_defender_posture_change_down",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1.4,
	speedRatio = 1,
	coneAngle = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 13,
	blindChance = 13,
	stunChance = 13,
	intimidateChance = 0,
	
	CbtSpamBlock = "a_auto_block",
	CbtSpamCounter = "a_auto_counter",
	CbtSpamEvade = "a_auto_evade",
	CbtSpamHit = "a_auto_hit",
	CbtSpamMiss = "a_auto_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack12)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack13 = {
	attackname = "imperialStormTrooperBlackHoleAttack13",
	animation = "charge",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1,
	speedRatio = 1,
	coneAngle = 0,
	accuracyBonus = 0,
		
	knockdownChance = 10,
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

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack13)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack14 = {
	attackname = "imperialStormTrooperBlackHoleAttack14",
	animation = "fire_defender_posture_change_down",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1.3,
	speedRatio = 1,
	coneAngle = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 20,
	blindChance = 20,
	stunChance = 20,
	intimidateChance = 0,
	
	CbtSpamBlock = "a_auto_block",
	CbtSpamCounter = "a_auto_counter",
	CbtSpamEvade = "a_auto_evade",
	CbtSpamHit = "a_auto_hit",
	CbtSpamMiss = "a_auto_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack14)
-----------------------------------------------------------------------

imperialStormTrooperBlackHoleAttack15 = {
	attackname = "imperialStormTrooperBlackHoleAttack15",
	animation = "charge",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 1.2,
	speedRatio = 1,
	coneAngle = 0,
	accuracyBonus = 0,
		
	knockdownChance = 40,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "chargeblast_block",
	CbtSpamCounter = "chargeblast_counter",
	CbtSpamEvade = "chargeblast_evade",
	CbtSpamHit = "chargeblast_hit",
	CbtSpamMiss = "chargeblast_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperBlackHoleAttack15)
-----------------------------------------------------------------------
