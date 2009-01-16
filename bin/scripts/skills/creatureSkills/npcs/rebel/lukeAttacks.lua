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

lukeAttack1 = {
	attackname = "lukeAttack1",
	animation = "saberthrow_posture_change",
	
	requiredWeaponType = JEDI,
	
	range = 32, --30,
	damageRatio = 1.2,
	speedRatio = 1,
	coneAngle = 40,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	--TODO: Find what the bleed attr and value is
	
	CbtSpamBlock = "saberthrow1_block",
	CbtSpamCounter = "saberthrow1_counter",
	CbtSpamEvade = "saberthrow1_evade",
	CbtSpamHit = "saberthrow1_hit",
	CbtSpamMiss = "saberthrow1_miss"
}

AddRandomPoolAttackTargetSkill(lukeAttack1)

-----------------------------------------------------------------------

lukeAttack2 = {
	attackname = "lukeAttack2",
	animation = "saberthrow_posture_change",
	
	requiredWeaponType = JEDI,
	
	range = 32, --30,
	damageRatio = 1.2,
	speedRatio = 1,
	coneAngle = 40,
	accuracyBonus = 300,
	
	knockdownChance = 35,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	CbtSpamBlock = "saberthrow2_block",
	CbtSpamCounter = "saberthrow2_counter",
	CbtSpamEvade = "saberthrow2_evade",
	CbtSpamHit = "saberthrow2_hit",
	CbtSpamMiss = "saberthrow2_miss"
}

AddRandomPoolAttackTargetSkill(lukeAttack2)

-----------------------------------------------------------------------

lukeAttack3 = {
	attackname = "lukeAttack3",
	animation = "saberthrow_posture_change",

	requiredWeaponType = JEDI,

	range = 32, --30,
	damageRatio = 1.2,
	speedRatio = 1,
	coneAngle = 40,
	accuracyBonus = 300,
	
	knockdownChance = 40,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	--TODO: Find what the bleed attr and value is
	
	CbtSpamBlock = "saberthrow3_block",
	CbtSpamCounter = "saberthrow3_counter",
	CbtSpamEvade = "saberthrow3_evade",
	CbtSpamHit = "saberthrow3_hit",
	CbtSpamMiss = "saberthrow3_miss"
}

AddRandomPoolAttackTargetSkill(lukeAttack3)

-----------------------------------------------------------------------

lukeAttack4 = {
	attackname = "lukeAttack4",
	animation = "combo_2d_light",

	requiredWeaponType = JEDI,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 300,
	postureDownChance = 10,
		
	healthAttackChance = 50,
	actionAttackChance = 35,
	mindAttackChance = 15,

	dotChance = 25,
	tickStrengthOfHit = 3, --1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0, --10, ?
	bleedingType = HEALTH,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "saberslash1_block",
	CbtSpamCounter = "saberslash1_counter",
	CbtSpamEvade = "saberslash1_evade",
	CbtSpamHit = "saberslash1_hit",
	CbtSpamMiss = "saberslash1_miss"
}

AddRandomPoolAttackTargetSkill(lukeAttack4)

-----------------------------------------------------------------------

lukeAttack5 = {
	attackname = "lukeAttack5",
	animation = "combo_2d_light",

	requiredWeaponType = JEDI,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 300,
	postureDownChance = 20,
		
	healthAttackChance = 50,
	actionAttackChance = 35,
	mindAttackChance = 15,

	dotChance = 50,
	tickStrengthOfHit = 3, --1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0, --10, ?
	bleedingType = HEALTH,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "saberslash2_block",
	CbtSpamCounter = "saberslash2_counter",
	CbtSpamEvade = "saberslash2_evade",
	CbtSpamHit = "saberslash2_hit",
	CbtSpamMiss = "saberslash2_miss"
}

AddRandomPoolAttackTargetSkill(lukeAttack5)

-----------------------------------------------------------------------

lukeAttack6 = {
	attackname = "lukeAttack6",
	animation = "showoff_2_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 8,
	coneAngel = 40,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 30,
	blindChance = 25,
	stunChance = 20,
	intimidateChance = 0,
	
	CbtSpamBlock = "saber1hflurry_block",
	CbtSpamCounter = "saber1hflurry_counter",
	CbtSpamEvade = "saber1hflurry_evade",
	CbtSpamHit = "saber1hflurry_hit",
	CbtSpamMiss = "saber1hflurry_miss"
}
	
AddRandomPoolAttackTargetSkill(lukeAttack6)

-----------------------------------------------------------------------

lukeAttack7 = {
	attackname = "lukeAttack7",
	animation = "combo_jedi_4_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 8,
	coneAngel = 40,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 50,
	blindChance = 45,
	stunChance = 40,
	intimidateChance = 0,
	
	CbtSpamBlock = "saber1hflurry2_block",
	CbtSpamCounter = "saber1hflurry2_counter",
	CbtSpamEvade = "saber1hflurry2_evade",
	CbtSpamHit = "saber1hflurry2_hit",
	CbtSpamMiss = "saber1hflurry2_miss"
}
	
AddRandomPoolAttackTargetSkill(lukeAttack7)

-----------------------------------------------------------------------

