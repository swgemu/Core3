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
-------------------------------NOVICE----------------------------------

CmbtEnhaceSkill = {
	skillname = "intimidate1",
	animation = "intimidate",

	range = 15,

	duration = 30.0,
	
	speedRatio = 1.0,

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

	selfEffect = "clienteffect/combat_special_attacker_intimidate.cef",

	FlyText = ""
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

HealEnhaceSkill = {
	skillname = "berserk1",
	effect = "clienteffect/combat_special_attacker_berserk.cef",
	
	duration = 30.0,
	
	speed = 1.0,

	healthBonus = 0,
	actionBonus = 0,
	mindBonus = 0,

	damageBonus = 10,
	accuracyBonus = -10,

	defenseBonus = 0,
	speedBonus = 0,

	StartFlyText = "go_berserk", 
	FinishFlyText = "no_berserk",
}

--AddEnhanceSelfSkill(HealEnhaceSkill)

-----------------------------------------------------------------------

EnhanceSkill = {
	skillname = "centerofbeing",
	effect = "",

	StartFlyText = "", 
	FinishFlyText = ""
}

AddEnhanceSelfSkill(EnhanceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "warcry1",
	animation = "warcry",

	range = 15,

	duration = 30.0,
	
	speedRatio = 1.0,

	meleeDamagePenalty = 0,
	rangedDamagePenalty = 0,

	meleeAccuracyPenalty = 0,
	rangedAccuracyPenalty = 0,

	defensePenalty = 0,
	speedPenalty = 0,

	nextAttackDelay = 10,

	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	selfEffect = "clienteffect/combat_special_attacker_warcry.cef",

	FlyText = ""
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee1hlunge1",
	animation = "lower_posture_1hmelee_1",

	requiredWeaponType = ONEHANDED,
	
	range = 20,
	damageRatio = 1.0,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 40,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmlunge1",
	animation = "attack_high_center_light_2",

	requiredWeaponType = POLEARM,
	
	range = 20,
	damageRatio = 1.0,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 40,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee2hlunge1",
	animation = "lower_posture_2hmelee_1",

	requiredWeaponType = TWOHANDED,
	
	range = 20,
	damageRatio = 1.0,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 40,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "unarmedlunge1",
	animation = "counter_mid_center_light",

	requiredWeaponType = UNARMED,
	
	range = 20,
	damageRatio = 1.0,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 40,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-------------------------------UNARMED-------------------------------

RandPoolAtt = { 
	attackname = "unarmedhit1",
	animation = "combo_2d_light",

	requiredWeaponType = UNARMED,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "unarmedstun1",
	animation = "combo_4c_light",

	requiredWeaponType = UNARMED,
	
	range = 11,
	damageRatio = 1.0,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 40,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "unarmedblind1",
	animation = "attack_high_center_light_1",

	requiredWeaponType = UNARMED,
	
	range = 11,
	damageRatio = 1.0,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 40,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "unarmedspinattack1",
	animation = "combo_3c_light",

	requiredWeaponType = UNARMED,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------1HANDED----------------------------------------

RandPoolAtt = { 
	attackname = "melee1hhit1",
	animation = "counter_high_center_light",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "melee1hbodyhit1",
	animation = "counter_high_right_light",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 50,
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
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee1hdizzyhit1",
	animation = "combo_2b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 1.0,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 40,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee1hspinattack1",
	animation = "attack_high_right_medium_2",

	requiredWeaponType = ONEHANDED,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------2HANDED--------------------------------------

RandPoolAtt = { 
	attackname = "melee2hhit1",
	animation = "combo_2c_medium",

	requiredWeaponType = TWOHANDED,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "melee2hheadhit1",
	animation = "combo_2d_medium",

	requiredWeaponType = TWOHANDED,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 50,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
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

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee2hsweep1",
	animation = "lower_posture_2hmelee_3",

	requiredWeaponType = TWOHANDED,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 40,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee2hspinattack1",
	animation = "attack_high_right_light_2",

	requiredWeaponType = TWOHANDED,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

------------------------------POLEARMS---------------------------------

RandPoolAtt = { 
	attackname = "polearmhit1",
	animation = "combo_2b_light",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "polearmleghit1",
	animation = "attack_low_left_medium_0",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 50,
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
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmstun1",
	animation = "combo_4a_light",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 1.0,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 40,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmspinattack1",
	animation = "attack_high_left_light_2",

	requiredWeaponType = POLEARM,
	
	range = 11,
	damageRatio = 1.15,
	speedRatio = 1.45,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

--------------------------------MASTER----------------------------------

RandPoolAtt = { 
	attackname = "melee1hlunge2",
	animation = "lower_posture_1hmelee_1",

	requiredWeaponType = ONEHANDED,
	
	range = 20,
	damageRatio = 2.0,
	speedRatio = 1.75,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 1,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee2hlunge2",
	animation = "lower_posture_2hmelee_1",

	requiredWeaponType = TWOHANDED,
	
	range = 20,
	damageRatio = 2.0,
	speedRatio = 1.75,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 1,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmlunge2",
	animation = "lower_posture_polearm_2",

	requiredWeaponType = POLEARM,
	
	range = 20,
	damageRatio = 2.0,
	speedRatio = 1.75,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 1,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "unarmedlunge2",
	animation = "counter_mid_center_light",

	requiredWeaponType = UNARMED,
	
	range = 20,
	damageRatio = 2.0,
	speedRatio = 1.75,
	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 1,
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

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "intimidate2",
	animation = "intimidate",

	range = 15,

	duration = 30.0,
	
	speedRatio = 1.0,

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

	selfEffect = "clienteffect/combat_special_attacker_intimidate.cef",

	FlyText = ""
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)

-----------------------------------------------------------------------

HealEnhaceSkill = {
	skillname = "berserk2",
	effect = "clienteffect/combat_special_attacker_berserk.cef",
	
	duration = 30.0,
	
	speed = 1.0,

	damageBonus = 20,
	accuracyBonus = -10,
	
	defenseBonus = 0,
	speedBonus = 0,

	StartFlyText = "go_berserk", 
	FinishFlyText = "no_berserk",
}

--AddEnhanceSelfSkill(HealEnhaceSkill)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "warcry2",
	animation = "warcry",

	range = 15,
	areaRange = 10,

	duration = 30.0,
	
	speedRatio = 1.0,

	meleeDamagePenalty = 0,
	rangedDamagePenalty = 0,

	meleeAccuracyPenalty = 0,
	rangedAccuracyPenalty = 0,

	defensePenalty = 0,
	speedPenalty = 0,

	nextAttackDelay = 20.0,

	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	selfEffect = "clienteffect/combat_special_attacker_warcry.cef",

	FlyText = ""
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)
