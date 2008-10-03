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

jediAttack1 = {
	attackname = "jediAttack1",
	animation = "combo_jedi_2_light",
	
	requiredWeaponType = JEDI,

	range = 11,

	damageRatio = 50,

	speedRatio = 1,
	coneAngle = 0,

	areaRange = 0,
	accuracyBonus = 50,
		
	knockdownChance = 50,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 50,
	blindChance = 50,
	stunChance = 50,
	intimidateChance = 50,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(jediAttack1)

-----------------------------------------------

jediAttack2 = {
	attackname = "jediAttack2",
	animation = "force_intimidate_chain",
	
	requiredWeaponType = JEDI,

	range = 32,

	damageRatio = 50,

	speedRatio = 1,
	coneAngle = 80,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 95,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(jediAttack2)

-----------------------------------------------
jediAttack3 = {
attackname = "jediAttack3",
animation = "force_knockdown_1_arc_particle_level_1",

	requiredWeaponType = JEDI,
	
	range = 8,
	damageRatio = 50,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 50,
		
	knockdownChance = 95,
	postureDownChance = 95,
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

AddRandomPoolAttackTargetSkill(jediAttack3)

-----------------------------------------------

jediAttack4 = {
	attackname = "jediAttack4",
	animation = "combo_jedi_2_light",

	requiredWeaponType = JEDI,

	range = 11,
	coneAngle = 40,
	damageRatio = 50,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 70,
	blindChance = 65,
	stunChance = 60,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmdervish2_block",
	CbtSpamCounter = "saberpolearmdervish2_counter",
	CbtSpamEvade = "saberpolearmdervish2_evade",
	CbtSpamHit = "saberpolearmdervish2_hit",
	CbtSpamMiss = "saberpolearmdervish2_miss"
}

AddRandomPoolAttackTargetSkill(jediAttack4)

-----------------------------------------------------------------------

jediAttack5 = {
	attackname = "jediAttack5",
	animation = "saberthrow_posture_change",

	requiredWeaponType = JEDI,

	range = 64,
	damageRatio = 50,
	speedRatio = 1.0,
	coneAngle = 40,
	accuracyBonus = 50,
	
	knockdownChance = 70,
	postureDownChance = 70,
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

AddRandomPoolAttackTargetSkill(jediAttack5)

-----------------------------------------------------------------------

jediAttack6 = { 
	attackname = "jediAttack6",
	animation = "combo_2d_light",

	requiredWeaponType = JEDI,
	
	range = 11,
	damageRatio = 40,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
	postureDownChance = 20,
		
	healthAttackChance = 90,
	actionAttackChance = 70,
	mindAttackChance = 50,

	dotChance = 50,
	tickStrengthOfHit = 10,

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

AddDotPoolAttackTargetSkill(jediAttack6)

-----------------------------------------------------------------------

jediAttack7 = { 
	attackname = "jediAttack7",
	animation = "force_choke_1_particle_level_1_medium",

	requiredWeaponType = JEDI,
	
	range = 64,
	damageRatio = 50,
	speedRatio = 1.0,
	coneAngle = 0,
	accuracyBonus = 50,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 95,
	blindChance = 50,
	stunChance = 50,
	intimidateChance = 10,
	
	CbtSpamBlock = "forcechoke_block",
	CbtSpamCounter = "forcechoke_counter",
    CbtSpamEvade = "forcechoke_evade",
    CbtSpamHit = "forcechoke_hit",
    CbtSpamMiss = "forcechoke_miss"
}

AddDotPoolAttackTargetSkill(jediAttack7)

-----------------------------------------------------------------------

jediAttack8 = { 
	attackname = "jediAttack8",	
	animation = "saberthrow_posture_change",

	requiredWeaponType = JEDI,

	range = 64,
	damageRatio = 50,
	speedRatio = 1.0,
	coneAngle = 0,
	accuracyBonus = 50,
	
	knockdownChance = 70,
	postureDownChance = 70,
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

AddDotPoolAttackTargetSkill(jediAttack8)

-----------------------------------------------------------------------
