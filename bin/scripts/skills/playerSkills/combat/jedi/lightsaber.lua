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

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saberpolearmdervish2",
	animation = "combo_jedi_2_light",

	requiredWeaponType = POLEARMSABER,

	range = 5,
	coneAngle = 40,
	damageRatio = 1.75, -- 2.25
	speedRatio = 1.0,
	accuracyBonus = 0,

	hamCostMultiplier = 1,
	forceCostMultiplier = 1,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 50,
	blindChance = 45,
	stunChance = 40,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmdervish2_block",
	CbtSpamCounter = "saberpolearmdervish2_counter",
	CbtSpamEvade = "saberpolearmdervish2_evade",
	CbtSpamHit = "saberpolearmdervish2_hit",
	CbtSpamMiss = "saberpolearmdervish2_miss"
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saberthrow3",
	animation = "saberthrow_posture_change",
	
	requiredWeaponType = JEDI,
	
	range = 32,
	damageRatio = 1.0,
	speedRatio = 1.0,
	coneAngle = 40,
	accuracyBonus = 0,

	hamCostMultiplier = 1,
	forceCostMultiplier = 1,
	
	knockdownChance = 40,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	CbtSpamBlock = "saberthrow3_block",
	CbtSpamCounter = "saberthrow3_counter",
	CbtSpamEvade = "saberthrow3_evade",
	CbtSpamHit = "saberthrow3_hit",
	CbtSpamMiss = "saberthrow3_miss"
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saberthrow2",
	animation = "saberthrow_posture_change",
	
	requiredWeaponType = JEDI,
	
	range = 32,
	damageRatio = 1.75,
	speedRatio = 2.0,
	coneAngle = 40,
	accuracyBonus = 0,

	hamCostMultiplier = 1,
	forceCostMultiplier = 1,
	
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

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saberthrow1",
	animation = "saberthrow_posture_change",
	
	requiredWeaponType = JEDI,
	
	range = 32,
	damageRatio = 0.35,
	speedRatio = 1.0,
	coneAngle = 40,
	accuracyBonus = 0,

	hamCostMultiplier = 1,
	forceCostMultiplier = 1,
	
	knockdownChance = 10,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	CbtSpamBlock = "saberthrow1_block",
	CbtSpamCounter = "saberthrow1_counter",
	CbtSpamEvade = "saberthrow1_evade",
	CbtSpamHit = "saberthrow1_hit",
	CbtSpamMiss = "saberthrow1_miss"
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

