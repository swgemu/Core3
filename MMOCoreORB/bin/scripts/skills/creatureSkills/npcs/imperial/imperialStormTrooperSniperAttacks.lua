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

imperialStormTrooperSniperAttack2 = { 
	attackname = "imperialStormTrooperSniperAttack2",
	animation = "fire_1_special_single_medium",

	requiredWeaponType = RIFLE,
	
	range = 75,
	damageRatio = 1.25,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "snipershot_block",
	CbtSpamCounter = "snipershot_counter",
	CbtSpamEvade = "snipershot_evade",
	CbtSpamHit = "snipershot_hit",
	CbtSpamMiss = "snipershot_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperSniperAttack2)

imperialStormTrooperSniperAttack1 = { 
	attackname = "imperialStormTrooperSniperAttack1",
	animation = "fire_area_medium",

	requiredWeaponType = RIFLE,
	
	range = 75,
	damageRatio = 5.0,
	speedRatio = 3.5,
	coneAngle = 60,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "advancedstrafe_block",
	CbtSpamCounter = "advancedstrafe_counter",
	CbtSpamEvade = "advancedstrafe_evade",
	CbtSpamHit = "advancedstrafe_hit",
	CbtSpamMiss = "advancedstrafe_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperSniperAttack1)

-----------------------------------------------------------------------

imperialStormTrooperRiflemanAttack1 = { 
	attackname = "imperialStormTrooperRiflemanAttack1",
	animation = "fire_5_special_single_medium",

	requiredWeaponType = RIFLE,
	
	range = 75,
	damageRatio = 2.0,
	speedRatio = 2.0,
	coneAngle = 60,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "strafeshot_block",
	CbtSpamCounter = "strafeshot_counter",
	CbtSpamEvade = "strafeshot_evade",
	CbtSpamHit = "strafeshot_hit",
	CbtSpamMiss = "strafeshot_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperRiflemanAttack1)

-----------------------------------------------------------------------

imperialStormTrooperRiflemanAttack2 = { 
	attackname = "imperialStormTrooperRiflemanAttack2",
	animation = "fire_1_special_single_medium_face",

	requiredWeaponType = RIFLE,
	
	range = 75,
	damageRatio = 3.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,
	
	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 100,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "masterheadshot_block",
	CbtSpamCounter = "masterheadshot_counter",
	CbtSpamEvade = "masterheadshot_evade",
	CbtSpamHit = "masterheadshot_hit",
	CbtSpamMiss = "masterheadshot_miss",
}

AddDirectPoolAttackTargetSkill(imperialStormTrooperRiflemanAttack2)

-----------------------------------------------------------------------

imperialStormTrooperRiflemanAttack3 = { 
	attackname = "imperialStormTrooperRiflemanAttack3",
	animation = "fire_1_special_single_medium",

	requiredWeaponType = RIFLE,
	
	range = 75,
	damageRatio = 2.5,
	speedRatio = 3.0,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "concealedshot_block",
	CbtSpamCounter = "concealedshot_counter",
	CbtSpamEvade = "concealedshot_evade",
	CbtSpamHit = "concealedshot_hit",
	CbtSpamMiss = "concealedshot_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperRiflemanAttack3)

-----------------------------------------------------------------------

imperialStormTrooperRiflemanAttack4 = { 
	attackname = "imperialStormTrooperRiflemanAttack4",
	animation = "fire_3_special_single_medium",

	requiredWeaponType = RIFLE,
	
	range = 75,
	damageRatio = 2.0,
	speedRatio = 2.1,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 20,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 20,
	intimidateChance = 0,
	
	CbtSpamBlock = "flushingshot_block",
	CbtSpamCounter = "flushingshot_counter",
	CbtSpamEvade = "flushingshot_evade",
	CbtSpamHit = "flushingshot_hit",
	CbtSpamMiss = "flushingshot_miss",
}

AddRandomPoolAttackTargetSkill(imperialStormTrooperRiflemanAttack4)