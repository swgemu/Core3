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

acklayAttack1 = {
	attackname = "acklayAttack1",
	animation = "creature_attack_ranged_light",
	
	requiredWeaponType = NONE,

	range = 40,

	damageRatio = 95,

	speedRatio = .5,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 100,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(acklayAttack1)

-----------------------------------------------

acklayAttack2 = {
	attackname = "acklayAttack2",
	animation = "creature_attack_special_1_medium",
	
	requiredWeaponType = NONE,

	range = 40,

	damageRatio = 95,

	speedRatio = .5,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 100,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(acklayAttack2)

-----------------------------------------------

acklayAttack3 = {
	attackname = "acklayAttack3",
	animation = "creature_attack_special_1_light",
	
	requiredWeaponType = NONE,

	range = 40,

	damageRatio = 95,

	speedRatio = .5,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 100,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(acklayAttack3)

-----------------------------------------------

acklayAttack4 = {
	attackname = "acklayAttack4",
	animation = "creature_attack_special_2_medium",
	
	requiredWeaponType = NONE,

	range = 40,

	damageRatio = 95,

	speedRatio = .5,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 100,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(acklayAttack4)

-----------------------------------------------

acklayAttack5 = {
	attackname = "acklayAttack5",
	animation = "creature_attack_special_2_light",
	
	requiredWeaponType = NONE,

	range = 40,

	damageRatio = 95,

	speedRatio = .5,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 100,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(acklayAttack5)

-----------------------------------------------

acklayAttack6 = {
	attackname = "acklayAttack6",
	animation = "creature_attack_medium",
	
	requiredWeaponType = NONE,

	range = 40,

	damageRatio = 95,

	speedRatio = .5,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 100,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(acklayAttack6)

-----------------------------------------------

acklayAttack7 = {
	attackname = "acklayAttack7",
	animation = "creature_attack_light",
	
	requiredWeaponType = NONE,

	range = 40,

	damageRatio = 95,

	speedRatio = .5,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 85,
	postureDownChance = 85,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(acklayAttack7)

-----------------------------------------------

acklayAttack8 = {
	attackname = "acklayAttack8",
	animation = "creature_attack_light",
	
	requiredWeaponType = NONE,

	range = 40,

	damageRatio = 95,

	speedRatio = .5,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 50,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(acklayAttack8)

-----------------------------------------------

acklayAttack9 = {
	attackname = "acklayAttack9",
	animation = "creature_attack_light",
	
	requiredWeaponType = NONE,

	range = 40,

	damageRatio = 95,

	speedRatio = 4,

	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	actionAttackChance = 100,
	mindAttackChance = 0,

	dotChance = 95,
	tickStrengthOfHit = 128,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
	bleedingType = 0,

	poisonStrength = 256,
	poisonType = ACTION,

	diseaseStrength = 0,
	diseaseType = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
}

AddDotPoolAttackTargetSkill(acklayAttack9)
