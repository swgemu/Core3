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
DotPoolAtt = { 
	attackname = "healthshot2",
	animation = "fire_1_special_single_light",

	requiredWeaponType = PISTOL,
	
	range = 0,
	damageRatio = 3.0,
	speedRatio = 1.9,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

	healthAttackChance = 100,
	actionAttackChance = 0,
	mindAttackChance = 0,
	
	dotChance = 60,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 1,
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

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "pointblanksingle2",
	animation = "fire_5_single_light",

	requiredWeaponType = PISTOL,
	
	range = 10,
	damageRatio = 2.9,
	speedRatio = 1.8,
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
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "pointblankblast_block",
	CbtSpamCounter = "pointblankblast_counter",
	CbtSpamEvade = "pointblankblast_evade",
	CbtSpamHit = "pointblankblast_hit",
	CbtSpamMiss = "pointblankblast_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)


-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "bodyshot3",
	animation = "fire_1_special_single_light",

	requiredWeaponType = PISTOL,
	
	range = 0,
	damageRatio = 2.5,
	speedRatio = 2.4,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

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

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "pointblankarea2",
	animation = "fire_area_no_trails_light",

	requiredWeaponType = PISTOL,
	
	range = 10,
	damageRatio = 4.3,
	speedRatio = 3.0,
	coneAngle = 30,
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
	
	CbtSpamBlock = "areashot_block",
	CbtSpamCounter = "areashot_counter",
	CbtSpamEvade = "areashot_evade",
	CbtSpamHit = "areashot_hit",
	CbtSpamMiss = "areashot_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "disarmingshot1",
	animation = "fire_3_single_light_face",

	requiredWeaponType = PISTOL,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 2.3,
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
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "disarmshot_block",
	CbtSpamCounter = "disarmshot_counter",
	CbtSpamEvade = "disarmshot_evade",
	CbtSpamHit = "disarmshot_hit",
	CbtSpamMiss = "disarmshot_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "doubletap",
	animation = "fire_7_single_light_face",

	requiredWeaponType = PISTOL,
	
	range = 0,
	damageRatio = 2.8,
	speedRatio = 2.1,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
	
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

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "stoppingshot",
	animation = "fire_1_special_single_light",

	requiredWeaponType = PISTOL,
	
	range = 0,
	damageRatio = 5.0,
	speedRatio = 4.0,
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
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "stoppingshot_block",
	CbtSpamCounter = "stoppingshot_counter",
	CbtSpamEvade = "stoppingshot_evade",
	CbtSpamHit = "stoppingshot_hit",
	CbtSpamMiss = "stoppingshot_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "fanshot",
	animation = "fire_area_light",

	requiredWeaponType = PISTOL,
	
	range = 0,
	damageRatio = 4.0,
	speedRatio = 2.4,
	areaRange = 0,
	coneAngle = 60,	
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
	
	CbtSpamBlock = "fanshot_block",
	CbtSpamCounter = "fanshot_counter",
	CbtSpamEvade = "fanshot_evade",
	CbtSpamHit = "fanshot_hit",
	CbtSpamMiss = "fanshot_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "pistolmeleedefense1",
	animation = "ranged_melee_light",

	requiredWeaponType = PISTOL,
	
	range = 5,
	damageRatio = 2.9,
	speedRatio = 2.3,
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
	
	CbtSpamBlock = "pistolwhip_block",
	CbtSpamCounter = "pistolwhip_counter",
	CbtSpamEvade = "pistolwhip_evade",
	CbtSpamHit = "pistolwhip_hit",
	CbtSpamMiss = "pistolwhip_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",

	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "pistolmeleedefense2",
	animation = "ranged_melee_light",

	requiredWeaponType = PISTOL,
	
	range = 5,
	damageRatio = 4.1,
	speedRatio = 2.5,
	areaRange = 0,
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
	
	CbtSpamBlock = "pistolsmash_block",
	CbtSpamCounter = "pistolsmash_counter",
	CbtSpamEvade = "pistolsmash_evade",
	CbtSpamHit = "pistolsmash_hit",
	CbtSpamMiss = "pistolsmash_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",

	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "multitargetpistolshot",
	animation = "fire_5_special_single_light",

	requiredWeaponType = PISTOL,
	
	range = 0,
	damageRatio = 4.2,
	speedRatio = 3.5,
	coneAngle = 30,
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
	
	CbtSpamBlock = "pistolmultishot_block",
	CbtSpamCounter = "pistolmultishot_counter",
	CbtSpamEvade = "pistolmultishot_evade",
	CbtSpamHit = "pistolmultishot_hit",
	CbtSpamMiss = "pistolmultishot_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "disarmingshot2",
	animation = "fire_3_single_light_face",

	requiredWeaponType = PISTOL,
	
	range = 0,
	damageRatio = 2.7,
	speedRatio = 2.5,
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
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "disarmblast_block",
	CbtSpamCounter = "disarmblast_counter",
	CbtSpamEvade = "disarmblast_evade",
	CbtSpamHit = "disarmblast_hit",
	CbtSpamMiss = "disarmblast_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------
