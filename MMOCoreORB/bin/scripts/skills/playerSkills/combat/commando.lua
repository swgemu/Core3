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
	attackname = "flamesingle1",
	animation = "fire_flame_thrower_single_1_light",

	requiredWeaponType = RIFLEFLAMETHROWER,
	
	range = 25,
	damageRatio = 5,
	speedRatio = 4,
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

	healthAttackChance = 34,
	actionAttackChance = 33,
	mindAttackChance = 33,

	dotChance = 100,
	tickStrengthOfHit = 1,

	fireStrength = 1,
	fireType = HEALTH,
	
	CbtSpamBlock = "flamesingle1_block",
	CbtSpamCounter = "flamesingle1_counter",
	CbtSpamEvade = "flamesingle1_evade",
	CbtSpamHit = "flamesingle1_hit",
	CbtSpamMiss = "flamesingle1_miss",
}

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

DotPoolAtt = { 
	attackname = "flamecone1",
	animation = "fire_flame_thrower_cone_1_light",

	requiredWeaponType = RIFLEFLAMETHROWER,
	
	range = 20,
	damageRatio = 5,
	speedRatio = 4,
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

	healthAttackChance = 34,
	actionAttackChance = 33,
	mindAttackChance = 33,

	dotChance = 100,
	tickStrengthOfHit = 1,

	fireStrength = 1,
	fireType = HEALTH,
	
	CbtSpamBlock = "flamecone1_block",
	CbtSpamCounter = "flamecone1_counter",
	CbtSpamEvade = "flamecone1_evade",
	CbtSpamHit = "flamecone1_hit",
	CbtSpamMiss = "flamecone1_miss",
}

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

DotPoolAtt = { 
	attackname = "flamesingle2",
	animation = "fire_flame_thrower_single_2_medium",

	requiredWeaponType = RIFLEFLAMETHROWER,
	
	range = 25,
	damageRatio = 8,
	speedRatio = 4,
	coneAngle = 0,
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

	healthAttackChance = 34,
	actionAttackChance = 33,
	mindAttackChance = 33,

	dotChance = 100,
	tickStrengthOfHit = 1,

	fireStrength = 1,
	fireType = HEALTH,
	
	CbtSpamBlock = "flamesingle2_block",
	CbtSpamCounter = "flamesingle2_counter",
	CbtSpamEvade = "flamesingle2_evade",
	CbtSpamHit = "flamesingle2_hit",
	CbtSpamMiss = "flamesingle2_miss",
}

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

