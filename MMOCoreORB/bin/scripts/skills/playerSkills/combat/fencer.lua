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
	attackname = "melee1hhit2",
	animation = "combo_4a_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 3.5,
	speedRatio = 1.25,
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
	
	CbtSpamBlock = "chosun_block",
	CbtSpamCounter = "chosun_counter",
	CbtSpamEvade = "chosun_evade",
	CbtSpamHit = "chosun_hit",
	CbtSpamMiss = "chosun_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "melee1hscatterhit1",
	animation = "combo_3b_light",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 3.0,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	healthAttackChance = 85,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,
	
	actionAttackChance = 90,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 12,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
	
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "scatterstab_block",
	CbtSpamCounter = "scatterstab_counter",
	CbtSpamEvade = "scatterstab_evade",
	CbtSpamHit = "scatterstab_hit",
	CbtSpamMiss = "scatterstab_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee1hdizzyhit2",
	animation = "combo_2d_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 3.5,
	speedRatio = 1.8,
	areaRange = 7,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 40,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "skullslash_block",
	CbtSpamCounter = "skullslash_counter",
	CbtSpamEvade = "skullslash_evade",
	CbtSpamHit = "skullslash_hit",
	CbtSpamMiss = "skullslash_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "melee1hscatterhit2",
	animation = "combo_5b_light",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 4.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	healthAttackChance = 85,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,
	
	actionAttackChance = 95,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 25,
	focusAttackChance = 0,
	willpowerAttackChance = 0,	

	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "scattershiak_block",
	CbtSpamCounter = "scattershiak_counter",
	CbtSpamEvade = "scattershiak_evade",
	CbtSpamHit = "scattershiak_hit",
	CbtSpamMiss = "scattershiak_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------


DotPoolAtt = { 
	attackname = "melee1hhealthhit1",
	animation = "counter_low_left_light",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 1.5,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

	healthAttackChance = 100,
	actionAttackChance = 0,
	mindAttackChance = 0,

	dotChance = 40,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 1,
	bleedingType = HEALTH,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "shiim_block",
	CbtSpamCounter = "shiim_counter",
	CbtSpamEvade = "shiim_evade",
	CbtSpamHit = "shiim_hit",
	CbtSpamMiss = "shiim_miss",
}

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee1hspinattack2",
	animation = "lower_posture_2hmelee_6",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 3.0,
	speedRatio = 1.45,
	areaRange = 7,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 40,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "blindspin_block",
	CbtSpamCounter = "blindspin_counter",
	CbtSpamEvade = "blindspin_evade",
	CbtSpamHit = "blindspin_hit",
	CbtSpamMiss = "blindspin_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------


DotPoolAtt = { 
	attackname = "melee1hhealthhit2",
	animation = "combo_3c_light",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 3.0,
	speedRatio = 1.45,
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
	
	CbtSpamBlock = "shiimshiak_block",
	CbtSpamCounter = "shiimshiak_counter",
	CbtSpamEvade = "shiimshiak_evade",
	CbtSpamHit = "shiimshiak_hit",
	CbtSpamMiss = "shiimshiak_miss",
}

AddDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "melee1hbodyhit2",
	animation = "combo_4b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 2.5,
	speedRatio = 1.45,
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
	
	CbtSpamBlock = "saisun_block",
	CbtSpamCounter = "saisun_counter",
	CbtSpamEvade = "saisun_evade",
	CbtSpamHit = "saisun_hit",
	CbtSpamMiss = "saisun_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "melee1hbodyhit3",
	animation = "combo_3a_light",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 3.5,
	speedRatio = 1.45,
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
	
	CbtSpamBlock = "saitok_block",
	CbtSpamCounter = "saitok_counter",
	CbtSpamEvade = "saitok_evade",
	CbtSpamHit = "saitok_hit",
	CbtSpamMiss = "saitok_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee1hblindhit1",
	animation = "combo_4b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 1.45,
	areaRange = 7,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 10,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "blindingstab_block",
	CbtSpamCounter = "blindingstab_counter",
	CbtSpamEvade = "blindingstab_evade",
	CbtSpamHit = "blindingstab_hit",
	CbtSpamMiss = "blindingstab_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee1hblindhit2",
	animation = "combo_2b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 2.5,
	speedRatio = 1.45,
	areaRange = 7,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 40,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "blindingslash_block",
	CbtSpamCounter = "blindingslash_counter",
	CbtSpamEvade = "blindingslash_evade",
	CbtSpamHit = "blindingslash_hit",
	CbtSpamMiss = "blindingslash_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee1hhit3",
	animation = "combo_5a_light",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 5.0,
	speedRatio = 2.0,
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
	blindChance = 40,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "chomok_block",
	CbtSpamCounter = "chomok_counter",
	CbtSpamEvade = "chomok_evade",
	CbtSpamHit = "chomok_hit",
	CbtSpamMiss = "chomok_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------




