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

tuskenAttack40 = { 
	attackname = "tuskenAttack40",
	animation = "combo_4a_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 6,
	damageRatio = 4.5,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,
		
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
}

AddRandomPoolAttackTargetSkill(tuskenAttack40)

-----------------------------------------------------------------------

tuskenAttack41 = { 
	attackname = "tuskenAttack41",
	animation = "combo_3b_light",

	requiredWeaponType = ONEHANDED,
	
	range = 6,
	damageRatio = 4.5,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,
		
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
}

AddRandomPoolAttackTargetSkill(tuskenAttack41)

-----------------------------------------------------------------------

tuskenAttack42 = { 
	attackname = "tuskenAttack42",
	animation = "combo_2d_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 6,
	damageRatio = 4,
	speedRatio = 1.5,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 1,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(tuskenAttack42)

-----------------------------------------------------------------------

tuskenAttack43 = { 
	attackname = "tuskenAttack43",
	animation = "combo_5b_light",

	requiredWeaponType = ONEHANDED,
	
	range = 6,
	damageRatio = 4.2,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,
		
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
}

AddRandomPoolAttackTargetSkill(tuskenAttack43)

-----------------------------------------------------------------------

tuskenAttack44 = { 
	attackname = "tuskenAttack44",
	animation = "counter_low_left_light",

	requiredWeaponType = ONEHANDED,
	
	range = 6,
	damageRatio = 4.2,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 25,
	actionAttackChance = 0,
	mindAttackChance = 0,

	dotChance = 50,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
	bleedingType = HEALTH,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddDotPoolAttackTargetSkill(tuskenAttack44)

-----------------------------------------------------------------------

tuskenAttack45 = { 
	attackname = "tuskenAttack45",
	animation = "lower_posture_2hmelee_6",

	requiredWeaponType = ONEHANDED,
	
	range = 6,
	damageRatio = 4,
	speedRatio = 1.5,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 1,
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
}

AddRandomPoolAttackTargetSkill(tuskenAttack45)

-----------------------------------------------------------------------

tuskenAttack46 = { 
	attackname = "tuskenAttack46",
	animation = "combo_3c_light",

	requiredWeaponType = ONEHANDED,
	
	range = 6,
	damageRatio = 4,
	speedRatio = 1.5,
	areaRange = 7,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 1,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(tuskenAttack46)

-----------------------------------------------------------------------

tuskenAttack47 = { 
	attackname = "tuskenAttack47",
	animation = "combo_4b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 6,
	damageRatio = 4,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,
		
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
}

AddRandomPoolAttackTargetSkill(tuskenAttack47)

-----------------------------------------------------------------------

tuskenAttack49 = { 
	attackname = "tuskenAttack49",
	animation = "combo_4b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 6,
	damageRatio = 4.15,
	speedRatio = 1.5,
	areaRange = 7,
	accuracyBonus = 0,
		
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
}

AddRandomPoolAttackTargetSkill(tuskenAttack49)

-----------------------------------------------------------------------

tuskenAttack50 = { 
	attackname = "tuskenAttack50",
	animation = "combo_2b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 6,
	damageRatio = 4.55,
	speedRatio = 1.5,
	areaRange = 7,
	accuracyBonus = 0,
		
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
}

AddRandomPoolAttackTargetSkill(tuskenAttack50)

-----------------------------------------------------------------------

tuskenAttack53 = { 
	attackname = "tuskenAttack53",
	animation = "combo_3c_light",

	requiredWeaponType = ONEHANDED,
	
	range = 6,
	damageRatio = 3.15,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,

	dotChance = 50,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
	bleedingType = 0,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 1,
	diseaseType = HEALTH,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddDotPoolAttackTargetSkill(tuskenAttack53)

-----------------------------------------------------------------------