DotPoolAtt = { 
	attackname = "flamecone2",
	animation = "fire_flame_thrower_cone_2_light",

	requiredWeaponType = RIFLEFLAMETHROWER,
	
	range = 20,
	damageRatio = 6,
	speedRatio = 4,
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
	rezChance = 0,

	healthAttackChance = 34,
	actionAttackChance = 33,
	mindAttackChance = 33,

	dotChance = 100,
	tickStrengthOfHit = 1,

	fireStrength = 1,
	fireType = HEALTH,
	
	CbtSpamBlock = "flamecone2_block",
	CbtSpamCounter = "flamecone2_counter",
	CbtSpamEvade = "flamecone2_evade",
	CbtSpamHit = "flamecone2_hit",
	CbtSpamMiss = "flamecone2_miss",
}

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "fireacidsingle1",
	animation = "fire_acid_rifle_single_1_medium",

	requiredWeaponType = RIFLEACIDBEAM,
	
	range = 40,
	damageRatio = 5,
	speedRatio = 4,
	coneAngle = 0,
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

	healthAttackChance = 34,
	actionAttackChance = 33,
	mindAttackChance = 33,
	
	CbtSpamBlock = "fireacidsingle1_block",
	CbtSpamCounter = "fireacidsingle1_counter",
	CbtSpamEvade = "fireacidsingle1_evade",
	CbtSpamHit = "fireacidsingle1_hit",
	CbtSpamMiss = "fireacidsingle1_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "fireacidcone1",
	animation = "fire_acid_rifle_cone_1_light",

	requiredWeaponType = RIFLEACIDBEAM,
	
	range = 30,
	damageRatio = 5,
	speedRatio = 4,
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

	healthAttackChance = 34,
	actionAttackChance = 33,
	mindAttackChance = 33,
	
	CbtSpamBlock = "fireacidcone1_block",
	CbtSpamCounter = "fireacidcone1_counter",
	CbtSpamEvade = "fireacidcone1_evade",
	CbtSpamHit = "fireacidcone1_hit",
	CbtSpamMiss = "fireacidcone1_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "fireacidsingle2",
	animation = "fire_acid_rifle_single_2_medium",

	requiredWeaponType = RIFLEACIDBEAM,
	
	range = 40,
	damageRatio = 8,
	speedRatio = 4,
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

	healthAttackChance = 34,
	actionAttackChance = 33,
	mindAttackChance = 33,
	
	CbtSpamBlock = "fireacidsingle2_block",
	CbtSpamCounter = "fireacidsingle2_counter",
	CbtSpamEvade = "fireacidsingle2_evade",
	CbtSpamHit = "fireacidsingle2_hit",
	CbtSpamMiss = "fireacidsingle2_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "fireacidcone2",
	animation = "fire_acid_rifle_cone_2_light",

	requiredWeaponType = RIFLEACIDBEAM,
	
	range = 30,
	damageRatio = 6,
	speedRatio = 4,
	coneAngle = 30,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

	healthAttackChance = 34,
	actionAttackChance = 33,
	mindAttackChance = 33,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "fireacidcone2_block",
	CbtSpamCounter = "fireacidcone2_counter",
	CbtSpamEvade = "fireacidcone2_evade",
	CbtSpamHit = "fireacidcone2_hit",
	CbtSpamMiss = "fireacidcone2_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

FireHWWeapon = {
	attackname = "firerocketlauncher",
	animation = "fire_heavy_rocket_launcher_medium",

	requiredWeaponType = ALL,
	
	range = 64,
	damageRatio = 1.0,
	speedRatio = 1.0,
	areaRange = 8,
	accuracyBonus = 0,
			
	knockdownChance = 75,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "rocket_launcher_block",
	CbtSpamCounter = "rocket_launcher_counter",
	CbtSpamEvade = "rocket_launcher_evade",
	CbtSpamHit = "rocket_launcher_hit",
	CbtSpamMiss = "rocket_launcher_miss",
	
	deBuffStrFile = "",
	deBuffHitMessage = "",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}
AddHeavyWeaponSkill(FireHWWeapon)

FireHWWeapon = {
	attackname = "firelightningbeam",
	animation = "fire_heavy_lightning_beam_medium",

	requiredWeaponType = ALL,
	
	range = 64,
	damageRatio = 1.0,
	speedRatio = 1.0,
	areaRange = 8,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "lightning_beam_block",
	CbtSpamCounter = "lightning_beam_counter",
	CbtSpamEvade = "lightning_beam_evade",
	CbtSpamHit = "lightning_beam_hit",
	CbtSpamMiss = "lightning_beam_miss",
	
	deBuffStrFile = "",
	deBuffHitMessage = "",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}
AddHeavyWeaponSkill(FireHWWeapon)

FireHWWeapon = {
	attackname = "fireacidbeam",
	animation = "fire_heavy_acid_beam_medium",

	requiredWeaponType = ALL,
	
	range = 64,
	damageRatio = 1.0,
	speedRatio = 1.0,
	areaRange = 8,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "acid_beam_block",
	CbtSpamCounter = "acid_beam_counter",
	CbtSpamEvade = "acid_beam_evade",
	CbtSpamHit = "acid_beam_hit",
	CbtSpamMiss = "acid_beam_miss",
	
	deBuffStrFile = "",
	deBuffHitMessage = "",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}
AddHeavyWeaponSkill(FireHWWeapon)

