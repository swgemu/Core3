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
	attackname = "underhandshot",
	animation = "fire_5_single_medium_face",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 3.0,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 30,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "underhandshot_block",
	CbtSpamCounter = "underhandshot_counter",
	CbtSpamEvade = "underhandshot_evade",
	CbtSpamHit = "underhandshot_hit",
	CbtSpamMiss = "underhandshot_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "knockdownfire",
	animation = "fire_1_special_single_medium",
		
	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 2.5,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 30,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 30,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,
	
	actionAttackChance = 100,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 0,
	focusAttackChance = 0,
	willpowerAttackChance = 0,

	dotChance = 60,
	tickStrengthOfHit = 2,

	fireStrength = 0,
	fireType = HEALTH,

	bleedingStrength = 0,
	bleedingType = 0,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "knockdownfire_block",
	CbtSpamCounter = "knockdownfire_counter",
	CbtSpamEvade = "knockdownfire_evade",
	CbtSpamHit = "knockdownfire_hit",
	CbtSpamMiss = "knockdownfire_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "confusionshot",
	animation = "fire_5_special_single_medium_face",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 3.0,
	speedRatio = 2.3,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 30,
	blindChance = 0,
	stunChance = 40,
	intimidateChance = 0,
	
	CbtSpamBlock = "confusionshot_block",
	CbtSpamCounter = "confusionshot_counter",
	CbtSpamEvade = "confusionshot_evade",
	CbtSpamHit = "confusionshot_hit",
	CbtSpamMiss = "confusionshot_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DotPoolAtt = { 
	attackname = "bleedingshot",
	animation = "fire_3_single_light",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 2.0,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,
		
	dotChance = 60,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
	bleedingType = MIND,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "bleedingshot_block",
	CbtSpamCounter = "bleedingshot_counter",
	CbtSpamEvade = "bleedingshot_evade",
	CbtSpamHit = "bleedingshot_hit",
	CbtSpamMiss = "bleedingshot_miss",
}

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "eyeshot",
	animation = "fire_3_special_single_light_face",

	requiredWeaponType = PISTOL,
	
	range = 65,
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
	blindChance = 40,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "eyeshot_block",
	CbtSpamCounter = "eyeshot_counter",
	CbtSpamEvade = "eyeshot_evade",
	CbtSpamHit = "eyeshot_hit",
	CbtSpamMiss = "eyeshot_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

DotPoolAtt = { 
	attackname = "torsoshot",
	animation = "fire_3_special_single_light_face",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 3.0,
	speedRatio = 2.3,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 100,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,
	
	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 0,
	focusAttackChance = 0,
	willpowerAttackChance = 0,

	dotChance = 60,
	tickStrengthOfHit = 2,

	fireStrength = 0,
	fireType = HEALTH,

	bleedingStrength = 0,
	bleedingType = 0,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "torsoshot_block",
	CbtSpamCounter = "torsoshot_counter",
	CbtSpamEvade = "torsoshot_evade",
	CbtSpamHit = "torsoshot_hit",
	CbtSpamMiss = "torsoshot_miss",
}

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "firelightningsingle1",
	animation = "fire_1_special_single_medium_face",

	requiredWeaponType = RIFLELIGHTNING,
	
	range = 65,
	damageRatio = 3.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "firelightningsingle1_block",
	CbtSpamCounter = "firelightningsingle1_counter",
	CbtSpamEvade = "firelightningsingle1_evade",
	CbtSpamHit = "firelightningsingle1_hit",
	CbtSpamMiss = "firelightningsingle1_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "firelightningcone1",
	animation = "fire_area_medium",

	requiredWeaponType = RIFLELIGHTNING,
	
	range = 65,
	damageRatio = 3.0,
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
	
	CbtSpamBlock = "firelightningcone1_block",
	CbtSpamCounter = "firelightningcone1_counter",
	CbtSpamEvade = "firelightningcone1_evade",
	CbtSpamHit = "firelightningcone1_hit",
	CbtSpamMiss = "firelightningcone1_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "firelightningsingle2",
	animation = "fire_1_special_single_medium_face",

	requiredWeaponType = RIFLELIGHTNING,
	
	range = 65,
	damageRatio = 5.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "firelightningsingle2_block",
	CbtSpamCounter = "firelightningsingle2_counter",
	CbtSpamEvade = "firelightningsingle2_evade",
	CbtSpamHit = "firelightningsingle2_hit",
	CbtSpamMiss = "firelightningsingle2_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "sprayshot",
	animation = "fire_7_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 5.5,
	speedRatio = 3.5,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 30,
	blindChance = 30,
	stunChance = 30,
	intimidateChance = 0,
	
	CbtSpamBlock = "sprayshot_block",
	CbtSpamCounter = "sprayshot_counter",
	CbtSpamEvade = "sprayshot_evade",
	CbtSpamHit = "sprayshot_hit",
	CbtSpamMiss = "sprayshot_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "firelightningcone2",
	animation = "fire_area_medium",

	requiredWeaponType = RIFLELIGHTNING,
	
	range = 65,
	damageRatio = 4.0,
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
	
	CbtSpamBlock = "firelightningcone2_block",
	CbtSpamCounter = "firelightningcone2_counter",
	CbtSpamEvade = "firelightningcone2_evade",
	CbtSpamHit = "firelightningcone2_hit",
	CbtSpamMiss = "firelightningcone2_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "fastblast",
	animation = "fire_5_special_single_light",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 4.15,
	speedRatio = 3.05,
	areaRange = 0,
	accuracyBonus = 0,

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
	
	CbtSpamBlock = "fastblast_block",
	CbtSpamCounter = "fastblast_counter",
	CbtSpamEvade = "fastblast_evade",
	CbtSpamHit = "fastblast_hit",
	CbtSpamMiss = "fastblast_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------
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
	attackname = "underhandshot",
	animation = "fire_5_single_medium_face",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 3.0,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 30,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "underhandshot_block",
	CbtSpamCounter = "underhandshot_counter",
	CbtSpamEvade = "underhandshot_evade",
	CbtSpamHit = "underhandshot_hit",
	CbtSpamMiss = "underhandshot_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "knockdownfire",
	animation = "fire_1_special_single_medium",
		
	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 2.5,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 30,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 30,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "knockdownfire_block",
	CbtSpamCounter = "knockdownfire_counter",
	CbtSpamEvade = "knockdownfire_evade",
	CbtSpamHit = "knockdownfire_hit",
	CbtSpamMiss = "knockdownfire_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "confusionshot",
	animation = "fire_5_special_single_medium_face",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 3.0,
	speedRatio = 2.3,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 30,
	blindChance = 0,
	stunChance = 40,
	intimidateChance = 0,
	
	CbtSpamBlock = "confusionshot_block",
	CbtSpamCounter = "confusionshot_counter",
	CbtSpamEvade = "confusionshot_evade",
	CbtSpamHit = "confusionshot_hit",
	CbtSpamMiss = "confusionshot_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DotPoolAtt = { 
	attackname = "bleedingshot",
	animation = "fire_3_single_light",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 2.0,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,
		
	dotChance = 60,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
	bleedingType = MIND,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "bleedingshot_block",
	CbtSpamCounter = "bleedingshot_counter",
	CbtSpamEvade = "bleedingshot_evade",
	CbtSpamHit = "bleedingshot_hit",
	CbtSpamMiss = "bleedingshot_miss",
}

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "eyeshot",
	animation = "fire_3_special_single_light_face",

	requiredWeaponType = PISTOL,
	
	range = 65,
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
	blindChance = 40,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "eyeshot_block",
	CbtSpamCounter = "eyeshot_counter",
	CbtSpamEvade = "eyeshot_evade",
	CbtSpamHit = "eyeshot_hit",
	CbtSpamMiss = "eyeshot_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

