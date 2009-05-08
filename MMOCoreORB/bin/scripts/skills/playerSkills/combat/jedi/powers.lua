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

CmbtEnhaceSkill = {
	skillname = "forcethrow1",
	animation = "force_throw_1_particle_level_1_light",
	
	attackType = FORCETHROW,
	minDamage = 500,  -- values added for testing will need confirming
	maxDamage = 550,
	damageType = KINETIC,
	
	forceCost = 28,

	range = 30,

	duration = 30.0,
	
	speed = 3.0,

	meleeDamagePenalty = 0,
	rangedDamagePenalty = 0,

	meleeAccuracyPenalty = 0,
	rangedAccuracyPenalty = 0,

	defensePenalty = 0,
	speedPenalty = 0,

	nextAttackDelay = 0,

	dizzyChance = 0,
	blindChance = 0,
	stunChance = 25,
	intimidateChance = 0,

	selfEffect = "",

	FlyText = "",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	instant = 0
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "forcethrow2",
	animation = "force_throw_1_particle_level_1_medium",

	attackType = FORCETHROW,
	minDamage = 1000, -- values added for testing will need confirming
	maxDamage = 1200,
	damageType = KINETIC,
	
	forceCost = 56,

	range = 30,
	coneAngle = 40, --needs to be confirmed
	
	duration = 30.0,
	
	speed = 3.0,

	meleeDamagePenalty = 0,
	rangedDamagePenalty = 0,

	meleeAccuracyPenalty = 0,
	rangedAccuracyPenalty = 0,

	defensePenalty = 0,
	speedPenalty = 0,

	nextAttackDelay = 0,

	dizzyChance = 0,
	blindChance = 0,
	stunChance = 50,
	intimidateChance = 0,

	selfEffect = "",

	FlyText = "",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	instant = 0
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "forceweaken1",
	animation = "force_weaken_1_particle_level_1_light",
	
	attackType = FORCEWEAKEN,

	forceCost = 400,

	range = 30,

	duration = 100.0,
	
	speed = 3.0,

	meleeDamagePenalty = 0,
	rangedDamagePenalty = 0,

	meleeAccuracyPenalty = 0,
	rangedAccuracyPenalty = 0,

	defensePenalty = 15,
	speedPenalty = 0,

	nextAttackDelay = 0,

	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	selfEffect = "",

	FlyText = "",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	instant = 0
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "forceweaken2",
	animation = "force_weaken_1_particle_level_1_light",

	attackType = FORCEWEAKEN,
	
	forceCost = 400,

	range = 30,

	duration = 100.0,
	
	speed = 3.0,

	meleeDamagePenalty = 0,
	rangedDamagePenalty = 0,

	meleeAccuracyPenalty = 0,
	rangedAccuracyPenalty = 0,

	defensePenalty = 40,
	speedPenalty = 0,

	nextAttackDelay = 0,

	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	selfEffect = "",

	FlyText = "",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	instant = 0
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "forceintimidate1",
	animation = "force_intimidate_chain",
	
	attackType = FORCEINTIMIDATE,

	forceCost = 300,

	range = 30,
	coneAngle = 40,  -- cone angle needs checking

	duration = 60.0,
	
	speed = 1.5,

	meleeDamagePenalty = 0,
	rangedDamagePenalty = 0,

	meleeAccuracyPenalty = 0,
	rangedAccuracyPenalty = 0,

	defensePenalty = 0,
	speedPenalty = 0,

	nextAttackDelay = 0,

	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 100,

	selfEffect = "",

	FlyText = "",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	instant = 0
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "forceintimidate2",
	animation = "force_intimidate",
	
	attackType = FORCEINTIMIDATE,

	forceCost = 500,

	range = 30, --seems a bit far
	coneAngle = 360,  -- area affect

	duration = 90.0,
	
	speed = 1.5,

	meleeDamagePenalty = 0,
	rangedDamagePenalty = 0,

	meleeAccuracyPenalty = 0,
	rangedAccuracyPenalty = 0,

	defensePenalty = 0,
	speedPenalty = 0,

	nextAttackDelay = 0,

	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 100,

	selfEffect = "",

	FlyText = "",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	instant = 0
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

RandomPoolAtt = {
	attackname = "mindblast1",
	animation = "force_mind_blast_1_particle_level_1_light",
	
	forceCost = 68,
	
	attackType = MINDBLAST,
	
	range = 32,
	damageRatio = 2.5,	--We dont know the real value yet
	speed = 3.0,
	accuracyBonus = 0,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0.5,
	stunChance = 0.5,
	
	CbtSpamBlock = "mindblast1_block",
	CbtSpamCounter = "mindblast1_counter",
	CbtSpamEvade = "mindblast1_evade",
	CbtSpamHit = "mindblast1_hit",
	CbtSpamMiss = "mindblast1_miss",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	
	instant = 0
}

AddForcePowersPoolAttackTargetSkill(RandomPoolAtt)

-----------------------------------------------------------------------

RandomPoolAtt = {
	attackname = "mindblast2",
	animation = "force_mind_blast_1_particle_level_1_medium",
	
	forceCost = 160,
	
	attackType = MINDBLAST,
	
	range = 32,
	damageRatio = 4.0,	--We dont know the real value yet
	speed = 4.0,
	accuracyBonus = 0,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 1.5,
	stunChance = 1.5,
	
	CbtSpamBlock = "mindblast2_block",
	CbtSpamCounter = "mindblast2_counter",
	CbtSpamEvade = "mindblast2_evade",
	CbtSpamHit = "mindblast2_hit",
	CbtSpamMiss = "mindblast2_miss",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	
	instant = 0
}

AddForcePowersPoolAttackTargetSkill(RandomPoolAtt)

-----------------------------------------------------------------------

RandomPoolAtt = {
	attackname = "forcelightningcone1",
	animation = "force_lightning_1_arc_particle_level_5_light",
	
	forceCost = 125,
	attackType = FORCELIGHTNING,
	
	minDamage = 750,
	maxDamage = 800,
	damageType = ELECTRICITY,
	
	speed = 4.0,
	
	range = 32,
	coneAngle = 60,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 1,
	
	CbtSpamBlock = "forcelightningcone1_block",
	CbtSpamCounter = "forcelightningcone1_counter",
	CbtSpamEvade = "forcelightningcone1_evade",
	CbtSpamHit = "forcelightningcone1_hit",
	CbtSpamMiss = "forcelightningcone1_miss",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,",
	
	instant = 0
}

AddForcePowersPoolAttackTargetSkill(RandomPoolAtt)

-----------------------------------------------------------------------

RandomPoolAtt = {
	attackname = "forcelightningcone2",
	animation = "force_lightning_1_arc_particle_level_5_medium",
	
	forceCost = 250,
	attackType = FORCELIGHTNING,
	
	minDamage = 1000,
	maxDamage = 1100,
	dmageType = ELECTRICITY,
	
	speed = 4.0,
	
	range = 32,
	coneAngle = 70,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 1,
	
	CbtSpamBlock = "forcelightningcone2_block",
	CbtSpamCounter = "forcelightningcone2_counter",
	CbtSpamEvade = "forcelightningcone2_evade",
	CbtSpamHit = "forcelightningcone2_hit",
	CbtSpamMiss = "forcelightningcone2_miss",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,",
	
	instant = 0
}

AddForcePowersPoolAttackTargetSkill(RandomPoolAtt)

-----------------------------------------------------------------------

RandomPoolAtt = {
	attackname = "forcelightningsingle1",
	animation = "force_lightning_1_particle_level_5_light",
	
	forceCost = 75,
	
	attackType = FORCELIGHTNING,
	
	minamage = 1000,
	maxDamage = 1100,
	damageType = ELECTRICITY,
	
	speed = 3.0,
	
	range = 32,
	coneAngle = 0,
	
	dizzyChance = 25,
	
	CbtSpamBlock = "forcelightningsingle1_block",
	CbtSpamCounter = "forcelightningsingle1_counter",
	CbtSpamEvade = "forcelightningsingle1_evade",
	CbtSpamHit = "forcelightningsingle1_hit",
	CbtSpamMiss = "forcelightningsingle1_miss",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,",
	
	instant = 0
}

AddForcePowersPoolAttackTargetSkill(RandomPoolAtt)

-----------------------------------------------------------------------

RandomPoolAtt = {
	attackname = "forcelightningsingle2",
	animation = "force_lightning_1_particle_level_5_medium",
	
	forceCost = 150,
	attackType = FORCELIGHTNING,
	
	minDamage = 1500,
	maxDamage = 1600,
	damageType = ELECTRICITY,
	
	speed = 4.0,
	
	range = 32,
	coneAngle = 0,
	
	dizzyChance = 35,
	
	CbtSpamBlock = "forcelightningsingle2_block",
	CbtSpamCounter = "forcelightningsingle2_counter",
	CbtSpamEvade = "forcelightningsingle2_evade",
	CbtSpamHit = "forcelightningsingle2_hit",
	CbtSpamMiss = "forcelightningsingle2_miss",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,",
	
	instant = 0
}

AddForcePowersPoolAttackTargetSkill(RandomPoolAtt)

-----------------------------------------------------------------------

RandomPoolAtt = {
	attackname = "forceknockdown1",
	animation = "force_knockdown_1_particle_level_1",
	
	forceCost = 75,
	
	attackType = FORCEKNOCKDOWN,
	
	range = 32,
	coneAngle = 0,  -- knockdown 1 attacks single target no damage
	speed = 3.5,
	accuracyBonus = 0,
	
	knockdownChance = 1,
	postureDownChance = 0,
	
	CbtSpamBlock = "forceknockdown1_block",
	CbtSpamCounter = "forceknockdown1_counter",
	CbtSpamEvade = "forceknockdown1_evade",
	CbtSpamHit = "forceknockdown1_hit",
	CbtSpamMiss = "forceknockdown1_miss",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	
	instant = 0
}

AddForcePowersPoolAttackTargetSkill(RandomPoolAtt)

-----------------------------------------------------------------------

RandomPoolAtt = {
	attackname = "forceknockdown2",
	animation = "force_knockdown_1_arc_particle_level_1",
	
	forceCost = 100,
	
	attackType = FORCEKNOCKDOWN,
	
	range = 32,
	coneAngle = 40,  --knockdown 2 affects cone no damage
	speed = 3.0,
	accuracyBonus = 0,
	
	knockdownChance = 1,
	postureDownChance = 0,
	
	CbtSpamBlock = "forceknockdown2_block",
	CbtSpamCounter = "forceknockdown2_counter",
	CbtSpamEvade = "forceknockdown2_evade",
	CbtSpamHit = "forceknockdown2_hit",
	CbtSpamMiss = "forceknockdown2_miss",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	
	instant = 0
}

AddForcePowersPoolAttackTargetSkill(RandomPoolAtt)

-----------------------------------------------------------------------

RandomPoolAtt = {
	attackname = "forceknockdown3",
	animation = "force_knockdown_1_arc_particle_level_1",
	
	forceCost = 200,
	
	attackType = FORCEKNOCKDOWN,
	
	range = 32,  --this sems rather large for area affect
	coneAngle = 360,  --knockdown 3 area affect, no damage
	speed = 2.5,
	accuracyBonus = 0,
	
	knockdownChance = 1,
	postureDownChance = 0,
	
	CbtSpamBlock = "forceknockdown3_block",
	CbtSpamCounter = "forceknockdown3_counter",
	CbtSpamEvade = "forceknockdown3_evade",
	CbtSpamHit = "forceknockdown3_hit",
	CbtSpamMiss = "forceknockdown3_miss",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	
	instant = 0
}

AddForcePowersPoolAttackTargetSkill(RandomPoolAtt)

-----------------------------------------------------------------------

RandomPoolAtt = {
	attackname = "forcechoke",
	animation = "force_choke_1_particle_level_1_medium",
	
	forceCost = 400,
	
	attackType = FORCECHOKE,
	
	range = 32,
	minDamage = 1200,	--We dont know the real value yet
	maxDamage = 1500,
	speed = 5.0,
	accuracyBonus = 0,
	damageType = FORCE,
	
	knockdownChance = 0,
	postureDownChance = 0,
	
	dotChance = 100,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 1,
	bleedingType = ACTION,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "forcechoke_block",
	CbtSpamCounter = "forcechoke_counter",
	CbtSpamEvade = "forcechoke_evade",
	CbtSpamHit = "forcechoke_hit",
	CbtSpamMiss = "forcechoke_miss",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	
	instant = 0
}

AddForcePowersPoolAttackTargetSkill(RandomPoolAtt)

-----------------------------------------------------------------------