FireHWWeapon = {
	attackname = "fireparticlebeam",
	animation = "fire_heavy_patricle_beam_medium",

	requiredWeaponType = ALL,
	
	range = 64,
	damageRatio = 1.0,
	speedRatio = 1.0,
	areaRange = 8,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "particle_beam_block",
	CbtSpamCounter = "particle_beam_counter",
	CbtSpamEvade = "particle_beam_evade",
	CbtSpamHit = "particle_beam_hit",
	CbtSpamMiss = "particle_beam_miss",
	
	deBuffStrFile = "",
	deBuffHitMessage = "",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}
AddHeavyWeaponSkill(FireHWWeapon)

--- Fragment Grenade (Novice Commando)ThrowSkill = { 
	attackname = "throwgrenadefragmentation",
	animation = "throw_grenade_medium_fragmentation",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 8,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "throw_fragmentation_block",
	CbtSpamCounter = "throw_fragmentation_counter",
	CbtSpamEvade = "throw_fragmentation_evade",
	CbtSpamHit = "throw_fragmentation_hit",
	CbtSpamMiss = "throw_fragmentation_miss",
	
	deBuffStrFile = "",
	deBuffHitMessage = "",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowGrenadeTargetSkill(ThrowSkill)

--- Glop Grenade (Field Tactics 1)ThrowSkill = { 
	attackname = "throwgrenadecryoban",
	animation = "throw_grenade_medium_cryoban",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 8,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "throw_cryoban_block",
	CbtSpamCounter = "throw_cryoban_counter",
	CbtSpamEvade = "throw_cryoban_evade",
	CbtSpamHit = "throw_cryoban_hit",
	CbtSpamMiss = "throw_cryoban_miss",
	
	deBuffStrFile = "",
	deBuffHitMessage = "",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowGrenadeTargetSkill(ThrowSkill)

--- Glop Grenade (Field Tactics 2)ThrowSkill = { 
	attackname = "throwgrenadeglop",
	animation = "throw_grenade_medium_glop",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 8,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "throw_glop_block",
	CbtSpamCounter = "throw_glop_counter",
	CbtSpamEvade = "throw_glop_evade",
	CbtSpamHit = "throw_glop_hit",
	CbtSpamMiss = "throw_glop_miss",
	
	deBuffStrFile = "",
	deBuffHitMessage = "",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowGrenadeTargetSkill(ThrowSkill)

--- Imperial Detonator (Field Tactics 3)ThrowSkill = { 
	attackname = "throwimperialdetonator",
	animation = "throw_grenade_medium_imperial_detonator",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 8,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "throw_imperial_detonator_block",
	CbtSpamCounter = "throw_imperial_detonator_counter",
	CbtSpamEvade = "throw_imperial_detonator_evade",
	CbtSpamHit = "throw_imperial_detonator_hit",
	CbtSpamMiss = "throw_imperial_detonator_miss",
	
	deBuffStrFile = "",
	deBuffHitMessage = "",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowGrenadeTargetSkill(ThrowSkill)

--- Thermal Detonator (Field Tactics 4)ThrowSkill = { 
	attackname = "throwthermaldetonator",
	animation = "throw_grenade_medium_thermal_detonator",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 8,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "throw_thermal_detonator_block",
	CbtSpamCounter = "throw_thermal_detonator_counter",
	CbtSpamEvade = "throw_thermal_detonator_evade",
	CbtSpamHit = "throw_thermal_detonator_hit",
	CbtSpamMiss = "throw_thermal_detonator_miss",
	
	deBuffStrFile = "",
	deBuffHitMessage = "",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowGrenadeTargetSkill(ThrowSkill)

--- Proton Grenade (Master Commando)ThrowSkill = { 
	attackname = "throwgrenadeproton",
	animation = "throw_grenade_medium_proton",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 8,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "throw_proton_block",
	CbtSpamCounter = "throw_proton_counter",
	CbtSpamEvade = "throw_proton_evade",
	CbtSpamHit = "throw_proton_hit",
	CbtSpamMiss = "throw_proton_miss",
	
	deBuffStrFile = "",
	deBuffHitMessage = "",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowGrenadeTargetSkill(ThrowSkill)
