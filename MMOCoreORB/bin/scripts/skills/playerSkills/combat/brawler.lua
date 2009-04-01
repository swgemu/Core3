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

	duration = 10.0,
	
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
	
	range = 15,
	damageRatio = 1.0,
	speedRatio = 1.25,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "sword1_sweep_block",
	CbtSpamCounter = "sword1_sweep_counter",
	CbtSpamEvade = "sword1_sweep_evade",
	CbtSpamHit = "sword1_sweep_hit",
	CbtSpamMiss = "sword1_sweep_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmlunge1",
	animation = "attack_high_center_light_2",

	requiredWeaponType = POLEARM,
	
	range = 15,
	damageRatio = 1.0,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "polearm_sweep_block",
	CbtSpamCounter = "polearm_sweep_counter",
	CbtSpamEvade = "polearm_sweep_evade",
	CbtSpamHit = "polearm_sweep_hit",
	CbtSpamMiss = "polearm_sweep_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee2hlunge1",
	animation = "lower_posture_2hmelee_1",

	requiredWeaponType = TWOHANDED,
	
	range = 15,
	damageRatio = 1.0,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "sword2_sweep_block",
	CbtSpamCounter = "sword2_sweep_counter",
	CbtSpamEvade = "sword2_sweep_evade",
	CbtSpamHit = "sword2_sweep_hit",
	CbtSpamMiss = "sword2_sweep_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "unarmedlunge1",
	animation = "counter_mid_center_light",

	requiredWeaponType = UNARMED,
	
	range = 15,
	damageRatio = 1.0,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "unarmed_sweep_block",
	CbtSpamCounter = "unarmed_sweep_counter",
	CbtSpamEvade = "unarmed_sweep_evade",
	CbtSpamHit = "unarmed_sweep_hit",
	CbtSpamMiss = "unarmed_sweep_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-------------------------------UNARMED-------------------------------

