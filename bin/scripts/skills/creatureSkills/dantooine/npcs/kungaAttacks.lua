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

kungaAttack01 = { 
	attackname = "kungaAttack01",
	animation = "lower_posture_2hmelee_2",

	requiredWeaponType = NONE,

	range = 15,
	damageRatio = 4.8,
	speedRatio = 2,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 90,
	actionAttackChance = 0,
	mindAttackChance = 0,
	
	dotChance = 0,
	tickStrengthOfHit = 0,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
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
}

AddDotPoolAttackTargetSkill(kungaAttack01)

-----------------------------------------------------------------------

kungaAttack02 = { 
	attackname = "kungaAttack02",
	animation = "combo_3c_light",

	requiredWeaponType = NONE,
	
	range = 15,
	damageRatio = 4.2,
	speedRatio = 2,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 90,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 1,
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
}

AddDirectPoolAttackTargetSkill(kungaAttack02)

-----------------------------------------------------------------------

kungaAttack03 = { 
	attackname = "kungaAttack03",
	animation = "combo_2c_medium",

	requiredWeaponType = NONE,
	
	range = 15,
	damageRatio = 4.8,
	speedRatio = 2,
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

AddRandomPoolAttackTargetSkill(kungaAttack03)

-----------------------------------------------------------------------

kungaAttack04 = { 
	attackname = "kungaAttack04",
	animation = "lower_posture_2hmelee_6",

	requiredWeaponType = NONE,
	
	range = 15,
	damageRatio = 4.2,
	speedRatio = 2,
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

AddRandomPoolAttackTargetSkill(kungaAttack04)

--------------------------------------------------------------------
kungaAttack05 = { 
	attackname = "kungaAttack05",
	animation = "combo_4a_medium",

	requiredWeaponType = NONE,
	
	range = 15,
	damageRatio = 4.8,
	speedRatio = 2,
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

AddRandomPoolAttackTargetSkill(kungaAttack05)

--------------------------------------------------------------------
kungaAttack06 = { 
	attackname = "kungaAttack06", 
	animation = "combo_2d_medium", 
	
	requiredWeaponType = NONE, 
	
	range = 15,
	damageRatio = 4.2,
	speedRatio = 2,
	areaRange = 7, 
	accuracyBonus = 0, 
	
	knockdownChance = 0, 
	postureDownChance = 0, 
	postureUpChance = 0, 
	dizzyChance = 0, 
	blindChance = 0, 
	stunChance = 0, 
	intimidateChance = 1, 
	
	CbtSpamBlock = "melee_block", 
	CbtSpamCounter = "melee_counter", 
	CbtSpamEvade = "melee_evade", 
	CbtSpamHit = "melee_hit", 
	CbtSpamMiss = "melee_miss", 
	} 
	
AddRandomPoolAttackTargetSkill(kungaAttack06) 

--------------------------------------------------------------------
kungaAttack07 = { 
	attackname = "kungaAttack07", 
	animation = "combo_3b_light", 
	
	requiredWeaponType = NONE, 
	
	range = 15,
	damageRatio = 4.8,
	speedRatio = 2,
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
	
AddRandomPoolAttackTargetSkill(kungaAttack07) 

--------------------------------------------------------------------
kungaAttack08 = { 
	attackname = "kungaAttack08", 
	animation = "combo_3b_medium", 
	
	requiredWeaponType = NONE, 
	
	range = 15,
	damageRatio = 4.2,
	speedRatio = 2,
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
	
AddRandomPoolAttackTargetSkill(kungaAttack08) 

----------------------------------------------------------
--This Attack is for the clan leaders only, its a hard hitting one!
kungaAttack09 = { 
	attackname = "kungaAttack09", 
	animation = "combo_5a_medium",
	
	requiredWeaponType = NONE, 
	
	range = 15,
	damageRatio = 4.8,
	speedRatio = 1,
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
	
AddRandomPoolAttackTargetSkill(kungaAttack09) 
