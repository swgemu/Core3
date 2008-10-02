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
	
	--forceCost = 28,

	range = 30,

	duration = 30.0,
	
	speedRatio = 3.0,

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

	FlyText = ""
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "forcethrow2",
	animation = "force_throw_1_particle_level_1_medium",
	
	--forceCost = 56,

	range = 30,

	duration = 30.0,
	
	speedRatio = 3.0,

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

	FlyText = ""
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "forceweaken1",
	animation = "force_weaken_1_particle_level_1_light",
	
	--forceCost = 400,

	range = 30,

	duration = 100.0,
	
	speedRatio = 3.0,

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

	FlyText = ""
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "forceweaken2",
	animation = "force_weaken_1_particle_level_1_light",
	
	--forceCost = 400,

	range = 30,

	duration = 100.0,
	
	speedRatio = 3.0,

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

	FlyText = ""
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "forceintimidate1",
	animation = "force_intimidate_chain",
	
	--forceCost = 300,

	range = 30,

	duration = 100.0,
	
	speedRatio = 1.5,

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
	intimidateChance = 25,

	selfEffect = "",

	FlyText = ""
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "forceintimidate2",
	animation = "force_intimidate",
	
	--forceCost = 500,

	range = 30,

	duration = 100.0,
	
	speedRatio = 1.5,

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
	intimidateChance = 50,

	selfEffect = "",

	FlyText = ""
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "mindblast1",
	animation = "force_mind_blast_1_particle_level_1_light",
	
	--forceCost = 68,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	damageRatio = 2.5,	--We dont know the real value yet
	speedRatio = 3.0,
	accuracyBonus = 0,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0.5,
	stunChance = 0.5,
	
	CbtSpamBlock = "mindblast1_block",
	CbtSpamCounter = "mindblast1_counter",
	CbtSpamEvade = "mindblast1_evade",
	CbtSpamHit = "mindblast1_hit",
	CbtSpamMiss = "mindblast1_miss"
	
}

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "mindblast2",
	animation = "force_mind_blast_1_particle_level_1_medium",
	
	--forceCost = 160,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	damageRatio = 4.0,	--We dont know the real value yet
	speedRatio = 4.0,
	accuracyBonus = 0,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 1.5,
	stunChance = 1.5,
	
	CbtSpamBlock = "mindblast2_block",
	CbtSpamCounter = "mindblast2_counter",
	CbtSpamEvade = "mindblast2_evade",
	CbtSpamHit = "mindblast2_hit",
	CbtSpamMiss = "mindblast2_miss"
	
}

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "forcelightningcone1",
	animation = "force_lightning_1_arc_particle_level_5_light",
	
	--forceCost = 125,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 60,
	damageRatio = 1.0,	--We dont know the real value yet
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 1,
	
	CbtSpamBlock = "forcelightningcone1_block",
	CbtSpamCounter = "forcelightningcone1_counter",
	CbtSpamEvade = "forcelightningcone1_evade",
	CbtSpamHit = "forcelightningcone1_hit",
	CbtSpamMiss = "forcelightningcone1_miss"
	
}

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "forcelightningcone2",
	animation = "force_lightning_1_arc_particle_level_5_medium",
	
	--forceCost = 250,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 70,
	damageRatio = 2.0,	--We dont know the real value yet
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 1,
	
	CbtSpamBlock = "forcelightningcone2_block",
	CbtSpamCounter = "forcelightningcone2_counter",
	CbtSpamEvade = "forcelightningcone2_evade",
	CbtSpamHit = "forcelightningcone2_hit",
	CbtSpamMiss = "forcelightningcone2_miss"
	
}

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "forcelightningsingle1",
	animation = "force_lightning_1_particle_level_5_light",
	
	--forceCost = 75,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 0,
	damageRatio = 2.5,	--We dont know the real value yet
	speedRatio = 4.0,
	accuracyBonus = 0,
	
	dizzyChance = 25,
	
	CbtSpamBlock = "forcelightningsingle1_block",
	CbtSpamCounter = "forcelightningsingle1_counter",
	CbtSpamEvade = "forcelightningsingle1_evade",
	CbtSpamHit = "forcelightningsingle1_hit",
	CbtSpamMiss = "forcelightningsingle1_miss"
	
}

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "forcelightningsingle2",
	animation = "force_lightning_1_particle_level_5_medium",
	
	--forceCost = 150,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 0,
	damageRatio = 3.5,	--We dont know the real value yet
	speedRatio = 4.0,
	accuracyBonus = 0,
	
	dizzyChance = 35,
	
	CbtSpamBlock = "forcelightningsingle2_block",
	CbtSpamCounter = "forcelightningsingle2_counter",
	CbtSpamEvade = "forcelightningsingle2_evade",
	CbtSpamHit = "forcelightningsingle2_hit",
	CbtSpamMiss = "forcelightningsingle2_miss"
	
}

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "forceknockdown1",
	animation = "force_knockdown_1_particle_level_1",
	
	--forceCost = 75,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 70,
	damageRatio = 1.0,	--We dont know the real value yet
	speedRatio = 3.5,
	accuracyBonus = 0,
	
	knockdownChance = 1,
	postureDownChance = 0,
	
	CbtSpamBlock = "forceknockdown1_block",
	CbtSpamCounter = "forceknockdown1_counter",
	CbtSpamEvade = "forceknockdown1_evade",
	CbtSpamHit = "forceknockdown1_hit",
	CbtSpamMiss = "forceknockdown1_miss"
	
}

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "forceknockdown2",
	animation = "force_knockdown_1_particle_level_1",
	
	--forceCost = 100,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 70,
	damageRatio = 2.0,	--We dont know the real value yet
	speedRatio = 3.0,
	accuracyBonus = 0,
	
	knockdownChance = 1,
	postureDownChance = 0,
	
	CbtSpamBlock = "forceknockdown2_block",
	CbtSpamCounter = "forceknockdown2_counter",
	CbtSpamEvade = "forceknockdown2_evade",
	CbtSpamHit = "forceknockdown2_hit",
	CbtSpamMiss = "forceknockdown2_miss"
	
}

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "forceknockdown3",
	animation = "force_knockdown_1_arc_particle_level_1",
	
	--forceCost = 200,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 70,
	damageRatio = 3.0,	--We dont know the real value yet
	speedRatio = 2.5,
	accuracyBonus = 0,
	
	knockdownChance = 1,
	postureDownChance = 0,
	
	CbtSpamBlock = "forceknockdown3_block",
	CbtSpamCounter = "forceknockdown3_counter",
	CbtSpamEvade = "forceknockdown3_evade",
	CbtSpamHit = "forceknockdown3_hit",
	CbtSpamMiss = "forceknockdown3_miss"
	
}

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "forcechoke",
	animation = "force_choke_1_particle_level_1_medium",
	
	--forceCost = 400,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	damageRatio = 2.0,	--We dont know the real value yet
	speedRatio = 2.5,
	accuracyBonus = 0,
	
	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "forcechoke_block",
	CbtSpamCounter = "forcechoke_counter",
	CbtSpamEvade = "forcechoke_evade",
	CbtSpamHit = "forcechoke_hit",
	CbtSpamMiss = "forcechoke_miss"
	
}

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------