lukeAttack8 = {
	attackname = "lukeAttack8",
	animation = "combo_jedi_2_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 8,
	coneAngel = 40,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 50,
	blindChance = 45,
	stunChance = 40,
	intimidateChance = 0,
	
	CbtSpamBlock = "saber2hphantom_block",
	CbtSpamCounter = "saber2hphantom_counter",
	CbtSpamEvade = "saber2hphantom_evade",
	CbtSpamHit = "saber2hphantom_hit",
	CbtSpamMiss = "saber2hphantom_miss"
	
}

AddRandomPoolAttackTargetSkill(lukeAttack8)

lukeAttack9 = {
	attackname = "lukeAttack9",
	animation = "combo_2b_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	
	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,
	
	mindAttackChance = 25,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "saber1hheadhit1_block",
	CbtSpamCounter = "saber1hheadhit1_counter",
	CbtSpamEvade = "saber1hheadhit1_evade",
	CbtSpamHit = "saber1hheadhit1_hit",
	CbtSpamMiss = "saber1hheadhit1_miss"
	
}

AddRandomPoolAttackTargetSkill(lukeAttack9)

-----------------------------------------------------------------------

lukeAttack10 = {
	attackname = "lukeAttack10",
	animation = "combo_3a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	
	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,
	
	mindAttackChance = 50,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0, --20, --why is 20 here -.-
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "saber1hheadhit2_block",
	CbtSpamCounter = "saber1hheadhit2_counter",
	CbtSpamEvade = "saber1hheadhit2_evade",
	CbtSpamHit = "saber1hheadhit2_hit",
	CbtSpamMiss = "saber1hheadhit2_miss"
	
}

AddRandomPoolAttackTargetSkill(lukeAttack10)

-----------------------------------------------------------------------

lukeAttack11 = {
	attackname = "lukeAttack11",
	animation = "combo_5a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	
	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,
	
	mindAttackChance = 75,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0, --40, who put 40 here -.-
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "saber1hheadhit3_block",
	CbtSpamCounter = "saber1hheadhit3_counter",
	CbtSpamEvade = "saber1hheadhit3_evade",
	CbtSpamHit = "saber1hheadhit3_hit",
	CbtSpamMiss = "saber1hheadhit3_miss"
	
}

AddRandomPoolAttackTargetSkill(lukeAttack11)

-----------------------------------------------------------------------

lukeAttack12 = {
	attackname = "lukeAttack12",
	animation = "combo_2a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 15,
	
	CbtSpamBlock = "saber1hcombohit1_block",
	CbtSpamCounter = "saber1hcombohit1_counter",
	CbtSpamEvade = "saber1hcombohit1_evade",
	CbtSpamHit = "saber1hcombohit1_hit",
	CbtSpamMiss = "saber1hcombohit1_miss"
	
}

AddRandomPoolAttackTargetSkill(lukeAttack12)

-----------------------------------------------------------------------

lukeAttack13 = {
	attackname = "lukeAttack13",
	animation = "combo_3c_lightt",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 25,
	
	CbtSpamBlock = "saber1hcombohit2_block",
	CbtSpamCounter = "saber1hcombohit2_counter",
	CbtSpamEvade = "saber1hcombohit2_evade",
	CbtSpamHit = "saber1hcombohit2_hit",
	CbtSpamMiss = "saber1hcombohit2_miss"
	
}

AddRandomPoolAttackTargetSkill(lukeAttack13)

-----------------------------------------------------------------------

lukeAttack14 = {
	attackname = "lukeAttack14",
	animation = "combo_4a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 40,
	
	CbtSpamBlock = "saber1hcombohit3_block",
	CbtSpamCounter = "saber1hcombohit3_counter",
	CbtSpamEvade = "saber1hcombohit3_evade",
	CbtSpamHit = "saber1hcombohit3_hit",
	CbtSpamMiss = "saber1hcombohit3_miss"
	
}

AddRandomPoolAttackTargetSkill(lukeAttack14)

-----------------------------------------------------------------------

lukeAttack15 = {
	attackname = "lukeAttack15",
	animation = "combo_3a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "saber1hhit1_block",
	CbtSpamCounter = "saber1hhit1_counter",
	CbtSpamEvade = "saber1hhit1_evade",
	CbtSpamHit = "saber1hhit1_hit",
	CbtSpamMiss = "saber1hhit1_miss"
	
}

AddRandomPoolAttackTargetSkill(lukeAttack15)

-----------------------------------------------------------------------

lukeAttack16 = {
	attackname = "lukeAttack16",
	animation = "combo_3a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	blindChance = 30,
	
	CbtSpamBlock = "saber1hhit2_block",
	CbtSpamCounter = "saber1hhit2_counter",
	CbtSpamEvade = "saber1hhit2_evade",
	CbtSpamHit = "saber1hhit2_hit",
	CbtSpamMiss = "saber1hhit2_miss"
	
}

AddRandomPoolAttackTargetSkill(lukeAttack16)

-----------------------------------------------------------------------

lukeAttack17 = {
	attackname = "lukeAttack17",
	animation = "combo_3a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	blindChance = 30,
	
	CbtSpamBlock = "saber1hhit3_block",
	CbtSpamCounter = "saber1hhit3_counter",
	CbtSpamEvade = "saber1hhit3_evade",
	CbtSpamHit = "saber1hhit3_hit",
	CbtSpamMiss = "saber1hhit3_miss"
	
}

AddRandomPoolAttackTargetSkill(lukeAttack17)
