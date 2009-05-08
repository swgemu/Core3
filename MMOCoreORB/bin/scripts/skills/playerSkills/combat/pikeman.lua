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
RandPoolAtt = { 
	attackname = "polearmhit2",
	animation = "combo_3a_medium",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 2.5,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 20,
	intimidateChance = 0,
	
	CbtSpamBlock = "bonebreaker_block",
	CbtSpamCounter = "bonebreaker_counter",
	CbtSpamEvade = "bonebreaker_evade",
	CbtSpamHit = "bonebreaker_hit",
	CbtSpamMiss = "bonebreaker_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmstun2",
	animation = "lower_posture_2hmelee_5",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 2.0,
	areaRange = 7,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 40,
	intimidateChance = 0,
	
	CbtSpamBlock = "breathtaker_block",
	CbtSpamCounter = "breathtaker_counter",
	CbtSpamEvade = "breathtaker_evade",
	CbtSpamHit = "breathtaker_hit",
	CbtSpamMiss = "breathtaker_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmspinattack2",
	animation = "combo_2c_medium",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 2.5,
	speedRatio = 3.0,
	areaRange = 7,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 30,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "polearmleghit2",
	animation = "combo_3c_light",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 100,
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

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmarea1",
	animation = "combo_2c_medium",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 2.2,
	areaRange = 7,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
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

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "polearmleghit3",
	animation = "combo_3b_medium",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 2.5,
	speedRatio = 3.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 100,
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

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmarea2",
	animation = "lower_posture_2hmelee_6",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 2.75,
	speedRatio = 3.0,
	areaRange = 7,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 30,
	blindChance = 0,
	stunChance = 30,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmsweep1",
	animation = "attack_low_right_medium_0",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 10,
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

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmsweep2",
	animation = "combo_3d_medium",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 2.5,
	speedRatio = 3.0,
	areaRange = 7,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 30,
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

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "polearmactionhit1",
	animation = "attack_low_right_medium_0",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

	healthAttackChance = 0,
	actionAttackChance = 100,
	mindAttackChance = 0,
		
	dotChance = 50,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 1,
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

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDotPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "polearmactionhit2",
	animation = "lower_posture_2hmelee_2",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 3.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

	healthAttackChance = 0,
	actionAttackChance = 100,
	mindAttackChance = 0,
	
	dotChance = 60,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 1,
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

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDotPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmhit3",
	animation = "combo_5a_medium",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 4.0,
	speedRatio = 3.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 60,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 30,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------