DotPoolAtt = { 
	attackname = "saberslash2",
	animation = "combo_2d_light",
	
	requiredWeaponType = JEDI,
	
	range = 11,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
	postureDownChance = 20,

	hamCostMultiplier = 1,
	forceCostMultiplier = 1,
		
	healthAttackChance = 50,
	actionAttackChance = 35,
	mindAttackChance = 15,

	dotChance = 50,
	tickStrengthOfHit = 3,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
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

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber1hflurry2",
	animation = "combo_jedi_4_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 11,
	coneAngel = 40,
	damageRatio = 1.75, --2.25
	speedRatio = 1.0,
	accuracyBonus = 0,

	hamCostMultiplier = 1,
	forceCostMultiplier = 1,
	
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
	
AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber1hflurry",
	animation = "combo_jedi_2_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 11,
	coneAngel = 40,
	damageRatio = 4.25, --2.25
	speedRatio = 4.0,
	accuracyBonus = 0,

	hamCostMultiplier = 1,
	forceCostMultiplier = 1,
	
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
	
AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber2hphantom",
	animation = "combo_jedi_2_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 7,
	coneAngel = 40,
	damageRatio = 1.75, -- 2.25
	speedRatio = 1.0,
	accuracyBonus = 0,

	hamCostMultiplier = 1,
	forceCostMultiplier = 1,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 50,
	blindChance = 45,
	stunChance = 40,
	intimidateChance = 0,
	
	CbtSpamBlock = "saber2hfrenzy_block",
	CbtSpamCounter = "saber2hfrenzy_counter",
	CbtSpamEvade = "saber2hfrenzy_evade",
	CbtSpamHit = "saber2hdfrenzy_hit",
	CbtSpamMiss = "saber2hfrenzy_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)
-----------------------------------------------------------------------

DirectPoolAtt = {
	attackname = "saber2hbodyhit1",
	animation = "combo_3a_medium",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 7,
	damageRatio = 0.55,
	speedRatio = 1.5,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	healthAttackChance = 40,
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
	
	CbtSpamBlock = "saber2hbodyhit1_block",
	CbtSpamCounter = "saber2hbodyhit1_counter",
	CbtSpamEvade = "saber2hbodyhit1_evade",
	CbtSpamHit = "saber2hbodyhit1_hit",
	CbtSpamMiss = "saber2hbodyhit1_miss"
	
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber2hsweep1",
	animation = "combo_2a_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 7,
	damageRatio = 0.25,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 0.5,
	
	CbtSpamBlock = "saber2hsweep1_block",
	CbtSpamCounter = "saber2hsweep1_counter",
	CbtSpamEvade = "saber2hsweep1_evade",
	CbtSpamHit = "saber2hsweep1_hit",
	CbtSpamMiss = "saber2hsweep1_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber2hsweep2",
	animation = "combo_3d_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 7,
	damageRatio = 0.50,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 1,
	
	CbtSpamBlock = "saber2hsweep2_block",
	CbtSpamCounter = "saber2hsweep2_counter",
	CbtSpamEvade = "saber2hsweep2_evade",
	CbtSpamHit = "saber2hsweep2_hit",
	CbtSpamMiss = "saber2hsweep2_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber2hsweep3",
	animation = "showoff_2_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 7,
	damageRatio = 0.75,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 45,
	
	CbtSpamBlock = "saber2hsweep3_block",
	CbtSpamCounter = "saber2hsweep3_counter",
	CbtSpamEvade = "saber2hsweep3_evade",
	CbtSpamHit = "saber2hsweep3_hit",
	CbtSpamMiss = "saber2hsweep3_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = {
	attackname = "saber2hbodyhit2",
	animation = "combo_3b_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 7,
	damageRatio = 0.75,
	speedRatio = 1.5,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

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
	
	CbtSpamBlock = "saber2hbodyhit2_block",
	CbtSpamCounter = "saber2hbodyhit2_counter",
	CbtSpamEvade = "saber2hbodyhit2_evade",
	CbtSpamHit = "saber2hbodyhit2_hit",
	CbtSpamMiss = "saber2hbodyhit2_miss"
	
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)
	
-----------------------------------------------------------------------

DirectPoolAtt = {
	attackname = "saber2hbodyhit3",
	animation = "showoff_3_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 7,
	damageRatio = 1.0,
	speedRatio = 1.5,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	healthAttackChance = 80,
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
	
	CbtSpamBlock = "saber2hbodyhit3_block",
	CbtSpamCounter = "saber2hbodyhit3_counter",
	CbtSpamEvade = "saber2hbodyhit3_evade",
	CbtSpamHit = "saber2hbodyhit3_hit",
	CbtSpamMiss = "saber2hbodyhit3_miss"
	
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber2hhit1",
	animation = "combo_2a_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 5,
	damageRatio = 0.25,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "saber2hhit1_block",
	CbtSpamCounter = "saber2hhit1_counter",
	CbtSpamEvade = "saber2hhit1_evade",
	CbtSpamHit = "saber2hhit1_hit",
	CbtSpamMiss = "saber2hhit1_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber2hhit2",
	animation = "combo_2b_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 5,
	damageRatio = 0.75,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "saber2hhit2_block",
	CbtSpamCounter = "saber2hhit2_counter",
	CbtSpamEvade = "saber2hhit2_evade",
	CbtSpamHit = "saber2hhit2_hit",
	CbtSpamMiss = "saber2hhit2_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber2hhit3",
	animation = "showoff_2_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 5,
	damageRatio = 1.5, 
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "saber2hhit3_block",
	CbtSpamCounter = "saber2hhit3_counter",
	CbtSpamEvade = "saber2hhit3_evade",
	CbtSpamHit = "saber2hhit3_hit",
	CbtSpamMiss = "saber2hhit3_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = {
	attackname = "saber1hheadhit1",
	animation = "combo_2b_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 5,
	damageRatio = 0.25,
	speedRatio = 1.5,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	healthAttackChance = 15,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 15,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,
	
	mindAttackChance = 30,
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

AddDirectPoolAttackTargetSkill(ForceDirectPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = {
	attackname = "saber1hheadhit2",
	animation = "combo_4b_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 5,
	damageRatio = 3.75,
	speedRatio = 3.5,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

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
	blindChance = 20,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "saber1hheadhit2_block",
	CbtSpamCounter = "saber1hheadhit2_counter",
	CbtSpamEvade = "saber1hheadhit2_evade",
	CbtSpamHit = "saber1hheadhit2_hit",
	CbtSpamMiss = "saber1hheadhit2_miss"
	
}

AddDirectPoolAttackTargetSkill(ForceDirectPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = {
	attackname = "saber1hheadhit3",
	animation = "combo_5a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 5,
	damageRatio = 4.0,
	speedRatio = 3.5,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,
	
	mindAttackChance = 80,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 40,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "saber1hheadhit3_block",
	CbtSpamCounter = "saber1hheadhit3_counter",
	CbtSpamEvade = "saber1hheadhit3_evade",
	CbtSpamHit = "saber1hheadhit3_hit",
	CbtSpamMiss = "saber1hheadhit3_miss"
	
}

AddDirectPoolAttackTargetSkill(ForceDirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber1hcombohit3",
	animation = "combo_4a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 5,
	damageRatio = 3.00,
	speedRatio = 4.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 40,
	
	CbtSpamBlock = "saber1hcombohit3_block",
	CbtSpamCounter = "saber1hcombohit3_counter",
	CbtSpamEvade = "saber1hcombohit3_evade",
	CbtSpamHit = "saber1hcombohit3_hit",
	CbtSpamMiss = "saber1hcombohit3_miss"
	
}

AddDirectPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber1hHit3",
	animation = "combo_3a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 5,
	damageRatio = 3.00,
	speedRatio = 3.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "saberhit3_block",
	CbtSpamCounter = "saberhit3_counter",
	CbtSpamEvade = "saberhit3_evade",
	CbtSpamHit = "saberhit3_hit",
	CbtSpamMiss = "saberhit3_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber1hhit2",
	animation = "combo_3a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 5,
	damageRatio = 3.00,
	speedRatio = 3.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "saber1hHit2_block",
	CbtSpamCounter = "saber1hHit2_counter",
	CbtSpamEvade = "saber1hHit2_evade",
	CbtSpamHit = "saber1hHit2_hit",
	CbtSpamMiss = "saber1hHit2_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saberhit2",
	animation = "combo_3a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 5,
	damageRatio = 3.00,
	speedRatio = 3.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "saberhit2_block",
	CbtSpamCounter = "saberhit2_counter",
	CbtSpamEvade = "saberhit2_evade",
	CbtSpamHit = "saberhit2_hit",
	CbtSpamMiss = "saberhit2_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)


-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber1hcombohit2",
	animation = "combo_3c_lightt",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 5,
	damageRatio = 0.70,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 25,
	
	CbtSpamBlock = "saber1hcombohit2_block",
	CbtSpamCounter = "saber1hcombohit2_counter",
	CbtSpamEvade = "saber1hcombohit2_evade",
	CbtSpamHit = "saber1hcombohit2_hit",
	CbtSpamMiss = "saber1hcombohit2_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saber1hcombohit1",
	animation = "combo_2a_light",
	
	requiredWeaponType = ONEHANDSABER,
	
	range = 5,
	damageRatio = 0.50,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 15,
	
	CbtSpamBlock = "saber1hcombohit1_block",
	CbtSpamCounter = "saber1hcombohit1_counter",
	CbtSpamEvade = "saber1hcombohit1_evade",
	CbtSpamHit = "saber1hcombohit1_hit",
	CbtSpamMiss = "saber1hcombohit1_miss"
	
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saberpolearmspinattack3",
	animation = "showoff_1_light",

	requiredWeaponType = POLEARMSABER,

	range = 11,
	coneAngle = 360,
	damageRatio = 1.0,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 75,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmspin3_block",
	CbtSpamCounter = "saberpolearmspin3_counter",
	CbtSpamEvade = "saberpolearmspin3_evade",
	CbtSpamHit = "saberpolearmspin3_hit",
	CbtSpamMiss = "saberpolearmspin3_miss"
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saberpolearmhit3",
	animation = "combo_4b_light",

	requiredWeaponType = POLEARMSABER,

	range = 11,
	coneAngle = 1,
	damageRatio = 1.0,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 55,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmhit3_block",
	CbtSpamCounter = "saberpolearmhit3_counter",
	CbtSpamEvade = "saberpolearmhit3_evade",
	CbtSpamHit = "saberpolearmhit3_hit",
	CbtSpamMiss = "saberpolearmhit3_miss"
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = {
	attackname = "saberpolearmleghit3",
	animation = "combo_2e_light",
	
	requiredWeaponType = POLEARMSABER,
	
	range = 5,
	damageRatio = 1.0,
	speedRatio = 1.5,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 95,
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
	
	CbtSpamBlock = "saber1hheadleghit3_block",
	CbtSpamCounter = "saber1hheadleg hit3_counter",
	CbtSpamEvade = "saber1hheadleghit3_evade",
	CbtSpamHit = "saber1hheadleghit3_hit",
	CbtSpamMiss = "saber1hheadleghit3_miss"
	
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saberpolearmdervish",
	animation = "combo_3b_light",

	requiredWeaponType = POLEARMSABER,

	range = 11,
	coneAngle = 360,
	damageRatio = 1.25,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 55,
	blindChance = 55,
	stunChance = 55,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmhit3_block",
	CbtSpamCounter = "saberpolearmhit3_counter",
	CbtSpamEvade = "saberpolearmhit3_evade",
	CbtSpamHit = "saberpolearmhit3_hit",
	CbtSpamMiss = "saberpolearmhit3_miss"
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saberpolearmspinattack2",
	animation = "showoff_1_light",

	requiredWeaponType = POLEARMSABER,

	range = 11,
	coneAngle = 360,
	damageRatio = 3.0,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 50,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmspin2_block",
	CbtSpamCounter = "saberpolearmspin2_counter",
	CbtSpamEvade = "saberpolearmspin2_evade",
	CbtSpamHit = "saberpolearmspin2_hit",
	CbtSpamMiss = "saberpolearmspin2_miss"
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = {
	attackname = "saberleghit2",
	animation = "combo_2e_light",
	
	requiredWeaponType = POLEARMSABER,
	
	range = 5,
	damageRatio = 2.5,
	speedRatio = 1.5,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 95,
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
	
	CbtSpamBlock = "saberleghit2_block",
	CbtSpamCounter = "saberleghit2_counter",
	CbtSpamEvade = "saberleghit2_evade",
	CbtSpamHit = "saberleghit2_hit",
	CbtSpamMiss = "saberleghit2_miss"
	
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = {
	attackname = "saberpolearmhit2",
	animation = "combo_5a_medium",

	requiredWeaponType = POLEARMSABER,

	range = 11,
	coneAngle = 1,
	damageRatio = 3.5,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	hamCostMultiplier = 1,
	forceCostMultiplier = 1,

	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 55,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmhit2_block",
	CbtSpamCounter = "saberpolearmhit2_counter",
	CbtSpamEvade = "saberpolearmhit2_evade",
	CbtSpamHit = "saberpolearmhit2_hit",
	CbtSpamMiss = "saberpolearmhit2_miss"
}

AddRandomPoolAttackTargetSkill(ForceRandomPoolAtt)