RandPoolAtt = { 
	attackname = "unarmedhit1",
	animation = "combo_2d_light",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 1.5,
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
	
	CbtSpamBlock = "unarmed_dam1_block",
	CbtSpamCounter = "unarmed_dam1_counter",
	CbtSpamEvade = "unarmed_dam1_evade",
	CbtSpamHit = "unarmed_dam1_hit",
	CbtSpamMiss = "unarmed_dam1_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "unarmedstun1",
	animation = "combo_4c_light",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 1.25,
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
	blindChance = 0,
	stunChance = 20,
	intimidateChance = 0,
	
	CbtSpamBlock = "unarmed_stun_block",
	CbtSpamCounter = "unarmed_stun_counter",
	CbtSpamEvade = "unarmed_stun_evade",
	CbtSpamHit = "unarmed_stun_hit",
	CbtSpamMiss = "unarmed_stun_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "unarmedblind1",
	animation = "attack_high_center_light_1",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 1.5,
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
	blindChance = 10,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "aryxslash_block",
	CbtSpamCounter = "aryxslash_counter",
	CbtSpamEvade = "aryxslash_evade",
	CbtSpamHit = "aryxslash_hit",
	CbtSpamMiss = "aryxslash_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "unarmedspinattack1",
	animation = "combo_3c_light",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 2.0,
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
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "spinningsmash_block",
	CbtSpamCounter = "spinningsmash_counter",
	CbtSpamEvade = "spinningsmash_evade",
	CbtSpamHit = "spinningsmash_hit",
	CbtSpamMiss = "spinningsmash_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------1HANDED----------------------------------------

RandPoolAtt = { 
	attackname = "melee1hhit1",
	animation = "counter_high_center_light",

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

	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "chomai_block",
	CbtSpamCounter = "chomai_counter",
	CbtSpamEvade = "chomai_evade",
	CbtSpamHit = "chomai_hit",
	CbtSpamMiss = "chomai_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "melee1hbodyhit1",
	animation = "counter_high_right_light",

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
	
	CbtSpamBlock = "saimai_block",
	CbtSpamCounter = "saimai_counter",
	CbtSpamEvade = "saimai_evade",
	CbtSpamHit = "saimai_hit",
	CbtSpamMiss = "saimai_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee1hdizzyhit1",
	animation = "combo_2b_medium",

	requiredWeaponType = ONEHANDED,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 1.45,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 10,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "sword1_dizzy_block",
	CbtSpamCounter = "sword1_dizzy_counter",
	CbtSpamEvade = "sword1_dizzy_evade",
	CbtSpamHit = "sword1_dizzy_hit",
	CbtSpamMiss = "sword1_dizzy_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee1hspinattack1",
	animation = "attack_high_right_medium_2",

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
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "slashspin_block",
	CbtSpamCounter = "slashspin_counter",
	CbtSpamEvade = "slashspin_evade",
	CbtSpamHit = "slashspin_hit",
	CbtSpamMiss = "slashspin_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------2HANDED--------------------------------------

RandPoolAtt = { 
	attackname = "melee2hhit1",
	animation = "combo_2c_medium",

	requiredWeaponType = TWOHANDED,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 1.5,
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
	
	CbtSpamBlock = "sword2_dam1_block",
	CbtSpamCounter = "sword2_dam1_counter",
	CbtSpamEvade = "sword2_dam1_evade",
	CbtSpamHit = "sword2_dam1_hit",
	CbtSpamMiss = "sword2_dam1_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "melee2hheadhit1",
	animation = "combo_2d_medium",

	requiredWeaponType = TWOHANDED,
	
	range = 0,
	damageRatio = 1.5,
	speedRatio = 1.6,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

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
	
	CbtSpamBlock = "sword2_head_block",
	CbtSpamCounter = "sword2_head_counter",
	CbtSpamEvade = "sword2_head_evade",
	CbtSpamHit = "sword2_head_hit",
	CbtSpamMiss = "sword2_head_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee2hsweep1",
	animation = "lower_posture_2hmelee_3",

	requiredWeaponType = TWOHANDED,
	
	range = 0,
	damageRatio = 1.5,
	speedRatio = 1.7,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee2hsweep1_block",
	CbtSpamCounter = "melee2hsweep1_counter",
	CbtSpamEvade = "melee2hsweep1_evade",
	CbtSpamHit = "melee2hsweep1_hit",
	CbtSpamMiss = "melee2hsweep1_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee2hspinattack1",
	animation = "attack_high_right_light_2",

	requiredWeaponType = TWOHANDED,
	
	range = 0,
	damageRatio = 2.0,
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
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 1.5,
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
	
	CbtSpamBlock = "polearm_dam1_block",
	CbtSpamCounter = "polearm_dam1_counter",
	CbtSpamEvade = "polearm_dam1_evade",
	CbtSpamHit = "polearm_dam1_hit",
	CbtSpamMiss = "polearm_dam1_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "polearmleghit1",
	animation = "attack_low_left_medium_0",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 1.5,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 100,
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
	
	CbtSpamBlock = "polearm_limbs_block",
	CbtSpamCounter = "polearm_limbs_counter",
	CbtSpamEvade = "polearm_limbs_evade",
	CbtSpamHit = "polearm_limbs_hit",
	CbtSpamMiss = "polearm_limbs_miss",
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmstun1",
	animation = "combo_4a_light",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 1.5,
	speedRatio = 1.6,
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
	stunChance = 20,
	intimidateChance = 0,
	
	CbtSpamBlock = "breathstealer_block",
	CbtSpamCounter = "breathstealer_counter",
	CbtSpamEvade = "breathstealer_evade",
	CbtSpamHit = "breathstealer_hit",
	CbtSpamMiss = "breathstealer_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmspinattack1",
	animation = "attack_high_left_light_2",

	requiredWeaponType = POLEARM,
	
	range = 0,
	damageRatio = 1.5,
	speedRatio = 1.5,
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
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 40,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "sword1_knockdown_block",
	CbtSpamCounter = "sword1_knockdown_counter",
	CbtSpamEvade = "sword1_knockdown_evade",
	CbtSpamHit = "sword1_knockdown_hit",
	CbtSpamMiss = "sword1_knockdown_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "melee2hlunge2",
	animation = "lower_posture_2hmelee_1",

	requiredWeaponType = TWOHANDED,
	
	range = 20,
	damageRatio = 2.0,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 40,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "sword2_knockdown_block",
	CbtSpamCounter = "sword2_knockdown_counter",
	CbtSpamEvade = "sword2_knockdown_evade",
	CbtSpamHit = "sword2_knockdown_hit",
	CbtSpamMiss = "sword2_knockdown_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "polearmlunge2",
	animation = "lower_posture_polearm_2",

	requiredWeaponType = POLEARM,
	
	range = 20,
	damageRatio = 2.0,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 40,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "polearm_knockdown_block",
	CbtSpamCounter = "polearm_knockdown_counter",
	CbtSpamEvade = "polerarm_knockdown_evade",
	CbtSpamHit = "polearm_knockdown_hit",
	CbtSpamMiss = "polearm_knockdown_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

RandPoolAtt = { 
	attackname = "unarmedlunge2",
	animation = "counter_mid_center_light",

	requiredWeaponType = UNARMED,
	
	range = 20,
	damageRatio = 3.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 40,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "unarmed_knockdown_block",
	CbtSpamCounter = "unarmed_knockdown_counter",
	CbtSpamEvade = "unarmed_knockdown_evade",
	CbtSpamHit = "unarmed_knockdown_hit",
	CbtSpamMiss = "unarmed_knockdown_miss",
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------------------

CmbtEnhaceSkill = {
	skillname = "intimidate2",
	animation = "intimidate",

	range = 15,

	duration = 120.0,
	
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
	intimidateChance = 40,

	selfEffect = "clienteffect/combat_special_attacker_intimidate.cef",

	FlyText = ""
}

AddDeBuffAttackTargetSkill(CmbtEnhaceSkill)
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

Berserk = {
	skillname = "berserk1",

	duration = 20,
	
	damage = 25
}

AddBerserkSelfSkill(Berserk)
Berserk = {
	skillname = "berserk2",

	duration = 40,
	
	damage = 75
}

AddBerserkSelfSkill(Berserk)