DotPoolAtt = { 
	attackname = "torsoshot",
	animation = "fire_3_special_single_light_face",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 3.0,
	speedRatio = 2.3,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 100,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,
	
	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 0,
	focusAttackChance = 0,
	willpowerAttackChance = 0,

	dotChance = 60,
	tickStrengthOfHit = 2,

	fireStrength = 50,
	fireType = HEALTH,

	bleedingStrength = 0,
	bleedingType = 0,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "torsoshot_block",
	CbtSpamCounter = "torsoshot_counter",
	CbtSpamEvade = "torsoshot_evade",
	CbtSpamHit = "torsoshot_hit",
	CbtSpamMiss = "torsoshot_miss",
}

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "firelightningsingle1",
	animation = "fire_1_special_single_medium_face",

	requiredWeaponType = RIFLELIGHTNING,
	
	range = 65,
	damageRatio = 3.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "firelightningsingle1_block",
	CbtSpamCounter = "firelightningsingle1_counter",
	CbtSpamEvade = "firelightningsingle1_evade",
	CbtSpamHit = "firelightningsingle1_hit",
	CbtSpamMiss = "firelightningsingle1_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "firelightningcone1",
	animation = "fire_area_medium",

	requiredWeaponType = RIFLELIGHTNING,
	
	range = 65,
	damageRatio = 3.0,
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
	
	CbtSpamBlock = "firelightningcone1_block",
	CbtSpamCounter = "firelightningcone1_counter",
	CbtSpamEvade = "firelightningcone1_evade",
	CbtSpamHit = "firelightningcone1_hit",
	CbtSpamMiss = "firelightningcone1_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "firelightningsingle2",
	animation = "fire_1_special_single_medium_face",

	requiredWeaponType = RIFLELIGHTNING,
	
	range = 65,
	damageRatio = 5.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "firelightningsingle2_block",
	CbtSpamCounter = "firelightningsingle2_counter",
	CbtSpamEvade = "firelightningsingle2_evade",
	CbtSpamHit = "firelightningsingle2_hit",
	CbtSpamMiss = "firelightningsingle2_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "sprayshot",
	animation = "fire_7_single_medium",

	requiredWeaponType = CARBINE,
	
	range = 64,
	damageRatio = 5.5,
	speedRatio = 3.5,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 30,
	blindChance = 30,
	stunChance = 30,
	intimidateChance = 0,
	
	CbtSpamBlock = "sprayshot_block",
	CbtSpamCounter = "sprayshot_counter",
	CbtSpamEvade = "sprayshot_evade",
	CbtSpamHit = "sprayshot_hit",
	CbtSpamMiss = "sprayshot_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "firelightningcone2",
	animation = "fire_area_medium",

	requiredWeaponType = RIFLELIGHTNING,
	
	range = 65,
	damageRatio = 4.0,
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
	
	CbtSpamBlock = "firelightningcone2_block",
	CbtSpamCounter = "firelightningcone2_counter",
	CbtSpamEvade = "firelightningcone2_evade",
	CbtSpamHit = "firelightningcone2_hit",
	CbtSpamMiss = "firelightningcone2_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "fastblast",
	animation = "fire_5_special_single_light",

	requiredWeaponType = PISTOL,
	
	range = 65,
	damageRatio = 4.15,
	speedRatio = 3.05,
	areaRange = 0,
	accuracyBonus = 0,

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
	
	CbtSpamBlock = "fastblast_block",
	CbtSpamCounter = "fastblast_counter",
	CbtSpamEvade = "fastblast_evade",
	CbtSpamHit = "fastblast_hit",
	CbtSpamMiss = "fastblast_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------
